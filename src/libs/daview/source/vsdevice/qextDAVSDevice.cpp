#include <private/qextDAVSDevice_p.h>

QExtDAVSDevicePrivate::QExtDAVSDevicePrivate(QExtDAVSDevice *q)
    : q_ptr(q)
{
}

QExtDAVSDevicePrivate::~QExtDAVSDevicePrivate()
{
}

QExtDAVSDevice::QExtDAVSDevice(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtDAVSDevicePrivate(this))
{
}

QExtDAVSDevice::QExtDAVSDevice(QExtDAVSDevicePrivate *d, QObject *parent)
    : QObject(parent)
    , dd_ptr(d)
{
}

QExtDAVSDevice::~QExtDAVSDevice()
{
}
