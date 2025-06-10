#ifndef _QEXTDAIODEVICEMANAGER_H
#define _QEXTDAIODEVICEMANAGER_H

#include <QObject>

#include <qextDAViewGlobal.h>
#include <qextSerializable.h>
#include <qextDAIODeviceFactory.h>

class QExtDAIODevice;
class QExtDAIODeviceModel;
class QExtDAIODeviceManagerPrivate;
class QEXT_DAVIEW_API QExtDAIODeviceManager : public QObject, public QExtSerializable
{
    Q_OBJECT
public:
    static QExtDAIODeviceManager *instance();
    ~QExtDAIODeviceManager() QEXT_OVERRIDE;

    QExtDAIODeviceFactory &ioDeviceFactory();

    int ioDeviceCount() const;
    QExtDAIODevice::SharedPtr ioDevice(int index) const;
    QExtDAIODevice::SharedPtr ioDevice(const QString &name) const;
    QList<QExtDAIODevice::SharedPtr> ioDeviceList() const;
    int ioDeviceIndex(const QExtDAIODevice::SharedPtr &ioDevice) const;

    void deleteAllIODevices();
    void deleteIODevice(QExtDAIODevice::SharedPtr &ioDevice);
    QExtDAIODevice::SharedPtr registerIODevice(const QExtDAIODevice::SharedPtr &ioDevice, qint64 id = 0);

    QExtDAIODeviceModel *makeIODeviceModel(QObject *parent = QEXT_NULLPTR);
    QExtDAIODevice::SharedPtr selectCreateIODevice(QWidget *parent = QEXT_NULLPTR);

    void serializeLoad(const SerializedItems &items) QEXT_OVERRIDE;
    SerializedItems serializeSave() const QEXT_OVERRIDE;

Q_SIGNALS:
    void ioDeviceAboutToBeDelete(const QExtDAIODevice::SharedPtr &ioDevice, qint64 id);
    void ioDeviceDeleted(qint64 id);

    void ioDeviceAboutToBeCreated(qint64 id);
    void ioDeviceCreated(const QExtDAIODevice::SharedPtr &ioDevice, qint64 id);

    void ioDeviceListChanged(const QList<QExtDAIODevice::SharedPtr> &ioDeviceList);
    void ioDevicePropertyChanged(const QExtDAIODevice::SharedPtr &ioDevice, const QString &name);

protected:
    explicit QExtDAIODeviceManager(QObject *parent = QEXT_NULLPTR);

    QScopedPointer<QExtDAIODeviceManagerPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAIODeviceManager)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceManager)
};

#endif // _QEXTDAIODEVICEMANAGER_H
