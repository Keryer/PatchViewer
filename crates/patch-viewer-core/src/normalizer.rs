use std::collections::HashMap;

use once_cell::sync::Lazy;
use regex::Regex;

use crate::config::DiffOptions;
use crate::parser::{LineRole, ParsedLine, RawToken, RawTokenKind};
use crate::type_norm::{normalize_line_pointer_units, VarTypeTable};

static RE_SUB: Lazy<Regex> = Lazy::new(|| Regex::new(r"^sub_[0-9A-Fa-f]+$").unwrap());
static RE_LOC: Lazy<Regex> =
    Lazy::new(|| Regex::new(r"^(?:(?:loc|locret)_[0-9A-Fa-f]+|LABEL_\d+)$").unwrap());
static RE_DAT: Lazy<Regex> = Lazy::new(|| {
    Regex::new(r"^(?:off|byte|word|dword|qword|xmmword|ymmword|unk|asc|stru|flt|dbl|jpt)_[0-9A-Fa-f]+$").unwrap()
});
static RE_AUTO_VAR: Lazy<Regex> =
    Lazy::new(|| Regex::new(r"^(?:v\d+(?:_\d+)?|result|[ijk])$").unwrap());
static RE_AUTO_ARG: Lazy<Regex> = Lazy::new(|| Regex::new(r"^a\d+$").unwrap());

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub enum IdentClass {
    Sub,
    Loc,
    Dat,
    AutoVar,
    AutoArg,
    Regular,
}

pub fn classify_identifier(ident: &str) -> IdentClass {
    if RE_SUB.is_match(ident) {
        IdentClass::Sub
    } else if RE_LOC.is_match(ident) {
        IdentClass::Loc
    } else if RE_DAT.is_match(ident) {
        IdentClass::Dat
    } else if RE_AUTO_VAR.is_match(ident) {
        IdentClass::AutoVar
    } else if RE_AUTO_ARG.is_match(ident) {
        IdentClass::AutoArg
    } else {
        IdentClass::Regular
    }
}

/// Normalized representation of a single line, either generic (category placeholders)
/// or sequentially numbered using a canonical map.
#[derive(Debug, Clone)]
pub struct NormalizedLine {
    pub line_no: usize,
    pub raw_text: String,
    pub role: LineRole,
    /// Whitespace-trimmed generic normalized key (`$VAR`, `$SUB`, `$LOC`, `$DAT`, `$ARG`)
    /// used for CFG structure alignment and coarse line pairing.
    pub generic_key: String,
    /// Canonical numbered normalized key (`$VAR_1`, `$SUB_1`, ...)
    /// used for final semantic vs noise-only diff classification.
    pub canonical_key: String,
    /// Normalized display text preserving leading indentation.
    pub canonical_display: String,
    /// For each non-whitespace token (excluding stripped comments), its `(raw_text, canonical_opt)`.
    pub token_mappings: Vec<(String, Option<String>)>,
}

#[derive(Debug, Default)]
pub struct CanonicalMaps {
    pub old_to_id: HashMap<String, String>,
    pub new_to_id: HashMap<String, String>,
    pub id_to_pair: Vec<(IdentClass, String, String, String)>, // (class, id, old, new)
    sub_counter: usize,
    loc_counter: usize,
    dat_counter: usize,
    var_counter: usize,
    arg_counter: usize,
}

impl CanonicalMaps {
    fn next_id(&mut self, class: IdentClass) -> String {
        match class {
            IdentClass::Sub => {
                self.sub_counter += 1;
                format!("$SUB_{}", self.sub_counter)
            }
            IdentClass::Loc => {
                self.loc_counter += 1;
                format!("$LOC_{}", self.loc_counter)
            }
            IdentClass::Dat => {
                self.dat_counter += 1;
                format!("$DAT_{}", self.dat_counter)
            }
            IdentClass::AutoVar => {
                self.var_counter += 1;
                format!("$VAR_{}", self.var_counter)
            }
            IdentClass::AutoArg => {
                self.arg_counter += 1;
                format!("$ARG_{}", self.arg_counter)
            }
            IdentClass::Regular => String::new(),
        }
    }

