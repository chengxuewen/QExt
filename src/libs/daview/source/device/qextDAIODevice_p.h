#ifndef _QEXTDAIODEVICE_P_H
#define _QEXTDAIODEVICE_P_H

#include <qextLinearBuffer.h>
#include <qextConcurrent.h>
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

    void updateBpsValue();
    void updateRxdBps(qulonglong rxdCount);
    void updateTxdBps(qulonglong txdCount);

    QExtDAIODevice * const q_ptr;

    QAtomicInt mRxdBps;
    QAtomicInt mTxdBps;
    qulonglong mRxdByteCount;
    qulonglong mTxdByteCount;
    qulonglong mRxdByteAllCount;
    qulonglong mTxdByteAllCount;
    QScopedPointer<QTimer> mBpsTimer;

    qint64 mId;
    QAtomicInt mIsOpened;
    QExtConcurrent<QString> mAlias;
    QExtConcurrent<QString> mIOPath;
    QExtConcurrent<QString> mIOState;
    QExtConcurrent<QString> mIOError;

    QPointer<QIODevice> mIO;
    QAtomicInt mBufferEnable;
    QExtOnceFlag mThreadOnceFlag;
    QExtOnceFlag mClearOnceFlag;
    QExtConcurrentInt64 mBufferSize;
    QScopedPointer<QThread> mThread;


    QQueue<QByteArray> mWriteDataQueue;
    QExtLinearBuffer mReadLinearBuffer;
    mutable QExtSpinLock mWriteDataQueueSpinlock;
    mutable QExtSpinLock mReadLinearBufferSpinlock;
    QScopedPointer<QExtPropertyModel> mPropertyModel;

private:
    Q_DECLARE_PUBLIC(QExtDAIODevice)
    QEXT_DISABLE_COPY_MOVE(QExtDAIODevicePrivate)
};

#endif // _QEXTDAIODEVICE_P_H
