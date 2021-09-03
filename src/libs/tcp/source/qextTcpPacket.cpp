#include <qextTcpPacket.h>
#include <qextTcpPacket_p.h>

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



QEXTTcpPacket::QEXTTcpPacket(const QSharedPointer<QEXTTcpPacketHeaderInterface> &header)
    : QEXTObject(*(new QEXTTcpPacketPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpPacket);
    d->m_header = header;
}

QEXTTcpPacket::QEXTTcpPacket(QEXTTcpPacketPrivate &dd, const QSharedPointer<QEXTTcpPacketHeaderInterface> &header)
    : QEXTObject(dd)
{
    QEXT_DECL_D(QEXTTcpPacket);
    d->m_header = header;
}

QEXTTcpPacket::~QEXTTcpPacket()
{

}

QDateTime QEXTTcpPacket::timestamp() const
{
    QEXT_DECL_DC(QEXTTcpPacket);
    return d->m_timestamp;
}

bool QEXTTcpPacket::isValid() const
{
    QEXT_DECL_DC(QEXTTcpPacket);
    return d->m_valid;
}

QByteArray QEXTTcpPacket::stream() const
{
    QEXT_DECL_DC(QEXTTcpPacket);
    return d->m_header->stream() + d->m_content;
}

QSharedPointer<QEXTTcpPacketHeaderInterface> QEXTTcpPacket::header() const
{
    QEXT_DECL_DC(QEXTTcpPacket);
    return d->m_header;
}

bool QEXTTcpPacket::setHeader(const QSharedPointer<QEXTTcpPacketHeaderInterface> &header)
{
    QEXT_DECL_D(QEXTTcpPacket);
    d->m_header = header;
    return true;
}

QByteArray QEXTTcpPacket::content() const
{
    QEXT_DECL_DC(QEXTTcpPacket);
    return d->m_content;
}

bool QEXTTcpPacket::setContent(const QByteArray &content)
{
    QEXT_DECL_D(QEXTTcpPacket);
    d->m_content = content;
    d->m_header->setContentSize(content.size());
    d->m_valid = true;
    return true;
}

qint64 QEXTTcpPacket::nextBlockSize() const
{
    QEXT_DECL_DC(QEXTTcpPacket);
    return d->m_nextBlockSize;
}

bool QEXTTcpPacket::setNextBlockSize(qint64 size)
{
    QEXT_DECL_D(QEXTTcpPacket);
    d->m_nextBlockSize = size;
    return true;
}