    pub fn bind_pair(&mut self, class: IdentClass, old_sym: &str, new_sym: &str) {
        if class == IdentClass::Regular {
            return;
        }
        let existing_old = self.old_to_id.get(old_sym).cloned();
        let existing_new = self.new_to_id.get(new_sym).cloned();
        match (existing_old, existing_new) {
            (Some(_), Some(_)) => {}
            (Some(id), None) => {
                // Only bind `new_sym` to `id` if `id` is not already claimed by a different `new_sym`
                let already_claimed = self
                    .id_to_pair
                    .iter()
                    .any(|(_, cid, _, n)| cid == &id && !n.is_empty() && n != new_sym);
                if !already_claimed {
                    self.new_to_id.insert(new_sym.to_string(), id.clone());
                    if let Some(entry) = self.id_to_pair.iter_mut().find(|(_, cid, _, _)| cid == &id) {
                        entry.3 = new_sym.to_string();
                    }
                }
            }
            (None, Some(id)) => {
                let already_claimed = self
                    .id_to_pair
                    .iter()
                    .any(|(_, cid, o, _)| cid == &id && !o.is_empty() && o != old_sym);
                if !already_claimed {
                    self.old_to_id.insert(old_sym.to_string(), id.clone());
                    if let Some(entry) = self.id_to_pair.iter_mut().find(|(_, cid, _, _)| cid == &id) {
                        entry.2 = old_sym.to_string();
                    }
                }
            }
            (None, None) => {
                let id = self.next_id(class);
                self.old_to_id.insert(old_sym.to_string(), id.clone());
                self.new_to_id.insert(new_sym.to_string(), id.clone());
                self.id_to_pair.push((
                    class,
                    id,
                    old_sym.to_string(),
                    new_sym.to_string(),
                ));
            }
        }
    }

    pub fn ensure_single(&mut self, is_old: bool, class: IdentClass, sym: &str) -> String {
        if class == IdentClass::Regular {
            return sym.to_string();
        }
        let map = if is_old {
            &self.old_to_id
        } else {
            &self.new_to_id
        };
        if let Some(existing) = map.get(sym) {
            return existing.clone();
        }
        let id = self.next_id(class);
        if is_old {
            self.old_to_id.insert(sym.to_string(), id.clone());
            self.id_to_pair
                .push((class, id.clone(), sym.to_string(), String::new()));
        } else {
            self.new_to_id.insert(sym.to_string(), id.clone());
            self.id_to_pair
                .push((class, id.clone(), String::new(), sym.to_string()));
        }
        id
    }
}

fn should_normalize_class(class: IdentClass, options: &DiffOptions) -> bool {
    match class {
        IdentClass::Sub | IdentClass::Loc | IdentClass::Dat => options.normalize_addresses,
        IdentClass::AutoVar | IdentClass::AutoArg => options.normalize_variables,
        IdentClass::Regular => false,
    }
}

fn generic_placeholder(class: IdentClass) -> &'static str {
    match class {
        IdentClass::Sub => "$SUB",
        IdentClass::Loc => "$LOC",
        IdentClass::Dat => "$DAT",
        IdentClass::AutoVar => "$VAR",
        IdentClass::AutoArg => "$ARG",
        IdentClass::Regular => "",
    }
}

