#ifndef QEXTTCPPACKETDISPATCHER_H
#define QEXTTCPPACKETDISPATCHER_H

#include <qextTcpGlobal.h>

#include <qextobject.h>

#include <QObject>
#include <QSharedPointer>

class QEXTTcpSocket;
class QEXTTcpTaskPool;
class QEXTTcpPacketParserInterface;
class QEXTTcpPacketTransceiver;
class QEXTTcpPacketInterface;
class QEXTTcpTaskFactory;
class QEXTTcpPacketDispatcherPrivate;
class QEXT_TCP_API QEXTTcpPacketDispatcher : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpPacketDispatcher(const QSharedPointer<QEXTTcpSocket> &socket);
    ~QEXTTcpPacketDispatcher();

    bool isSocketValid() const;
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser() const;
    QSharedPointer<QEXTTcpPacketDispatcher> sharedPointer() const;
    QSharedPointer<QEXTTcpSocket> socket() const;
    QSharedPointer<QEXTTcpTaskPool> taskPool() const;

    QSharedPointer<QEXTTcpTaskFactory> taskFactory() const;
    void setTaskFactory(const QSharedPointer<QEXTTcpTaskFactory> &taskFactory);

    void registerRequestPacketIdWithTransceiver(quint64 requestPacketId, QEXTTcpPacketTransceiver *transceiver);
    void unregisterRequestPacketId(quint64 requestPacketId);
    void unregisterTransceiver(QEXTTcpPacketTransceiver *transceiver);
    bool sendPacket(QEXTTcpPacketTransceiver *transceiver, const QSharedPointer<QEXTTcpPacketInterface> &packet);

    virtual bool dispatchPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet, QString *error = QEXT_DECL_NULLPTR);

Q_SIGNALS:
    void error(const QString &error);
    void send();

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketDispatcher)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketDispatcher)
};


class QEXT_TCP_API QEXTTcpPacketDispatcherFactory
{
public:
    QEXTTcpPacketDispatcherFactory() {}
    ~QEXTTcpPacketDispatcherFactory() {}

    virtual QSharedPointer<QEXTTcpPacketDispatcher> createPacketDispatcher(const QSharedPointer<QEXTTcpSocket> &socket);
};

#endif // QEXTTCPPACKETDISPATCHER_H
