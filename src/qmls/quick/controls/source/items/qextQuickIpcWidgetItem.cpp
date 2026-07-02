#include "qextQuickIpcWidgetItem_p.h"
#include "qextQuickEmbedIpcHandler.h"

#ifdef QEXT_HAVE_NOZZLE
#include "qextQuickNozzleIpcHandler.h"
#endif

#include <QTimer>
#include <QEvent>
#include <QApplication>
#include <QRegularExpression>

Q_LOGGING_CATEGORY(lcQExtQuickIpc, "qext.quick.ipc", QtWarningMsg)
// ---------------------------------------------------------------------------
// QExtQuickIpcWidgetItemPrivate
// ---------------------------------------------------------------------------

QExtQuickIpcWidgetItemPrivate::QExtQuickIpcWidgetItemPrivate(QExtQuickIpcWidgetItem *q)
    : QExtQuickWidgetItemPrivate(q)
{
}

QExtQuickIpcWidgetItemPrivate::~QExtQuickIpcWidgetItemPrivate()
{
    // C12 fix: unbind all callbacks to prevent dangling pointers
    mShutdownGuard = true;
    if (mProcessInterface)
    {
        mProcessInterface->setWIdCallback(nullptr);
        mProcessInterface->setLogCallback(nullptr);
        mProcessInterface->setReadyCallback(nullptr);
        mProcessInterface->setLostCallback(nullptr);
    }
}

void QExtQuickIpcWidgetItemPrivate::init()
{
    Q_Q(QExtQuickIpcWidgetItem);
    qRegisterMetaType<WId>("WId");

    QObject::connect(q, &QExtQuickIpcWidgetItem::asyncSetWidgetWId, q, [=](quintptr winId)
    {
        WId wid = static_cast<WId>(winId);
        qCDebug(lcQExtQuickIpc) << "[QExtIPC] WId =" << wid;
        mChildWindow = QWindow::fromWinId(wid);
        if (!mChildWindow.isNull() && !mWrapperWidget.isNull())
        {
            mChildWindowContainer = QWidget::createWindowContainer(mChildWindow.data(), mWrapperWidget, Qt::Widget);
            mChildWindowParent = mChildWindow->parent();
            if (!mWrapperWidget->isVisible())
            {
                q->setWidget(mWrapperWidget);
            }
            this->clearLayout();
            mLayout->addWidget(mChildWindowContainer.data());
            mChildWindow->resize(mWrapperWidget->width(), mWrapperWidget->height());
            qCDebug(lcQExtQuickIpc) << "[QExtIPC] after childWindow resize:" << mChildWindow->width() << "x" << mChildWindow->height();
            mChildWindowContainer->resize(mWrapperWidget->size());
            qCDebug(lcQExtQuickIpc) << "[QExtIPC] after container setFixedSize:" << mWrapperWidget->size()
                     << "container.actual:" << mChildWindowContainer->size();
            if (mProcessInterface)
            {
                mProcessInterface->sendResizeCommand(mWrapperWidget->width(), mWrapperWidget->height());
                mProcessInterface->sendShowCommand();
            }
            mChildWindowContainer->show();
            qCDebug(lcQExtQuickIpc) << "[QExtIPC] asyncSetWidgetWId: embedding complete" << "size:" << mWrapperWidget->size();
        }
        else
        {
            qCWarning(lcQExtQuickIpc) << "[QExtIPC] asyncSetWidgetWId: deferred - childWindow.isNull = "
                     << mChildWindow.isNull() << "wrapperWidget.isNull =" << mWrapperWidget.isNull();
        }
    });

    QObject::connect(q, &QExtQuickIpcWidgetItem::asyncUpdateWidgetGeometry,
                     q, &QExtQuickIpcWidgetItem::updateWidgetGeometry);

    QObject::connect(q, &QExtQuickIpcWidgetItem::rootWindowChanged, q, [=](QWindow *window)
    {
        if (!mWrapperWidget.isNull())
        {
            mWrapperWidget->disconnect(q);
            mWrapperWidget->deleteLater();
            mWrapperWidget.clear();
        }
        mLayout = new QVBoxLayout;
        mLayout->setMargin(0);
        mLayout->setSpacing(0);
        mWrapperWidget = new QWidget;
        mWrapperWidget->hide();
        mWrapperWidget->setLayout(mLayout);
        mWrapperWidget->installEventFilter(q);
        mWrapperWidget->setStyleSheet("background-color: rgb(136, 138, 133);");
        if (window)
        {
            if (!mProcessInterface) {
                qCWarning(lcQExtQuickIpc) << "rootWindowChanged: processInterface is null, skipping auto-start";
                return;
            }
            if (!q->startProcess())
            {
                qCWarning(lcQExtQuickIpc) << "[QExtIPC] rootWindowChanged: startProcess returned false";
            }
        }
    });

    // Crash recovery: probe retry timer for reconnection polling
    mProbeRetryTimer = new QTimer(q);
    mProbeRetryTimer->setInterval(500);
    QObject::connect(mProbeRetryTimer, &QTimer::timeout, q, [this, q]() {
        if (mShutdownGuard) return;
        if (mState != ProcessInterface::Disconnected)
        {
            mProbeRetryTimer->stop();
            qCDebug(lcQExtQuickIpc) << "[QExtIPC] probeRetry stopped: state changed to" << mState;
            return;
        }
        mRetryCount++;
        if (mRetryCount >= 3)
        {
            mProbeRetryTimer->stop();
            qCWarning(lcQExtQuickIpc) << "[QExtIPC] probeRetry: max retries (3) reached, stopping";
            return;
        }
        if (mProcessInterface && mProcessInterface->probe())
        {
            qCDebug(lcQExtQuickIpc) << "[QExtIPC] probeRetry: calling start() at epoch" << mConnectionEpoch;
            q->start();
        }
    });
}

