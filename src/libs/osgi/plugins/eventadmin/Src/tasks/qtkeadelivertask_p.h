#ifndef QTKEADELIVERTASK_P_H
#define QTKEADELIVERTASK_P_H

#include "qtkeahandlertask_p.h"

#include <QList>

template<class Impl, class HandlerTask>
struct QTKEADeliverTask
{
    virtual ~QTKEADeliverTask() {}

    void execute(const QList<HandlerTask> &listHandlerTasks) {
        static_cast<Impl*>(this)->execute(listHandlerTasks);
    }
};

#endif // QTKEADELIVERTASK_P_H
