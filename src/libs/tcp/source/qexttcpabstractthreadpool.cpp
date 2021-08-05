#include <qexttcpabstractthreadpool.h>
#include <qexttcpabstractthreadpool_p.h>
#include <qexttcpserver.h>



QEXTTcpAbstractThreadPoolPrivate::QEXTTcpAbstractThreadPoolPrivate(QEXTTcpAbstractThreadPool *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTTcpAbstractThreadPoolPrivate::~QEXTTcpAbstractThreadPoolPrivate()
{

}



QEXTTcpAbstractThreadPool::QEXTTcpAbstractThreadPool(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTTcpAbstractThreadPoolPrivate(this)))
{

}

QEXTTcpAbstractThreadPool::QEXTTcpAbstractThreadPool(QEXTTcpAbstractThreadPoolPrivate &dd, QObject *parent)
    : QObject(parent), QEXTObject(dd)
{

}

QEXTTcpAbstractThreadPool::~QEXTTcpAbstractThreadPool()
{

}

bool QEXTTcpAbstractThreadPool::isTcpThreadsEmpty() const
{
    QEXT_DC(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_allThreadsSet.isEmpty();
}

int QEXTTcpAbstractThreadPool::tcpThreadsSize() const
{
    QEXT_DC(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_allThreadsSet.size();
}

int QEXTTcpAbstractThreadPool::allTcpThreadsCount() const
{
    QEXT_DC(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_allThreadsSet.size();
}

QList<QEXTTcpAbstractThread *> QEXTTcpAbstractThreadPool::allTcpThreads() const
{
    QEXT_DC(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_allThreadsSet.toList();
}

QList<QEXTTcpAbstractThread *> QEXTTcpAbstractThreadPool::workingTcpThreads() const
{
    QEXT_DC(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_workingThreadsSet.toList();
}

QList<QEXTTcpAbstractThread *> QEXTTcpAbstractThreadPool::idleTcpThreads() const
{
    QEXT_DC(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_idleThreadsQueue.toVector().toList();
}

void QEXTTcpAbstractThreadPool::setTcpThreadIdle(QEXTTcpAbstractThread *thread)
{
    qDebug() << "QEXTTcpThreadPoolBase::setTcpThreadIdle():" << this->thread();
    QEXT_D(QEXTTcpAbstractThreadPool);
    if (thread) {
        QMutexLocker mutexLocker(&d->m_threadMutex);
        d->m_idleThreadsQueue.enqueue(thread);
        d->m_workingThreadsSet.remove(thread);
    }
}

void QEXTTcpAbstractThreadPool::setTcpThreadWorking(QEXTTcpAbstractThread *thread)
{
    qDebug() << "QEXTTcpThreadPoolBase::setTcpThreadWorking():" << this->thread();
    QEXT_D(QEXTTcpAbstractThreadPool);
    if (thread) {
        QMutexLocker mutexLocker(&d->m_threadMutex);
        d->m_workingThreadsSet.insert(thread);
    }
}

void QEXTTcpAbstractThreadPool::resizeThreads(int count)
{
    QEXT_D(QEXTTcpAbstractThreadPool);
    if (count > 0) {
        int size = this->allTcpThreadsCount();
        if (count > size) {
            this->addThreads(count - size);
        } else if (count < size) {
            this->removeThreads(size - count);
        }
    } else {
        qCritical() << "QEXTTcpThreadPoolBase::resizeThreads():count must greate than 0";
    }
}

void QEXTTcpAbstractThreadPool::removeThreads(int count)
{
    QEXT_D(QEXTTcpAbstractThreadPool);
    int size = d->m_allThreadsSet.size();
    if (count > 0 && count < size) {
        for (int i = 0; i < count; ++i) {
            this->removeThread();
        }
    } else {
        qCritical() << "QEXTTcpThreadPoolBase::resizeThreads():count must greate 0 and less than threads num " << size;
    }
}

void QEXTTcpAbstractThreadPool::addThreads(int count)
{
    QEXT_D(QEXTTcpAbstractThreadPool);
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            this->addThread();
        }
    } else {
        qCritical() << "QEXTTcpThreadPoolBase::resizeThreads():count must greate than 0";
    }
}

QEXTTcpAbstractPacketParser *QEXTTcpAbstractThreadPool::packetParser() const
{
    QEXT_DC(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser.data();
}

void QEXTTcpAbstractThreadPool::setPacketParser(QEXTTcpAbstractPacketParser *packetParser)
{
    QEXT_D(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    if (packetParser && packetParser != d->m_packetParser.data()) {
        d->m_packetParser.reset(packetParser);
        QListIterator<QEXTTcpAbstractThread *> iter(this->allTcpThreads());
        while (iter.hasNext()) {
            iter.next()->setPacketParser(packetParser->cloneParser());
        }
    }
}

QEXTTcpAbstractTaskPool *QEXTTcpAbstractThreadPool::taskPool() const
{
    QEXT_DC(QEXTTcpAbstractThreadPool);
    QMutexLocker mutexLocker(&d->m_taskPoolMutex);
    return d->m_taskPool.data();
}
