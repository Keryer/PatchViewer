use std::collections::{HashMap, HashSet};

use similar::{capture_diff_slices, Algorithm, DiffOp};

use crate::config::DiffOptions;
use crate::model::CfgReorderTag;
use crate::normalizer::{compute_generic_key, conditions_are_inverted};
use crate::parser::{CaseNode, LineRole, ParsedLine, StmtNode};

/// A contiguous structural segment produced by CFG alignment.
#[derive(Debug, Clone)]
pub struct AlignedSegment {
    pub old_indices: Vec<usize>,
    pub new_indices: Vec<usize>,
    pub tag: Option<CfgReorderTag>,
    /// When true (e.g. an inverted `if (c)` vs `if (!c)` header where conditions
    /// are exact logical negations), treat the header as structurally equivalent (`NoiseOnly`).
    pub condition_inverted_pair: bool,
    /// When true, this segment represents a declaration block where lines can be
    /// paired order-independently by canonical representation.
    pub is_declaration_block: bool,
}

pub struct AlignContext<'a> {
    pub old_lines: &'a [ParsedLine],
    pub new_lines: &'a [ParsedLine],
    pub old_generic: Vec<String>,
    pub new_generic: Vec<String>,
    pub options: &'a DiffOptions,
}

impl<'a> AlignContext<'a> {
    pub fn new(
        old_lines: &'a [ParsedLine],
        new_lines: &'a [ParsedLine],
        options: &'a DiffOptions,
    ) -> Self {
        let old_generic = old_lines
            .iter()
            .map(|l| compute_generic_key(l, options))
            .collect();
        let new_generic = new_lines
            .iter()
            .map(|l| compute_generic_key(l, options))
            .collect();
        Self {
            old_lines,
            new_lines,
            old_generic,
            new_generic,
            options,
        }
    }

    fn collect_node_lines(node: &StmtNode, out: &mut Vec<usize>) {
        match node {
            StmtNode::Blank { line_idx }
            | StmtNode::Declaration { line_idx }
            | StmtNode::Simple { line_idx } => out.push(*line_idx),
            StmtNode::Block {
                open_brace_line,
                body,
                close_brace_line,
            } => {
                if let Some(i) = open_brace_line {
                    out.push(*i);
                }
                for n in body {
                    Self::collect_node_lines(n, out);
                }
                if let Some(i) = close_brace_line {
                    out.push(*i);
                }
            }
            StmtNode::If {
                header_line,
                then_open_brace,
                then_body,
                then_close_brace,
                else_line,
                else_open_brace,
                else_body,
                else_close_brace,
                ..
            } => {
                out.push(*header_line);
                if let Some(i) = then_open_brace {
                    out.push(*i);
                }
                for n in then_body {
                    Self::collect_node_lines(n, out);
                }
                if let Some(i) = then_close_brace {
                    out.push(*i);
                }
                if let Some(i) = else_line {
                    out.push(*i);
                }
                if let Some(i) = else_open_brace {
                    out.push(*i);
                }
                for n in else_body {
                    Self::collect_node_lines(n, out);
                }
                if let Some(i) = else_close_brace {
                    out.push(*i);
                }
            }
            StmtNode::Switch {
                header_line,
                open_brace_line,
                cases,
                close_brace_line,
                ..
            } => {
                out.push(*header_line);
                if let Some(i) = open_brace_line {
                    out.push(*i);
                }
                for c in cases {
                    out.push(c.label_line);
                    for n in &c.body {
                        Self::collect_node_lines(n, out);
                    }
                }
                if let Some(i) = close_brace_line {
                    out.push(*i);
                }
            }
            StmtNode::LabelBlock {
                label_line, body, ..
            } => {
                out.push(*label_line);
                for n in body {
                    Self::collect_node_lines(n, out);
                }
            }
        }
    }

    fn node_tokens(&self, node: &StmtNode, is_old: bool) -> HashSet<String> {
        let mut idxs = Vec::new();
        Self::collect_node_lines(node, &mut idxs);
        let generic = if is_old {
            &self.old_generic
        } else {
            &self.new_generic
        };
        let mut set = HashSet::new();
        for idx in idxs {
            let g = &generic[idx];
            if g.is_empty() || g == "{" || g == "}" {
                continue;
            }
            for w in g.split_whitespace() {
                set.insert(w.to_string());
            }
        }
        set
    }

    fn nodes_tokens(&self, nodes: &[StmtNode], is_old: bool) -> HashSet<String> {
        let mut set = HashSet::new();
        for n in nodes {
            set.extend(self.node_tokens(n, is_old));
        }
        set
    }

    fn jaccard(a: &HashSet<String>, b: &HashSet<String>) -> f64 {
        if a.is_empty() && b.is_empty() {
            return 1.0;
        }
        if a.is_empty() || b.is_empty() {
            return 0.0;
        }
        let inter = a.intersection(b).count();
        let union = a.union(b).count();
        if union == 0 {
            0.0
        } else {
            inter as f64 / union as f64
        }
    }

    fn body_similarity(&self, old_body: &[StmtNode], new_body: &[StmtNode]) -> f64 {
        let a = self.nodes_tokens(old_body, true);
        let b = self.nodes_tokens(new_body, false);
        Self::jaccard(&a, &b)
    }

    fn generic_str(&self, raw_expr: &str) -> String {
        let mut in_bc = false;
        let toks = crate::parser::lex_line(raw_expr, &mut in_bc);
        let dummy = ParsedLine {
            line_no: 0,
            raw_text: raw_expr.to_string(),
            indent: 0,
            tokens: toks,
            role: LineRole::Code,
        };
        compute_generic_key(&dummy, self.options)
    }

    fn node_structural_key(&self, node: &StmtNode, is_old: bool) -> String {
        let generic = if is_old {
            &self.old_generic
        } else {
            &self.new_generic
        };
        match node {
            StmtNode::Blank { .. } => "<BLANK>".to_string(),
            StmtNode::Declaration { line_idx } => format!("DECL:{}", generic[*line_idx]),
            StmtNode::Simple { line_idx } => format!("STMT:{}", generic[*line_idx]),
            StmtNode::Block { .. } => "BLOCK".to_string(),
            StmtNode::If {
                cond_raw,
                then_body,
                else_body,
                ..
            } => {
                let has_nested_ctrl = then_body.iter().chain(else_body.iter()).any(|n| {
                    matches!(
                        n,
                        StmtNode::Block { .. } | StmtNode::If { .. } | StmtNode::Switch { .. }
                    )
                });
                format!(
                    "IF:{}|ELSE:{}|N:{}",
                    self.generic_str(cond_raw),
                    !else_body.is_empty(),
                    has_nested_ctrl
                )
            }
            StmtNode::Switch { expr_raw, .. } => {
                format!("SWITCH:{}", self.generic_str(expr_raw))
            }
            StmtNode::LabelBlock { body, .. } => {
                let mut parts = Vec::new();
                for b in body.iter().take(2) {
                    let mut idxs = Vec::new();
                    Self::collect_node_lines(b, &mut idxs);
                    for i in idxs {
                        if !generic[i].is_empty() {
                            parts.push(generic[i].clone());
                        }
                    }
                }
                format!("LABEL:{}", parts.join(";"))
            }
        }
    }

    pub fn align_ast(&self, old_ast: &[StmtNode], new_ast: &[StmtNode]) -> Vec<AlignedSegment> {
        let mut raw_segments = if !self.options.align_control_flow {
            self.align_without_cfg(old_ast, new_ast)
        } else {
            let mut out = Vec::new();
            self.align_node_slice(old_ast, new_ast, None, &mut out);
            out
        };

        // Merge consecutive declaration-block segments so all declarations are compared together.
        if self.options.collapse_declarations {
            let mut merged: Vec<AlignedSegment> = Vec::with_capacity(raw_segments.len());
            for seg in raw_segments.drain(..) {
                if seg.is_declaration_block {
                    if let Some(last) = merged.last_mut() {
                        if last.is_declaration_block {
                            last.old_indices.extend(seg.old_indices);
                            last.new_indices.extend(seg.new_indices);
                            continue;
                        }
                    }
                }
                merged.push(seg);
            }
            merged
        } else {
            raw_segments
        }
    }

