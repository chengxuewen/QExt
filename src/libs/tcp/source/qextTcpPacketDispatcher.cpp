#include <qextTcpPacketDispatcher.h>
#include <qextTcpPacketDispatcher_p.h>
#include <qextTcpUtils.h>
#include <qextTcpSocket.h>
#include <qextTcpFactory.h>
#include <qextTcpTask.h>
#include <qextTcpTaskPool.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketTransceiver.h>

#include <QDebug>
#include <QTimer>

QEXTTcpPacketDispatcherPrivate::QEXTTcpPacketDispatcherPrivate(QEXTTcpPacketDispatcher *q)
    : q_ptr(q)
{
}

QEXTTcpPacketDispatcherPrivate::~QEXTTcpPacketDispatcherPrivate()
{

}


QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(QEXTTcpSocket *socket)
    : QObject(QEXT_DECL_NULLPTR), dd_ptr(new QEXTTcpPacketDispatcherPrivate(this))
{
    Q_D(QEXTTcpPacketDispatcher);
    connect(this, SIGNAL(send()), socket, SLOT(sendPacket()));
    d->m_socket = socket;
    d->m_taskPool = QSharedPointer<QEXTTcpTaskPool>(new QEXTTcpTaskPool(this));
    this->setTcpFactory(QSharedPointer<QEXTTcpFactory>(new QEXTTcpFactory));
}

QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(QEXTTcpSocket *socket,
                                                 const QSharedPointer<QEXTTcpFactory> &tcpFactory)
    : QObject(QEXT_DECL_NULLPTR), dd_ptr(new QEXTTcpPacketDispatcherPrivate(this))
{
    Q_D(QEXTTcpPacketDispatcher);
    connect(this, SIGNAL(send()), socket, SLOT(sendPacket()));
    d->m_socket = socket;
    d->m_taskPool = QSharedPointer<QEXTTcpTaskPool>(new QEXTTcpTaskPool(this));
    this->setTcpFactory(tcpFactory);
}

QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate *d,
                                                 QEXTTcpSocket *socket)
    : QObject(QEXT_DECL_NULLPTR), dd_ptr(d)
{
    connect(this, SIGNAL(send()), socket, SLOT(sendPacket()));
    dd_ptr->m_socket = socket;
    dd_ptr->m_taskPool = QSharedPointer<QEXTTcpTaskPool>(new QEXTTcpTaskPool(this));
    this->setTcpFactory(QSharedPointer<QEXTTcpFactory>(new QEXTTcpFactory));
}

QEXTTcpPacketDispatcher::QEXTTcpPacketDispatcher(QEXTTcpPacketDispatcherPrivate *d,
                                                 QEXTTcpSocket *socket,
                                                 const QSharedPointer<QEXTTcpFactory> &tcpFactory)
    : QObject(QEXT_DECL_NULLPTR), dd_ptr(d)
{
    connect(this, SIGNAL(send()), socket, SLOT(sendPacket()));
    dd_ptr->m_socket = socket;
    dd_ptr->m_taskPool = QSharedPointer<QEXTTcpTaskPool>(new QEXTTcpTaskPool(this));
    this->setTcpFactory(tcpFactory);
}

QEXTTcpPacketDispatcher::~QEXTTcpPacketDispatcher()
{

}

bool QEXTTcpPacketDispatcher::isSocketValid() const
{
    Q_D(const QEXTTcpPacketDispatcher);
    return !d->m_socket.isNull() && d->m_socket->isConnected();
}

QSharedPointer<QEXTTcpPacketParserInterface> QEXTTcpPacketDispatcher::packetParser() const
{
    Q_D(const QEXTTcpPacketDispatcher);
    return d->m_socket->packetParser();
}

QPointer<QEXTTcpSocket> QEXTTcpPacketDispatcher::socket() const
{
    Q_D(const QEXTTcpPacketDispatcher);
    return d->m_socket;
}

QSharedPointer<QEXTTcpTaskPool> QEXTTcpPacketDispatcher::taskPool() const
{
    Q_D(const QEXTTcpPacketDispatcher);
    return d->m_taskPool;
}

QSharedPointer<QEXTTcpFactory> QEXTTcpPacketDispatcher::tcpFactory() const
{
    Q_D(const QEXTTcpPacketDispatcher);
    QMutexLocker taskMutexLocker(&d->m_taskMutex);
    return d->m_tcpFactory;
}

