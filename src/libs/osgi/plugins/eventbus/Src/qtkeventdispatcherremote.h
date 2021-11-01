#ifndef QTKEVENTDISPATCHERREMOTE_H
#define QTKEVENTDISPATCHERREMOTE_H

//include list
#include "qtkeventdefinitions.h"
#include "qtkeventdispatcher.h"

namespace qtkeventbus {

class QTKNetworkConnector;

class QTK_EVENTBUS_EXPORT QTKEventDispatcherRemote : public QTKEventDispatcher
{
    Q_OBJECT

public:
    QTKEventDispatcherRemote();
    ~QTKEventDispatcherRemote();

    void notifyEvent(QTKBusEvent &eventDictionary, QTKEventArgumentsList *pArgList = nullptr,
                     QTKGenericReturnArgument *pReturnArg = nullptr) const;

    void setNetworkConnectorServer(QTKNetworkConnector *pConnector);

    QTKNetworkConnector *networkConnectorServer();

    void setNetworkConnectorClient(QTKNetworkConnector *pConnector);

    QTKNetworkConnector *networkConnectorClient();

protected:
    void initializeGlobalEvents();

private:
    QTKNetworkConnector *m_pNetworkConnectorServer; ///< Class used to manage the communication with the remote event bus.
    QTKNetworkConnector *m_pNetworkConnectorClient; ///< Class used to manage the communication with the remote event bus.
};

} //namespace QTKEventBus

Q_DECLARE_METATYPE(QVariantList);

#endif // QTKEVENTDISPATCHERREMOTE_H
