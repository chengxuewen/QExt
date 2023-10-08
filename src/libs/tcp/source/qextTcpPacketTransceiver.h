#ifndef _QEXTTCPPACKETTRANSCEIVER_H
#define _QEXTTCPPACKETTRANSCEIVER_H

#include <qextTcpGlobal.h>
#include <qextId.h>

#include <QObject>
#include <QSharedPointer>

class QEXTTcpPacketParserInterface;
class QEXTTcpPacketDispatcher;
class QEXTTcpPacketInterface;
class QEXTTcpPacketTransceiverPrivate;
class QEXT_TCP_API QEXTTcpPacketTransceiver : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTTcpPacketTransceiver)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTTcpPacketTransceiver)
public:
    QEXTTcpPacketTransceiver(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);
    QEXTTcpPacketTransceiver(QEXTTcpPacketTransceiverPrivate *d);
    QEXTTcpPacketTransceiver(QEXTTcpPacketTransceiverPrivate *d, const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);
    ~QEXTTcpPacketTransceiver();

    QEXTId identityId() const;
    bool isSocketValid() const;

    bool send(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket);
    bool sendReply(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket,
                   QSharedPointer<QEXTTcpPacketInterface> &receivedPacket);
    bool sendNotify(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket);
    bool sendRequest(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket);
    bool sendRequestSync(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket,
                         QSharedPointer<QEXTTcpPacketInterface> &receivedPacket,
                         quint16 timeoutMsecs = 1500);

    bool waitForData(int msecs = 3000);
    void cancelWait();

    QSharedPointer<QEXTTcpPacketInterface> syncSendedPacket() const;
    QSharedPointer<QEXTTcpPacketInterface> syncReceivedPacket() const;

    int packetCount() const;
    bool isPacketQueueEmpty() const;
    QSharedPointer<QEXTTcpPacketInterface> dequeuePacket();
    void enqueuePacket(const QSharedPointer<QEXTTcpPacketInterface> &packet);

    QSharedPointer<QEXTTcpPacketParserInterface> packetParser() const;
    QSharedPointer<QEXTTcpPacketDispatcher> dispatcher() const;
    QString lastError() const;

Q_SIGNALS:
    void error(const QString &error);
    void packetReady();

protected:
    void setRequestSyncFlag(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket);
    void resetRequestSyncFlag(const QSharedPointer<QEXTTcpPacketInterface> &receivedPacket);
    void setError(const QString &error);

    QScopedPointer<QEXTTcpPacketTransceiverPrivate> dd_ptr;
};

#endif // _QEXTTCPPACKETTRANSCEIVER_H
