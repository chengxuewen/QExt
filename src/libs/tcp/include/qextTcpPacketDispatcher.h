#ifndef _QEXTTCPPACKETDISPATCHER_H
#define _QEXTTCPPACKETDISPATCHER_H

#include <qextTcpGlobal.h>

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
class QEXT_TCP_API QEXTTcpPacketDispatcher : public QObject
{
    Q_OBJECT
public:
    QEXTTcpPacketDispatcher(QEXTTcpSocket *socket);
    QEXTTcpPacketDispatcher(QEXTTcpSocket *socket, const QSharedPointer<QEXTTcpFactory> &tcpFactory);
    QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate *d, QEXTTcpSocket *socket);
    QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate *d, QEXTTcpSocket *socket,
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

protected:
    QScopedPointer<QEXTTcpPacketDispatcherPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QEXTTcpPacketDispatcher)
    QEXT_DECL_DISABLE_COPY(QEXTTcpPacketDispatcher)
};

#endif // _QEXTTCPPACKETDISPATCHER_H