/// Filter out redundant IDA macro wrappers (`LOBYTE`, `HIBYTE`, `LOWORD`, `HIWORD`, `LODWORD`, `HIDWORD`)
/// or redundant `(unsigned int)` casts when `simplify_ida_casts` is enabled.
fn preprocess_tokens_for_casts(tokens: &[RawToken], options: &DiffOptions) -> Vec<RawToken> {
    if !options.simplify_ida_casts {
        return tokens.to_vec();
    }
    let mut out = Vec::with_capacity(tokens.len());
    let mut i = 0;
    while i < tokens.len() {
        let tok = &tokens[i];
        if tok.kind == RawTokenKind::Identifier
            && matches!(
                tok.text.as_str(),
                "LOBYTE" | "HIBYTE" | "LOWORD" | "HIWORD" | "LODWORD" | "HIDWORD" | "SLOBYTE" | "SHIBYTE"
            )
            && i + 1 < tokens.len()
            && tokens[i + 1].text == "("
        {
            // Strip macro name and its balanced wrapping parens if simple
            let mut depth = 0isize;
            let mut j = i + 1;
            let mut matched_end = None;
            while j < tokens.len() {
                if tokens[j].text == "(" {
                    depth += 1;
                } else if tokens[j].text == ")" {
                    depth -= 1;
                    if depth == 0 {
                        matched_end = Some(j);
                        break;
                    }
                }
                j += 1;
            }
            if let Some(end) = matched_end {
                out.extend_from_slice(&tokens[i + 2..end]);
                i = end + 1;
                continue;
            }
        }
        // Strip `(void *)`, `(unsigned int)`, `(__int64)` simple C casts
        if tok.text == "(" {
            let mut j = i + 1;
            let mut is_simple_cast = false;
            let mut has_cast_kw = false;
            while j < tokens.len() && j <= i + 7 {
                let t = &tokens[j];
                if t.text == ")" {
                    is_simple_cast = has_cast_kw;
                    break;
                }
                if matches!(
                    t.text.as_str(),
                    "void" | "unsigned" | "signed" | "int" | "char" | "short" | "long"
                        | "__int64" | "__int32" | "__int16" | "__int8" | "_DWORD" | "_QWORD"
                        | "_WORD" | "_BYTE" | "*"
                ) {
                    has_cast_kw = true;
                } else if t.kind != RawTokenKind::Whitespace {
                    break;
                }
                j += 1;
            }
            if is_simple_cast {
                i = j + 1;
                // Skip trailing whitespace right after cast
                while i < tokens.len() && tokens[i].kind == RawTokenKind::Whitespace {
                    i += 1;
                }
                continue;
            }
        }
        out.push(tok.clone());
        i += 1;
    }
    out
}

fn is_member_access(toks: &[RawToken], idx: usize) -> bool {
    let mut k = idx;
    while k > 0 {
        k -= 1;
        if toks[k].kind == RawTokenKind::Whitespace {
            continue;
        }
        return toks[k].text == "." || toks[k].text == "->";
    }
    false
}

fn prepare_tokens(line: &ParsedLine, types: &VarTypeTable, options: &DiffOptions) -> Vec<RawToken> {
    let ptr_toks = normalize_line_pointer_units(line, &line.tokens, types, options);
    preprocess_tokens_for_casts(&ptr_toks, options)
}

/// Produce the generic normalized line key (`$VAR`, `$SUB`, ...) used before paired binding.
pub fn compute_generic_key(line: &ParsedLine, options: &DiffOptions) -> String {
    compute_generic_key_with_types(line, &VarTypeTable::default(), options)
}

/// Produce the generic normalized line key (`$VAR`, `$SUB`, ...), including pointer/bitfield
/// minimum-unit normalization using `types`.
pub fn compute_generic_key_with_types(
    line: &ParsedLine,
    types: &VarTypeTable,
    options: &DiffOptions,
) -> String {
    let toks = prepare_tokens(line, types, options);
    let mut out = String::new();
    let mut prev_ws = true;
    for (idx, t) in toks.iter().enumerate() {
        match t.kind {
            RawTokenKind::Comment if options.ignore_comments => {}
            RawTokenKind::Whitespace => {
                if !prev_ws {
                    out.push(' ');
                    prev_ws = true;
                }
            }
            RawTokenKind::Identifier => {
                let cls = if is_member_access(&toks, idx) {
                    IdentClass::Regular
                } else {
                    classify_identifier(&t.text)
                };
                if should_normalize_class(cls, options) {
                    out.push_str(generic_placeholder(cls));
                } else {
                    out.push_str(&t.text);
                }
                prev_ws = false;
            }
            _ => {
                out.push_str(&t.text);
                prev_ws = false;
            }
        }
    }
    out.trim().to_string()
}

