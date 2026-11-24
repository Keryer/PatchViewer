use serde::{Deserialize, Serialize};

/// Configuration flags controlling how IDA Hex-Rays pseudocode is normalized,
/// structurally aligned, and diffed.
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq)]
#[serde(default)]
pub struct DiffOptions {
    /// Strip comments (`// ...`, `/* ... */`), including IDA stack frame
    /// annotations like `// [rsp+20h] [rbp-18h] BYREF` and register hints (`// eax`).
    pub ignore_comments: bool,
    /// Normalize IDA address-encoded symbols (`sub_140012A40`, `loc_xxx`, `dword_xxx`, etc.).
    pub normalize_addresses: bool,
    /// When normalizing addresses, assign sequential canonical IDs (`$SUB_1`, `$LOC_1`, `$DAT_1`)
    /// by first-use order in executable statements instead of generic placeholders (`$SUB`).
    pub sequential_address_numbering: bool,
    /// Normalize IDA auto-named local variables (`v1..vN`, `result`) and parameters (`a1..aN`)
    /// by first-use order in executable statements (`$VAR_1`, `$ARG_1`).
    pub normalize_variables: bool,
    /// Group and align top-of-function local variable declarations (`int v3; // eax`)
    /// so register reallocation or stack-frame shifts do not pollute the diff.
    pub collapse_declarations: bool,
    /// Simplify common redundant IDA macro wrappers and casts (`LOBYTE`, `LODWORD`, `(unsigned int)`).
    pub simplify_ida_casts: bool,
    /// Enable structural control-flow alignment (branch inversion, guard-clause flattening,
    /// `goto` label block relocation, and `switch-case` reordering).
    pub align_control_flow: bool,
    /// Hint for UI/CLI renderers to hide or fold `NoiseOnly` rows.
    pub hide_noise_lines: bool,
}

impl Default for DiffOptions {
    fn default() -> Self {
        Self {
            ignore_comments: true,
            normalize_addresses: true,
            sequential_address_numbering: true,
            normalize_variables: true,
            collapse_declarations: true,
            simplify_ida_casts: false,
            align_control_flow: true,
            hide_noise_lines: false,
        }
    }
}
