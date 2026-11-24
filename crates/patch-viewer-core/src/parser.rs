use once_cell::sync::Lazy;
use regex::Regex;

/// Token category produced by the fault-tolerant IDA Hex-Rays C lexer.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RawTokenKind {
    Identifier,
    Number,
    StringLit,
    Operator,
    Punctuation,
    Whitespace,
    Comment,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RawToken {
    pub kind: RawTokenKind,
    pub text: String,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LineRole {
    Blank,
    CommentOnly,
    Declaration,
    Code,
}

/// Parsed single line of IDA pseudocode.
#[derive(Debug, Clone)]
pub struct ParsedLine {
    /// 1-based original line number.
    pub line_no: usize,
    pub raw_text: String,
    pub indent: usize,
    pub tokens: Vec<RawToken>,
    pub role: LineRole,
}

/// Structural AST representation of IDA pseudocode statements for CFG alignment.
#[derive(Debug, Clone)]
pub enum StmtNode {
    Blank {
        line_idx: usize,
    },
    Declaration {
        line_idx: usize,
    },
    Simple {
        line_idx: usize,
    },
    Block {
        open_brace_line: Option<usize>,
        body: Vec<StmtNode>,
        close_brace_line: Option<usize>,
    },
    If {
        header_line: usize,
        cond_raw: String,
        then_open_brace: Option<usize>,
        then_body: Vec<StmtNode>,
        then_close_brace: Option<usize>,
        else_line: Option<usize>,
        else_open_brace: Option<usize>,
        else_body: Vec<StmtNode>,
        else_close_brace: Option<usize>,
    },
    Switch {
        header_line: usize,
        expr_raw: String,
        open_brace_line: Option<usize>,
        cases: Vec<CaseNode>,
        close_brace_line: Option<usize>,
    },
    LabelBlock {
        label_line: usize,
        label_name: String,
        body: Vec<StmtNode>,
    },
}

#[derive(Debug, Clone)]
pub struct CaseNode {
    pub label_line: usize,
    pub case_key: String,
    pub body: Vec<StmtNode>,
}

static RE_LABEL_LINE: Lazy<Regex> =
    Lazy::new(|| Regex::new(r"^([A-Za-z_][A-Za-z0-9_]*)\s*:\s*$").unwrap());

/// Lex a single line of IDA Hex-Rays C pseudocode into raw tokens.
/// Updates `in_block_comment` across lines.
pub fn lex_line(line: &str, in_block_comment: &mut bool) -> Vec<RawToken> {
    let mut tokens = Vec::new();
    let chars: Vec<char> = line.chars().collect();
    let n = chars.len();
    let mut i = 0;

    while i < n {
        if *in_block_comment {
            let start = i;
            while i < n {
                if i + 1 < n && chars[i] == '*' && chars[i + 1] == '/' {
                    i += 2;
                    *in_block_comment = false;
                    break;
                }
                i += 1;
            }
            tokens.push(RawToken {
                kind: RawTokenKind::Comment,
                text: chars[start..i].iter().collect(),
            });
            continue;
        }

        let ch = chars[i];

        // Whitespace
        if ch.is_whitespace() {
            let start = i;
            while i < n && chars[i].is_whitespace() {
                i += 1;
            }
            tokens.push(RawToken {
                kind: RawTokenKind::Whitespace,
                text: chars[start..i].iter().collect(),
            });
            continue;
        }

        // Line comment //
        if ch == '/' && i + 1 < n && chars[i + 1] == '/' {
            let text: String = chars[i..n].iter().collect();
            tokens.push(RawToken {
                kind: RawTokenKind::Comment,
                text,
            });
            break;
        }

        // Block comment /* ... */
        if ch == '/' && i + 1 < n && chars[i + 1] == '*' {
            let start = i;
            i += 2;
            *in_block_comment = true;
            while i < n {
                if i + 1 < n && chars[i] == '*' && chars[i + 1] == '/' {
                    i += 2;
                    *in_block_comment = false;
                    break;
                }
                i += 1;
            }
            tokens.push(RawToken {
                kind: RawTokenKind::Comment,
                text: chars[start..i].iter().collect(),
            });
            continue;
        }

        // String or char literal
        if ch == '"' || ch == '\'' {
            let quote = ch;
            let start = i;
            i += 1;
            while i < n {
                if chars[i] == '\\' && i + 1 < n {
                    i += 2;
                    continue;
                }
                if chars[i] == quote {
                    i += 1;
                    break;
                }
                i += 1;
            }
            tokens.push(RawToken {
                kind: RawTokenKind::StringLit,
                text: chars[start..i].iter().collect(),
            });
            continue;
        }

        // Identifier (supports IDA `@<rax>` suffix separately as operator/ident)
        if ch.is_ascii_alphabetic() || ch == '_' || ch == '$' {
            let start = i;
            i += 1;
            while i < n && (chars[i].is_ascii_alphanumeric() || chars[i] == '_') {
                i += 1;
            }
            tokens.push(RawToken {
                kind: RawTokenKind::Identifier,
                text: chars[start..i].iter().collect(),
            });
            continue;
        }

        // Numeric literal (hex, decimal, suffixes like LL, u, i64, ui64)
        if ch.is_ascii_digit() {
            let start = i;
            i += 1;
            while i < n
                && (chars[i].is_ascii_alphanumeric() || chars[i] == '.' || chars[i] == '_')
            {
                i += 1;
            }
            tokens.push(RawToken {
                kind: RawTokenKind::Number,
                text: chars[start..i].iter().collect(),
            });
            continue;
        }

        // Punctuation vs Operators
        if matches!(ch, '{' | '}' | '(' | ')' | '[' | ']' | ';' | ',' | ':' | '?') {
            tokens.push(RawToken {
                kind: RawTokenKind::Punctuation,
                text: ch.to_string(),
            });
            i += 1;
            continue;
        }

        // Multi-char operators
        let two: String = if i + 1 < n {
            chars[i..i + 2].iter().collect()
        } else {
            String::new()
        };
        let three: String = if i + 2 < n {
            chars[i..i + 3].iter().collect()
        } else {
            String::new()
        };
        if matches!(three.as_str(), "<<=" | ">>=") {
            tokens.push(RawToken {
                kind: RawTokenKind::Operator,
                text: three,
            });
            i += 3;
            continue;
        }
        if matches!(
            two.as_str(),
            "==" | "!="
                | "<="
                | ">="
                | "&&"
                | "||"
                | "<<"
                | ">>"
                | "->"
                | "++"
                | "--"
                | "+="
                | "-="
                | "*="
                | "/="
                | "%="
                | "&="
                | "|="
                | "^="
                | "::"
        ) {
            tokens.push(RawToken {
                kind: RawTokenKind::Operator,
                text: two,
            });
            i += 2;
            continue;
        }

        tokens.push(RawToken {
            kind: RawTokenKind::Operator,
            text: ch.to_string(),
        });
        i += 1;
    }

    tokens
}

/// Extract non-whitespace, non-comment code text of a line.
pub fn code_only_text(tokens: &[RawToken]) -> String {
    let mut out = String::new();
    let mut prev_ws = true;
    for t in tokens {
        match t.kind {
            RawTokenKind::Comment => {}
            RawTokenKind::Whitespace => {
                if !prev_ws {
                    out.push(' ');
                    prev_ws = true;
                }
            }
            _ => {
                out.push_str(&t.text);
                prev_ws = false;
            }
        }
    }
    out.trim().to_string()
}

fn is_control_keyword(s: &str) -> bool {
    matches!(
        s,
        "if" | "else"
            | "for"
            | "while"
            | "do"
            | "switch"
            | "case"
            | "default"
            | "return"
            | "goto"
            | "break"
            | "continue"
    )
}

/// Heuristic to detect IDA Hex-Rays local variable declarations at the top of a function body.
/// Examples:
///   `unsigned int v4; // edi`
///   `__int64 v7; // rbx`
///   `void *v8; // r14`
///   `char v10[32]; // [rsp+28h] [rbp-30h] BYREF`
fn looks_like_ida_declaration(tokens: &[RawToken]) -> bool {
    let meaningful: Vec<&RawToken> = tokens
        .iter()
        .filter(|t| !matches!(t.kind, RawTokenKind::Whitespace | RawTokenKind::Comment))
        .collect();
    if meaningful.is_empty() {
        return false;
    }
    if meaningful.last().map(|t| t.text.as_str()) != Some(";") {
        return false;
    }
    if let Some(first) = meaningful.first() {
        if is_control_keyword(&first.text) || first.text == "{" || first.text == "}" {
            return false;
        }
    }
    // Pure declarations in Hex-Rays have no assignment `=` and no function call `ident(`.
    let mut ident_count = 0usize;
    for (idx, tok) in meaningful.iter().enumerate() {
        if tok.text == "=" || tok.text == "+=" || tok.text == "-=" || tok.text == "++" || tok.text == "--" {
            return false;
        }
        if tok.kind == RawTokenKind::Identifier {
            ident_count += 1;
            if idx + 1 < meaningful.len() && meaningful[idx + 1].text == "(" {
                // Function call unless it's a function pointer `(*v5)` or `(__fastcall *v19)(...)`
                let is_direct_ptr = idx > 0 && meaningful[idx - 1].text == "*";
                let is_fn_ptr_decl = idx + 2 < meaningful.len()
                    && matches!(
                        meaningful[idx + 2].text.as_str(),
                        "*" | "__fastcall" | "__cdecl" | "__stdcall" | "__thiscall" | "__usercall" | "__userpurge"
                    );
                if !is_direct_ptr && !is_fn_ptr_decl {
                    return false;
                }
            }
        }
    }
    ident_count >= 2
}

/// Parse source text into `ParsedLine`s with `LineRole` classifications.
pub fn parse_lines(source: &str) -> Vec<ParsedLine> {
    let mut in_block_comment = false;
    let mut lines = Vec::new();
    let mut saw_func_open_brace = false;
    let mut in_top_decl_zone = false;
    let mut brace_depth = 0isize;

    for (idx, raw) in source.lines().enumerate() {
        let raw_clean = raw.trim_end_matches('\r').to_string();
        let indent = raw_clean.chars().take_while(|c| c.is_whitespace()).count();
        let tokens = lex_line(&raw_clean, &mut in_block_comment);

        let has_code = tokens
            .iter()
            .any(|t| !matches!(t.kind, RawTokenKind::Whitespace | RawTokenKind::Comment));
        let has_comment = tokens.iter().any(|t| t.kind == RawTokenKind::Comment);

        let mut role = if !has_code && !has_comment {
            LineRole::Blank
        } else if !has_code && has_comment {
            LineRole::CommentOnly
        } else {
            LineRole::Code
        };

        if role == LineRole::Code {
            let code_trim = code_only_text(&tokens);
            if !saw_func_open_brace {
                if code_trim == "{" || code_trim.ends_with('{') {
                    saw_func_open_brace = true;
                    in_top_decl_zone = true;
                }
            } else if in_top_decl_zone {
                if brace_depth == 1 && looks_like_ida_declaration(&tokens) {
                    role = LineRole::Declaration;
                } else {
                    in_top_decl_zone = false;
                }
            }

            for t in &tokens {
                if t.kind == RawTokenKind::Punctuation {
                    if t.text == "{" {
                        brace_depth += 1;
                    } else if t.text == "}" {
                        brace_depth -= 1;
                    }
                }
            }
        }

        lines.push(ParsedLine {
            line_no: idx + 1,
            raw_text: raw_clean,
            indent,
            tokens,
            role,
        });
    }

    lines
}

/// Extract parenthesized condition / switch expression from a header line like `if ( a && b )`.
fn extract_header_paren_expr(code: &str, keyword: &str) -> Option<(String, String)> {
    let trimmed = code.trim();
    let rest = if trimmed == keyword {
        return None;
    } else if let Some(after) = trimmed.strip_prefix(keyword) {
        let after_ws = after.trim_start();
        if !after.starts_with(char::is_whitespace) && !after.starts_with('(') {
            return None;
        }
        after_ws
    } else {
        return None;
    };

    if !rest.starts_with('(') {
        return None;
    }
    let chars: Vec<char> = rest.chars().collect();
    let mut depth = 0isize;
    let mut in_str: Option<char> = None;
    let mut end_idx = None;
    let mut i = 0;
    while i < chars.len() {
        let c = chars[i];
        if let Some(q) = in_str {
            if c == '\\' && i + 1 < chars.len() {
                i += 2;
                continue;
            }
            if c == q {
                in_str = None;
            }
        } else if c == '"' || c == '\'' {
            in_str = Some(c);
        } else if c == '(' {
            depth += 1;
        } else if c == ')' {
            depth -= 1;
            if depth == 0 {
                end_idx = Some(i);
                break;
            }
        }
        i += 1;
    }

    let close = end_idx?;
    let expr: String = chars[1..close].iter().collect();
    let trailing: String = chars[close + 1..].iter().collect();
    Some((expr.trim().to_string(), trailing.trim().to_string()))
}

struct AstParser<'a> {
    lines: &'a [ParsedLine],
    code_texts: Vec<String>,
    pos: usize,
}

