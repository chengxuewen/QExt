# Development Constraints

> QExt 项目约束。

## Git 提交规则

- 兼容分支（compat-msrcs 等）提交无需 Change-Id；提交身份 `chengxuewen <1398831004@qq.com>`（仓库级 config 未设置，commit 时 `-c` 显式指定）
- 依赖变更（submodule/3rdparty）与配套构建改动须同一提交，避免半更新状态
- `git status` 检查：交付时无本轮新增 staged/committed 意外项（C1）
