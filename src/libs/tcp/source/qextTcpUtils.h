#ifndef _QEXTTCPUTILS_H
#define _QEXTTCPUTILS_H

#include <qextTcpGlobal.h>

#include <QSharedPointer>

class QExtTcpPacketInterface;
class QEXT_TCP_API QExtTcpUtils
{
public:
    QExtTcpUtils();

    static QString packetData(const QSharedPointer<QExtTcpPacketInterface> &packet);
    static QString packetData(QExtTcpPacketInterface *packet);
    static void printPacket(const QSharedPointer<QExtTcpPacketInterface> &packet);
    static void printPacket(QExtTcpPacketInterface *packet);
};

#endif // _QEXTTCPUTILS_H
