#ifndef QTKEATHREADFACTORY_P_H
#define QTKEATHREADFACTORY_P_H

class QTKEAInterruptibleThread;
class QTKEARunnable;

struct QTKEAThreadFactory
{
    virtual ~QTKEAThreadFactory() {}

    virtual QTKEAInterruptibleThread *newThread(QTKEARunnable *pCommand) = 0;
};

#endif // QTKEATHREADFACTORY_P_H
