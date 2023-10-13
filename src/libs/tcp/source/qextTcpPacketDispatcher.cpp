#include <private/qextTcpPacketDispatcher_p.h>
#include <qextTcpUtils.h>
#include <qextTcpSocket.h>
#include <qextTcpFactory.h>
#include <qextTcpTask.h>
#include <qextTcpTaskPool.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketTransceiver.h>

#include <QDebug>
#include <QTimer>

QExtTcpPacketDispatcherPrivate::QExtTcpPacketDispatcherPrivate(QExtTcpPacketDispatcher *q)
    : q_ptr(q)
{
}

QExtTcpPacketDispatcherPrivate::~QExtTcpPacketDispatcherPrivate()
{

}


QExtTcpPacketDispatcher::QExtTcpPacketDispatcher(QExtTcpSocket *socket)
    : QObject(QEXT_DECL_NULLPTR), dd_ptr(new QExtTcpPacketDispatcherPrivate(this))
{
    Q_D(QExtTcpPacketDispatcher);
    connect(this, SIGNAL(send()), socket, SLOT(sendPacket()));
    d->m_socket = socket;
    d->m_taskPool = QSharedPointer<QExtTcpTaskPool>(new QExtTcpTaskPool(this));
    this->setTcpFactory(QSharedPointer<QExtTcpFactory>(new QExtTcpFactory));
}

QExtTcpPacketDispatcher::QExtTcpPacketDispatcher(QExtTcpSocket *socket,
                                                 const QSharedPointer<QExtTcpFactory> &tcpFactory)
    : QObject(QEXT_DECL_NULLPTR), dd_ptr(new QExtTcpPacketDispatcherPrivate(this))
{
    Q_D(QExtTcpPacketDispatcher);
    connect(this, SIGNAL(send()), socket, SLOT(sendPacket()));
    d->m_socket = socket;
    d->m_taskPool = QSharedPointer<QExtTcpTaskPool>(new QExtTcpTaskPool(this));
    this->setTcpFactory(tcpFactory);
}

QExtTcpPacketDispatcher::QExtTcpPacketDispatcher(QExtTcpPacketDispatcherPrivate *d,
                                                 QExtTcpSocket *socket)
    : QObject(QEXT_DECL_NULLPTR), dd_ptr(d)
{
    connect(this, SIGNAL(send()), socket, SLOT(sendPacket()));
    dd_ptr->m_socket = socket;
    dd_ptr->m_taskPool = QSharedPointer<QExtTcpTaskPool>(new QExtTcpTaskPool(this));
    this->setTcpFactory(QSharedPointer<QExtTcpFactory>(new QExtTcpFactory));
}

QExtTcpPacketDispatcher::QExtTcpPacketDispatcher(QExtTcpPacketDispatcherPrivate *d,
                                                 QExtTcpSocket *socket,
                                                 const QSharedPointer<QExtTcpFactory> &tcpFactory)
    : QObject(QEXT_DECL_NULLPTR), dd_ptr(d)
{
    connect(this, SIGNAL(send()), socket, SLOT(sendPacket()));
    dd_ptr->m_socket = socket;
    dd_ptr->m_taskPool = QSharedPointer<QExtTcpTaskPool>(new QExtTcpTaskPool(this));
    this->setTcpFactory(tcpFactory);
}

QExtTcpPacketDispatcher::~QExtTcpPacketDispatcher()
{

}

bool QExtTcpPacketDispatcher::isSocketValid() const
{
    Q_D(const QExtTcpPacketDispatcher);
    return !d->m_socket.isNull() && d->m_socket->isConnected();
}

QSharedPointer<QExtTcpPacketParserInterface> QExtTcpPacketDispatcher::packetParser() const
{
    Q_D(const QExtTcpPacketDispatcher);
    return d->m_socket->packetParser();
}

QPointer<QExtTcpSocket> QExtTcpPacketDispatcher::socket() const
{
    Q_D(const QExtTcpPacketDispatcher);
    return d->m_socket;
}

QSharedPointer<QExtTcpTaskPool> QExtTcpPacketDispatcher::taskPool() const
{
    Q_D(const QExtTcpPacketDispatcher);
    return d->m_taskPool;
}

QSharedPointer<QExtTcpFactory> QExtTcpPacketDispatcher::tcpFactory() const
{
    Q_D(const QExtTcpPacketDispatcher);
    QMutexLocker taskMutexLocker(&d->m_taskMutex);
    return d->m_tcpFactory;
}

