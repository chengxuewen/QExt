#include <qexttcpthreadpoolbase.h>
#include <qexttcpthreadpoolbase_p.h>
#include <qexttcpserver.h>


QEXTTcpThreadPoolBasePrivate::QEXTTcpThreadPoolBasePrivate(QEXTTcpThreadPoolBase *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTTcpThreadPoolBasePrivate::~QEXTTcpThreadPoolBasePrivate()
{

}



QEXTTcpThreadPoolBase::QEXTTcpThreadPoolBase(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTTcpThreadPoolBasePrivate(this)))
{

}

QEXTTcpThreadPoolBase::QEXTTcpThreadPoolBase(QEXTTcpThreadPoolBasePrivate &dd, QObject *parent)
    : QObject(parent), QEXTObject(dd)
{

}

QEXTTcpThreadPoolBase::~QEXTTcpThreadPoolBase()
{

}

bool QEXTTcpThreadPoolBase::isTcpThreadsEmpty() const
{
    QEXT_DC(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_allThreadsSet.isEmpty();
}

int QEXTTcpThreadPoolBase::tcpThreadsSize() const
{
    QEXT_DC(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_allThreadsSet.size();
}

int QEXTTcpThreadPoolBase::allTcpThreadsCount() const
{
    QEXT_DC(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_allThreadsSet.size();
}

QList<QEXTTcpThreadBase *> QEXTTcpThreadPoolBase::allTcpThreads() const
{
    QEXT_DC(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_allThreadsSet.toList();
}

QList<QEXTTcpThreadBase *> QEXTTcpThreadPoolBase::workingTcpThreads() const
{
    QEXT_DC(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_workingThreadsSet.toList();
}

QList<QEXTTcpThreadBase *> QEXTTcpThreadPoolBase::idleTcpThreads() const
{
    QEXT_DC(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_threadMutex);
    return d->m_idleThreadsQueue.toVector().toList();
}

void QEXTTcpThreadPoolBase::setTcpThreadIdle(QEXTTcpThreadBase *thread)
{
    qDebug() << "QEXTTcpThreadPoolBase::setTcpThreadIdle():" << this->thread();
    QEXT_D(QEXTTcpThreadPoolBase);
    if (thread) {
        QMutexLocker mutexLocker(&d->m_threadMutex);
        d->m_idleThreadsQueue.enqueue(thread);
        d->m_workingThreadsSet.remove(thread);
    }
}

void QEXTTcpThreadPoolBase::setTcpThreadWorking(QEXTTcpThreadBase *thread)
{
    qDebug() << "QEXTTcpThreadPoolBase::setTcpThreadWorking():" << this->thread();
    QEXT_D(QEXTTcpThreadPoolBase);
    if (thread) {
        QMutexLocker mutexLocker(&d->m_threadMutex);
        d->m_workingThreadsSet.insert(thread);
    }
}

void QEXTTcpThreadPoolBase::resizeThreads(int count)
{
    QEXT_D(QEXTTcpThreadPoolBase);
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

void QEXTTcpThreadPoolBase::removeThreads(int count)
{
    QEXT_D(QEXTTcpThreadPoolBase);
    int size = d->m_allThreadsSet.size();
    if (count > 0 && count < size) {
        for (int i = 0; i < count; ++i) {
            this->removeThread();
        }
    } else {
        qCritical() << "QEXTTcpThreadPoolBase::resizeThreads():count must greate 0 and less than threads num " << size;
    }
}

void QEXTTcpThreadPoolBase::addThreads(int count)
{
    QEXT_D(QEXTTcpThreadPoolBase);
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            this->addThread();
        }
    } else {
        qCritical() << "QEXTTcpThreadPoolBase::resizeThreads():count must greate than 0";
    }
}

QEXTTcpPacketParserBase *QEXTTcpThreadPoolBase::packetParser() const
{
    QEXT_DC(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    return d->m_packetParser.data();
}

void QEXTTcpThreadPoolBase::setPacketParser(QEXTTcpPacketParserBase *packetParser)
{
    QEXT_D(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_packetParserMutex);
    if (packetParser && packetParser != d->m_packetParser.data()) {
        d->m_packetParser.reset(packetParser);
        QListIterator<QEXTTcpThreadBase *> iter(this->allTcpThreads());
        while (iter.hasNext()) {
            iter.next()->setPacketParser(packetParser->cloneParser());
        }
    }
}

QEXTTcpTaskPoolBase *QEXTTcpThreadPoolBase::taskPool() const
{
    QEXT_DC(QEXTTcpThreadPoolBase);
    QMutexLocker mutexLocker(&d->m_taskPoolMutex);
    return d->m_taskPool.data();
}
