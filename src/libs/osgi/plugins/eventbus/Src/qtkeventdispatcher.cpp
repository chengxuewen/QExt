#include "qtkeventdispatcher.h"
#include "qtkbusevent.h"

#define CALLBACK_SIGNATURE "1"
#define SIGNAL_SIGNATURE   "2"

using namespace qtkeventbus;

QTKEventDispatcher::QTKEventDispatcher() {

}

QTKEventDispatcher::~QTKEventDispatcher() {

}

bool QTKEventDispatcher::isLocalSignalPresent(const QString strTopic) const
{
    return m_signalsHash.values(strTopic).size() != 0;
}

void QTKEventDispatcher::resetHashes()
{
    // delete all lists present into the hash.
    QHash<QString, QTKBusEvent *>::iterator iter;
    for (iter = m_callbacksHash.begin(); iter != m_callbacksHash.end(); ++iter) {
        delete iter.value();
    }
    m_callbacksHash.clear();

    for (iter = m_signalsHash.begin(); iter != m_signalsHash.end(); ++iter) {
        delete iter.value();
    }
    m_signalsHash.clear();
}

void QTKEventDispatcher::initializeGlobalEvents()
{
    QTKBusEvent *pRemoteDone = new QTKBusEvent("qtk/local/eventBus/remoteCommunicationDone",
                                               QTKEventTypeLocal, QTKSignatureTypeSignal,
                                               this, "remoteCommunicationDone()");
    this->registerSignal(*pRemoteDone);

    QTKBusEvent *pRemoteFailed = new QTKBusEvent("qtk/local/eventBus/remoteCommunicationFailed",
                                                 QTKEventTypeLocal, QTKSignatureTypeSignal,
                                                 this, "remoteCommunicationFailed()");
    this->registerSignal(*pRemoteFailed);
}

bool QTKEventDispatcher::isSignaturePresent(QTKBusEvent &props) const
{
    QString strTopic = props[TOPIC].toString();
    QTKEventItemListType itemEventPropList;
    if(props[SIGTYPE].toInt() == QTKSignatureTypeCallback) {
        itemEventPropList = m_callbacksHash.values(strTopic);
    } else {
        itemEventPropList = m_signalsHash.values(strTopic);
    }

    QObject *pObjParameter = props[OBJECT].value<QObject *>();
    foreach(QTKBusEvent *pItemEventProp, itemEventPropList) {
        QObject *pObjInList = (*pItemEventProp)[OBJECT].value<QObject *>();
        if(pObjInList == pObjParameter && (*pItemEventProp)[SIGNATURE].toString() == props[SIGNATURE].toString()) {
            return true;
        }
    }
    return false;
}

bool QTKEventDispatcher::disconnectSignal(QTKBusEvent &props)
{
    QObject *pObjSignal = props[OBJECT].value<QObject*>();
    QString strSig = props[SIGNATURE].toString();
    QString strEventSig = SIGNAL_SIGNATURE;
    strEventSig.append(strSig);
    bool bResult = pObjSignal->disconnect(pObjSignal, strEventSig.toLatin1(), 0, 0);
    return bResult;
}

bool QTKEventDispatcher::disconnectCallback(QTKBusEvent &props)
{
    //need to disconnect observer from the signal
    QString strObserverSig = CALLBACK_SIGNATURE;
    strObserverSig.append(props[SIGNATURE].toString());

    QTKBusEvent *pItemSignal = m_signalsHash.value(props[TOPIC].toString());
    QString strEventSig = SIGNAL_SIGNATURE;
    strEventSig.append((*pItemSignal)[SIGNATURE].toString());

    QObject *pObjSignal = (*pItemSignal)[OBJECT].value<QObject *>();
    QObject *pObjSlot = props[OBJECT].value<QObject *>();

    return disconnect(pObjSignal, strEventSig.toLatin1(), pObjSlot, strObserverSig.toLatin1());
}

