---
name: openspec-propose
description: >-
  Propose a new change for QExt with structured artifacts (proposal, design,
  tasks). Generates .sisyphus/plans/<name>/proposal.md + design.md + tasks.md.
  Use when the user describes what they want to build and needs a complete proposal ready for implementation.
license: MIT
compatibility: Designed for Claude Code, GitHub Copilot, and similar agents.
disable-model-invocation: false
metadata:
  author: openspec
  version: "2.0"
  category: workflow
  project: QExt
---

# OpenSpec Propose — QExt

Create a structured change proposal for QExt. Produce three artifacts that together answer
"what are we building, how does it fit, and what's the plan?"

When ready to implement, follow with `/openspec-apply`.

---

**Input**: The user describes a feature, fix, or refactor. Do not start without a feature description.

---

## Steps

### 1. Confirm the change name

Ask: "What should we call this change? (kebab-case, e.g. `add-quick-component`)"

**DO NOT auto-generate without asking.** Validate: lowercase letters, digits, hyphens only.

### 2. Gather context

Before writing any artifact, understand the existing surface area:

#### a. Read relevant specs

Search `openspec/specs/` for specs related to the change by package prefix
(如 `qextquickcontrols`, `cmake-infra`). Read every spec whose package overlaps. Note if no relevant spec exists.

#### b. Read project memory

- `.agents/memorys/status.md` — current branch, work status, known gaps
- `.agents/memorys/decisions.md` — D1-D50 architecture decisions
- `.agents/memorys/pitfalls.md` — known sharp edges (QML Singleton、d-pointer、deployqt traps)
- `.agents/memorys/conventions.md` — naming, 分支策略, 用户偏好

#### c. Assess affected layers

| Layer | Location | When affected |
|-------|----------|---------------|
| **组件库** | `libs/` (QuickControls 等) | 新 QML/Widget 组件、现有组件修改 |
| **构建基础设施** | `cmake/` | qext_add_library、FindWrap、install 机制变化 |
| **IPC** | IPC 相关 lib | 双模式（Texture/Embed）状态机与处理器 |
| **示例** | `examples/` | 组件用法演示更新 |

#### d. Assess branch impact

| 分支 | 用途 |
|-----------|---------|
| **master** | 上游主线（通用能力） |
| **compat-msrcs** | MSRCS/MSRC 下游集成适配 |

适配下游专属的改动走 compat 分支；通用组件能力走 master。

### 3. Create the proposal directory

```bash
mkdir -p .sisyphus/plans/<change-name>
```

### 4. Write proposal.md

Create `.sisyphus/plans/<change-name>/proposal.md` with these sections:
- **What** — 2-4 sentences, specific
- **Why** — problem, use case, gap
- **Scope** — in scope / out of scope
- **Layers Affected** — checklist: 组件库 / 构建基础设施 / IPC / 示例
- **Branch Impact** — master: yes/no, compat-msrcs: yes/no（禁止在兼容分支混入无关新功能）
- **Existing Specs** — list `openspec/specs/<name>.md` with one-line description each
- **New Specs Needed** — list or "None"
- **Risks** — 2-4 bullet points (线程安全、QML 引擎时序、构建兼容、下游 ABI)
- **Success Criteria** — how we know it's done
- **References** — links to issues, design docs, external references

### 5. Write design.md

Create `.sisyphus/plans/<change-name>/design.md` with these sections:
- **Architecture** — ASCII diagram or text description showing modules, data flow, ownership
- **Files to Touch** — Create / Modify / Delete sub-tables with file paths and purpose
- **Data Flow** — critical path from entry to exit
- **Integration Points** — lib 边界、CMake target 边界、QML 模块边界
- **C++/Qt Specifics** — new classes/Q_PROPERTY, signal wiring, d-pointer 所有权, lc 日志分类, 线程亲和性
- **Error Handling** — 错误传播路径与降级行为
- **Testing Strategy** — checklist: C++ unit, QML smoke, 示例验证, 构建门禁
- **Dependencies** — new 3rdparty wraps (or "None")

### 6. Write tasks.md

Create `.sisyphus/plans/<change-name>/tasks.md`. Tasks must be **atomic, ordered, independently testable** — each produces one verifiable result. Structure in phases:

```markdown
# Tasks: <Change-Name>

## Phase 1: Foundation

- [ ] **Add `<class>` to <lib>**
  - File: `libs/<lib>/src/<file>.h/.cpp`
  - Verify: cmake configure + build <lib> target

## Phase 2: Integration

- [ ] **Wire into existing component / CMake**
  - File: `libs/<lib>/CMakeLists.txt`
  - Verify: build passes, install rules intact

## Phase 3: Tests

- [ ] **Add unit tests** (AAA pattern)
  - File: same lib tests dir
  - Verify: ctest passes

## Phase 4: Documentation & Cleanup

- [ ] **Write/update spec file**
  - File: `openspec/specs/<package>/spec.md` (SDD format: ID→precondition→operation→expected→edge cases)

- [ ] **Update project memory** (after implementation)
  - `.agents/memorys/status.md`, `decisions.md`, `pitfalls.md` as applicable
```

Adjust phases to fit the change: single-file fix → 3 tasks; multi-module feature → 15+ tasks across 5 phases.

### 7. Present and iterate

Display summary — change name, artifact list, line counts. Let user request changes, iterate until approved.

---

## File Path Conventions

| Purpose | Path |
|---------|------|
| 组件库源码 | `libs/<lib>/src/` |
| 构建基础设施 | `cmake/` |
| 示例 | `examples/` |
| Specs | `openspec/specs/<package>/` |
| Plans | `.sisyphus/plans/<change-name>/` |
| Tests | 各 lib tests 目录 |

---

## QExt-Specific Guidelines

### Module references

| Module | Path | Type |
|---------|------|------|
| QuickControls | `libs/QExtQuickControls/` | QML 组件库 (Toast、软键盘等) |
| Core | `libs/QExtCore/` | C++ 基础库 |
| CMake infra | `cmake/` | qext_add_library、FindWrap、install |

### Build commands

```bash
cmake --build build/<dir>                      # 按 preset/环境构建
ctest --test-dir build/<dir>                   # 测试
```

### C++/Qt conventions

- C++17 / Qt 5.15（下游 MSRCS 兼容约束）
- d-pointer + Q_DECLARE_PRIVATE 配对（缺 d_ptr = 野指针崩溃，见 pitfalls）
- 日志分类 lc 前缀 + 三层 category
- QML 模块内文件禁止 import 自身模块（Singleton 循环依赖）
- Q_INVOKABLE/slot 是反射 ABI 契约，删除前全局搜索 invokeMethod 引用

---

## Guardrails

- **Always ask for the change name** — do not generate one without user confirmation
- **Read specs before proposing** — ignoring existing SDD contracts is waste
- **Layer assessment must be explicit** — "maybe affects 构建基础设施" is not acceptable; decide and document
- **Branch impact must be explicit** — master? compat-msrcs? Document the split
- **Tasks must be atomic** — each task produces one verifiable result (compiling code, passing tests)
- Always reference actual QExt file paths and lib names
- If context is critically unclear, ask — but prefer reasonable decisions to keep momentum
- If a proposal with that name already exists, ask to continue or create new
- Do NOT propose changes to `version.txt` — versioning is user-managed
- Do NOT propose changes to external dependencies — separate repositories
- Verify each artifact file exists after writing before proceeding
