#ifndef _QEXTDAIODEVICEMANAGER_H
#define _QEXTDAIODEVICEMANAGER_H

#include <QObject>

#include <qextDAViewGlobal.h>

class QExtDAIODevice;
class QExtDAIODeviceModel;
class QExtDAIODeviceManagerPrivate;
class QEXT_DAVIEW_API QExtDAIODeviceManager : public QObject
{
    Q_OBJECT
public:
    static QExtDAIODeviceManager *instance();
    ~QExtDAIODeviceManager() QEXT_OVERRIDE;

    int ioDeviceCount() const;
    QExtDAIODevice *ioDevice(int index) const;
    QList<QExtDAIODevice *> ioDeviceList() const;
    int ioDeviceIndex(QExtDAIODevice *ioDevice) const;

    void deleteAllIODevices();
    void deleteIODevice(QExtDAIODevice *ioDevice);
    QExtDAIODevice *createIODevice(QExtDAIODevice *ioDevice, quint64 id = 0);

    QExtDAIODeviceModel *makeIODeviceModel(QObject *parent = QEXT_NULLPTR);

Q_SIGNALS:
    void ioDeviceAboutToBeDelete(QExtDAIODevice *ioDevice, quint64 id);
    void ioDeviceDeleted(quint64 id);

    void ioDeviceAboutToBeCreated(quint64 id);
    void ioDeviceCreated(QExtDAIODevice *ioDevice, quint64 id);

    void ioDevicePropertyChanged(QExtDAIODevice *ioDevice, const QString &name);

protected:
    explicit QExtDAIODeviceManager(QObject *parent = QEXT_NULLPTR);

    QScopedPointer<QExtDAIODeviceManagerPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAIODeviceManager)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODeviceManager)
};

#endif // _QEXTDAIODEVICEMANAGER_H
