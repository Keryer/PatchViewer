# IDA Patch Viewer (`patch-viewer`)

面向 **IDA Pro (Hex-Rays)** 反编译伪代码的补丁差异对比工具（Patch Diffing Viewer），支持 **交互式 TUI / ANSI CLI** 与 **Desktop 桌面端**。

针对反编译伪代码对比中常见的“伪差异（False Positives）”与结构错位，内置双轨归一化与四类控制流重排对齐引擎：

1. **地址符号归一化**：自动识别 `sub_xxx`、`loc_xxx`、`locret_xxx`、`off_xxx`、`dword_xxx` / `qword_xxx` 等地址相关符号，按配对锚点映射到 `$SUB_1`、`$LOC_1`、`$DAT_1` 等规范化标识。
2. **局部变量与参数重编号**：识别 `v1..vN`、`result` 与 `a1..aN`，基于**可执行语句中的结构锚点**建立双向映射（插入一个新临时变量不会导致后续全部变量标红）。
3. **注释与栈帧偏移降噪**：剥离 `// [rsp+20h] [rbp-38h] BYREF`、`// eax` 等注释差异，并在原始代码展示中弱化标注为 `≈ NoiseOnly`。
4. **顶部变量声明区对齐**：按规范化类型与变量匹配声明区，避免寄存器分配变化引发的声明顺序差异。
5. **四类控制流重排对齐**：
   - `if / else` 分支反转（`if (c) A else B` ↔ `if (!c) B else A`）
   - Guard Clause（提前 `return/goto`）与嵌套 `if` 块展开对齐
   - `switch-case` 分支顺序洗牌对齐
   - `goto loc_xxx:` 基本块位置移动跨位置配对

---

## 目录结构

- `crates/patch-viewer-core`：核心引擎（词法与容错 AST 解析、双轨归一化、控制流对齐、行级/Token 级 Diff）
- `crates/patch-viewer-cli`：命令行工具（Ratatui 交互式 TUI、ANSI 彩色输出、JSON 导出、内置桌面 Web GUI 服务）
- `apps/desktop`：Tauri v2 + React + TypeScript 桌面客户端源码
- `examples/`：内置测试样例（`cve_patch_old.c` 与 `cve_patch_new.c`，包含漏洞补丁与全部 4 类控制流重排）

---

## 快速使用

> 如果本机安装了 `w64devkit`，项目根目录的 `.cargo/config.toml` 已自动配置 `-C link-self-contained=yes` 以确保可直接编译运行。

### 1. 运行单元测试

```powershell
cargo test --workspace
```

### 2. CLI 交互式 TUI 查看器（默认）

```powershell
# 直接使用内置 IDA CVE 补丁样例体验
cargo run -p patch-viewer-cli -- --demo

# 对比任意两份导出的 IDA 伪代码文件
cargo run -p patch-viewer-cli -- old_func.c new_func.c
```

TUI 快捷键：
- `1`：地址符号归一化开关 (`sub_` / `loc_` / `dword_`)
- `2`：局部变量重编号开关 (`v1..vN` / `a1..aN`)
- `3`：忽略注释与栈帧偏移开关
- `4`：控制流重排对齐开关 (4 类)
- `5`：顶部声明区重排对齐开关
- `6`：简化 IDA 冗余强转/宏 (`LOBYTE`, `(unsigned int)`)
- `7`：占位填充对齐模式开关（缺失侧自动补齐 `if ( true ) { pass; }` 等结构占位）
- `h`：隐藏/显示纯噪音行
- `v`：切换显示原始伪代码 / 规范化伪代码
- `Tab`：切换并排 (Side-by-Side) / 统一 (Unified) 视图
- `m`：弹出/关闭 变量与地址符号映射表
- `n` / `p`：跳转到下一处 / 上一处真实语义变更
- `j` / `k` / `↑` / `↓` / `PgUp` / `PgDn`：滚动，`q` 退出

### 3. 非交互式 ANSI 彩色输出 / JSON 导出

```powershell
# 终端并排输出并附带映射表
cargo run -p patch-viewer-cli -- --ansi --mappings examples/cve_patch_old.c examples/cve_patch_new.c

# 统一视图 + 查看规范化代码
cargo run -p patch-viewer-cli -- --ansi --unified --show-normalized examples/cve_patch_old.c examples/cve_patch_new.c

# 导出结构化 JSON
cargo run -p patch-viewer-cli -- --json examples/cve_patch_old.c examples/cve_patch_new.c
```

### 4. Desktop 桌面端

#### 方式 A：单二进制直接拉起桌面窗口（无需额外构建前端）

```powershell
# 自动启动本地服务并用 Edge App 模式打开桌面窗口
cargo run -p patch-viewer-cli -- --gui

# 或仅启动本地 Web 服务（默认 3780 端口）
cargo run -p patch-viewer-cli -- --web 3780
```

#### 方式 B：Tauri v2 原生桌面打包 (`apps/desktop`)

```powershell
cd apps/desktop
npm install
npm run tauri dev
```