    fn align_without_cfg(&self, old_ast: &[StmtNode], new_ast: &[StmtNode]) -> Vec<AlignedSegment> {
        let mut old_idxs = Vec::new();
        for n in old_ast {
            Self::collect_node_lines(n, &mut old_idxs);
        }
        let mut new_idxs = Vec::new();
        for n in new_ast {
            Self::collect_node_lines(n, &mut new_idxs);
        }

        if !self.options.collapse_declarations {
            return vec![AlignedSegment {
                old_indices: old_idxs,
                new_indices: new_idxs,
                tag: None,
                condition_inverted_pair: false,
                is_declaration_block: false,
            }];
        }

        let old_decls: Vec<usize> = old_idxs
            .iter()
            .copied()
            .filter(|&i| self.old_lines[i].role == LineRole::Declaration)
            .collect();
        let new_decls: Vec<usize> = new_idxs
            .iter()
            .copied()
            .filter(|&i| self.new_lines[i].role == LineRole::Declaration)
            .collect();
        let mut out = Vec::new();
        if !old_decls.is_empty() || !new_decls.is_empty() {
            let first_old = old_decls.first().copied().unwrap_or(usize::MAX);
            let last_old = old_decls.last().copied().unwrap_or(0);
            let first_new = new_decls.first().copied().unwrap_or(usize::MAX);
            let last_new = new_decls.last().copied().unwrap_or(0);

            let pre_old: Vec<usize> = old_idxs.iter().copied().filter(|&i| i < first_old).collect();
            let pre_new: Vec<usize> = new_idxs.iter().copied().filter(|&i| i < first_new).collect();
            if !pre_old.is_empty() || !pre_new.is_empty() {
                out.push(AlignedSegment {
                    old_indices: pre_old,
                    new_indices: pre_new,
                    tag: None,
                    condition_inverted_pair: false,
                    is_declaration_block: false,
                });
            }
            out.push(AlignedSegment {
                old_indices: old_decls,
                new_indices: new_decls,
                tag: Some(CfgReorderTag::DeclarationBlock),
                condition_inverted_pair: false,
                is_declaration_block: true,
            });
            let post_old: Vec<usize> = old_idxs
                .iter()
                .copied()
                .filter(|&i| i > last_old && self.old_lines[i].role != LineRole::Declaration)
                .collect();
            let post_new: Vec<usize> = new_idxs
                .iter()
                .copied()
                .filter(|&i| i > last_new && self.new_lines[i].role != LineRole::Declaration)
                .collect();
            if !post_old.is_empty() || !post_new.is_empty() {
                out.push(AlignedSegment {
                    old_indices: post_old,
                    new_indices: post_new,
                    tag: None,
                    condition_inverted_pair: false,
                    is_declaration_block: false,
                });
            }
        } else {
            out.push(AlignedSegment {
                old_indices: old_idxs,
                new_indices: new_idxs,
                tag: None,
                condition_inverted_pair: false,
                is_declaration_block: false,
            });
        }
        out
    }

    fn count_non_brace_equal_lines(&self, segs: &[AlignedSegment]) -> usize {
        let mut matched = 0usize;
        for seg in segs {
            if seg.is_declaration_block || seg.old_indices.is_empty() || seg.new_indices.is_empty()
            {
                continue;
            }
            if seg.condition_inverted_pair
                && seg.old_indices.len() == 1
                && seg.new_indices.len() == 1
            {
                matched += 1;
                continue;
            }
            let ok: Vec<&str> = seg
                .old_indices
                .iter()
                .map(|&i| self.old_generic[i].as_str())
                .collect();
            let nk: Vec<&str> = seg
                .new_indices
                .iter()
                .map(|&i| self.new_generic[i].as_str())
                .collect();
            for op in capture_diff_slices(Algorithm::Myers, &ok, &nk) {
                if let DiffOp::Equal {
                    old_index, len, ..
                } = op
                {
                    for k in 0..len {
                        let g = ok[old_index + k];
                        if !g.is_empty() && g != "{" && g != "}" {
                            matched += 1;
                        }
                    }
                }
            }
        }
        matched
    }

    fn count_node_line_len(node: &StmtNode) -> usize {
        let mut v = Vec::new();
        Self::collect_node_lines(node, &mut v);
        v.len()
    }

    fn align_node_slice(
        &self,
        old_nodes: &[StmtNode],
        new_nodes: &[StmtNode],
        inherited_tag: Option<CfgReorderTag>,
        out: &mut Vec<AlignedSegment>,
    ) {
        let mut local_out = Vec::new();
        self.align_node_slice_inner(old_nodes, new_nodes, inherited_tag.clone(), &mut local_out);

        // Monotonicity guardrail: never allow CFG container splits on executable code
        // to match fewer non-brace lines than flat Myers on the same executable lines.
        let has_both_sides = local_out
            .iter()
            .any(|s| !s.is_declaration_block && !s.old_indices.is_empty())
            && local_out
                .iter()
                .any(|s| !s.is_declaration_block && !s.new_indices.is_empty());

        if has_both_sides && local_out.iter().filter(|s| !s.is_declaration_block).count() > 1 {
            let mut decl_segs = Vec::new();
            let mut flat_old = Vec::new();
            let mut flat_new = Vec::new();
            let mut exec_segs = Vec::new();

            for seg in &local_out {
                if seg.is_declaration_block {
                    decl_segs.push(seg.clone());
                } else {
                    flat_old.extend_from_slice(&seg.old_indices);
                    flat_new.extend_from_slice(&seg.new_indices);
                    exec_segs.push(seg.clone());
                }
            }

            flat_old.sort_unstable();
            flat_old.dedup();
            flat_new.sort_unstable();
            flat_new.dedup();

            let flat_seg = AlignedSegment {
                old_indices: flat_old,
                new_indices: flat_new,
                tag: inherited_tag,
                condition_inverted_pair: false,
                is_declaration_block: false,
            };
            let ast_score = self.count_non_brace_equal_lines(&exec_segs);
            let flat_score = self.count_non_brace_equal_lines(std::slice::from_ref(&flat_seg));

            if ast_score < flat_score {
                out.extend(decl_segs);
                out.push(flat_seg);
                return;
            }
        }

        out.extend(local_out);
    }

