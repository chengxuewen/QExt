#include <qextTcpPacketDispatcher.h>
#include <qextTcpPacketDispatcher_p.h>
#include <qextTcpUtils.h>
#include <qextTcpSocket.h>
#include <qextTcpTask.h>
#include <qextTcpTaskPool.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketTransceiver.h>

#include <QDebug>
#include <QTimer>

QEXTTcpPacketDispatcherPrivate::QEXTTcpPacketDispatcherPrivate(QEXTTcpPacketDispatcher *qq)
    : QEXTObjectPrivate(qq)
{
}

QEXTTcpPacketDispatcherPrivate::~QEXTTcpPacketDispatcherPrivate()
{

}


QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(const QSharedPointer<QEXTTcpSocket> &socket)
    : QObject(), QEXTObject(*(new QEXTTcpPacketDispatcherPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    connect(this, SIGNAL(send()), socket.data(), SLOT(sendPacket()));
    d->m_socket = socket.toWeakRef();
    d->m_taskPool = QSharedPointer<QEXTTcpTaskPool>(new QEXTTcpTaskPool(this));
    this->setTaskFactory(QSharedPointer<QEXTTcpTaskFactory>(new QEXTTcpTaskFactory));
}

QEXTTcpPacketDispatcher::~QEXTTcpPacketDispatcher()
{

}

bool QEXTTcpPacketDispatcher::isSocketValid() const
{
    QEXT_DECL_DC(QEXTTcpPacketDispatcher);
    QSharedPointer<QEXTTcpSocket> socket(d->m_socket);
    return !socket.isNull() && socket->isConnected();
}

QSharedPointer<QEXTTcpPacketParserInterface> QEXTTcpPacketDispatcher::packetParser() const
{
    QEXT_DECL_DC(QEXTTcpPacketDispatcher);
    QSharedPointer<QEXTTcpSocket> socket(d->m_socket);
    return socket->packetParser();
}

QSharedPointer<QEXTTcpPacketDispatcher> QEXTTcpPacketDispatcher::sharedPointer() const
{
    return this->socket()->packetDispatcher();
}

QSharedPointer<QEXTTcpSocket> QEXTTcpPacketDispatcher::socket() const
{
    QEXT_DECL_DC(QEXTTcpPacketDispatcher);
    return d->m_socket;
}

QSharedPointer<QEXTTcpTaskPool> QEXTTcpPacketDispatcher::taskPool() const
{
    QEXT_DECL_DC(QEXTTcpPacketDispatcher);
    return d->m_taskPool;
}

QSharedPointer<QEXTTcpTaskFactory> QEXTTcpPacketDispatcher::taskFactory() const
{
    QEXT_DECL_DC(QEXTTcpPacketDispatcher);
    return d->m_taskFactory;
}

void QEXTTcpPacketDispatcher::setTaskFactory(const QSharedPointer<QEXTTcpTaskFactory> &taskFactory)
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    QMutexLocker locker(&d->m_taskMutex);
    if (taskFactory != d->m_taskFactory)
    {
        d->m_taskFactory = taskFactory;
    }
}

void QEXTTcpPacketDispatcher::registerRequestPacketIdWithTransceiver(quint64 requestPacketId, QEXTTcpPacketTransceiver *transceiver)
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    QMutexLocker locker(&d->m_transceiverMutex);
    d->m_requestPacketIdToReceiverMap.insert(requestPacketId, QPointer<QEXTTcpPacketTransceiver>(transceiver));
}

void QEXTTcpPacketDispatcher::unregisterRequestPacketId(quint64 requestPacketId)
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    QMutexLocker locker(&d->m_transceiverMutex);
    d->m_requestPacketIdToReceiverMap.remove(requestPacketId);
}

void QEXTTcpPacketDispatcher::unregisterTransceiver(QEXTTcpPacketTransceiver *transceiver)
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    QMutexLocker locker(&d->m_transceiverMutex);
    QList<quint64> keys = d->m_requestPacketIdToReceiverMap.keys(QPointer<QEXTTcpPacketTransceiver>(transceiver));
    QList<quint64>::iterator iter;
    for (iter = keys.begin(); iter != keys.end(); ++iter)
    {
        d->m_requestPacketIdToReceiverMap.remove(*iter);
    }
}

bool QEXTTcpPacketDispatcher::sendPacket(QEXTTcpPacketTransceiver *transceiver, const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    QMutexLocker locker(&d->m_socketMutex);
    QSharedPointer<QEXTTcpSocket> socket(d->m_socket);
    this->registerRequestPacketIdWithTransceiver(socket->packetParser()->packetId(packet.data()), transceiver);
    socket->enqueueSendPacket(packet);
    emit this->send();
    return true;
}

bool QEXTTcpPacketDispatcher::dispatchPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet, QString *error)
{
    Q_UNUSED(error);
    QEXT_DECL_D(QEXTTcpPacketDispatcher);
    QMutexLocker locker(&d->m_transceiverMutex);
    QSharedPointer<QEXTTcpSocket> socket(d->m_socket);
    quint64 id = socket->packetParser()->packetId(packet.data());
    QPointer<QEXTTcpPacketTransceiver> transceiver = d->m_requestPacketIdToReceiverMap.value(id);
    if (!transceiver.isNull())
    {
        transceiver->enqueuePacket(packet);
        return true;
    }
    else
    {
        QList<quint64> keys = d->m_requestPacketIdToReceiverMap.keys(transceiver);
        QList<quint64>::iterator iter;
        for (iter = keys.begin(); iter != keys.end(); ++iter)
        {
            d->m_requestPacketIdToReceiverMap.remove(*iter);
        }
    }
    if (!d->m_taskFactory.isNull())
    {
        QEXTTcpTask *task = d->m_taskFactory->createTask(this->sharedPointer(), packet);
        if (task)
        {
            d->m_taskPool->enqueueTask(task);
            return true;
        }
    }
    return false;
}



QSharedPointer<QEXTTcpPacketDispatcher> QEXTTcpPacketDispatcherFactory::createPacketDispatcher(const QSharedPointer<QEXTTcpSocket> &socket)
{
    return QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(socket));
}
