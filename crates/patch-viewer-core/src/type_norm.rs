use std::collections::HashMap;

use crate::config::DiffOptions;
use crate::parser::{LineRole, ParsedLine, RawToken, RawTokenKind};

/// Per-function map of pointer/array variable names to their element stride in bytes (`sizeof(*p)`),
/// extracted from the function signature and Hex-Rays local variable declarations.
#[derive(Debug, Clone, Default)]
pub struct VarTypeTable {
    ptr_elem_sizes: HashMap<String, usize>,
    sig_line_no: Option<usize>,
}

impl VarTypeTable {
    /// Extract pointer/array element sizes from parsed lines of a decompiled function.
    /// Non-pointer scalar variables are intentionally omitted so integer arithmetic is never scaled.
    pub fn from_lines(lines: &[ParsedLine]) -> Self {
        let mut table = Self::default();

        // Detect signature line: first code/decl line before `{` containing balanced `(...)`
        // and not terminated by `;`.
        for line in lines {
            if matches!(line.role, LineRole::Blank | LineRole::CommentOnly) {
                continue;
            }
            let sig = sig_tokens(&line.tokens);
            if sig.is_empty() || sig[0].text == "{" || sig[0].text == "}" {
                break;
            }
            if sig.last().map(|t| t.text.as_str()) == Some(";") {
                continue;
            }
            if let Some(open) = sig.iter().position(|t| t.text == "(") {
                let sig_vec = sig_owned(&sig);
                if let Some(close) = find_matching_delim(&sig_vec, open, "(", ")") {
                    table.sig_line_no = Some(line.line_no);
                    let params = &sig[open + 1..close];
                    for param in split_top_level_commas(params) {
                        if let Some((name, elem_size)) = parse_decl_entry(&param) {
                            table.ptr_elem_sizes.insert(name, elem_size);
                        }
                    }
                    break;
                }
            }
        }

        // Collect pointer and array local variable declarations.
        for line in lines {
            if line.role != LineRole::Declaration {
                continue;
            }
            let mut sig = sig_tokens(&line.tokens);
            if sig.last().map(|t| t.text.as_str()) == Some(";") {
                sig.pop();
            }
            if let Some((name, elem_size)) = parse_decl_entry(&sig) {
                table.ptr_elem_sizes.insert(name, elem_size);
            }
        }

        table
    }

    pub fn elem_size(&self, ident: &str) -> Option<usize> {
        self.ptr_elem_sizes.get(ident).copied()
    }

    pub fn is_signature_line(&self, line_no: usize) -> bool {
        self.sig_line_no == Some(line_no)
    }
}

fn sig_tokens<'a>(tokens: &'a [RawToken]) -> Vec<&'a RawToken> {
    tokens
        .iter()
        .filter(|t| !matches!(t.kind, RawTokenKind::Whitespace | RawTokenKind::Comment))
        .collect()
}

fn sig_owned(sig: &[&RawToken]) -> Vec<RawToken> {
    sig.iter().map(|t| (*t).clone()).collect()
}

fn split_top_level_commas<'a>(toks: &[&'a RawToken]) -> Vec<Vec<&'a RawToken>> {
    let mut groups = Vec::new();
    let mut start = 0usize;
    let mut depth = 0isize;
    for (idx, t) in toks.iter().enumerate() {
        match t.text.as_str() {
            "(" | "[" => depth += 1,
            ")" | "]" => depth -= 1,
            "," if depth == 0 => {
                if start < idx {
                    groups.push(toks[start..idx].to_vec());
                }
                start = idx + 1;
            }
            _ => {}
        }
    }
    if start < toks.len() {
        groups.push(toks[start..].to_vec());
    }
    groups
}

fn is_type_qualifier(s: &str) -> bool {
    matches!(
        s,
        "const"
            | "volatile"
            | "restrict"
            | "__restrict"
            | "signed"
            | "unsigned"
            | "struct"
            | "union"
            | "enum"
            | "__ptr64"
            | "__ptr32"
            | "__unaligned"
    )
}

fn scalar_type_size(words: &[&str], saw_sign_kw: bool) -> Option<usize> {
    let core: Vec<&str> = words
        .iter()
        .copied()
        .filter(|w| !is_type_qualifier(w))
        .collect();

    if core.is_empty() {
        return if saw_sign_kw { Some(4) } else { None };
    }

    if core.len() == 2 && core[0] == "long" && core[1] == "long" {
        return Some(8);
    }
    if core.len() == 2 && core[0] == "long" && core[1] == "int" {
        return Some(8);
    }
    if core.len() == 2 && core[0] == "short" && core[1] == "int" {
        return Some(2);
    }
    if core.len() != 1 {
        return None;
    }

    match core[0] {
        "char" | "__int8" | "_BYTE" | "BYTE" | "int8_t" | "uint8_t" | "bool" | "_BOOL1"
        | "void" => Some(1),
        "short" | "__int16" | "_WORD" | "WORD" | "int16_t" | "uint16_t" | "_BOOL2" => Some(2),
        "int" | "_DWORD" | "DWORD" | "int32_t" | "uint32_t" | "__int32" | "_BOOL4" | "float" => {
            Some(4)
        }
        "__int64" | "_QWORD" | "QWORD" | "int64_t" | "uint64_t" | "size_t" | "ssize_t"
        | "ptrdiff_t" | "intptr_t" | "uintptr_t" | "double" | "long" => Some(8),
        "__m128" | "__m128i" | "__m128d" | "_OWORD" | "__int128" => Some(16),
        "__m256" | "__m256i" | "_YMMWORD" => Some(32),
        _ => None,
    }
}

/// Parse one parameter or local variable declaration into `(var_name, elem_size_bytes)`.
fn parse_decl_entry(toks: &[&RawToken]) -> Option<(String, usize)> {
    if toks.is_empty() {
        return None;
    }
    // Skip function pointer declarations like `unsigned int (__fastcall *v19)(...)`.
    if toks.iter().any(|t| t.text == "(") {
        return None;
    }

    let mut end = toks.len();
    let mut is_array = false;
    while end > 0 && toks[end - 1].text == "]" {
        let open = toks[..end].iter().rposition(|t| t.text == "[")?;
        is_array = true;
        end = open;
    }

    if end == 0 || toks[end - 1].kind != RawTokenKind::Identifier {
        return None;
    }
    let var_name = toks[end - 1].text.clone();
    let prefix = &toks[..end - 1];
    if prefix.is_empty() {
        return None;
    }

    let mut star_count = 0usize;
    let mut type_words: Vec<&str> = Vec::new();
    let mut saw_sign_kw = false;

    for t in prefix {
        if t.text == "*" {
            star_count += 1;
        } else if t.kind == RawTokenKind::Identifier {
            if t.text == "signed" || t.text == "unsigned" {
                saw_sign_kw = true;
            }
            type_words.push(t.text.as_str());
        } else {
            return None;
        }
    }

    if star_count == 0 && !is_array {
        return None;
    }
    if star_count >= 2 {
        return Some((var_name, 8));
    }
    scalar_type_size(&type_words, saw_sign_kw).map(|sz| (var_name, sz))
}

/// Parse C decimal or hex integer literal, rejecting already-normalized unit literals (`8B`, `10b`, `7w`).
fn parse_c_int(s: &str) -> Option<i128> {
    if s.ends_with('B') || s.ends_with('b') || s.ends_with('w') {
        return None;
    }
    let lower = s.to_ascii_lowercase();
    let mut digits = lower.as_str();
    for suffix in ["ui64", "i64", "ui32", "i32", "ull", "ll", "ul", "u", "l"] {
        if let Some(stripped) = digits.strip_suffix(suffix) {
            if !stripped.is_empty() {
                digits = stripped;
                break;
            }
        }
    }
    if let Some(hex) = digits.strip_prefix("0x") {
        if hex.is_empty() {
            return None;
        }
        i128::from_str_radix(hex, 16).ok()
    } else {
        digits.parse::<i128>().ok()
    }
}