    fn align_node_slice_inner(
        &self,
        old_nodes: &[StmtNode],
        new_nodes: &[StmtNode],
        inherited_tag: Option<CfgReorderTag>,
        out: &mut Vec<AlignedSegment>,
    ) {
        let old_nb: Vec<&StmtNode> = old_nodes
            .iter()
            .filter(|n| !matches!(n, StmtNode::Blank { .. }))
            .collect();
        let new_nb: Vec<&StmtNode> = new_nodes
            .iter()
            .filter(|n| !matches!(n, StmtNode::Blank { .. }))
            .collect();

        if old_nb.is_empty() && new_nb.is_empty() {
            return;
        }
        if old_nb.is_empty() {
            let mut idxs = Vec::new();
            for n in new_nb {
                Self::collect_node_lines(n, &mut idxs);
            }
            out.push(AlignedSegment {
                old_indices: Vec::new(),
                new_indices: idxs,
                tag: inherited_tag,
                condition_inverted_pair: false,
                is_declaration_block: false,
            });
            return;
        }
        if new_nb.is_empty() {
            let mut idxs = Vec::new();
            for n in old_nb {
                Self::collect_node_lines(n, &mut idxs);
            }
            out.push(AlignedSegment {
                old_indices: idxs,
                new_indices: Vec::new(),
                tag: inherited_tag,
                condition_inverted_pair: false,
                is_declaration_block: false,
            });
            return;
        }

        let old_keys: Vec<String> = old_nb
            .iter()
            .map(|n| self.structural_match_key(n, true))
            .collect();
        let new_keys: Vec<String> = new_nb
            .iter()
            .map(|n| self.structural_match_key(n, false))
            .collect();

        let ops = capture_diff_slices(Algorithm::Myers, &old_keys, &new_keys);

        let has_delete_or_replace = |range: std::ops::Range<usize>| -> bool {
            ops[range].iter().any(|op| {
                matches!(op, DiffOp::Delete { .. } | DiffOp::Replace { .. })
            })
        };
        let has_insert_or_replace = |range: std::ops::Range<usize>| -> bool {
            ops[range].iter().any(|op| {
                matches!(op, DiffOp::Insert { .. } | DiffOp::Replace { .. })
            })
        };

        // Pre-pass: find LabelBlocks across non-Equal ops so relocated `goto loc_xxx:` blocks
        // separated by unchanged statements still pair cleanly!
        let mut unmatched_old_labels = Vec::new();
        let mut unmatched_new_labels = Vec::new();
        for op in &ops {
            match *op {
                DiffOp::Delete {
                    old_index,
                    old_len: len,
                    ..
                } => {
                    for oi in old_index..old_index + len {
                        if matches!(old_nb[oi], StmtNode::LabelBlock { .. }) {
                            unmatched_old_labels.push(oi);
                        }
                    }
                }
                DiffOp::Insert {
                    new_index,
                    new_len: len,
                    ..
                } => {
                    for nj in new_index..new_index + len {
                        if matches!(new_nb[nj], StmtNode::LabelBlock { .. }) {
                            unmatched_new_labels.push(nj);
                        }
                    }
                }
                DiffOp::Replace {
                    old_index,
                    old_len,
                    new_index,
                    new_len,
                } => {
                    for oi in old_index..old_index + old_len {
                        if matches!(old_nb[oi], StmtNode::LabelBlock { .. }) {
                            unmatched_old_labels.push(oi);
                        }
                    }
                    for nj in new_index..new_index + new_len {
                        if matches!(new_nb[nj], StmtNode::LabelBlock { .. }) {
                            unmatched_new_labels.push(nj);
                        }
                    }
                }
                DiffOp::Equal { .. } => {}
            }
        }

        let mut global_label_old_to_new: HashMap<usize, usize> = HashMap::new();
        let mut global_label_new_consumed: HashSet<usize> = HashSet::new();
        for &oi in &unmatched_old_labels {
            let o_len = Self::count_node_line_len(old_nb[oi]);
            if o_len > 60 {
                continue;
            }
            if let StmtNode::LabelBlock { body: ob, .. } = old_nb[oi] {
                let mut best_nj = None;
                let mut best_sim = 0.48f64;
                for &nj in &unmatched_new_labels {
                    if global_label_new_consumed.contains(&nj) {
                        continue;
                    }
                    let n_len = Self::count_node_line_len(new_nb[nj]);
                    if n_len > 60 || o_len.min(n_len) * 3 < o_len.max(n_len) {
                        continue;
                    }
                    if let StmtNode::LabelBlock { body: nb, .. } = new_nb[nj] {
                        let sim = self.body_similarity(ob, nb);
                        if sim > best_sim {
                            best_sim = sim;
                            best_nj = Some(nj);
                        }
                    }
                }
                if let Some(nj) = best_nj {
                    global_label_old_to_new.insert(oi, nj);
                    global_label_new_consumed.insert(nj);
                }
            }
        }

        for (op_idx, &op) in ops.iter().enumerate() {
            match op {
                DiffOp::Equal {
                    old_index,
                    new_index,
                    len,
                } => {
                    for k in 0..len {
                        let o = old_nb[old_index + k];
                        let n = new_nb[new_index + k];
                        if matches!(o, StmtNode::LabelBlock { .. })
                            && matches!(n, StmtNode::LabelBlock { .. })
                        {
                            let crossed_before_after = (has_delete_or_replace(0..op_idx)
                                && has_insert_or_replace((op_idx + 1)..ops.len()))
                                || (has_insert_or_replace(0..op_idx)
                                    && has_delete_or_replace((op_idx + 1)..ops.len()));
                            self.align_moved_label(o, n, crossed_before_after, out);
                        } else {
                            self.align_paired_nodes(o, n, inherited_tag.clone(), out);
                        }
                    }
                }
                DiffOp::Delete {
                    old_index,
                    old_len: len,
                    ..
                } => {
                    let mut buf: Vec<&StmtNode> = Vec::new();
                    for oi in old_index..old_index + len {
                        if let Some(&nj) = global_label_old_to_new.get(&oi) {
                            self.emit_unmatched_slice(&buf, true, inherited_tag.clone(), out);
                            buf.clear();
                            self.align_moved_label(old_nb[oi], new_nb[nj], true, out);
                        } else {
                            buf.push(old_nb[oi]);
                        }
                    }
                    self.emit_unmatched_slice(&buf, true, inherited_tag.clone(), out);
                }
                DiffOp::Insert {
                    new_index,
                    new_len: len,
                    ..
                } => {
                    let mut buf: Vec<&StmtNode> = Vec::new();
                    for nj in new_index..new_index + len {
                        if global_label_new_consumed.contains(&nj) {
                            self.emit_unmatched_slice(&buf, false, inherited_tag.clone(), out);
                            buf.clear();
                        } else {
                            buf.push(new_nb[nj]);
                        }
                    }
                    self.emit_unmatched_slice(&buf, false, inherited_tag.clone(), out);
                }
                DiffOp::Replace {
                    old_index,
                    old_len,
                    new_index,
                    new_len,
                } => {
                    // Check if any label blocks in this Replace were paired globally across different ops;
                    // if a label was paired with a label outside this Replace, handle it cleanly.
                    let mut old_slice: Vec<&StmtNode> = Vec::new();
                    let mut moved_pairs_here: Vec<(usize, usize)> = Vec::new();
                    for oi in old_index..old_index + old_len {
                        if let Some(&nj) = global_label_old_to_new.get(&oi) {
                            let inside_this_replace = nj >= new_index && nj < new_index + new_len;
                            if inside_this_replace {
                                old_slice.push(old_nb[oi]);
                            } else {
                                moved_pairs_here.push((oi, nj));
                            }
                        } else {
                            old_slice.push(old_nb[oi]);
                        }
                    }
                    let mut new_slice: Vec<&StmtNode> = Vec::new();
                    for nj in new_index..new_index + new_len {
                        let paired_outside = global_label_new_consumed.contains(&nj)
                            && !global_label_old_to_new
                                .iter()
                                .any(|(&oi, &mapped_nj)| mapped_nj == nj && oi >= old_index && oi < old_index + old_len);
                        if !paired_outside {
                            new_slice.push(new_nb[nj]);
                        }
                    }
                    if !old_slice.is_empty() || !new_slice.is_empty() {
                        self.align_replaced_slice(&old_slice, &new_slice, inherited_tag.clone(), out);
                    }
                    for (oi, nj) in moved_pairs_here {
                        self.align_moved_label(old_nb[oi], new_nb[nj], true, out);
                    }
                }
            }
        }
    }

    fn structural_match_key(&self, node: &StmtNode, is_old: bool) -> String {
        match node {
            StmtNode::Declaration { .. } if self.options.collapse_declarations => {
                "__DECL__".to_string()
            }
            StmtNode::Block { .. } => "__BLOCK__".to_string(),
            StmtNode::Switch { expr_raw, .. } => {
                format!("__SWITCH__:{}", self.generic_str(expr_raw))
            }
            _ => self.node_structural_key(node, is_old),
        }
    }

