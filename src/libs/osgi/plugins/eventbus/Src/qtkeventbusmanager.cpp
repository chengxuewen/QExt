#include "qtkeventbusmanager.h"
#include "qtktopicregistry.h"
#include "qtknetworkconnector.h"
#include "qtknetworkconnectorqtsoap.h"

using namespace qtkeventbus;

QTKEventBusManager::QTKEventBusManager()
    : m_bEnableEventLogging(false),
      m_strLogEventTopic("*"),
      m_bSkipDetach(false)
{
    // Create local event dispatcher.
    m_pLocalDispatcher = new QTKEventDispatcherLocal();
    m_pLocalDispatcher->setObjectName("Local Event Dispatcher");

    // Create the remote event dispatcher.
    m_pRemoteDispatcher = new QTKEventDispatcherRemote();
    m_pRemoteDispatcher->setObjectName("Remote Event Dispatcher");
}

QTKEventBusManager::~QTKEventBusManager()
{
    QTKNetworkConnectorHash::iterator iter = m_mapNetworkConnector.begin();
    while(iter != m_mapNetworkConnector.end()) {
        delete iter.value();
        ++iter;
    }
    m_mapNetworkConnector.clear();

    //disconnet detachFromEventBus
    m_bSkipDetach = true;

    if(m_pLocalDispatcher) {
        m_pLocalDispatcher->resetHashes();
        delete m_pLocalDispatcher;
    }
    if(m_pRemoteDispatcher) {
        m_pRemoteDispatcher->resetHashes();
        delete m_pRemoteDispatcher;
    }
}

void QTKEventBusManager::plugNetworkConnector(const QString &strProtocol, QTKNetworkConnector *pConnector)
{
    m_mapNetworkConnector.insert(strProtocol, pConnector);
}

bool QTKEventBusManager::isLocalSignalPresent(const QString strTopic) const
{
    return m_pLocalDispatcher->isLocalSignalPresent(strTopic);
}

QTKEventBusManager* QTKEventBusManager::instance()
{
    static QTKEventBusManager instanceEventBus;
    return &instanceEventBus;
}

void QTKEventBusManager::shutdown()
{
    qtkeventbus::QTKTopicRegistry::instance()->shutdown();
}

void QTKEventBusManager::initializeNetworkConnectors()
{
    plugNetworkConnector("SOAP", new QTKNetworkConnectorQtSoap());
}

bool QTKEventBusManager::addEventProperty(QTKBusEvent &props) const
{
    bool bResult = false;
    QString strTopic = props[TOPIC].toString();
    QObject *pObj = props[OBJECT].value<QObject*>();

    if(props[TYPE].toInt() == QTKEventTypeLocal) {
        // Local event dispatching.
        if(props[SIGTYPE].toInt() == QTKSignatureTypeCallback) {
            bResult = m_pLocalDispatcher->addObserver(props);
        } else {
            //Add topic to the QTKTopicRegistry
            bResult = qtkeventbus::QTKTopicRegistry::instance()->registerTopic(strTopic, pObj);
            if(!bResult) {
                return bResult;
            }
            bResult = m_pLocalDispatcher->registerSignal(props);
        }
    } else {
        // Remote event dispatching.
        if(props[SIGTYPE].toInt() == QTKSignatureTypeCallback) {
            bResult = m_pRemoteDispatcher->addObserver(props);
        } else {
            //Add topic to the QTKTopicRegistry
            bResult = qtkeventbus::QTKTopicRegistry::instance()->registerTopic(strTopic, pObj);
            if(!bResult) {
                return bResult;
            }
            bResult = m_pRemoteDispatcher->registerSignal(props);
        }
    }

    bResult = connect(pObj, SIGNAL(destroyed()), this, SLOT(detachObjectFromBus()));
    return bResult;
}

void QTKEventBusManager::detachObjectFromBus()
{
    if(m_bSkipDetach) {
        return;
    }

    QObject *pObj = QObject::sender();
    this->removeObserver(pObj, "", false);
    removeSignal(pObj, "", false);
}

void QTKEventBusManager::removeObserver(const QObject *pObj, const QString strTopic, bool bQtDisconnect)
{
    if(pObj == nullptr) {
        return;
    }
    m_pLocalDispatcher->removeObserver(pObj, strTopic, bQtDisconnect);
    m_pRemoteDispatcher->removeObserver(pObj, strTopic, bQtDisconnect);
}

