#include <private/qextDAIODevice_p.h>
#include <qextDAConstants.h>

#include <QDebug>

QExtDAIODevicePrivate::QExtDAIODevicePrivate(QExtDAIODevice *q)
    : q_ptr(q)
    , mBufferSize(1000)
    , mIO(QEXT_NULLPTR)
    , mRxdBps(0)
    , mBufferEnable(true)
    , mRxdByteCount(0)
    , mRxdByteAllCount(0)
{
}

QExtDAIODevicePrivate::~QExtDAIODevicePrivate()
{
}

void QExtDAIODevicePrivate::initIO(QIODevice *io)
{
    Q_Q(QExtDAIODevice);
    mIO = io;
    QObject::connect(io, &QIODevice::readyRead, q, &QExtDAIODevice::onIOReadyRead);
    QObject::connect(io, &QIODevice::aboutToClose, q, &QExtDAIODevice::aboutToClose);
}

void QExtDAIODevicePrivate::updateBpsValue()
{
    Q_Q(QExtDAIODevice);
    mRxdBps = mRxdByteCount;
    mTxdBps = mTxdByteCount;
    emit q->rxdBpsChanged(mRxdBps);
    emit q->txdBpsChanged(mTxdBps);
    mRxdByteCount = 0;
    mTxdByteCount = 0;
}

void QExtDAIODevicePrivate::updateRxdBps(qulonglong rxdCount)
{
    mRxdByteCount += rxdCount;
    mRxdByteAllCount += rxdCount;
}

