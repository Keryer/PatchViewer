use std::collections::{HashMap, HashSet};

use similar::{capture_diff_slices, Algorithm, DiffOp};

use crate::cfg_align::{AlignContext, AlignedSegment};
use crate::config::DiffOptions;
use crate::model::{
    AlignedRow, CfgReorderTag, ChangeKind, DiffResult, DiffSummary, LineSide, TokenHighlight,
    TokenSpan,
};
use crate::normalizer::{
    classify_identifier, compute_generic_key, conditions_are_inverted, line_normalizable_idents,
    render_canonical_line, CanonicalMaps, IdentClass, NormalizedLine,
};
use crate::parser::{parse_ast, parse_lines, ParsedLine, RawToken, RawTokenKind};

/// Execute full dual-track pseudocode diffing over two IDA Pro (Hex-Rays) pseudocode inputs.
pub fn diff_pseudocode(old_src: &str, new_src: &str, options: &DiffOptions) -> DiffResult {
    let old_lines = parse_lines(old_src);
    let new_lines = parse_lines(new_src);

    let old_ast = parse_ast(&old_lines);
    let new_ast = parse_ast(&new_lines);

    let align_ctx = AlignContext::new(&old_lines, &new_lines, options);
    let segments = align_ctx.align_ast(&old_ast, &new_ast);

    // Pass 1: Discover canonical variable and address symbol mappings across matched anchors.
    let mut maps = CanonicalMaps::default();
    build_canonical_anchors(&old_lines, &new_lines, &segments, &mut maps, options);

    // Pass 2: Render canonical normalized lines for every line in old and new.
    let old_norm: Vec<NormalizedLine> = old_lines
        .iter()
        .map(|l| render_canonical_line(l, true, &mut maps, options))
        .collect();
    let new_norm: Vec<NormalizedLine> = new_lines
        .iter()
        .map(|l| render_canonical_line(l, false, &mut maps, options))
        .collect();

    // Pass 3: Build AlignedRows from each structural segment.
    let mut rows = Vec::new();
    for seg in &segments {
        diff_segment(
            seg,
            &old_lines,
            &new_lines,
            &old_norm,
            &new_norm,
            &maps,
            options,
            &mut rows,
        );
    }

    for (idx, row) in rows.iter_mut().enumerate() {
        row.row_index = idx;
    }

    // Build summary & mapping tables
    let summary = build_summary(&rows, &maps);

    DiffResult {
        rows,
        summary,
        options: options.clone(),
    }
}

