#ifndef QEXTTCPPACKET_H
#define QEXTTCPPACKET_H

#include <qextobject.h>

#include <qexttcpglobal.h>
#include <qexttcpabstractpacket.h>

#include <QString>
#include <QTcpSocket>



class QEXTTcpPacketPrivate;
class QEXT_TCP_API QEXTTcpPacket : public QEXTTcpAbstractPacket, public QEXTObject
{
public:
    QEXTTcpPacket(QEXTTcpAbstractPacketHeader *header, const QEXTId &id);
    QEXTTcpPacket(QEXTTcpAbstractPacketHeader *header, QEXTTcpPacketPrivate &dd, const QEXTId &id);
    ~QEXTTcpPacket();

    QEXTId socketId() const QEXT_DECL_OVERRIDE;
    QDateTime timestamp() const QEXT_DECL_OVERRIDE;
    bool isValid() const QEXT_DECL_OVERRIDE;

    QByteArray stream() const QEXT_DECL_OVERRIDE;

    QEXTTcpAbstractPacketHeader *header() const QEXT_DECL_OVERRIDE;
    bool setHeader(QEXTTcpAbstractPacketHeader *header) QEXT_DECL_OVERRIDE;

    QByteArray content() const QEXT_DECL_OVERRIDE;
    bool setContent(const QByteArray &content) QEXT_DECL_OVERRIDE;

    qint64 nextBlockSize() const QEXT_DECL_OVERRIDE;
    bool setNextBlockSize(qint64 size) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacket)
};



#endif // QEXTTCPPACKET_H
