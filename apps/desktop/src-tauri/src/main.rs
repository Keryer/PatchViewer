#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use patch_viewer_core::{diff_pseudocode, DiffOptions, DiffResult};
use serde::Serialize;

const DEMO_OLD: &str = include_str!("../../../../examples/cve_patch_old.c");
const DEMO_NEW: &str = include_str!("../../../../examples/cve_patch_new.c");

#[derive(Serialize)]
struct DemoPair {
    old_src: &'static str,
    new_src: &'static str,
}

#[tauri::command]
fn load_demo_pair() -> DemoPair {
    DemoPair {
        old_src: DEMO_OLD,
        new_src: DEMO_NEW,
    }
}

#[tauri::command]
fn compute_diff(old_src: String, new_src: String, options: DiffOptions) -> DiffResult {
    diff_pseudocode(&old_src, &new_src, &options)
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![load_demo_pair, compute_diff])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
