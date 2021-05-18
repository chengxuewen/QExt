#ifndef QEXTTCPABSTRACTTHREAD_H
#define QEXTTCPABSTRACTTHREAD_H

#include <qextobject.h>

#include <qexttcpglobal.h>

#include <QSharedPointer>
#include <QObject>



class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractThreadPool;
class QEXTTcpAbstractPacketParser;
class QEXTTcpAbstractThreadPrivate;
class QEXT_TCP_API QEXTTcpAbstractThread : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    enum LoadAverageType {
        LoadAverage_1Minute = 0,
        LoadAverage_5Minute,
        LoadAverage_15Minute,
        LoadAverage_30Minute,
        LoadAverage_1Hour
    };

    QEXTTcpAbstractThread(QEXTTcpAbstractThreadPrivate &dd, QEXTTcpAbstractThreadPool *threadPool);
    ~QEXTTcpAbstractThread();

    bool isBusy() const;
    bool isQuit() const;
    double loadAverage(LoadAverageType type = LoadAverage_1Minute) const;

    QEXTTcpAbstractPacketParser *packetParser() const;
    QEXTTcpAbstractTaskPool *taskPool() const;

    virtual void quit() = 0;
    virtual QEXTTcpAbstractThreadPool *tcpThreadPool() const = 0;

public Q_SLOTS:
    virtual void setPacketParser(QEXTTcpAbstractPacketParser *packetParser);
    virtual void setTaskPool(QSharedPointer<QEXTTcpAbstractTaskPool> taskPool);

protected Q_SLOTS:
    void loadAverageTimerTimeout();

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpAbstractThread)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpAbstractThread)
};



#endif // QEXTTCPABSTRACTTHREAD_H
