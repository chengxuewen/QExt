#include <qexttcptransferthread.h>
#include <qexttcptransferthread_p.h>
#include <qexttcptransferthreadpool.h>
#include <qexttcpserversocket.h>
#include <qexttcptaskbase.h>

#include <QHostAddress>
#include <QDebug>

QMap<int, QString> QEXTTcpTransferThreadPrivate::sm_errorStringMap;

QEXTTcpTransferThreadPrivate::QEXTTcpTransferThreadPrivate(QEXTTcpTransferThread *qq)
    : QEXTTcpThreadBasePrivate(qq)
{

}

QEXTTcpTransferThreadPrivate::~QEXTTcpTransferThreadPrivate()
{

}

void QEXTTcpTransferThreadPrivate::handleSocketConnect(QEXTTcpServerSocket *socket, bool connect)
{
    QEXT_Q(QEXTTcpTransferThread);
    if (connect) {
        QObject::connect(socket, SIGNAL(readyRead()), q, SLOT(readPacket()));
        QObject::connect(socket, SIGNAL(disconnected()), q, SLOT(handleSocketClosed()));
        QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), q, SLOT(handleSocketError(QAbstractSocket::SocketError)));
    } else {
        QObject::disconnect(socket, SIGNAL(readyRead()), q, SLOT(readPacket()));
        QObject::disconnect(socket, SIGNAL(disconnected()), q, SLOT(handleSocketClosed()));
        QObject::disconnect(socket, SIGNAL(error(QAbstractSocket::SocketError)), q, SLOT(handleSocketError(QAbstractSocket::SocketError)));
    }
}



QEXTTcpTransferThread::QEXTTcpTransferThread(QEXTTcpTransferThreadPool *threadPool)
    : QEXTTcpThreadBase(*(new QEXTTcpTransferThreadPrivate(this)), threadPool)
{
}

QEXTTcpTransferThread::~QEXTTcpTransferThread()
{

}

void QEXTTcpTransferThread::quit()
{
    QEXT_D(QEXTTcpTransferThread);
    QWriteLocker writeLocker(&d->m_quitLock);
    if (!d->m_isQuit) {
        QMutexLocker mutexLocker(&d->m_socketMutex);
        QSetIterator<QEXTTcpServerSocket *> iter(d->m_socketSet);
        while (iter.hasNext()) {
            d->handleSocketConnect(iter.next(), false);
        }
        d->m_isQuit = true;
        connect(this, SIGNAL(destroyed(QObject*)), this->thread(), SLOT(deleteLater()));
    }
}

QEXTTcpThreadPoolBase *QEXTTcpTransferThread::tcpThreadPool() const
{
    QEXT_DC(QEXTTcpTransferThread);
    return d->m_threadPool.data();
}

QQueue<QEXTTcpPacketBase *> QEXTTcpTransferThread::allSendPacketsQueue() const
{
    QEXT_DC(QEXTTcpTransferThread);
    QMutexLocker mutexLocker(&d->m_packetMutex);
    return d->m_sendPacketQueue;
}

QSet<QEXTTcpServerSocket *> QEXTTcpTransferThread::allSocketsSet() const
{
    QEXT_DC(QEXTTcpTransferThread);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_socketSet;
}

int QEXTTcpTransferThread::socketCount() const
{
    QEXT_DC(QEXTTcpTransferThread);
    QMutexLocker mutexLocker(&d->m_socketMutex);
    return d->m_socketSet.size();
}

void QEXTTcpTransferThread::incomingConnection(QObject *threadObj, QEXTSocketDescriptor socketDescriptor)
{
    if (this != threadObj) {
        return;
    }

    QEXT_D(QEXTTcpTransferThread);
    QEXTTcpServerSocket *socket = new QEXTTcpServerSocket;
    if (socket) {
        if (socket->setSocketDescriptor(socketDescriptor)) {
            socket->updateIdentityId();
            d->handleSocketConnect(socket, true);
            d->m_socketMutex.lock();
            d->m_socketSet.insert(socket);
            d->m_socketHashMap.insert(socket->identityId(), socket);
            d->m_socketMutex.unlock();
            emit this->socketMessage(socket, tr("Info->socket %1 connected.").arg(socket->identityId().toString()));
            emit this->socketConnected(socket);
            QEXTTcpTransferThreadPool *threadPool = dynamic_cast<QEXTTcpTransferThreadPool *>(d->m_threadPool.data());
            if (threadPool) {
                threadPool->addSocket(socket, this);
            }
        } else {
            socket->deleteLater();
        }
    }
}

void QEXTTcpTransferThread::enqueueSendPacket(QObject *threadObj, QEXTTcpPacketBase *packet)
{
    QEXT_D(QEXTTcpTransferThread);
    if (this == threadObj && !this->isQuit()) {
        d->m_packetMutex.lock();
        d->m_sendPacketQueue.enqueue(packet);
        d->m_packetMutex.unlock();
        QTimer::singleShot(0, this, SLOT(sendPacket()));
    }
}

