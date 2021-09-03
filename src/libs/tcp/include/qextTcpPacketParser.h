#ifndef QEXTTCPPACKETPARSER_H
#define QEXTTCPPACKETPARSER_H

#include <qextobject.h>

#include <qextTcpGlobal.h>
#include <qextTcpPacket.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketHeader.h>

#include <QString>

class QEXTTcpPacketParserPrivate;
class QEXT_TCP_API QEXTTcpPacketParser : public QEXTTcpPacketParserInterface, public QEXTObject
{
public:
    QEXTTcpPacketParser(const QEXTTcpPacketHeader::DataInfoVector &extraHeaderDataInfo = QEXTTcpPacketHeader::DataInfoVector());
    QEXTTcpPacketParser(QEXTTcpPacketParserPrivate &dd);
    ~QEXTTcpPacketParser();

    QString name() const QEXT_DECL_OVERRIDE;
    QString errorString() const QEXT_DECL_OVERRIDE;

    bool comparePacket(QEXTTcpPacketInterface *lpacket, QEXTTcpPacketInterface *rpacket) const QEXT_DECL_OVERRIDE;
    bool checkIsSyncReplyPacket(QEXTTcpPacketInterface *send, QEXTTcpPacketInterface *rcv) const QEXT_DECL_OVERRIDE;
    quint64 packetId(QEXTTcpPacketInterface *packet) const QEXT_DECL_OVERRIDE;

    bool isRequestPacket(QEXTTcpPacketInterface *packet) const QEXT_DECL_OVERRIDE;
    bool setRequestPacket(QEXTTcpPacketInterface *packet) QEXT_DECL_OVERRIDE;

    bool isReplyPacket(QEXTTcpPacketInterface *packet) const QEXT_DECL_OVERRIDE;
    bool setReplyPacket(QEXTTcpPacketInterface *send, QEXTTcpPacketInterface *rcv) QEXT_DECL_OVERRIDE;

    bool isNotifyPacket(QEXTTcpPacketInterface *packet) const QEXT_DECL_OVERRIDE;
    bool setNotifyPacket(QEXTTcpPacketInterface *packet) QEXT_DECL_OVERRIDE;

    QSharedPointer<QEXTTcpPacketHeaderInterface> createHeader() const QEXT_DECL_OVERRIDE;
    QSharedPointer<QEXTTcpPacketInterface> createPacket() const QEXT_DECL_OVERRIDE;
    QSharedPointer<QEXTTcpPacketInterface> clonePacket(QEXTTcpPacketInterface *packet) const QEXT_DECL_OVERRIDE;
    QSharedPointer<QEXTTcpPacketInterface> createReplyPacket(QEXTTcpPacketInterface *rcv) const QEXT_DECL_OVERRIDE;
    QSharedPointer<QEXTTcpPacketParserInterface> clonePacketParser() const QEXT_DECL_OVERRIDE;

    QSharedPointer<QEXTTcpPacketInterface> readData(QEXTTcpSocket *socket, bool &success) QEXT_DECL_OVERRIDE;
    qint64 writeData(QEXTTcpSocket *socket, const QSharedPointer<QEXTTcpPacketInterface> &packet) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketParser)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketParser)
};



#endif // QEXTTCPPACKETPARSER_H
