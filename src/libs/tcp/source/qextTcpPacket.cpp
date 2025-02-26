#include <private/qextTcpPacket_p.h>

#include <QDebug>



QExtTcpPacketPrivate::QExtTcpPacketPrivate(QExtTcpPacket *q)
    : q_ptr(q)
{
    m_nextBlockSize = 0;
    m_valid = true;
    m_timestamp = QDateTime::currentDateTime();
}

QExtTcpPacketPrivate::~QExtTcpPacketPrivate()
{

}



QExtTcpPacket::QExtTcpPacket(const QSharedPointer<QExtTcpPacketHeaderInterface> &header)
    : dd_ptr(new QExtTcpPacketPrivate(this))
{
    Q_D(QExtTcpPacket);
    d->m_header = header;
}

QExtTcpPacket::QExtTcpPacket(QExtTcpPacketPrivate *d,
                             const QSharedPointer<QExtTcpPacketHeaderInterface> &header)
    : dd_ptr(d)
{
    dd_ptr->m_header = header;
}

QExtTcpPacket::~QExtTcpPacket()
{

}

QDateTime QExtTcpPacket::timestamp() const
{
    Q_D(const QExtTcpPacket);
    return d->m_timestamp;
}

bool QExtTcpPacket::isValid() const
{
    Q_D(const QExtTcpPacket);
    return d->m_valid;
}

QByteArray QExtTcpPacket::stream() const
{
    Q_D(const QExtTcpPacket);
    return d->m_header->stream() + d->m_content;
}

QSharedPointer<QExtTcpPacketHeaderInterface> QExtTcpPacket::header() const
{
    Q_D(const QExtTcpPacket);
    return d->m_header;
}

bool QExtTcpPacket::setHeader(const QSharedPointer<QExtTcpPacketHeaderInterface> &header)
{
    Q_D(QExtTcpPacket);
    d->m_header = header;
    return true;
}

QByteArray QExtTcpPacket::content() const
{
    Q_D(const QExtTcpPacket);
    return d->m_content;
}

bool QExtTcpPacket::setContent(const QByteArray &content)
{
    Q_D(QExtTcpPacket);
    d->m_content = content;
    d->m_header->setContentSize(content.size());
    d->m_valid = true;
    return true;
}

qint64 QExtTcpPacket::nextBlockSize() const
{
    Q_D(const QExtTcpPacket);
    return d->m_nextBlockSize;
}

bool QExtTcpPacket::setNextBlockSize(qint64 size)
{
    Q_D(QExtTcpPacket);
    d->m_nextBlockSize = size;
    return true;
}
