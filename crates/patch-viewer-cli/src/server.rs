use std::io::{BufRead, BufReader, Read, Write};
use std::net::{TcpListener, TcpStream};
use std::sync::Arc;

use anyhow::{Context, Result};
use patch_viewer_core::{diff_pseudocode, DiffOptions};
use serde::{Deserialize, Serialize};

const WEB_UI_HTML: &str = include_str!("web_ui.html");
const DEMO_OLD: &str = include_str!("../../../examples/cve_patch_old.c");
const DEMO_NEW: &str = include_str!("../../../examples/cve_patch_new.c");

#[derive(Clone)]
struct ServerContext {
    old_src: String,
    new_src: String,
    old_label: String,
    new_label: String,
    options: DiffOptions,
}

#[derive(Serialize)]
struct InitPayload<'a> {
    old_src: &'a str,
    new_src: &'a str,
    old_label: &'a str,
    new_label: &'a str,
    demo_old_src: &'a str,
    demo_new_src: &'a str,
    options: &'a DiffOptions,
}

#[derive(Deserialize)]
struct DiffRequest {
    old_src: String,
    new_src: String,
    options: DiffOptions,
}

pub fn serve_web_gui(
    port: u16,
    open_app_window: bool,
    old_src: String,
    new_src: String,
    old_label: String,
    new_label: String,
    options: DiffOptions,
) -> Result<()> {
    let addr = format!("127.0.0.1:{port}");
    let listener = TcpListener::bind(&addr).with_context(|| format!("绑定端口失败 {addr}"))?;
    let actual_port = listener.local_addr()?.port();
    let url = format!("http://127.0.0.1:{actual_port}");

    println!("IDA 伪代码补丁查看器 Desktop Web UI 已启动: {url}");
    println!("按 Ctrl+C 退出服务。");

    if open_app_window {
        try_open_desktop_window(&url);
    }

    let ctx = Arc::new(ServerContext {
        old_src,
        new_src,
        old_label,
        new_label,
        options,
    });

    for stream in listener.incoming() {
        match stream {
            Ok(s) => {
                let ctx_clone = Arc::clone(&ctx);
                std::thread::spawn(move || {
                    let _ = handle_connection(s, &ctx_clone);
                });
            }
            Err(e) => eprintln!("accept error: {e}"),
        }
    }

    Ok(())
}

fn try_open_desktop_window(url: &str) {
    #[cfg(target_os = "windows")]
    {
        let app_arg = format!("--app={url}");
        if std::process::Command::new("msedge")
            .arg(&app_arg)
            .spawn()
            .is_ok()
        {
            return;
        }
        let _ = std::process::Command::new("cmd")
            .args(["/C", "start", "", url])
            .spawn();
    }
    #[cfg(target_os = "macos")]
    {
        let _ = std::process::Command::new("open").arg(url).spawn();
    }
    #[cfg(all(unix, not(target_os = "macos")))]
    {
        let _ = std::process::Command::new("xdg-open").arg(url).spawn();
    }
}

fn handle_connection(mut stream: TcpStream, ctx: &ServerContext) -> Result<()> {
    let mut reader = BufReader::new(stream.try_clone()?);
    let mut request_line = String::new();
    if reader.read_line(&mut request_line)? == 0 {
        return Ok(());
    }

    let parts: Vec<&str> = request_line.split_whitespace().collect();
    if parts.len() < 2 {
        return Ok(());
    }
    let method = parts[0];
    let path = parts[1];

    let mut content_length = 0usize;
    loop {
        let mut header_line = String::new();
        let n = reader.read_line(&mut header_line)?;
        if n == 0 || header_line == "\r\n" || header_line == "\n" {
            break;
        }
        if let Some((k, v)) = header_line.split_once(':') {
            if k.trim().eq_ignore_ascii_case("Content-Length") {
                content_length = v.trim().parse::<usize>().unwrap_or(0);
            }
        }
    }

    let mut body = vec![0u8; content_length];
    if content_length > 0 {
        reader.read_exact(&mut body)?;
    }

    match (method, path) {
        ("GET", "/") | ("GET", "/index.html") => {
            write_response(&mut stream, "200 OK", "text/html; charset=utf-8", WEB_UI_HTML.as_bytes())?;
        }
        ("GET", "/api/health") => {
            write_response(&mut stream, "200 OK", "application/json", br#"{"status":"ok"}"#)?;
        }
        ("GET", "/api/init") => {
            let payload = InitPayload {
                old_src: &ctx.old_src,
                new_src: &ctx.new_src,
                old_label: &ctx.old_label,
                new_label: &ctx.new_label,
                demo_old_src: DEMO_OLD,
                demo_new_src: DEMO_NEW,
                options: &ctx.options,
            };
            let json = serde_json::to_vec(&payload)?;
            write_response(&mut stream, "200 OK", "application/json", &json)?;
        }
        ("POST", "/api/diff") => {
            let req: DiffRequest = serde_json::from_slice(&body)?;
            let res = diff_pseudocode(&req.old_src, &req.new_src, &req.options);
            let json = serde_json::to_vec(&res)?;
            write_response(&mut stream, "200 OK", "application/json", &json)?;
        }
        _ => {
            write_response(&mut stream, "404 Not Found", "text/plain", b"Not Found")?;
        }
    }

    Ok(())
}

fn write_response(stream: &mut TcpStream, status: &str, content_type: &str, body: &[u8]) -> Result<()> {
    let headers = format!(
        "HTTP/1.1 {status}\r\nContent-Type: {content_type}\r\nContent-Length: {}\r\nConnection: close\r\nAccess-Control-Allow-Origin: *\r\n\r\n",
        body.len()
    );
    stream.write_all(headers.as_bytes())?;
    stream.write_all(body)?;
    stream.flush()?;
    Ok(())
}