void QEXTTcpPacketDispatcher::setTcpFactory(const QSharedPointer<QEXTTcpFactory> &tcpFactory)
{
    Q_D(QEXTTcpPacketDispatcher);
    QMutexLocker taskMutexLocker(&d->m_taskMutex);
    if (tcpFactory != d->m_tcpFactory)
    {
        d->m_tcpFactory = tcpFactory;
    }
}

QSharedPointer<QEXTTcpPacketTransceiver> QEXTTcpPacketDispatcher::createPacketTransceiver() const
{
    return QSharedPointer<QEXTTcpPacketTransceiver>(new QEXTTcpPacketTransceiver(this->socket()->packetDispatcher()));
}

void QEXTTcpPacketDispatcher::registerRequestPacketIdWithTransceiver(quint64 requestPacketId, QEXTTcpPacketTransceiver *transceiver)
{
    Q_D(QEXTTcpPacketDispatcher);
    QMutexLocker transceiverMutexLocker(&d->m_transceiverMutex);
    d->m_requestPacketIdToReceiverMap.insert(requestPacketId, QPointer<QEXTTcpPacketTransceiver>(transceiver));
}

void QEXTTcpPacketDispatcher::unregisterRequestPacketId(quint64 requestPacketId)
{
    Q_D(QEXTTcpPacketDispatcher);
    QMutexLocker transceiverMutexLocker(&d->m_transceiverMutex);
    d->m_requestPacketIdToReceiverMap.remove(requestPacketId);
}

void QEXTTcpPacketDispatcher::unregisterTransceiver(QEXTTcpPacketTransceiver *transceiver)
{
    Q_D(QEXTTcpPacketDispatcher);
    QMutexLocker transceiverMutexLocker(&d->m_transceiverMutex);
    QList<quint64> keys = d->m_requestPacketIdToReceiverMap.keys(QPointer<QEXTTcpPacketTransceiver>(transceiver));
    QList<quint64>::iterator iter;
    for (iter = keys.begin(); iter != keys.end(); ++iter)
    {
        d->m_requestPacketIdToReceiverMap.remove(*iter);
    }
}

bool QEXTTcpPacketDispatcher::sendPacket(QEXTTcpPacketTransceiver *transceiver, const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    Q_D(QEXTTcpPacketDispatcher);
    this->registerRequestPacketIdWithTransceiver(d->m_socket->packetParser()->packetId(packet), transceiver);
    d->m_socket->enqueueSendPacket(packet);
    emit this->send();
    return true;
}

bool QEXTTcpPacketDispatcher::dispatchPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet, QString *error)
{
    Q_UNUSED(error);
    Q_D(QEXTTcpPacketDispatcher);
    if (this->dispatchToTransceiver(packet))
    {
        return true;
    }
    if (this->dispatchToTask(packet))
    {
        return true;
    }
    if (error)
    {
        quint64 id = d->m_socket->packetParser()->packetId(packet);
        *error = QString("packet %1 not handle").arg(id);
    }
    qCritical() << "QEXTTcpPacketDispatcher::dispatchPacket():packet not handle";
    QEXTTcpUtils::printPacket(packet);
    return false;
}

bool QEXTTcpPacketDispatcher::dispatchToTransceiver(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    Q_D(QEXTTcpPacketDispatcher);
    quint64 id = d->m_socket->packetParser()->packetId(packet);
    QMutexLocker transceiverMutexLocker(&d->m_transceiverMutex);
    /*remove null transceiver*/
    QList<quint64> invalIdList = d->m_requestPacketIdToReceiverMap.keys(QEXT_DECL_NULLPTR);
    for (QList<quint64>::Iterator iter = invalIdList.begin(); iter != invalIdList.end(); ++iter) {
        d->m_requestPacketIdToReceiverMap.remove((*iter));
    }
    /*find target transceiver*/
    QPointer<QEXTTcpPacketTransceiver> transceiver = d->m_requestPacketIdToReceiverMap.value(id, QEXT_DECL_NULLPTR);
    if (!transceiver.isNull())
    {
        transceiver->enqueuePacket(packet);
        d->m_requestPacketIdToReceiverMap.remove(id);
        return true;
    }
    return false;
}

bool QEXTTcpPacketDispatcher::dispatchToTask(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    Q_D(QEXTTcpPacketDispatcher);
    QMutexLocker taskMutexLocker(&d->m_taskMutex);
    if (!d->m_tcpFactory.isNull())
    {
        QEXTTcpTask *task = d->m_tcpFactory->createTask(d->m_socket->packetDispatcher(), packet);
        if (task)
        {
            d->m_taskPool->enqueueTask(task);
            return true;
        }
    }
    return false;
}