void QExtQuickIpcWidgetItemPrivate::initIpcCallbacks()
{
    Q_Q(QExtQuickIpcWidgetItem);
    if (!mProcessInterface)
    {
        return;
    }

    qCDebug(lcQExtQuickIpc) << "[QExtIPC] initIpcCallbacks: setting up WId, log, ready, lost callbacks";
    mProcessInterface->setLogCallback([](const QString &msg)
    {
        qCDebug(lcQExtQuickIpc) << "[QExtIPC]" << msg;
    });

    mProcessInterface->setWIdCallback([this, q](quintptr winId)
    {
        ConnectionEpoch callbackEpoch = mConnectionEpoch;
        QMetaObject::invokeMethod(q, [=]() {
            // C6: shutdown idempotent guard
            if (mShutdownGuard) return;
            // Epoch validation: reject stale callbacks from old connections
            if (callbackEpoch != mConnectionEpoch)
            {
                qCWarning(lcQExtQuickIpc) << "[QExtIPC] WId callback discarded: stale epoch" << callbackEpoch
                         << "current:" << mConnectionEpoch;
                return;
            }
            // State guard: only accept WId when in Connecting state
            if (mState != ProcessInterface::Connecting)
            {
                qCWarning(lcQExtQuickIpc) << "[QExtIPC] WId callback discarded: not in Connecting state (" << mState << ")";
                return;
            }
            qCDebug(lcQExtQuickIpc) << "[QExtIPC] state:" << mState << "\u2192 Connected";
            mState = ProcessInterface::Connected;
            emit q->asyncSetWidgetWId(winId, QExtQuickIpcWidgetItem::QPrivateSignal());
        }, Qt::QueuedConnection);
    });

    // C5 fix: ready callback via QueuedConnection
    mProcessInterface->setReadyCallback([this, q]()
    {
        ConnectionEpoch callbackEpoch = mConnectionEpoch;
        QMetaObject::invokeMethod(q, [=]() {
            if (mShutdownGuard) return;
            if (callbackEpoch != mConnectionEpoch)
            {
                qCWarning(lcQExtQuickIpc) << "[QExtIPC] ready callback discarded: stale epoch" << callbackEpoch
                         << "current:" << mConnectionEpoch;
                return;
            }
            qCDebug(lcQExtQuickIpc) << "[QExtIPC] ready callback: connection established";
            // C3 fix: initFrameTransport auto-called on ready (no-op for Embed, call anyway)
            if (mProcessInterface)
            {
                mProcessInterface->initFrameTransport();
            }
            if (mState == ProcessInterface::Connecting)
            {
                qCDebug(lcQExtQuickIpc) << "[QExtIPC] state:" << mState << "\u2192 Connected";
                mState = ProcessInterface::Connected;
            }
        }, Qt::QueuedConnection);
    });

    // C5 fix: lost callback via QueuedConnection
    mProcessInterface->setLostCallback([this, q]()
    {
        ConnectionEpoch callbackEpoch = mConnectionEpoch;
        QMetaObject::invokeMethod(q, [=]() {
            if (mShutdownGuard) return;
            if (callbackEpoch != mConnectionEpoch)
            {
                qCWarning(lcQExtQuickIpc) << "[QExtIPC] lost callback discarded: stale epoch" << callbackEpoch
                         << "current:" << mConnectionEpoch;
                return;
            }
            qCWarning(lcQExtQuickIpc) << "[QExtIPC] lost callback: connection lost, cleaning up";
            q->stop();
            // Crash recovery: start probe retry for auto-reconnection
            if (!mShutdownGuard && !mProcessPath.isEmpty())
            {
                qCDebug(lcQExtQuickIpc) << "[QExtIPC] starting probe retry (500ms) for crash recovery";
                startProbeRetry();
            }
        }, Qt::QueuedConnection);
    });
}
void QExtQuickIpcWidgetItemPrivate::clearLayout()
{
    if (!mLayout.isNull())
    {
        QLayoutItem *child;
        while ((child = mLayout->takeAt(0)) != 0)
        {
            if (child->widget())
            {
                delete child->widget();
            }
            delete child;
        }
    }
}

