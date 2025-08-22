#ifndef _QEXTDAIOREADER_H
#define _QEXTDAIOREADER_H

#include <QObject>

#include <qextDAViewGlobal.h>

class QExtDAIODevice;
class QExtDAIOReaderPrivate;
class QEXT_DAVIEW_API QExtDAIOReader : public QObject
{
    Q_OBJECT
public:
    explicit QExtDAIOReader(QObject *parent = QEXT_NULLPTR);
    QExtDAIOReader(QExtDAIOReaderPrivate *d, QObject *parent = QEXT_NULLPTR);
    ~QExtDAIOReader() QEXT_OVERRIDE;

    virtual bool initReader(QExtDAIODevice *ioDevice);

protected:
    QScopedPointer<QExtDAIOReaderPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDAIOReader)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDAIOReader)
};

#endif // _QEXTDAIOREADER_H