impl<'a> AstParser<'a> {
    fn new(lines: &'a [ParsedLine]) -> Self {
        let code_texts = lines.iter().map(|l| code_only_text(&l.tokens)).collect();
        Self {
            lines,
            code_texts,
            pos: 0,
        }
    }

    fn peek_code(&self) -> &str {
        if self.pos < self.code_texts.len() {
            &self.code_texts[self.pos]
        } else {
            ""
        }
    }

    fn skip_blanks(&mut self, out: &mut Vec<StmtNode>) {
        while self.pos < self.lines.len()
            && matches!(self.lines[self.pos].role, LineRole::Blank | LineRole::CommentOnly)
        {
            out.push(StmtNode::Blank { line_idx: self.pos });
            self.pos += 1;
        }
    }

    fn parse_top_level(&mut self) -> Vec<StmtNode> {
        let mut nodes = Vec::new();
        while self.pos < self.lines.len() {
            if let Some(node) = self.parse_statement(false) {
                nodes.push(node);
            } else {
                // Unexpected closing brace at top level; consume as Simple to avoid infinite loop
                if self.pos < self.lines.len() {
                    let idx = self.pos;
                    self.pos += 1;
                    nodes.push(StmtNode::Simple { line_idx: idx });
                }
            }
        }
        nodes
    }

