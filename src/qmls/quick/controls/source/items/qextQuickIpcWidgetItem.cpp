#include "qextQuickIpcWidgetItem_p.h"

#include <QTimer>
#include <QEvent>
#include <QApplication>
#include <QRegularExpression>

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

    QObject::connect(q, &QExtQuickIpcWidgetItem::asyncSetWidgetWId, q, [=](quintptr winId)
    {
        WId wid = static_cast<WId>(winId);
        qDebug() << "[QExtIPC] WId =" << wid;
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
            // Resize AFTER setWidget — mWrapperWidget now at correct QQuickItem size
            mChildWindow->resize(mWrapperWidget->width(), mWrapperWidget->height());
            qDebug() << "[QExtIPC] after childWindow resize:" << mChildWindow->width() << "x" << mChildWindow->height();
            // setFixedSize prevents layout from overriding with child window's native size
            mChildWindowContainer->resize(mWrapperWidget->size());
            qDebug() << "[QExtIPC] after container setFixedSize:" << mWrapperWidget->size()
                     << "container.actual:" << mChildWindowContainer->size();
            if (mProcessInterface) 
            {
                mProcessInterface->sendResizeCommand(mWrapperWidget->width(), mWrapperWidget->height());
                mProcessInterface->sendShowCommand();
            }
            mChildWindowContainer->show();
            qDebug() << "[QExtIPC] asyncSetWidgetWId: embedding complete" << "size:" << mWrapperWidget->size();
        }
        else
        {
            qDebug() << "[QExtIPC] asyncSetWidgetWId: deferred - childWindow.isNull = "
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

    mProcessInterface->setWIdCallback([this, q](quintptr winId)
    {
        WId wid = static_cast<WId>(winId);
        mCachedWId = wid;
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
        if (watched == d->mWrapperWidget.data() && !d->mChildWindowContainer.isNull())
        {
            d->mChildWindow->resize(d->mWrapperWidget->width(), d->mWrapperWidget->height());
            if (d->mProcessInterface && d->mProcessInterface->isRunning()) {
                d->mProcessInterface->sendResizeCommand(d->mWrapperWidget->width(), d->mWrapperWidget->height());
            }
            qDebug() << "[QExtIPC] eventFilter Resize: wrapperWidget" << d->mWrapperWidget->size()
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

    // Propagate processPath/processArgs to ProcessInterface via setConfig
    QVariantMap config;
    if (!d->mProcessPath.isEmpty())
    {
        config["processPath"] = d->mProcessPath;
    }
    if (!d->mProcessArgs.isEmpty())
    {
        config["processArgs"] = d->mProcessArgs;
    }
    if (!config.isEmpty())
    {
        interface->setConfig(config);
    }
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
        // Propagate to ProcessInterface
        if (d->mProcessInterface) 
        {
            QVariantMap config = d->mProcessInterface->config();
            config["processPath"] = path;
            d->mProcessInterface->setConfig(config);
        }
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
        // Propagate to ProcessInterface
        if (d->mProcessInterface) 
        {
            QVariantMap config = d->mProcessInterface->config();
            config["processArgs"] = args;
            d->mProcessInterface->setConfig(config);
        }
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