/// Extract ordered `(IdentClass, raw_identifier)` occurrences from a parsed line.
pub fn line_normalizable_idents(line: &ParsedLine, options: &DiffOptions) -> Vec<(IdentClass, String)> {
    line_normalizable_idents_with_types(line, &VarTypeTable::default(), options)
}

/// Extract ordered `(IdentClass, raw_identifier)` occurrences using `types` for pointer normalization.
pub fn line_normalizable_idents_with_types(
    line: &ParsedLine,
    types: &VarTypeTable,
    options: &DiffOptions,
) -> Vec<(IdentClass, String)> {
    let toks = prepare_tokens(line, types, options);
    let mut res = Vec::new();
    for (idx, t) in toks.iter().enumerate() {
        if t.kind == RawTokenKind::Identifier {
            if is_member_access(&toks, idx) {
                continue;
            }
            let cls = classify_identifier(&t.text);
            if should_normalize_class(cls, options) {
                res.push((cls, t.text.clone()));
            }
        }
    }
    res
}

/// Build a canonical `NormalizedLine` using the provided `CanonicalMaps`.
pub fn render_canonical_line(
    line: &ParsedLine,
    is_old: bool,
    maps: &mut CanonicalMaps,
    options: &DiffOptions,
) -> NormalizedLine {
    render_canonical_line_with_types(line, is_old, &VarTypeTable::default(), maps, options)
}

/// Build a canonical `NormalizedLine` using `types` and the provided `CanonicalMaps`.
pub fn render_canonical_line_with_types(
    line: &ParsedLine,
    is_old: bool,
    types: &VarTypeTable,
    maps: &mut CanonicalMaps,
    options: &DiffOptions,
) -> NormalizedLine {
    let generic_key = compute_generic_key_with_types(line, types, options);
    let toks = prepare_tokens(line, types, options);

    let mut key_out = String::new();
    let mut disp_out = String::new();
    let mut prev_ws = true;
    let mut at_line_start = true;
    let mut token_mappings = Vec::new();

    for (idx, t) in toks.iter().enumerate() {
        match t.kind {
            RawTokenKind::Comment if options.ignore_comments => {}
            RawTokenKind::Whitespace => {
                if at_line_start {
                    disp_out.push_str(&t.text);
                } else if !prev_ws {
                    key_out.push(' ');
                    disp_out.push(' ');
                    prev_ws = true;
                }
            }
            RawTokenKind::Identifier => {
                at_line_start = false;
                let cls = if is_member_access(&toks, idx) {
                    IdentClass::Regular
                } else {
                    classify_identifier(&t.text)
                };
                if should_normalize_class(cls, options) {
                    let canon = if matches!(cls, IdentClass::Sub | IdentClass::Loc | IdentClass::Dat)
                        && !options.sequential_address_numbering
                    {
                        generic_placeholder(cls).to_string()
                    } else {
                        maps.ensure_single(is_old, cls, &t.text)
                    };
                    key_out.push_str(&canon);
                    disp_out.push_str(&canon);
                    token_mappings.push((t.text.clone(), Some(canon)));
                } else {
                    key_out.push_str(&t.text);
                    disp_out.push_str(&t.text);
                    token_mappings.push((t.text.clone(), None));
                }
                prev_ws = false;
            }
            _ => {
                at_line_start = false;
                key_out.push_str(&t.text);
                disp_out.push_str(&t.text);
                token_mappings.push((t.text.clone(), None));
                prev_ws = false;
            }
        }
    }

    NormalizedLine {
        line_no: line.line_no,
        raw_text: line.raw_text.clone(),
        role: line.role,
        generic_key,
        canonical_key: key_out.trim().to_string(),
        canonical_display: disp_out.trim_end().to_string(),
        token_mappings,
    }
}

