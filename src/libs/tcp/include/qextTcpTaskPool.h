#ifndef _QEXTTCPTASKPOOL_H
#define _QEXTTCPTASKPOOL_H

#include <qextTcpGlobal.h>
#include <qextId.h>

#include <QObject>
#include <QThreadPool>

class QEXTTcpPacketDispatcher;
class QEXTTcpTask;
class QEXTTcpTaskPoolPrivate;
class QEXT_TCP_API QEXTTcpTaskPool : public QObject
{
    Q_OBJECT
public:
    QEXTTcpTaskPool(QEXTTcpPacketDispatcher *dispatcher);
    ~QEXTTcpTaskPool();

    bool isWaitingTaskEmpty() const;
    bool isRunningTaskEmpty() const;
    int waitingTaskCount() const;
    int runningTaskCount() const;

    QThreadPool *threadPool() const;
    void enqueueTask(QEXTTcpTask *task);

Q_SIGNALS:
    void taskError(const QEXTId &id, const QString &error);
    void taskFinished(const QEXTId &id);

protected Q_SLOTS:
    void onTaskError(const QString &error);
    void onTaskFinished(quint64 id);

protected:
    QScopedPointer<QEXTTcpTaskPoolPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QEXTTcpTaskPool)
    QEXT_DECL_DISABLE_COPY(QEXTTcpTaskPool)
};

#endif // _QEXTTCPTASKPOOL_H