fn build_canonical_anchors(
    old_lines: &[ParsedLine],
    new_lines: &[ParsedLine],
    segments: &[AlignedSegment],
    maps: &mut CanonicalMaps,
    options: &DiffOptions,
) {
    // Anchor non-declaration executable/header segments first so real code usage
    // determines canonical variable & address ordering.
    for seg in segments {
        if seg.is_declaration_block {
            continue;
        }
        if seg.condition_inverted_pair && seg.old_indices.len() == 1 && seg.new_indices.len() == 1
        {
            let oi = seg.old_indices[0];
            let ni = seg.new_indices[0];
            let o_idents = line_normalizable_idents(&old_lines[oi], options);
            let n_idents = line_normalizable_idents(&new_lines[ni], options);
            if o_idents.len() == n_idents.len() {
                for ((oc, os), (nc, ns)) in o_idents.iter().zip(n_idents.iter()) {
                    if oc == nc {
                        maps.bind_pair(*oc, os, ns);
                    }
                }
            }
            continue;
        }

        let o_keys: Vec<String> = seg
            .old_indices
            .iter()
            .map(|&i| compute_generic_key(&old_lines[i], options))
            .collect();
        let n_keys: Vec<String> = seg
            .new_indices
            .iter()
            .map(|&i| compute_generic_key(&new_lines[i], options))
            .collect();

        let ops = capture_diff_slices(Algorithm::Myers, &o_keys, &n_keys);
        for op in ops {
            match op {
                DiffOp::Equal {
                    old_index,
                    new_index,
                    len,
                } => {
                    for k in 0..len {
                        let oi = seg.old_indices[old_index + k];
                        let ni = seg.new_indices[new_index + k];
                        let o_idents = line_normalizable_idents(&old_lines[oi], options);
                        let n_idents = line_normalizable_idents(&new_lines[ni], options);
                        if o_idents.len() == n_idents.len() {
                            for ((oc, os), (nc, ns)) in o_idents.iter().zip(n_idents.iter()) {
                                if oc == nc {
                                    maps.bind_pair(*oc, os, ns);
                                }
                            }
                        }
                    }
                }
                DiffOp::Replace {
                    old_index,
                    old_len,
                    new_index,
                    new_len,
                } => {
                    // Fuzzy line pair matching inside replacement blocks to bind shared callees/vars
                    let pairs = pair_similar_lines(
                        &seg.old_indices[old_index..old_index + old_len],
                        &seg.new_indices[new_index..new_index + new_len],
                        |i| compute_generic_key(&old_lines[i], options),
                        |j| compute_generic_key(&new_lines[j], options),
                    );
                    for (oi_opt, ni_opt) in pairs {
                        if let (Some(oi), Some(ni)) = (oi_opt, ni_opt) {
                            let o_idents = line_normalizable_idents(&old_lines[oi], options);
                            let n_idents = line_normalizable_idents(&new_lines[ni], options);
                            if o_idents.len() == n_idents.len() {
                                for ((oc, os), (nc, ns)) in o_idents.iter().zip(n_idents.iter()) {
                                    if oc == nc {
                                        maps.bind_pair(*oc, os, ns);
                                    }
                                }
                            } else {
                                // Bind matching Sub/Dat/Loc anchors if counts match per class
                                bind_single_class_anchors(&o_idents, &n_idents, maps);
                            }
                        }
                    }
                }
                _ => {}
            }
        }
    }
}

fn bind_single_class_anchors(
    o_idents: &[(IdentClass, String)],
    n_idents: &[(IdentClass, String)],
    maps: &mut CanonicalMaps,
) {
    for cls in [
        IdentClass::Sub,
        IdentClass::Loc,
        IdentClass::Dat,
        IdentClass::AutoArg,
    ] {
        let o_cls: Vec<&str> = o_idents
            .iter()
            .filter(|(c, _)| *c == cls)
            .map(|(_, s)| s.as_str())
            .collect();
        let n_cls: Vec<&str> = n_idents
            .iter()
            .filter(|(c, _)| *c == cls)
            .map(|(_, s)| s.as_str())
            .collect();
        if !o_cls.is_empty() && o_cls.len() == n_cls.len() {
            for (o, n) in o_cls.iter().zip(n_cls.iter()) {
                maps.bind_pair(cls, o, n);
            }
        }
    }
}

