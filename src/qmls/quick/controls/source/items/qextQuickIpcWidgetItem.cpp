#include "qextQuickIpcWidgetItem_p.h"

#include <QTimer>
#include <QProcess>
#include <QApplication>
#include <QRegularExpression>
#include <QEvent>

// ---------------------------------------------------------------------------
// QExtQuickIpcWidgetItemPrivate
// ---------------------------------------------------------------------------

QExtQuickIpcWidgetItemPrivate::QExtQuickIpcWidgetItemPrivate(QExtQuickIpcWidgetItem *q)
    : QExtQuickWidgetItemPrivate(q)
{
}

QExtQuickIpcWidgetItemPrivate::~QExtQuickIpcWidgetItemPrivate()
{
    if (mProcessInterface) 
    {
        mProcessInterface->setWIdCallback(nullptr);
        mProcessInterface->setLogCallback(nullptr);
    }
}

void QExtQuickIpcWidgetItemPrivate::init()
{
    Q_Q(QExtQuickIpcWidgetItem);
    qRegisterMetaType<WId>("WId");

    QObject::connect(q, &QExtQuickIpcWidgetItem::asyncSetWidgetWId, q, [=](WId winId) 
    {
        qDebug() << "[QExtIPC] WId =" << winId;
        mChildWindow = QWindow::fromWinId(winId);
        if (!mChildWindow.isNull() && !mWraperWidget.isNull()) 
        {
            mChildWindowContainer = QWidget::createWindowContainer(mChildWindow.data(), mWraperWidget, Qt::Widget);
            mChildWindowParent = mChildWindow->parent();
            if (!mWraperWidget->isVisible()) 
            {
                q->setWidget(mWraperWidget);
            }
            this->clearLayout();
            mLayout->addWidget(mChildWindowContainer.data());
            // Resize AFTER setWidget — mWraperWidget now at correct QQuickItem size
            mChildWindow->resize(mWraperWidget->width(), mWraperWidget->height());
            qDebug() << "[QExtIPC] after childWindow resize:" << mChildWindow->width() << "x" << mChildWindow->height();
            // setFixedSize prevents layout from overriding with child window's native size
            mChildWindowContainer->resize(mWraperWidget->size());
            qDebug() << "[QExtIPC] after container setFixedSize:" << mWraperWidget->size()
                     << "container.actual:" << mChildWindowContainer->size();
            if (mProcessInterface) 
            {
                mProcessInterface->sendResizeCommand(mWraperWidget->width(), mWraperWidget->height());
                mProcessInterface->sendShowCommand();
            }
            mChildWindowContainer->show();
            qDebug() << "[QExtIPC] asyncSetWidgetWId: embedding complete" << "size:" << mWraperWidget->size();
        }
        else
        {
            qDebug() << "[QExtIPC] asyncSetWidgetWId: deferred - childWindow.isNull = "
                     << mChildWindow.isNull() << "wraperWidget.isNull =" << mWraperWidget.isNull();
        }
    });

    QObject::connect(q, &QExtQuickIpcWidgetItem::asyncUpdateWidgetGeometry,
                     q, &QExtQuickIpcWidgetItem::updateWidgetGeometry);

    QObject::connect(q, &QExtQuickIpcWidgetItem::rootWindowChanged, q, [=](QWindow *window) 
    {
        if (!mWraperWidget.isNull()) 
        {
            mWraperWidget->disconnect(q);
            mWraperWidget->deleteLater();
            mWraperWidget.clear();
        }
        mLayout = new QVBoxLayout;
        mLayout->setMargin(0);
        mLayout->setSpacing(0);
        mWraperWidget = new QWidget;
        mWraperWidget->hide();
        mWraperWidget->setLayout(mLayout);
        mWraperWidget->installEventFilter(q);
        mWraperWidget->setStyleSheet("background-color: rgb(136, 138, 133);");
        if (window) 
        {
            if (!q->startProcess() && mChildWindow.isNull()) 
            {
                if (mCachedWId != 0) 
                {
                    emit q->asyncSetWidgetWId(mCachedWId, QExtQuickIpcWidgetItem::QPrivateSignal());
                }
            }
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

    qDebug() << "[QExtIPC] initIpcCallbacks: setting up WId and log callbacks";
    mProcessInterface->setLogCallback([](const QString &msg) 
    {
        qDebug() << "[QExtIPC]" << msg;
    });

    mProcessInterface->setWIdCallback([this, q](WId winId) 
    {
        mCachedWId = winId;
        emit q->asyncSetWidgetWId(winId, QExtQuickIpcWidgetItem::QPrivateSignal());
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
    : QExtQuickWidgetItem(new QExtQuickIpcWidgetItemPrivate(this), parent)
{
    Q_D(QExtQuickIpcWidgetItem);
    d->init();
}

QExtQuickIpcWidgetItem::QExtQuickIpcWidgetItem(QExtQuickIpcWidgetItemPrivate *d, QQuickItem *parent)
    : QExtQuickWidgetItem(d, parent)
{
    d->init();
}

QExtQuickIpcWidgetItem::~QExtQuickIpcWidgetItem()
{
    Q_D(QExtQuickIpcWidgetItem);
    d->detachChildWindow();
}

void QExtQuickIpcWidgetItem::start()
{
    Q_D(QExtQuickIpcWidgetItem);
    if (!d->mProcessInterface)
    {
        qDebug() << "[QExtIPC] start skipped: processInterface is null";
    }
    else if (!d->mProcessInterface->isStopped())
    {
        qDebug() << "[QExtIPC] start skipped: process is already running";
    }
    else
    {
        bool ok = this->startProcess();
        qDebug() << "[QExtIPC] start: startProcess returned" << ok;
    }
}

void QExtQuickIpcWidgetItem::stop()
{
    Q_D(QExtQuickIpcWidgetItem);
    if (d->mProcessInterface)
    {
        d->mProcessInterface->stop();
    }
    d->clearLayout();
    d->detachChildWindow();
}

bool QExtQuickIpcWidgetItem::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        Q_D(QExtQuickIpcWidgetItem);
        if (watched == d->mWraperWidget.data() && !d->mChildWindowContainer.isNull())
        {
            d->mChildWindow->resize(d->mWraperWidget->width(), d->mWraperWidget->height());
            if (d->mProcessInterface && d->mProcessInterface->isRunning()) {
                d->mProcessInterface->sendResizeCommand(d->mWraperWidget->width(), d->mWraperWidget->height());
            }
            qDebug() << "[QExtIPC] eventFilter Resize: wraperWidget" << d->mWraperWidget->size()
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
    d->initIpcCallbacks();
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
        emit this->processArgsChanged(args);
    }
}

QString QExtQuickIpcWidgetItem::workingPath() const
{
    Q_D(const QExtQuickIpcWidgetItem);
    return d->mProcessInterface ? d->mProcessInterface->workingPath() : QString();
}

void QExtQuickIpcWidgetItem::setWorkingPath(const QString &path)
{
    Q_D(QExtQuickIpcWidgetItem);
    if (d->mProcessInterface) 
    {
        d->mProcessInterface->setWorkingPath(path);
        emit this->workingPathChanged(path);
    }
}

bool QExtQuickIpcWidgetItem::startProcess()
{
    Q_D(QExtQuickIpcWidgetItem);
    if (d->mProcessPath.isEmpty())
    {
        qDebug() << "[QExtIPC] startProcess failed: processPath is empty";
        return false;
    }
    if (d->mRootWindow.isNull())
    {
        qDebug() << "[QExtIPC] startProcess failed: rootWindow is null";
        return false;
    }
    if (!d->mProcessInterface)
    {
        qDebug() << "[QExtIPC] startProcess failed: processInterface is null";
        return false;
    }
    if (!d->mProcessInterface->isStopped())
    {
        qDebug() << "[QExtIPC] startProcess failed: process is already running";
        return false;
    }
    qDebug() << "[QExtIPC] startProcess: launching" << d->mProcessPath << d->mProcessArgs;
    return d->mProcessInterface->start(d->mProcessPath, d->mProcessArgs);
}


QExtQuickIpcWidgetItemProcessHandler::QExtQuickIpcWidgetItemProcessHandler(QObject *parent)
    : QObject(parent)
    , mProcess(std::make_unique<QProcess>())
    , mKillTimer(std::make_unique<QTimer>())
{
    mKillTimer->setSingleShot(true);
    mKillTimer->setInterval(3000);

    // Forward QProcess signals to our own signals
    connect(mProcess.get(), &QProcess::started,
            this, &QExtQuickIpcWidgetItemProcessHandler::started);
    connect(mProcess.get(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &QExtQuickIpcWidgetItemProcessHandler::onProcessFinished);
    connect(mProcess.get(), &QProcess::errorOccurred,
            this, &QExtQuickIpcWidgetItemProcessHandler::onProcessErrorOccurred);
    connect(mProcess.get(), &QProcess::readyReadStandardOutput,
            this, &QExtQuickIpcWidgetItemProcessHandler::onReadyReadStandardOutput);

    // Kill timer: if terminate() didn't stop the process in 3s, force kill
    connect(mKillTimer.get(), &QTimer::timeout,
            this, &QExtQuickIpcWidgetItemProcessHandler::onKillTimeout);
}

QExtQuickIpcWidgetItemProcessHandler::~QExtQuickIpcWidgetItemProcessHandler() = default;

bool QExtQuickIpcWidgetItemProcessHandler::start(const QString &path, const QStringList &args)
{
    if (this->isRunning()) 
    {
        qWarning() << "QExtQuickIpcWidgetItemProcessHandler::start: process is already running";
        return false;
    }

    mProcess->start(path, args);
    if (!mProcess->waitForStarted(5000)) 
    {
        const QString err = QStringLiteral("Failed to start process: %1").arg(mProcess->errorString());
        qWarning() << err;
        emit this->errorOccurred(err);
        return false;
    }

    return true;
}

void QExtQuickIpcWidgetItemProcessHandler::stop()
{
    if (this->isStopped()) 
    {
        return;
    }

    mProcess->terminate();

    if (!mProcess->waitForFinished(3000)) 
    {
        // Start kill timer — if the process still hasn't exited after 3s, kill it
        mKillTimer->start();
    }
}

bool QExtQuickIpcWidgetItemProcessHandler::isRunning() const
{
    return mProcess->state() == QProcess::Running;
}

bool QExtQuickIpcWidgetItemProcessHandler::isStopped() const
{
    return mProcess->state() == QProcess::NotRunning;
}

void QExtQuickIpcWidgetItemProcessHandler::setWorkingPath(const QString &path)
{
    mProcess->setWorkingDirectory(path);
}

QString QExtQuickIpcWidgetItemProcessHandler::workingPath() const
{
    return mProcess->workingDirectory();
}

void QExtQuickIpcWidgetItemProcessHandler::setWIdCallback(std::function<void(WId)> callback)
{
    mWidCallback = std::move(callback);
}

void QExtQuickIpcWidgetItemProcessHandler::setLogCallback(std::function<void(const QString &)> callback)
{
    mLogCallback = std::move(callback);
}

void QExtQuickIpcWidgetItemProcessHandler::sendShowCommand()
{
    if (!isRunning()) 
    {
        qWarning() << "QExtQuickIpcWidgetItemProcessHandler::sendShowCommand: process is not running";
        return;
    }

    mProcess->write("\n");
}

void QExtQuickIpcWidgetItemProcessHandler::sendResizeCommand(int width, int height)
{
    if (!isRunning()) return;
    mProcess->write(QString(">>>SIZE:%1,%2<<<\n").arg(width).arg(height).toUtf8());
}
// ---------------------------------------------------------------------------
// Private slots
// ---------------------------------------------------------------------------

void QExtQuickIpcWidgetItemProcessHandler::onReadyReadStandardOutput()
{
    const QByteArray data = mProcess->readAllStandardOutput();

    // Forward to log callback if set
    if (mLogCallback) 
    {
        mLogCallback(QString::fromUtf8(data));
    }

    // Parse WId from "WID:12345" pattern
    static const QRegularExpression re(QStringLiteral("WID:(\\d+)"));
    const QString text = QString::fromUtf8(data);
    const auto match = re.match(text);
    if (match.hasMatch() && mWidCallback) 
    {
        bool ok = false;
        const WId wid = static_cast<WId>(match.captured(1).toULongLong(&ok));
        if (ok) 
        {
            mWidCallback(wid);
        }
    }
}

void QExtQuickIpcWidgetItemProcessHandler::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode)
    Q_UNUSED(exitStatus)

    mKillTimer->stop();
    emit this->stopped();
}

void QExtQuickIpcWidgetItemProcessHandler::onProcessErrorOccurred(QProcess::ProcessError error)
{
    switch (error) 
    {
    case QProcess::FailedToStart:
        emit this->errorOccurred(QStringLiteral("Process failed to start"));
        break;
    case QProcess::Crashed:
        emit this->errorOccurred(QStringLiteral("Process crashed"));
        break;
    case QProcess::Timedout:
        emit this->errorOccurred(QStringLiteral("Process timed out"));
        break;
    case QProcess::WriteError:
        emit this->errorOccurred(QStringLiteral("Process write error"));
        break;
    case QProcess::ReadError:
        emit this->errorOccurred(QStringLiteral("Process read error"));
        break;
    default:
        emit this->errorOccurred(QStringLiteral("Unknown process error"));
        break;
    }
}

void QExtQuickIpcWidgetItemProcessHandler::onKillTimeout()
{
    if (this->isRunning()) 
    {
        qWarning() << "QExtQuickIpcWidgetItemProcessHandler: terminate timed out, killing process";
        mProcess->kill();
    }
}
