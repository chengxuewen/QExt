#ifndef QTKEVENTSUBSCRIBERPLUGIN_H
#define QTKEVENTSUBSCRIBERPLUGIN_H

#include "qtksubscribereventhandler.h"

#include <QTKPluginFramework/QTKPluginActivator>
#include <QTKPluginFramework/QTKPluginContext>

#include <QObject>
#include <QScopedPointer>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEventSubscriberPlugin : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKEventSubscriberPlugin")

public:
    void start(QTKPluginContext *pContext) Q_DECL_OVERRIDE;
    void stop(QTKPluginContext *pContext) Q_DECL_OVERRIDE;

private:
    QTKSubscriberEventHandler *m_pEventHandler;
};

#endif // QTKEVENTSUBSCRIBERPLUGIN_H
