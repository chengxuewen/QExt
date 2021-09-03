#ifndef QEXTTCPPACKETPARSERINTERFACE_H
#define QEXTTCPPACKETPARSERINTERFACE_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>
#include <qextTcpPacketInterface.h>
#include <qextTcpGlobal.h>
#include <qextTcpSocket.h>

#include <QSharedPointer>

class QEXT_TCP_API QEXTTcpPacketParserInterface
{
public:
    QEXTTcpPacketParserInterface() {}
    virtual ~QEXTTcpPacketParserInterface() {}

    virtual QString name() const = 0;
    virtual QString errorString() const = 0;

    virtual bool comparePacket(QEXTTcpPacketInterface *lpacket, QEXTTcpPacketInterface *rpacket) const = 0;
    virtual bool checkIsSyncReplyPacket(QEXTTcpPacketInterface *send, QEXTTcpPacketInterface *rcv) const = 0;
    virtual quint64 packetId(QEXTTcpPacketInterface *packet) const = 0;

    virtual bool isRequestPacket(QEXTTcpPacketInterface *packet) const = 0;
    virtual bool setRequestPacket(QEXTTcpPacketInterface *packet) = 0;

    virtual bool isReplyPacket(QEXTTcpPacketInterface *packet) const = 0;
    virtual bool setReplyPacket(QEXTTcpPacketInterface *send, QEXTTcpPacketInterface *rcv) = 0;

    virtual bool isNotifyPacket(QEXTTcpPacketInterface *packet) const = 0;
    virtual bool setNotifyPacket(QEXTTcpPacketInterface *packet) = 0;

    virtual QSharedPointer<QEXTTcpPacketHeaderInterface> createHeader() const = 0;
    virtual QSharedPointer<QEXTTcpPacketInterface> createPacket() const = 0;
    virtual QSharedPointer<QEXTTcpPacketInterface> clonePacket(QEXTTcpPacketInterface *packet) const = 0;
    virtual QSharedPointer<QEXTTcpPacketInterface> createReplyPacket(QEXTTcpPacketInterface *rcv) const = 0;
    virtual QSharedPointer<QEXTTcpPacketParserInterface> clonePacketParser() const = 0;

    virtual QSharedPointer<QEXTTcpPacketInterface> readData(QEXTTcpSocket *socket, bool &success) = 0;
    virtual qint64 writeData(QEXTTcpSocket *socket, const QSharedPointer<QEXTTcpPacketInterface> &packet) = 0;
};


#endif // QEXTTCPPACKETPARSERINTERFACE_H