void QExtQuickIpcWidgetItemPrivate::detachChildWindow()
{
    if (!mChildWindow.isNull())
    {
        mChildWindow->hide();
        mChildWindow->setParent(nullptr);
        mChildWindow.clear();
    }
}

// ---------------------------------------------------------------------------
// QExtQuickIpcWidgetItem
// ---------------------------------------------------------------------------

QExtQuickIpcWidgetItem::QExtQuickIpcWidgetItem(QQuickItem *parent)
    : QExtQuickIpcWidgetItem(new QExtQuickIpcWidgetItemPrivate(this), parent)
{
}

QExtQuickIpcWidgetItem::QExtQuickIpcWidgetItem(QExtQuickIpcWidgetItemPrivate *d, QQuickItem *parent)
    : QExtQuickWidgetItem(d, parent)
{
    d->init();
}

QExtQuickIpcWidgetItem::~QExtQuickIpcWidgetItem()
{
    // C6 fix: shutdown idempotent guard
    Q_D(QExtQuickIpcWidgetItem);
    d->mShutdownGuard = true;
    d->detachChildWindow();
}

void QExtQuickIpcWidgetItem::start()
{
    Q_D(QExtQuickIpcWidgetItem);

    // C6: shutdown idempotent guard (extended to all entry points)
    if (d->mShutdownGuard)
    {
        qCWarning(lcQExtQuickIpc) << "[QExtIPC] start skipped: shutting down";
        return;
    }

    // State machine: only allow start from Disconnected
    if (d->mState != ProcessInterface::Disconnected)
    {
        qCWarning(lcQExtQuickIpc) << "[QExtIPC] start skipped: already in state" << d->mState;
        return;
    }

    if (!d->mProcessInterface)
    {
        qCCritical(lcQExtQuickIpc) << "[QExtIPC] start skipped: processInterface is null";
        return;
    }

    // State transition: Disconnected → Connecting
    auto oldState = d->mState;
    d->mState = ProcessInterface::Connecting;
    d->mConnectionEpoch++;
    d->stopProbeRetry();
    d->mRetryCount = 0;
    qCDebug(lcQExtQuickIpc) << "[QExtIPC] state:" << oldState << "\u2192 Connecting (epoch=" << d->mConnectionEpoch << ")";

    bool ok = this->startProcess();
    if (!ok)
    {
        qCWarning(lcQExtQuickIpc) << "[QExtIPC] state: Connecting \u2192 Disconnected (startProcess failed)";
        d->mState = ProcessInterface::Disconnected;
    }
    qCDebug(lcQExtQuickIpc) << "[QExtIPC] start: startProcess returned" << ok;
}

