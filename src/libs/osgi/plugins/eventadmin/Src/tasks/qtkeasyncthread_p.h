#ifndef QTKEASYNCTHREAD_P_H
#define QTKEASYNCTHREAD_P_H

#include "../dispatch/qtkeainterruptiblethread_p.h"
#include "../util/qtkearendezvous_p.h"

#include <QThread>
#include <QAtomicPointer>
#include <QAtomicInt>

class QTKEASyncThread : public QTKEAInterruptibleThread
{
    Q_OBJECT

public:
    QTKEASyncThread(QTKEARunnable *pTarget, QObject *pParent = nullptr);
};

#endif // QTKEASYNCTHREAD_P_H
