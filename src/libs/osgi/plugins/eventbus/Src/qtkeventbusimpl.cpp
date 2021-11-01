#include "qtkeventbusimpl.h"
#include "qtkeventhandlerwrapper_p.h"
#include "qtkbusevent.h"
#include "qtkeventdefinitions.h"

#include <QSetIterator>

#define QTKEventArgument(type,data) QArgument<type >(#type, data)

QTKEventBusImpl::QTKEventBusImpl()
{
    m_pEventBusManager = qtkeventbus::QTKEventBusManager::instance();
}

void QTKEventBusImpl::postEvent(const ::QTKEvent &event)
{
    this->dispatchEvent(event, true);
}

void QTKEventBusImpl::sendEvent(const ::QTKEvent &event)
{
    this->dispatchEvent(event, false);
}

void QTKEventBusImpl::publishSignal(const QObject *pPublisher, const char *pSignal,
                                    const QString &strTopic, Qt::ConnectionType eType)
{
    Q_UNUSED(eType);
    QTKBusEvent *pMesbEvent = new QTKBusEvent(strTopic, qtkeventbus::QTKEventTypeLocal, qtkeventbus::QTKSignatureTypeSignal, const_cast<QObject *>(pPublisher), pSignal);
    m_pEventBusManager->addEventProperty(*pMesbEvent);
}

void QTKEventBusImpl::unpublishSignal(const QObject *pPublisher, const char *pSignal, const QString &strTopic)
{
    Q_UNUSED(pPublisher)
    Q_UNUSED(pSignal)
    Q_UNUSED(strTopic)
    //    TODO implement
}

qlonglong QTKEventBusImpl::subscribeSlot(const QObject *pSubscriber, const char *pMember,
                                         const QTKDictionary &properties, Qt::ConnectionType eType)
{
    Q_UNUSED(eType)

    QTKDictionary toSend(properties);
    QString strTopic = properties.value(TOPIC).toString();
    toSend.insert(TOPIC, strTopic);
    toSend.insert(TYPE, qtkeventbus::QTKEventTypeLocal);
    toSend.insert(SIGTYPE, qtkeventbus::QTKSignatureTypeCallback);
    QVariant var;
    var.setValue(const_cast<QObject *>(pSubscriber));
    toSend.insert(OBJECT, var);
    toSend.insert(SIGNATURE,pMember);
    QTKBusEvent *pMesbEvent = new QTKBusEvent(strTopic, toSend);
    m_pEventBusManager->addEventProperty(*pMesbEvent);

    return strTopic.toLongLong();
}

void QTKEventBusImpl::unsubscribeSlot(qlonglong llSubscriptionId)
{
    Q_UNUSED(llSubscriptionId)
    // @@@@to be implemented
}

bool QTKEventBusImpl::updateProperties(qlonglong llSubsriptionId, const QTKDictionary &properties)
{
    Q_UNUSED(llSubsriptionId)
    Q_UNUSED(properties)
    // @@@@to be implemented
    return false;
}

void QTKEventBusImpl::dispatchEvent(const QTKEvent &event, bool bIsAsync)
{
    Q_UNUSED(bIsAsync)
    QTKBusEvent *pMebEvent = new QTKBusEvent("",qtkeventbus::QTKEventTypeRemote,qtkeventbus::QTKSignatureTypeSignal, this, "no");
    //cycle for all other elements
    QStringList listKey = event.getPropertyNames();
    QStringList::const_iterator constIterator;
    for (constIterator = listKey.constBegin(); constIterator != listKey.constEnd(); ++constIterator) {
        QVariant value = event.getProperty((*constIterator));
        //qDebug() << (*constIterator) << " " << value.toString();
        (*pMebEvent)[(*constIterator)] = event.getProperty((*constIterator));
    }

    typedef QList<QGenericArgument> QTKEventArgumentList;

    QTKEventArgumentList list;
    list.append(Q_ARG(QVariantList,event.getProperty("localEvent").toList()));
    list.append(Q_ARG(QVariantList,event.getProperty("localData").toList()));

    m_pEventBusManager->notifyEvent(*pMebEvent, &list);
}

bool QTKEventBusImpl::createServer(const QString &strCommunicationProtocol, unsigned int ulListenPort)
{
    return m_pEventBusManager->createServer(strCommunicationProtocol,ulListenPort);
}

void QTKEventBusImpl::startListen()
{
    m_pEventBusManager->startListen();
}

bool QTKEventBusImpl::createClient(const QString &strCommunicationProtocol, const QString &strServerHost, unsigned int uiPort)
{
    return m_pEventBusManager->createClient(strCommunicationProtocol,strServerHost,uiPort);
}
