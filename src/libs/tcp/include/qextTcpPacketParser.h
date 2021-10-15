#ifndef QEXTTCPPACKETPARSER_H
#define QEXTTCPPACKETPARSER_H

#include <qextObject.h>

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

    bool comparePacket(const QSharedPointer<QEXTTcpPacketInterface> &lpacket, const QSharedPointer<QEXTTcpPacketInterface> &rpacket) const QEXT_DECL_OVERRIDE;
    bool checkIsSyncReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &send, const QSharedPointer<QEXTTcpPacketInterface> &rcv) const QEXT_DECL_OVERRIDE;
    quint64 packetId(const QSharedPointer<QEXTTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;

    bool isRequestPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;
    bool setRequestPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) QEXT_DECL_OVERRIDE;

    bool isReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;
    bool setReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &send, const QSharedPointer<QEXTTcpPacketInterface> &rcv) QEXT_DECL_OVERRIDE;

    bool isNotifyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;
    bool setNotifyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) QEXT_DECL_OVERRIDE;

    QSharedPointer<QEXTTcpPacketHeaderInterface> createHeader() const QEXT_DECL_OVERRIDE;
    QSharedPointer<QEXTTcpPacketInterface> createPacket() const QEXT_DECL_OVERRIDE;
    QSharedPointer<QEXTTcpPacketInterface> clonePacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;
    QSharedPointer<QEXTTcpPacketInterface> createReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &rcv) const QEXT_DECL_OVERRIDE;
    QSharedPointer<QEXTTcpPacketParserInterface> clonePacketParser() const QEXT_DECL_OVERRIDE;

    QSharedPointer<QEXTTcpPacketInterface> readData(QEXTTcpSocket *socket, bool &success) QEXT_DECL_OVERRIDE;
    qint64 writeData(QEXTTcpSocket *socket, const QSharedPointer<QEXTTcpPacketInterface> &packet) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketParser)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketParser)
};



#endif // QEXTTCPPACKETPARSER_H
