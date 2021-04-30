#ifndef QEXTTCPPACKET_P_H
#define QEXTTCPPACKET_P_H

#include <qextobject_p.h>
#include <qextid.h>

#include <qextnetworkglobal.h>
#include <qexttcppacketbase.h>

#include <QDateTime>

class QEXTTcpPacket;
class QEXT_NETWORK_API QEXTTcpPacketPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpPacketPrivate(QEXTTcpPacket *qq);
    ~QEXTTcpPacketPrivate();

    QScopedPointer<QEXTTcpPacketHeaderBase> m_header;
    QByteArray m_content;
    quint64 m_nextBlockSize;
    bool m_valid;

    QEXTId m_socketId;
    QDateTime m_timestamp;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpPacket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketPrivate)
};

#endif // QEXTTCPPACKET_P_H
