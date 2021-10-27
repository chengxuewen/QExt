#ifndef _QEXTTCPPACKET_P_H
#define _QEXTTCPPACKET_P_H

#include <qextId.h>
#include <qextTcpGlobal.h>

#include <QScopedPointer>
#include <QDateTime>

class QEXTTcpPacketHeaderInterface;
class QEXTTcpPacket;
class QEXT_TCP_API QEXTTcpPacketPrivate
{
public:
    explicit QEXTTcpPacketPrivate(QEXTTcpPacket *q);
    virtual ~QEXTTcpPacketPrivate();

    QEXTTcpPacket * const q_ptr;

    QSharedPointer<QEXTTcpPacketHeaderInterface> m_header;
    QByteArray m_content;
    quint64 m_nextBlockSize;
    QDateTime m_timestamp;
    bool m_valid;

private:
    QEXT_DECL_PUBLIC(QEXTTcpPacket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketPrivate)
};



#endif // _QEXTTCPPACKET_P_H
