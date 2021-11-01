#ifndef QTKEVENTADMINBUS_H
#define QTKEVENTADMINBUS_H

#include <QTKPluginFramework/Service/Event/QTKEventAdmin>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEventAdminBus : public QTKEventAdmin
{
public:
    virtual bool createServer(const QString &strCommunicationProtocol, unsigned int iListenPort) = 0;
    virtual void startListen() = 0;
    virtual bool createClient(const QString &strCommunicationProtocol, const QString &strServerHost, unsigned int uiPort) = 0;
};

Q_DECLARE_INTERFACE(QTKEventAdminBus, "org.qtk.service.event.EventAdminBus")

#endif // QTKEVENTADMIN_H
