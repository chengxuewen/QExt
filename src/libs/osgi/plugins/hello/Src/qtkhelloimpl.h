#ifndef QTKHELLOIMPL_H
#define QTKHELLOIMPL_H

#include "qtkhelloservice.h"

#include <QTKPluginFramework/QTKPluginContext>

#include <QObject>
#include <QTimer>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKHelloImpl : public QObject, public QTKHelloService
{
    Q_OBJECT
    Q_INTERFACES(QTKHelloService)

public:
    explicit QTKHelloImpl(QTKPluginContext *pContext);
    ~QTKHelloImpl();

    QString sayHello() override;
};

#endif // QTKHELLOIMPL_H
