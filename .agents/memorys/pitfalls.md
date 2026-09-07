# QExt 踩坑记录

## PIT-1: QML Singleton 模块自 import 循环依赖 → SIGSEGV (2026-06)
- **症状**: QML 模块内 `.qml` 文件 import 自己所在模块，Singleton 初始化循环依赖，启动 SIGSEGV。
- **解法**: Loader 延迟加载解耦（`376d24d6`）；模块内文件禁止 import 自身模块。

## PIT-2: Q_DECLARE_PRIVATE_D 野指针崩溃 (2026-06)
- **症状**: `Q_DECLARE_PRIVATE` 缺少对应 `d_ptr` 成员时，命中 `QObject::d_ptr`（偏移错位），访问野指针崩溃（`qextQuickIpcWidgetItem.h:74`）。
- **解法**: Q_DECLARE_PRIVATE 必须配对声明 `d_ptr`；显式 d 指针用 Q_DECLARE_PRIVATE_D 时同样检查成员存在。

## PIT-3: mapToGlobal margin 偏移 (2026-06)
- **症状**: WidgetItem 坐标换算含 margin 偏移，弹出定位错位（`qextQuickWidgetItem.cpp:196`）。
- **解法**: mapToGlobal 换算扣减 margin；嵌入场景下注意 native 窗口几何与 widget 几何差异。

## PIT-4: Q_INVOKABLE 移除 → 反射调用静默失败 (2026-06)
- **症状**: 移除 Q_INVOKABLE 标记后 `QMetaObject::invokeMethod` 反射调用不再解析，无编译错误、无运行时报错。
- **解法**: Q_INVOKABLE/slot 标记视为公开 ABI 契约，删除前全局搜索 invokeMethod 引用。

## PIT-5: linuxdeployqt FUSE 依赖 (2026-06)
- **症状**: linuxdeployqt 单文件 AppImage 依赖 FUSE，容器/无 FUSE 环境直接失败。
- **解法**: `--appimage-extract` 解压运行（`32f8fb83`）+ deployqt PATH 注入（`676a7c10`）+ 失败降级为警告（`52c75fe3`）。

## PIT-6: 子构建 CMake 告警洪水 (2026-06)
- **症状**: FindWrap 类三方子构建 cmake_minimum_required < 3.10 弃用告警 + Manually-specified variables 告警刷屏，掩盖真实错误。
- **解法**: FindWrap configure 调用统一加 `-Wno-deprecated` 与 `--no-warn-unused-cli`（`de47c567`）。
