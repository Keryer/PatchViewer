import React, { useEffect, useRef, useState } from "react";
import { invoke } from "@tauri-apps/api/core";

export interface DiffOptions {
  ignore_comments: boolean;
  normalize_addresses: boolean;
  sequential_address_numbering: boolean;
  normalize_variables: boolean;
  collapse_declarations: boolean;
  simplify_ida_casts: boolean;
  align_control_flow: boolean;
  hide_noise_lines: boolean;
}

export interface TokenSpan {
  text: string;
  normalized?: string | null;
  counterpart?: string | null;
  highlight: "None" | "NoiseChange" | "SemanticAdd" | "SemanticDelete" | "SemanticModify";
}

export interface LineSide {
  line_no: number;
  raw_text: string;
  normalized_text: string;
  tokens: TokenSpan[];
}

export type CfgReorderTag =
  | { type: "BranchInverted"; data: { note: string } }
  | { type: "GuardFlattened"; data: { note: string } }
  | { type: "LabelMoved"; data: { label_old: string; label_new: string; from_line: number; to_line: number } }
  | { type: "CaseReordered"; data: { case_key: string } }
  | { type: "DeclarationBlock" };

export interface AlignedRow {
  row_index: number;
  old_line?: LineSide | null;
  new_line?: LineSide | null;
  kind: "Unchanged" | "NoiseOnly" | "Modified" | "Added" | "Removed";
  cfg_tag?: CfgReorderTag | null;
}

export interface DiffSummary {
  total_rows: number;
  unchanged_rows: number;
  noise_filtered_rows: number;
  semantic_modified_rows: number;
  semantic_added_rows: number;
  semantic_removed_rows: number;
  cfg_reorders_aligned: number;
  variable_mappings: [string, string, string][];
  symbol_mappings: [string, string, string][];
}

export interface DiffResult {
  rows: AlignedRow[];
  summary: DiffSummary;
  options: DiffOptions;
}

const DEFAULT_OPTIONS: DiffOptions = {
  ignore_comments: true,
  normalize_addresses: true,
  sequential_address_numbering: true,
  normalize_variables: true,
  collapse_declarations: true,
  simplify_ida_casts: false,
  align_control_flow: true,
  hide_noise_lines: false
};

const DEMOS: Record<string, { oldLabel: string; newLabel: string; oldSrc: string; newSrc: string }> = {
  branch_invert: {
    oldLabel: "old_branch.c",
    newLabel: "new_branch.c",
    oldSrc: `int __fastcall sub_401000(int a1, int a2)\n{\n  if ( a1 == 0x100 )\n  {\n    sub_401100(a2);\n    return 1;\n  }\n  else\n  {\n    sub_401200(a2);\n    return 0;\n  }\n}`,
    newSrc: `int __fastcall sub_402000(int a1, int a2)\n{\n  if ( a1 != 0x100 )\n  {\n    sub_402200(a2);\n    return 0;\n  }\n  else\n  {\n    sub_402100(a2);\n    return 1;\n  }\n}`
  },
  guard_clause: {
    oldLabel: "old_guard.c",
    newLabel: "new_nested.c",
    oldSrc: `int __fastcall sub_401000(int *a1)\n{\n  int v2; // eax\n\n  if ( !a1 )\n    return -1;\n  v2 = *a1;\n  sub_401100(v2);\n  return 0;\n}`,
    newSrc: `int __fastcall sub_402000(int *a1)\n{\n  int v3; // eax\n\n  if ( a1 )\n  {\n    v3 = *a1;\n    sub_402100(v3);\n    return 0;\n  }\n  return -1;\n}`
  }
};

function renderCfgBadge(tag?: CfgReorderTag | null) {
  if (!tag) return null;
  switch (tag.type) {
    case "BranchInverted":
      return <span className="cfg-badge cfg-BranchInverted">⇄ if/else 分支反转</span>;
    case "GuardFlattened":
      return <span className="cfg-badge cfg-GuardFlattened">⇄ Guard / 嵌套已对齐</span>;
    case "LabelMoved":
      return <span className="cfg-badge cfg-LabelMoved">⇄ {tag.data.label_old}↔{tag.data.label_new}</span>;
    case "CaseReordered":
      return <span className="cfg-badge cfg-CaseReordered">⇄ {tag.data.case_key} 重排</span>;
    case "DeclarationBlock":
      return <span className="cfg-badge cfg-DeclarationBlock">📦 声明区</span>;
  }
}

