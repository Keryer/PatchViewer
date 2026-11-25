use std::io;

use anyhow::Result;
use crossterm::{
    event::{self, Event, KeyCode, KeyEventKind},
    execute,
    terminal::{disable_raw_mode, enable_raw_mode, EnterAlternateScreen, LeaveAlternateScreen},
};
use patch_viewer_core::{
    diff_pseudocode, AlignedRow, CfgReorderTag, ChangeKind, DiffOptions, DiffResult, LineSide,
    TokenHighlight,
};
use ratatui::{
    backend::CrosstermBackend,
    layout::{Constraint, Direction, Layout, Rect},
    style::{Color, Modifier, Style},
    text::{Line, Span},
    widgets::{Block, Borders, Clear, List, ListItem, Paragraph, Wrap},
    Terminal,
};

use crate::ansi::format_cfg_tag;

struct TuiState {
    old_src: String,
    new_src: String,
    old_label: String,
    new_label: String,
    options: DiffOptions,
    diff: DiffResult,
    scroll: usize,
    unified: bool,
    show_normalized: bool,
    show_mappings: bool,
    selected_semantic_idx: Option<usize>,
}

impl TuiState {
    fn new(
        old_src: String,
        new_src: String,
        old_label: String,
        new_label: String,
        options: DiffOptions,
        unified: bool,
    ) -> Self {
        let diff = diff_pseudocode(&old_src, &new_src, &options);
        Self {
            old_src,
            new_src,
            old_label,
            new_label,
            options,
            diff,
            scroll: 0,
            unified,
            show_normalized: false,
            show_mappings: false,
            selected_semantic_idx: None,
        }
    }

    fn recompute(&mut self) {
        self.diff = diff_pseudocode(&self.old_src, &self.new_src, &self.options);
        let vis = self.visible_rows();
        if self.scroll >= vis.len() {
            self.scroll = vis.len().saturating_sub(1);
        }
    }

    fn visible_rows(&self) -> Vec<&AlignedRow> {
        self.diff
            .rows
            .iter()
            .filter(|r| !(self.options.hide_noise_lines && r.kind == ChangeKind::NoiseOnly))
            .collect()
    }

    fn jump_semantic(&mut self, forward: bool) {
        let vis = self.visible_rows();
        let sem_positions: Vec<usize> = vis
            .iter()
            .enumerate()
            .filter(|(_, r)| {
                matches!(
                    r.kind,
                    ChangeKind::Added | ChangeKind::Removed | ChangeKind::Modified
                )
            })
            .map(|(i, _)| i)
            .collect();
        if sem_positions.is_empty() {
            return;
        }
        let target = if forward {
            sem_positions
                .iter()
                .copied()
                .find(|&pos| pos > self.scroll)
                .unwrap_or(sem_positions[0])
        } else {
            sem_positions
                .iter()
                .rev()
                .copied()
                .find(|&pos| pos < self.scroll)
                .unwrap_or(*sem_positions.last().unwrap())
        };
        self.scroll = target;
        self.selected_semantic_idx = Some(target);
    }
}

pub fn run_tui(
    old_src: String,
    new_src: String,
    old_label: String,
    new_label: String,
    options: DiffOptions,
    unified: bool,
) -> Result<()> {
    enable_raw_mode()?;
    let mut stdout = io::stdout();
    execute!(stdout, EnterAlternateScreen)?;
    let backend = CrosstermBackend::new(stdout);
    let mut terminal = Terminal::new(backend)?;

    let mut state = TuiState::new(old_src, new_src, old_label, new_label, options, unified);

    let res = tui_loop(&mut terminal, &mut state);

    disable_raw_mode()?;
    execute!(terminal.backend_mut(), LeaveAlternateScreen)?;
    terminal.show_cursor()?;

    res
}

