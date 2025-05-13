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

    QExtDAIODeviceManager * const q_ptr;

    QExtIdRegistry mIdRegistry;
    QList<QExtDAIODevice *> mIODeviceList;
    QMap<quint64, QExtDAIODevice *> mIdToIODeviceMap;
    QMap<QString, QExtDAIODevice *> mNameToIODeviceMap;
    QMap<QExtDAIODevice *, QThread *> mIODeviceThreadMap;

    QScopedPointer<QExtDAIODeviceModel> mIODeviceModel;

private:
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
}

int QExtDAIODeviceManager::ioDeviceCount() const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mIODeviceList.size();
}

QExtDAIODevice *QExtDAIODeviceManager::ioDevice(int index) const
{
    Q_D(const QExtDAIODeviceManager);
    if (index < 0 || index >= d->mIODeviceList.size())
    {
        qCritical() << "QExtDAIODeviceManager::ioDevice():index out of range";
        return nullptr;
    }
    return d->mIODeviceList.at(index);
}

QList<QExtDAIODevice *> QExtDAIODeviceManager::ioDeviceList() const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mIODeviceList;
}

int QExtDAIODeviceManager::ioDeviceIndex(QExtDAIODevice *ioDevice) const
{
    Q_D(const QExtDAIODeviceManager);
    return d->mIODeviceList.indexOf(ioDevice);
}

void QExtDAIODeviceManager::deleteAllIODevices()
{
}

void QExtDAIODeviceManager::deleteIODevice(QExtDAIODevice *ioDevice)
{
    Q_D(QExtDAIODeviceManager);
    if (ioDevice)
    {
        ioDevice->disconnect();
        if (ioDevice->isOpened())
        {
            ioDevice->close();
        }
        quint64 id = ioDevice->id();
        emit this->ioDeviceAboutToBeDelete(ioDevice, id);
        QThread *thread = d->mIODeviceThreadMap.take(ioDevice);
        d->mNameToIODeviceMap.remove(ioDevice->name());
        d->mIODeviceList.removeOne(ioDevice);
        d->mIdRegistry.unregisterId(id);
        d->mIdToIODeviceMap.remove(id);
        emit this->ioDeviceDeleted(id);
        thread->quit();
        thread->wait();
        delete ioDevice;
    }
}

QExtDAIODevice *QExtDAIODeviceManager::createIODevice(QExtDAIODevice *ioDevice, quint64 id)
{
    Q_D(QExtDAIODeviceManager);
    Q_ASSERT(ioDevice);
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
    connect(ioDevice, &QExtDAIODevice::aliasChanged, this, [=]()
            {
                emit this->ioDevicePropertyChanged(ioDevice, QExtDAConstants::IODEVICE_PROPERTY_ALIAS);
            });
    connect(ioDevice, &QExtDAIODevice::stateChanged, this, [=]()
            {
                emit this->ioDevicePropertyChanged(ioDevice, QExtDAConstants::IODEVICE_PROPERTY_STATE);
            });
    connect(ioDevice, &QExtDAIODevice::pathChanged, this, [=]()
            {
                emit this->ioDevicePropertyChanged(ioDevice, QExtDAConstants::IODEVICE_PROPERTY_PATH);
            });
    connect(ioDevice, &QExtDAIODevice::bpsChanged, this, [=]()
            {
                emit this->ioDevicePropertyChanged(ioDevice, QExtDAConstants::IODEVICE_PROPERTY_BPS);
            });
    qSort(d->mIODeviceList.begin(), d->mIODeviceList.end(), [=](QExtDAIODevice *lhs, QExtDAIODevice *rhs)
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

QExtDAIODeviceManager::QExtDAIODeviceManager(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtDAIODeviceManagerPrivate(this))
{
}