/// Invert a C boolean condition expression for detecting `if/else` branch inversions
/// and guard-clause vs nested-`if` conversions.
pub fn invert_condition(cond: &str) -> String {
    let s = cond.trim();
    if let Some(inner) = s.strip_prefix('!') {
        let inner = inner.trim();
        if inner.starts_with('(') && inner.ends_with(')') && is_balanced_outer_parens(inner) {
            return inner[1..inner.len() - 1].trim().to_string();
        }
        return inner.to_string();
    }
    // Check top-level binary comparison operators (`==`, `!=`, `<`, `<=`, `>`, `>=`)
    if let Some(inverted) = invert_top_level_comparison(s) {
        return inverted;
    }
    if s.contains(' ') || s.contains("&&") || s.contains("||") {
        format!("!({})", s)
    } else {
        format!("!{}", s)
    }
}

/// Check if two normalized condition strings are logical negations of each other.
pub fn conditions_are_inverted(cond_a: &str, cond_b: &str) -> bool {
    let a = normalize_cond_ws(cond_a);
    let b = normalize_cond_ws(cond_b);
    if a.is_empty() || b.is_empty() {
        return false;
    }
    normalize_cond_ws(&invert_condition(&a)) == b || normalize_cond_ws(&invert_condition(&b)) == a
}

fn normalize_cond_ws(s: &str) -> String {
    let mut in_bc = false;
    let toks = crate::parser::lex_line(s, &mut in_bc);
    let mut out = String::new();
    let mut prev_ws = true;
    for t in toks {
        if t.kind == RawTokenKind::Whitespace {
            if !prev_ws {
                out.push(' ');
                prev_ws = true;
            }
        } else {
            out.push_str(&t.text);
            prev_ws = false;
        }
    }
    out.trim().to_string()
}

fn is_balanced_outer_parens(s: &str) -> bool {
    let chars: Vec<char> = s.chars().collect();
    if chars.first() != Some(&'(') || chars.last() != Some(&')') {
        return false;
    }
    let mut depth = 0isize;
    for (idx, c) in chars.iter().enumerate() {
        match c {
            '(' => depth += 1,
            ')' => {
                depth -= 1;
                if depth == 0 && idx + 1 < chars.len() {
                    return false;
                }
            }
            _ => {}
        }
    }
    depth == 0
}

fn invert_top_level_comparison(s: &str) -> Option<String> {
    let mut in_bc = false;
    let toks = crate::parser::lex_line(s, &mut in_bc);
    let meaningful: Vec<&RawToken> = toks
        .iter()
        .filter(|t| t.kind != RawTokenKind::Whitespace)
        .collect();
    let mut paren_depth = 0isize;
    let mut op_idx = None;
    for (i, t) in meaningful.iter().enumerate() {
        if t.text == "(" || t.text == "[" {
            paren_depth += 1;
        } else if t.text == ")" || t.text == "]" {
            paren_depth -= 1;
        } else if paren_depth == 0 {
            if matches!(t.text.as_str(), "&&" | "||") {
                // Compound boolean expression: requires De Morgan wrap, don't swap single cmp
                return None;
            }
            if matches!(t.text.as_str(), "==" | "!=" | "<" | "<=" | ">" | ">=") {
                if op_idx.is_some() {
                    return None;
                }
                op_idx = Some(i);
            }
        }
    }
    let idx = op_idx?;
    let flipped = match meaningful[idx].text.as_str() {
        "==" => "!=",
        "!=" => "==",
        "<" => ">=",
        ">=" => "<",
        ">" => "<=",
        "<=" => ">",
        _ => return None,
    };
    let lhs: Vec<&str> = meaningful[..idx].iter().map(|t| t.text.as_str()).collect();
    let rhs: Vec<&str> = meaningful[idx + 1..].iter().map(|t| t.text.as_str()).collect();
    Some(format!("{} {} {}", lhs.join(" "), flipped, rhs.join(" ")))
}
