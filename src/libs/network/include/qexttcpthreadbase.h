#ifndef QEXTTCPTHREADBASE_H
#define QEXTTCPTHREADBASE_H

#include <qextobject.h>

#include <qextnetworkglobal.h>

#include <QSharedPointer>
#include <QObject>

class QEXTTcpTaskPoolBase;
class QEXTTcpThreadPoolBase;
class QEXTTcpPacketParserBase;
class QEXTTcpThreadBasePrivate;
class QEXT_NETWORK_API QEXTTcpThreadBase : public QObject, public QEXTObject
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

    QEXTTcpThreadBase(QEXTTcpThreadBasePrivate &dd, QEXTTcpThreadPoolBase *threadPool);
    ~QEXTTcpThreadBase();

    bool isBusy() const;
    bool isQuit() const;
    double loadAverage(LoadAverageType type = LoadAverage_1Minute) const;

    QEXTTcpPacketParserBase *packetParser() const;
    QEXTTcpTaskPoolBase *taskPool() const;

    virtual void quit() = 0;
    virtual QEXTTcpThreadPoolBase *tcpThreadPool() const = 0;

public Q_SLOTS:
    virtual void setPacketParser(QEXTTcpPacketParserBase *packetParser);
    virtual void setTaskPool(QSharedPointer<QEXTTcpTaskPoolBase> taskPool);

protected Q_SLOTS:
    void loadAverageTimerTimeout();

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpThreadBase)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpThreadBase)
};

#endif // QEXTTCPTHREADBASE_H
