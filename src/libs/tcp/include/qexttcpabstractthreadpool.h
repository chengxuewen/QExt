#ifndef QEXTTCPABSTRACTTHREADPOOL_H
#define QEXTTCPABSTRACTTHREADPOOL_H

#include <qextobject.h>

#include <qexttcpglobal.h>
#include <qexttcpabstractthread.h>

#include <QSharedPointer>
#include <QObject>



class QEXTTcpServer;
class QEXTTcpAbstractPacketParser;
class QEXTTcpAbstractThreadPoolPrivate;
class QEXT_TCP_API QEXTTcpAbstractThreadPool : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpAbstractThreadPool(QObject *parent = QEXT_NULLPTR);
    QEXTTcpAbstractThreadPool(QEXTTcpAbstractThreadPoolPrivate &dd, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpAbstractThreadPool();

    virtual bool isTcpThreadsEmpty() const;
    virtual int tcpThreadsSize() const;

    virtual int allTcpThreadsCount() const;
    virtual QList<QEXTTcpAbstractThread *> allTcpThreads() const;
    virtual QList<QEXTTcpAbstractThread *> workingTcpThreads() const;
    virtual QList<QEXTTcpAbstractThread *> idleTcpThreads() const;

    virtual void setTcpThreadIdle(QEXTTcpAbstractThread *thread);
    virtual void setTcpThreadWorking(QEXTTcpAbstractThread *thread);

    virtual void removeThread() = 0;
    virtual void addThread() = 0;

    void resizeThreads(int count);
    void removeThreads(int count);
    void addThreads(int count);

    QEXTTcpAbstractPacketParser *packetParser() const;
    virtual void setPacketParser(QEXTTcpAbstractPacketParser *packetParser);

    QEXTTcpAbstractTaskPool *taskPool() const;
    virtual void setTaskPool(QSharedPointer<QEXTTcpAbstractTaskPool> taskPool) = 0;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpAbstractThreadPool)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpAbstractThreadPool)
};



#endif // QEXTTCPABSTRACTTHREADPOOL_H
