#include <qexttcptransferthreadpool.h>
#include <qexttcptransferthreadpool_p.h>
#include <qexttcpserversocket.h>
#include <qexttcpserver.h>

#include <QSetIterator>
#include <QMutexLocker>



QEXTTcpTransferThreadPoolPrivate::QEXTTcpTransferThreadPoolPrivate(QEXTTcpTransferThreadPool *qq)
    : QEXTTcpAbstractThreadPoolPrivate(qq)
{

}

QEXTTcpTransferThreadPoolPrivate::~QEXTTcpTransferThreadPoolPrivate()
{

}

void QEXTTcpTransferThreadPoolPrivate::handleThreadConnection(QEXTTcpTransferThread *thread, bool connect)
{
    QEXT_Q(QEXTTcpTransferThreadPool);
    if (connect) {
        QObject::connect(q, SIGNAL(establishConnectionInThread(QObject*,QEXTSocketDescriptor)),
                         thread, SLOT(incomingConnection(QObject*,QEXTSocketDescriptor)), Qt::QueuedConnection);
        QObject::connect(q, SIGNAL(addPacketToThread(QObject*,QEXTTcpAbstractPacket*)),
                         thread, SLOT(enqueueSendPacket(QObject*,QEXTTcpAbstractPacket*)), Qt::QueuedConnection);
        QObject::connect(q, SIGNAL(addSocketToThread(QObject*,QEXTTcpServerSocket*,QList<QEXTTcpAbstractPacket*>)),
                         thread, SLOT(addServerSocket(QObject*,QEXTTcpServerSocket*,QList<QEXTTcpAbstractPacket*>)), Qt::QueuedConnection);

        QObject::connect(thread, SIGNAL(socketMessage(QEXTTcpServerSocket*,QString)),
                         q, SIGNAL(socketMessage(QEXTTcpServerSocket*,QString)), Qt::QueuedConnection);
        QObject::connect(thread, SIGNAL(socketError(QEXTTcpServerSocket*,QAbstractSocket::SocketError)),
                         q, SIGNAL(socketError(QEXTTcpServerSocket*,QAbstractSocket::SocketError)), Qt::QueuedConnection);
        QObject::connect(thread, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)),
                         q, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)), Qt::QueuedConnection);

        QObject::connect(thread, SIGNAL(socketConnected(QEXTTcpServerSocket*)),
                         q, SIGNAL(socketConnected(QEXTTcpServerSocket*)), Qt::QueuedConnection);
        QObject::connect(thread, SIGNAL(socketDisconnected(QEXTTcpServerSocket*)),
                         q, SIGNAL(socketDisconnected(QEXTTcpServerSocket*)), Qt::QueuedConnection);
    } else {
        QObject::disconnect(q, SIGNAL(establishConnectionInThread(QObject*,QEXTSocketDescriptor)),
                            thread, SLOT(incomingConnection(QObject*,QEXTSocketDescriptor)));
        QObject::disconnect(q, SIGNAL(addPacketToThread(QObject*,QEXTTcpAbstractPacket*)),
                            thread, SLOT(enqueueSendPacket(QObject*,QEXTTcpAbstractPacket*)));

        QObject::disconnect(thread, SIGNAL(socketMessage(QEXTTcpServerSocket*,QString)),
                            q, SIGNAL(socketMessage(QEXTTcpServerSocket*,QString)));
        QObject::disconnect(thread, SIGNAL(socketError(QEXTTcpServerSocket*,QAbstractSocket::SocketError)),
                            q, SIGNAL(socketError(QEXTTcpServerSocket*,QAbstractSocket::SocketError)));
        QObject::disconnect(thread, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)),
                            q, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)));

        QObject::disconnect(thread, SIGNAL(socketConnected(QEXTTcpServerSocket*)),
                            q, SIGNAL(socketConnected(QEXTTcpServerSocket*)));
        QObject::disconnect(thread, SIGNAL(socketDisconnected(QEXTTcpServerSocket*)),
                            q, SIGNAL(socketDisconnected(QEXTTcpServerSocket*)));
    }
}



