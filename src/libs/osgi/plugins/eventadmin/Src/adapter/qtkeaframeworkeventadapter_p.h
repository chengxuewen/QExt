#ifndef QTKEAFRAMEWORKEVENTADAPTER_P_H
#define QTKEAFRAMEWORKEVENTADAPTER_P_H

#include "qtkeaabstractadapter_p.h"

#include <QTKPluginFramework/QTKPluginFrameworkEvent>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEAFrameworkEventAdapter : public QObject, public QTKEAAbstractAdapter
{
    Q_OBJECT

public:
    QTKEAFrameworkEventAdapter(QTKPluginContext *pContext, QTKEventAdmin *pAdmin);

    void destroy(QTKPluginContext *pContext);

public Q_SLOTS:
    void frameworkEvent(const QTKPluginFrameworkEvent &event);
};

#endif // QTKEAFRAMEWORKEVENTADAPTER_P_H
