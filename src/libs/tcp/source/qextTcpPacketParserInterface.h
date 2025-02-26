#ifndef _QEXTTCPPACKETPARSERINTERFACE_H
#define _QEXTTCPPACKETPARSERINTERFACE_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>
#include <qextTcpPacketInterface.h>
#include <qextTcpGlobal.h>
#include <qextTcpSocket.h>

#include <QSharedPointer>

class QEXT_TCP_API QExtTcpPacketParserInterface
{
public:
    QExtTcpPacketParserInterface() {}
    virtual ~QExtTcpPacketParserInterface() {}

    virtual QString name() const = 0;
    virtual QString errorString() const = 0;

    virtual bool comparePacket(const QSharedPointer<QExtTcpPacketInterface> &lpacket, const QSharedPointer<QExtTcpPacketInterface> &rpacket) const = 0;
    virtual bool checkIsSyncReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &send, const QSharedPointer<QExtTcpPacketInterface> &rcv) const = 0;
    virtual quint64 packetId(const QSharedPointer<QExtTcpPacketInterface> &packet) const = 0;

    virtual bool isRequestPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const = 0;
    virtual bool setRequestPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) = 0;

    virtual bool isReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const = 0;
    virtual bool setReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &send, const QSharedPointer<QExtTcpPacketInterface> &rcv) = 0;

    virtual bool isNotifyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const = 0;
    virtual bool setNotifyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) = 0;

    virtual QSharedPointer<QExtTcpPacketHeaderInterface> createHeader() const = 0;
    virtual QSharedPointer<QExtTcpPacketInterface> createPacket() const = 0;
    virtual QSharedPointer<QExtTcpPacketInterface> clonePacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const = 0;
    virtual QSharedPointer<QExtTcpPacketInterface> createReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &rcv) const = 0;
    virtual QSharedPointer<QExtTcpPacketParserInterface> clonePacketParser() const = 0;

    virtual QSharedPointer<QExtTcpPacketInterface> readData(QExtTcpSocket *socket, bool &success) = 0;
    virtual qint64 writeData(QExtTcpSocket *socket, const QSharedPointer<QExtTcpPacketInterface> &packet) = 0;
};


#endif // _QEXTTCPPACKETPARSERINTERFACE_H