#[allow(clippy::too_many_arguments)]
fn diff_segment(
    seg: &AlignedSegment,
    old_lines: &[ParsedLine],
    new_lines: &[ParsedLine],
    old_norm: &[NormalizedLine],
    new_norm: &[NormalizedLine],
    maps: &CanonicalMaps,
    options: &DiffOptions,
    out: &mut Vec<AlignedRow>,
) {
    if seg.is_declaration_block {
        diff_declaration_block(seg, old_lines, new_lines, old_norm, new_norm, maps, options, out);
        return;
    }

    if seg.condition_inverted_pair && seg.old_indices.len() == 1 && seg.new_indices.len() == 1 {
        let oi = seg.old_indices[0];
        let ni = seg.new_indices[0];
        let o_can = &old_norm[oi].canonical_key;
        let n_can = &new_norm[ni].canonical_key;
        let kind = if o_can == n_can {
            if old_lines[oi].raw_text.trim() == new_lines[ni].raw_text.trim() {
                ChangeKind::Unchanged
            } else {
                ChangeKind::NoiseOnly
            }
        } else if are_inverted_header_lines(o_can, n_can) {
            ChangeKind::NoiseOnly
        } else {
            ChangeKind::Modified
        };
        let (old_side, new_side) = build_paired_sides(
            &old_lines[oi],
            &new_lines[ni],
            &old_norm[oi],
            &new_norm[ni],
            kind,
            maps,
            options,
        );
        out.push(AlignedRow {
            row_index: 0,
            old_line: Some(old_side),
            new_line: Some(new_side),
            kind,
            cfg_tag: seg.tag.clone(),
        });
        return;
    }

    let o_keys: Vec<&str> = seg
        .old_indices
        .iter()
        .map(|&i| old_norm[i].canonical_key.as_str())
        .collect();
    let n_keys: Vec<&str> = seg
        .new_indices
        .iter()
        .map(|&i| new_norm[i].canonical_key.as_str())
        .collect();

    let ops = capture_diff_slices(Algorithm::Myers, &o_keys, &n_keys);

    // Attach CFG tag only on the first row (or meaningful rows) of the segment?
    // Attaching seg.tag to every row inside that aligned CFG block makes TUI & Desktop UI
    // clearly highlight the whole reordered block, while summary counts distinct CFG blocks or transitions.
    for op in ops {
        match op {
            DiffOp::Equal {
                old_index,
                new_index,
                len,
            } => {
                for k in 0..len {
                    let oi = seg.old_indices[old_index + k];
                    let ni = seg.new_indices[new_index + k];
                    let raw_eq = if options.ignore_comments {
                        old_lines[oi].raw_text.trim() == new_lines[ni].raw_text.trim()
                    } else {
                        old_lines[oi].raw_text.trim() == new_lines[ni].raw_text.trim()
                    };
                    let kind = if raw_eq {
                        ChangeKind::Unchanged
                    } else {
                        ChangeKind::NoiseOnly
                    };
                    let (old_side, new_side) = build_paired_sides(
                        &old_lines[oi],
                        &new_lines[ni],
                        &old_norm[oi],
                        &new_norm[ni],
                        kind,
                        maps,
                        options,
                    );
                    out.push(AlignedRow {
                        row_index: 0,
                        old_line: Some(old_side),
                        new_line: Some(new_side),
                        kind,
                        cfg_tag: seg.tag.clone(),
                    });
                }
            }
            DiffOp::Delete {
                old_index,
                old_len: len,
                ..
            } => {
                for k in 0..len {
                    let oi = seg.old_indices[old_index + k];
                    let old_side = build_single_side(
                        &old_lines[oi],
                        &old_norm[oi],
                        true,
                        TokenHighlight::SemanticDelete,
                        maps,
                        options,
                    );
                    out.push(AlignedRow {
                        row_index: 0,
                        old_line: Some(old_side),
                        new_line: None,
                        kind: ChangeKind::Removed,
                        cfg_tag: seg.tag.clone(),
                    });
                }
            }
            DiffOp::Insert {
                new_index,
                new_len: len,
                ..
            } => {
                for k in 0..len {
                    let ni = seg.new_indices[new_index + k];
                    let new_side = build_single_side(
                        &new_lines[ni],
                        &new_norm[ni],
                        false,
                        TokenHighlight::SemanticAdd,
                        maps,
                        options,
                    );
                    out.push(AlignedRow {
                        row_index: 0,
                        old_line: None,
                        new_line: Some(new_side),
                        kind: ChangeKind::Added,
                        cfg_tag: seg.tag.clone(),
                    });
                }
            }
            DiffOp::Replace {
                old_index,
                old_len,
                new_index,
                new_len,
            } => {
                let pairs = pair_similar_lines(
                    &seg.old_indices[old_index..old_index + old_len],
                    &seg.new_indices[new_index..new_index + new_len],
                    |i| old_norm[i].canonical_key.clone(),
                    |j| new_norm[j].canonical_key.clone(),
                );
                for (oi_opt, ni_opt) in pairs {
                    match (oi_opt, ni_opt) {
                        (Some(oi), Some(ni)) => {
                            let kind = if old_norm[oi].canonical_key == new_norm[ni].canonical_key {
                                if old_lines[oi].raw_text.trim() == new_lines[ni].raw_text.trim() {
                                    ChangeKind::Unchanged
                                } else {
                                    ChangeKind::NoiseOnly
                                }
                            } else {
                                ChangeKind::Modified
                            };
                            let (old_side, new_side) = build_paired_sides(
                                &old_lines[oi],
                                &new_lines[ni],
                                &old_norm[oi],
                                &new_norm[ni],
                                kind,
                                maps,
                                options,
                            );
                            out.push(AlignedRow {
                                row_index: 0,
                                old_line: Some(old_side),
                                new_line: Some(new_side),
                                kind,
                                cfg_tag: seg.tag.clone(),
                            });
                        }
                        (Some(oi), None) => {
                            let old_side = build_single_side(
                                &old_lines[oi],
                                &old_norm[oi],
                                true,
                                TokenHighlight::SemanticDelete,
                                maps,
                                options,
                            );
                            out.push(AlignedRow {
                                row_index: 0,
                                old_line: Some(old_side),
                                new_line: None,
                                kind: ChangeKind::Removed,
                                cfg_tag: seg.tag.clone(),
                            });
                        }
                        (None, Some(ni)) => {
                            let new_side = build_single_side(
                                &new_lines[ni],
                                &new_norm[ni],
                                false,
                                TokenHighlight::SemanticAdd,
                                maps,
                                options,
                            );
                            out.push(AlignedRow {
                                row_index: 0,
                                old_line: None,
                                new_line: Some(new_side),
                                kind: ChangeKind::Added,
                                cfg_tag: seg.tag.clone(),
                            });
                        }
                        (None, None) => {}
                    }
                }
            }
        }
    }
}

