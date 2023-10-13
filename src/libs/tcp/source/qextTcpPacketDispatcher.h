#ifndef _QEXTTCPPACKETDISPATCHER_H
#define _QEXTTCPPACKETDISPATCHER_H

#include <qextTcpGlobal.h>

#include <QObject>
#include <QPointer>
#include <QSharedPointer>

class QExtTcpTask;
class QExtTcpSocket;
class QExtTcpTaskPool;
class QExtTcpPacketParserInterface;
class QExtTcpPacketTransceiver;
class QExtTcpPacketInterface;
class QExtTcpFactory;
class QExtTcpPacketDispatcherPrivate;
class QEXT_TCP_API QExtTcpPacketDispatcher : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtTcpPacketDispatcher)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpPacketDispatcher)
public:
    QExtTcpPacketDispatcher(QExtTcpSocket *socket);
    QExtTcpPacketDispatcher(QExtTcpSocket *socket, const QSharedPointer<QExtTcpFactory> &tcpFactory);
    QExtTcpPacketDispatcher(QExtTcpPacketDispatcherPrivate *d, QExtTcpSocket *socket);
    QExtTcpPacketDispatcher(QExtTcpPacketDispatcherPrivate *d, QExtTcpSocket *socket,
                            const QSharedPointer<QExtTcpFactory> &tcpFactory);
    ~QExtTcpPacketDispatcher();

    bool isSocketValid() const;
    QPointer<QExtTcpSocket> socket() const;

    QSharedPointer<QExtTcpPacketParserInterface> packetParser() const;
    QSharedPointer<QExtTcpTaskPool> taskPool() const;

    QSharedPointer<QExtTcpFactory> tcpFactory() const;
    void setTcpFactory(const QSharedPointer<QExtTcpFactory> &tcpFactory);

    QSharedPointer<QExtTcpPacketTransceiver> createPacketTransceiver() const;
    void registerRequestPacketIdWithTransceiver(quint64 requestPacketId, QExtTcpPacketTransceiver *transceiver);
    void unregisterRequestPacketId(quint64 requestPacketId);
    void unregisterTransceiver(QExtTcpPacketTransceiver *transceiver);
    bool sendPacket(QExtTcpPacketTransceiver *transceiver, const QSharedPointer<QExtTcpPacketInterface> &packet);

    virtual bool dispatchPacket(const QSharedPointer<QExtTcpPacketInterface> &packet, QString *error = QEXT_DECL_NULLPTR);
    bool dispatchToTransceiver(const QSharedPointer<QExtTcpPacketInterface> &packet);
    bool dispatchToTask(const QSharedPointer<QExtTcpPacketInterface> &packet);

Q_SIGNALS:
    void error(const QString &error);
    void send();

protected:
    QScopedPointer<QExtTcpPacketDispatcherPrivate> dd_ptr;
};

#endif // _QEXTTCPPACKETDISPATCHER_H
