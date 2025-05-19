#ifndef _QEXTDAIODEVICEMANAGER_H
#define _QEXTDAIODEVICEMANAGER_H

#include <QObject>

#include <qextDAViewGlobal.h>
#include <qextDASerializable.h>
#include <qextDAIODeviceFactory.h>

class QExtDAIODevice;
class QExtDAIODeviceModel;
class QExtDAIODeviceManagerPrivate;
class QEXT_DAVIEW_API QExtDAIODeviceManager : public QObject, public QExtDASerializable
{
    Q_OBJECT
public:
    static QExtDAIODeviceManager *instance();
    ~QExtDAIODeviceManager() QEXT_OVERRIDE;

    QExtDAIODeviceFactory &ioDeviceFactory();

    int ioDeviceCount() const;
    QExtDAIODevice::SharedPointer ioDevice(int index) const;
    QList<QExtDAIODevice::SharedPointer> ioDeviceList() const;
    int ioDeviceIndex(const QExtDAIODevice::SharedPointer &ioDevice) const;

    void deleteAllIODevices();
    void deleteIODevice(QExtDAIODevice::SharedPointer &ioDevice);
    QExtDAIODevice::SharedPointer registerIODevice(const QExtDAIODevice::SharedPointer &ioDevice, qint64 id = 0);

    QExtDAIODeviceModel *makeIODeviceModel(QObject *parent = QEXT_NULLPTR);
    QExtDAIODevice::SharedPointer selectCreateIODevice(QWidget *parent = QEXT_NULLPTR);

    void load(const Items &items) QEXT_OVERRIDE;
    Items save() const QEXT_OVERRIDE;

Q_SIGNALS:
    void ioDeviceAboutToBeDelete(const QExtDAIODevice::SharedPointer &ioDevice, qint64 id);
    void ioDeviceDeleted(qint64 id);

    void ioDeviceAboutToBeCreated(qint64 id);
    void ioDeviceCreated(const QExtDAIODevice::SharedPointer &ioDevice, qint64 id);

    void ioDevicePropertyChanged(const QExtDAIODevice::SharedPointer &ioDevice, const QString &name);

protected:
    explicit QExtDAIODeviceManager(QObject *parent = QEXT_NULLPTR);

    QScopedPointer<QExtDAIODeviceManagerPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAIODeviceManager)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceManager)
};

#endif // _QEXTDAIODEVICEMANAGER_H
