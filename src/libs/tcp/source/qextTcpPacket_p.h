#ifndef _QEXTTCPPACKET_P_H
#define _QEXTTCPPACKET_P_H

#include <qextId.h>
#include <qextTcpPacket.h>

#include <QScopedPointer>
#include <QDateTime>

class QExtTcpPacketHeaderInterface;
class QExtTcpPacket;
class QEXT_TCP_API QExtTcpPacketPrivate
{
public:
    explicit QExtTcpPacketPrivate(QExtTcpPacket *q);
    virtual ~QExtTcpPacketPrivate();

    QExtTcpPacket * const q_ptr;

    QSharedPointer<QExtTcpPacketHeaderInterface> m_header;
    QByteArray m_content;
    quint64 m_nextBlockSize;
    QDateTime m_timestamp;
    bool m_valid;

private:
    Q_DECLARE_PUBLIC(QExtTcpPacket)
    Q_DISABLE_COPY(QExtTcpPacketPrivate)
};



#endif // _QEXTTCPPACKET_P_H