fn parse_unit_val(s: &str, suffix: char) -> Option<i128> {
    let raw = s.strip_suffix(suffix)?;
    if raw.is_empty() {
        return None;
    }
    raw.parse::<i128>().ok()
}

fn find_matching_delim(toks: &[RawToken], open_idx: usize, open: &str, close: &str) -> Option<usize> {
    if toks.get(open_idx)?.text != open {
        return None;
    }
    let mut depth = 0isize;
    for (idx, t) in toks.iter().enumerate().skip(open_idx) {
        if t.text == open {
            depth += 1;
        } else if t.text == close {
            depth -= 1;
            if depth == 0 {
                return Some(idx);
            }
        }
    }
    None
}

/// Match a C scalar/IDA pointer cast `(T *)` or `(T **)` at `start`.
/// Returns `(close_paren_idx, deref_elem_size, star_count)`.
fn parse_ptr_cast(toks: &[RawToken], start: usize) -> Option<(usize, usize, usize)> {
    if toks.get(start)?.text != "(" {
        return None;
    }
    let close = find_matching_delim(toks, start, "(", ")")?;
    if close <= start + 2 {
        return None;
    }
    let inner = &toks[start + 1..close];
    let first_star = inner.iter().position(|t| t.text == "*")?;
    if first_star == 0 {
        return None;
    }
    let mut star_count = 0usize;
    for t in &inner[first_star..] {
        if t.text != "*" {
            return None;
        }
        star_count += 1;
    }

    let mut type_words: Vec<&str> = Vec::new();
    let mut saw_sign_kw = false;
    for t in &inner[..first_star] {
        if t.kind != RawTokenKind::Identifier {
            return None;
        }
        if t.text == "signed" || t.text == "unsigned" {
            saw_sign_kw = true;
        }
        type_words.push(t.text.as_str());
    }

    let base_size = scalar_type_size(&type_words, saw_sign_kw)?;
    let elem_size = if star_count >= 2 { 8 } else { base_size };
    Some((close, elem_size, star_count))
}

/// Parse a scalar pointer type specifier `[qualifiers/base_type]+ *+` starting at `start`.
/// Returns `(end_idx_exclusive, star_count)`.
fn parse_scalar_ptr_type_span(toks: &[RawToken], start: usize) -> Option<(usize, usize)> {
    let mut idx = start;
    let mut words: Vec<&str> = Vec::new();
    let mut saw_sign_kw = false;

    while let Some(t) = toks.get(idx) {
        if t.kind != RawTokenKind::Identifier || t.text.starts_with('$') {
            break;
        }
        // Only consume known type words / qualifiers so variable names aren't eaten.
        let s = t.text.as_str();
        if !is_type_qualifier(s) && scalar_type_size(&[s], false).is_none() {
            break;
        }
        if s == "signed" || s == "unsigned" {
            saw_sign_kw = true;
        }
        words.push(s);
        idx += 1;
    }

    if words.is_empty() || scalar_type_size(&words, saw_sign_kw).is_none() {
        return None;
    }

    let mut star_count = 0usize;
    while toks.get(idx).map(|t| t.text.as_str()) == Some("*") {
        star_count += 1;
        idx += 1;
    }
    if star_count == 0 {
        return None;
    }

    Some((idx, star_count))
}

fn ptr_canon_token(star_count: usize) -> RawToken {
    make_ident(if star_count >= 2 { "$PTR2" } else { "$PTR" })
}

/// Replace scalar/IDA pointer type specifiers (`unsigned __int16 *`, `char *`, `void **`)
/// with `$PTR` / `$PTR2` inside declarations, signatures, and function-pointer parameter lists.
fn normalize_scalar_ptr_types(toks: &[RawToken], in_decl_or_sig: bool) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;
    let mut bracket_depth = 0isize;

    while i < toks.len() {
        let t = &toks[i];
        if t.text == "[" {
            bracket_depth += 1;
            out.push(t.clone());
            i += 1;
            continue;
        }
        if t.text == "]" {
            bracket_depth -= 1;
            out.push(t.clone());
            i += 1;
            continue;
        }

        if in_decl_or_sig && bracket_depth == 0 {
            let prev_is_member = i > 0 && matches!(toks[i - 1].text.as_str(), "." | "->" | "::");
            if !prev_is_member {
                if let Some((end, stars)) = parse_scalar_ptr_type_span(toks, i) {
                    out.push(ptr_canon_token(stars));
                    i = end;
                    continue;
                }
            }
        } else if !in_decl_or_sig && t.text == "(" {
            // Look for function pointer cast `(<ret> (<conv> *) (<params>))`
            if let Some(cast_end) = find_matching_delim(toks, i, "(", ")") {
                if let Some((params_open_rel, params_close_rel)) =
                    find_fnptr_cast_params(&toks[i..=cast_end])
                {
                    out.extend(normalize_scalar_ptr_params(
                        &toks[i..=cast_end],
                        params_open_rel,
                        params_close_rel,
                    ));
                    i = cast_end + 1;
                    continue;
                }
            }
        }

        out.push(t.clone());
        i += 1;
    }

    out
}

fn find_fnptr_cast_params(span: &[RawToken]) -> Option<(usize, usize)> {
    if span.len() < 7 || span.first().map(|t| t.text.as_str()) != Some("(") {
        return None;
    }
    for idx in 1..span.len().saturating_sub(3) {
        if span[idx].text != "(" {
            continue;
        }
        if span[1..idx]
            .iter()
            .any(|t| matches!(t.text.as_str(), ">>" | "<<" | "+" | "-" | "&" | "|" | ";" | "="))
        {
            continue;
        }
        if let Some(close_rel) = find_matching_delim(span, idx, "(", ")") {
            let middle = &span[idx + 1..close_rel];
            if !middle.is_empty()
                && middle.last().map(|t| t.text.as_str()) == Some("*")
                && middle[..middle.len() - 1].iter().all(|t| {
                    matches!(
                        t.text.as_str(),
                        "__fastcall" | "__cdecl" | "__stdcall" | "__thiscall" | "__usercall"
                            | "__userpurge"
                    )
                })
                && span.get(close_rel + 1).map(|t| t.text.as_str()) == Some("(")
            {
                if let Some(params_close) = find_matching_delim(span, close_rel + 1, "(", ")") {
                    if params_close == span.len() - 2 {
                        return Some((close_rel + 1, params_close));
                    }
                }
            }
        }
    }
    None
}

fn normalize_scalar_ptr_params(
    span: &[RawToken],
    params_open_rel: usize,
    params_close_rel: usize,
) -> Vec<RawToken> {
    let mut out = span[..=params_open_rel].to_vec();
    let mut i = params_open_rel + 1;
    while i < params_close_rel {
        if let Some((type_end, stars)) = parse_scalar_ptr_type_span(span, i) {
            if matches!(
                span.get(type_end).map(|t| t.text.as_str()),
                Some(",") | Some(")")
            ) {
                out.push(ptr_canon_token(stars));
                i = type_end;
                continue;
            }
        }
        out.push(span[i].clone());
        i += 1;
    }
    out.extend_from_slice(&span[params_close_rel..]);
    out
}

fn make_ident(s: &str) -> RawToken {
    RawToken {
        kind: RawTokenKind::Identifier,
        text: s.to_string(),
    }
}

fn make_op(s: &str) -> RawToken {
    RawToken {
        kind: RawTokenKind::Operator,
        text: s.to_string(),
    }
}

fn make_punct(s: &str) -> RawToken {
    RawToken {
        kind: RawTokenKind::Punctuation,
        text: s.to_string(),
    }
}

fn make_num(s: &str) -> RawToken {
    RawToken {
        kind: RawTokenKind::Number,
        text: s.to_string(),
    }
}

