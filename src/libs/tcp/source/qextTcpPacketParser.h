#ifndef _QEXTTCPPACKETPARSER_H
#define _QEXTTCPPACKETPARSER_H

#include <qextTcpGlobal.h>
#include <qextTcpPacket.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketHeader.h>

#include <QString>

class QExtTcpPacketParserPrivate;
class QEXT_TCP_API QExtTcpPacketParser : public QExtTcpPacketParserInterface
{
    Q_DISABLE_COPY(QExtTcpPacketParser)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpPacketParser)
public:
    QExtTcpPacketParser(const QExtTcpPacketHeader::DataInfoVector &extraHeaderDataInfo = QExtTcpPacketHeader::DataInfoVector());
    QExtTcpPacketParser(QExtTcpPacketParserPrivate *d);
    ~QExtTcpPacketParser();

    QString name() const QEXT_DECL_OVERRIDE;
    QString errorString() const QEXT_DECL_OVERRIDE;

    bool comparePacket(const QSharedPointer<QExtTcpPacketInterface> &lpacket, const QSharedPointer<QExtTcpPacketInterface> &rpacket) const QEXT_DECL_OVERRIDE;
    bool checkIsSyncReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &send, const QSharedPointer<QExtTcpPacketInterface> &rcv) const QEXT_DECL_OVERRIDE;
    quint64 packetId(const QSharedPointer<QExtTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;

    bool isRequestPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;
    bool setRequestPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) QEXT_DECL_OVERRIDE;

    bool isReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;
    bool setReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &send, const QSharedPointer<QExtTcpPacketInterface> &rcv) QEXT_DECL_OVERRIDE;

    bool isNotifyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;
    bool setNotifyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) QEXT_DECL_OVERRIDE;

    QSharedPointer<QExtTcpPacketHeaderInterface> createHeader() const QEXT_DECL_OVERRIDE;
    QSharedPointer<QExtTcpPacketInterface> createPacket() const QEXT_DECL_OVERRIDE;
    QSharedPointer<QExtTcpPacketInterface> clonePacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const QEXT_DECL_OVERRIDE;
    QSharedPointer<QExtTcpPacketInterface> createReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &rcv) const QEXT_DECL_OVERRIDE;
    QSharedPointer<QExtTcpPacketParserInterface> clonePacketParser() const QEXT_DECL_OVERRIDE;

    QSharedPointer<QExtTcpPacketInterface> readData(QExtTcpSocket *socket, bool &success) QEXT_DECL_OVERRIDE;
    qint64 writeData(QExtTcpSocket *socket, const QSharedPointer<QExtTcpPacketInterface> &packet) QEXT_DECL_OVERRIDE;

protected:
    QScopedPointer<QExtTcpPacketParserPrivate> dd_ptr;
};



#endif // _QEXTTCPPACKETPARSER_H
