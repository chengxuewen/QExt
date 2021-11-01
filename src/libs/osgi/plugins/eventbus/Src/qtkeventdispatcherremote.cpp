#include "qtkeventdispatcherremote.h"
#include "qtkbusevent.h"
#include "qtknetworkconnector.h"

using namespace qtkeventbus;

QTKEventDispatcherRemote::QTKEventDispatcherRemote()
    : QTKEventDispatcher(),
      m_pNetworkConnectorServer(nullptr),
      m_pNetworkConnectorClient(nullptr)
{
    this->initializeGlobalEvents();
}

QTKEventDispatcherRemote::~QTKEventDispatcherRemote()
{
    if(m_pNetworkConnectorServer) {
        delete m_pNetworkConnectorServer;
    }
    m_pNetworkConnectorServer = nullptr;
    if(m_pNetworkConnectorClient) {
        delete m_pNetworkConnectorClient;
    }
    m_pNetworkConnectorClient = nullptr;
}

QTKNetworkConnector *QTKEventDispatcherRemote::networkConnectorServer()
{
    return m_pNetworkConnectorServer;
}

QTKNetworkConnector *QTKEventDispatcherRemote::networkConnectorClient()
{
    return m_pNetworkConnectorClient;
}

void QTKEventDispatcherRemote::initializeGlobalEvents()
{
    QTKBusEvent *pRroperties = new QTKBusEvent("QTK/remote/eventBus/globalUpdate", QTKEventTypeRemote,
                                               QTKSignatureTypeSignal, this, "notifyDefaultEvent()");
    this->registerSignal(*pRroperties);

    // events like remoteCommunicationDone or failed represents th bridge events between a remote communication
    // and the possibility to call local slots. The notifyEvent local sends events inside the local objects registered as observers
    // through the event bus manager while the remote notification (QTKEventTypeRemote) uses the network connector.
}

void QTKEventDispatcherRemote::setNetworkConnectorServer(QTKNetworkConnector *pConnector)
{
    if(m_pNetworkConnectorServer == nullptr) {
        m_pNetworkConnectorServer = pConnector->clone();
        m_pNetworkConnectorServer->initializeForEventBus();
    } else {
        if(m_pNetworkConnectorServer->protocol() != pConnector->protocol()) {
            delete m_pNetworkConnectorServer; //if there will be multiprotocol , here there will be a problem for thread app
            m_pNetworkConnectorServer = pConnector->clone();
            m_pNetworkConnectorServer->initializeForEventBus();
        }
    }
}

void QTKEventDispatcherRemote::setNetworkConnectorClient(QTKNetworkConnector *pConnector)
{
    if(m_pNetworkConnectorClient == nullptr) {
        m_pNetworkConnectorClient = pConnector->clone();
        m_pNetworkConnectorClient->initializeForEventBus();
    } else {
        if(m_pNetworkConnectorClient->protocol() != pConnector->protocol()) {
            delete m_pNetworkConnectorClient; //if there will be multiprotocol , here there will be a problem for thread app
            m_pNetworkConnectorClient = pConnector->clone();
            m_pNetworkConnectorClient->initializeForEventBus();
        }
    }
}

void QTKEventDispatcherRemote::notifyEvent(QTKBusEvent &eventDictionary, QTKEventArgumentsList *pArgList,
                                           QTKGenericReturnArgument *pReturnArg) const
{
    Q_UNUSED(pReturnArg);

    // Call the notifyEventRemote converting the arguments...
    m_pNetworkConnectorClient->send(eventDictionary[TOPIC].toString(), pArgList);
}