fn tui_loop(
    terminal: &mut Terminal<CrosstermBackend<io::Stdout>>,
    state: &mut TuiState,
) -> Result<()> {
    loop {
        terminal.draw(|f| draw_ui(f, state))?;

        if let Event::Key(key) = event::read()? {
            if key.kind != KeyEventKind::Press {
                continue;
            }
            match key.code {
                KeyCode::Char('q') | KeyCode::Esc => {
                    if state.show_mappings {
                        state.show_mappings = false;
                    } else {
                        break;
                    }
                }
                KeyCode::Char('j') | KeyCode::Down => {
                    let max_scroll = state.visible_rows().len().saturating_sub(1);
                    if state.scroll < max_scroll {
                        state.scroll += 1;
                    }
                }
                KeyCode::Char('k') | KeyCode::Up => {
                    state.scroll = state.scroll.saturating_sub(1);
                }
                KeyCode::PageDown | KeyCode::Char(' ') => {
                    let max_scroll = state.visible_rows().len().saturating_sub(1);
                    state.scroll = (state.scroll + 20).min(max_scroll);
                }
                KeyCode::PageUp => {
                    state.scroll = state.scroll.saturating_sub(20);
                }
                KeyCode::Char('g') | KeyCode::Home => state.scroll = 0,
                KeyCode::Char('G') | KeyCode::End => {
                    state.scroll = state.visible_rows().len().saturating_sub(1);
                }
                KeyCode::Char('n') => state.jump_semantic(true),
                KeyCode::Char('p') => state.jump_semantic(false),
                KeyCode::Tab => state.unified = !state.unified,
                KeyCode::Char('v') => state.show_normalized = !state.show_normalized,
                KeyCode::Char('m') => state.show_mappings = !state.show_mappings,
                KeyCode::Char('h') => {
                    state.options.hide_noise_lines = !state.options.hide_noise_lines;
                    state.recompute();
                }
                KeyCode::Char('1') => {
                    state.options.normalize_addresses = !state.options.normalize_addresses;
                    state.recompute();
                }
                KeyCode::Char('2') => {
                    state.options.normalize_variables = !state.options.normalize_variables;
                    state.recompute();
                }
                KeyCode::Char('3') => {
                    state.options.ignore_comments = !state.options.ignore_comments;
                    state.recompute();
                }
                KeyCode::Char('4') => {
                    state.options.align_control_flow = !state.options.align_control_flow;
                    state.recompute();
                }
                KeyCode::Char('5') => {
                    state.options.collapse_declarations = !state.options.collapse_declarations;
                    state.recompute();
                }
                KeyCode::Char('6') => {
                    state.options.simplify_ida_casts = !state.options.simplify_ida_casts;
                    state.recompute();
                }
                KeyCode::Char('7') => {
                    state.options.placeholder_padding = !state.options.placeholder_padding;
                    state.recompute();
                }
                KeyCode::Char('8') => {
                    state.options.normalize_pointer_units = !state.options.normalize_pointer_units;
                    state.recompute();
                }
                _ => {}
            }
        }
    }
    Ok(())
}

fn draw_ui(f: &mut ratatui::Frame, state: &TuiState) {
    let chunks = Layout::default()
        .direction(Direction::Vertical)
        .constraints([
            Constraint::Length(3),
            Constraint::Min(8),
            Constraint::Length(3),
        ])
        .split(f.area());

    draw_header(f, chunks[0], state);
    draw_diff_body(f, chunks[1], state);
    draw_footer(f, chunks[2], state);

    if state.show_mappings {
        draw_mapping_modal(f, f.area(), state);
    }
}

fn draw_header(f: &mut ratatui::Frame, area: Rect, state: &TuiState) {
    let s = &state.diff.summary;
    let mode_str = if state.unified { "统一视图" } else { "并排视图" };
    let text_mode = if state.show_normalized {
        "规范化代码"
    } else {
        "原始代码"
    };

    let line1 = Line::from(vec![
        Span::styled(
            " IDA 伪代码补丁对比查看器 ",
            Style::default()
                .fg(Color::Black)
                .bg(Color::Cyan)
                .add_modifier(Modifier::BOLD),
        ),
        Span::raw(format!("  {}  ↔  {}   ", state.old_label, state.new_label)),
        Span::styled(
            format!("[{mode_str} | {text_mode}]"),
            Style::default().fg(Color::LightBlue),
        ),
    ]);

    let line2 = Line::from(vec![
        Span::styled(
            format!(" +{} 新增 ", s.semantic_added_rows),
            Style::default().fg(Color::Green).add_modifier(Modifier::BOLD),
        ),
        Span::styled(
            format!(" -{} 删除 ", s.semantic_removed_rows),
            Style::default().fg(Color::Red).add_modifier(Modifier::BOLD),
        ),
        Span::styled(
            format!(" ~{} 修改 ", s.semantic_modified_rows),
            Style::default().fg(Color::Yellow).add_modifier(Modifier::BOLD),
        ),
        Span::raw(" │ "),
        Span::styled(
            format!("≈ {} 噪音已过滤", s.noise_filtered_rows),
            Style::default().fg(Color::DarkGray),
        ),
        Span::raw(" │ "),
        Span::styled(
            format!("⇄ {} 控制流重排对齐", s.cfg_reorders_aligned),
            Style::default().fg(Color::Magenta),
        ),
    ]);

    let header = Paragraph::new(vec![line1, line2])
        .block(Block::default().borders(Borders::BOTTOM).border_style(Style::default().fg(Color::DarkGray)));
    f.render_widget(header, area);
}