export default function App() {
  const [oldSrc, setOldSrc] = useState("");
  const [newSrc, setNewSrc] = useState("");
  const [oldLabel, setOldLabel] = useState("cve_patch_old.c");
  const [newLabel, setNewLabel] = useState("cve_patch_new.c");
  const [options, setOptions] = useState<DiffOptions>(DEFAULT_OPTIONS);
  const [showNormalized, setShowNormalized] = useState(false);
  const [sidebarOpen, setSidebarOpen] = useState(false);
  const [pasteOpen, setPasteOpen] = useState(false);
  const [pasteOld, setPasteOld] = useState("");
  const [pasteNew, setPasteNew] = useState("");
  const [result, setResult] = useState<DiffResult | null>(null);
  const [activeRow, setActiveRow] = useState<number | null>(null);
  const semCursor = useRef(-1);

  useEffect(() => {
    invoke<{ old_src: string; new_src: string }>("load_demo_pair").then((pair) => {
      setOldSrc(pair.old_src);
      setNewSrc(pair.new_src);
    });
  }, []);

  useEffect(() => {
    if (!oldSrc && !newSrc) return;
    invoke<DiffResult>("compute_diff", {
      oldSrc,
      newSrc,
      options
    }).then((res) => {
      setResult(res);
      semCursor.current = -1;
      setActiveRow(null);
    });
  }, [oldSrc, newSrc, options]);

  const toggleOpt = (key: keyof DiffOptions) => {
    setOptions((prev) => ({ ...prev, [key]: !prev[key] }));
  };

  const jumpNextSemantic = () => {
    if (!result) return;
    const semanticRows = result.rows.filter(
      (r) => r.kind === "Added" || r.kind === "Removed" || r.kind === "Modified"
    );
    if (!semanticRows.length) return;
    semCursor.current = (semCursor.current + 1) % semanticRows.length;
    const target = semanticRows[semCursor.current].row_index;
    setActiveRow(target);
    document.querySelector(`[data-row="${target}"]`)?.scrollIntoView({ behavior: "smooth", block: "center" });
  };

  const renderSide = (side?: LineSide | null) => {
    if (!side) return null;
    if (showNormalized) return side.normalized_text;
    return side.tokens.map((tok, i) => {
      const cls = [
        tok.highlight !== "None" ? `tok-${tok.highlight}` : "",
        tok.normalized ? "tok-mapped" : ""
      ]
        .filter(Boolean)
        .join(" ");
      const title = tok.normalized
        ? `规范化: ${tok.normalized}${tok.counterpart ? ` ↔ ${tok.counterpart}` : ""}`
        : undefined;
      return cls ? (
        <span key={i} className={cls} title={title}>
          {tok.text}
        </span>
      ) : (
        <React.Fragment key={i}>{tok.text}</React.Fragment>
      );
    });
  };

  const handleLoadFile = (e: React.ChangeEvent<HTMLInputElement>, side: "old" | "new") => {
    const f = e.target.files?.[0];
    if (!f) return;
    const reader = new FileReader();
    reader.onload = () => {
      const txt = String(reader.result ?? "");
      if (side === "old") {
        setPasteOld(txt);
        setOldLabel(f.name);
      } else {
        setPasteNew(txt);
        setNewLabel(f.name);
      }
    };
    reader.readAsText(f);
  };

  const visibleRows =
    result?.rows.filter((r) => !(options.hide_noise_lines && r.kind === "NoiseOnly")) ?? [];

  return (
    <div className="app-shell">
      <header>
        <div className="brand">
          <span>IDA 伪代码补丁查看器</span>
          <span className="brand-badge">Hex-Rays 智能 Diff 引擎</span>
          <span style={{ fontWeight: 400, fontSize: 12, color: "var(--muted)" }}>
            {oldLabel} ↔ {newLabel}
          </span>
        </div>
        <div className="actions">
          <select
            onChange={(e) => {
              if (e.target.value === "cve_patch") {
                invoke<{ old_src: string; new_src: string }>("load_demo_pair").then((pair) => {
                  setOldSrc(pair.old_src);
                  setNewSrc(pair.new_src);
                  setOldLabel("cve_patch_old.c");
                  setNewLabel("cve_patch_new.c");
                });
              } else if (DEMOS[e.target.value]) {
                const d = DEMOS[e.target.value];
                setOldSrc(d.oldSrc);
                setNewSrc(d.newSrc);
                setOldLabel(d.oldLabel);
                setNewLabel(d.newLabel);
              }
            }}
          >
            <option value="cve_patch">示例: CVE 补丁 + 4类控制流重排</option>
            <option value="branch_invert">示例: if/else 分支反转</option>
            <option value="guard_clause">示例: Guard Clause vs 嵌套 if</option>
          </select>
          <button
            onClick={() => {
              setPasteOld(oldSrc);
              setPasteNew(newSrc);
              setPasteOpen(true);
            }}
          >
            📋 粘贴 / 导入文件
          </button>
          <button className="primary" onClick={jumpNextSemantic}>
            ⬇ 下一处真实修改
          </button>
          <button onClick={() => setSidebarOpen((v) => !v)}>🗺 变量/符号映射表</button>
        </div>
      </header>

      <div className="toolbar">
        <div className="toggles">
          {(
            [
              ["normalize_addresses", "地址符号归一化 (sub_/loc_)"],
              ["normalize_variables", "局部变量重编号 (v1..vN)"],
              ["ignore_comments", "忽略栈帧/注释"],
              ["align_control_flow", "控制流重排对齐 (4类)"],
              ["collapse_declarations", "声明区重排对齐"],
              ["simplify_ida_casts", "简化 IDA 强转/宏"],
              ["hide_noise_lines", "隐藏纯噪音行"]
            ] as [keyof DiffOptions, string][]
          ).map(([k, label]) => (
            <div
              key={k}
              className={`pill ${options[k] ? "active" : ""}`}
              onClick={() => toggleOpt(k)}
            >
              <span className="dot" />
              <span>{label}</span>
            </div>
          ))}
          <div
            className={`pill ${showNormalized ? "active" : ""}`}
            onClick={() => setShowNormalized((v) => !v)}
          >
            <span className="dot" />
            <span>显示归一化伪代码</span>
          </div>
        </div>

        {result && (
          <div className="stats">
            <span className="stat-chip stat-add">+{result.summary.semantic_added_rows} 新增</span>
            <span className="stat-chip stat-del">-{result.summary.semantic_removed_rows} 删除</span>
            <span className="stat-chip stat-mod">~{result.summary.semantic_modified_rows} 修改</span>
            <span className="stat-chip stat-noise">≈ {result.summary.noise_filtered_rows} 噪音已降权</span>
            <span className="stat-chip stat-cfg">⇄ {result.summary.cfg_reorders_aligned} 控制流对齐</span>
          </div>
        )}
      </div>

      <main>
        <div className="diff-container">
          <table className="diff-table">
            <thead>
              <tr>
                <th className="col-ln">旧行</th>
                <th>旧版伪代码 (Old)</th>
                <th className="col-ln">新行</th>
                <th>新版伪代码 (New)</th>
                <th className="col-tag">状态 / 控制流重排对齐</th>
              </tr>
            </thead>
            <tbody>
              {visibleRows.map((r) => (
                <tr
                  key={r.row_index}
                  data-row={r.row_index}
                  className={`diff-row row-${r.kind} ${activeRow === r.row_index ? "row-active" : ""}`}
                >
                  <td className="ln">{r.old_line?.line_no ?? ""}</td>
                  <td className="code code-old divider">{renderSide(r.old_line)}</td>
                  <td className="ln">{r.new_line?.line_no ?? ""}</td>
                  <td className="code code-new">{renderSide(r.new_line)}</td>
                  <td>
                    {r.kind === "NoiseOnly" && (
                      <span style={{ color: "var(--muted)", fontSize: 11 }}>≈ 仅噪音 </span>
                    )}
                    {r.kind === "Added" && (
                      <span style={{ color: "var(--green)", fontWeight: 600, fontSize: 11 }}>
                        + 真实新增{" "}
                      </span>
                    )}
                    {r.kind === "Removed" && (
                      <span style={{ color: "var(--red)", fontWeight: 600, fontSize: 11 }}>
                        - 真实删除{" "}
                      </span>
                    )}
                    {r.kind === "Modified" && (
                      <span style={{ color: "var(--yellow)", fontWeight: 600, fontSize: 11 }}>
                        ~ 真实修改{" "}
                      </span>
                    )}
                    {renderCfgBadge(r.cfg_tag)}
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>

        {sidebarOpen && result && (
          <aside className="sidebar">
            <h3>变量映射 ({result.summary.variable_mappings.length})</h3>
            {result.summary.variable_mappings.map(([id, o, n]) => (
              <div className="map-row" key={id}>
                <span className="map-id">{id}</span>
                <span>{o}</span>
                <span>{n}</span>
              </div>
            ))}
            <h3 style={{ marginTop: 14 }}>地址符号映射 ({result.summary.symbol_mappings.length})</h3>
            {result.summary.symbol_mappings.map(([id, o, n]) => (
              <div className="map-row" key={id}>
                <span className="map-id">{id}</span>
                <span>{o}</span>
                <span>{n}</span>
              </div>
            ))}
          </aside>
        )}
      </main>

      {pasteOpen && (
        <div className="modal-backdrop">
          <div className="modal">
            <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center" }}>
              <strong>粘贴或导入两份 IDA 伪代码</strong>
              <button onClick={() => setPasteOpen(false)}>✕</button>
            </div>
            <div className="paste-grid">
              <div>
                <div style={{ marginBottom: 6, fontSize: 12, color: "var(--muted)" }}>
                  旧版伪代码 (Old): <input type="file" onChange={(e) => handleLoadFile(e, "old")} />
                </div>
                <textarea value={pasteOld} onChange={(e) => setPasteOld(e.target.value)} />
              </div>
              <div>
                <div style={{ marginBottom: 6, fontSize: 12, color: "var(--muted)" }}>
                  新版伪代码 (New): <input type="file" onChange={(e) => handleLoadFile(e, "new")} />
                </div>
                <textarea value={pasteNew} onChange={(e) => setPasteNew(e.target.value)} />
              </div>
            </div>
            <div style={{ display: "flex", justifyContent: "flex-end", gap: 8 }}>
              <button onClick={() => setPasteOpen(false)}>取消</button>
              <button
                className="primary"
                onClick={() => {
                  setOldSrc(pasteOld);
                  setNewSrc(pasteNew);
                  setPasteOpen(false);
                }}
              >
                开始智能对比
              </button>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
