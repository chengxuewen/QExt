#ifndef QEXTTCPTHREADPOOLBASE_H
#define QEXTTCPTHREADPOOLBASE_H

#include <qextobject.h>

#include <qextnetworkglobal.h>
#include <qexttcpthreadbase.h>

#include <QSharedPointer>
#include <QObject>

class QEXTTcpServer;
class QEXTTcpPacketParserBase;
class QEXTTcpThreadPoolBasePrivate;
class QEXT_NETWORK_API QEXTTcpThreadPoolBase : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpThreadPoolBase(QObject *parent = QEXT_NULLPTR);
    QEXTTcpThreadPoolBase(QEXTTcpThreadPoolBasePrivate &dd, QObject *parent = QEXT_NULLPTR);
    ~QEXTTcpThreadPoolBase();

    virtual bool isTcpThreadsEmpty() const;
    virtual int tcpThreadsSize() const;

    virtual int allTcpThreadsCount() const;
    virtual QList<QEXTTcpThreadBase *> allTcpThreads() const;
    virtual QList<QEXTTcpThreadBase *> workingTcpThreads() const;
    virtual QList<QEXTTcpThreadBase *> idleTcpThreads() const;

    virtual void setTcpThreadIdle(QEXTTcpThreadBase *thread);
    virtual void setTcpThreadWorking(QEXTTcpThreadBase *thread);

    virtual void removeThread() = 0;
    virtual void addThread() = 0;

    void resizeThreads(int count);
    void removeThreads(int count);
    void addThreads(int count);

    QEXTTcpPacketParserBase *packetParser() const;
    virtual void setPacketParser(QEXTTcpPacketParserBase *packetParser);

    QEXTTcpTaskPoolBase *taskPool() const;
    virtual void setTaskPool(QSharedPointer<QEXTTcpTaskPoolBase> taskPool) = 0;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpThreadPoolBase)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpThreadPoolBase)
};

#endif // QEXTTCPTHREADPOOLBASE_H