fn side_to_spans<'a>(
    side: &'a LineSide,
    kind: ChangeKind,
    show_normalized: bool,
    max_chars: usize,
) -> Vec<Span<'a>> {
    let mut spans = Vec::new();
    let mut used = 0usize;

    let base_fg = match kind {
        ChangeKind::Unchanged => Color::Gray,
        ChangeKind::NoiseOnly => Color::DarkGray,
        ChangeKind::Added => Color::LightGreen,
        ChangeKind::Removed => Color::LightRed,
        ChangeKind::Modified => Color::White,
    };

    if show_normalized {
        let txt = &side.normalized_text;
        let clipped: String = txt.chars().take(max_chars).collect();
        let style = if side.is_placeholder {
            Style::default()
                .fg(Color::Cyan)
                .add_modifier(Modifier::DIM | Modifier::ITALIC)
        } else {
            Style::default().fg(base_fg)
        };
        spans.push(Span::styled(clipped, style));
        return spans;
    }

    for tok in &side.tokens {
        if used >= max_chars {
            break;
        }
        let avail = max_chars - used;
        let ch_len = tok.text.chars().count();
        let slice: String = if ch_len > avail {
            tok.text.chars().take(avail).collect()
        } else {
            tok.text.clone()
        };
        used += slice.chars().count();

        let style = match tok.highlight {
            TokenHighlight::None => Style::default().fg(base_fg),
            TokenHighlight::NoiseChange => Style::default()
                .fg(Color::DarkGray)
                .add_modifier(Modifier::UNDERLINED),
            TokenHighlight::SemanticAdd => Style::default()
                .fg(Color::Black)
                .bg(Color::Green)
                .add_modifier(Modifier::BOLD),
            TokenHighlight::SemanticDelete => Style::default()
                .fg(Color::White)
                .bg(Color::Red)
                .add_modifier(Modifier::BOLD),
            TokenHighlight::SemanticModify => Style::default()
                .fg(Color::Black)
                .bg(Color::Yellow)
                .add_modifier(Modifier::BOLD),
            TokenHighlight::Placeholder => Style::default()
                .fg(Color::Cyan)
                .add_modifier(Modifier::DIM | Modifier::ITALIC),
        };
        spans.push(Span::styled(slice, style));
    }

    if used < max_chars {
        spans.push(Span::raw(" ".repeat(max_chars - used)));
    }
    spans
}

fn tag_badge(tag: &Option<CfgReorderTag>) -> Option<Span<'static>> {
    let t = tag.as_ref()?;
    let label = format_cfg_tag(t);
    let color = match t {
        CfgReorderTag::BranchInverted { .. } => Color::Magenta,
        CfgReorderTag::GuardFlattened { .. } => Color::Cyan,
        CfgReorderTag::LabelMoved { .. } => Color::LightBlue,
        CfgReorderTag::CaseReordered { .. } => Color::LightMagenta,
        CfgReorderTag::DeclarationBlock => Color::DarkGray,
    };
    Some(Span::styled(
        format!(" [{label}]"),
        Style::default().fg(color),
    ))
}