bool QTKEventDispatcher::removeEventItem(QTKBusEvent &props) {
    bool bIsDisconnected = false;
    bool bIsPresent = isSignaturePresent(props);
    if(bIsPresent == true) {
        //QTKEventItemListType itemEventPropList;
        if(props[SIGTYPE].toInt() == QTKSignatureTypeCallback) {
            bIsDisconnected = this->disconnectCallback(props);
            //iterator for erasing hash entry
            QTKEventsHashType::iterator iter = m_callbacksHash.find(props[TOPIC].toString());
            while (iter != m_callbacksHash.end() && iter.key() == props[TOPIC]) {
                QObject *pObj = (*(iter.value()))[OBJECT].value<QObject *>();
                QObject *pObjCheck = props[OBJECT].value<QObject *>();
                if (pObj == pObjCheck && (*(iter.value()))[SIGNATURE].toString() == props[SIGNATURE].toString()) {
                    delete iter.value();
                    iter = m_callbacksHash.erase(iter);
                } else {
                    ++iter;
                }
            }
        } else {
            //itemEventPropList = m_SignalsHash.values();
            bIsDisconnected = this->disconnectSignal(props);
            QTKEventsHashType::iterator iter = m_callbacksHash.find(props[TOPIC].toString());
            while (iter != m_callbacksHash.end() && iter.key() == props[TOPIC].toString()) {
                delete iter.value();
                iter++;
            }
            iter = m_signalsHash.find(props[TOPIC].toString());
            while (iter != m_signalsHash.end() && iter.key() == props[TOPIC].toString()) {
                delete iter.value();
                iter++;
            }
            m_signalsHash.remove(props[TOPIC].toString()); //in signal hash the id is unique
            m_callbacksHash.remove(props[TOPIC].toString()); //remove also all the id associated in callback
        }
    }
    return bIsDisconnected;
}

bool QTKEventDispatcher::addObserver(QTKBusEvent &props)
{
    QString strTopic = props[TOPIC].toString();
    // check if the object has been already registered with the same signature to avoid duplicates.
    if(m_callbacksHash.contains(strTopic) && this->isSignaturePresent(props) == true) {
        return false;
    }

    QVariant sigVariant = props[SIGNATURE];
    QString strSig = sigVariant.toString();

    QObject *pObjSlot = props[OBJECT].value<QObject *>();

    if(strSig.length() > 0 && pObjSlot != nullptr) {
        QTKBusEvent *pItemEventProp;
        pItemEventProp = m_signalsHash.value(strTopic);
        if(pItemEventProp == nullptr) {
            qDebug() << tr("Signal not present for topic %1, create only the entry in CallbacksHash").arg(strTopic);
            QTKBusEvent *pDict = const_cast<QTKBusEvent *>(&props);
            m_callbacksHash.insertMulti(strTopic, pDict);
            return true;
        }

        QString strObserverSig = CALLBACK_SIGNATURE;
        strObserverSig.append(props[SIGNATURE].toString());
        
        QString strEventSig = SIGNAL_SIGNATURE;
        strEventSig.append((*pItemEventProp)[SIGNATURE].toString());
        
        // Add the new observer to the Hash.
        QTKBusEvent *pDict = const_cast<QTKBusEvent *>(&props);
        m_callbacksHash.insertMulti(strTopic, pDict);
        QObject *pObjSignal = (*pItemEventProp)[OBJECT].value<QObject *>();

        return connect(pObjSignal, strEventSig.toLatin1(), pObjSlot, strObserverSig.toLatin1());
    }
    
    qDebug() << tr("Signal not valid for topic: %1").arg(strTopic);
    QString strObjValid = pObjSlot ? "YES":"NO";
    qDebug() << tr("Object valid Address: %1").arg(strObjValid);
    qDebug() << tr("Signature: %1").arg(strSig);
    return false;
}

bool QTKEventDispatcher::removeObserver(const QObject *pObj, const QString strTopic, bool bQtDisconnect)
{
    if(pObj == nullptr) {
        return false;
    }
    return removeFromHash(&m_callbacksHash, pObj, strTopic, bQtDisconnect);
}

bool QTKEventDispatcher::removeSignal(const QObject *pObj, const QString strTopic, bool bQtDisconnect)
{
    if(pObj == nullptr) {
        return false;
    }
    return removeFromHash(&m_signalsHash, pObj, strTopic, bQtDisconnect);
}

