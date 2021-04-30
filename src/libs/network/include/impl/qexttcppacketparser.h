#ifndef QEXTTCPPACKETPARSER_H
#define QEXTTCPPACKETPARSER_H

#include <qextobject.h>

#include <qextnetworkglobal.h>
#include <qexttcppacket.h>
#include <qexttcppacketbase.h>
#include <qexttcppacketheader.h>

#include <QString>

class QEXTTcpPacketParserPrivate;
class QEXT_NETWORK_API QEXTTcpPacketParser : public QEXTTcpPacketParserBase, public QEXTObject
{
public:
    QEXTTcpPacketParser(const QEXTTcpPacketHeader::DataInfoVector &extraHeaderDataInfo = QEXTTcpPacketHeader::DataInfoVector());
    QEXTTcpPacketParser(QEXTTcpPacketParserPrivate &dd);
    ~QEXTTcpPacketParser();

    QString name() const QEXT_OVERRIDE;
    QString errorString() const QEXT_OVERRIDE;

    bool checkIsSyncReplyPacket(QEXTTcpPacketBase *send, QEXTTcpPacketBase *rcv) const QEXT_OVERRIDE;

    bool isRequestPacket(QEXTTcpPacketBase *packet) const QEXT_OVERRIDE;
    bool setRequestPacket(QEXTTcpPacketBase *packet) QEXT_OVERRIDE;

    bool isReplyPacket(QEXTTcpPacketBase *packet) const QEXT_OVERRIDE;
    bool setReplyPacket(QEXTTcpPacketBase *packet) QEXT_OVERRIDE;

    bool isNotifyPacket(QEXTTcpPacketBase *packet) const QEXT_OVERRIDE;
    bool setNotifyPacket(QEXTTcpPacketBase *packet) QEXT_OVERRIDE;

    QEXTTcpPacketHeaderBase *createHeader() const QEXT_OVERRIDE;
    QEXTTcpPacketBase *createPacket(const QEXTId &socketId) const QEXT_OVERRIDE;
    QEXTTcpPacketBase *createReplyPacket(QEXTTcpPacketBase *rcv) const QEXT_OVERRIDE;
    QEXTTcpPacketParserBase *cloneParser() const QEXT_OVERRIDE;

    QEXTTcpPacketBase *readData(QEXTTcpSocket *socket, bool &success) QEXT_OVERRIDE;
    qint64 writeData(QEXTTcpSocket *socket, QEXTTcpPacketBase *packet) QEXT_OVERRIDE;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpPacketParser)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketParser)
};

#endif // QEXTTCPPACKETPARSER_H
