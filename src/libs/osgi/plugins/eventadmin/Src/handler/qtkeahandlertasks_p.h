#ifndef QTKEAHANDLERTASKS_P_H
#define QTKEAHANDLERTASKS_P_H

#include <QTKPluginFramework/Service/Event/QTKEvent>

#include <QList>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

template<class HandlerTasks> class QTKEAHandlerTask;

template<class Impl>
struct QTKEAHandlerTasks
{
    virtual ~QTKEAHandlerTasks() {}

    QList<QTKEAHandlerTask<Impl> > createHandlerTasks(const QTKEvent &event) {
        return static_cast<Impl*>(this)->createHandlerTasks(event);
    }
};

#endif // QTKEAHANDLERTASKS_P_H
