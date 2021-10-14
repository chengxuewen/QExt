#ifndef QEXTTCPPACKETDISPATCHER_H
#define QEXTTCPPACKETDISPATCHER_H

#include <qextTcpGlobal.h>

#include <qextObject.h>

#include <QObject>
#include <QPointer>
#include <QSharedPointer>

class QEXTTcpTask;
class QEXTTcpSocket;
class QEXTTcpTaskPool;
class QEXTTcpPacketParserInterface;
class QEXTTcpPacketTransceiver;
class QEXTTcpPacketInterface;
class QEXTTcpFactory;
class QEXTTcpPacketDispatcherPrivate;
class QEXT_TCP_API QEXTTcpPacketDispatcher : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpPacketDispatcher(QEXTTcpSocket *socket);
    QEXTTcpPacketDispatcher(QEXTTcpSocket *socket, const QSharedPointer<QEXTTcpFactory> &tcpFactory);
    QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate &dd, QEXTTcpSocket *socket);
    QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate &dd, QEXTTcpSocket *socket,
                            const QSharedPointer<QEXTTcpFactory> &tcpFactory);
    ~QEXTTcpPacketDispatcher();

    bool isSocketValid() const;
    QPointer<QEXTTcpSocket> socket() const;

    QSharedPointer<QEXTTcpPacketParserInterface> packetParser() const;
    QSharedPointer<QEXTTcpTaskPool> taskPool() const;

    QSharedPointer<QEXTTcpFactory> tcpFactory() const;
    void setTcpFactory(const QSharedPointer<QEXTTcpFactory> &tcpFactory);

    QSharedPointer<QEXTTcpPacketTransceiver> createPacketTransceiver() const;
    void registerRequestPacketIdWithTransceiver(quint64 requestPacketId, QEXTTcpPacketTransceiver *transceiver);
    void unregisterRequestPacketId(quint64 requestPacketId);
    void unregisterTransceiver(QEXTTcpPacketTransceiver *transceiver);
    bool sendPacket(QEXTTcpPacketTransceiver *transceiver, const QSharedPointer<QEXTTcpPacketInterface> &packet);

    virtual bool dispatchPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet, QString *error = QEXT_DECL_NULLPTR);
    bool dispatchToTransceiver(const QSharedPointer<QEXTTcpPacketInterface> &packet);
    bool dispatchToTask(const QSharedPointer<QEXTTcpPacketInterface> &packet);

Q_SIGNALS:
    void error(const QString &error);
    void send();

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketDispatcher)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketDispatcher)
};

#endif // QEXTTCPPACKETDISPATCHER_H
