#ifndef QEXTTCPPACKETPARSER_H
#define QEXTTCPPACKETPARSER_H

#include <qextobject.h>

#include <qexttcpglobal.h>
#include <qexttcppacket.h>
#include <qexttcpabstractpacket.h>
#include <qexttcppacketheader.h>

#include <QString>



class QEXTTcpPacketParserPrivate;
class QEXT_TCP_API QEXTTcpPacketParser : public QEXTTcpAbstractPacketParser, public QEXTObject
{
public:
    QEXTTcpPacketParser(const QEXTTcpPacketHeader::DataInfoVector &extraHeaderDataInfo = QEXTTcpPacketHeader::DataInfoVector());
    QEXTTcpPacketParser(QEXTTcpPacketParserPrivate &dd);
    ~QEXTTcpPacketParser();

    QString name() const QEXT_DECL_OVERRIDE;
    QString errorString() const QEXT_DECL_OVERRIDE;

    bool checkIsSyncReplyPacket(QEXTTcpAbstractPacket *send, QEXTTcpAbstractPacket *rcv) const QEXT_DECL_OVERRIDE;

    bool isRequestPacket(QEXTTcpAbstractPacket *packet) const QEXT_DECL_OVERRIDE;
    bool setRequestPacket(QEXTTcpAbstractPacket *packet) QEXT_DECL_OVERRIDE;

    bool isReplyPacket(QEXTTcpAbstractPacket *packet) const QEXT_DECL_OVERRIDE;
    bool setReplyPacket(QEXTTcpAbstractPacket *packet) QEXT_DECL_OVERRIDE;

    bool isNotifyPacket(QEXTTcpAbstractPacket *packet) const QEXT_DECL_OVERRIDE;
    bool setNotifyPacket(QEXTTcpAbstractPacket *packet) QEXT_DECL_OVERRIDE;

    QEXTTcpAbstractPacketHeader *createHeader() const QEXT_DECL_OVERRIDE;
    QEXTTcpAbstractPacket *createPacket(const QEXTId &socketId) const QEXT_DECL_OVERRIDE;
    QEXTTcpAbstractPacket *createReplyPacket(QEXTTcpAbstractPacket *rcv) const QEXT_DECL_OVERRIDE;
    QEXTTcpAbstractPacketParser *cloneParser() const QEXT_DECL_OVERRIDE;

    QEXTTcpAbstractPacket *readData(QEXTTcpSocket *socket, bool &success) QEXT_DECL_OVERRIDE;
    qint64 writeData(QEXTTcpSocket *socket, QEXTTcpAbstractPacket *packet) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketParser)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketParser)
};



#endif // QEXTTCPPACKETPARSER_H
