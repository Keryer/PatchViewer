mod ansi;
mod server;
mod tui;

use std::fs;
use std::io::IsTerminal;
use std::path::PathBuf;

use anyhow::{bail, Context, Result};
use clap::Parser;
use patch_viewer_core::{diff_pseudocode, DiffOptions};

const DEMO_OLD: &str = include_str!("../../../examples/cve_patch_old.c");
const DEMO_NEW: &str = include_str!("../../../examples/cve_patch_new.c");

#[derive(Parser, Debug)]
#[command(
    name = "patch-viewer",
    version,
    about = "IDA Pro (Hex-Rays) 反编译伪代码补丁差异查看器，支持符号降噪与四类控制流重排对齐"
)]
struct Cli {
    /// 旧版伪代码文件路径（省略时配合 --demo 使用内置样例）
    old_file: Option<PathBuf>,

    /// 新版伪代码文件路径（省略时配合 --demo 使用内置样例）
    new_file: Option<PathBuf>,

    /// 使用内置的 IDA CVE 补丁 + 4 类控制流重排演示样例
    #[arg(long)]
    demo: bool,

    /// 强制进入交互式 Ratatui 终端界面 (TUI)
    #[arg(long)]
    tui: bool,

    /// 非交互式终端彩色 Diff 输出并退出
    #[arg(long, alias = "no-tui")]
    ansi: bool,

    /// 导出完整结构化 DiffResult JSON 并退出
    #[arg(long)]
    json: bool,

    /// 启动桌面版 Web GUI 服务（不自动弹出浏览器窗口）
    #[arg(long, value_name = "端口", num_args = 0..=1, default_missing_value = "3780")]
    web: Option<u16>,

    /// 启动桌面版 GUI 服务并自动弹出独立应用窗口
    #[arg(long, value_name = "端口", num_args = 0..=1, default_missing_value = "3780")]
    gui: Option<u16>,

    /// 使用统一单栏视图 (Unified) 替代并排双栏视图 (Side-by-Side)
    #[arg(long, short = 'u')]
    unified: bool,

    /// 打印规范化后的伪代码而非原始伪代码（ANSI 模式）
    #[arg(long)]
    show_normalized: bool,

    /// 打印变量与地址符号映射表（ANSI 模式）
    #[arg(long, short = 'm')]
    mappings: bool,

    /// 关闭 IDA 地址符号归一化 (sub_xxx, loc_xxx, dword_xxx 等)
    #[arg(long)]
    no_addr_norm: bool,

    /// 关闭地址顺序编号，改用通用占位符 ($SUB 等)
    #[arg(long)]
    no_seq_addr: bool,

    /// 关闭局部变量与参数重编号 (v1..vN, a1..aN)
    #[arg(long)]
    no_var_norm: bool,

    /// 保留注释与栈帧偏移注释参与比对
    #[arg(long)]
    no_comment_strip: bool,

    /// 关闭控制流重排对齐 (if/else 分支反转、Guard、switch、goto)
    #[arg(long)]
    no_cfg_align: bool,

    /// 关闭函数顶部局部变量声明区归并重排对齐
    #[arg(long)]
    no_decl_collapse: bool,

    /// 简化常见 IDA 冗余宏与强转 (LOBYTE, (unsigned int) 等)
    #[arg(long)]
    simplify_casts: bool,

    /// 隐藏仅包含归一化噪音的行
    #[arg(long)]
    hide_noise: bool,
}

fn load_inputs(cli: &Cli) -> Result<(String, String, String, String)> {
    if cli.demo || (cli.old_file.is_none() && cli.new_file.is_none()) {
        return Ok((
            DEMO_OLD.to_string(),
            DEMO_NEW.to_string(),
            "examples/cve_patch_old.c".to_string(),
            "examples/cve_patch_new.c".to_string(),
        ));
    }

    match (&cli.old_file, &cli.new_file) {
        (Some(o), Some(n)) => {
            let old_src = fs::read_to_string(o)
                .with_context(|| format!("读取旧版伪代码文件失败: {}", o.display()))?;
            let new_src = fs::read_to_string(n)
                .with_context(|| format!("读取新版伪代码文件失败: {}", n.display()))?;
            Ok((
                old_src,
                new_src,
                o.display().to_string(),
                n.display().to_string(),
            ))
        }
        _ => bail!("请同时提供旧版与新版伪代码文件路径，或传入 --demo 使用内置样例"),
    }
}

fn main() -> Result<()> {
    let cli = Cli::parse();
    let (old_src, new_src, old_label, new_label) = load_inputs(&cli)?;

    let options = DiffOptions {
        ignore_comments: !cli.no_comment_strip,
        normalize_addresses: !cli.no_addr_norm,
        sequential_address_numbering: !cli.no_seq_addr,
        normalize_variables: !cli.no_var_norm,
        collapse_declarations: !cli.no_decl_collapse,
        simplify_ida_casts: cli.simplify_casts,
        align_control_flow: !cli.no_cfg_align,
        hide_noise_lines: cli.hide_noise,
    };

    if let Some(port) = cli.gui {
        return server::serve_web_gui(port, true, old_src, new_src, old_label, new_label, options);
    }

    if let Some(port) = cli.web {
        return server::serve_web_gui(port, false, old_src, new_src, old_label, new_label, options);
    }

    if cli.json {
        let res = diff_pseudocode(&old_src, &new_src, &options);
        println!("{}", serde_json::to_string_pretty(&res)?);
        return Ok(());
    }

    let use_tui = if cli.ansi {
        false
    } else if cli.tui {
        true
    } else {
        std::io::stdout().is_terminal()
    };

    if use_tui {
        tui::run_tui(old_src, new_src, old_label, new_label, options, cli.unified)?;
    } else {
        let res = diff_pseudocode(&old_src, &new_src, &options);
        ansi::print_ansi_diff(
            &res,
            &old_label,
            &new_label,
            cli.unified,
            cli.show_normalized,
            cli.mappings,
        );
    }

    Ok(())
}
