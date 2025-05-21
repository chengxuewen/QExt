#ifndef _QEXTDAIOREADER_P_H
#define _QEXTDAIOREADER_P_H

#include <qextDAIOReader.h>
#include <qextDAIODevice.h>

#include <QPointer>

class QExtDAIOReaderPrivate
{
public:
    explicit QExtDAIOReaderPrivate(QExtDAIOReader *q);
    virtual ~QExtDAIOReaderPrivate();

    QPointer<QExtDAIODevice> mDAIODevice;

protected:
    QExtDAIOReader * const q_ptr;
    Q_DECLARE_PUBLIC(QExtDAIOReader)
    QEXT_DISABLE_COPY_MOVE(QExtDAIOReaderPrivate)
};


#endif // _QEXTDAIOREADER_P_H
