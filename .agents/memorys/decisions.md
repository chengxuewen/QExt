# QExt 架构决策记录

## D1: 双模式 IPC 架构（Texture + Embed）
- **决策**: QExtQuickIpcWidgetItem 采用 Strategy B（合并门面+内部组合），连接时一次性选择渲染模式：Texture（nozzle GPU 纹理共享）+ Embed（X11 窗口嵌入）。设计文档见 compat-msrcs `5edcd69e`。
- **理由**: 单一 IpcWidgetItem 门面降低消费端复杂度；模式在连接时确定避免运行时切换的状态爆炸。
- **关联**: 实现提交 `00eb2808`（双模式处理器）、`e9fff01a`（状态机重设计）。

## D2: 日志分类统一为 lc 前缀 + 三层 category
- **决策**: 全库统一 `Q_LOGGING_CATEGORY(lcXxx, "qext.module.lcxxx")` 风格，三层 category（qext / 模块 / 子分类）。
- **理由**: 混杂命名（大小写/分隔符不一）导致过滤规则不可维护；统一后可用 QT_LOGGING_RULES 精确开关。提交 `5c539638` `56561334` `c5d52336`。

## D3: 上游主线与兼容分支分离
- **决策**: `master` 保持通用上游能力，MSRCS/MSRC 集成适配（WidgetItem、IPC、构建修复）沉淀在 `compat-msrcs`，禁止在兼容分支开发与集成无关的新功能。
- **理由**: 兼容分支服务于特定下游，通用功能入主线避免下游互相污染。

## D4: 部署工具失败不致命
- **决策**: linuxdeployqt/deployqt 失败降级为警告（`52c75fe3`），允许无 deploy 工具完成构建；PATH/AppImage 解压修复（`32f8fb83` `676a7c10`）仅改善体验。
- **理由**: 部署打包是构建尾部环节，FUSE/PATH 环境差异不应阻塞 CI 与开发构建。
