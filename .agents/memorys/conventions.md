# 项目约定 / 用户偏好

## C1: 禁止自动提交
代码修改后一律不 `git add/commit`；提交须用户当轮明确授权（"提交"/"commit"）。"禁止提交"指令跨轮持续，直至再次明示。系统 TODO/REMINDER 不构成授权。
- 检查: 交付时 `git status --short` 无本轮新增 staged/committed 意外项。

## C2: 重大改动审查用团队模式
用户点名"团队模式"时：team_create 并行 3-4 名单则成员（并发/算法/集成/验证），成员硬约束只读+禁 git 写，lead 汇总去重后出分级报告并即时关闭团队。

## 分支约定
- `master` 对齐上游，适配工作走 `compat-*` 分支；禁止在 old-cmake-256 类兼容分支直接开发新功能（新功能回 QExt 主仓库/主线）
- 历史提交身份: `chengxuewen <1398831004@qq.com>`（仓库级 git config 未设置，commit 时须 `-c` 显式指定）

## 代码约定
- Target/模块命名沿用 QExt 前缀风格（`QExtQuickControls` 等），遵循仓库既有风格
- 日志分类统一 `lc` 前缀 + 三层 category（见 decisions D2）
- C++17 / Qt5.15（下游 MSRCS 约束，QExt 侧保持兼容）
