#ifndef _QEXTTCPPACKETPARSER_H
#define _QEXTTCPPACKETPARSER_H

#include <qextTcpGlobal.h>
#include <qextTcpPacket.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketHeader.h>

#include <QString>

class QEXTTcpPacketParserPrivate;
class QEXT_TCP_API QEXTTcpPacketParser : public QEXTTcpPacketParserInterface
{
    Q_DISABLE_COPY(QEXTTcpPacketParser)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTTcpPacketParser)
public:
    QEXTTcpPacketParser(const QEXTTcpPacketHeader::DataInfoVector &extraHeaderDataInfo = QEXTTcpPacketHeader::DataInfoVector());
    QEXTTcpPacketParser(QEXTTcpPacketParserPrivate *d);
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

protected:
    QScopedPointer<QEXTTcpPacketParserPrivate> dd_ptr;
};



#endif // _QEXTTCPPACKETPARSER_H
