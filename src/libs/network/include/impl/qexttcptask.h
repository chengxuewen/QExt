#ifndef QEXTTCPTASK_H
#define QEXTTCPTASK_H

#include <qextobject.h>

#include <qextnetworkglobal.h>
#include <qexttcptaskbase.h>

#include <QObject>

class QEXTTcpTaskPrivate;
class QEXT_NETWORK_API QEXTTcpTask : public QEXTTcpTaskBase
{
public:
    QEXTTcpTask(QEXTTcpPacketBase *packet, QEXTTcpTaskPoolBase *taskPool);
    ~QEXTTcpTask();

    bool run() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTask)
};

#endif // QEXTTCPTASK_H
