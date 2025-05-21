#include <qextDAIODeviceManager.h>
#include <qextDAIODeviceModel.h>
#include <qextDAConstants.h>
#include <qextDAIODevice.h>
#include <qextIdRegistry.h>
#include <qextOnceFlag.h>

#include <QMap>
#include <QList>
#include <QDebug>
#include <QThread>

class QExtDAIODeviceManagerPrivate
{
public:
    explicit QExtDAIODeviceManagerPrivate(QExtDAIODeviceManager *q);
    virtual ~QExtDAIODeviceManagerPrivate();

    QExtIdRegistry mIdRegistry;
    QExtDAIODeviceFactory mIODeviceFactory;
    QList<QExtDAIODevice::SharedPointer> mIODeviceList;
    QMap<qint64, QExtDAIODevice::SharedPointer> mIdToIODeviceMap;
    QMap<QString, QExtDAIODevice::SharedPointer> mNameToIODeviceMap;
    QMap<QExtDAIODevice::SharedPointer, QThread *> mIODeviceThreadMap;

    QScopedPointer<QExtDAIODeviceModel> mIODeviceModel;

protected:
    QExtDAIODeviceManager * const q_ptr;
    Q_DECLARE_PUBLIC(QExtDAIODeviceManager)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceManagerPrivate)
};

QExtDAIODeviceManagerPrivate::QExtDAIODeviceManagerPrivate(QExtDAIODeviceManager *q)
    : q_ptr(q)
{
}

QExtDAIODeviceManagerPrivate::~QExtDAIODeviceManagerPrivate()
{
}

QExtDAIODeviceManager *QExtDAIODeviceManager::instance()
{
    static QExtOnceFlag onceFlag;
    static QExtDAIODeviceManager *instance = QEXT_NULLPTR;
    qextCallOnce(onceFlag, [=](){ instance = new QExtDAIODeviceManager; });
    return instance;
}

QExtDAIODeviceManager::~QExtDAIODeviceManager()
{
    this->deleteAllIODevices();
}

QExtDAIODeviceFactory &QExtDAIODeviceManager::ioDeviceFactory()
{
    Q_D(QExtDAIODeviceManager);
    return d->mIODeviceFactory;
}

int QExtDAIODeviceManager::ioDeviceCount() const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mIODeviceList.size();
}

QExtDAIODevice::SharedPointer QExtDAIODeviceManager::ioDevice(int index) const
{
    Q_D(const QExtDAIODeviceManager);
    if (index < 0 || index >= d->mIODeviceList.size())
    {
        qCritical() << "QExtDAIODeviceManager::ioDevice():index out of range";
        return nullptr;
    }
    return d->mIODeviceList.at(index);
}

QList<QExtDAIODevice::SharedPointer> QExtDAIODeviceManager::ioDeviceList() const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mIODeviceList;
}

int QExtDAIODeviceManager::ioDeviceIndex(const QExtDAIODevice::SharedPointer &ioDevice) const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mIODeviceList.indexOf(ioDevice);
}

void QExtDAIODeviceManager::deleteAllIODevices()
{
    Q_D(QExtDAIODeviceManager);
    QList<QExtDAIODevice::SharedPointer> ioDeviceList = d->mIODeviceList;
    for (int i = 0; i < ioDeviceList.size(); ++i)
    {
        this->deleteIODevice(ioDeviceList[i]);
    }
}

void QExtDAIODeviceManager::deleteIODevice(QExtDAIODevice::SharedPointer &ioDevice)
{
    Q_D(QExtDAIODeviceManager);
    if (ioDevice)
    {
        ioDevice->disconnect();
        if (ioDevice->isOpened())
        {
            ioDevice->close();
        }
        qint64 id = ioDevice->id();
        emit this->ioDeviceAboutToBeDelete(ioDevice, id);
        d->mIODeviceThreadMap.take(ioDevice);
        d->mNameToIODeviceMap.remove(ioDevice->name());
        d->mIODeviceList.removeOne(ioDevice);
        d->mIdRegistry.unregisterId(id);
        d->mIdToIODeviceMap.remove(id);
        emit this->ioDeviceDeleted(id);
        ioDevice->destroyDevice();
    }
}

