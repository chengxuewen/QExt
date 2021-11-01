#ifndef QTKEAPLUGINEVENTADAPTER_P_H
#define QTKEAPLUGINEVENTADAPTER_P_H

#include "qtkeaabstractadapter_p.h"

#include <QTKPluginFramework/QTKPluginEvent>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

/**
 * @brief The QTKEAPluginEventAdapter class
 * This class registers itself as a listener for plugin events and posts them via
 * the QTKEventAdmin as specified in 113.6.4 OSGi R4 compendium.
 */
class QTKEAPluginEventAdapter : public QObject, public QTKEAAbstractAdapter
{
    Q_OBJECT

public:
    QTKEAPluginEventAdapter(QTKPluginContext *pContext, QTKEventAdmin *pAdmin);

    void destroy(QTKPluginContext *pContext);

public Q_SLOTS:
    void pluginChanged(const QTKPluginEvent &event);
};

#endif // QTKEAPLUGINEVENTADAPTER_P_H