void QExtQuickIpcWidgetItem::stop()
{
    // C6 fix: idempotent \u2014 safe to call multiple times
    Q_D(QExtQuickIpcWidgetItem);
    if (d->mShutdownGuard) return;

    // State machine: Disconnected or already disconnecting \u2192 no-op
    if (d->mState == ProcessInterface::Disconnected)
    {
        qCDebug(lcQExtQuickIpc) << "[QExtIPC] stop: already Disconnected";
        return;
    }
    if (d->mState == ProcessInterface::Disconnecting)
    {
        qCDebug(lcQExtQuickIpc) << "[QExtIPC] stop: already Disconnecting";
        return;
    }

    // State transition \u2192 Disconnecting
    auto oldState = d->mState;
    d->mState = ProcessInterface::Disconnecting;
    qCDebug(lcQExtQuickIpc) << "[QExtIPC] state:" << oldState << "\u2192 Disconnecting";

    if (d->mProcessInterface)
    {
        d->mProcessInterface->stop();
    }
    d->clearLayout();
    d->detachChildWindow();

    // State transition: Disconnecting \u2192 Disconnected
    d->mState = ProcessInterface::Disconnected;
    qCDebug(lcQExtQuickIpc) << "[QExtIPC] state: Disconnecting \u2192 Disconnected";
}

bool QExtQuickIpcWidgetItem::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        Q_D(QExtQuickIpcWidgetItem);
        if (watched == d->mWrapperWidget.data() && !d->mChildWindowContainer.isNull())
        {
            d->mChildWindow->resize(d->mWrapperWidget->width(), d->mWrapperWidget->height());
            if (d->mProcessInterface && d->mProcessInterface->isAlive()) {
                d->mProcessInterface->sendResizeCommand(d->mWrapperWidget->width(), d->mWrapperWidget->height());
            }
            qCDebug(lcQExtQuickIpc) << "[QExtIPC] eventFilter Resize: wrapperWidget" << d->mWrapperWidget->size()
                     << "\u2192 container setFixedSize"
                     << "container.actual:" << d->mChildWindowContainer->size()
                     << "childWindow:" << d->mChildWindow->width() << "x" << d->mChildWindow->height();
        }
    }
    return QExtQuickWidgetItem::eventFilter(watched, event);
}

QExtQuickIpcWidgetItem::ProcessInterface::SharedPtr QExtQuickIpcWidgetItem::processInterface() const
{
    Q_D(const QExtQuickIpcWidgetItem);
    return d->mProcessInterface;
}

void QExtQuickIpcWidgetItem::setProcessInterface(const QExtQuickIpcWidgetItem::ProcessInterface::SharedPtr &interface)
{
    Q_D(QExtQuickIpcWidgetItem);
    d->mProcessInterface = interface;

    // Propagate path/args to EmbedIpcHandler if applicable
    auto *embedHandler = dynamic_cast<QExtQuickEmbedIpcHandler *>(d->mProcessInterface.data());
    if (embedHandler)
    {
        if (!d->mProcessPath.isEmpty())
            embedHandler->setProcessPath(d->mProcessPath);
        if (!d->mProcessArgs.isEmpty())
            embedHandler->setProcessArgs(d->mProcessArgs);
    }

    d->initIpcCallbacks();
}

