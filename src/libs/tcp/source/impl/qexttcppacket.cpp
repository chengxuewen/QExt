#include <qexttcppacket.h>
#include <qexttcppacket_p.h>

#include <QDebug>



QEXTTcpPacketPrivate::QEXTTcpPacketPrivate(QEXTTcpPacket *qq)
    : QEXTObjectPrivate(qq)
{
    m_nextBlockSize = 0;
    m_valid = true;
    m_timestamp = QDateTime::currentDateTime();
}

QEXTTcpPacketPrivate::~QEXTTcpPacketPrivate()
{

}



QEXTTcpPacket::QEXTTcpPacket(QEXTTcpAbstractPacketHeader *header, const QEXTId &id)
    : QEXTObject(*(new QEXTTcpPacketPrivate(this)))
{
    QEXT_D(QEXTTcpPacket);
    d->m_socketId = id;
    d->m_header.reset(header);
}

QEXTTcpPacket::QEXTTcpPacket(QEXTTcpAbstractPacketHeader *header, QEXTTcpPacketPrivate &dd, const QEXTId &id)
    : QEXTObject(dd)
{
    QEXT_D(QEXTTcpPacket);
    d->m_socketId = id;
    d->m_header.reset(header);
}

QEXTTcpPacket::~QEXTTcpPacket()
{

}

QEXTId QEXTTcpPacket::socketId() const
{
    QEXT_DC(QEXTTcpPacket);
    return d->m_socketId;
}

QDateTime QEXTTcpPacket::timestamp() const
{
    QEXT_DC(QEXTTcpPacket);
    return d->m_timestamp;
}

bool QEXTTcpPacket::isValid() const
{
    QEXT_DC(QEXTTcpPacket);
    return d->m_valid;
}

QByteArray QEXTTcpPacket::stream() const
{
    QEXT_DC(QEXTTcpPacket);
    return d->m_header->stream() + d->m_content;
}

QEXTTcpAbstractPacketHeader *QEXTTcpPacket::header() const
{
    QEXT_DC(QEXTTcpPacket);
    return d->m_header.data();
}

bool QEXTTcpPacket::setHeader(QEXTTcpAbstractPacketHeader *header)
{
    QEXT_D(QEXTTcpPacket);
    d->m_header.reset(header);
    return true;
}

QByteArray QEXTTcpPacket::content() const
{
    QEXT_DC(QEXTTcpPacket);
    return d->m_content;
}

bool QEXTTcpPacket::setContent(const QByteArray &content)
{
    QEXT_D(QEXTTcpPacket);
    d->m_content = content;
    d->m_header->setContentSize(content.size());
    d->m_valid = true;
    return true;
}

qint64 QEXTTcpPacket::nextBlockSize() const
{
    QEXT_DC(QEXTTcpPacket);
    return d->m_nextBlockSize;
}

bool QEXTTcpPacket::setNextBlockSize(qint64 size)
{
    QEXT_D(QEXTTcpPacket);
    d->m_nextBlockSize = size;
    return true;
}