fn draw_diff_body(f: &mut ratatui::Frame, area: Rect, state: &TuiState) {
    let vis = state.visible_rows();
    let height = area.height as usize;
    let slice_end = (state.scroll + height).min(vis.len());
    let rows = &vis[state.scroll.min(vis.len())..slice_end];

    let mut lines: Vec<Line> = Vec::with_capacity(rows.len());

    if state.unified {
        let width = area.width.saturating_sub(14) as usize;
        for row in rows {
            let marker = match row.kind {
                ChangeKind::Unchanged => Span::styled("   ", Style::default().fg(Color::DarkGray)),
                ChangeKind::NoiseOnly => Span::styled(" ≈ ", Style::default().fg(Color::DarkGray)),
                ChangeKind::Added => Span::styled(" + ", Style::default().fg(Color::Green).add_modifier(Modifier::BOLD)),
                ChangeKind::Removed => Span::styled(" - ", Style::default().fg(Color::Red).add_modifier(Modifier::BOLD)),
                ChangeKind::Modified => Span::styled(" ~ ", Style::default().fg(Color::Yellow).add_modifier(Modifier::BOLD)),
            };
            if row.kind == ChangeKind::Modified {
                if let Some(o) = &row.old_line {
                    let mut spans = vec![
                        Span::styled(format!("{:>4}    ", o.line_no), Style::default().fg(Color::DarkGray)),
                        Span::styled(" - ", Style::default().fg(Color::Red)),
                    ];
                    spans.extend(side_to_spans(o, ChangeKind::Removed, state.show_normalized, width));
                    lines.push(Line::from(spans));
                }
                if let Some(n) = &row.new_line {
                    let mut spans = vec![
                        Span::styled(format!("    {:>4}", n.line_no), Style::default().fg(Color::DarkGray)),
                        Span::styled(" + ", Style::default().fg(Color::Green)),
                    ];
                    spans.extend(side_to_spans(n, ChangeKind::Added, state.show_normalized, width));
                    if let Some(b) = tag_badge(&row.cfg_tag) {
                        spans.push(b);
                    }
                    lines.push(Line::from(spans));
                }
            } else {
                let o_no = row.old_line.as_ref().map(|l| format!("{:>4}", l.line_no)).unwrap_or_else(|| "    ".into());
                let n_no = row.new_line.as_ref().map(|l| format!("{:>4}", l.line_no)).unwrap_or_else(|| "    ".into());
                let mut spans = vec![
                    Span::styled(format!("{o_no} {n_no}"), Style::default().fg(Color::DarkGray)),
                    marker,
                ];
                if let Some(side) = row.new_line.as_ref().or(row.old_line.as_ref()) {
                    spans.extend(side_to_spans(side, row.kind, state.show_normalized, width));
                }
                if let Some(b) = tag_badge(&row.cfg_tag) {
                    spans.push(b);
                }
                lines.push(Line::from(spans));
            }
        }
    } else {
        // Side-by-side layout
        let tag_reserve = 22usize;
        let usable = area.width.saturating_sub((tag_reserve + 14) as u16) as usize;
        let col_w = (usable / 2).max(16);

        for (rel_idx, row) in rows.iter().enumerate() {
            let abs_idx = state.scroll + rel_idx;
            let is_cursor = state.selected_semantic_idx == Some(abs_idx);

            let o_no = row
                .old_line
                .as_ref()
                .map(|l| {
                    if l.is_placeholder {
                        "   · ".to_string()
                    } else {
                        format!("{:>4} ", l.line_no)
                    }
                })
                .unwrap_or_else(|| "     ".into());
            let n_no = row
                .new_line
                .as_ref()
                .map(|l| {
                    if l.is_placeholder {
                        "   · ".to_string()
                    } else {
                        format!("{:>4} ", l.line_no)
                    }
                })
                .unwrap_or_else(|| "     ".into());

            let mut spans = Vec::new();
            let prefix = if is_cursor { "▶" } else { " " };
            spans.push(Span::styled(
                format!("{prefix}{o_no}"),
                Style::default().fg(if is_cursor { Color::Yellow } else { Color::DarkGray }),
            ));

            if let Some(o) = &row.old_line {
                let k = if row.kind == ChangeKind::Modified {
                    ChangeKind::Modified
                } else {
                    row.kind
                };
                spans.extend(side_to_spans(o, k, state.show_normalized, col_w));
            } else {
                spans.push(Span::raw(" ".repeat(col_w)));
            }

            let sep_style = match row.kind {
                ChangeKind::Added => Style::default().fg(Color::Green),
                ChangeKind::Removed => Style::default().fg(Color::Red),
                ChangeKind::Modified => Style::default().fg(Color::Yellow),
                _ => Style::default().fg(Color::DarkGray),
            };
            spans.push(Span::styled(" │ ", sep_style));
            spans.push(Span::styled(n_no, Style::default().fg(Color::DarkGray)));

            if let Some(n) = &row.new_line {
                let k = if row.kind == ChangeKind::Modified {
                    ChangeKind::Modified
                } else {
                    row.kind
                };
                spans.extend(side_to_spans(n, k, state.show_normalized, col_w));
            } else {
                spans.push(Span::raw(" ".repeat(col_w)));
            }

            if let Some(b) = tag_badge(&row.cfg_tag) {
                spans.push(b);
            }
            lines.push(Line::from(spans));
        }
    }

    let body = Paragraph::new(lines).wrap(Wrap { trim: false });
    f.render_widget(body, area);
}