#[allow(clippy::too_many_arguments)]
fn diff_declaration_block(
    seg: &AlignedSegment,
    old_lines: &[ParsedLine],
    new_lines: &[ParsedLine],
    old_norm: &[NormalizedLine],
    new_norm: &[NormalizedLine],
    maps: &CanonicalMaps,
    options: &DiffOptions,
    out: &mut Vec<AlignedRow>,
) {
    // Pass 1: Match declarations by exact canonical_key regardless of order in the declaration block
    let mut new_by_key: HashMap<&str, Vec<usize>> = HashMap::new();
    for &ni in &seg.new_indices {
        new_by_key
            .entry(new_norm[ni].canonical_key.as_str())
            .or_default()
            .push(ni);
    }
    let mut old_matched_to: HashMap<usize, (usize, ChangeKind)> = HashMap::new();
    let mut new_used: HashSet<usize> = HashSet::new();

    for &oi in &seg.old_indices {
        let key = old_norm[oi].canonical_key.as_str();
        if let Some(ni) = new_by_key
            .get(key)
            .and_then(|list| list.iter().copied().find(|ni| !new_used.contains(ni)))
        {
            new_used.insert(ni);
            let kind = if old_lines[oi].raw_text.trim() == new_lines[ni].raw_text.trim() {
                ChangeKind::Unchanged
            } else {
                ChangeKind::NoiseOnly
            };
            old_matched_to.insert(oi, (ni, kind));
        }
    }

    // Pass 2: Pair remaining declarations that share the same canonical variable ID ($VAR_k)
    // when Hex-Rays inferred a different C type (e.g. `void *v3` vs `char *v3`).
    let decl_var_id = |norm: &NormalizedLine| -> Option<String> {
        norm.token_mappings
            .iter()
            .rev()
            .find_map(|(_, canon)| {
                canon
                    .as_ref()
                    .filter(|c| c.starts_with("$VAR_") || c.starts_with("$ARG_"))
                    .cloned()
            })
    };

    let mut new_by_var: HashMap<String, usize> = HashMap::new();
    for &ni in &seg.new_indices {
        if !new_used.contains(&ni) {
            if let Some(vid) = decl_var_id(&new_norm[ni]) {
                new_by_var.entry(vid).or_insert(ni);
            }
        }
    }

    for &oi in &seg.old_indices {
        if old_matched_to.contains_key(&oi) {
            continue;
        }
        if let Some(vid) = decl_var_id(&old_norm[oi]) {
            if let Some(&ni) = new_by_var.get(&vid) {
                if !new_used.contains(&ni) {
                    new_used.insert(ni);
                    old_matched_to.insert(oi, (ni, ChangeKind::Modified));
                }
            }
        }
    }

    for &oi in &seg.old_indices {
        if let Some(&(ni, kind)) = old_matched_to.get(&oi) {
            let (old_side, new_side) = build_paired_sides(
                &old_lines[oi],
                &new_lines[ni],
                &old_norm[oi],
                &new_norm[ni],
                kind,
                maps,
                options,
            );
            out.push(AlignedRow {
                row_index: 0,
                old_line: Some(old_side),
                new_line: Some(new_side),
                kind,
                cfg_tag: Some(CfgReorderTag::DeclarationBlock),
            });
        } else {
            let old_side = build_single_side(
                &old_lines[oi],
                &old_norm[oi],
                true,
                TokenHighlight::SemanticDelete,
                maps,
                options,
            );
            out.push(AlignedRow {
                row_index: 0,
                old_line: Some(old_side),
                new_line: None,
                kind: ChangeKind::Removed,
                cfg_tag: Some(CfgReorderTag::DeclarationBlock),
            });
        }
    }

    for &ni in &seg.new_indices {
        if !new_used.contains(&ni) {
            let new_side = build_single_side(
                &new_lines[ni],
                &new_norm[ni],
                false,
                TokenHighlight::SemanticAdd,
                maps,
                options,
            );
            out.push(AlignedRow {
                row_index: 0,
                old_line: None,
                new_line: Some(new_side),
                kind: ChangeKind::Added,
                cfg_tag: Some(CfgReorderTag::DeclarationBlock),
            });
        }
    }
}