    fn parse_block_contents(&mut self, stop_on_case: bool) -> (Vec<StmtNode>, Option<usize>) {
        let mut body = Vec::new();
        while self.pos < self.lines.len() {
            let code = self.peek_code().to_string();
            if code == "}" {
                let close = self.pos;
                self.pos += 1;
                return (body, Some(close));
            }
            if stop_on_case && is_case_line(&code) {
                return (body, None);
            }
            if let Some(node) = self.parse_statement(stop_on_case) {
                body.push(node);
            } else {
                break;
            }
        }
        (body, None)
    }

    fn parse_single_or_braced_body(&mut self) -> (Option<usize>, Vec<StmtNode>, Option<usize>) {
        let mut leading_blanks = Vec::new();
        while self.pos < self.lines.len()
            && matches!(self.lines[self.pos].role, LineRole::Blank | LineRole::CommentOnly)
        {
            leading_blanks.push(StmtNode::Blank { line_idx: self.pos });
            self.pos += 1;
        }
        if self.pos < self.lines.len() && self.peek_code() == "{" {
            let open_line = self.pos;
            self.pos += 1;
            let (mut body, close_line) = self.parse_block_contents(false);
            if !leading_blanks.is_empty() {
                leading_blanks.extend(body);
                body = leading_blanks;
            }
            (Some(open_line), body, close_line)
        } else {
            let mut body = leading_blanks;
            if let Some(stmt) = self.parse_statement(false) {
                body.push(stmt);
            }
            (None, body, None)
        }
    }