bool QTKEventDispatcher::removeFromHash(QTKEventsHashType *pHash, const QObject *pObj,
                                        const QString strTopic, bool bQtDisconnect)
{
    bool bDisconnectItem = true;
    if(strTopic.length() > 0 && pHash->contains(strTopic)) {
        // Remove the observer from the given topic.
        QTKEventsHashType::iterator iter = pHash->find(strTopic);
        while (iter != pHash->end() && iter.key() == strTopic) {
            QObject *pItem = (*(iter.value()))[OBJECT].value<QObject *>();
            if (pItem == pObj) {
                QTKBusEvent *pProp = iter.value();
                bool bCurrentDisconnetFlag = false;
                if(bQtDisconnect) {
                    if (*pHash == m_callbacksHash) {
                        bCurrentDisconnetFlag = disconnectCallback(*pProp);
                    } else {
                        bCurrentDisconnetFlag = disconnectSignal(*pProp);
                    }
                } else {
                    bCurrentDisconnetFlag = true;
                }
                bDisconnectItem = bDisconnectItem && bCurrentDisconnetFlag;
                if (bCurrentDisconnetFlag) {
                    delete iter.value();
                    iter = pHash->erase(iter);
                } else {
                    qDebug() << tr("Unable to disconnect object %1 on topic %2").arg(pObj->objectName(), strTopic);
                    ++iter;
                }
            } else {
                ++iter;
            }
        }
        return bDisconnectItem;
    }

    if(strTopic.isEmpty()) {
        QTKEventsHashType::iterator iter = pHash->begin();
        while (iter != pHash->end()) {
            QObject *ptem = (*(iter.value()))[OBJECT].value<QObject *>();
            if(ptem == pObj) {
                QTKBusEvent *pProp = iter.value();
                bool bCurrentDisconnetFlag = false;
                if(bQtDisconnect) {
                    if (*pHash == m_callbacksHash) {
                        bCurrentDisconnetFlag = disconnectCallback(*pProp);
                    } else {
                        bCurrentDisconnetFlag = disconnectSignal(*pProp);
                    }
                } else {
                    bCurrentDisconnetFlag = true;
                }
                bDisconnectItem = bDisconnectItem && bCurrentDisconnetFlag;
                if (bCurrentDisconnetFlag) {
                    delete iter.value();
                    iter = pHash->erase(iter);
                } else {
                    qWarning() << tr("Unable to disconnect object %1 from topic %2").arg(pObj->objectName(), (*pProp)[TOPIC].toString());
                    ++iter;
                }
            } else {
                ++iter;
            }
        }
        return bDisconnectItem;
    }

    return false; //need to enter in one of the conditions
}

bool QTKEventDispatcher::removeObserver(QTKBusEvent &props)
{
    return removeEventItem(props);
}

bool QTKEventDispatcher::registerSignal(QTKBusEvent &props)
{
    // check if the object has been already registered with the same signature to avoid duplicates.
    if (props["Signature"].toString().length() == 0) {
        QVariant var;
        var.setValue((QObject *)this);
        props[OBJECT] = var;
        props[SIGNATURE] = "notifyDefaultEvent()";
    }

    QString strTopic = props[TOPIC].toString();
    // Check if a signal (corresponding to a mafID) already is present.
    if(m_signalsHash.contains(strTopic)) {// && (this->isSignaturePresent(signal_props) == true)) {
        // Only one signal for a given id can be registered!!
        QObject *pObj = props[OBJECT].value<QObject *>();
        if(pObj != nullptr) {
            qWarning("%s", tr("Object %1 is trying to register a signal with Topic '%2' that has been already registered!!").arg(pObj->metaObject()->className(), strTopic).toLatin1().data());
        } else {
            qWarning("%s", tr("nullptr is trying to register a signal with Topic '%2' that has been already registered!!").arg(strTopic).toLatin1().data());
        }
        return false;
    }

    QTKEventItemListType itemEventPropList;
    itemEventPropList = m_callbacksHash.values(strTopic);
    if(itemEventPropList.count() == 0) {
//        qDebug() << tr("Callbacks not present for topic %1, create only the entry in SignalsHash").arg(strTopic);

        // Add the new signal to the Hash.
        QTKBusEvent *pDict = const_cast<QTKBusEvent *>(&props);
        m_signalsHash.insert(strTopic, pDict);
        return true;
    }

    QObject *pObjSignal = props[OBJECT].value<QObject *>();
    QVariant sigVariant = props[SIGNATURE];
    QString strSig = sigVariant.toString();

    QTKBusEvent *pCurrentEvent = nullptr;
    bool bCumulativeConnect = true;
    if(strSig.length() > 0 && pObjSignal != nullptr) {
        foreach(pCurrentEvent, itemEventPropList) {
            QString strObserverSig = CALLBACK_SIGNATURE;
            strObserverSig.append((*pCurrentEvent)[SIGNATURE].toString());

            QString strEventSig = SIGNAL_SIGNATURE;
            strEventSig.append(strSig);

            QObject *pbjSlot = (*pCurrentEvent)[OBJECT].value<QObject *>();
            bCumulativeConnect = bCumulativeConnect && connect(pObjSignal, strEventSig.toLatin1(), pbjSlot, strObserverSig.toLatin1());
        }
        QTKBusEvent *pDict = const_cast<QTKBusEvent *>(&props);
        m_signalsHash.insert(strTopic, pDict);
    }

    return bCumulativeConnect;
}

bool QTKEventDispatcher::removeSignal(QTKBusEvent &props)
{
    return removeEventItem(props);
}

void QTKEventDispatcher::notifyEvent(QTKBusEvent &eventDictionary, QTKEventArgumentsList *pArgList,
                                     QTKGenericReturnArgument *pReturnArg) const
{
    Q_UNUSED(eventDictionary);
    Q_UNUSED(pArgList);
    Q_UNUSED(pReturnArg);
}
