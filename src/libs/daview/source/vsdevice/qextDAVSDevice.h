#ifndef _QEXTDAVSDEVICE_H
#define _QEXTDAVSDEVICE_H

#include <qextDAViewGlobal.h>

#include <qextSerializable.h>

#include <QObject>

class QExtDAVSDevicePrivate;
class QEXT_DAVIEW_API QExtDAVSDevice : public QObject, public QExtSerializable
{
    Q_OBJECT
public:
    typedef QSharedPointer<QExtDAVSDevice> SharedPtr;

    explicit QExtDAVSDevice(QObject *parent = QEXT_NULLPTR);
    QExtDAVSDevice(QExtDAVSDevicePrivate *d, QObject *parent = QEXT_NULLPTR);
    ~QExtDAVSDevice() QEXT_OVERRIDE;

    // SerializedItems serializeSave() const QEXT_OVERRIDE;
    // void serializeLoad(const SerializedItems &items) QEXT_OVERRIDE;

protected:
    QScopedPointer<QExtDAVSDevicePrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtDAVSDevice)
    QEXT_DISABLE_COPY_MOVE(QExtDAVSDevice)
};

#endif // _QEXTDAVSDEVICE_H