QEXTTcpTransferThreadPool::QEXTTcpTransferThreadPool(QObject *parent)
    : QEXTTcpAbstractThreadPool(*(new QEXTTcpTransferThreadPoolPrivate(this)), parent)
{
    QEXT_D(QEXTTcpTransferThreadPool);
    qRegisterMetaType<QList<QEXTTcpAbstractPacket*> >("QList<QEXTTcpAbstractPacket*>");
    this->addThreads(1);
}

QEXTTcpTransferThreadPool::~QEXTTcpTransferThreadPool()
{

}

void QEXTTcpTransferThreadPool::removeThread()
{
    QEXT_D(QEXTTcpTransferThreadPool);
    if (this->allTcpThreadsCount() > 0) {
        QMutexLocker mutexLocker(&d->m_threadMutex);
        QEXTTcpAbstractThread *tcpThread = d->m_allThreadsSet.values().last();
        QEXTTcpTransferThread *transferThread = dynamic_cast<QEXTTcpTransferThread *>(tcpThread);
        d->handleThreadConnection(transferThread, false);
        tcpThread->quit();
        d->m_threadMap.remove(tcpThread);
        d->m_allThreadsSet.remove(tcpThread);
        d->m_workingThreadsSet.remove(tcpThread);
        d->m_idleThreadsQueue.removeOne(tcpThread);

        QQueue<QEXTTcpAbstractPacket *> allSendPacketsQueue = transferThread->allSendPacketsQueue();
        QSet<QEXTTcpServerSocket *> allSocketsSet = transferThread->allSocketsSet();
        tcpThread->deleteLater();
        QMap<QEXTId, QList<QEXTTcpAbstractPacket *> > socketIdToPacketMap;
        while (!allSendPacketsQueue.isEmpty()) {
            QEXTTcpAbstractPacket *packet = allSendPacketsQueue.dequeue();
            QList<QEXTTcpAbstractPacket *> packetList = socketIdToPacketMap.value(packet->socketId());
            packetList.append(packet);
            socketIdToPacketMap.insert(packet->socketId(), packetList);
        }
        QSetIterator<QEXTTcpServerSocket *> iter(allSocketsSet);
        while (iter.hasNext()) {
            QEXTTcpServerSocket *socket = iter.next();
            QList<QEXTTcpAbstractPacket *> packetList = socketIdToPacketMap.value(socket->identityId());
            this->dispatchSocketToThread(socket, packetList);
        }
    }
}

void QEXTTcpTransferThreadPool::addThread()
{
    QEXT_D(QEXTTcpTransferThreadPool);
    QThread *thread = new QThread;
    QEXTTcpTransferThread *transferThread = new QEXTTcpTransferThread(this);
    transferThread->moveToThread(thread);
    if (!d->m_packetParser.isNull()) {
        transferThread->setPacketParser(d->m_packetParser->cloneParser());
    }
    if (!d->m_taskPool.isNull()) {
        transferThread->setTaskPool(d->m_taskPool);
    }
    d->m_threadMutex.lock();
    d->m_allThreadsSet.insert(transferThread);
    d->m_threadMap.insert(transferThread, thread);
    d->m_threadMutex.unlock();
    //Connect signals
    d->handleThreadConnection(transferThread, true);

    thread->start();
}

bool transferEfficiencyLessThan(QEXTTcpAbstractThread *t1, QEXTTcpAbstractThread *t2)
{
    return t1->loadAverage() < t2->loadAverage();
}