fn is_scalar_value_cast_close(toks: &[RawToken], close_idx: usize) -> bool {
    if toks.get(close_idx).map(|t| t.text.as_str()) != Some(")") {
        return false;
    }
    let mut depth = 0isize;
    let mut open_idx = None;
    for idx in (0..=close_idx).rev() {
        match toks[idx].text.as_str() {
            ")" => depth += 1,
            "(" => {
                depth -= 1;
                if depth == 0 {
                    open_idx = Some(idx);
                    break;
                }
            }
            _ => {}
        }
    }
    let Some(open) = open_idx else {
        return false;
    };
    let inner = &toks[open + 1..close_idx];
    if inner.is_empty() {
        return false;
    }
    let mut words: Vec<&str> = Vec::new();
    let mut saw_sign_kw = false;
    for t in inner {
        if t.kind != RawTokenKind::Identifier || t.text.starts_with('$') {
            return false;
        }
        if t.text == "signed" || t.text == "unsigned" {
            saw_sign_kw = true;
        }
        words.push(t.text.as_str());
    }
    scalar_type_size(&words, saw_sign_kw).is_some()
}

fn is_unary_op_pos(toks: &[RawToken], idx: usize) -> bool {
    if idx == 0 {
        return true;
    }
    let prev = &toks[idx - 1];
    if matches!(
        prev.text.as_str(),
        "(" | "["
            | ","
            | ";"
            | "="
            | "+="
            | "-="
            | "*="
            | "/="
            | "%="
            | "&="
            | "|="
            | "^="
            | "<<="
            | ">>="
            | "=="
            | "!="
            | "<"
            | "<="
            | ">"
            | ">="
            | "&&"
            | "||"
            | "+"
            | "-"
            | "*"
            | "/"
            | "%"
            | "&"
            | "|"
            | "^"
            | "<<"
            | ">>"
            | "!"
            | "~"
            | "?"
            | ":"
    ) {
        return true;
    }
    if prev.text == ")" && is_scalar_value_cast_close(toks, idx - 1) {
        return true;
    }
    matches!(prev.text.as_str(), "return" | "case")
}

fn emit_mem_access(width: usize, base_toks: Vec<RawToken>, offset_expr: OffsetExpr) -> Vec<RawToken> {
    let mut out = vec![make_ident(&format!("MEM_{width}B")), make_punct("(")];
    out.extend(base_toks);
    match offset_expr {
        OffsetExpr::ConstBytes(bytes) => {
            if bytes < 0 {
                out.push(make_op("-"));
                out.push(make_num(&format!("{}B", -bytes)));
            } else {
                out.push(make_op("+"));
                out.push(make_num(&format!("{bytes}B")));
            }
        }
        OffsetExpr::ScaledExpr { op, expr, elem_size } => {
            out.push(make_op(op));
            if elem_size == 1 {
                out.extend(expr);
            } else {
                let needs_parens = has_low_prec_op(&expr);
                if needs_parens {
                    out.push(make_punct("("));
                }
                out.extend(expr);
                if needs_parens {
                    out.push(make_punct(")"));
                }
                out.push(make_op("*"));
                out.push(make_num(&format!("{elem_size}B")));
            }
        }
    }
    out.push(make_punct(")"));
    out
}

fn has_low_prec_op(toks: &[RawToken]) -> bool {
    let mut depth = 0isize;
    for t in toks {
        match t.text.as_str() {
            "(" | "[" => depth += 1,
            ")" | "]" => depth -= 1,
            "+" | "-" | "|" | "^" | "&" | "<<" | ">>" if depth == 0 => return true,
            _ => {}
        }
    }
    false
}

enum OffsetExpr {
    ConstBytes(i128),
    ScaledExpr {
        op: &'static str,
        expr: Vec<RawToken>,
        elem_size: usize,
    },
}

/// Parse signed integer literal (`K` or `-K`), rejecting unit-suffixed numbers.
fn parse_signed_const(toks: &[RawToken]) -> Option<i128> {
    if toks.len() == 1 {
        parse_c_int(&toks[0].text)
    } else if toks.len() == 2 && toks[0].text == "-" {
        parse_c_int(&toks[1].text).map(|v| -v)
    } else if toks.len() == 2 && toks[0].text == "+" {
        parse_c_int(&toks[1].text)
    } else {
        None
    }
}

fn unwrap_outer_parens(toks: &[RawToken]) -> &[RawToken] {
    let mut slice = toks;
    while slice.len() >= 2
        && slice[0].text == "("
        && find_matching_delim(slice, 0, "(", ")") == Some(slice.len() - 1)
    {
        slice = &slice[1..slice.len() - 1];
    }
    slice
}

/// Find last top-level `+` or `-` in `toks` (excluding unary leading `+`/`-`).
fn split_top_level_add_sub(toks: &[RawToken]) -> Option<(usize, &'static str)> {
    let mut depth = 0isize;
    let mut last = None;
    for (idx, t) in toks.iter().enumerate() {
        match t.text.as_str() {
            "(" | "[" => depth += 1,
            ")" | "]" => depth -= 1,
            "+" if depth == 0 && idx > 0 && !is_unary_op_pos(toks, idx) => {
                last = Some((idx, "+"));
            }
            "-" if depth == 0 && idx > 0 && !is_unary_op_pos(toks, idx) => {
                last = Some((idx, "-"));
            }
            _ => {}
        }
    }
    last
}