void QExtDAIODevicePrivate::updateTxdBps(qulonglong txdCount)
{
    mTxdByteCount += txdCount;
    mTxdByteAllCount += txdCount;
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

int QExtDAIODevice::bps() const
{
    Q_D(const QExtDAIODevice);
    return d->mRxdBps.load();
}

qint64 QExtDAIODevice::id() const
{
    Q_D(const QExtDAIODevice);
    return d->mId;
}

QString QExtDAIODevice::name() const
{
    Q_D(const QExtDAIODevice);
    return this->nameFromId(d->mId);
}

QThread *QExtDAIODevice::thread() const
{
    Q_D(const QExtDAIODevice);
    return d->mThread.data();
}

QString QExtDAIODevice::nameAlias() const
{
    Q_D(const QExtDAIODevice);
    if (!d->mAlias.data()->isEmpty())
    {
        return QString("%1[%2]").arg(this->name(), d->mAlias.value());
    }
    else
    {
        return this->name();
    }
}

qint64 QExtDAIODevice::bufferSize() const
{
    Q_D(const QExtDAIODevice);
    return d->mBufferSize.get();
}

void QExtDAIODevice::setBufferSize(qint64 size)
{
    Q_D(QExtDAIODevice);
    d->mBufferSize.set(qMax(qint64(1000), size));
}

bool QExtDAIODevice::isBufferEnabled() const
{
    Q_D(const QExtDAIODevice);
    return d->mBufferEnable.load();
}

void QExtDAIODevice::setBufferEnable(bool enable)
{
    Q_D(QExtDAIODevice);
    d->mBufferEnable.store(enable);
}

QString QExtDAIODevice::alias() const
{
    Q_D(const QExtDAIODevice);
    return d->mAlias.get();
}

void QExtDAIODevice::setAlias(const QString &alias)
{
    Q_D(QExtDAIODevice);
    if (d->mAlias.reset(alias))
    {
        Q_EMIT this->aliasChanged(alias);
    }
}

QString QExtDAIODevice::ioError() const
{
    Q_D(const QExtDAIODevice);
    return d->mIOError.get();
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

QThread *QExtDAIODevice::initDevice(qint64 id)
{
    Q_D(QExtDAIODevice);
    d->mId = id;
    if (d->mThreadOnceFlag.enter())
    {
        d->mThread.reset(new QThread);
        d->mThread->start();
        this->moveToThread(d->mThread.data());
        d->mIO->moveToThread(d->mThread.data());
        d->mBpsTimer.reset(new QTimer);
        d->mBpsTimer->setInterval(1000);
        d->mBpsTimer->moveToThread(d->mThread.data());
        connect(d->mThread.data(), &QThread::finished, d->mBpsTimer.data(), &QTimer::stop);
        connect(d->mBpsTimer.data(), &QTimer::timeout, this, [=]()
                {
                    d->updateBpsValue();
                });
        connect(this, &QExtDAIODevice::stateChanged, this, [=](bool opened)
                {
                    if (opened)
                    {
                        d->mBpsTimer->start();
                    }
                    else
                    {
                        d->mBpsTimer->stop();
                    }
                });
        d->mThreadOnceFlag.leave();
    }
    return d->mThread.data();
}

bool QExtDAIODevice::clearDevice()
{
    Q_D(QExtDAIODevice);
    if (d->mClearOnceFlag.enter())
    {
        d->mThread->quit();
        d->mThread->wait();
        d->mThread.reset();
        d->mIO->disconnect();
        delete d->mIO.data();
        d->mClearOnceFlag.leave();
        return true;
    }
    return false;
}

bool QExtDAIODevice::isOpened() const
{
    Q_D(const QExtDAIODevice);
    return d->mIsOpened.load();
}

QIODevice *QExtDAIODevice::io() const
{
    Q_D(const QExtDAIODevice);
    return d->mIO.data();
}

QString QExtDAIODevice::ioPath() const
{
    Q_D(const QExtDAIODevice);
    return d->mIOPath.get();
}

QString QExtDAIODevice::ioState() const
{
    Q_D(const QExtDAIODevice);
    return d->mIOState.get();
}

void QExtDAIODevice::close()
{
    if (this->isOpened())
    {
        QTimer::singleShot(0, this, [=]()
                           {
                               this->updateIOError();
                               this->ioClose();
                           });
    }
}

void QExtDAIODevice::open()
{
    QTimer::singleShot(0, this, [=]()
                       {
                           this->updateIOError();
                           if (!this->ioOpen())
                           {
                               this->onIOOpenFailed();
                           }
                       });
}

void QExtDAIODevice::serializeLoad(const SerializedItemsMap &items)
{
    this->setAlias(items.value(QExtDAConstants::IODEVICE_PROPERTY_ALIAS, "").toString());
    this->setBufferSize(items.value(QExtDAConstants::IODEVICE_PROPERTY_BUFFER_SIZE, 1000).toLongLong());
    this->setBufferEnable(items.value(QExtDAConstants::IODEVICE_PROPERTY_BUFFER_ENABLED, true).toBool());
}

QExtSerializable::SerializedItemsMap QExtDAIODevice::serializeSave() const
{
    QExtSerializable::SerializedItemsMap items;
    items[QExtDAConstants::IODEVICE_PROPERTY_ID] = this->id();
    items[QExtDAConstants::IODEVICE_PROPERTY_TYPE] = this->ioType();
    items[QExtDAConstants::IODEVICE_PROPERTY_ALIAS] = this->alias();
    items[QExtDAConstants::IODEVICE_PROPERTY_BUFFER_SIZE] = this->bufferSize();
    items[QExtDAConstants::IODEVICE_PROPERTY_BUFFER_ENABLED] = this->isBufferEnabled();
    return items;
}

QByteArray QExtDAIODevice::readAll()
{
    Q_D(QExtDAIODevice);
    QExtSpinLock::Locker locker(d->mReadLinearBufferSpinlock);
    return d->mReadLinearBuffer.readAll();
}

bool QExtDAIODevice::canReadLine() const
{
    Q_D(const QExtDAIODevice);
    QExtSpinLock::Locker locker(d->mReadLinearBufferSpinlock);
    return d->mReadLinearBuffer.canReadLine();
}

qint64 QExtDAIODevice::bytesAvailable() const
{
    Q_D(const QExtDAIODevice);
    QExtSpinLock::Locker locker(d->mReadLinearBufferSpinlock);
    return d->mReadLinearBuffer.size();
}

int QExtDAIODevice::getChar(bool *ok)
{
    Q_D(QExtDAIODevice);
    QExtSpinLock::Locker locker(d->mReadLinearBufferSpinlock);
    return d->mReadLinearBuffer.getChar(ok);
}

qint64 QExtDAIODevice::read(char *target, qint64 size)
{
    Q_D(QExtDAIODevice);
    QExtSpinLock::Locker locker(d->mReadLinearBufferSpinlock);
    return d->mReadLinearBuffer.read(target, size);
}

qint64 QExtDAIODevice::peek(char *target, qint64 size)
{
    Q_D(QExtDAIODevice);
    QExtSpinLock::Locker locker(d->mReadLinearBufferSpinlock);
    return d->mReadLinearBuffer.peek(target, size);
}

qint64 QExtDAIODevice::readLine(char *target, qint64 size)
{
    Q_D(QExtDAIODevice);
    QExtSpinLock::Locker locker(d->mReadLinearBufferSpinlock);
    return d->mReadLinearBuffer.readLine(target, size);
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

qint64 QExtDAIODevice::loadId(const SerializedItemsMap &items)
{
    return items.value(QExtDAConstants::IODEVICE_PROPERTY_ID, -1).toLongLong();
}

QString QExtDAIODevice::loadType(const SerializedItemsMap &items)
{
    return items.value(QExtDAConstants::IODEVICE_PROPERTY_TYPE, "").toString();
}

QString QExtDAIODevice::nameFromId(qint64 id)
{
    return QString("IO%1").arg(id);
}

qint64 QExtDAIODevice::idFromName(const QString &name)
{
    bool ok = false;
    QString idString = name;
    const qlonglong id = idString.remove("IO").toLongLong(&ok);
    return ok ? id : -1;
}

void QExtDAIODevice::onIOReadyRead()
{
    Q_D(QExtDAIODevice);
    QByteArray bytes = this->ioRead();
    if (d->mBufferEnable.load())
    {
        d->mReadLinearBufferSpinlock.lock();
        const qint64 overflowSize = d->mReadLinearBuffer.size() - d->mBufferSize.get();
        if (overflowSize > 0)
        {
            d->mReadLinearBuffer.skip(overflowSize);
        }
        char *ptr = d->mReadLinearBuffer.reserve(bytes.size());
        memcpy(ptr, bytes.data(), bytes.size());
        d->mReadLinearBufferSpinlock.unlock();
        Q_EMIT this->readyRead();
    }
    else
    {
        Q_EMIT this->dataReaded(bytes, QExtDateTimeUtils::msecsTimeSinceEpoch());
    }
    d->updateRxdBps(bytes.size());
}

void QExtDAIODevice::onIOReadyWrite()
{
    Q_D(QExtDAIODevice);
    QExtSpinLock::Locker locker(d->mWriteDataQueueSpinlock);
    if (!d->mWriteDataQueue.isEmpty())
    {
        auto bytes = d->mWriteDataQueue.dequeue();
        locker.unlock();
        const qint64 size = this->ioWrite(bytes.data(), bytes.size());
        if (size > 0)
        {
            Q_EMIT this->dataWrited(QByteArray(bytes.data(), size), QExtDateTimeUtils::msecsTimeSinceEpoch());
        }
        if (bytes.size() != size)
        {
            this->onIOWriteFailed();
        }
    }
    Q_EMIT this->readyWrite();
}

void QExtDAIODevice::onIOWriteFailed()
{
}

void QExtDAIODevice::onIOOpenFailed()
{
    Q_D(QExtDAIODevice);
    qDebug() << QString("DAIODevice:%1, %2").arg(this->ioPath()).arg(d->mIO->errorString());
}

void QExtDAIODevice::onIOOpenSuccessed()
{
}

QByteArray QExtDAIODevice::ioRead()
{
    Q_D(QExtDAIODevice);
    return d->mIO->readAll();
}

bool QExtDAIODevice::ioOpen()
{
    Q_D(QExtDAIODevice);
    return d->mIO->open(QIODevice::ReadWrite);
}

void QExtDAIODevice::ioClose()
{
    Q_D(QExtDAIODevice);
    this->io()->close();
}

qint64 QExtDAIODevice::ioWrite(const char *data, qint64 len)
{
    Q_D(QExtDAIODevice);
    return d->mIO->write(data, len);
}

void QExtDAIODevice::initPropertyModel(QExtPropertyModel *propertyModel)
{
    QExtPropertyModelItem *rootItem = propertyModel->rootItem();
    rootItem->appendChild(new QExtDAIODeviceStatePropertyItem(this));
    rootItem->appendChild(new QExtDAIODeviceAliasPropertyItem(this));
}

void QExtDAIODevice::updateOpenState(bool opened)
{
    Q_D(QExtDAIODevice);
    if (d->mIsOpened.fetchAndStoreOrdered(opened) != opened)
    {
        this->onStateChanged(opened);
        Q_EMIT this->stateChanged(opened);
    }
}

void QExtDAIODevice::updateIOPath(const QString &path)
{
    Q_D(QExtDAIODevice);
    if (d->mIOPath.reset(path))
    {
        this->onIOPathChanged(path);
        Q_EMIT this->ioPathChanged(path);
    }
}

void QExtDAIODevice::updateIOState(const QString &state)
{
    Q_D(QExtDAIODevice);
    if (d->mIOState.reset(state))
    {
        this->onIOStateChanged(state);
        Q_EMIT this->ioStateChanged(state);
    }
}

void QExtDAIODevice::updateIOError(const QString &error)
{
    Q_D(QExtDAIODevice);
    if (d->mIOError.reset(error))
    {
        this->onIOErrorChanged(error);
        Q_EMIT this->ioErrorChanged(error);
    }
}


QExtDAIODeviceStatePropertyItem::QExtDAIODeviceStatePropertyItem(QExtDAIODevice *ioDevice)
    : mIODevice(ioDevice)
{
    connect(ioDevice, &QExtDAIODevice::ioStateChanged, this, &QExtPropertyModelItem::updateItem);
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
        return mIODevice->ioState();
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

