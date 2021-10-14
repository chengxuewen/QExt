#ifndef QEXTTCPPACKETTRANSCEIVER_H
#define QEXTTCPPACKETTRANSCEIVER_H

#include <qextTcpGlobal.h>

#include <qextObject.h>
#include <qextid.h>

#include <QObject>
#include <QSharedPointer>

class QEXTTcpPacketParserInterface;
class QEXTTcpPacketDispatcher;
class QEXTTcpPacketInterface;
class QEXTTcpPacketTransceiverPrivate;
class QEXT_TCP_API QEXTTcpPacketTransceiver : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpPacketTransceiver(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);
    QEXTTcpPacketTransceiver(QEXTTcpPacketTransceiverPrivate &dd);
    QEXTTcpPacketTransceiver(QEXTTcpPacketTransceiverPrivate &dd, const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher);
    ~QEXTTcpPacketTransceiver();

    QEXTId identityId() const;
    bool isSocketValid() const;

    bool send(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket);
    bool sendReply(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket, QSharedPointer<QEXTTcpPacketInterface> &receivedPacket);
    bool sendNotify(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket);
    bool sendRequest(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket);
    bool sendRequestSync(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket, QSharedPointer<QEXTTcpPacketInterface> &receivedPacket);

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

protected:
    void setRequestSyncFlag(const QSharedPointer<QEXTTcpPacketInterface> &sendPacket);
    void resetRequestSyncFlag(const QSharedPointer<QEXTTcpPacketInterface> &receivedPacket);
    void setError(const QString &error);

Q_SIGNALS:
    void error(const QString &error);
    void packetReady();

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketTransceiver)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketTransceiver)
};

#endif // QEXTTCPPACKETTRANSCEIVER_H
