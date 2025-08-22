#ifndef _QEXTDAVSDEVICE_P_H
#define _QEXTDAVSDEVICE_P_H

#include <qextDAVSDevice.h>

class QExtDAVSDevicePrivate
{
    QExtDAVSDevice * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtDAVSDevice)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDAVSDevicePrivate)
public:
    explicit QExtDAVSDevicePrivate(QExtDAVSDevice *q);
    virtual ~QExtDAVSDevicePrivate();
};

#endif // _QEXTDAVSDEVICE_P_H