fn are_inverted_header_lines(old_can: &str, new_can: &str) -> bool {
    let extract = |s: &str| -> Option<String> {
        let rest = s.trim().strip_prefix("if")?.trim();
        let rest = rest.strip_prefix('(')?;
        // Strip trailing `{` if any and final `)`
        let before_brace = rest.trim_end_matches('{').trim();
        before_brace.strip_suffix(')').map(|c| c.trim().to_string())
    };
    if let (Some(c1), Some(c2)) = (extract(old_can), extract(new_can)) {
        conditions_are_inverted(&c1, &c2)
    } else {
        false
    }
}

/// Pair lines inside a `Replace` hunk using normalized token Jaccard similarity,
/// preserving relative order for paired anchors.
fn pair_similar_lines<FO, FN>(
    old_idxs: &[usize],
    new_idxs: &[usize],
    old_key_fn: FO,
    new_key_fn: FN,
) -> Vec<(Option<usize>, Option<usize>)>
where
    FO: Fn(usize) -> String,
    FN: Fn(usize) -> String,
{
    let mut new_used = vec![false; new_idxs.len()];
    let mut old_match: Vec<Option<usize>> = vec![None; old_idxs.len()];
    let mut min_new = 0usize;

    for (oi_pos, &oi) in old_idxs.iter().enumerate() {
        let ok = old_key_fn(oi);
        let o_set: HashSet<&str> = ok.split_whitespace().collect();
        let mut best_pos = None;
        let mut best_sim = 0.48f64;

        for (nj_pos, &nj) in new_idxs.iter().enumerate().skip(min_new) {
            if new_used[nj_pos] {
                continue;
            }
            let nk = new_key_fn(nj);
            if ok == nk {
                best_pos = Some(nj_pos);
                break;
            }
            let n_set: HashSet<&str> = nk.split_whitespace().collect();
            let sim = jaccard_str(&o_set, &n_set);
            if sim > best_sim {
                best_sim = sim;
                best_pos = Some(nj_pos);
            }
        }
        if let Some(np) = best_pos {
            new_used[np] = true;
            old_match[oi_pos] = Some(np);
            min_new = np + 1;
        }
    }

    let mut result = Vec::new();
    let mut next_new = 0usize;
    for (oi_pos, &oi) in old_idxs.iter().enumerate() {
        if let Some(np) = old_match[oi_pos] {
            while next_new < np {
                if !new_used[next_new] {
                    result.push((None, Some(new_idxs[next_new])));
                }
                next_new += 1;
            }
            result.push((Some(oi), Some(new_idxs[np])));
            next_new = np + 1;
        } else {
            result.push((Some(oi), None));
        }
    }
    while next_new < new_idxs.len() {
        if !new_used[next_new] {
            result.push((None, Some(new_idxs[next_new])));
        }
        next_new += 1;
    }
    result
}