fn toggle_span(key: &str, label: &str, on: bool) -> Span<'static> {
    let state = if on { "开" } else { "关" };
    let color = if on { Color::Green } else { Color::DarkGray };
    Span::styled(format!(" [{key}]{label}:{state} "), Style::default().fg(color))
}

fn draw_footer(f: &mut ratatui::Frame, area: Rect, state: &TuiState) {
    let o = &state.options;
    let line1 = Line::from(vec![
        toggle_span("1", "地址", o.normalize_addresses),
        toggle_span("2", "变量", o.normalize_variables),
        toggle_span("3", "注释", o.ignore_comments),
        toggle_span("4", "控制流", o.align_control_flow),
        toggle_span("5", "声明区", o.collapse_declarations),
        toggle_span("6", "强转", o.simplify_ida_casts),
        toggle_span("7", "占位填充", o.placeholder_padding),
        toggle_span("8", "指针单位", o.normalize_pointer_units),
        toggle_span("h", "隐藏噪音", o.hide_noise_lines),
    ]);
    let line2 = Line::from(vec![
        Span::styled(
            " [Tab]并排/统一  [v]原始/规范化  [m]映射表  [n/p]下/上一处真实修改  [j/k]滚动  [q]退出 ",
            Style::default().fg(Color::Cyan),
        ),
    ]);
    let footer = Paragraph::new(vec![line1, line2])
        .block(Block::default().borders(Borders::TOP).border_style(Style::default().fg(Color::DarkGray)));
    f.render_widget(footer, area);
}

fn draw_mapping_modal(f: &mut ratatui::Frame, area: Rect, state: &TuiState) {
    let popup = Rect {
        x: area.width / 8,
        y: area.height / 8,
        width: (area.width * 3 / 4).max(30),
        height: (area.height * 3 / 4).max(10),
    };
    f.render_widget(Clear, popup);

    let s = &state.diff.summary;
    let mut items = Vec::new();
    items.push(ListItem::new(Span::styled(
        "局部变量与参数映射 (旧版 ↔ 新版):",
        Style::default().fg(Color::Cyan).add_modifier(Modifier::BOLD),
    )));
    for (id, old_v, new_v) in &s.variable_mappings {
        items.push(ListItem::new(format!("  {id:<8}  {old_v:<16} ↔  {new_v}")));
    }
    items.push(ListItem::new(""));
    items.push(ListItem::new(Span::styled(
        "地址符号映射 (旧版 ↔ 新版):",
        Style::default().fg(Color::Magenta).add_modifier(Modifier::BOLD),
    )));
    for (id, old_s, new_s) in &s.symbol_mappings {
        items.push(ListItem::new(format!("  {id:<8}  {old_s:<20} ↔  {new_s}")));
    }

    let list = List::new(items).block(
        Block::default()
            .title(" 规范化变量与地址符号映射表 (按 m 或 Esc 关闭) ")
            .borders(Borders::ALL)
            .border_style(Style::default().fg(Color::Cyan)),
    );
    f.render_widget(list, popup);
}
