#ifndef QEXTTCPTASK_H
#define QEXTTCPTASK_H

#include <qextobject.h>

#include <qexttcpglobal.h>
#include <qexttcpabstracttask.h>

#include <QObject>



class QEXTTcpTaskPrivate;
class QEXT_TCP_API QEXTTcpTask : public QEXTTcpAbstractTask
{
public:
    QEXTTcpTask(QEXTTcpAbstractPacket *packet, QEXTTcpAbstractTaskPool *taskPool);
    ~QEXTTcpTask();

    QEXTTcpAbstractPacket *packet() const;

    bool run() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTask)
};



#endif // QEXTTCPTASK_H
