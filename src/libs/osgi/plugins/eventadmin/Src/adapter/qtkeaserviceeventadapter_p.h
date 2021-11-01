#ifndef QTKEASERVICEEVENTADAPTER_P_H
#define QTKEASERVICEEVENTADAPTER_P_H

#include "qtkeaabstractadapter_p.h"

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEAServiceEventAdapter : public QObject, public QTKEAAbstractAdapter
{
    Q_OBJECT

public:
    /**
     * @brief QTKEAServiceEventAdapter
     * This will register the adapter with the given context as a <tt>ServiceListener</tt>
     * and subsequently, will post received events via the given EventAdmin.
     * @param pContext The plugin context with which to register as a listener.
     * @param pAdmin The <tt>QTKEventAdmin</tt> to use for posting events.
     */
    QTKEAServiceEventAdapter(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext *pContext, QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEventAdmin *pAdmin);

    void destroy(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginContext *pContext);

public Q_SLOTS:
    void serviceChanged(const QTKServiceEvent &event);
};

#endif // QTKEASERVICEEVENTADAPTER_P_H
