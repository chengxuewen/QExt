#ifndef _QEXTDAIODEVICE_P_H
#define _QEXTDAIODEVICE_P_H

#include <qextDAIODevice.h>
#include <qextSpinlock.h>
#include <qextOnceFlag.h>

#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QPointer>

class QEXT_DAVIEW_API QExtDAIODevicePrivate
{
public:
    explicit QExtDAIODevicePrivate(QExtDAIODevice *q);
    virtual ~QExtDAIODevicePrivate();

    void initIO(QIODevice *io);
    void updateByteCount(qulonglong rxCount);

    QExtDAIODevice * const q_ptr;

    int mRXBps;
    quint64 mId;
    QString mAlias;
    QPointer<QIODevice> mIO;
    qulonglong mRXByteCount;
    qulonglong mRXByteAllCount;
    QExtOnceFlag mThreadOnceFlag;
    QScopedPointer<QThread> mThread;
    QScopedPointer<QTimer> mRXBpsTimer;
    QQueue<QByteArray> mWriteDataQueue;
    QExtSpinLock mWriteDataQueueSpinlock;
    QScopedPointer<QExtPropertyModel> mPropertyModel;

private:
    Q_DECLARE_PUBLIC(QExtDAIODevice)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODevicePrivate)
};

#endif // _QEXTDAIODEVICE_P_H
