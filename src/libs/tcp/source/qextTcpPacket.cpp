#include <qextTcpPacket.h>
#include <qextTcpPacket_p.h>

#include <QDebug>



QEXTTcpPacketPrivate::QEXTTcpPacketPrivate(QEXTTcpPacket *q)
    : q_ptr(q)
{
    m_nextBlockSize = 0;
    m_valid = true;
    m_timestamp = QDateTime::currentDateTime();
}

QEXTTcpPacketPrivate::~QEXTTcpPacketPrivate()
{

}



QEXTTcpPacket::QEXTTcpPacket(const QSharedPointer<QEXTTcpPacketHeaderInterface> &header)
    : d_ptr(new QEXTTcpPacketPrivate(this))
{
    Q_D(QEXTTcpPacket);
    d->m_header = header;
}

QEXTTcpPacket::QEXTTcpPacket(QEXTTcpPacketPrivate *d,
                             const QSharedPointer<QEXTTcpPacketHeaderInterface> &header)
    : d_ptr(d)
{
    d_ptr->m_header = header;
}

QEXTTcpPacket::~QEXTTcpPacket()
{

}

QDateTime QEXTTcpPacket::timestamp() const
{
    Q_D(const QEXTTcpPacket);
    return d->m_timestamp;
}

bool QEXTTcpPacket::isValid() const
{
    Q_D(const QEXTTcpPacket);
    return d->m_valid;
}

QByteArray QEXTTcpPacket::stream() const
{
    Q_D(const QEXTTcpPacket);
    return d->m_header->stream() + d->m_content;
}

QSharedPointer<QEXTTcpPacketHeaderInterface> QEXTTcpPacket::header() const
{
    Q_D(const QEXTTcpPacket);
    return d->m_header;
}

bool QEXTTcpPacket::setHeader(const QSharedPointer<QEXTTcpPacketHeaderInterface> &header)
{
    Q_D(QEXTTcpPacket);
    d->m_header = header;
    return true;
}

QByteArray QEXTTcpPacket::content() const
{
    Q_D(const QEXTTcpPacket);
    return d->m_content;
}

bool QEXTTcpPacket::setContent(const QByteArray &content)
{
    Q_D(QEXTTcpPacket);
    d->m_content = content;
    d->m_header->setContentSize(content.size());
    d->m_valid = true;
    return true;
}

qint64 QEXTTcpPacket::nextBlockSize() const
{
    Q_D(const QEXTTcpPacket);
    return d->m_nextBlockSize;
}

bool QEXTTcpPacket::setNextBlockSize(qint64 size)
{
    Q_D(QEXTTcpPacket);
    d->m_nextBlockSize = size;
    return true;
}
