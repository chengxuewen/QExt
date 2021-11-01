#ifndef QTKEVENTBUSMANAGER_H
#define QTKEVENTBUSMANAGER_H

// Includes list
#include "qtkeventdefinitions.h"
#include "qtkeventdispatcherlocal.h"
#include "qtkeventdispatcherremote.h"
#include "qtkbusevent.h"

namespace qtkeventbus {

class QTK_EVENTBUS_EXPORT QTKEventBusManager : public QObject
{
    Q_OBJECT

public:
    static QTKEventBusManager *instance();

    bool addEventProperty(QTKBusEvent &props) const;

    bool removeEventProperty(QTKBusEvent &props) const;
    void removeObserver(const QObject *pObj, const QString strTopic = "", bool bQtDisconnect = true);
    void removeSignal(const QObject *pObj, QString strTopic = "", bool bQtDisconnect = true);

    void notifyEvent(QTKBusEvent &eventDictionary, QTKEventArgumentsList *pArgList = nullptr,
                     QTKGenericReturnArgument *pReturnArg = nullptr) const;
    void notifyEvent(const QString strTopic, QTKEventType eventType = QTKEventTypeLocal,
                     QTKEventArgumentsList *pArgList = nullptr, QTKGenericReturnArgument *pReturnArg = nullptr) const;

    void enableEventLogging(bool bEnable = true);

    void logEventTopic(const QString strTopic);
    void logAllEvents();

    void shutdown();
    void initializeNetworkConnectors();

    bool isLocalSignalPresent(const QString strTopic) const;
    void plugNetworkConnector(const QString &strProtocol, QTKNetworkConnector *pConnector);

    bool createServer(const QString &strCommunicationProtocol, unsigned int uiListenPort);
    void startListen();
    bool createClient(const QString &strCommunicationProtocol, const QString &strServerHost, unsigned int uiPort);

public Q_SLOTS:
    void detachObjectFromBus();

private:
    QTKEventBusManager();
    ~QTKEventBusManager();

    QTKEventDispatcherLocal *m_pLocalDispatcher; ///< Dispatcher class which dispatches events locally to the application.
    QTKEventDispatcherRemote *m_pRemoteDispatcher; ///< Dispatcher class dispatches events remotely to another applications or via network.

    bool m_bEnableEventLogging; ///< Flag to enable/disable logging for event sent.
    QString m_strLogEventTopic; ///< Store the current Event_Id to track through the logger.
    QTKNetworkConnectorHash m_mapNetworkConnector; ///< Hash table used to store the association of network protocols and network connector types.

    bool m_bSkipDetach; ///< lifesafe variable to avoid the detach from eventbus.
};

} // namespace QTKEventBus

#endif // QTKEVENTBUSMANAGER
