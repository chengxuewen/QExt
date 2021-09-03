#ifndef QEXTTCPUTILS_H
#define QEXTTCPUTILS_H

#include <qextTcpGlobal.h>

#include <QSharedPointer>

class QEXTTcpPacketInterface;
class QEXT_TCP_API QEXTTcpUtils
{
public:
    QEXTTcpUtils();

    static QString packetData(const QSharedPointer<QEXTTcpPacketInterface> &packet);
    static QString packetData(QEXTTcpPacketInterface *packet);
    static void printPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet);
    static void printPacket(QEXTTcpPacketInterface *packet);
};

#endif // QEXTTCPUTILS_H
