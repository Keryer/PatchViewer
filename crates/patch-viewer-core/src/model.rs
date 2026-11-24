use serde::{Deserialize, Serialize};

use crate::config::DiffOptions;

/// Classification of a single aligned row in the dual-track diff result.
#[derive(Debug, Clone, Copy, Serialize, Deserialize, PartialEq, Eq)]
pub enum ChangeKind {
    /// Raw text and normalized text are strictly identical.
    Unchanged,
    /// Raw text differs (e.g. `v4` vs `v5`, `sub_140005120` vs `sub_140006890`, stack comments),
    /// but normalized semantic representation is identical.
    NoiseOnly,
    /// Aligned lines share context/structure but contain a genuine semantic difference.
    Modified,
    /// Line exists only in the new pseudocode version (genuine addition).
    Added,
    /// Line exists only in the old pseudocode version (genuine removal).
    Removed,
}

/// Structural annotation attached when control-flow alignment or declaration grouping matched blocks.
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq)]
#[serde(tag = "type", content = "data")]
pub enum CfgReorderTag {
    BranchInverted {
        note: String,
    },
    GuardFlattened {
        note: String,
    },
    LabelMoved {
        label_old: String,
        label_new: String,
        from_line: usize,
        to_line: usize,
    },
    CaseReordered {
        case_key: String,
    },
    DeclarationBlock,
}

/// Highlight category for an individual token span within a line.
#[derive(Debug, Clone, Copy, Serialize, Deserialize, PartialEq, Eq)]
pub enum TokenHighlight {
    None,
    NoiseChange,
    SemanticAdd,
    SemanticDelete,
    SemanticModify,
}

/// Token-level slice inside a line, carrying optional canonical mapping metadata.
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq)]
pub struct TokenSpan {
    pub text: String,
    pub normalized: Option<String>,
    pub counterpart: Option<String>,
    pub highlight: TokenHighlight,
}

/// One side (Old or New) of an aligned diff row.
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq)]
pub struct LineSide {
    /// 1-based line number in the original input file.
    pub line_no: usize,
    /// Original line text from input.
    pub raw_text: String,
    /// Canonical normalized representation used for comparison.
    pub normalized_text: String,
    /// Tokenized spans with intra-line highlights and mapping tooltips.
    pub tokens: Vec<TokenSpan>,
}

/// A single row in the side-by-side / unified diff view.
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq)]
pub struct AlignedRow {
    pub row_index: usize,
    pub old_line: Option<LineSide>,
    pub new_line: Option<LineSide>,
    pub kind: ChangeKind,
    pub cfg_tag: Option<CfgReorderTag>,
}

/// Aggregated statistics and canonical symbol/variable mappings for a diff run.
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq, Default)]
pub struct DiffSummary {
    pub total_rows: usize,
    pub unchanged_rows: usize,
    pub noise_filtered_rows: usize,
    pub semantic_modified_rows: usize,
    pub semantic_added_rows: usize,
    pub semantic_removed_rows: usize,
    pub cfg_reorders_aligned: usize,
    /// Tuples of `(canonical_id, old_var, new_var)` e.g. `("$VAR_1", "v4", "v5")`.
    pub variable_mappings: Vec<(String, String, String)>,
    /// Tuples of `(canonical_id, old_symbol, new_symbol)` e.g. `("$SUB_1", "sub_140005120", "sub_140006890")`.
    pub symbol_mappings: Vec<(String, String, String)>,
}

/// Complete output returned by `patch_viewer_core::diff_pseudocode`.
#[derive(Debug, Clone, Serialize, Deserialize, PartialEq, Eq)]
pub struct DiffResult {
    pub rows: Vec<AlignedRow>,
    pub summary: DiffSummary,
    pub options: DiffOptions,
}