    fn parse_statement(&mut self, stop_on_case: bool) -> Option<StmtNode> {
        if self.pos >= self.lines.len() {
            return None;
        }

        let role = self.lines[self.pos].role;
        if matches!(role, LineRole::Blank | LineRole::CommentOnly) {
            let idx = self.pos;
            self.pos += 1;
            return Some(StmtNode::Blank { line_idx: idx });
        }
        if role == LineRole::Declaration {
            let idx = self.pos;
            self.pos += 1;
            return Some(StmtNode::Declaration { line_idx: idx });
        }

        let code = self.peek_code().to_string();
        if code == "}" {
            return None;
        }
        if stop_on_case && is_case_line(&code) {
            return None;
        }

        // Braced block `{ ... }`
        if code == "{" {
            let open = self.pos;
            self.pos += 1;
            let (body, close) = self.parse_block_contents(false);
            return Some(StmtNode::Block {
                open_brace_line: Some(open),
                body,
                close_brace_line: close,
            });
        }

        // `if ( cond ) ...`
        if let Some((cond_raw, trailing)) = extract_header_paren_expr(&code, "if") {
            let header_line = self.pos;
            self.pos += 1;
            let (then_open_brace, then_body, then_close_brace) = if trailing == "{" {
                let (b, c) = self.parse_block_contents(false);
                (None, b, c)
            } else if !trailing.is_empty() {
                // Single-line `if (cond) stmt;`
                (None, Vec::new(), None)
            } else {
                self.parse_single_or_braced_body()
            };

            // Check for `else` (skipping blank/comment lines temporarily via lookahead)
            let saved_pos = self.pos;
            let mut between_blanks = Vec::new();
            self.skip_blanks(&mut between_blanks);
            let mut else_line = None;
            let mut else_open_brace = None;
            let mut else_body = Vec::new();
            let mut else_close_brace = None;

            if self.pos < self.lines.len() {
                let next_code = self.peek_code().to_string();
                if next_code == "else" || next_code.starts_with("else ") || next_code.starts_with("else{") {
                    else_line = Some(self.pos);
                    self.pos += 1;
                    if next_code == "else" {
                        let (eo, eb, ec) = self.parse_single_or_braced_body();
                        else_open_brace = eo;
                        else_body = eb;
                        else_close_brace = ec;
                    } else if next_code == "else {" || next_code == "else{" {
                        let (eb, ec) = self.parse_block_contents(false);
                        else_body = eb;
                        else_close_brace = ec;
                    } else if next_code.starts_with("else if") {
                        // Treat `else if (...)` as an If statement inside else_body
                        self.pos -= 1;
                        let else_if_line = self.pos;
                        // Synthesize parse by stripping leading `else ` logically
                        if let Some((c2, t2)) = extract_header_paren_expr(
                            next_code.strip_prefix("else").unwrap_or("").trim(),
                            "if",
                        ) {
                            self.pos += 1;
                            let (to2, tb2, tc2) = if t2 == "{" {
                                let (b, c) = self.parse_block_contents(false);
                                (None, b, c)
                            } else if !t2.is_empty() {
                                (None, Vec::new(), None)
                            } else {
                                self.parse_single_or_braced_body()
                            };
                            else_line = None; // Header itself is `else if`
                            else_body.push(StmtNode::If {
                                header_line: else_if_line,
                                cond_raw: c2,
                                then_open_brace: to2,
                                then_body: tb2,
                                then_close_brace: tc2,
                                else_line: None,
                                else_open_brace: None,
                                else_body: Vec::new(),
                                else_close_brace: None,
                            });
                        } else {
                            self.pos += 1;
                        }
                    }
                } else {
                    // Restore position if no else
                    self.pos = saved_pos;
                }
            } else {
                self.pos = saved_pos;
            }

            return Some(StmtNode::If {
                header_line,
                cond_raw,
                then_open_brace,
                then_body,
                then_close_brace,
                else_line,
                else_open_brace,
                else_body,
                else_close_brace,
            });
        }

        // `switch ( expr )`
        if let Some((expr_raw, trailing)) = extract_header_paren_expr(&code, "switch") {
            let header_line = self.pos;
            self.pos += 1;
            let mut open_brace_line = None;
            let mut close_brace_line = None;
            let mut cases = Vec::new();

            if trailing != "{" {
                while self.pos < self.lines.len()
                    && matches!(self.lines[self.pos].role, LineRole::Blank | LineRole::CommentOnly)
                {
                    self.pos += 1;
                }
                if self.pos < self.lines.len() && self.peek_code() == "{" {
                    open_brace_line = Some(self.pos);
                    self.pos += 1;
                }
            }

            while self.pos < self.lines.len() {
                while self.pos < self.lines.len()
                    && matches!(self.lines[self.pos].role, LineRole::Blank | LineRole::CommentOnly)
                {
                    self.pos += 1;
                }
                if self.pos >= self.lines.len() {
                    break;
                }
                let c = self.peek_code().to_string();
                if c == "}" {
                    close_brace_line = Some(self.pos);
                    self.pos += 1;
                    break;
                }
                if is_case_line(&c) {
                    let label_line = self.pos;
                    let case_key = extract_case_key(&c);
                    self.pos += 1;
                    let (body, maybe_close) = self.parse_block_contents(true);
                    cases.push(CaseNode {
                        label_line,
                        case_key,
                        body,
                    });
                    if let Some(close) = maybe_close {
                        close_brace_line = Some(close);
                        break;
                    }
                } else {
                    // Fallback if switch body has unexpected lines before first case
                    let _ = self.parse_statement(true);
                }
            }

            return Some(StmtNode::Switch {
                header_line,
                expr_raw,
                open_brace_line,
                cases,
                close_brace_line,
            });
        }

        // Label block `loc_xxx:`
        if let Some(caps) = RE_LABEL_LINE.captures(&code) {
            let label_line = self.pos;
            let label_name = caps[1].to_string();
            self.pos += 1;
            let mut body = Vec::new();
            while self.pos < self.lines.len() {
                let nxt = self.peek_code().to_string();
                if nxt == "}" || RE_LABEL_LINE.is_match(&nxt) || (stop_on_case && is_case_line(&nxt)) {
                    break;
                }
                if matches!(self.lines[self.pos].role, LineRole::Blank | LineRole::CommentOnly) {
                    // Do not swallow trailing blank line after terminator
                    let mut look = self.pos;
                    while look < self.lines.len()
                        && matches!(self.lines[look].role, LineRole::Blank | LineRole::CommentOnly)
                    {
                        look += 1;
                    }
                    if look >= self.lines.len() || self.code_texts[look] == "}" || RE_LABEL_LINE.is_match(&self.code_texts[look]) {
                        break;
                    }
                }
                if let Some(stmt) = self.parse_statement(stop_on_case) {
                    let is_term = is_unconditional_terminator(&stmt, &self.code_texts);
                    body.push(stmt);
                    if is_term {
                        break;
                    }
                } else {
                    break;
                }
            }
            return Some(StmtNode::LabelBlock {
                label_line,
                label_name,
                body,
            });
        }

        // Function header `{ ... }` or simple statement
        let idx = self.pos;
        self.pos += 1;
        Some(StmtNode::Simple { line_idx: idx })
    }
}

fn is_case_line(code: &str) -> bool {
    let t = code.trim();
    (t.starts_with("case ") || t == "default:" || t.starts_with("default :")) && t.ends_with(':')
}

fn extract_case_key(code: &str) -> String {
    let t = code.trim().trim_end_matches(':').trim();
    if t.starts_with("default") {
        "default".to_string()
    } else {
        t.to_string()
    }
}

fn is_unconditional_terminator(stmt: &StmtNode, code_texts: &[String]) -> bool {
    match stmt {
        StmtNode::Simple { line_idx } => {
            let t = code_texts[*line_idx].trim();
            t.starts_with("return ") || t == "return;" || t.starts_with("goto ") || t == "break;"
        }
        _ => false,
    }
}

/// Build hierarchical `StmtNode` AST over the parsed lines.
pub fn parse_ast(lines: &[ParsedLine]) -> Vec<StmtNode> {
    let mut parser = AstParser::new(lines);
    parser.parse_top_level()
}
