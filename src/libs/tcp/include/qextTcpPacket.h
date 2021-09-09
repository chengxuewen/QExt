#ifndef QEXTTCPPACKET_H
#define QEXTTCPPACKET_H

#include <qextObject.h>

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>
#include <qextTcpPacketInterface.h>

#include <QString>
#include <QTcpSocket>

class QEXTTcpPacketPrivate;
class QEXT_TCP_API QEXTTcpPacket : public QEXTTcpPacketInterface, public QEXTObject
{
public:
    QEXTTcpPacket(const QSharedPointer<QEXTTcpPacketHeaderInterface> &header);
    QEXTTcpPacket(QEXTTcpPacketPrivate &dd, const QSharedPointer<QEXTTcpPacketHeaderInterface> &header);
    ~QEXTTcpPacket();

    QDateTime timestamp() const QEXT_DECL_OVERRIDE;
    bool isValid() const QEXT_DECL_OVERRIDE;

    QByteArray stream() const QEXT_DECL_OVERRIDE;

    QSharedPointer<QEXTTcpPacketHeaderInterface> header() const QEXT_DECL_OVERRIDE;
    bool setHeader(const QSharedPointer<QEXTTcpPacketHeaderInterface> &header) QEXT_DECL_OVERRIDE;

    QByteArray content() const QEXT_DECL_OVERRIDE;
    bool setContent(const QByteArray &content) QEXT_DECL_OVERRIDE;

    qint64 nextBlockSize() const QEXT_DECL_OVERRIDE;
    bool setNextBlockSize(qint64 size) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacket)
};



#endif // QEXTTCPPACKET_H
