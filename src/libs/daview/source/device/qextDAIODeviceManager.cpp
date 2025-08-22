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
    QList<QExtDAIODevice::SharedPtr> mIODeviceList;
    QMap<qint64, QExtDAIODevice::SharedPtr> mIdToIODeviceMap;
    QMap<QString, QExtDAIODevice::SharedPtr> mNameToIODeviceMap;
    QMap<QExtDAIODevice::SharedPtr, QThread *> mIODeviceThreadMap;

    QScopedPointer<QExtDAIODeviceModel> mIODeviceModel;

protected:
    QExtDAIODeviceManager * const q_ptr;
    Q_DECLARE_PUBLIC(QExtDAIODeviceManager)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDAIODeviceManagerPrivate)
};

QExtDAIODeviceManagerPrivate::QExtDAIODeviceManagerPrivate(QExtDAIODeviceManager *q)
    : q_ptr(q)
{
}

QExtDAIODeviceManagerPrivate::~QExtDAIODeviceManagerPrivate()
{
}

QExtDAIODeviceManager::~QExtDAIODeviceManager()
{
    this->clearAllIODevices();
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

QExtDAIODevice::SharedPtr QExtDAIODeviceManager::ioDevice(int index) const
{
    Q_D(const QExtDAIODeviceManager);
    if (index < 0 || index >= d->mIODeviceList.size())
    {
        qCritical() << "QExtDAIODeviceManager::ioDevice():index out of range";
        return nullptr;
    }
    return d->mIODeviceList.at(index);
}

QExtDAIODevice::SharedPtr QExtDAIODeviceManager::ioDevice(const QString &name) const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mNameToIODeviceMap.value(name);
}

QList<QExtDAIODevice::SharedPtr> QExtDAIODeviceManager::ioDeviceList() const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mIODeviceList;
}

int QExtDAIODeviceManager::ioDeviceIndex(const QExtDAIODevice::SharedPtr &ioDevice) const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mIODeviceList.indexOf(ioDevice);
}

void QExtDAIODeviceManager::clearAllIODevices()
{
    Q_D(QExtDAIODeviceManager);
    QList<QExtDAIODevice::SharedPtr> ioDeviceList = d->mIODeviceList;
    for (int i = 0; i < ioDeviceList.size(); ++i)
    {
        this->clearIODevice(ioDeviceList[i]);
    }
}

void QExtDAIODeviceManager::clearIODevice(QExtDAIODevice::SharedPtr &ioDevice)
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
        emit this->ioDeviceListChanged(d->mIODeviceList);
        ioDevice->clearDevice();
    }
}

QExtDAIODevice::SharedPtr QExtDAIODeviceManager::registerIODevice(const QExtDAIODevice::SharedPtr &ioDevice,
                                                                  qint64 id)
{
    Q_D(QExtDAIODeviceManager);
    Q_ASSERT(!ioDevice.isNull());
    if (this->ioDeviceCount() >= QExtDAConstants::IODEVICE_MAX_COUNT)
    {
        qCritical() << QString("QExtDAIODeviceManager::registerIODevice():io device max number is %1").
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
        qCritical() << QString("QExtDAIODeviceManager::registerIODevice():io device init failed!");
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
    qSort(d->mIODeviceList.begin(), d->mIODeviceList.end(), [=](const QExtDAIODevice::SharedPtr &lhs,
                                                                const QExtDAIODevice::SharedPtr &rhs)
          {
              return lhs->id() < rhs->id();
          });
    emit this->ioDeviceCreated(ioDevice, id);
    emit this->ioDeviceListChanged(d->mIODeviceList);
    return ioDevice;
}

QExtDAIODeviceModel *QExtDAIODeviceManager::makeIODeviceModel(QObject *parent)
{
    return new QExtDAIODeviceModel(this, parent ? parent : this);
}

QExtDAIODevice::SharedPtr QExtDAIODeviceManager::selectCreateIODevice(QWidget *parent)
{
    Q_D(QExtDAIODeviceManager);
    QExtDAIODevice::SharedPtr ioDevice = d->mIODeviceFactory.selectCreateIODevice(parent);
    return !ioDevice.isNull() ? this->registerIODevice(ioDevice) : ioDevice;
}

void QExtDAIODeviceManager::serializeLoad(const SerializedItemsMap &items)
{
    Q_D(QExtDAIODeviceManager);
    QExtSerializable::SerializedItemsMap::ConstIterator iter(items.constBegin());
    while (items.constEnd() != iter)
    {
        const QExtSerializable::SerializedItemsMap childItems = iter.value().toMap();
        const QString type = QExtDAIODevice::loadType(childItems);
        const qint64 id = QExtDAIODevice::loadId(childItems);
        if (id >= 0 && !type.isEmpty())
        {
            QExtDAIODevice::SharedPtr ioDevice = d->mIODeviceFactory.createIODevice(type);
            ioDevice = this->registerIODevice(ioDevice, id);
            if (!ioDevice.isNull())
            {
                ioDevice->serializeLoad(childItems);
            }
        }
        iter++;
    }
}

QExtSerializable::SerializedItemsMap QExtDAIODeviceManager::serializeSave() const
{
    Q_D(const QExtDAIODeviceManager);
    QExtSerializable::SerializedItemsMap items;
    QList<QExtDAIODevice::SharedPtr>::ConstIterator iter(d->mIODeviceList.constBegin());
    while (d->mIODeviceList.constEnd() != iter)
    {
        items.insert((*iter)->name() ,(*iter)->serializeSave());
        iter++;
    }
    return items;
}

QExtDAIODeviceManager::QExtDAIODeviceManager(QObject *parent)
    : QExtSerializableObject(parent)
    , dd_ptr(new QExtDAIODeviceManagerPrivate(this))
{
}
