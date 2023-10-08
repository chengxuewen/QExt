#ifndef _QEXTTCPPACKETPARSERINTERFACE_H
#define _QEXTTCPPACKETPARSERINTERFACE_H

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

    virtual bool comparePacket(const QSharedPointer<QEXTTcpPacketInterface> &lpacket, const QSharedPointer<QEXTTcpPacketInterface> &rpacket) const = 0;
    virtual bool checkIsSyncReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &send, const QSharedPointer<QEXTTcpPacketInterface> &rcv) const = 0;
    virtual quint64 packetId(const QSharedPointer<QEXTTcpPacketInterface> &packet) const = 0;

    virtual bool isRequestPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const = 0;
    virtual bool setRequestPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) = 0;

    virtual bool isReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const = 0;
    virtual bool setReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &send, const QSharedPointer<QEXTTcpPacketInterface> &rcv) = 0;

    virtual bool isNotifyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const = 0;
    virtual bool setNotifyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) = 0;

    virtual QSharedPointer<QEXTTcpPacketHeaderInterface> createHeader() const = 0;
    virtual QSharedPointer<QEXTTcpPacketInterface> createPacket() const = 0;
    virtual QSharedPointer<QEXTTcpPacketInterface> clonePacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const = 0;
    virtual QSharedPointer<QEXTTcpPacketInterface> createReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &rcv) const = 0;
    virtual QSharedPointer<QEXTTcpPacketParserInterface> clonePacketParser() const = 0;

    virtual QSharedPointer<QEXTTcpPacketInterface> readData(QEXTTcpSocket *socket, bool &success) = 0;
    virtual qint64 writeData(QEXTTcpSocket *socket, const QSharedPointer<QEXTTcpPacketInterface> &packet) = 0;
};


#endif // _QEXTTCPPACKETPARSERINTERFACE_H