fn jaccard_str(a: &HashSet<&str>, b: &HashSet<&str>) -> f64 {
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

fn lookup_token_meta(
    raw: &RawToken,
    is_old: bool,
    maps: &CanonicalMaps,
    options: &DiffOptions,
) -> (Option<String>, Option<String>) {
    if raw.kind != RawTokenKind::Identifier {
        return (None, None);
    }
    let cls = classify_identifier(&raw.text);
    let enabled = match cls {
        IdentClass::Sub | IdentClass::Loc | IdentClass::Dat => options.normalize_addresses,
        IdentClass::AutoVar | IdentClass::AutoArg => options.normalize_variables,
        IdentClass::Regular => false,
    };
    if !enabled {
        return (None, None);
    }

    let id_opt = if is_old {
        maps.old_to_id.get(&raw.text).cloned()
    } else {
        maps.new_to_id.get(&raw.text).cloned()
    };

    if let Some(id) = id_opt {
        let counterpart = maps
            .id_to_pair
            .iter()
            .find(|(_, cid, _, _)| cid == &id)
            .and_then(|(_, _, o, n)| {
                let cp = if is_old { n } else { o };
                if cp.is_empty() {
                    None
                } else {
                    Some(cp.clone())
                }
            });
        (Some(id), counterpart)
    } else {
        (None, None)
    }
}

fn build_single_side(
    parsed: &ParsedLine,
    norm: &NormalizedLine,
    is_old: bool,
    hl: TokenHighlight,
    maps: &CanonicalMaps,
    options: &DiffOptions,
) -> LineSide {
    let tokens = parsed
        .tokens
        .iter()
        .map(|t| {
            let (normalized, counterpart) = lookup_token_meta(t, is_old, maps, options);
            let token_hl = if t.kind == RawTokenKind::Whitespace {
                TokenHighlight::None
            } else {
                hl
            };
            TokenSpan {
                text: t.text.clone(),
                normalized,
                counterpart,
                highlight: token_hl,
            }
        })
        .collect();

    LineSide {
        line_no: parsed.line_no,
        raw_text: parsed.raw_text.clone(),
        normalized_text: norm.canonical_display.clone(),
        tokens,
    }
}

fn build_paired_sides(
    old_parsed: &ParsedLine,
    new_parsed: &ParsedLine,
    old_norm: &NormalizedLine,
    new_norm: &NormalizedLine,
    kind: ChangeKind,
    maps: &CanonicalMaps,
    options: &DiffOptions,
) -> (LineSide, LineSide) {
    if kind == ChangeKind::Unchanged {
        let o = build_single_side(
            old_parsed,
            old_norm,
            true,
            TokenHighlight::None,
            maps,
            options,
        );
        let n = build_single_side(
            new_parsed,
            new_norm,
            false,
            TokenHighlight::None,
            maps,
            options,
        );
        return (o, n);
    }

    // Extract indices of non-whitespace, non-stripped-comment tokens on both sides
    let o_sig_idxs: Vec<usize> = old_parsed
        .tokens
        .iter()
        .enumerate()
        .filter(|(_, t)| {
            t.kind != RawTokenKind::Whitespace
                && !(options.ignore_comments && t.kind == RawTokenKind::Comment)
        })
        .map(|(i, _)| i)
        .collect();
    let n_sig_idxs: Vec<usize> = new_parsed
        .tokens
        .iter()
        .enumerate()
        .filter(|(_, t)| {
            t.kind != RawTokenKind::Whitespace
                && !(options.ignore_comments && t.kind == RawTokenKind::Comment)
        })
        .map(|(i, _)| i)
        .collect();

    let o_canon_toks: Vec<String> = o_sig_idxs
        .iter()
        .map(|&idx| {
            let t = &old_parsed.tokens[idx];
            lookup_token_meta(t, true, maps, options)
                .0
                .unwrap_or_else(|| t.text.clone())
        })
        .collect();
    let n_canon_toks: Vec<String> = n_sig_idxs
        .iter()
        .map(|&idx| {
            let t = &new_parsed.tokens[idx];
            lookup_token_meta(t, false, maps, options)
                .0
                .unwrap_or_else(|| t.text.clone())
        })
        .collect();

    let mut o_hl = vec![TokenHighlight::None; old_parsed.tokens.len()];
    let mut n_hl = vec![TokenHighlight::None; new_parsed.tokens.len()];

    // Mark stripped comments as NoiseChange when ignore_comments is active and comment text differs
    if options.ignore_comments {
        let o_comment: String = old_parsed
            .tokens
            .iter()
            .filter(|t| t.kind == RawTokenKind::Comment)
            .map(|t| t.text.as_str())
            .collect();
        let n_comment: String = new_parsed
            .tokens
            .iter()
            .filter(|t| t.kind == RawTokenKind::Comment)
            .map(|t| t.text.as_str())
            .collect();
        if o_comment != n_comment {
            for (i, t) in old_parsed.tokens.iter().enumerate() {
                if t.kind == RawTokenKind::Comment {
                    o_hl[i] = TokenHighlight::NoiseChange;
                }
            }
            for (i, t) in new_parsed.tokens.iter().enumerate() {
                if t.kind == RawTokenKind::Comment {
                    n_hl[i] = TokenHighlight::NoiseChange;
                }
            }
        }
    }

    let ops = capture_diff_slices(Algorithm::Myers, &o_canon_toks, &n_canon_toks);
    for op in ops {
        match op {
            DiffOp::Equal {
                old_index,
                new_index,
                len,
            } => {
                for k in 0..len {
                    let oi = o_sig_idxs[old_index + k];
                    let ni = n_sig_idxs[new_index + k];
                    if old_parsed.tokens[oi].text != new_parsed.tokens[ni].text {
                        o_hl[oi] = TokenHighlight::NoiseChange;
                        n_hl[ni] = TokenHighlight::NoiseChange;
                    }
                }
            }
            DiffOp::Delete {
                old_index,
                old_len: len,
                ..
            } => {
                let hl = if kind == ChangeKind::NoiseOnly {
                    TokenHighlight::NoiseChange
                } else {
                    TokenHighlight::SemanticDelete
                };
                for k in 0..len {
                    o_hl[o_sig_idxs[old_index + k]] = hl;
                }
            }
            DiffOp::Insert {
                new_index,
                new_len: len,
                ..
            } => {
                let hl = if kind == ChangeKind::NoiseOnly {
                    TokenHighlight::NoiseChange
                } else {
                    TokenHighlight::SemanticAdd
                };
                for k in 0..len {
                    n_hl[n_sig_idxs[new_index + k]] = hl;
                }
            }
            DiffOp::Replace {
                old_index,
                old_len,
                new_index,
                new_len,
            } => {
                let hl = if kind == ChangeKind::NoiseOnly {
                    TokenHighlight::NoiseChange
                } else {
                    TokenHighlight::SemanticModify
                };
                for k in 0..old_len {
                    o_hl[o_sig_idxs[old_index + k]] = hl;
                }
                for k in 0..new_len {
                    n_hl[n_sig_idxs[new_index + k]] = hl;
                }
            }
        }
    }

    let o_spans = old_parsed
        .tokens
        .iter()
        .enumerate()
        .map(|(i, t)| {
            let (normalized, counterpart) = lookup_token_meta(t, true, maps, options);
            TokenSpan {
                text: t.text.clone(),
                normalized,
                counterpart,
                highlight: o_hl[i],
            }
        })
        .collect();

    let n_spans = new_parsed
        .tokens
        .iter()
        .enumerate()
        .map(|(i, t)| {
            let (normalized, counterpart) = lookup_token_meta(t, false, maps, options);
            TokenSpan {
                text: t.text.clone(),
                normalized,
                counterpart,
                highlight: n_hl[i],
            }
        })
        .collect();

    (
        LineSide {
            line_no: old_parsed.line_no,
            raw_text: old_parsed.raw_text.clone(),
            normalized_text: old_norm.canonical_display.clone(),
            tokens: o_spans,
        },
        LineSide {
            line_no: new_parsed.line_no,
            raw_text: new_parsed.raw_text.clone(),
            normalized_text: new_norm.canonical_display.clone(),
            tokens: n_spans,
        },
    )
}

fn build_summary(rows: &[AlignedRow], maps: &CanonicalMaps) -> DiffSummary {
    let mut s = DiffSummary {
        total_rows: rows.len(),
        ..Default::default()
    };

    let mut seen_cfg_events: HashSet<String> = HashSet::new();

    for r in rows {
        match r.kind {
            ChangeKind::Unchanged => s.unchanged_rows += 1,
            ChangeKind::NoiseOnly => s.noise_filtered_rows += 1,
            ChangeKind::Modified => s.semantic_modified_rows += 1,
            ChangeKind::Added => s.semantic_added_rows += 1,
            ChangeKind::Removed => s.semantic_removed_rows += 1,
        }
        if let Some(tag) = &r.cfg_tag {
            let key = match tag {
                CfgReorderTag::BranchInverted { .. } => "branch_inverted".to_string(),
                CfgReorderTag::GuardFlattened { .. } => "guard_flattened".to_string(),
                CfgReorderTag::LabelMoved {
                    label_old,
                    label_new,
                    ..
                } => format!("label:{}:{}", label_old, label_new),
                CfgReorderTag::CaseReordered { case_key } => format!("case:{}", case_key),
                CfgReorderTag::DeclarationBlock => continue,
            };
            if seen_cfg_events.insert(key) {
                s.cfg_reorders_aligned += 1;
            }
        }
    }

    for (cls, id, o, n) in &maps.id_to_pair {
        let o_disp = if o.is_empty() { "—".to_string() } else { o.clone() };
        let n_disp = if n.is_empty() { "—".to_string() } else { n.clone() };
        match cls {
            IdentClass::AutoVar | IdentClass::AutoArg => {
                s.variable_mappings.push((id.clone(), o_disp, n_disp));
            }
            IdentClass::Sub | IdentClass::Loc | IdentClass::Dat => {
                s.symbol_mappings.push((id.clone(), o_disp, n_disp));
            }
            IdentClass::Regular => {}
        }
    }

    s
}