// Sole location of #ifdef QEXT_HAVE_NOZZLE
QExtQuickIpcWidgetItem::ProcessInterface::SharedPtr QExtQuickIpcWidgetItem::createDefaultHandler()
{
#ifdef QEXT_HAVE_NOZZLE
    return QExtQuickNozzleIpcHandler::create();
#else
    return QExtQuickEmbedIpcHandler::create();
#endif
}

QString QExtQuickIpcWidgetItem::processPath() const
{
    Q_D(const QExtQuickIpcWidgetItem);
    return d->mProcessPath;
}

void QExtQuickIpcWidgetItem::setProcessPath(const QString &path)
{
    Q_D(QExtQuickIpcWidgetItem);
    if (path != d->mProcessPath)
    {
        d->mProcessPath = path;
        emit this->processPathChanged(path);
        // Propagate to EmbedIpcHandler if applicable
        auto *embedHandler = dynamic_cast<QExtQuickEmbedIpcHandler *>(d->mProcessInterface.data());
        if (embedHandler)
        {
            embedHandler->setProcessPath(path);
        }
    }
}

QStringList QExtQuickIpcWidgetItem::processArgs() const
{
    Q_D(const QExtQuickIpcWidgetItem);
    return d->mProcessArgs;
}

void QExtQuickIpcWidgetItem::setProcessArgs(const QStringList &args)
{
    Q_D(QExtQuickIpcWidgetItem);
    if (args != d->mProcessArgs)
    {
        d->mProcessArgs = args;
        // Propagate to EmbedIpcHandler if applicable
        auto *embedHandler = dynamic_cast<QExtQuickEmbedIpcHandler *>(d->mProcessInterface.data());
        if (embedHandler)
        {
            embedHandler->setProcessArgs(args);
        }
        emit this->processArgsChanged(args);
    }
}

bool QExtQuickIpcWidgetItem::startProcess()
{
    Q_D(QExtQuickIpcWidgetItem);
    if (d->mProcessPath.isEmpty())
    {
        qCWarning(lcQExtQuickIpc) << "[QExtIPC] startProcess failed: processPath is empty";
        return false;
    }
    if (d->mRootWindow.isNull())
    {
        qCCritical(lcQExtQuickIpc) << "[QExtIPC] startProcess failed: rootWindow is null";
        return false;
    }
    if (!d->mProcessInterface)
    {
        qCCritical(lcQExtQuickIpc) << "[QExtIPC] startProcess failed: processInterface is null";
        return false;
    }
    if (d->mProcessInterface->isAlive())
    {
        qCWarning(lcQExtQuickIpc) << "[QExtIPC] startProcess failed: process is already running";
        return false;
    }

    // Propagate path/args to EmbedIpcHandler before start
    auto *embedHandler = dynamic_cast<QExtQuickEmbedIpcHandler *>(d->mProcessInterface.data());
    if (embedHandler)
    {
        embedHandler->setProcessPath(d->mProcessPath);
        embedHandler->setProcessArgs(d->mProcessArgs);
    }

    qCDebug(lcQExtQuickIpc) << "[QExtIPC] startProcess: launching" << d->mProcessPath << d->mProcessArgs;
    return d->mProcessInterface->start();
}

void QExtQuickIpcWidgetItemPrivate::startProbeRetry()
{
    if (mProbeRetryTimer && !mProbeRetryTimer->isActive())
    {
        qCDebug(lcQExtQuickIpc) << "[QExtIPC] probeRetry timer started (interval=500ms, epoch=" << mConnectionEpoch << ")";
        mProbeRetryTimer->start();
    }
}

void QExtQuickIpcWidgetItemPrivate::stopProbeRetry()
{
    if (mProbeRetryTimer && mProbeRetryTimer->isActive())
    {
        qCDebug(lcQExtQuickIpc) << "[QExtIPC] probeRetry timer stopped";
        mProbeRetryTimer->stop();
    }
}
