#ifndef QTKEASLOTHANDLER_P_H
#define QTKEASLOTHANDLER_P_H

#include <QTKPluginFramework/QTKServiceRegistration>
#include <QTKPluginFramework/Service/Event/QTKEventHandler>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEASlotHandler : public QObject, public QTKEventHandler
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKEventHandler)

public:
    void updateProperties(const QTKDictionary &properties);

    void handleEvent(const QTKEvent &event);

    QTKServiceRegistration m_serviceReg;

Q_SIGNALS:
    void eventOccured(const QTKEvent &event);
};

#endif // QTKEASLOTHANDLER_P_H
