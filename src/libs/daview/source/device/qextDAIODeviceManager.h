#ifndef _QEXTDAIODEVICEMANAGER_H
#define _QEXTDAIODEVICEMANAGER_H

#include <QObject>

#include <qextSingleton.h>
#include <qextDAViewGlobal.h>
#include <qextSerializable.h>
#include <qextDAIODeviceFactory.h>

class QExtDAIODevice;
class QExtDAIODeviceModel;
class QExtDAIODeviceManagerPrivate;
class QEXT_DAVIEW_API QExtDAIODeviceManager : public QExtSerializableObject, public QExtSingleton<QExtDAIODeviceManager>
{
    Q_OBJECT
    QEXT_DECLARE_SINGLETON(QExtDAIODeviceManager)
public:

    QExtDAIODeviceFactory &ioDeviceFactory();

    int ioDeviceCount() const;
    QExtDAIODevice::SharedPtr ioDevice(int index) const;
    QExtDAIODevice::SharedPtr ioDevice(const QString &name) const;
    QList<QExtDAIODevice::SharedPtr> ioDeviceList() const;
    int ioDeviceIndex(const QExtDAIODevice::SharedPtr &ioDevice) const;

    void clearAllIODevices();
    void clearIODevice(QExtDAIODevice::SharedPtr &ioDevice);
    QExtDAIODevice::SharedPtr registerIODevice(const QExtDAIODevice::SharedPtr &ioDevice, qint64 id = 0);

    QExtDAIODeviceModel *makeIODeviceModel(QObject *parent = QEXT_NULLPTR);
    QExtDAIODevice::SharedPtr selectCreateIODevice(QWidget *parent = QEXT_NULLPTR);

    void serializeLoad(const SerializedItemsMap &items) QEXT_OVERRIDE;
    SerializedItemsMap serializeSave() const QEXT_OVERRIDE;

Q_SIGNALS:
    void ioDeviceAboutToBeDelete(const QExtDAIODevice::SharedPtr &ioDevice, qint64 id);
    void ioDeviceDeleted(qint64 id);

    void ioDeviceAboutToBeCreated(qint64 id);
    void ioDeviceCreated(const QExtDAIODevice::SharedPtr &ioDevice, qint64 id);

    void ioDeviceListChanged(const QList<QExtDAIODevice::SharedPtr> &ioDeviceList);
    void ioDevicePropertyChanged(const QExtDAIODevice::SharedPtr &ioDevice, const QString &name);

protected:
    explicit QExtDAIODeviceManager(QObject *parent = QEXT_NULLPTR);
    ~QExtDAIODeviceManager() QEXT_OVERRIDE;

    QScopedPointer<QExtDAIODeviceManagerPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAIODeviceManager)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceManager)
};

#define qextDAIODeviceManager QExtDAIODeviceManager::instance()

#endif // _QEXTDAIODEVICEMANAGER_H
