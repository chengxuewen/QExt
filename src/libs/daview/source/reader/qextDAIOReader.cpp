#include <private/qextDAIOReader_p.h>

QExtDAIOReaderPrivate::QExtDAIOReaderPrivate(QExtDAIOReader *q)
    : q_ptr(q)
{
}

QExtDAIOReaderPrivate::~QExtDAIOReaderPrivate()
{
}

QExtDAIOReader::QExtDAIOReader(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtDAIOReaderPrivate(this))
{
}

QExtDAIOReader::QExtDAIOReader(QExtDAIOReaderPrivate *d, QObject *parent)
    : QObject(parent)
    , dd_ptr(d)
{
}

QExtDAIOReader::~QExtDAIOReader()
{
}

bool QExtDAIOReader::initReader(QExtDAIODevice *ioDevice)
{
    return true;
}
