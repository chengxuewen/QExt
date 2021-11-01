#ifndef QTKSUBSCRIBEREVENTHANDLER_H
#define QTKSUBSCRIBEREVENTHANDLER_H

#include <QTKPluginFramework/Service/Event/QTKEventHandler>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKSubscriberEventHandler : public QObject, public QTKEventHandler
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEventHandler)

public:
    void handleEvent(const QTKEvent &event) override;
};

#endif // QTKSUBSCRIBEREVENTHANDLER_H
