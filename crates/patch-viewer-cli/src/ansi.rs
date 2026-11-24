use patch_viewer_core::{CfgReorderTag, ChangeKind, DiffResult, TokenHighlight};

const RESET: &str = "\x1b[0m";
const DIM: &str = "\x1b[2m";
const BOLD: &str = "\x1b[1m";
const RED: &str = "\x1b[31m";
const BG_RED: &str = "\x1b[48;5;52m";
const GREEN: &str = "\x1b[32m";
const BG_GREEN: &str = "\x1b[48;5;22m";
const YELLOW: &str = "\x1b[33m";
const BG_YELLOW: &str = "\x1b[48;5;58m";
const CYAN: &str = "\x1b[36m";
const DIM_CYAN_ITALIC: &str = "\x1b[2;3;36m";
const MAGENTA: &str = "\x1b[35m";
const GRAY: &str = "\x1b[90m";

pub fn format_cfg_tag(tag: &CfgReorderTag) -> String {
    match tag {
        CfgReorderTag::BranchInverted { .. } => "⇄ 分支反转".to_string(),
        CfgReorderTag::GuardFlattened { .. } => "⇄ Guard展开对齐".to_string(),
        CfgReorderTag::LabelMoved {
            label_old,
            label_new,
            from_line,
            to_line,
        } => format!("⇄ 标签块移动 {label_old}(L{from_line})↔{label_new}(L{to_line})"),
        CfgReorderTag::CaseReordered { case_key } => format!("⇄ Case重排({case_key})"),
        CfgReorderTag::DeclarationBlock => "📦 声明区".to_string(),
    }
}

fn render_tokens_ansi(
    tokens: &[patch_viewer_core::TokenSpan],
    use_normalized: bool,
    dim_row: bool,
) -> String {
    if use_normalized {
        let mut s = String::new();
        for t in tokens {
            if let Some(norm) = &t.normalized {
                s.push_str(&format!("{CYAN}{norm}{RESET}"));
            } else if t.highlight == TokenHighlight::NoiseChange {
                // Skip stripped comments in normalized mode
                if t.text.starts_with("//") || t.text.starts_with("/*") {
                    continue;
                }
                s.push_str(&t.text);
            } else {
                s.push_str(&t.text);
            }
        }
        return s;
    }

    let mut out = String::new();
    for t in tokens {
        match t.highlight {
            TokenHighlight::None => {
                if dim_row {
                    out.push_str(&format!("{GRAY}{}{RESET}", t.text));
                } else {
                    out.push_str(&t.text);
                }
            }
            TokenHighlight::NoiseChange => {
                out.push_str(&format!("{GRAY}\x1b[4m{}{RESET}", t.text));
            }
            TokenHighlight::SemanticAdd => {
                out.push_str(&format!("{BG_GREEN}{GREEN}{}{RESET}", t.text));
            }
            TokenHighlight::SemanticDelete => {
                out.push_str(&format!("{BG_RED}{RED}{}{RESET}", t.text));
            }
            TokenHighlight::SemanticModify => {
                out.push_str(&format!("{BG_YELLOW}{YELLOW}{}{RESET}", t.text));
            }
            TokenHighlight::Placeholder => {
                out.push_str(&format!("{DIM_CYAN_ITALIC}{}{RESET}", t.text));
            }
        }
    }
    out
}

fn truncate_pad(raw: &str, width: usize) -> String {
    let chars: Vec<char> = raw.chars().collect();
    if chars.len() > width {
        let mut s: String = chars[..width.saturating_sub(1)].iter().collect();
        s.push('…');
        s
    } else {
        let pad = width - chars.len();
        format!("{raw}{}", " ".repeat(pad))
    }
}