void QEXTTcpTransferThreadPool::establishConnection(QEXTSocketDescriptor socketDescriptor)
{
    QEXT_D(QEXTTcpTransferThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    QList<QEXTTcpAbstractThread *> allThreadsList = d->m_allThreadsSet.toList();
    qSort(allThreadsList.begin(), allThreadsList.end(), transferEfficiencyLessThan);
    if (allThreadsList.isEmpty()) {
        qWarning() << "QEXTTcpTransferThreadPool::establishConnection():allThreeadsList.isEmpty()";
        return;
    }

    QEXTTcpTransferThread *transferThread = dynamic_cast<QEXTTcpTransferThread *>(allThreadsList.first());
    if (transferThread) {
        emit this->establishConnectionInThread(transferThread, socketDescriptor);
    }
}

void QEXTTcpTransferThreadPool::dispatchPacketToThread(QEXTTcpAbstractPacket *packet)
{
    QEXT_D(QEXTTcpTransferThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    QEXTTcpTransferThread *transferThread = d->m_socketTransferThreadMap.value(packet->socketId());
    if (transferThread) {
        emit this->addPacketToThread(transferThread, packet);
    } else {
        emit this->transferError(QEXTTcpSocket::TransferError_SocketNotFound);
        delete packet;
    }
}

void QEXTTcpTransferThreadPool::dispatchSocketToThread(QEXTTcpServerSocket *socket, const QList<QEXTTcpAbstractPacket *> &packetList)
{
    QEXT_D(QEXTTcpTransferThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    QList<QEXTTcpAbstractThread *> allThreadsList = d->m_allThreadsSet.toList();
    qSort(allThreadsList.begin(), allThreadsList.end(), transferEfficiencyLessThan);
    if (allThreadsList.isEmpty()) {
        qWarning() << "QEXTTcpTransferThreadPool::dispatchSocketToThread():allThreeadsList.isEmpty()";
        return;
    }

    QEXTTcpTransferThread *transferThread = dynamic_cast<QEXTTcpTransferThread *>(allThreadsList.first());
    if (transferThread) {
        emit this->addSocketToThread(transferThread, socket, packetList);
    }
}

void QEXTTcpTransferThreadPool::setTaskPool(QSharedPointer<QEXTTcpAbstractTaskPool> taskPool)
{
    QEXT_D(QEXTTcpTransferThreadPool);
    QMutexLocker mutexLocker(&d->m_taskPoolMutex);
    if (!taskPool.isNull() && taskPool != d->m_taskPool) {
        if (!d->m_taskPool.isNull()) {
            disconnect(d->m_taskPool.data(), SIGNAL(newPacketReady(QEXTTcpAbstractPacket*)),
                       this, SLOT(dispatchPacketToThread(QEXTTcpAbstractPacket*)));
        }
        d->m_taskPool = taskPool;
        QMutexLocker mutexLocker(&d->m_threadMutex);
        QListIterator<QEXTTcpAbstractThread *> iter(d->m_allThreadsSet.toList());
        while (iter.hasNext()) {
            iter.next()->setTaskPool(taskPool);
        }
        connect(d->m_taskPool.data(), SIGNAL(newPacketReady(QEXTTcpAbstractPacket*)),
                this, SLOT(dispatchPacketToThread(QEXTTcpAbstractPacket*)), Qt::QueuedConnection);
    }
}

void QEXTTcpTransferThreadPool::addSocket(QEXTTcpServerSocket *socket, QEXTTcpTransferThread *thread)
{
    QEXT_D(QEXTTcpTransferThreadPool);
    if (socket && thread) {
        QMutexLocker mutexLocker(&d->m_threadMutex);
        d->m_socketTransferThreadMap.insert(socket->identityId(), thread);
    }
}

void QEXTTcpTransferThreadPool::removeSocket(QEXTTcpServerSocket *socket, QEXTTcpTransferThread *thread)
{
    QEXT_D(QEXTTcpTransferThreadPool);
    if (socket && thread) {
        QMutexLocker mutexLocker(&d->m_threadMutex);
        d->m_socketTransferThreadMap.remove(socket->identityId());
    }
}