    fn emit_unmatched_slice(
        &self,
        slice: &[&StmtNode],
        is_old: bool,
        inherited_tag: Option<CfgReorderTag>,
        out: &mut Vec<AlignedSegment>,
    ) {
        if slice.is_empty() {
            return;
        }
        let mut idxs = Vec::new();
        for n in slice {
            Self::collect_node_lines(n, &mut idxs);
        }
        if idxs.is_empty() {
            return;
        }
        let is_decl = self.options.collapse_declarations
            && slice
                .iter()
                .all(|n| matches!(n, StmtNode::Declaration { .. }));
        let tag = if is_decl {
            Some(CfgReorderTag::DeclarationBlock)
        } else {
            inherited_tag
        };
        if is_old {
            out.push(AlignedSegment {
                old_indices: idxs,
                new_indices: Vec::new(),
                tag,
                condition_inverted_pair: false,
                is_declaration_block: is_decl,
            });
        } else {
            out.push(AlignedSegment {
                old_indices: Vec::new(),
                new_indices: idxs,
                tag,
                condition_inverted_pair: false,
                is_declaration_block: is_decl,
            });
        }
    }

    fn align_replaced_slice(
        &self,
        old_slice: &[&StmtNode],
        new_slice: &[&StmtNode],
        inherited_tag: Option<CfgReorderTag>,
        out: &mut Vec<AlignedSegment>,
    ) {
        // 1. Both sides are pure Declaration runs
        if self.options.collapse_declarations
            && !old_slice.is_empty()
            && !new_slice.is_empty()
            && old_slice
                .iter()
                .all(|n| matches!(n, StmtNode::Declaration { .. }))
            && new_slice
                .iter()
                .all(|n| matches!(n, StmtNode::Declaration { .. }))
        {
            let mut o_idxs = Vec::new();
            for n in old_slice {
                Self::collect_node_lines(n, &mut o_idxs);
            }
            let mut n_idxs = Vec::new();
            for n in new_slice {
                Self::collect_node_lines(n, &mut n_idxs);
            }
            out.push(AlignedSegment {
                old_indices: o_idxs,
                new_indices: n_idxs,
                tag: Some(CfgReorderTag::DeclarationBlock),
                condition_inverted_pair: false,
                is_declaration_block: true,
            });
            return;
        }

        // 2. Check Guard Clause vs Nested If pattern across this replaced slice
        if let Some(true) =
            self.try_align_guard_clause(old_slice, new_slice, inherited_tag.clone(), out)
        {
            return;
        }

        // 2b. Check Wrapper `If` (e.g. added depth/bounds `if (cond) { body }` wrapping existing body)
        //     OR LabelBlock <-> Block container equivalence (`LABEL_3: ...` <-> `do { ... } while (...)`)
        if let Some(true) =
            self.try_align_wrapper_or_loop_container(old_slice, new_slice, inherited_tag.clone(), out)
        {
            return;
        }

        // 3. Pair relocated LabelBlocks + If/Switch inside the replaced slice
        let mut old_used = vec![false; old_slice.len()];
        let mut new_used = vec![false; new_slice.len()];

        let mut label_pairs: Vec<(usize, usize)> = Vec::new();
        for (oi, o) in old_slice.iter().enumerate() {
            if let StmtNode::LabelBlock { body: ob, .. } = o {
                let mut best_j = None;
                let mut best_sim = 0.44f64;
                for (nj, n) in new_slice.iter().enumerate() {
                    if new_used[nj] {
                        continue;
                    }
                    if let StmtNode::LabelBlock { body: nb, .. } = n {
                        let sim = self.body_similarity(ob, nb);
                        if sim > best_sim {
                            best_sim = sim;
                            best_j = Some(nj);
                        }
                    }
                }
                if let Some(nj) = best_j {
                    old_used[oi] = true;
                    new_used[nj] = true;
                    label_pairs.push((oi, nj));
                }
            }
        }

        let mut struct_pairs: Vec<(usize, usize)> = Vec::new();
        for (oi, o) in old_slice.iter().enumerate() {
            if old_used[oi] {
                continue;
            }
            match o {
                StmtNode::If {
                    then_body: ot,
                    else_body: oe,
                    cond_raw: oc,
                    ..
                } => {
                    let mut best_j = None;
                    let mut best_score = 0.25f64;
                    for (nj, n) in new_slice.iter().enumerate() {
                        if new_used[nj] {
                            continue;
                        }
                        if let StmtNode::If {
                            then_body: nt,
                            else_body: ne,
                            cond_raw: nc,
                            ..
                        } = n
                        {
                            let direct = self.body_similarity(ot, nt)
                                + if oe.is_empty() && ne.is_empty() {
                                    0.0
                                } else {
                                    self.body_similarity(oe, ne)
                                };
                            let inv = self.body_similarity(ot, ne) + self.body_similarity(oe, nt);
                            let cond_bonus = if conditions_are_inverted(
                                &self.generic_str(oc),
                                &self.generic_str(nc),
                            ) || self.generic_str(oc) == self.generic_str(nc)
                            {
                                0.35
                            } else {
                                0.0
                            };
                            let score = direct.max(inv) + cond_bonus;
                            if score > best_score {
                                best_score = score;
                                best_j = Some(nj);
                            }
                        }
                    }
                    if let Some(nj) = best_j {
                        old_used[oi] = true;
                        new_used[nj] = true;
                        struct_pairs.push((oi, nj));
                    }
                }
                StmtNode::Switch { .. } => {
                    for (nj, n) in new_slice.iter().enumerate() {
                        if !new_used[nj] && matches!(n, StmtNode::Switch { .. }) {
                            old_used[oi] = true;
                            new_used[nj] = true;
                            struct_pairs.push((oi, nj));
                            break;
                        }
                    }
                }
                _ => {}
            }
        }

        if label_pairs.is_empty() && struct_pairs.is_empty() {
            let mut o_idxs = Vec::new();
            for n in old_slice {
                Self::collect_node_lines(n, &mut o_idxs);
            }
            let mut n_idxs = Vec::new();
            for n in new_slice {
                Self::collect_node_lines(n, &mut n_idxs);
            }
            out.push(AlignedSegment {
                old_indices: o_idxs,
                new_indices: n_idxs,
                tag: inherited_tag,
                condition_inverted_pair: false,
                is_declaration_block: false,
            });
            return;
        }

        let mut all_pairs: Vec<(usize, usize, bool)> = Vec::new();
        for (oi, nj) in struct_pairs {
            all_pairs.push((oi, nj, false));
        }
        for (oi, nj) in label_pairs {
            all_pairs.push((oi, nj, true));
        }
        all_pairs.sort_by_key(|p| (p.0, p.1));

        let mut cur_o = 0usize;
        let mut cur_n = 0usize;
        for (oi, nj, is_label) in all_pairs {
            let mut pre_o = Vec::new();
            while cur_o < oi {
                if !old_used[cur_o] {
                    Self::collect_node_lines(old_slice[cur_o], &mut pre_o);
                    old_used[cur_o] = true;
                }
                cur_o += 1;
            }
            let mut pre_n = Vec::new();
            while cur_n < nj {
                if !new_used[cur_n] {
                    Self::collect_node_lines(new_slice[cur_n], &mut pre_n);
                    new_used[cur_n] = true;
                }
                cur_n += 1;
            }
            if !pre_o.is_empty() || !pre_n.is_empty() {
                out.push(AlignedSegment {
                    old_indices: pre_o,
                    new_indices: pre_n,
                    tag: inherited_tag.clone(),
                    condition_inverted_pair: false,
                    is_declaration_block: false,
                });
            }

            if is_label {
                self.align_moved_label(old_slice[oi], new_slice[nj], oi != nj, out);
            } else {
                self.align_paired_nodes(old_slice[oi], new_slice[nj], inherited_tag.clone(), out);
            }
            cur_o = cur_o.max(oi + 1);
            cur_n = cur_n.max(nj + 1);
        }

        let mut tail_o = Vec::new();
        for oi in 0..old_slice.len() {
            if !old_used[oi] {
                Self::collect_node_lines(old_slice[oi], &mut tail_o);
            }
        }
        let mut tail_n = Vec::new();
        for nj in 0..new_slice.len() {
            if !new_used[nj] {
                Self::collect_node_lines(new_slice[nj], &mut tail_n);
            }
        }
        if !tail_o.is_empty() || !tail_n.is_empty() {
            out.push(AlignedSegment {
                old_indices: tail_o,
                new_indices: tail_n,
                tag: inherited_tag,
                condition_inverted_pair: false,
                is_declaration_block: false,
            });
        }
    }

