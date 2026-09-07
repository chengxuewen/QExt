# QExt 项目状态

> 最后更新: 2026-09-07

## 基本信息

| 项 | 值 |
|---|---|
| 仓库 | gitee.com/chengxuewen/QExt |
| 工作分支 | `compat-msrcs`（本地 detached @ `3b5ad501` = origin/compat-msrcs 顶端） |
| master | `67312cdd`（= origin/master），compat-msrcs 领先 21 提交、可 fast-forward |
| 工作树 | 干净 |

## 分支布局

| 分支 | 用途 |
|---|---|
| `master` | 上游主线（版本化 so 符号链接等基础能力） |
| `compat-msrcs` | MSRC/MSRCS 集成适配线（当前工作线，21 个提交） |
| `compat-*` / `dev-*` | 其他目标/实验分支 |

## compat-msrcs 主要工作（67312cdd → 3b5ad501）

| 主题 | 提交 | 摘要 |
|---|---|---|
| 双模式 IPC | `00eb2808` `e9fff01a` `5edcd69e` | IpcWidgetItem 状态机重设计 + 观察者状态机设计文档 |
| WidgetItem | `5b3fca34` `14d935a3` | 新增 WidgetItem/IpcWidgetItem + IPC 示例 + QPointer include |
| 崩溃/审查修复 | `376d24d6` `39621f79` | 崩溃修复 + 22 项代码审查修复 + QML 循环依赖解耦 |
| 日志分类系统 | `5c539638` `56561334` `c5d52336` | lc 前缀 + 三层 category 统一 |
| 软键盘 | `b3bbcb1c` | QML 软键盘弹出修复 |
| 打包/构建 | `32f8fb83` `676a7c10` `52c75fe3` `de47c567` | linuxdeployqt PATH/FUSE 修复 + 子构建告警抑制 |
| Toast | `74f11223` `3b5ad501` | SVG 图标 + Loader 冗余渲染/id 冲突修复 |

## 待办

- [ ] compat-msrcs 21 提交与 master 的合并策略待定（可 fast-forward）
- [ ] `.agents/` `.opencode/` AI 配置适配 QExt 后入库
