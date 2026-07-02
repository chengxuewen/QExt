# QExtQuickIpcWidgetItem 观察者状态机 + ProcessInterface API 设计文档

> **文档定位**: 架构设计文档（不含代码实现）
> **关联 ADR**: ADR-026 (ProcessInterface 内嵌 struct), ADR-027 (ProcessHandler 移出库), ADR-028/031 (d_ptr 修正), ADR-032 (QML Singleton 解耦), ADR-033 (双模式 IPC 架构)
> **关联计划**: `.agents/plans/dual-mode-ipc-redesign.md`
> **设计阶段**: Wave 1, Task T2

---

## 目录

1. [设计概述](#1-设计概述)
2. [状态机](#2-状态机)
3. [连接纪元 (Connection Epoch)](#3-连接纪元-connection-epoch)
4. [ProcessInterface API 表](#4-processinterface-api-表)
5. [EmbedIpcHandler 设计](#5-embedipchandler-设计)
6. [NozzleIpcHandler 设计](#6-nozzleipchandler-设计)
7. [FrameTransportImpl 设计](#7-frametransportimpl-设计)
8. [回调时序规则](#8-回调时序规则)
9. [createDefaultHandler() 工厂](#9-createdefaulthandler-工厂)
10. [删除的死代码](#10-删除的死代码)
11. [审查修复对照表 (C1-C12)](#11-审查修复对照表-c1-c12)

---

## 1. 设计概述

### 1.1 背景

`QExtQuickIpcWidgetItem` 当前使用纯虚 `ProcessInterface`（12 个纯虚方法）作为进程通信接口。嵌入模式已 90% 可用（`asyncSetWidgetWId` 中 `QWindow::fromWinId` + `QWidget::createWindowContainer`），但缺乏：

- 显式连接状态管理（状态隐含在 `isRunning()`/`isStopped()` 中）
- 过期回调保护（进程崩溃后旧回调仍可能触发）
- Texture 渲染模式预留（nozzle GPU 纹理共享）
- 统一的命令通道抽象

### 1.2 架构策略

**Strategy B — 合并门面 + 内部组合**（ADR-033）：

```
QExtQuickIpcWidgetItem (门面)
  └─ ProcessInterface (内嵌 struct, ADR-026)
       ├─ EmbedIpcHandler     (具体类, 总是可用)
       └─ NozzleIpcHandler    (stub, #ifdef QEXT_HAVE_NOZZLE, 默认 OFF)
            └─ FrameTransportImpl (内部组合, 不可见)
```

- **连接时一次性模式选择**：Auto / Texture / Embed，不支持运行时切换
- **nozzle 集成**：`#ifdef QEXT_HAVE_NOZZLE` 条件编译，默认 OFF
- **ProcessInterface** 保留为内嵌 struct（ADR-026 精神），不提取为独立文件

### 1.3 设计约束

| 约束 | 说明 |
|------|------|
| C++17 | 项目标准，GCC 9 兼容 |
| Qt 5.15 | 不使用 Qt6 API |
| Q_INVOKABLE | `setWidget`/`widget`/`rootWindow` 上的 Q_INVOKABLE 不可移除（反射调用依赖） |
| Q_DECLARE_PRIVATE_D | 使用 `dd_ptr` 复用父类私有指针（ADR-031） |
| 线程安全 | 所有回调经 `Qt::QueuedConnection` 派发（C5 修复） |

---

## 2. 状态机

### 2.1 状态定义

| 状态 | 说明 | 典型表现 |
|------|------|----------|
| **Disconnected** | 初始状态 / 断开完成 | 无子进程，无嵌入窗口，`mCachedWId == 0` |
| **Connecting** | 正在建立连接 | 进程已启动，等待子进程回传 WId（或 nozzle 握手完成） |
| **Connected** | 连接建立 | WId 已接收，`createWindowContainer` 完成，子窗口可见 |
| **Disconnecting** | 正在断开 | 正在停止进程 + 清理窗口资源 |

### 2.2 状态转移图

```
                          start() / probe()==true
    ┌──────────────┐ ──────────────────────────> ┌──────────────┐
    │ Disconnected │                              │  Connecting  │
    └──────────────┘ <────────────────────────── └──────────────┘
          ▲                                           │
          │                                           │ WId 回调到达
          │                                           │ createWindowContainer 完成
          │                                           ▼
          │                                      ┌──────────────┐
          │   stop() / probe()==false /          │   Connected  │
          │   进程崩溃                             └──────────────┘
          │                                           │
          │   stop()                                  │
          └──────────────────────────┐               │
                                      ▼               │ stop()
               ┌─────────────────────────┐           │
               │     Disconnecting       │ <─────────┘
               └─────────────────────────┘
                      │
                      │ 清理完成
                      ▼
               ┌──────────────┐
               │ Disconnected │
               └──────────────┘
```

### 2.3 转移条件

| From | To | 触发条件 |
|------|----|----------|
| Disconnected | Connecting | `start()` 调用 → `probe()` 返回 true |
| Connecting | Connected | WId 回调到达且 `createWindowContainer` 成功 |
| Connecting | Disconnected | `probe()` 返回 false（启动超时或进程立即退出） |
| Connected | Disconnecting | `stop()` 或 `disconnect()` 被调用 |
| Connected | Disconnected | 进程崩溃检测（`isAlive()` 返回 false，由 QProcess::finished 或 nozzle 心跳超时触发） |
| Disconnecting | Disconnected | 清理完成（窗口分离 + 进程终止 + 回调解绑） |

### 2.4 状态机实现要点

1. **状态存储**：`ProcessInterface::State` 枚举，存于 handler 内部（非 PIMPL d_ptr），因为状态属于 handler 而非 widget 本身
2. **状态变更通知**：handler 内部状态变更后，通过 `setReadyCallback` / `setLostCallback` 通知 widget 层
3. **幂等保护**：`stop()` 在 Disconnected 状态下是 no-op；`start()` 在 Connected/Connecting 状态下是 no-op
4. **异常路径**：Connecting 状态下进程崩溃 → 直接进入 Disconnecting → Disconnected（跳过 Connected）

### 2.5 与当前代码的对比

当前代码（修改前）隐含状态：
- `isStopped()` == true → 等价于 Disconnected
- `isRunning()` == true 但 `mCachedWId == 0` → 等价于 Connecting
- `isRunning()` == true 且 `mCachedWId != 0` → 等价于 Connected

新设计将隐含状态提升为显式状态，消除了 `isRunning()`/`isStopped()` 二义性查询（这两个方法将被删除，见 §10）。

---

## 3. 连接纪元 (Connection Epoch)

### 3.1 设计动机

进程崩溃后，旧的异步回调（如 `asyncSetWidgetWId` 信号）可能仍在事件队列中排队。如果新连接已建立，旧回调会导致：
- 嵌入错误的窗口 WId
- 访问已释放的 QWindow 对象
- 状态机混乱

### 3.2 设计方案

```cpp
// 连接纪元：单调递增的 uint64 计数器
// 每次 connect 尝试（start() → Connecting 转移）时递增
using ConnectionEpoch = uint64_t;
```

**生命周期**：

1. **递增时机**：`start()` 被调用且通过 `probe()` 检查后，epoch 自增
2. **回调携带**：所有异步回调（WId 回调、Ready 回调、Lost 回调、FrameAvailable 回调）创建时捕获当前 epoch 值
3. **过期检查**：回调被触发时，比较捕获的 epoch 与当前 epoch：
   - 相等 → 执行回调
   - 不等 → 丢弃回调（stale callback），记录日志
4. **重置**：不重置。epoch 只增不减，保证全局唯一性

### 3.3 纪元传播路径

```
start() → epoch++ → handler 记录 currentEpoch
  ↓
handler 启动子进程 / nozzle 握手
  ↓
子进程回传 WId（携带创建时的 epoch）
  ↓
widget 层回调：if (callbackEpoch == currentEpoch) { /* 执行 */ }
```

### 3.4 与信号系统的集成

当前 `asyncSetWidgetWId` 信号使用 `QPrivateSignal`，无法携带 epoch 参数。设计方案有两种选择：

| 方案 | 说明 | 优缺点 |
|------|------|--------|
| **A: 信号携带 epoch** | `asyncSetWidgetWId(quintptr wId, ConnectionEpoch epoch, QPrivateSignal)` | 精确，但需改信号签名 |
| **B: handler 内检查** | 回调在 handler 内检查 epoch，仅通过后才 emit 信号 | 不改信号，但 handler 需持有 epoch 引用 |

**推荐方案 B**：handler 在触发回调前检查 epoch，仅通过后才调用 `setWIdCallback` 注册的函数。这样信号签名不变，epoch 检查集中在 handler 内。

### 3.5 进程崩溃场景示例

```
时刻 T1: start() → epoch=1 → 启动进程A
时刻 T2: 进程A 回传 WId → callback(epoch=1) → currentEpoch=1 ✓ → 嵌入成功
时刻 T3: stop() → 清理
时刻 T4: start() → epoch=2 → 启动进程B
时刻 T5: 进程A 的延迟 WId 回调到达 → callback(epoch=1) → currentEpoch=2 ✗ → 丢弃
```

---

## 4. ProcessInterface API 表

### 4.1 结构定义

`ProcessInterface` 保留为 `QExtQuickIpcWidgetItem` 的内嵌 struct（ADR-026）。

```cpp
// 在 qextQuickIpcWidgetItem.h 中
class QExtQuickIpcWidgetItem : public QExtQuickWidgetItem
{
    // ...
public:
    struct ProcessInterface
    {
        using SharedPtr = QSharedPointer<ProcessInterface>;
        using ConnectionEpoch = uint64_t;

        enum Command { Show, Resize, Custom = 1000 };

        virtual ~ProcessInterface() = default;

        // === 生命周期 ===
        virtual bool start() = 0;          // 无参数，配置来自 setProcessPath/setProcessArgs
        virtual void stop() = 0;
        virtual bool probe() = 0;          // 探测连接可行性
        virtual bool isAlive() const = 0;  // 连接是否活跃
        virtual void disconnect() = 0;     // 断开连接（不终止进程）

        // === 回调注册 ===
        virtual void setWIdCallback(std::function<void(quintptr)> cb) = 0;
        virtual void setLogCallback(std::function<void(const QString &)> cb) = 0;
        virtual void setReadyCallback(std::function<void()> cb) = 0;   // Connected 通知
        virtual void setLostCallback(std::function<void()> cb) = 0;    // 断开/崩溃通知

        // === 命令通道 ===
        virtual void sendShowCommand() = 0;
        virtual void sendResizeCommand(int width, int height) = 0;
        virtual void *commandChannel() = 0;  // 底层通道指针（QProcess*, nozzle handle 等）

        // === Texture 帧传输（stub，默认返回 false/nullptr） ===
        virtual bool initFrameTransport() = 0;
        virtual void shutdownFrameTransport() = 0;
        virtual bool isFrameTransportAvailable() const = 0;
        virtual void *acquireFrame() = 0;
        virtual void releaseFrame(void *handle) = 0;
        virtual void setFrameAvailableCallback(std::function<void()> cb) = 0;
        virtual void destroyGlResources() = 0;
    };
    // ...
};
```

### 4.2 完整方法表

| 方法 | 签名 | 默认返回值 | EmbedIpcHandler 实现 | NozzleIpcHandler (未来) |
|------|------|-----------|----------------------|------------------------|
| **start** | `bool start()` | `false` | 从 `m_processPath`/`m_processArgs` 启动 QProcess；`waitForStarted(5000)`；成功后状态→Connecting | nozzle 握手；成功后状态→Connecting |
| **stop** | `void stop()` | — | `m_process->terminate()` → `waitForFinished(3000)` → `kill()` fallback；状态→Disconnecting→Disconnected | nozzle 断开 + 资源清理；状态转移同 |
| **probe** | `bool probe()` | `false` | 检查 `m_processPath` 非空 + `QProcess::NotRunning`（可启动）| 检查 nozzle 连接器可用 + 未连接 |
| **isAlive** | `bool isAlive() const` | `false` | `m_cachedWId != 0 && m_process->state() == QProcess::Running` | nozzle 心跳在窗口内 + 连接有效 |
| **disconnect** | `void disconnect()` | — | `m_process->terminate()`；状态→Disconnecting→Disconnected（与 stop 类似但语义上是"断开"而非"终止"） | nozzle 断开，不终止进程 |
| **setWIdCallback** | `void setWIdCallback(std::function<void(quintptr)>)` | — | 存储 callback；WId 从 stdout 解析后调用（携带 epoch 检查） | 不适用（nozzle 不通过 WId 嵌入）；callback 不触发 |
| **setLogCallback** | `void setLogCallback(std::function<void(const QString &)>)` | — | 存储 callback；stdout/stderr 解析后调用 | nozzle 日志通道转发 |
| **setReadyCallback** | `void setReadyCallback(std::function<void()>)` | — | 存储 callback；`createWindowContainer` 完成后触发 | nozzle 帧传输就绪后触发 |
| **setLostCallback** | `void setLostCallback(std::function<void()>)` | — | 存储 callback；`QProcess::finished` 信号触发 | nozzle 心跳超时触发 |
| **sendShowCommand** | `void sendShowCommand()` | — | `m_process->write(">>>SHOW<<<\n")` | nozzle 命令通道发送 Show |
| **sendResizeCommand** | `void sendResizeCommand(int, int)` | — | `m_process->write(">>>SIZE:w,h<<<\n")` | nozzle 命令通道发送 Resize |
| **commandChannel** | `void *commandChannel()` | `nullptr` | 返回 `static_cast<void*>(m_process.data())` | 返回 nozzle 命令通道 handle |
| **initFrameTransport** | `bool initFrameTransport()` | `false` | `return false`（Embed 模式不支持） | `m_transport->init()`；成功返回 true |
| **shutdownFrameTransport** | `void shutdownFrameTransport()` | — | no-op | `m_transport->shutdown()` |
| **isFrameTransportAvailable** | `bool isFrameTransportAvailable() const` | `false` | `return false` | `return m_transport && m_transport->isAvailable()` |
| **acquireFrame** | `void *acquireFrame()` | `nullptr` | `return nullptr` | `return m_transport->acquireFrame()` |
| **releaseFrame** | `void releaseFrame(void *handle)` | — | no-op（handle 永远为 nullptr） | `m_transport->releaseFrame(handle)` |
| **setFrameAvailableCallback** | `void setFrameAvailableCallback(std::function<void()>)` | — | 存储 callback 但永不触发 | 转发到 `m_transport->setFrameAvailableCallback()` |
| **destroyGlResources** | `void destroyGlResources()` | — | no-op | `m_transport->destroyGlResources()` |

### 4.3 Command 枚举

```cpp
enum Command { Show, Resize, Custom = 1000 };
```

- `Show`：通知子进程显示窗口
- `Resize`：通知子进程调整窗口尺寸
- `Custom = 1000`：用户自定义命令起始值，避免与内置命令冲突

**用途**：`sendShowCommand()` 和 `sendResizeCommand()` 是内置便捷方法。用户可通过 `commandChannel()` 获取底层通道，自行发送 `Custom` 命令。

### 4.4 start() 签名变更

| 修改前 | 修改后 |
|--------|--------|
| `bool start(const QString &path, const QStringList &args)` | `bool start()` |

**原因**：
- `processPath` 和 `processArgs` 已是 `QExtQuickIpcWidgetItem` 的 Q_PROPERTY
- 当前 `setProcessInterface()` 中通过 `setConfig()` 传播路径参数，但 `setConfig` 被列为死代码删除
- 新方案：handler 在 `start()` 内部从 widget 层获取 `processPath`/`processArgs`（通过构造时传入的引用或 weak pointer）
- handler 构造时接收 widget 的 d_ptr 或直接接收 path/args 引用

### 4.5 方法分类汇总

| 类别 | 方法数 | 方法列表 |
|------|--------|----------|
| 生命周期 | 5 | start, stop, probe, isAlive, disconnect |
| 回调注册 | 4 | setWIdCallback, setLogCallback, setReadyCallback, setLostCallback |
| 命令通道 | 3 | sendShowCommand, sendResizeCommand, commandChannel |
| Texture 帧传输 | 7 | initFrameTransport, shutdownFrameTransport, isFrameTransportAvailable, acquireFrame, releaseFrame, setFrameAvailableCallback, destroyGlResources |
| 基础设施 | 1 | enum Command |
| **总计** | **20 方法 + 1 枚举** | |

---

## 5. EmbedIpcHandler 设计

### 5.1 定位

`EmbedIpcHandler` 是库提供的**具体实现类**，始终可用（无条件编译）。实现 X11 窗口嵌入模式（当前已 90% 工作的 `asyncSetWidgetWId` 逻辑）。

### 5.2 类设计

```
EmbedIpcHandler : public QExtQuickIpcWidgetItem::ProcessInterface
│
├─ 继承 QObject（用于 QProcess 信号槽）
├─ 继承 ProcessInterface（实现所有纯虚方法）
│
├─ 成员:
│   ├─ QPointer<QProcess> m_process          // 子进程管理
│   ├─ quintptr m_cachedWId{0}               // 缓存的窗口 ID
│   ├─ ConnectionEpoch m_epoch{0}            // 连接纪元
│   ├─ State m_state{Disconnected}           // 状态机
│   ├─ std::function<void(quintptr)> m_wIdCallback
│   ├─ std::function<void(const QString&)> m_logCallback
│   ├─ std::function<void()> m_readyCallback
│   ├─ std::function<void()> m_lostCallback
│   └─ QString m_processPath, m_processArgs  // 启动参数（从 widget 获取）
│
└─ 无 m_transport 成员（Embed 模式不需要 FrameTransportImpl）
```

### 5.3 关键方法行为

#### start()

```cpp
bool start()
{
    if (m_state != Disconnected) return false;  // 幂等保护
    if (m_processPath.isEmpty()) return false;
    
    m_epoch++;                                   // 纪元递增
    m_state = Connecting;
    
    m_process->setWorkingDirectory(...);
    m_process->start(m_processPath, m_processArgs);
    if (!m_process->waitForStarted(5000)) {
        m_state = Disconnected;
        return false;
    }
    return true;
}
```

#### probe()

```cpp
bool probe()
{
    return !m_processPath.isEmpty() 
        && m_state == Disconnected;
}
```

#### isAlive()

```cpp
bool isAlive() const
{
    return m_cachedWId != 0 
        && m_process 
        && m_process->state() == QProcess::Running;
}
```

#### sendShowCommand() / sendResizeCommand()

```cpp
void sendShowCommand()
{
    if (!isAlive()) return;
    m_process->write(">>>SHOW<<<\n");
}

void sendResizeCommand(int w, int h)
{
    if (!isAlive()) return;
    m_process->write(QString(">>>SIZE:%1,%2<<<\n").arg(w).arg(h).toUtf8());
}
```

#### commandChannel()

```cpp
void *commandChannel()
{
    return static_cast<void*>(m_process.data());
}
```

#### 帧传输方法（全部返回 false/nullptr）

```cpp
bool initFrameTransport() { return false; }
void shutdownFrameTransport() {}
bool isFrameTransportAvailable() const { return false; }
void *acquireFrame() { return nullptr; }
void releaseFrame(void *) {}
void setFrameAvailableCallback(std::function<void()>) {}  // 存储但不触发
void destroyGlResources() {}
```

### 5.4 stdout 解析（WId 回调）

保持当前 `QProcessHandler` 示例中的正则解析模式：

```cpp
void onStdout()
{
    while (m_process->canReadLine()) {
        QString line = QString::fromUtf8(m_process->readLine()).trimmed();
        // >>>WID:12345<<<
        static QRegularExpression widRx(">>>WID:(\\d+)<<<");
        auto match = widRx.match(line);
        if (match.hasMatch()) {
            quintptr wid = match.captured(1).toULongLong();
            ConnectionEpoch callbackEpoch = m_epoch;  // 捕获当前纪元
            // 通过 QueuedConnection 负载到主线程
            QMetaObject::invokeMethod(this, [=]() {
                if (callbackEpoch != m_epoch) return;  // 过期检查
                m_cachedWId = wid;
                if (m_wIdCallback) m_wIdCallback(wid);
            }, Qt::QueuedConnection);
        } else {
            if (m_logCallback) m_logCallback("[stdout] " + line);
        }
    }
}
```

### 5.5 进程崩溃处理

```cpp
void onProcessFinished(int code, QProcess::ExitStatus status)
{
    Q_UNUSED(code);
    Q_UNUSED(status);
    
    ConnectionEpoch callbackEpoch = m_epoch;
    QMetaObject::invokeMethod(this, [=]() {
        if (callbackEpoch != m_epoch) return;  // 过期检查
        m_cachedWId = 0;
        m_state = Disconnected;
        if (m_lostCallback) m_lostCallback();  // 通知 widget 层
    }, Qt::QueuedConnection);
}
```

### 5.6 与当前 QProcessHandler 的区别

| 维度 | 当前 QProcessHandler（示例代码） | 新 EmbedIpcHandler（库代码） |
|------|----------------------------------|-------------------------------|
| 位置 | `examples/widget/ipcwidgetitem/main.cpp` | QExt 库 `source/items/` 目录 |
| 状态管理 | 隐含（`isRunning`/`isStopped`） | 显式状态机 |
| 纪元保护 | 无 | 有（ConnectionEpoch） |
| 回调线程安全 | 直接调用（可能跨线程） | QueuedConnection + epoch 检查 |
| 帧传输 | 不涉及 | 返回 false/nullptr（占位） |
| Ready/Lost 回调 | 无 | 有（setReadyCallback/setLostCallback） |
| 启动参数 | `start(path, args)` 传入 | `start()` 无参，从 widget 层获取 |

---

## 6. NozzleIpcHandler 设计

### 6.1 定位

`NozzleIpcHandler` 是 Texture 渲染模式的处理器，当前阶段为**桩 (stub)**，仅在 `#ifdef QEXT_HAVE_NOZZLE` 下编译。默认 OFF。

### 6.2 条件编译

```cpp
#ifdef QEXT_HAVE_NOZZLE
class NozzleIpcHandler : public QExtQuickIpcWidgetItem::ProcessInterface
{
    // ...
};
#endif // QEXT_HAVE_NOZZLE
```

**`QEXT_HAVE_NOZZLE` 定义位置**：QExt CMake 配置（`QExtGlobalConfig.cmake` 或编译选项），默认不定义。

### 6.3 类设计

```
#ifdef QEXT_HAVE_NOZZLE
NozzleIpcHandler : public QExtQuickIpcWidgetItem::ProcessInterface
│
├─ 成员:
│   ├─ std::unique_ptr<FrameTransportImpl> m_transport  // 组合（非继承）
│   ├─ ConnectionEpoch m_epoch{0}
│   ├─ State m_state{Disconnected}
│   ├─ std::function<void(quintptr)> m_wIdCallback     // 不触发（nozzle 不用 WId 嵌入）
│   ├─ std::function<void(const QString&)> m_logCallback
│   ├─ std::function<void()> m_readyCallback
│   ├─ std::function<void()> m_lostCallback
│   └─ void* m_nozzleHandle{nullptr}                   // nozzle 连接句柄
│
└─ 关键差异:
    ├─ 有 m_transport 成员（与 EmbedIpcHandler 不同）
    ├─ 帧传输方法委托给 m_transport
    └─ WId 回调不触发（Texture 模式不嵌入窗口）
```

### 6.4 当前阶段行为（全部返回 false/nullptr）

**当前阶段 nozzle 尚未实现**，所有方法返回默认值：

| 方法 | 返回值 |
|------|--------|
| start() | false |
| stop() | no-op |
| probe() | false |
| isAlive() | false |
| disconnect() | no-op |
| sendShowCommand() | no-op |
| sendResizeCommand() | no-op |
| commandChannel() | nullptr |
| initFrameTransport() | false |
| shutdownFrameTransport() | no-op |
| isFrameTransportAvailable() | false |
| acquireFrame() | nullptr |
| releaseFrame() | no-op |
| setFrameAvailableCallback() | 存储但不触发 |
| destroyGlResources() | no-op |

### 6.5 未来实现方向（不在本阶段实现）

- `start()`：nozzle 握手 → 建立 GPU 纹理共享通道 → 状态→Connecting
- `probe()`：检查 nozzle 连接器可用 + GPU 上下文
- `isAlive()`：nozzle 心跳在超时窗口内
- 帧传输委托 `m_transport->acquireFrame()` / `releaseFrame()`
- `setReadyCallback`：纹理共享通道建立后触发
- `setLostCallback`：心跳超时触发

### 6.6 析构与资源清理

```cpp
~NozzleIpcHandler()
{
    // C12 修复：析构时解绑所有回调
    m_wIdCallback = nullptr;
    m_logCallback = nullptr;
    m_readyCallback = nullptr;
    m_lostCallback = nullptr;
    
    // 两阶段 GL teardown (C2 修复)
    if (m_transport) {
        m_transport->destroyGlResources();  // 阶段1: 销毁 GL 资源
        m_transport->shutdown();            // 阶段2: 关闭传输通道
        m_transport.reset();                // unique_ptr 自动释放
    }
}
```

---

## 7. FrameTransportImpl 设计

### 7.1 定位

`FrameTransportImpl` 是**内部基类**，不暴露给用户。仅被 `NozzleIpcHandler` 通过组合持有。当前阶段为默认实现（所有方法返回 false/nullptr）。

### 7.2 可见性

- **不是** ProcessInterface 的一部分
- **不**出现在公开头文件中
- 仅在 `qextQuickIpcWidgetItem.cpp` 或内部头文件中定义
- 用户通过 ProcessInterface 的帧传输方法间接使用

### 7.3 类设计

```cpp
// 内部头文件或 cpp 内
class FrameTransportImpl
{
public:
    virtual ~FrameTransportImpl() = default;
    
    // === 初始化与生命周期 ===
    virtual bool init() { return false; }               // 默认: 不可用
    virtual void shutdown() {}                           // 默认: no-op
    virtual bool isAvailable() const { return false; }   // 默认: 不可用
    
    // === 帧获取与释放 ===
    virtual void *acquireFrame() { return nullptr; }     // 默认: 无帧
    virtual void releaseFrame(void * /*handle*/) {}      // 默认: no-op
    
    // === 回调 ===
    virtual void setFrameAvailableCallback(std::function<void()>) {}  // 默认: no-op
    
    // === GL 资源 ===
    virtual void *commandChannel() { return nullptr; }   // 默认: 无通道
    virtual void destroyGlResources() {}                  // 默认: no-op
};
```

### 7.4 方法说明

| 方法 | 默认返回 | 说明 |
|------|----------|------|
| `init()` | `false` | 初始化帧传输通道（GPU 纹理共享上下文等） |
| `shutdown()` | — | 关闭传输通道，释放连接资源 |
| `isAvailable()` | `false` | 传输通道是否可用 |
| `acquireFrame()` | `nullptr` | 获取一帧纹理句柄（调用者持有期间不得释放） |
| `releaseFrame(handle)` | — | 释放获取的帧句柄 |
| `setFrameAvailableCallback(cb)` | — | 注册新帧可用通知回调 |
| `commandChannel()` | `nullptr` | 返回底层命令通道指针（nozzle handle 等） |
| `destroyGlResources()` | — | 销毁 GL 资源（纹理对象、FBO 等） |

### 7.5 两阶段 GL Teardown (C2 修复)

GL 资源必须在 GL 上下文有效时销毁，否则会导致 GPU 驱动泄漏或崩溃。因此析构采用两阶段：

1. **阶段 1 — `destroyGlResources()`**：在 GL 上下文仍有效时调用，销毁纹理/FBO
2. **阶段 2 — `shutdown()`**：关闭传输通道，释放 nozzle 连接

```
NozzleIpcHandler::~NozzleIpcHandler()
    │
    ├─ m_transport->destroyGlResources()   // 阶段1: GL 资源
    │     └─ 必须在 GL 上下文有效时调用
    │
    ├─ m_transport->shutdown()             // 阶段2: 通道关闭
    │     └─ 释放 nozzle 连接、socket 等
    │
    └─ m_transport.reset()                 // unique_ptr 析构
          └─ 析构 FrameTransportImpl 子类
```

### 7.6 initFrameTransport 自动调用 (C3 修复)

`NozzleIpcHandler::start()` 成功后，应自动调用 `initFrameTransport()`：

```cpp
// 未来实现（当前阶段全部返回 false）
bool start()
{
    // ... nozzle 握手 ...
    if (成功) {
        m_state = Connecting;
        // 自动初始化帧传输
        if (initFrameTransport()) {
            // 帧传输就绪
            if (m_readyCallback) m_readyCallback();
        }
    }
    return 成功;
}
```

**不要求用户手动调用 `initFrameTransport()`**。它在 `start()` 成功后被自动调用。`shutdownFrameTransport()` 在 `stop()` / `disconnect()` / 析构中被自动调用。

### 7.7 默认实现子类

当前阶段可提供一个 `DefaultFrameTransportImpl`（或直接用基类），所有方法返回默认值。未来 nozzle 实现时提供 `NozzleFrameTransportImpl` 子类。

---

## 8. 回调时序规则

### 8.1 QueuedConnection 强制 (C5 修复)

**所有回调**必须通过 `Qt::QueuedConnection` 派发到主线程：

| 回调 | 触发源线程 | 派发方式 |
|------|-----------|----------|
| `setWIdCallback` | QProcess stdout 读取（主线程） | QueuedConnection（确保异步语义一致） |
| `setLogCallback` | QProcess stdout/stderr（主线程） | 直接调用（日志性能敏感，且已在主线程） |
| `setReadyCallback` | createWindowContainer 完成后（主线程） | QueuedConnection（确保在事件循环中触发） |
| `setLostCallback` | QProcess::finished 信号（主线程） | QueuedConnection（确保状态一致） |
| `setFrameAvailableCallback` | nozzle 帧回调（可能非主线程） | QueuedConnection（跨线程必须） |

**例外**：`setLogCallback` 直接调用，因为：
1. 日志频率高，QueuedConnection 开销不可接受
2. QProcess 信号在主线程触发（`readyReadStandardOutput` 是 DirectConnection）
3. 日志不涉及状态变更，无需线程安全

### 8.2 回调触发时序

```
start()
  │
  ├─ QProcess::start → waitForStarted(5000)
  │     │
  │     ├─ [成功] 状态→Connecting
  │     │     │
  │     │     └─ 子进程 stdout: ">>>WID:123<<<"
  │     │           │
  │     │           ├─ epoch 检查
  │     │           ├─ m_cachedWId = 123
  │     │           ├─ setWIdCallback(123)           ← 回调1: WId 到达
  │     │           │     │
  │     │           │     └─ widget: asyncSetWidgetWId(123)
  │     │           │           │
  │     │           │           ├─ QWindow::fromWinId(123)
  │     │           │           ├─ QWidget::createWindowContainer(...)
  │     │           │           ├─ sendResizeCommand(w, h)
  │     │           │           ├─ sendShowCommand()
  │     │           │           │
  │     │           │           └─ setReadyCallback()   ← 回调2: 连接就绪
  │     │           │                 │
  │     │           │                 └─ 状态→Connected
  │     │           │
  │     └─ [失败] 状态→Disconnected
  │           └─ setLostCallback()                     ← 回调3: 连接丢失
  │
  └─ [后续] 进程崩溃
        ├─ QProcess::finished 信号
        ├─ epoch 检查
        ├─ m_cachedWId = 0
        ├─ 状态→Disconnected
        └─ setLostCallback()                           ← 回调3: 连接丢失
```

### 8.3 回调幂等性

- `setReadyCallback`：每次成功连接只触发一次（Connecting→Connected 转移时）
- `setLostCallback`：每次连接断开只触发一次（→Disconnected 转移时）
- `setWIdCallback`：每次子进程回传 WId 时触发（通常一次，但设计上允许多次以支持窗口重建）

### 8.4 回调解绑 (C12 修复)

析构时必须解绑所有回调，防止悬空指针：

```cpp
~EmbedIpcHandler()
{
    m_wIdCallback = nullptr;
    m_logCallback = nullptr;
    m_readyCallback = nullptr;
    m_lostCallback = nullptr;
    
    // 停止进程
    if (m_process && m_process->state() != QProcess::NotRunning) {
        m_process->kill();
        m_process->waitForFinished(3000);
    }
}
```

**同样适用于 `QExtQuickIpcWidgetItemPrivate` 析构**（当前代码已有此模式，见 `.cpp` 第 19-24 行）。

### 8.5 回调与信号的关系

| ProcessInterface 回调 | QExtQuickIpcWidgetItem 信号 | 关系 |
|------------------------|----------------------------|------|
| `setWIdCallback` | `asyncSetWidgetWId(quintptr, QPrivateSignal)` | handler 触发 callback → callback 内 emit 信号 |
| `setReadyCallback` | (无对应信号，状态内部管理) | handler → widget 内部状态更新 |
| `setLostCallback` | (无对应信号，触发 stop/cleanup) | handler → widget 调用 cleanup |
| `setLogCallback` | (无对应信号，直接 qDebug) | handler → 日志输出 |
| `setFrameAvailableCallback` | (无对应信号) | handler → widget 触发 QML update |

---

## 9. createDefaultHandler() 工厂

### 9.1 设计

工厂函数是**唯一**包含 `#ifdef QEXT_HAVE_NOZZLE` 的位置：

```cpp
// 在 qextQuickIpcWidgetItem.h 中
static ProcessInterface::SharedPtr createDefaultHandler();
```

```cpp
// 在 qextQuickIpcWidgetItem.cpp 中
QExtQuickIpcWidgetItem::ProcessInterface::SharedPtr 
QExtQuickIpcWidgetItem::createDefaultHandler()
{
#ifdef QEXT_HAVE_NOZZLE
    return ProcessInterface::SharedPtr(new NozzleIpcHandler());
#else
    return ProcessInterface::SharedPtr(new EmbedIpcHandler());
#endif
}
```

### 9.2 设计理由

1. **单一条件编译点**：用户代码无需关心 nozzle 是否启用，只需调用 `createDefaultHandler()`
2. **默认值**：nozzle OFF 时默认返回 EmbedIpcHandler（当前唯一可用实现）
3. **可扩展**：未来添加更多模式时，在此函数中扩展条件编译
4. **用户可覆盖**：用户仍可手动构造 handler 并通过 `setProcessInterface()` 注入（`createDefaultHandler` 仅为便捷方法）

### 9.3 使用示例（QML 侧）

```cpp
// C++ 侧（main.cpp 或 controller）
auto handler = QExtQuickIpcWidgetItem::createDefaultHandler();
ipcItem->setProcessPath("./child_process");
ipcItem->setProcessInterface(handler);
ipcItem->start();
```

```qml
// QML 侧
QExtQuickIpcWidgetItem {
    id: ipcItem
    processPath: "./child_process"
    // processInterface 通过 C++ 注入或 QML attached property
}
```

### 9.4 与 Auto 模式选择的关系

ADR-033 提到"连接时一次性模式选择（Auto/Texture/Embed）"。`createDefaultHandler()` 返回的默认 handler 在 `start()` 内部进行模式探测：

- EmbedIpcHandler：总是 Embed 模式（不支持探测切换）
- NozzleIpcHandler：总是 Texture 模式（不支持探测切换）
- 未来 `AutoIpcHandler`：`probe()` 时探测 nozzle 可用性，选择 Texture 或降级到 Embed（C7 内部降级路径）

**当前阶段不实现 Auto 模式**。`createDefaultHandler()` 直接返回 EmbedIpcHandler（nozzle OFF 时）或 NozzleIpcHandler（nozzle ON 时）。

---

## 10. 删除的死代码

### 10.1 从 ProcessInterface 中删除的方法

| 删除的方法 | 原因 | 替代方案 |
|-----------|------|----------|
| `bool start(const QString &path, const QStringList &args)` | 参数通过 widget Q_PROPERTY 传递，handler 内部获取 | `bool start()` 无参版本 |
| `bool isRunning() const` | 状态机替代隐含状态查询 | `isAlive()` + 状态枚举 |
| `bool isStopped() const` | 同上 | `isAlive()` 取反 + 状态枚举 |
| `QString workingPath() const` | QProcess 自行管理工作目录，widget 层不需要查询 | 无（移除功能） |
| `void setWorkingPath(const QString &path)` | 同上 | 无（移除功能） |
| `QVariantMap config() const` | 配置传播改为直接属性设置 | handler 构造时传入 path/args |
| `void setConfig(const QVariantMap &config)` | 同上 | 同上 |

### 10.2 从 QExtQuickIpcWidgetItem 中删除的成员

| 删除的成员 | 原因 |
|-----------|------|
| `Q_PROPERTY(QString workingPath ...)` | workingPath 移除 |
| `Q_SIGNAL void workingPathChanged(...)` | 同上 |
| `void setWorkingPath(const QString &path)` | 同上 |
| `QString workingPath() const` | 同上 |

### 10.3 保留的成员（不可删除）

| 保留的成员 | 原因 |
|-----------|------|
| `Q_INVOKABLE void setWidget(QWidget *)` | QMetaObject::invokeMethod 反射调用依赖（pitfall） |
| `Q_INVOKABLE QWidget *widget() const` | 同上 |
| `Q_INVOKABLE QWindow *rootWindow() const` | 同上 |
| `Q_INVOKABLE void setRootWindow(QWindow *)` | 同上 |
| `Q_PROPERTY(QString processPath ...)` | handler 启动参数来源 |
| `Q_PROPERTY(QStringList processArgs ...)` | handler 启动参数来源 |
| `Q_DECLARE_PRIVATE_D(dd_ptr, ...)` | ADR-031 修复，不可改回 Q_DECLARE_PRIVATE |

---

## 11. 审查修复对照表 (C1-C12)

来自 ADR-033 Oracle 审查的 12 项修复，在此设计文档中对应的位置：

| 修复项 | 问题 | 设计文档对应章节 | 设计决策 |
|--------|------|-----------------|----------|
| **C1** | commandChannel 类型为 void* | §4.2, §7.3 | `void *commandChannel()` 返回 `nullptr`（Embed）或 nozzle handle（Texture），类型安全由调用方负责 |
| **C2** | 两阶段 GL teardown | §7.5 | 析构时先 `destroyGlResources()` 再 `shutdown()` |
| **C3** | initFrameTransport 自动调用 | §7.6 | `start()` 成功后自动调用，不要求用户手动调用 |
| **C4** | PIMPL d_ptr/q_ptr | §1.3 (约束) | 使用 `Q_DECLARE_PRIVATE_D(dd_ptr, ...)` 复用父类 dd_ptr（ADR-031） |
| **C5** | QueuedConnection 回调 | §8.1 | 所有回调经 `Qt::QueuedConnection` 派发（logCallback 例外） |
| **C6** | shutdown 幂等双 guard | §2.4 (幂等保护) | `stop()` 在 Disconnected 状态下是 no-op；`shutdownFrameTransport()` 可重复调用 |
| **C7** | 内部降级路径 | §9.4 | Auto 模式（未来）在 probe() 失败时降级到 Embed；当前阶段不实现 |
| **C8** | senderName 来自 config | §4.4, §10.1 | 删除 config()/setConfig()，senderName 不再需要（handler 直接持有 processPath） |
| **C9** | enum Command | §4.3 | `enum Command { Show, Resize, Custom = 1000 }` |
| **C10** | EmbedIpcHandler 无 m_process 误用 | §5.2 | EmbedIpcHandler 有 m_process（QProcess），无 m_transport（FrameTransportImpl） |
| **C11** | 回调时序文档 | §8 (整章) | 完整文档化回调触发时机、QueuedConnection、epoch 检查 |
| **C12** | 析构回调解绑 | §8.4 | 析构时所有 callback 置 nullptr |

---

## 附录 A: 当前代码 → 新设计映射

| 当前代码 (修改前) | 新设计 (修改后) | 变更类型 |
|-------------------|-----------------|----------|
| `ProcessInterface::start(path, args)` | `ProcessInterface::start()` | 签名变更（参数移至 Q_PROPERTY） |
| `ProcessInterface::isRunning()` | 删除 → `isAlive()` | 语义变更（状态机替代） |
| `ProcessInterface::isStopped()` | 删除 → 状态枚举 | 语义变更 |
| `ProcessInterface::workingPath()` | 删除 | 功能移除 |
| `ProcessInterface::setWorkingPath()` | 删除 | 功能移除 |
| `ProcessInterface::config()` | 删除 | 功能移除（配置通过属性传递） |
| `ProcessInterface::setConfig()` | 删除 | 功能移除 |
| `ProcessInterface::setWIdCallback()` | 保留 | 不变（增加 epoch 保护） |
| `ProcessInterface::setLogCallback()` | 保留 | 不变 |
| `ProcessInterface::sendShowCommand()` | 保留 | 不变 |
| `ProcessInterface::sendResizeCommand()` | 保留 | 不变 |
| — | `ProcessInterface::probe()` | 新增 |
| — | `ProcessInterface::isAlive()` | 新增 |
| — | `ProcessInterface::disconnect()` | 新增 |
| — | `ProcessInterface::setReadyCallback()` | 新增 |
| — | `ProcessInterface::setLostCallback()` | 新增 |
| — | `ProcessInterface::commandChannel()` | 新增 |
| — | `ProcessInterface::initFrameTransport()` | 新增（stub） |
| — | `ProcessInterface::shutdownFrameTransport()` | 新增（stub） |
| — | `ProcessInterface::isFrameTransportAvailable()` | 新增（stub） |
| — | `ProcessInterface::acquireFrame()` | 新增（stub） |
| — | `ProcessInterface::releaseFrame()` | 新增（stub） |
| — | `ProcessInterface::setFrameAvailableCallback()` | 新增（stub） |
| — | `ProcessInterface::destroyGlResources()` | 新增（stub） |
| — | `ProcessInterface::Command` 枚举 | 新增 |
| — | `ProcessInterface::ConnectionEpoch` | 新增 |
| — | `ProcessInterface::State` 枚举 | 新增 |
| QProcessHandler（示例代码） | EmbedIpcHandler（库代码） | 提升为库实现 |
| 无 | NozzleIpcHandler（stub） | 新增 |
| 无 | FrameTransportImpl | 新增（内部基类） |
| 无 | `createDefaultHandler()` | 新增（工厂） |
| `setProcessInterface()` 传播 config | `setProcessInterface()` 直接设置 path/args | 简化 |
| `asyncSetWidgetWId` 信号 | 保留（不变） | epoch 检查在 handler 内 |

---

## 附录 B: 文件影响范围

| 文件 | 变更类型 | 说明 |
|------|----------|------|
| `qextQuickIpcWidgetItem.h` | **修改** | ProcessInterface 重构（新增/删除方法）、createDefaultHandler() 声明 |
| `qextQuickIpcWidgetItem.cpp` | **修改** | EmbedIpcHandler 实现、NozzleIpcHandler stub、createDefaultHandler() 实现 |
| `qextQuickIpcWidgetItem_p.h` | **修改** | 状态/纪元成员、remove workingPath 相关 |
| `qextQuickWidgetItem.h` | 不变 | 基类不受影响 |
| `examples/.../main.cpp` | **修改** | QProcessHandler 替换为 createDefaultHandler() |
| CMake 配置 | **修改** | 添加 QEXT_HAVE_NOZZLE 选项（默认 OFF） |

> **注意**：本设计文档不含代码实现。实际代码修改在后续 Task 中进行。
