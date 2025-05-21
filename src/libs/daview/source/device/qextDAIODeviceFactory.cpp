#include <qextDAIODeviceFactory.h>
#include <qextDATcpSocketIODevice.h>
#include <qextDAUdpSocketIODevice.h>
#include <qextDASerialPortIODevice.h>
#include <qextDAConstants.h>
#include <qextInputDialog.h>

#include <QMutex>

typedef QHash<QString, QExtDAIODeviceCreaterFunc> QExtDAIODeviceCreaterMap;

class QExtDAIODeviceFactoryPrivate
{
public:
    explicit QExtDAIODeviceFactoryPrivate(QExtDAIODeviceFactory *q);
    virtual ~QExtDAIODeviceFactoryPrivate();

    mutable QMutex mMutex;
    QExtDAIODeviceCreaterMap mIODeviceCreaterMaps;

protected:
    QExtDAIODeviceFactory * const q_ptr;
    Q_DECLARE_PUBLIC(QExtDAIODeviceFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceFactoryPrivate)
};

QExtDAIODeviceFactoryPrivate::QExtDAIODeviceFactoryPrivate(QExtDAIODeviceFactory *q)
    : q_ptr(q)
{
}

QExtDAIODeviceFactoryPrivate::~QExtDAIODeviceFactoryPrivate()
{
}

QExtDAIODeviceFactory::QExtDAIODeviceFactory(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtDAIODeviceFactoryPrivate(this))
{
    this->registerIODevice<QExtDASerialPortIODevice>(QExtDAConstants::IODEVICE_TYPE_SERIALPORT);
    this->registerIODevice<QExtDATcpSocketIODevice>(QExtDAConstants::IODEVICE_TYPE_TCPSOCKET);
    this->registerIODevice<QExtDAUdpSocketIODevice>(QExtDAConstants::IODEVICE_TYPE_UDPSOCKET);
}

QExtDAIODeviceFactory::~QExtDAIODeviceFactory()
{
}

QStringList QExtDAIODeviceFactory::ioDeviceTypes() const
{
    Q_D(const QExtDAIODeviceFactory);
    QMutexLocker locker(&d->mMutex);
    return d->mIODeviceCreaterMaps.keys();
}

QExtDAIODevice::SharedPointer QExtDAIODeviceFactory::createIODevice(const QString &type) const
{
    Q_D(const QExtDAIODeviceFactory);
    QMutexLocker locker(&d->mMutex);
    QExtDAIODeviceCreaterMap::ConstIterator iter = d->mIODeviceCreaterMaps.find(type);
    if (d->mIODeviceCreaterMaps.constEnd() != iter)
    {
        QExtDAIODeviceCreaterFunc func = iter.value();
        if (func)
        {
            return func();
        }
    }
    return QEXT_NULLPTR;
}

void QExtDAIODeviceFactory::registerIODevice(const QString &type, QExtDAIODeviceCreaterFunc func)
{
    Q_D(QExtDAIODeviceFactory);
    QMutexLocker locker(&d->mMutex);
    d->mIODeviceCreaterMaps.insert(type, func);
}

QStandardItemModel *QExtDAIODeviceFactory::makeIODeviceTypeListModel(QObject *parent) const
{
    const QStringList types = this->ioDeviceTypes();
    QStandardItemModel *model = new QStandardItemModel(parent);
    for (int i = 0; i < types.size(); ++i)
    {
        model->appendRow(new QStandardItem(types.at(i)));
    }
    return model;
}

QExtDAIODevice::SharedPointer QExtDAIODeviceFactory::selectCreateIODevice(QWidget *parent) const
{
    bool ok = false;
    const QStringList types = this->ioDeviceTypes();
    const QString type = QExtInputDialog::getItem(parent, tr("Select Create IODevice"),
                                                  tr("Types:"), types, 0, false, &ok,
                                                  !Qt::WindowContextHelpButtonHint);
    if (ok && !type.isEmpty())
    {
        return this->createIODevice(type);
    }
    return QEXT_NULLPTR;
}
