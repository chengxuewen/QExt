#ifndef _QEXTTCPPACKETTRANSCEIVER_H
#define _QEXTTCPPACKETTRANSCEIVER_H

#include <qextTcpGlobal.h>
#include <qextTag.h>

#include <QObject>
#include <QSharedPointer>

class QExtTcpPacketParserInterface;
class QExtTcpPacketDispatcher;
class QExtTcpPacketInterface;
class QExtTcpPacketTransceiverPrivate;
class QEXT_TCP_API QExtTcpPacketTransceiver : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtTcpPacketTransceiver)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpPacketTransceiver)
public:
    QExtTcpPacketTransceiver(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher);
    QExtTcpPacketTransceiver(QExtTcpPacketTransceiverPrivate *d);
    QExtTcpPacketTransceiver(QExtTcpPacketTransceiverPrivate *d, const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher);
    ~QExtTcpPacketTransceiver();

    QExtTag identityId() const;
    bool isSocketValid() const;

    bool send(const QSharedPointer<QExtTcpPacketInterface> &sendPacket);
    bool sendReply(const QSharedPointer<QExtTcpPacketInterface> &sendPacket,
                   QSharedPointer<QExtTcpPacketInterface> &receivedPacket);
    bool sendNotify(const QSharedPointer<QExtTcpPacketInterface> &sendPacket);
    bool sendRequest(const QSharedPointer<QExtTcpPacketInterface> &sendPacket);
    bool sendRequestSync(const QSharedPointer<QExtTcpPacketInterface> &sendPacket,
                         QSharedPointer<QExtTcpPacketInterface> &receivedPacket,
                         quint16 timeoutMsecs = 1500);

    bool waitForData(int msecs = 3000);
    void cancelWait();

    QSharedPointer<QExtTcpPacketInterface> syncSendedPacket() const;
    QSharedPointer<QExtTcpPacketInterface> syncReceivedPacket() const;

    int packetCount() const;
    bool isPacketQueueEmpty() const;
    QSharedPointer<QExtTcpPacketInterface> dequeuePacket();
    void enqueuePacket(const QSharedPointer<QExtTcpPacketInterface> &packet);

    QSharedPointer<QExtTcpPacketParserInterface> packetParser() const;
    QSharedPointer<QExtTcpPacketDispatcher> dispatcher() const;
    QString lastError() const;

Q_SIGNALS:
    void error(const QString &error);
    void packetReady();

protected:
    void setRequestSyncFlag(const QSharedPointer<QExtTcpPacketInterface> &sendPacket);
    void resetRequestSyncFlag(const QSharedPointer<QExtTcpPacketInterface> &receivedPacket);
    void setError(const QString &error);

    QScopedPointer<QExtTcpPacketTransceiverPrivate> dd_ptr;
};

#endif // _QEXTTCPPACKETTRANSCEIVER_H
