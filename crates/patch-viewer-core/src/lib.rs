pub mod cfg_align;
pub mod config;
pub mod differ;
pub mod model;
pub mod normalizer;
pub mod parser;
pub mod type_norm;

pub use config::DiffOptions;
pub use differ::diff_pseudocode;
pub use model::{
    AlignedRow, CfgReorderTag, ChangeKind, DiffResult, DiffSummary, LineSide, TokenHighlight,
    TokenSpan,
};