QExtDAIODevice::SharedPointer QExtDAIODeviceManager::registerIODevice(const QExtDAIODevice::SharedPointer &ioDevice,
                                                                      qint64 id)
{
    Q_D(QExtDAIODeviceManager);
    Q_ASSERT(!ioDevice.isNull());
    if (this->ioDeviceCount() >= QExtDAConstants::IODEVICE_MAX_COUNT)
    {
        qCritical() << QString("QExtDAIODeviceManager::createIODevice():io device max number is %1").
                       arg(QExtDAConstants::IODEVICE_MAX_COUNT);
        ioDevice->deleteLater();
        return QEXT_NULLPTR;
    }

    if (0 == id)
    {
        id = d->mIdRegistry.requestId();
    }
    d->mIdRegistry.registerId(id);
    QThread *thread = ioDevice->initDevice(id);
    if (!thread)
    {
        qCritical() << QString("QExtDAIODeviceManager::createIODevice():io device init failed!");
        d->mIdRegistry.unregisterId(id);
        ioDevice->deleteLater();
        return QEXT_NULLPTR;
    }
    emit this->ioDeviceAboutToBeCreated(id);
    d->mIODeviceList.append(ioDevice);
    d->mIdToIODeviceMap.insert(id, ioDevice);
    d->mIODeviceThreadMap.insert(ioDevice, thread);
    d->mNameToIODeviceMap.insert(ioDevice->name(), ioDevice);
    connect(ioDevice.data(), &QExtDAIODevice::aliasChanged, this, [=]()
            {
                emit this->ioDevicePropertyChanged(ioDevice, QExtDAConstants::IODEVICE_PROPERTY_ALIAS);
            });
    connect(ioDevice.data(), &QExtDAIODevice::ioStateChanged, this, [=]()
            {
                emit this->ioDevicePropertyChanged(ioDevice, QExtDAConstants::IODEVICE_PROPERTY_STATE);
            });
    connect(ioDevice.data(), &QExtDAIODevice::ioPathChanged, this, [=]()
            {
                emit this->ioDevicePropertyChanged(ioDevice, QExtDAConstants::IODEVICE_PROPERTY_PATH);
            });
    connect(ioDevice.data(), &QExtDAIODevice::rxdBpsChanged, this, [=]()
            {
                emit this->ioDevicePropertyChanged(ioDevice, QExtDAConstants::IODEVICE_PROPERTY_BPS);
            });
    qSort(d->mIODeviceList.begin(), d->mIODeviceList.end(), [=](const QExtDAIODevice::SharedPointer &lhs,
                                                                const QExtDAIODevice::SharedPointer &rhs)
          {
              return lhs->id() < rhs->id();
          });
    emit this->ioDeviceCreated(ioDevice, id);
    return ioDevice;
}

QExtDAIODeviceModel *QExtDAIODeviceManager::makeIODeviceModel(QObject *parent)
{
    return new QExtDAIODeviceModel(this, parent ? parent : this);
}

QExtDAIODevice::SharedPointer QExtDAIODeviceManager::selectCreateIODevice(QWidget *parent)
{
    Q_D(QExtDAIODeviceManager);
    QExtDAIODevice::SharedPointer ioDevice = d->mIODeviceFactory.selectCreateIODevice(parent);
    return !ioDevice.isNull() ? this->registerIODevice(ioDevice) : ioDevice;
}

void QExtDAIODeviceManager::load(const Items &items)
{
    Q_D(QExtDAIODeviceManager);
    QExtDASerializable::Items::ConstIterator iter(items.constBegin());
    while (items.constEnd() != iter)
    {
        const QExtDASerializable::Items childItems = iter.value().toHash();
        const QString type = QExtDAIODevice::loadType(childItems);
        const qint64 id = QExtDAIODevice::loadId(childItems);
        if (id >= 0 && !type.isEmpty())
        {
            QExtDAIODevice::SharedPointer ioDevice = d->mIODeviceFactory.createIODevice(type);
            ioDevice = this->registerIODevice(ioDevice, id);
            if (!ioDevice.isNull())
            {
                ioDevice->load(childItems);
            }
        }
        iter++;
    }
}

QExtDASerializable::Items QExtDAIODeviceManager::save() const
{
    Q_D(const QExtDAIODeviceManager);
    QExtDASerializable::Items items;
    QList<QExtDAIODevice::SharedPointer>::ConstIterator iter(d->mIODeviceList.constBegin());
    while (d->mIODeviceList.constEnd() != iter)
    {
        items.insert((*iter)->name() ,(*iter)->save());
        iter++;
    }
    return items;
}

QExtDAIODeviceManager::QExtDAIODeviceManager(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtDAIODeviceManagerPrivate(this))
{
}
