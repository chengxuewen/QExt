#ifndef _QEXTTCPPACKET_H
#define _QEXTTCPPACKET_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>
#include <qextTcpPacketInterface.h>

#include <QString>
#include <QTcpSocket>

class QExtTcpPacketPrivate;
class QEXT_TCP_API QExtTcpPacket : public QExtTcpPacketInterface
{
    Q_DISABLE_COPY(QExtTcpPacket)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpPacket)
public:
    QExtTcpPacket(const QSharedPointer<QExtTcpPacketHeaderInterface> &header);
    QExtTcpPacket(QExtTcpPacketPrivate *d, const QSharedPointer<QExtTcpPacketHeaderInterface> &header);
    ~QExtTcpPacket();

    QDateTime timestamp() const QEXT_DECL_OVERRIDE;
    bool isValid() const QEXT_DECL_OVERRIDE;

    QByteArray stream() const QEXT_DECL_OVERRIDE;

    QSharedPointer<QExtTcpPacketHeaderInterface> header() const QEXT_DECL_OVERRIDE;
    bool setHeader(const QSharedPointer<QExtTcpPacketHeaderInterface> &header) QEXT_DECL_OVERRIDE;

    QByteArray content() const QEXT_DECL_OVERRIDE;
    bool setContent(const QByteArray &content) QEXT_DECL_OVERRIDE;

    qint64 nextBlockSize() const QEXT_DECL_OVERRIDE;
    bool setNextBlockSize(qint64 size) QEXT_DECL_OVERRIDE;

protected:
    QScopedPointer<QExtTcpPacketPrivate> dd_ptr;
};

#endif // _QEXTTCPPACKET_H