void QExtTcpPacketDispatcher::setTcpFactory(const QSharedPointer<QExtTcpFactory> &tcpFactory)
{
    Q_D(QExtTcpPacketDispatcher);
    QMutexLocker taskMutexLocker(&d->m_taskMutex);
    if (tcpFactory != d->m_tcpFactory)
    {
        d->m_tcpFactory = tcpFactory;
    }
}

QSharedPointer<QExtTcpPacketTransceiver> QExtTcpPacketDispatcher::createPacketTransceiver() const
{
    return QSharedPointer<QExtTcpPacketTransceiver>(new QExtTcpPacketTransceiver(this->socket()->packetDispatcher()));
}

void QExtTcpPacketDispatcher::registerRequestPacketIdWithTransceiver(quint64 requestPacketId, QExtTcpPacketTransceiver *transceiver)
{
    Q_D(QExtTcpPacketDispatcher);
    QMutexLocker transceiverMutexLocker(&d->m_transceiverMutex);
    d->m_requestPacketIdToReceiverMap.insert(requestPacketId, QPointer<QExtTcpPacketTransceiver>(transceiver));
}

void QExtTcpPacketDispatcher::unregisterRequestPacketId(quint64 requestPacketId)
{
    Q_D(QExtTcpPacketDispatcher);
    QMutexLocker transceiverMutexLocker(&d->m_transceiverMutex);
    d->m_requestPacketIdToReceiverMap.remove(requestPacketId);
}

void QExtTcpPacketDispatcher::unregisterTransceiver(QExtTcpPacketTransceiver *transceiver)
{
    Q_D(QExtTcpPacketDispatcher);
    QMutexLocker transceiverMutexLocker(&d->m_transceiverMutex);
    QList<quint64> keys = d->m_requestPacketIdToReceiverMap.keys(QPointer<QExtTcpPacketTransceiver>(transceiver));
    QList<quint64>::iterator iter;
    for (iter = keys.begin(); iter != keys.end(); ++iter)
    {
        d->m_requestPacketIdToReceiverMap.remove(*iter);
    }
}

bool QExtTcpPacketDispatcher::sendPacket(QExtTcpPacketTransceiver *transceiver, const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    Q_D(QExtTcpPacketDispatcher);
    this->registerRequestPacketIdWithTransceiver(d->m_socket->packetParser()->packetId(packet), transceiver);
    d->m_socket->enqueueSendPacket(packet);
    emit this->send();
    return true;
}

bool QExtTcpPacketDispatcher::dispatchPacket(const QSharedPointer<QExtTcpPacketInterface> &packet, QString *error)
{
    Q_UNUSED(error);
    Q_D(QExtTcpPacketDispatcher);
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
    qCritical() << "QExtTcpPacketDispatcher::dispatchPacket():packet not handle";
    QExtTcpUtils::printPacket(packet);
    return false;
}

bool QExtTcpPacketDispatcher::dispatchToTransceiver(const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    Q_D(QExtTcpPacketDispatcher);
    quint64 id = d->m_socket->packetParser()->packetId(packet);
    QMutexLocker transceiverMutexLocker(&d->m_transceiverMutex);
    /*remove null transceiver*/
    QList<quint64> invalIdList = d->m_requestPacketIdToReceiverMap.keys(QEXT_DECL_NULLPTR);
    for (QList<quint64>::Iterator iter = invalIdList.begin(); iter != invalIdList.end(); ++iter) {
        d->m_requestPacketIdToReceiverMap.remove((*iter));
    }
    /*find target transceiver*/
    QPointer<QExtTcpPacketTransceiver> transceiver = d->m_requestPacketIdToReceiverMap.value(id, QEXT_DECL_NULLPTR);
    if (!transceiver.isNull())
    {
        transceiver->enqueuePacket(packet);
        d->m_requestPacketIdToReceiverMap.remove(id);
        return true;
    }
    return false;
}

bool QExtTcpPacketDispatcher::dispatchToTask(const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    Q_D(QExtTcpPacketDispatcher);
    QMutexLocker taskMutexLocker(&d->m_taskMutex);
    if (!d->m_tcpFactory.isNull())
    {
        QExtTcpTask *task = d->m_tcpFactory->createTask(d->m_socket->packetDispatcher(), packet);
        if (task)
        {
            d->m_taskPool->enqueueTask(task);
            return true;
        }
    }
    return false;
}