    fn try_align_wrapper_or_loop_container(
        &self,
        old_slice: &[&StmtNode],
        new_slice: &[&StmtNode],
        inherited_tag: Option<CfgReorderTag>,
        out: &mut Vec<AlignedSegment>,
    ) -> Option<bool> {
        // Case A: Old is `LabelBlock` and New has a large `Block` (e.g. `LABEL_3:` vs `do { ... }`)
        if let Some(old_lbl_pos) = old_slice
            .iter()
            .position(|n| matches!(n, StmtNode::LabelBlock { body, .. } if body.len() >= 4))
        {
            if let Some(new_blk_pos) = new_slice
                .iter()
                .position(|n| matches!(n, StmtNode::Block { body, .. } if body.len() >= 4))
            {
                if let (
                    StmtNode::LabelBlock {
                        label_line,
                        label_name,
                        body: ob,
                    },
                    StmtNode::Block {
                        open_brace_line,
                        body: nb,
                        close_brace_line,
                    },
                ) = (old_slice[old_lbl_pos], new_slice[new_blk_pos])
                {
                    if self.body_similarity(ob, nb) >= 0.35 {
                        self.emit_unmatched_slice(
                            &old_slice[..old_lbl_pos],
                            true,
                            inherited_tag.clone(),
                            out,
                        );
                        self.emit_unmatched_slice(
                            &new_slice[..new_blk_pos],
                            false,
                            inherited_tag.clone(),
                            out,
                        );
                        let tag = Some(CfgReorderTag::LabelMoved {
                            label_old: label_name.clone(),
                            label_new: "do-block".to_string(),
                            from_line: self.old_lines[*label_line].line_no,
                            to_line: open_brace_line
                                .map(|i| self.new_lines[i].line_no)
                                .unwrap_or(0),
                        });
                        let mut n_hdr = Vec::new();
                        if let Some(b) = open_brace_line {
                            n_hdr.push(*b);
                        }
                        out.push(AlignedSegment {
                            old_indices: vec![*label_line],
                            new_indices: n_hdr,
                            tag: tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                        self.align_node_slice(ob, nb, inherited_tag.clone(), out);
                        if let Some(c) = close_brace_line {
                            out.push(AlignedSegment {
                                old_indices: Vec::new(),
                                new_indices: vec![*c],
                                tag,
                                condition_inverted_pair: false,
                                is_declaration_block: false,
                            });
                        }
                        if old_lbl_pos + 1 < old_slice.len() || new_blk_pos + 1 < new_slice.len() {
                            let rest_o: Vec<StmtNode> =
                                old_slice[old_lbl_pos + 1..].iter().map(|s| (*s).clone()).collect();
                            let rest_n: Vec<StmtNode> =
                                new_slice[new_blk_pos + 1..].iter().map(|s| (*s).clone()).collect();
                            self.align_node_slice(&rest_o, &rest_n, inherited_tag, out);
                        }
                        return Some(true);
                    }
                }
            }
        }

        // Symmetric Case B: New is `LabelBlock` and Old has a large `Block`
        if let Some(new_lbl_pos) = new_slice
            .iter()
            .position(|n| matches!(n, StmtNode::LabelBlock { body, .. } if body.len() >= 4))
        {
            if let Some(old_blk_pos) = old_slice
                .iter()
                .position(|n| matches!(n, StmtNode::Block { body, .. } if body.len() >= 4))
            {
                if let (
                    StmtNode::Block {
                        open_brace_line,
                        body: ob,
                        close_brace_line,
                    },
                    StmtNode::LabelBlock {
                        label_line,
                        label_name,
                        body: nb,
                    },
                ) = (old_slice[old_blk_pos], new_slice[new_lbl_pos])
                {
                    if self.body_similarity(ob, nb) >= 0.35 {
                        self.emit_unmatched_slice(
                            &old_slice[..old_blk_pos],
                            true,
                            inherited_tag.clone(),
                            out,
                        );
                        self.emit_unmatched_slice(
                            &new_slice[..new_lbl_pos],
                            false,
                            inherited_tag.clone(),
                            out,
                        );
                        let tag = Some(CfgReorderTag::LabelMoved {
                            label_old: "do-block".to_string(),
                            label_new: label_name.clone(),
                            from_line: open_brace_line
                                .map(|i| self.old_lines[i].line_no)
                                .unwrap_or(0),
                            to_line: self.new_lines[*label_line].line_no,
                        });
                        let mut o_hdr = Vec::new();
                        if let Some(b) = open_brace_line {
                            o_hdr.push(*b);
                        }
                        out.push(AlignedSegment {
                            old_indices: o_hdr,
                            new_indices: vec![*label_line],
                            tag: tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                        self.align_node_slice(ob, nb, inherited_tag.clone(), out);
                        if let Some(c) = close_brace_line {
                            out.push(AlignedSegment {
                                old_indices: vec![*c],
                                new_indices: Vec::new(),
                                tag,
                                condition_inverted_pair: false,
                                is_declaration_block: false,
                            });
                        }
                        if old_blk_pos + 1 < old_slice.len() || new_lbl_pos + 1 < new_slice.len() {
                            let rest_o: Vec<StmtNode> =
                                old_slice[old_blk_pos + 1..].iter().map(|s| (*s).clone()).collect();
                            let rest_n: Vec<StmtNode> =
                                new_slice[new_lbl_pos + 1..].iter().map(|s| (*s).clone()).collect();
                            self.align_node_slice(&rest_o, &rest_n, inherited_tag, out);
                        }
                        return Some(true);
                    }
                }
            }
        }

        // Case C: Added depth/bounds check wrapping existing statements:
        // Old = [stmt1, stmt2, ...], New = [if (cond) { body }, trailing...]
        if let Some(StmtNode::If {
            header_line,
            then_open_brace,
            then_body,
            then_close_brace,
            else_body,
            ..
        }) = new_slice.first()
        {
            if else_body.is_empty() && !then_body.is_empty() {
                let old_owned: Vec<StmtNode> = old_slice.iter().map(|s| (*s).clone()).collect();
                if self.body_similarity(&old_owned, then_body) >= 0.45 {
                    let tag = Some(CfgReorderTag::GuardFlattened {
                        note: "新增条件包裹原有代码块，已展开对齐内部语句".to_string(),
                    });
                    let mut hdr = vec![*header_line];
                    if let Some(b) = then_open_brace {
                        hdr.push(*b);
                    }
                    out.push(AlignedSegment {
                        old_indices: Vec::new(),
                        new_indices: hdr,
                        tag: tag.clone(),
                        condition_inverted_pair: false,
                        is_declaration_block: false,
                    });
                    self.align_node_slice(&old_owned, then_body, inherited_tag.clone(), out);
                    if let Some(c) = then_close_brace {
                        out.push(AlignedSegment {
                            old_indices: Vec::new(),
                            new_indices: vec![*c],
                            tag,
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }
                    if new_slice.len() > 1 {
                        self.emit_unmatched_slice(&new_slice[1..], false, inherited_tag, out);
                    }
                    return Some(true);
                }
            }
        }

        // Case D (Symmetric): Old starts with wrapper `if (cond) { body }`, New has flat statements
        if let Some(StmtNode::If {
            header_line,
            then_open_brace,
            then_body,
            then_close_brace,
            else_body,
            ..
        }) = old_slice.first()
        {
            if else_body.is_empty() && !then_body.is_empty() {
                let new_owned: Vec<StmtNode> = new_slice.iter().map(|s| (*s).clone()).collect();
                if self.body_similarity(then_body, &new_owned) >= 0.45 {
                    let tag = Some(CfgReorderTag::GuardFlattened {
                        note: "原有条件包裹代码块已展开对齐内部语句".to_string(),
                    });
                    let mut hdr = vec![*header_line];
                    if let Some(b) = then_open_brace {
                        hdr.push(*b);
                    }
                    out.push(AlignedSegment {
                        old_indices: hdr,
                        new_indices: Vec::new(),
                        tag: tag.clone(),
                        condition_inverted_pair: false,
                        is_declaration_block: false,
                    });
                    self.align_node_slice(then_body, &new_owned, inherited_tag.clone(), out);
                    if let Some(c) = then_close_brace {
                        out.push(AlignedSegment {
                            old_indices: vec![*c],
                            new_indices: Vec::new(),
                            tag,
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }
                    if old_slice.len() > 1 {
                        self.emit_unmatched_slice(&old_slice[1..], true, inherited_tag, out);
                    }
                    return Some(true);
                }
            }
        }

        Some(false)
    }

    fn try_align_guard_clause(
        &self,
        old_slice: &[&StmtNode],
        new_slice: &[&StmtNode],
        inherited_tag: Option<CfgReorderTag>,
        out: &mut Vec<AlignedSegment>,
    ) -> Option<bool> {
        // Pattern A: Old starts with guard `if (c1) <early_exit>` + `rest_old...`
        if let Some(StmtNode::If {
            header_line: g_hdr,
            cond_raw: g_cond,
            then_open_brace: g_to,
            then_body: g_exit,
            then_close_brace: g_tc,
            else_body: g_else,
            ..
        }) = old_slice.first()
        {
            if g_else.is_empty()
                && old_slice.len() >= 2
                && self.is_early_exit_body(g_exit, true)
            {
                if let Some(StmtNode::If {
                    header_line: n_hdr,
                    cond_raw: n_cond,
                    then_open_brace: n_to,
                    then_body: n_body,
                    then_close_brace: n_tc,
                    else_line: n_else_line,
                    else_open_brace: n_eo,
                    else_body: n_else,
                    else_close_brace: n_ec,
                }) = new_slice.first()
                {
                    let cond_inv = conditions_are_inverted(
                        &self.generic_str(g_cond),
                        &self.generic_str(n_cond),
                    );
                    let rest_old_owned: Vec<StmtNode> =
                        old_slice[1..].iter().map(|s| (*s).clone()).collect();
                    let body_sim = self.body_similarity(&rest_old_owned, n_body);
                    if cond_inv || body_sim >= 0.45 {
                        let tag = Some(CfgReorderTag::GuardFlattened {
                            note: "Guard 提前返回 ↔ 嵌套 if 块已展开对齐".to_string(),
                        });
                        out.push(AlignedSegment {
                            old_indices: vec![*g_hdr],
                            new_indices: vec![*n_hdr],
                            tag: tag.clone(),
                            condition_inverted_pair: cond_inv,
                            is_declaration_block: false,
                        });
                        let mut o_br = Vec::new();
                        if let Some(b) = g_to {
                            o_br.push(*b);
                        }
                        let mut n_br = Vec::new();
                        if let Some(b) = n_to {
                            n_br.push(*b);
                        }
                        if !o_br.is_empty() || !n_br.is_empty() {
                            out.push(AlignedSegment {
                                old_indices: o_br,
                                new_indices: n_br,
                                tag: tag.clone(),
                                condition_inverted_pair: false,
                                is_declaration_block: false,
                            });
                        }

                        self.align_node_slice(&rest_old_owned, n_body, inherited_tag.clone(), out);

                        let mut o_cl = Vec::new();
                        if let Some(c) = g_tc {
                            o_cl.push(*c);
                        }
                        let mut n_cl = Vec::new();
                        if let Some(c) = n_tc {
                            n_cl.push(*c);
                        }
                        if !o_cl.is_empty() || !n_cl.is_empty() {
                            out.push(AlignedSegment {
                                old_indices: o_cl,
                                new_indices: n_cl,
                                tag: tag.clone(),
                                condition_inverted_pair: false,
                                is_declaration_block: false,
                            });
                        }

                        if !n_else.is_empty() {
                            if let Some(el) = n_else_line {
                                out.push(AlignedSegment {
                                    old_indices: Vec::new(),
                                    new_indices: vec![*el],
                                    tag: tag.clone(),
                                    condition_inverted_pair: false,
                                    is_declaration_block: false,
                                });
                            }
                            if let Some(eo) = n_eo {
                                out.push(AlignedSegment {
                                    old_indices: Vec::new(),
                                    new_indices: vec![*eo],
                                    tag: tag.clone(),
                                    condition_inverted_pair: false,
                                    is_declaration_block: false,
                                });
                            }
                            self.align_node_slice(g_exit, n_else, tag.clone(), out);
                            if let Some(ec) = n_ec {
                                out.push(AlignedSegment {
                                    old_indices: Vec::new(),
                                    new_indices: vec![*ec],
                                    tag: tag.clone(),
                                    condition_inverted_pair: false,
                                    is_declaration_block: false,
                                });
                            }
                            if new_slice.len() > 1 {
                                self.emit_unmatched_slice(
                                    &new_slice[1..],
                                    false,
                                    inherited_tag,
                                    out,
                                );
                            }
                        } else {
                            let new_tail: Vec<StmtNode> =
                                new_slice[1..].iter().map(|s| (*s).clone()).collect();
                            self.align_node_slice(g_exit, &new_tail, tag, out);
                        }
                        return Some(true);
                    }
                }
            }
        }

        // Pattern B (Symmetric): New starts with guard `if (c2) <early_exit>` + `rest_new...`
        if let Some(StmtNode::If {
            header_line: g_hdr,
            cond_raw: g_cond,
            then_open_brace: g_to,
            then_body: g_exit,
            then_close_brace: g_tc,
            else_body: g_else,
            ..
        }) = new_slice.first()
        {
            if g_else.is_empty()
                && new_slice.len() >= 2
                && self.is_early_exit_body(g_exit, false)
            {
                if let Some(StmtNode::If {
                    header_line: o_hdr,
                    cond_raw: o_cond,
                    then_open_brace: o_to,
                    then_body: o_body,
                    then_close_brace: o_tc,
                    else_line: o_else_line,
                    else_open_brace: o_eo,
                    else_body: o_else,
                    else_close_brace: o_ec,
                }) = old_slice.first()
                {
                    let cond_inv = conditions_are_inverted(
                        &self.generic_str(o_cond),
                        &self.generic_str(g_cond),
                    );
                    let rest_new_owned: Vec<StmtNode> =
                        new_slice[1..].iter().map(|s| (*s).clone()).collect();
                    let body_sim = self.body_similarity(o_body, &rest_new_owned);
                    if cond_inv || body_sim >= 0.45 {
                        let tag = Some(CfgReorderTag::GuardFlattened {
                            note: "嵌套 if 块 ↔ Guard 提前返回已展开对齐".to_string(),
                        });
                        out.push(AlignedSegment {
                            old_indices: vec![*o_hdr],
                            new_indices: vec![*g_hdr],
                            tag: tag.clone(),
                            condition_inverted_pair: cond_inv,
                            is_declaration_block: false,
                        });
                        let mut o_br = Vec::new();
                        if let Some(b) = o_to {
                            o_br.push(*b);
                        }
                        let mut n_br = Vec::new();
                        if let Some(b) = g_to {
                            n_br.push(*b);
                        }
                        if !o_br.is_empty() || !n_br.is_empty() {
                            out.push(AlignedSegment {
                                old_indices: o_br,
                                new_indices: n_br,
                                tag: tag.clone(),
                                condition_inverted_pair: false,
                                is_declaration_block: false,
                            });
                        }

                        self.align_node_slice(o_body, &rest_new_owned, inherited_tag.clone(), out);

                        let mut o_cl = Vec::new();
                        if let Some(c) = o_tc {
                            o_cl.push(*c);
                        }
                        let mut n_cl = Vec::new();
                        if let Some(c) = g_tc {
                            n_cl.push(*c);
                        }
                        if !o_cl.is_empty() || !n_cl.is_empty() {
                            out.push(AlignedSegment {
                                old_indices: o_cl,
                                new_indices: n_cl,
                                tag: tag.clone(),
                                condition_inverted_pair: false,
                                is_declaration_block: false,
                            });
                        }

                        if !o_else.is_empty() {
                            if let Some(el) = o_else_line {
                                out.push(AlignedSegment {
                                    old_indices: vec![*el],
                                    new_indices: Vec::new(),
                                    tag: tag.clone(),
                                    condition_inverted_pair: false,
                                    is_declaration_block: false,
                                });
                            }
                            if let Some(eo) = o_eo {
                                out.push(AlignedSegment {
                                    old_indices: vec![*eo],
                                    new_indices: Vec::new(),
                                    tag: tag.clone(),
                                    condition_inverted_pair: false,
                                    is_declaration_block: false,
                                });
                            }
                            self.align_node_slice(o_else, g_exit, tag.clone(), out);
                            if let Some(ec) = o_ec {
                                out.push(AlignedSegment {
                                    old_indices: vec![*ec],
                                    new_indices: Vec::new(),
                                    tag: tag.clone(),
                                    condition_inverted_pair: false,
                                    is_declaration_block: false,
                                });
                            }
                            if old_slice.len() > 1 {
                                self.emit_unmatched_slice(
                                    &old_slice[1..],
                                    true,
                                    inherited_tag,
                                    out,
                                );
                            }
                        } else {
                            let old_tail: Vec<StmtNode> =
                                old_slice[1..].iter().map(|s| (*s).clone()).collect();
                            self.align_node_slice(&old_tail, g_exit, tag, out);
                        }
                        return Some(true);
                    }
                }
            }
        }

        Some(false)
    }

    fn is_early_exit_body(&self, body: &[StmtNode], is_old: bool) -> bool {
        let non_blank: Vec<&StmtNode> = body
            .iter()
            .filter(|n| !matches!(n, StmtNode::Blank { .. }))
            .collect();
        if non_blank.is_empty() || non_blank.len() > 4 {
            return false;
        }
        let generic = if is_old {
            &self.old_generic
        } else {
            &self.new_generic
        };
        if let Some(StmtNode::Simple { line_idx }) = non_blank.last() {
            let g = generic[*line_idx].trim();
            return g.starts_with("return ") || g == "return;" || g.starts_with("goto ");
        }
        false
    }

    fn align_moved_label(
        &self,
        old_node: &StmtNode,
        new_node: &StmtNode,
        actually_moved: bool,
        out: &mut Vec<AlignedSegment>,
    ) {
        if let (
            StmtNode::LabelBlock {
                label_line: ol,
                label_name: oname,
                body: ob,
            },
            StmtNode::LabelBlock {
                label_line: nl,
                label_name: nname,
                body: nb,
            },
        ) = (old_node, new_node)
        {
            let tag = if actually_moved {
                Some(CfgReorderTag::LabelMoved {
                    label_old: oname.clone(),
                    label_new: nname.clone(),
                    from_line: self.old_lines[*ol].line_no,
                    to_line: self.new_lines[*nl].line_no,
                })
            } else {
                None
            };
            out.push(AlignedSegment {
                old_indices: vec![*ol],
                new_indices: vec![*nl],
                tag: tag.clone(),
                condition_inverted_pair: false,
                is_declaration_block: false,
            });
            self.align_node_slice(ob, nb, tag, out);
        }
    }

    fn align_paired_nodes(
        &self,
        old_node: &StmtNode,
        new_node: &StmtNode,
        inherited_tag: Option<CfgReorderTag>,
        out: &mut Vec<AlignedSegment>,
    ) {
        match (old_node, new_node) {
            (
                StmtNode::Declaration { line_idx: oi },
                StmtNode::Declaration { line_idx: ni },
            ) => {
                out.push(AlignedSegment {
                    old_indices: vec![*oi],
                    new_indices: vec![*ni],
                    tag: if self.options.collapse_declarations {
                        Some(CfgReorderTag::DeclarationBlock)
                    } else {
                        inherited_tag
                    },
                    condition_inverted_pair: false,
                    is_declaration_block: self.options.collapse_declarations,
                });
            }
            (
                StmtNode::Block {
                    open_brace_line: oo,
                    body: ob,
                    close_brace_line: oc,
                },
                StmtNode::Block {
                    open_brace_line: no,
                    body: nb,
                    close_brace_line: nc,
                },
            ) => {
                let mut o_br = Vec::new();
                if let Some(i) = oo {
                    o_br.push(*i);
                }
                let mut n_br = Vec::new();
                if let Some(i) = no {
                    n_br.push(*i);
                }
                if !o_br.is_empty() || !n_br.is_empty() {
                    out.push(AlignedSegment {
                        old_indices: o_br,
                        new_indices: n_br,
                        tag: inherited_tag.clone(),
                        condition_inverted_pair: false,
                        is_declaration_block: false,
                    });
                }
                self.align_node_slice(ob, nb, inherited_tag.clone(), out);
                let mut o_cl = Vec::new();
                if let Some(i) = oc {
                    o_cl.push(*i);
                }
                let mut n_cl = Vec::new();
                if let Some(i) = nc {
                    n_cl.push(*i);
                }
                if !o_cl.is_empty() || !n_cl.is_empty() {
                    out.push(AlignedSegment {
                        old_indices: o_cl,
                        new_indices: n_cl,
                        tag: inherited_tag,
                        condition_inverted_pair: false,
                        is_declaration_block: false,
                    });
                }
            }
            (
                StmtNode::If {
                    header_line: oh,
                    cond_raw: oc,
                    then_open_brace: oto,
                    then_body: otb,
                    then_close_brace: otc,
                    else_line: oe_l,
                    else_open_brace: oeo,
                    else_body: oeb,
                    else_close_brace: oec,
                },
                StmtNode::If {
                    header_line: nh,
                    cond_raw: nc,
                    then_open_brace: nto,
                    then_body: ntb,
                    then_close_brace: ntc,
                    else_line: ne_l,
                    else_open_brace: neo,
                    else_body: neb,
                    else_close_brace: nec,
                },
            ) => {
                let has_both_else = !oeb.is_empty() && !neb.is_empty();
                let cond_inv = conditions_are_inverted(
                    &self.generic_str(oc),
                    &self.generic_str(nc),
                );
                let direct_sim =
                    self.body_similarity(otb, ntb) + self.body_similarity(oeb, neb);
                let inv_sim =
                    self.body_similarity(otb, neb) + self.body_similarity(oeb, ntb);

                let inverted = has_both_else
                    && ((cond_inv && inv_sim >= direct_sim) || inv_sim > direct_sim + 0.25);

                if inverted {
                    let inv_tag = Some(CfgReorderTag::BranchInverted {
                        note: "if/else 条件取反，真假分支已互换对齐".to_string(),
                    });
                    out.push(AlignedSegment {
                        old_indices: vec![*oh],
                        new_indices: vec![*nh],
                        tag: inv_tag.clone(),
                        condition_inverted_pair: cond_inv,
                        is_declaration_block: false,
                    });

                    let mut o_br = Vec::new();
                    if let Some(i) = oto {
                        o_br.push(*i);
                    }
                    let mut n_br = Vec::new();
                    if let Some(i) = neo {
                        n_br.push(*i);
                    }
                    if !o_br.is_empty() || !n_br.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_br,
                            new_indices: n_br,
                            tag: inv_tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }

                    self.align_node_slice(otb, neb, inv_tag.clone(), out);

                    let mut o_cl = Vec::new();
                    if let Some(i) = otc {
                        o_cl.push(*i);
                    }
                    let mut n_cl = Vec::new();
                    if let Some(i) = nec {
                        n_cl.push(*i);
                    }
                    if !o_cl.is_empty() || !n_cl.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_cl,
                            new_indices: n_cl,
                            tag: inv_tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }

                    let mut o_el = Vec::new();
                    if let Some(i) = oe_l {
                        o_el.push(*i);
                    }
                    let mut n_el = Vec::new();
                    if let Some(i) = ne_l {
                        n_el.push(*i);
                    }
                    if !o_el.is_empty() || !n_el.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_el,
                            new_indices: n_el,
                            tag: inv_tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }

                    let mut o_ebr = Vec::new();
                    if let Some(i) = oeo {
                        o_ebr.push(*i);
                    }
                    let mut n_ebr = Vec::new();
                    if let Some(i) = nto {
                        n_ebr.push(*i);
                    }
                    if !o_ebr.is_empty() || !n_ebr.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_ebr,
                            new_indices: n_ebr,
                            tag: inv_tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }

                    self.align_node_slice(oeb, ntb, inv_tag.clone(), out);

                    let mut o_ecl = Vec::new();
                    if let Some(i) = oec {
                        o_ecl.push(*i);
                    }
                    let mut n_ecl = Vec::new();
                    if let Some(i) = ntc {
                        n_ecl.push(*i);
                    }
                    if !o_ecl.is_empty() || !n_ecl.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_ecl,
                            new_indices: n_ecl,
                            tag: inv_tag,
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }
                } else {
                    out.push(AlignedSegment {
                        old_indices: vec![*oh],
                        new_indices: vec![*nh],
                        tag: inherited_tag.clone(),
                        condition_inverted_pair: false,
                        is_declaration_block: false,
                    });
                    let mut o_br = Vec::new();
                    if let Some(i) = oto {
                        o_br.push(*i);
                    }
                    let mut n_br = Vec::new();
                    if let Some(i) = nto {
                        n_br.push(*i);
                    }
                    if !o_br.is_empty() || !n_br.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_br,
                            new_indices: n_br,
                            tag: inherited_tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }
                    self.align_node_slice(otb, ntb, inherited_tag.clone(), out);
                    let mut o_cl = Vec::new();
                    if let Some(i) = otc {
                        o_cl.push(*i);
                    }
                    let mut n_cl = Vec::new();
                    if let Some(i) = ntc {
                        n_cl.push(*i);
                    }
                    if !o_cl.is_empty() || !n_cl.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_cl,
                            new_indices: n_cl,
                            tag: inherited_tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }

                    let mut o_el = Vec::new();
                    if let Some(i) = oe_l {
                        o_el.push(*i);
                    }
                    let mut n_el = Vec::new();
                    if let Some(i) = ne_l {
                        n_el.push(*i);
                    }
                    if !o_el.is_empty() || !n_el.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_el,
                            new_indices: n_el,
                            tag: inherited_tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }

                    let mut o_ebr = Vec::new();
                    if let Some(i) = oeo {
                        o_ebr.push(*i);
                    }
                    let mut n_ebr = Vec::new();
                    if let Some(i) = neo {
                        n_ebr.push(*i);
                    }
                    if !o_ebr.is_empty() || !n_ebr.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_ebr,
                            new_indices: n_ebr,
                            tag: inherited_tag.clone(),
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }

                    if !oeb.is_empty() || !neb.is_empty() {
                        self.align_node_slice(oeb, neb, inherited_tag.clone(), out);
                    }

                    let mut o_ecl = Vec::new();
                    if let Some(i) = oec {
                        o_ecl.push(*i);
                    }
                    let mut n_ecl = Vec::new();
                    if let Some(i) = nec {
                        n_ecl.push(*i);
                    }
                    if !o_ecl.is_empty() || !n_ecl.is_empty() {
                        out.push(AlignedSegment {
                            old_indices: o_ecl,
                            new_indices: n_ecl,
                            tag: inherited_tag,
                            condition_inverted_pair: false,
                            is_declaration_block: false,
                        });
                    }
                }
            }
            (
                StmtNode::Switch {
                    header_line: oh,
                    open_brace_line: oo,
                    cases: ocases,
                    close_brace_line: oc,
                    ..
                },
                StmtNode::Switch {
                    header_line: nh,
                    open_brace_line: no,
                    cases: ncases,
                    close_brace_line: nc,
                    ..
                },
            ) => {
                out.push(AlignedSegment {
                    old_indices: vec![*oh],
                    new_indices: vec![*nh],
                    tag: inherited_tag.clone(),
                    condition_inverted_pair: false,
                    is_declaration_block: false,
                });
                let mut o_br = Vec::new();
                if let Some(i) = oo {
                    o_br.push(*i);
                }
                let mut n_br = Vec::new();
                if let Some(i) = no {
                    n_br.push(*i);
                }
                if !o_br.is_empty() || !n_br.is_empty() {
                    out.push(AlignedSegment {
                        old_indices: o_br,
                        new_indices: n_br,
                        tag: inherited_tag.clone(),
                        condition_inverted_pair: false,
                        is_declaration_block: false,
                    });
                }

                self.align_switch_cases(ocases, ncases, inherited_tag.clone(), out);

                let mut o_cl = Vec::new();
                if let Some(i) = oc {
                    o_cl.push(*i);
                }
                let mut n_cl = Vec::new();
                if let Some(i) = nc {
                    n_cl.push(*i);
                }
                if !o_cl.is_empty() || !n_cl.is_empty() {
                    out.push(AlignedSegment {
                        old_indices: o_cl,
                        new_indices: n_cl,
                        tag: inherited_tag,
                        condition_inverted_pair: false,
                        is_declaration_block: false,
                    });
                }
            }
            _ => {
                if matches!(old_node, StmtNode::LabelBlock { .. })
                    && matches!(new_node, StmtNode::LabelBlock { .. })
                {
                    self.align_moved_label(old_node, new_node, false, out);
                    return;
                }
                let mut o_idxs = Vec::new();
                Self::collect_node_lines(old_node, &mut o_idxs);
                let mut n_idxs = Vec::new();
                Self::collect_node_lines(new_node, &mut n_idxs);
                out.push(AlignedSegment {
                    old_indices: o_idxs,
                    new_indices: n_idxs,
                    tag: inherited_tag,
                    condition_inverted_pair: false,
                    is_declaration_block: false,
                });
            }
        }
    }

    fn align_switch_cases(
        &self,
        ocases: &[CaseNode],
        ncases: &[CaseNode],
        inherited_tag: Option<CfgReorderTag>,
        out: &mut Vec<AlignedSegment>,
    ) {
        let mut new_by_key: HashMap<String, usize> = HashMap::new();
        for (idx, c) in ncases.iter().enumerate() {
            new_by_key.entry(c.case_key.clone()).or_insert(idx);
        }

        let mut new_matched = vec![false; ncases.len()];

        for (oi, oc) in ocases.iter().enumerate() {
            if let Some(&ni) = new_by_key.get(&oc.case_key) {
                new_matched[ni] = true;
                let nc = &ncases[ni];
                let reordered = oi != ni;
                let tag = if reordered {
                    Some(CfgReorderTag::CaseReordered {
                        case_key: oc.case_key.clone(),
                    })
                } else {
                    inherited_tag.clone()
                };
                out.push(AlignedSegment {
                    old_indices: vec![oc.label_line],
                    new_indices: vec![nc.label_line],
                    tag: tag.clone(),
                    condition_inverted_pair: false,
                    is_declaration_block: false,
                });
                self.align_node_slice(&oc.body, &nc.body, tag, out);
            } else {
                let mut idxs = vec![oc.label_line];
                for b in &oc.body {
                    Self::collect_node_lines(b, &mut idxs);
                }
                out.push(AlignedSegment {
                    old_indices: idxs,
                    new_indices: Vec::new(),
                    tag: inherited_tag.clone(),
                    condition_inverted_pair: false,
                    is_declaration_block: false,
                });
            }
        }

        for (ni, nc) in ncases.iter().enumerate() {
            if !new_matched[ni] {
                let mut idxs = vec![nc.label_line];
                for b in &nc.body {
                    Self::collect_node_lines(b, &mut idxs);
                }
                out.push(AlignedSegment {
                    old_indices: Vec::new(),
                    new_indices: idxs,
                    tag: inherited_tag.clone(),
                    condition_inverted_pair: false,
                    is_declaration_block: false,
                });
            }
        }
    }
}
