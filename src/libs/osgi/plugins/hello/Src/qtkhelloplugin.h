#ifndef QTKHELLOPLUGIN_H
#define QTKHELLOPLUGIN_H

#include "qtkhelloservice.h"

#include <QTKPluginFramework/QTKPluginActivator>

#include <QObject>
#include <QScopedPointer>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKHelloPlugin : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKHelloService")

public:
    void start(QTKPluginContext *pContext) Q_DECL_OVERRIDE;
    void stop(QTKPluginContext *pContext) Q_DECL_OVERRIDE;

private:
    QScopedPointer<QTKHelloService> m_service;
};

#endif // QTKHELLOPLUGIN_H