pub fn print_ansi_diff(
    res: &DiffResult,
    old_label: &str,
    new_label: &str,
    unified: bool,
    show_normalized: bool,
    show_mappings: bool,
) {
    let s = &res.summary;
    println!("{BOLD}{CYAN}=== IDA 反编译伪代码补丁对比 ==={RESET}");
    println!("  旧版: {BOLD}{old_label}{RESET}  |  新版: {BOLD}{new_label}{RESET}");
    println!(
        "  {GREEN}+{} 新增{RESET}  {RED}-{} 删除{RESET}  {YELLOW}~{} 修改{RESET}  |  {GRAY}已过滤噪音: {}{RESET}  |  {MAGENTA}控制流重排对齐: {}{RESET}",
        s.semantic_added_rows,
        s.semantic_removed_rows,
        s.semantic_modified_rows,
        s.noise_filtered_rows,
        s.cfg_reorders_aligned,
    );
    println!();

    if show_mappings && (!s.variable_mappings.is_empty() || !s.symbol_mappings.is_empty()) {
        println!("{BOLD}规范化变量与符号映射表:{RESET}");
        for (id, o, n) in s.variable_mappings.iter().chain(s.symbol_mappings.iter()) {
            println!("  {CYAN}{id:<8}{RESET} : {o:<18} ↔  {n}");
        }
        println!();
    }

    if unified {
        for r in &res.rows {
            if res.options.hide_noise_lines && r.kind == ChangeKind::NoiseOnly {
                continue;
            }
            let tag_str = r
                .cfg_tag
                .as_ref()
                .map(|t| format!(" {MAGENTA}[{}]{RESET}", format_cfg_tag(t)))
                .unwrap_or_default();
            match r.kind {
                ChangeKind::Unchanged => {
                    if let Some(l) = &r.new_line {
                        println!(
                            "{GRAY}{:>4} {:>4}  {}{RESET}{tag_str}",
                            r.old_line.as_ref().map(|x| x.line_no).unwrap_or(0),
                            l.line_no,
                            if show_normalized { &l.normalized_text } else { &l.raw_text }
                        );
                    }
                }
                ChangeKind::NoiseOnly => {
                    if let (Some(o), Some(n)) = (&r.old_line, &r.new_line) {
                        println!(
                            "{GRAY}{:>4} {:>4} ≈ {}{RESET}{tag_str}",
                            o.line_no,
                            n.line_no,
                            render_tokens_ansi(&n.tokens, show_normalized, true),
                        );
                    }
                }
                ChangeKind::Added => {
                    if let Some(n) = &r.new_line {
                        println!(
                            "{GREEN}   - {:>4} + {}{RESET}{tag_str}",
                            n.line_no,
                            render_tokens_ansi(&n.tokens, show_normalized, false),
                        );
                    }
                }
                ChangeKind::Removed => {
                    if let Some(o) = &r.old_line {
                        println!(
                            "{RED}{:>4}    - - {}{RESET}{tag_str}",
                            o.line_no,
                            render_tokens_ansi(&o.tokens, show_normalized, false),
                        );
                    }
                }
                ChangeKind::Modified => {
                    if let Some(o) = &r.old_line {
                        println!(
                            "{RED}{:>4}    ~ - {}{RESET}{tag_str}",
                            o.line_no,
                            render_tokens_ansi(&o.tokens, show_normalized, false),
                        );
                    }
                    if let Some(n) = &r.new_line {
                        println!(
                            "{GREEN}   ~ {:>4} + {}{RESET}{tag_str}",
                            n.line_no,
                            render_tokens_ansi(&n.tokens, show_normalized, false),
                        );
                    }
                }
            }
        }
        return;
    }

    // Side-by-side output
    let col_w = 56usize;
    println!(
        "{BOLD}{:<4} {:<51} │ {:<4} {:<51} │ 状态 / 控制流对齐{RESET}",
        "旧行", "旧版伪代码", "新行", "新版伪代码"
    );
    println!("{}", "─".repeat(col_w * 2 + 34));

    for r in &res.rows {
        if res.options.hide_noise_lines && r.kind == ChangeKind::NoiseOnly {
            continue;
        }
        let o_num = r
            .old_line
            .as_ref()
            .map(|l| {
                if l.is_placeholder {
                    "   ·".to_string()
                } else {
                    format!("{:>4}", l.line_no)
                }
            })
            .unwrap_or_else(|| "    ".to_string());
        let n_num = r
            .new_line
            .as_ref()
            .map(|l| {
                if l.is_placeholder {
                    "   ·".to_string()
                } else {
                    format!("{:>4}", l.line_no)
                }
            })
            .unwrap_or_else(|| "    ".to_string());

        let o_is_ph = r.old_line.as_ref().map(|l| l.is_placeholder).unwrap_or(false);
        let n_is_ph = r.new_line.as_ref().map(|l| l.is_placeholder).unwrap_or(false);

        let o_raw = r
            .old_line
            .as_ref()
            .map(|l| {
                if show_normalized {
                    l.normalized_text.as_str()
                } else {
                    l.raw_text.as_str()
                }
            })
            .unwrap_or("");
        let n_raw = r
            .new_line
            .as_ref()
            .map(|l| {
                if show_normalized {
                    l.normalized_text.as_str()
                } else {
                    l.raw_text.as_str()
                }
            })
            .unwrap_or("");

        let o_pad = truncate_pad(o_raw, col_w);
        let n_pad = truncate_pad(n_raw, col_w);

        let (o_styled, n_styled, status) = match r.kind {
            ChangeKind::Unchanged => (
                format!("{DIM}{o_pad}{RESET}"),
                format!("{DIM}{n_pad}{RESET}"),
                format!("{GRAY}={RESET}"),
            ),
            ChangeKind::NoiseOnly => (
                format!("{GRAY}{o_pad}{RESET}"),
                format!("{GRAY}{n_pad}{RESET}"),
                format!("{GRAY}≈ 仅噪音{RESET}"),
            ),
            ChangeKind::Modified => (
                format!("{YELLOW}{o_pad}{RESET}"),
                format!("{YELLOW}{n_pad}{RESET}"),
                format!("{YELLOW}{BOLD}~ 修改{RESET}"),
            ),
            ChangeKind::Added => (
                if o_is_ph {
                    format!("{DIM_CYAN_ITALIC}{o_pad}{RESET}")
                } else {
                    format!("{GRAY}{o_pad}{RESET}")
                },
                format!("{GREEN}{n_pad}{RESET}"),
                format!("{GREEN}{BOLD}+ 新增{RESET}"),
            ),
            ChangeKind::Removed => (
                format!("{RED}{o_pad}{RESET}"),
                if n_is_ph {
                    format!("{DIM_CYAN_ITALIC}{n_pad}{RESET}")
                } else {
                    format!("{GRAY}{n_pad}{RESET}")
                },
                format!("{RED}{BOLD}- 删除{RESET}"),
            ),
        };

        let tag_str = r
            .cfg_tag
            .as_ref()
            .map(|t| format!(" {MAGENTA}{}{RESET}", format_cfg_tag(t)))
            .unwrap_or_default();

        println!("{GRAY}{o_num}{RESET} {o_styled} │ {GRAY}{n_num}{RESET} {n_styled} │ {status}{tag_str}");
    }
}