void QTKEventBusManager::removeSignal(const QObject *pObj, QString strTopic, bool bQtDisconnect)
{
    if(pObj == nullptr) {
        return;
    }
    //remove topic from the QTKTopicRegistry
    bool bResult = qtkeventbus::QTKTopicRegistry::instance()->unregisterTopic(strTopic);
    if(bResult) {
        return;
    }

    m_pLocalDispatcher->removeSignal(pObj, strTopic, bQtDisconnect);
    m_pRemoteDispatcher->removeSignal(pObj, strTopic, bQtDisconnect);
}

bool QTKEventBusManager::removeEventProperty(QTKBusEvent &props) const
{
    if(props.eventType() == QTKEventTypeLocal) {
        // Local event dispatching.
        if(props[SIGTYPE].toInt() == QTKSignatureTypeCallback) {
            return m_pLocalDispatcher->removeObserver(props);
        } else {
            return m_pLocalDispatcher->removeSignal(props);
        }
    } else {
        // Remote event dispatching.
        if(props[SIGTYPE].toInt() == QTKSignatureTypeCallback) {
            return m_pRemoteDispatcher->removeObserver(props);
        } else {
            return m_pRemoteDispatcher->removeSignal(props);
        }
    }
    return false;
}

void QTKEventBusManager::notifyEvent(const QString strTopic, QTKEventType eventType,
                                     QTKEventArgumentsList *pArgList, QTKGenericReturnArgument *pReturnArg) const
{
    if(m_bEnableEventLogging) {
        if(m_strLogEventTopic == "*" || m_strLogEventTopic == strTopic) {
            qDebug() << tr("Event notification for TOPIC: %1").arg(strTopic);
        }
    }

    //event dispatched in local channel
    QTKBusEvent *pEventDic = new QTKBusEvent(strTopic, eventType, 0, nullptr, "");
    /*(*event_dic)[TOPIC] = topic;
    (*event_dic)[TYPE] = static_cast<int>(ev_type);*/
    this->notifyEvent(*pEventDic, pArgList, pReturnArg);
    delete pEventDic;
}

void QTKEventBusManager::notifyEvent(QTKBusEvent &eventDictionary, QTKEventArgumentsList *pArgList,
                                     QTKGenericReturnArgument *pReturnArg) const
{
    //event dispatched in remote channel
    if(eventDictionary[TYPE].toInt() == QTKEventTypeLocal) {
        m_pLocalDispatcher->notifyEvent(eventDictionary, pArgList, pReturnArg);
    } else {
        m_pRemoteDispatcher->notifyEvent(eventDictionary, pArgList);
    }
}

void QTKEventBusManager::enableEventLogging(bool bEnable)
{
    m_bEnableEventLogging = bEnable;
}

void QTKEventBusManager::logEventTopic(const QString strTopic)
{
    m_strLogEventTopic = strTopic;
}

void QTKEventBusManager::logAllEvents()
{
    m_strLogEventTopic = "*";
}

bool QTKEventBusManager::createServer(const QString &strCommunicationProtocol, unsigned int uiListenPort)
{
    if(m_mapNetworkConnector.count() == 0) {
        initializeNetworkConnectors();
    }

    bool bRes = m_mapNetworkConnector.contains(strCommunicationProtocol);
    if(bRes) {
        QTKNetworkConnector *pConnector = m_mapNetworkConnector.value(strCommunicationProtocol);
        m_pRemoteDispatcher->setNetworkConnectorServer(pConnector);
        //QTKNetworkConnector *connector = m_RemoteDispatcher->networkConnectorServer();
        bRes = (pConnector != nullptr);
        if(bRes) {
            m_pRemoteDispatcher->networkConnectorServer()->createServer(uiListenPort);
        }
    }
    return bRes;
}

void QTKEventBusManager::startListen()
{
    QTKNetworkConnector *pConnector = m_pRemoteDispatcher->networkConnectorServer();
    if(pConnector) {
        pConnector->startListen();
    } else {
        qWarning("%s", tr("Server can not start. Create it first, then call startListen again!!").toLatin1().data());
    }
}

bool QTKEventBusManager::createClient(const QString &strCommunicationProtocol, const QString &strServerHost, unsigned int uiPort)
{
    if(m_mapNetworkConnector.count() == 0) {
        initializeNetworkConnectors();
    }

    bool bRes = m_mapNetworkConnector.contains(strCommunicationProtocol);
    if(bRes) {
        m_pRemoteDispatcher->setNetworkConnectorClient(m_mapNetworkConnector.value(strCommunicationProtocol));
        QTKNetworkConnector *pConnector = m_pRemoteDispatcher->networkConnectorClient();
        bRes = (pConnector != nullptr);
        if(bRes) {
            m_pRemoteDispatcher->networkConnectorClient()->createClient(strServerHost, uiPort);
        }
    }
    return bRes;
}
