#include <private/qextDAIODevice_p.h>

#include <QDebug>

QExtDAIODevicePrivate::QExtDAIODevicePrivate(QExtDAIODevice *q)
    : q_ptr(q)
    , mRXBps(0)
    , mIO(QEXT_NULLPTR)
    , mRXByteCount(0)
    , mRXByteAllCount(0)
{
}

QExtDAIODevicePrivate::~QExtDAIODevicePrivate()
{
    mIO->disconnect();
    mIO->deleteLater();
}

void QExtDAIODevicePrivate::initIO(QIODevice *io)
{
    Q_Q(QExtDAIODevice);
    mIO = io;
    QObject::connect(io, &QIODevice::readyRead, q, &QExtDAIODevice::onIOReadyRead);
    QObject::connect(io, &QIODevice::aboutToClose, q, &QExtDAIODevice::aboutToClose);
}

void QExtDAIODevicePrivate::updateByteCount(qulonglong rxCount)
{
    mRXByteCount += rxCount;
    mRXByteAllCount += rxCount;
}

QExtDAIODevice::QExtDAIODevice(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtDAIODevicePrivate(this))
{
}

QExtDAIODevice::QExtDAIODevice(QExtDAIODevicePrivate *d, QObject *parent)
    : QObject(parent)
    , dd_ptr(d)
{
}

QExtDAIODevice::~QExtDAIODevice()
{
}

quint64 QExtDAIODevice::id() const
{
    Q_D(const QExtDAIODevice);
    return d->mId;
}

QString QExtDAIODevice::name() const
{
    Q_D(const QExtDAIODevice);
    return QString("IO%1").arg(d->mId);
}

QString QExtDAIODevice::nameAlias() const
{
    Q_D(const QExtDAIODevice);
    if (!d->mAlias.isEmpty())
    {
        return QString("%1[%2]").arg(this->name(), d->mAlias);
    }
    else
    {
        return this->name();
    }
}

QString QExtDAIODevice::alias() const
{
    Q_D(const QExtDAIODevice);
    return d->mAlias;
}

void QExtDAIODevice::setAlias(const QString &alias)
{
    Q_D(QExtDAIODevice);
    if (alias != d->mAlias)
    {
        d->mAlias = alias;
        Q_EMIT this->aliasChanged(alias);
    }
}

QString QExtDAIODevice::stateString() const
{
    Q_D(const QExtDAIODevice);
    return this->isOpened() ? tr("Opened [%1B/S]").arg(d->mRXBps) : tr("Closed");
}

QString QExtDAIODevice::errorString() const
{
    return this->io()->errorString();
}

QExtPropertyModel *QExtDAIODevice::propertyModel()
{
    Q_D(QExtDAIODevice);
    if (d->mPropertyModel.isNull())
    {
        d->mPropertyModel.reset(new QExtPropertyModel);
        this->initPropertyModel(d->mPropertyModel.data());
    }
    return d->mPropertyModel.data();
}

QExtPropertyDelegate *QExtDAIODevice::propertyDelegate(QObject *parent)
{
    return new QExtPropertyDelegate(parent ? parent : this);
}

QThread *QExtDAIODevice::initDevice(quint64 id)
{
    Q_D(QExtDAIODevice);
    d->mId = id;
    if (d->mThreadOnceFlag.enter())
    {
        d->mThread.reset(new QThread);
        d->mThread->start();
        this->moveToThread(d->mThread.data());
        d->mIO->moveToThread(d->mThread.data());
        d->mRXBpsTimer.reset(new QTimer);
        d->mRXBpsTimer->setInterval(1000);
        d->mRXBpsTimer->moveToThread(d->mThread.data());
        connect(d->mThread.data(), &QThread::finished, d->mRXBpsTimer.data(), &QTimer::stop);
        connect(d->mRXBpsTimer.data(), &QTimer::timeout, this, [=]()
                {
                    d->mRXBps = d->mRXByteCount;
                    d->mRXByteCount = 0;
                    emit this->bpsChanged(d->mRXBps);
                });
        connect(this, &QExtDAIODevice::stateChanged, this, [=](bool opened)
                {
                    if (opened)
                    {
                        d->mRXBpsTimer->start();
                    }
                    else
                    {
                        d->mRXBpsTimer->stop();
                    }
                });
        d->mThreadOnceFlag.leave();
    }
    return d->mThread.data();
}

bool QExtDAIODevice::isOpened() const
{
    return this->io()->isOpen();
}

QIODevice *QExtDAIODevice::io() const
{
    Q_D(const QExtDAIODevice);
    return d->mIO.data();
}

void QExtDAIODevice::close()
{
    if (this->isOpened())
    {
        QTimer::singleShot(0, this, [=]()
                           {
                               this->io()->close();
                               Q_EMIT this->stateChanged(false);
                           });
    }
}

void QExtDAIODevice::open(QIODevice::OpenMode mode)
{
    QTimer::singleShot(0, this, [=]()
                       {
                           if (!this->io()->open(mode))
                           {
                               this->onIOOpenFailed();
                           }
                       });
}

void QExtDAIODevice::write(const char *data, qint64 size)
{
    Q_D(QExtDAIODevice);
    if (this->isOpened())
    {
        QExtSpinLock::Locker locker(d->mWriteDataQueueSpinlock);
        d->mWriteDataQueue.enqueue(QByteArray(data, size));
        QTimer::singleShot(0, this, &QExtDAIODevice::onIOReadyWrite);
    }
}

void QExtDAIODevice::onIOReadyRead()
{
}

void QExtDAIODevice::onIOReadyWrite()
{
    Q_EMIT this->readyWrite();
}

void QExtDAIODevice::onIOWriteFailed()
{
}

void QExtDAIODevice::onIOOpenFailed()
{
}

void QExtDAIODevice::onIOOpenSuccessed()
{
    Q_EMIT this->stateChanged(true);
}

void QExtDAIODevice::initPropertyModel(QExtPropertyModel *propertyModel)
{
    QExtPropertyModelItem *rootItem = propertyModel->rootItem();
    rootItem->appendChild(new QExtDAIODeviceStatePropertyItem(this));
    rootItem->appendChild(new QExtDAIODeviceAliasPropertyItem(this));
}


QExtDAIODeviceStatePropertyItem::QExtDAIODeviceStatePropertyItem(QExtDAIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDAIODevice::stateChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDAIODeviceStatePropertyItem::name() const
{
    return tr("State");
}

Qt::ItemFlags QExtDAIODeviceStatePropertyItem::flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

QVariant QExtDAIODeviceStatePropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return mIODevice->isOpened() ? tr("Opened") : tr("Closed");
    }
    else if (role == Qt::CheckStateRole)
    {
        return mIODevice->isOpened() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool QExtDAIODeviceStatePropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        bool checked = value.toInt() == Qt::Checked;
        if (checked)
        {
            mIODevice->open();
        }
        else
        {
            mIODevice->close();
        }
        return true;
    }
    return false;
}

QExtDAIODeviceAliasPropertyItem::QExtDAIODeviceAliasPropertyItem(QExtDAIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDAIODevice::aliasChanged, this, &QExtPropertyModelItem::updateItem);
}

QString QExtDAIODeviceAliasPropertyItem::name() const
{
    return tr("Alias");
}

Qt::ItemFlags QExtDAIODeviceAliasPropertyItem::flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant QExtDAIODeviceAliasPropertyItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        return mIODevice->alias();
    }
    return QVariant();
}

bool QExtDAIODeviceAliasPropertyItem::setData(const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        mIODevice->setAlias(value.toString());
        return true;
    }
    return false;
}