void QEXTTcpTransferThread::addServerSocket(QObject *threadObj, QEXTTcpServerSocket *socket, const QList<QEXTTcpPacketBase *> &packetList)
{
    if (this != threadObj) {
        return;
    }

    QEXT_D(QEXTTcpTransferThread);
    if (socket) {
        d->handleSocketConnect(socket, true);
        d->m_socketMutex.lock();
        d->m_socketSet.insert(socket);
        d->m_socketHashMap.insert(socket->identityId(), socket);
        d->m_socketMutex.unlock();
        QListIterator<QEXTTcpPacketBase *> iter(packetList);
        while (iter.hasNext()) {
            this->enqueueSendPacket(this, iter.next());
        }
        emit this->socketMessage(socket, tr("Info->socket %1 add in.").arg(socket->identityId().toString()));
    }
}

void QEXTTcpTransferThread::sendPacket()
{
    if (!this->isQuit()) {
        QEXT_D(QEXTTcpTransferThread);
        d->updateRunningFlag(true);
        while (!d->m_sendPacketQueue.isEmpty()) {
            d->m_packetMutex.lock();
            QEXTTcpPacketBase *packet = d->m_sendPacketQueue.dequeue();
            d->m_packetMutex.unlock();
            QEXTTcpServerSocket *socket = d->m_socketHashMap.value(packet->socketId());
            if (socket) {
                qint64 size = d->m_packetParser->writeData(socket, packet);
                if (packet->header()->headerSize() + packet->header()->contentSize() != size) {
                    emit this->transferError(QEXTTcpSocket::TransferError_PacketParserWriteFailed);
                }
            } else {
                emit this->transferError(QEXTTcpSocket::TransferError_SocketNotFound);
            }
            delete packet;
        }
        d->updateRunningFlag(false);
    }
}

void QEXTTcpTransferThread::readPacket()
{
    qDebug() << "QEXTTcpTransferThread::readPacket():" << this->thread();
    if (!this->isQuit()) {
        QEXT_D(QEXTTcpTransferThread);
        d->updateRunningFlag(true);
        QEXTTcpServerSocket *socket = qobject_cast<QEXTTcpServerSocket *>(sender());
        if (socket) {
            d->m_packetParserMutex.lock();
            if (!d->m_packetParser.isNull()) {
                bool success = true;
                QEXTTcpPacketBase *packet = d->m_packetParser->readData(socket, success);
                if (packet) {
                    QMutexLocker mutexLocker(&d->m_taskPoolMutex);
                    if (!d->m_taskPool.isNull()) {
                        d->m_taskPool->enqueuePacket(packet);
                    } else {
                        socket->readAll();
                        emit this->transferError(QEXTTcpSocket::TransferError_TaskPoolNotExist);
                    }
                } else if (!success) {
                    socket->readAll();
                    emit this->transferError(QEXTTcpSocket::TransferError_PacketParserReadFailed);
                }
            } else {
                emit this->transferError(QEXTTcpSocket::TransferError_PacketParserNotExist);
            }
            d->m_packetParserMutex.unlock();
            if (socket->bytesAvailable()) {
                socket->sendReadyRead();
            }
        } else {
            emit this->transferError(QEXTTcpSocket::TransferError_SocketError);
        }
        d->updateRunningFlag(false);
    }
}

void QEXTTcpTransferThread::handleSocketClosed()
{
    QEXT_D(QEXTTcpTransferThread);
    QEXTTcpServerSocket *socket = qobject_cast<QEXTTcpServerSocket *>(sender());
    if (socket) {
        socket->abort();
        d->handleSocketConnect(socket, false);
        d->m_socketMutex.lock();
        d->m_socketSet.remove(socket);
        d->m_socketHashMap.remove(socket->identityId());
        d->m_socketMutex.unlock();
        emit this->socketMessage(socket, tr("Info->Socket %1 closed.").arg(socket->identityId().toString()));
        emit this->socketDisconnected(socket);
        QEXTTcpTransferThreadPool *threadPool = dynamic_cast<QEXTTcpTransferThreadPool *>(d->m_threadPool.data());
        if (threadPool) {
            threadPool->removeSocket(socket, this);
        }
    }
}

void QEXTTcpTransferThread::handleSocketError(QAbstractSocket::SocketError socketError)
{
    QEXT_D(QEXTTcpTransferThread);
    QEXTTcpServerSocket *socket = qobject_cast<QEXTTcpServerSocket*>(sender());
    if (socket) {
        d->handleSocketConnect(socket, false);
        d->m_socketMutex.lock();
        d->m_socketSet.remove(socket);
        d->m_socketHashMap.remove(socket->identityId());
        d->m_socketMutex.unlock();
        emit this->socketError(socket, socketError);
        emit this->socketMessage(socket, tr("Info->Socket %1 error for %2, closed.")
                                 .arg(socket->identityId().toString()).arg(socket->errorString()));
    }
}