/// Pass 2: Convert cast-based dereferences (`*((T *)p + k)`, `*(T *)(...)`, `*(T *)p`) into `MEM_<W>B(...)`.
fn pass_cast_derefs(toks: &[RawToken], types: &VarTypeTable, options: &DiffOptions) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;

    while i < toks.len() {
        if toks[i].text == "*" && is_unary_op_pos(toks, i) {
            // Pattern A: `*((T *)base + idx)` or `*((T *)base - K)`
            if toks.get(i + 1).map(|t| t.text.as_str()) == Some("(") {
                if let Some(outer_end) = find_matching_delim(toks, i + 1, "(", ")") {
                    let after_outer = toks.get(outer_end + 1).map(|t| t.text.as_str());
                    if !matches!(after_outer, Some("[") | Some(".") | Some("->")) {
                        let inner = &toks[i + 2..outer_end];
                        if let Some((cast_end, width, _)) = parse_ptr_cast(inner, 0) {
                            let rest = &inner[cast_end + 1..];
                            if let Some((op_idx, op)) = split_top_level_add_sub(rest) {
                                let base_raw = unwrap_outer_parens(&rest[..op_idx]);
                                let rhs_raw = &rest[op_idx + 1..];
                                let norm_base = if base_raw.len() == 1 {
                                    base_raw.to_vec()
                                } else {
                                    normalize_expr_tokens(base_raw, types, options)
                                };
                                if let Some(k) = parse_signed_const(rhs_raw) {
                                    let bytes = if op == "-" { -k } else { k } * (width as i128);
                                    out.extend(emit_mem_access(width, norm_base, OffsetExpr::ConstBytes(bytes)));
                                    i = outer_end + 1;
                                    continue;
                                } else if op == "+" {
                                    let norm_idx = normalize_expr_tokens(rhs_raw, types, options);
                                    out.extend(emit_mem_access(
                                        width,
                                        norm_base,
                                        OffsetExpr::ScaledExpr {
                                            op: "+",
                                            expr: norm_idx,
                                            elem_size: width,
                                        },
                                    ));
                                    i = outer_end + 1;
                                    continue;
                                }
                            } else {
                                // `*((T *)base)` with no offset
                                let base_clean = unwrap_outer_parens(rest);
                                if !base_clean.is_empty()
                                    && base_clean.iter().all(|t| t.kind == RawTokenKind::Identifier)
                                    && base_clean.len() == 1
                                {
                                    out.extend(emit_mem_access(
                                        width,
                                        base_clean.to_vec(),
                                        OffsetExpr::ConstBytes(0),
                                    ));
                                    i = outer_end + 1;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }

            // Pattern B: `*(T *)(inner)` or `*(T *)ident`
            if let Some((cast_end, width, _)) = parse_ptr_cast(toks, i + 1) {
                if toks.get(cast_end + 1).map(|t| t.text.as_str()) == Some("(") {
                    if let Some(paren_end) = find_matching_delim(toks, cast_end + 1, "(", ")") {
                        let after_paren = toks.get(paren_end + 1).map(|t| t.text.as_str());
                        if !matches!(after_paren, Some("[") | Some(".") | Some("->")) {
                            let inner = &toks[cast_end + 2..paren_end];
                            let norm_inner = normalize_expr_tokens(inner, types, options);
                            let norm_clean = unwrap_outer_parens(&norm_inner);
                            if norm_clean.len() == 1 && norm_clean[0].kind == RawTokenKind::Identifier {
                                out.extend(emit_mem_access(
                                    width,
                                    norm_clean.to_vec(),
                                    OffsetExpr::ConstBytes(0),
                                ));
                                i = paren_end + 1;
                                continue;
                            }
                            // Integer address base `+`/`-` constant byte offset, e.g. `__int64 a1 + 24`
                            if norm_clean.len() == 3
                                && norm_clean[0].kind == RawTokenKind::Identifier
                                && matches!(norm_clean[1].text.as_str(), "+" | "-")
                            {
                                if let Some(bytes) = parse_c_int(&norm_clean[2].text) {
                                    let signed_b = if norm_clean[1].text == "-" { -bytes } else { bytes };
                                    out.extend(emit_mem_access(
                                        width,
                                        vec![norm_clean[0].clone()],
                                        OffsetExpr::ConstBytes(signed_b),
                                    ));
                                    i = paren_end + 1;
                                    continue;
                                }
                            }
                            out.push(make_ident(&format!("MEM_{width}B")));
                            out.push(make_punct("("));
                            out.extend_from_slice(norm_clean);
                            out.push(make_punct(")"));
                            i = paren_end + 1;
                            continue;
                        }
                    }
                } else if let Some(ident) = toks.get(cast_end + 1) {
                    let after_ident = toks.get(cast_end + 2).map(|t| t.text.as_str());
                    if ident.kind == RawTokenKind::Identifier
                        && !matches!(
                            after_ident,
                            Some("[") | Some(".") | Some("->") | Some("++") | Some("--")
                        )
                    {
                        out.extend(emit_mem_access(
                            width,
                            vec![ident.clone()],
                            OffsetExpr::ConstBytes(0),
                        ));
                        i = cast_end + 2;
                        continue;
                    }
                }
            }
        }

        out.push(toks[i].clone());
        i += 1;
    }

    out
}

/// Pass 3: Convert unary `&ident[idx]` into byte-scaled pointer arithmetic `ident + idx * SB`.
fn pass_addr_of_subscript(
    toks: &[RawToken],
    types: &VarTypeTable,
    options: &DiffOptions,
) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;

    while i < toks.len() {
        if toks[i].text == "&" && is_unary_op_pos(toks, i) {
            if let Some(ident) = toks.get(i + 1) {
                if ident.kind == RawTokenKind::Identifier
                    && toks.get(i + 2).map(|t| t.text.as_str()) == Some("[")
                {
                    if let Some(elem_size) = types.elem_size(&ident.text) {
                        if let Some(close_br) = find_matching_delim(toks, i + 2, "[", "]") {
                            let after_br = toks.get(close_br + 1).map(|t| t.text.as_str());
                            if !matches!(after_br, Some("[") | Some(".") | Some("->")) {
                                let idx_norm = normalize_expr_tokens(
                                    &toks[i + 3..close_br],
                                    types,
                                    options,
                                );
                                out.push(ident.clone());
                                if let Some(k) = parse_signed_const(&idx_norm) {
                                    let bytes = k * (elem_size as i128);
                                    if bytes > 0 {
                                        out.push(make_op("+"));
                                        out.push(make_num(&format!("{bytes}B")));
                                    } else if bytes < 0 {
                                        out.push(make_op("-"));
                                        out.push(make_num(&format!("{}B", -bytes)));
                                    }
                                } else {
                                    out.push(make_op("+"));
                                    if elem_size == 1 {
                                        out.extend(idx_norm);
                                    } else {
                                        let needs_parens = has_low_prec_op(&idx_norm);
                                        if needs_parens {
                                            out.push(make_punct("("));
                                        }
                                        out.extend(idx_norm);
                                        if needs_parens {
                                            out.push(make_punct(")"));
                                        }
                                        out.push(make_op("*"));
                                        out.push(make_num(&format!("{elem_size}B")));
                                    }
                                }
                                i = close_br + 1;
                                continue;
                            }
                        }
                    }
                }
            }
        }

        out.push(toks[i].clone());
        i += 1;
    }

    out
}

/// Pass 4: Convert typed array/pointer subscripts `ident[idx]` into `MEM_<S>B(ident + ...)`.
fn pass_array_subscript(
    toks: &[RawToken],
    types: &VarTypeTable,
    options: &DiffOptions,
) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;

    while i < toks.len() {
        let t = &toks[i];
        let prev_is_member_or_amp = (i > 0 && matches!(toks[i - 1].text.as_str(), "." | "->"))
            || (i > 0 && toks[i - 1].text == "&" && is_unary_op_pos(toks, i - 1));

        if !prev_is_member_or_amp
            && t.kind == RawTokenKind::Identifier
            && toks.get(i + 1).map(|x| x.text.as_str()) == Some("[")
        {
            if let Some(elem_size) = types.elem_size(&t.text) {
                if let Some(close_br) = find_matching_delim(toks, i + 1, "[", "]") {
                    let idx_norm = normalize_expr_tokens(&toks[i + 2..close_br], types, options);
                    if let Some(k) = parse_signed_const(&idx_norm) {
                        let bytes = k * (elem_size as i128);
                        out.extend(emit_mem_access(
                            elem_size,
                            vec![t.clone()],
                            OffsetExpr::ConstBytes(bytes),
                        ));
                    } else {
                        out.extend(emit_mem_access(
                            elem_size,
                            vec![t.clone()],
                            OffsetExpr::ScaledExpr {
                                op: "+",
                                expr: idx_norm,
                                elem_size,
                            },
                        ));
                    }
                    i = close_br + 1;
                    continue;
                }
            }
        }

        out.push(t.clone());
        i += 1;
    }

    out
}

/// Pass 5: Convert plain unary dereference `*ident` (with typed pointer `ident`) into `MEM_<S>B(ident + 0B)`.
fn pass_unary_deref(toks: &[RawToken], types: &VarTypeTable) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;

    while i < toks.len() {
        if toks[i].text == "*" && is_unary_op_pos(toks, i) {
            if let Some(ident) = toks.get(i + 1) {
                if ident.kind == RawTokenKind::Identifier {
                    if let Some(elem_size) = types.elem_size(&ident.text) {
                        let after = toks.get(i + 2).map(|t| t.text.as_str());
                        if !matches!(
                            after,
                            Some("[") | Some(".") | Some("->") | Some("++") | Some("--")
                        ) {
                            out.extend(emit_mem_access(
                                elem_size,
                                vec![ident.clone()],
                                OffsetExpr::ConstBytes(0),
                            ));
                            i += 2;
                            continue;
                        }
                    }
                }
            }
        }

        out.push(toks[i].clone());
        i += 1;
    }

    out
}

fn is_stmt_boundary_left(toks: &[RawToken], idx: usize) -> bool {
    idx == 0 || matches!(toks[idx - 1].text.as_str(), ";" | "{")
}

fn is_stmt_boundary_right(toks: &[RawToken], idx: usize) -> bool {
    toks.get(idx).map(|t| t.text.as_str()) == Some(";")
}

fn is_tight_arith_op(s: Option<&str>) -> bool {
    matches!(s, Some("*") | Some("/") | Some("%") | Some("<<") | Some(">>"))
}

/// Pass 6: Normalize pointer strides (`++p;`, `p += K`, `(T *)base + K`, `p + K`, `p = p + NB;`)
/// and erase redundant pointer view casts `(T *)` when not part of a dereference.
fn pass_pointer_arithmetic_and_casts(toks: &[RawToken], types: &VarTypeTable) -> Vec<RawToken> {
    let mut step1 = Vec::with_capacity(toks.len());
    let mut i = 0usize;

    while i < toks.len() {
        // Standalone `++p;` / `--p;`
        if matches!(toks[i].text.as_str(), "++" | "--")
            && is_stmt_boundary_left(toks, i)
            && toks.get(i + 1).map(|t| t.kind) == Some(RawTokenKind::Identifier)
            && is_stmt_boundary_right(toks, i + 2)
        {
            if let Some(elem_size) = types.elem_size(&toks[i + 1].text) {
                let op = if toks[i].text == "++" { "+=" } else { "-=" };
                step1.push(toks[i + 1].clone());
                step1.push(make_op(op));
                step1.push(make_num(&format!("{elem_size}B")));
                i += 2;
                continue;
            }
        }

        // Standalone `p++;` / `p--;`
        if toks[i].kind == RawTokenKind::Identifier
            && is_stmt_boundary_left(toks, i)
            && toks
                .get(i + 1)
                .map(|t| matches!(t.text.as_str(), "++" | "--"))
                .unwrap_or(false)
            && is_stmt_boundary_right(toks, i + 2)
        {
            if let Some(elem_size) = types.elem_size(&toks[i].text) {
                let op = if toks[i + 1].text == "++" { "+=" } else { "-=" };
                step1.push(toks[i].clone());
                step1.push(make_op(op));
                step1.push(make_num(&format!("{elem_size}B")));
                i += 2;
                continue;
            }
        }

        // `p += K` / `p -= K`
        if toks[i].kind == RawTokenKind::Identifier
            && toks
                .get(i + 1)
                .map(|t| matches!(t.text.as_str(), "+=" | "-="))
                .unwrap_or(false)
        {
            if let Some(elem_size) = types.elem_size(&toks[i].text) {
                if let Some(num_tok) = toks.get(i + 2) {
                    if let Some(k) = parse_c_int(&num_tok.text) {
                        if !is_tight_arith_op(toks.get(i + 3).map(|t| t.text.as_str())) {
                            step1.push(toks[i].clone());
                            step1.push(toks[i + 1].clone());
                            step1.push(make_num(&format!("{}B", k * (elem_size as i128))));
                            i += 3;
                            continue;
                        }
                    }
                }
            }
        }

        // Casted pointer arithmetic `(T *)base +/- K` or `(char *)base + idx` (not preceded by unary `*`)
        let preceded_by_star = i > 0 && toks[i - 1].text == "*" && is_unary_op_pos(toks, i - 1);
        if !preceded_by_star && toks[i].text == "(" {
            if let Some((cast_end, width, _)) = parse_ptr_cast(toks, i) {
                if let Some(base_tok) = toks.get(cast_end + 1) {
                    if base_tok.kind == RawTokenKind::Identifier {
                        if let Some(op_tok) = toks.get(cast_end + 2) {
                            if matches!(op_tok.text.as_str(), "+" | "-") {
                                if let Some(rhs_tok) = toks.get(cast_end + 3) {
                                    if let Some(k) = parse_c_int(&rhs_tok.text) {
                                        if !is_tight_arith_op(
                                            toks.get(cast_end + 4).map(|t| t.text.as_str()),
                                        ) {
                                            let bytes = k * (width as i128);
                                            step1.push(base_tok.clone());
                                            if bytes != 0 {
                                                step1.push(op_tok.clone());
                                                step1.push(make_num(&format!("{bytes}B")));
                                            }
                                            i = cast_end + 4;
                                            continue;
                                        }
                                    } else if op_tok.text == "+" && width == 1 {
                                        step1.push(base_tok.clone());
                                        step1.push(op_tok.clone());
                                        i = cast_end + 3;
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Uncast typed pointer arithmetic `p +/- K`
        let prev_blocks_ptr_add = i > 0
            && matches!(
                toks[i - 1].text.as_str(),
                "." | "->" | "++" | "--" | "*" | "/" | "%" | "+" | "-"
            )
            || (i > 0 && toks[i - 1].text == "&" && is_unary_op_pos(toks, i - 1));
        if !prev_blocks_ptr_add && toks[i].kind == RawTokenKind::Identifier {
            if let Some(elem_size) = types.elem_size(&toks[i].text) {
                if let Some(op_tok) = toks.get(i + 1) {
                    if matches!(op_tok.text.as_str(), "+" | "-") {
                        if let Some(rhs_tok) = toks.get(i + 2) {
                            if let Some(k) = parse_c_int(&rhs_tok.text) {
                                let after_rhs = toks.get(i + 3).map(|t| t.text.as_str());
                                if !is_tight_arith_op(after_rhs) && after_rhs != Some("&") {
                                    let bytes = k * (elem_size as i128);
                                    step1.push(toks[i].clone());
                                    if bytes != 0 {
                                        step1.push(op_tok.clone());
                                        step1.push(make_num(&format!("{bytes}B")));
                                    }
                                    i += 3;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
        }

        step1.push(toks[i].clone());
        i += 1;
    }

    // Pass 7a: Erase remaining scalar pointer view casts `(T *)` (not preceded by `*` or `sizeof`).
    let mut step2 = Vec::with_capacity(step1.len());
    let mut j = 0usize;
    while j < step1.len() {
        let prev_is_star_or_sizeof = (j > 0
            && step1[j - 1].text == "*"
            && is_unary_op_pos(&step1, j - 1))
            || (j > 0 && step1[j - 1].text == "sizeof");
        if !prev_is_star_or_sizeof && step1[j].text == "(" {
            if let Some((cast_end, _, _)) = parse_ptr_cast(&step1, j) {
                // Only erase cast when applied to an operand on its right.
                if let Some(next_tok) = step1.get(cast_end + 1) {
                    if matches!(
                        next_tok.kind,
                        RawTokenKind::Identifier | RawTokenKind::Number | RawTokenKind::StringLit
                    ) || next_tok.text == "("
                        || next_tok.text == "&"
                    {
                        j = cast_end + 1;
                        continue;
                    }
                }
            }
        }
        step2.push(step1[j].clone());
        j += 1;
    }

    // Pass 7b: Unwrap trivial parens around `(base +/- offset)` after `=` / `+=` / `-=` / `,` / `(` / cmp.
    let step3 = unwrap_trivial_ptr_expr_parens(&step2);

    // Pass 6b: Normalize `p = p + NB;` / `p = p - NB;` into `p += NB;` / `p -= NB;`.
    let mut step4 = Vec::with_capacity(step3.len());
    let mut k = 0usize;
    while k < step3.len() {
        if step3[k].kind == RawTokenKind::Identifier
            && types.elem_size(&step3[k].text).is_some()
            && step3.get(k + 1).map(|t| t.text.as_str()) == Some("=")
            && step3.get(k + 2).map(|t| t.text.as_str()) == Some(step3[k].text.as_str())
            && step3
                .get(k + 3)
                .map(|t| matches!(t.text.as_str(), "+" | "-"))
                .unwrap_or(false)
            && step3
                .get(k + 4)
                .map(|t| parse_unit_val(&t.text, 'B').is_some())
                .unwrap_or(false)
            && is_stmt_boundary_right(&step3, k + 5)
        {
            let op = if step3[k + 3].text == "+" { "+=" } else { "-=" };
            step4.push(step3[k].clone());
            step4.push(make_op(op));
            step4.push(step3[k + 4].clone());
            k += 5;
            continue;
        }
        step4.push(step3[k].clone());
        k += 1;
    }

    step4
}

fn unwrap_trivial_ptr_expr_parens(toks: &[RawToken]) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;
    while i < toks.len() {
        if toks[i].text == "(" {
            if let Some(close) = find_matching_delim(toks, i, "(", ")") {
                let left_ok = i == 0
                    || matches!(
                        toks[i - 1].text.as_str(),
                        "=" | "+=" | "-=" | "," | "(" | "return" | "==" | "!=" | "<" | "<=" | ">" | ">="
                    );
                let right_ok = toks.get(close + 1).map(|t| t.text.as_str()).map(|s| {
                    matches!(
                        s,
                        ";" | "," | ")" | "==" | "!=" | "<" | "<=" | ">" | ">=" | "&&" | "||"
                    )
                }).unwrap_or(true);
                let inner = &toks[i + 1..close];
                let is_simple_ptr_arith = inner.len() == 3
                    && inner[0].kind == RawTokenKind::Identifier
                    && matches!(inner[1].text.as_str(), "+" | "-")
                    && (inner[2].kind == RawTokenKind::Identifier
                        || parse_unit_val(&inner[2].text, 'B').is_some());
                let is_single_ident_or_mem = inner.len() == 1
                    && matches!(inner[0].kind, RawTokenKind::Identifier | RawTokenKind::Number);

                // Never unwrap `if ( x )` / `while ( x )`.
                let prev_kw = i > 0
                    && matches!(
                        toks[i - 1].text.as_str(),
                        "if" | "while" | "for" | "switch" | "sizeof"
                    );
                if !prev_kw && left_ok && right_ok && (is_simple_ptr_arith || is_single_ident_or_mem) {
                    out.extend_from_slice(inner);
                    i = close + 1;
                    continue;
                }
            }
        }
        out.push(toks[i].clone());
        i += 1;
    }
    out
}

fn pow2_shift_amount(tok: &RawToken) -> Option<u32> {
    if tok.kind != RawTokenKind::Number {
        return None;
    }
    let val = parse_c_int(&tok.text)?;
    if val >= 2 && val <= (1i128 << 31) && (val & (val - 1)) == 0 {
        Some(val.trailing_zeros())
    } else {
        None
    }
}

/// Pass 8: Normalize power-of-2 multiplication `2^k * expr` and `expr * 2^k` into `(expr << k)`.
fn pass_pow2_shift(toks: &[RawToken]) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;

    while i < toks.len() {
        // Case 1: `2^k * expr`
        if let Some(shift) = pow2_shift_amount(&toks[i]) {
            let left_ok = i == 0
                || !matches!(
                    toks[i - 1].text.as_str(),
                    "." | "->" | "*" | "/" | "%" | "<<" | ">>"
                );
            if left_ok && toks.get(i + 1).map(|t| t.text.as_str()) == Some("*") {
                if let Some((expr_end, expr_slice)) = parse_factor_span(toks, i + 2) {
                    out.push(make_punct("("));
                    out.extend_from_slice(expr_slice);
                    out.push(make_op("<<"));
                    out.push(make_num(&shift.to_string()));
                    out.push(make_punct(")"));
                    i = expr_end;
                    continue;
                }
            }
        }

        // Case 2: `expr * 2^k`
        let left_ok = i == 0 || !matches!(toks[i - 1].text.as_str(), "." | "->" | "*" | "/" | "%");
        if left_ok {
            if let Some((expr_end, expr_slice)) = parse_factor_span(toks, i) {
                if toks.get(expr_end).map(|t| t.text.as_str()) == Some("*") {
                    if let Some(num_tok) = toks.get(expr_end + 1) {
                        if let Some(shift) = pow2_shift_amount(num_tok) {
                            let right_ok = !matches!(
                                toks.get(expr_end + 2).map(|t| t.text.as_str()),
                                Some("[") | Some("*") | Some("/") | Some("%")
                            );
                            if right_ok {
                                out.push(make_punct("("));
                                out.extend_from_slice(expr_slice);
                                out.push(make_op("<<"));
                                out.push(make_num(&shift.to_string()));
                                out.push(make_punct(")"));
                                i = expr_end + 2;
                                continue;
                            }
                        }
                    }
                }
            }
        }

        out.push(toks[i].clone());
        i += 1;
    }

    out
}

fn parse_factor_span(toks: &[RawToken], start: usize) -> Option<(usize, &[RawToken])> {
    let t = toks.get(start)?;
    if t.kind == RawTokenKind::Identifier {
        let after = toks.get(start + 1).map(|x| x.text.as_str());
        if !matches!(
            after,
            Some("(") | Some("[") | Some(".") | Some("->") | Some("++") | Some("--")
        ) {
            return Some((start + 1, &toks[start..start + 1]));
        }
    } else if t.text == "(" {
        let close = find_matching_delim(toks, start, "(", ")")?;
        return Some((close + 1, &toks[start..=close]));
    }
    None
}

#[derive(Debug, Clone, PartialEq, Eq)]
struct MemRef {
    width: usize,
    base: String,
    byte_off: i128,
}

/// Match `MEM_<W>B(base + <off>B)` or `MEM_<W>B(base - <off>B)` starting at `start`.
/// Returns `(next_idx, MemRef)`.
fn parse_mem_ref(toks: &[RawToken], start: usize) -> Option<(usize, MemRef)> {
    let name = toks.get(start)?.text.as_str();
    let w_str = name.strip_prefix("MEM_")?.strip_suffix('B')?;
    let width = w_str.parse::<usize>().ok()?;
    if toks.get(start + 1).map(|t| t.text.as_str()) != Some("(") {
        return None;
    }
    let close = find_matching_delim(toks, start + 1, "(", ")")?;
    let inner = &toks[start + 2..close];
    if inner.len() != 3 || inner[0].kind != RawTokenKind::Identifier {
        return None;
    }
    let off = parse_unit_val(&inner[2].text, 'B')?;
    let byte_off = match inner[1].text.as_str() {
        "+" => off,
        "-" => -off,
        _ => return None,
    };
    Some((
        close + 1,
        MemRef {
            width,
            base: inner[0].text.clone(),
            byte_off,
        },
    ))
}

fn contiguous_mask_bits(mask: i128) -> Option<usize> {
    if mask <= 0 {
        return None;
    }
    let m = mask as u128;
    if (m & (m + 1)) == 0 {
        Some((128 - m.leading_zeros()) as usize)
    } else {
        None
    }
}

fn word_bit_mask(width_bytes: usize) -> Option<u128> {
    match width_bytes {
        1 => Some(0xFF),
        2 => Some(0xFFFF),
        4 => Some(0xFFFF_FFFF),
        8 => Some(u64::MAX as u128),
        _ => None,
    }
}

fn emit_bf_read(base: &str, bit_off: i128, bits: usize) -> Vec<RawToken> {
    vec![
        make_ident("BF"),
        make_punct("("),
        make_ident(base),
        make_punct(","),
        make_num(&format!("{bit_off}b")),
        make_punct(","),
        make_num(&format!("{bits}w")),
        make_punct(")"),
    ]
}

fn emit_bf_set(base: &str, bit_off: i128, bits: usize, val: &[RawToken]) -> Vec<RawToken> {
    let mut out = vec![
        make_ident("BF_SET"),
        make_punct("("),
        make_ident(base),
        make_punct(","),
        make_num(&format!("{bit_off}b")),
        make_punct(","),
        make_num(&format!("{bits}w")),
        make_punct(","),
    ];
    out.extend_from_slice(val);
    out.push(make_punct(")"));
    out
}

/// Match `(val_expr & field_mask) << shift` (with arbitrary redundant outer parens).
fn parse_shifted_field_insert(slice: &[RawToken]) -> Option<(Vec<RawToken>, i128, usize, usize)> {
    let inner = unwrap_outer_parens(slice);
    // Find top-level `<<`
    let mut depth = 0isize;
    let mut shl_pos = None;
    for (idx, t) in inner.iter().enumerate() {
        match t.text.as_str() {
            "(" | "[" => depth += 1,
            ")" | "]" => depth -= 1,
            "<<" if depth == 0 => {
                shl_pos = Some(idx);
            }
            _ => {}
        }
    }
    let shl_idx = shl_pos?;
    let shift_toks = &inner[shl_idx + 1..];
    if shift_toks.len() != 1 {
        return None;
    }
    let shift = parse_c_int(&shift_toks[0].text)? as usize;

    let masked = unwrap_outer_parens(&inner[..shl_idx]);
    // Find top-level `&` inside `val & field_mask`
    depth = 0;
    let mut amp_pos = None;
    for (idx, t) in masked.iter().enumerate() {
        match t.text.as_str() {
            "(" | "[" => depth += 1,
            ")" | "]" => depth -= 1,
            "&" if depth == 0 && !is_unary_op_pos(masked, idx) => {
                amp_pos = Some(idx);
            }
            _ => {}
        }
    }
    let amp_idx = amp_pos?;
    let val_toks = unwrap_outer_parens(&masked[..amp_idx]);
    let mask_toks = &masked[amp_idx + 1..];
    if val_toks.is_empty() || mask_toks.len() != 1 {
        return None;
    }
    let field_mask = parse_c_int(&mask_toks[0].text)?;
    let bits = contiguous_mask_bits(field_mask)?;
    Some((val_toks.to_vec(), field_mask, bits, shift))
}

/// Match `MEM_<W>B(...) & clear_mask` (with arbitrary outer parens).
fn parse_mem_clear(slice: &[RawToken]) -> Option<(MemRef, i128)> {
    let inner = unwrap_outer_parens(slice);
    let (mem_end, mem) = parse_mem_ref(inner, 0)?;
    if mem_end >= inner.len() || inner[mem_end].text != "&" {
        return None;
    }
    if mem_end + 2 != inner.len() {
        return None;
    }
    let clear_mask = parse_c_int(&inner[mem_end + 1].text)?;
    Some((mem, clear_mask))
}

/// Try matching bitfield RMW statement at `i`:
/// `MEM_WB(...) = (<clear> | <insert>)` (or `(<insert> | <clear>)`).
fn try_match_bf_rmw(toks: &[RawToken], i: usize) -> Option<(usize, Vec<RawToken>)> {
    if !is_stmt_boundary_left(toks, i) {
        return None;
    }
    let (lhs_end, lhs_mem) = parse_mem_ref(toks, i)?;
    if lhs_mem.byte_off < 0 || toks.get(lhs_end).map(|t| t.text.as_str()) != Some("=") {
        return None;
    }
    let word_mask = word_bit_mask(lhs_mem.width)?;
    let rhs_start = lhs_end + 1;
    let stmt_end = toks[rhs_start..]
        .iter()
        .position(|t| t.text == ";")
        .map(|off| rhs_start + off)?;
    let rhs = &toks[rhs_start..stmt_end];

    // Split top-level `|` inside RHS
    let mut depth = 0isize;
    let mut or_positions = Vec::new();
    for (idx, t) in rhs.iter().enumerate() {
        match t.text.as_str() {
            "(" | "[" => depth += 1,
            ")" | "]" => depth -= 1,
            "|" if depth == 0 => or_positions.push(idx),
            _ => {}
        }
    }
    if or_positions.len() != 1 {
        return None;
    }
    let or_idx = or_positions[0];
    let part_a = &rhs[..or_idx];
    let part_b = &rhs[or_idx + 1..];

    let (clear_mem, clear_mask, insert_slice) = if let Some((m, cm)) = parse_mem_clear(part_a) {
        (m, cm, part_b)
    } else if let Some((m, cm)) = parse_mem_clear(part_b) {
        (m, cm, part_a)
    } else {
        return None;
    };

    if clear_mem != lhs_mem {
        return None;
    }

    let width_bits = lhs_mem.width * 8;
    let masked_clear = (clear_mask as u128) & word_mask;

    // Variant 1: `((val & field_mask) << shift)`
    if let Some((val_toks, field_mask, bits, shift)) = parse_shifted_field_insert(insert_slice) {
        if shift + bits <= width_bits {
            let expected_clear = word_mask ^ ((field_mask as u128) << shift);
            if masked_clear == expected_clear {
                let total_bit_off = lhs_mem.byte_off * 8 + (shift as i128);
                return Some((stmt_end, emit_bf_set(&lhs_mem.base, total_bit_off, bits, &val_toks)));
            }
        }
    }

    // Variant 2: `shift == 0` constant field write, e.g. `MEM_1B(a1 + 31B) & 0x80 | 0xB`
    let insert_clean = unwrap_outer_parens(insert_slice);
    if insert_clean.len() == 1 {
        if let Some(const_val) = parse_c_int(&insert_clean[0].text) {
            if const_val >= 0 {
                let cleared_bits = word_mask ^ masked_clear;
                if let Some(bits) = contiguous_mask_bits(cleared_bits as i128) {
                    if bits < width_bits && (const_val as u128) <= cleared_bits {
                        let total_bit_off = lhs_mem.byte_off * 8;
                        return Some((
                            stmt_end,
                            emit_bf_set(&lhs_mem.base, total_bit_off, bits, insert_clean),
                        ));
                    }
                }
            }
        }
    }

    None
}

/// Pass 9: Fold `MEM_<W>B(...)` bitfield reads and read-modify-writes into `BF(...)` / `BF_SET(...)`.
fn pass_bitfield_fold(toks: &[RawToken]) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;

    while i < toks.len() {
        // 1. Check bitfield read-modify-write statement first.
        if let Some((stmt_end, replacement)) = try_match_bf_rmw(toks, i) {
            out.extend(replacement);
            i = stmt_end;
            continue;
        }

        // 2. Check parenthesized shifted bitfield read: `(MEM_WB(...) >> shift) & mask`
        if toks[i].text == "(" {
            if let Some(close) = find_matching_delim(toks, i, "(", ")") {
                if toks.get(close + 1).map(|t| t.text.as_str()) == Some("&") {
                    if let Some(mask_tok) = toks.get(close + 2) {
                        if let Some(mask_val) = parse_c_int(&mask_tok.text) {
                            if let Some(bits) = contiguous_mask_bits(mask_val) {
                                let inner = unwrap_outer_parens(&toks[i + 1..close]);
                                if let Some((mem_end, mem)) = parse_mem_ref(inner, 0) {
                                    if mem.byte_off >= 0
                                        && mem_end + 2 == inner.len()
                                        && inner[mem_end].text == ">>"
                                    {
                                        if let Some(shift_val) = parse_c_int(&inner[mem_end + 1].text)
                                        {
                                            if shift_val >= 0
                                                && (shift_val as usize) + bits <= mem.width * 8
                                            {
                                                let bit_off = mem.byte_off * 8 + shift_val;
                                                out.extend(emit_bf_read(&mem.base, bit_off, bits));
                                                i = close + 3;
                                                continue;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // 3. Check unparenthesized bitfield read:
        //    `MEM_WB(...) >> shift & mask` OR `MEM_WB(...) & mask` (shift == 0)
        if let Some((mem_end, mem)) = parse_mem_ref(toks, i) {
            if mem.byte_off >= 0 {
                // `MEM >> shift & mask`
                if toks.get(mem_end).map(|t| t.text.as_str()) == Some(">>")
                    && toks.get(mem_end + 2).map(|t| t.text.as_str()) == Some("&")
                {
                    if let (Some(shift_tok), Some(mask_tok)) =
                        (toks.get(mem_end + 1), toks.get(mem_end + 3))
                    {
                        if let (Some(shift_val), Some(mask_val)) =
                            (parse_c_int(&shift_tok.text), parse_c_int(&mask_tok.text))
                        {
                            if let Some(bits) = contiguous_mask_bits(mask_val) {
                                if shift_val >= 0 && (shift_val as usize) + bits <= mem.width * 8 {
                                    let bit_off = mem.byte_off * 8 + shift_val;
                                    out.extend(emit_bf_read(&mem.base, bit_off, bits));
                                    i = mem_end + 4;
                                    continue;
                                }
                            }
                        }
                    }
                }

                // `MEM & mask` (shift = 0)
                if toks.get(mem_end).map(|t| t.text.as_str()) == Some("&")
                    && !matches!(toks.get(i.saturating_sub(1)).map(|t| t.text.as_str()), Some(">>") | Some("<<"))
                {
                    if let Some(mask_tok) = toks.get(mem_end + 1) {
                        if let Some(mask_val) = parse_c_int(&mask_tok.text) {
                            if let Some(bits) = contiguous_mask_bits(mask_val) {
                                let after_mask = toks.get(mem_end + 2).map(|t| t.text.as_str());
                                if bits < mem.width * 8 && !matches!(after_mask, Some("<<") | Some(">>")) {
                                    let bit_off = mem.byte_off * 8;
                                    out.extend(emit_bf_read(&mem.base, bit_off, bits));
                                    i = mem_end + 2;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
        }

        out.push(toks[i].clone());
        i += 1;
    }

    // Strip redundant parens immediately wrapping a single `BF(...)` or `BF_SET(...)` call,
    // e.g. `if ( (BF(a1, 10b, 7w)) != 0x3F )` -> `if ( BF(a1, 10b, 7w) != 0x3F )`.
    unwrap_single_bf_call_parens(&out)
}

fn unwrap_single_bf_call_parens(toks: &[RawToken]) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(toks.len());
    let mut i = 0usize;
    while i < toks.len() {
        if toks[i].text == "(" {
            if let Some(close) = find_matching_delim(toks, i, "(", ")") {
                let inner = &toks[i + 1..close];
                let prev_ok = i == 0
                    || matches!(
                        toks[i - 1].text.as_str(),
                        "(" | "=" | "==" | "!=" | "<" | "<=" | ">" | ">=" | "&&" | "||" | "," | "+" | "-"
                    );
                let next_ok = toks
                    .get(close + 1)
                    .map(|t| {
                        matches!(
                            t.text.as_str(),
                            ")" | ";" | "," | "==" | "!=" | "<" | "<=" | ">" | ">=" | "&&" | "||" | "+" | "-"
                        )
                    })
                    .unwrap_or(true);
                if prev_ok && next_ok && is_single_bf_call(inner) {
                    out.extend_from_slice(inner);
                    i = close + 1;
                    continue;
                }
            }
        }
        out.push(toks[i].clone());
        i += 1;
    }
    out
}

fn is_single_bf_call(toks: &[RawToken]) -> bool {
    if toks.len() < 4 || !matches!(toks[0].text.as_str(), "BF" | "BF_SET") || toks[1].text != "(" {
        return false;
    }
    find_matching_delim(toks, 1, "(", ")") == Some(toks.len() - 1)
}

fn normalize_expr_tokens(toks: &[RawToken], types: &VarTypeTable, options: &DiffOptions) -> Vec<RawToken> {
    run_code_fixpoint(toks.to_vec(), types, options)
}

fn run_code_fixpoint(
    mut sig: Vec<RawToken>,
    types: &VarTypeTable,
    options: &DiffOptions,
) -> Vec<RawToken> {
    for _ in 0..6 {
        let before = sig.clone();
        sig = normalize_scalar_ptr_types(&sig, false);
        sig = pass_cast_derefs(&sig, types, options);
        sig = pass_addr_of_subscript(&sig, types, options);
        sig = pass_array_subscript(&sig, types, options);
        sig = pass_unary_deref(&sig, types);
        sig = pass_pointer_arithmetic_and_casts(&sig, types);
        sig = pass_pow2_shift(&sig);
        sig = pass_bitfield_fold(&sig);
        if sig == before {
            break;
        }
    }
    sig
}

fn needs_space(prev: &RawToken, curr: &RawToken, prev_prev: Option<&RawToken>) -> bool {
    if matches!(curr.text.as_str(), ";" | "," | "]" | "." | "->" | "[") {
        return false;
    }
    if matches!(prev.text.as_str(), "[" | "." | "->") {
        return false;
    }
    if prev.text == "(" || curr.text == ")" {
        return false;
    }
    // Keep spaces before `(` for keywords, return, or operators/assigns, not for function calls `foo(`.
    if curr.text == "(" {
        if prev.kind == RawTokenKind::Identifier {
            return matches!(
                prev.text.as_str(),
                "if" | "else" | "for" | "while" | "switch" | "return" | "sizeof" | "$PTR" | "$PTR2"
            );
        }
        return !matches!(prev.text.as_str(), "(" | "[" | "!" | "~" | "&" | "*");
    }
    // Unary `!`, `~`
    if matches!(prev.text.as_str(), "!" | "~") {
        return false;
    }
    // Unary `*` / `&` / `-` / `+`
    if matches!(prev.text.as_str(), "*" | "&" | "-" | "+") {
        let prev_is_unary = prev_prev
            .map(|pp| {
                matches!(
                    pp.text.as_str(),
                    "(" | "[" | "," | ";" | "=" | "+=" | "-=" | "==" | "!=" | "<" | "<=" | ">"
                        | ">=" | "&&" | "||" | "+" | "-" | "*" | "/" | "%" | "&" | "|" | "^"
                        | "<<" | ">>" | "!" | "~" | "?" | ":" | "return" | "case"
                )
            })
            .unwrap_or(true);
        if prev_is_unary {
            return false;
        }
    }
    // Postfix/prefix `++` / `--`
    if matches!(curr.text.as_str(), "++" | "--") && prev.kind == RawTokenKind::Identifier {
        return false;
    }
    if matches!(prev.text.as_str(), "++" | "--") && curr.kind == RawTokenKind::Identifier {
        return false;
    }
    true
}

fn format_with_canonical_ws(leading_ws: Option<RawToken>, sig: Vec<RawToken>) -> Vec<RawToken> {
    let mut out = Vec::with_capacity(sig.len() * 2 + 1);
    if let Some(ws) = leading_ws {
        out.push(ws);
    }
    for idx in 0..sig.len() {
        if idx > 0 {
            let prev_prev = if idx >= 2 { Some(&sig[idx - 2]) } else { None };
            if needs_space(&sig[idx - 1], &sig[idx], prev_prev) {
                out.push(RawToken {
                    kind: RawTokenKind::Whitespace,
                    text: " ".to_string(),
                });
            }
        }
        out.push(sig[idx].clone());
    }
    out
}

/// Normalize pointer strides, byte offsets, dereferences, and bitfield accesses
/// to minimum units (`1B` and `1bit`) and canonicalize pointer types to `$PTR`.
pub fn normalize_line_pointer_units(
    line: &ParsedLine,
    tokens: &[RawToken],
    types: &VarTypeTable,
    options: &DiffOptions,
) -> Vec<RawToken> {
    if !options.normalize_pointer_units {
        return tokens.to_vec();
    }

    let leading_ws = tokens
        .first()
        .filter(|t| t.kind == RawTokenKind::Whitespace)
        .cloned();

    let sig: Vec<RawToken> = tokens
        .iter()
        .filter(|t| {
            t.kind != RawTokenKind::Whitespace
                && !(options.ignore_comments && t.kind == RawTokenKind::Comment)
        })
        .cloned()
        .collect();

    if sig.is_empty() {
        return leading_ws.into_iter().collect();
    }

    // Preserve comments verbatim if `ignore_comments == false` so comment diffs stay visible.
    if !options.ignore_comments && sig.iter().any(|t| t.kind == RawTokenKind::Comment) {
        return tokens.to_vec();
    }

    let rewritten = if line.role == LineRole::Declaration || types.is_signature_line(line.line_no) {
        normalize_scalar_ptr_types(&sig, true)
    } else {
        run_code_fixpoint(sig, types, options)
    };

    format_with_canonical_ws(leading_ws, rewritten)
}
