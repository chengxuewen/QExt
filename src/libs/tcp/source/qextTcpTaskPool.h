#ifndef _QEXTTCPTASKPOOL_H
#define _QEXTTCPTASKPOOL_H

#include <qextTcpGlobal.h>
#include <qextId.h>

#include <QObject>
#include <QThreadPool>

class QExtTcpPacketDispatcher;
class QExtTcpTask;
class QExtTcpTaskPoolPrivate;
class QEXT_TCP_API QExtTcpTaskPool : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtTcpTaskPool)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpTaskPool)
public:
    QExtTcpTaskPool(QExtTcpPacketDispatcher *dispatcher);
    ~QExtTcpTaskPool();

    bool isWaitingTaskEmpty() const;
    bool isRunningTaskEmpty() const;
    int waitingTaskCount() const;
    int runningTaskCount() const;

    QThreadPool *threadPool() const;
    void enqueueTask(QExtTcpTask *task);

Q_SIGNALS:
    void taskError(const QExtId &id, const QString &error);
    void taskFinished(const QExtId &id);

protected Q_SLOTS:
    void onTaskError(const QString &error);
    void onTaskFinished(quint64 id);

protected:
    QScopedPointer<QExtTcpTaskPoolPrivate> dd_ptr;
};

#endif // _QEXTTCPTASKPOOL_H
