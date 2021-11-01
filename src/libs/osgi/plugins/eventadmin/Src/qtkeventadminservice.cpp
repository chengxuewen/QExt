#include "qtkeventadminservice_p.h"
#include "handler/qtkeaslothandler_p.h"

#include <QTKPluginFramework/QTKPluginConstants>

QTKEventAdminService::QTKEventAdminService(QTKPluginContext *pContext, HandlerTasksInterface *pManagers,
                                           QTKEADefaultThreadPool *pSyncPool, QTKEADefaultThreadPool *pAsyncPool,
                                           int iTimeout, const QStringList &listIgnoreTimeout)
    : m_impl(pManagers, pSyncPool, pAsyncPool, iTimeout, listIgnoreTimeout),
      m_pContext(pContext)
{

}

QTKEventAdminService::~QTKEventAdminService()
{
    qDeleteAll(m_mapSlotHandler);
    foreach(QList<QTKEASignalPublisher*> list, m_mapSignalPublisher.values()) {
        qDeleteAll(list);
    }
}

void QTKEventAdminService::postEvent(const QTKEvent &event)
{
    m_impl.postEvent(event);
}

void QTKEventAdminService::sendEvent(const QTKEvent &event)
{
    m_impl.sendEvent(event);
}

void QTKEventAdminService::publishSignal(const QObject *pPublisher, const char *psSignal,
                                         const QString &strTopic, Qt::ConnectionType eType)
{
    if (strTopic.isEmpty()) {
        throw QTKInvalidArgumentException("topic must not be empty");
    }

    // check if the signal was already registered under the given topic
    if (m_mapSignalPublisher.contains(pPublisher)) {
        const QList<QTKEASignalPublisher*> &listSignalPublishers = m_mapSignalPublisher[pPublisher];
        for (int i = 0; i < listSignalPublishers.size(); ++i) {
            if (listSignalPublishers[i]->getSignalName() == psSignal && listSignalPublishers[i]->getTopicName() == strTopic) {
                return;
            }
        }
    }

    QList<QTKEASignalPublisher*> &listSignal = m_mapSignalPublisher[pPublisher];
    listSignal.push_back(new QTKEASignalPublisher(this, psSignal, strTopic));
    if (eType == Qt::DirectConnection) {
        connect(pPublisher, psSignal, listSignal.back(), SLOT(publishSyncSignal(QTKDictionary)), Qt::DirectConnection);
    } else if (eType == Qt::QueuedConnection) {
        connect(pPublisher, psSignal, listSignal.back(), SLOT(publishAsyncSignal(QTKDictionary)), Qt::DirectConnection);
    } else {
        throw QTKInvalidArgumentException("type must be either Qt::DirectConnection or Qt::QueuedConnection");
    }
}

void QTKEventAdminService::unpublishSignal(const QObject *pPublisher, const char *psSignal,
                                           const QString &strTopic)
{
    if (!m_mapSignalPublisher.contains(pPublisher)) {
        return;
    }

    if (nullptr == psSignal && strTopic.isEmpty()) {
        // unpublish everything from the given publisher
        // this automatically disconnects signals
        qDeleteAll(m_mapSignalPublisher.take(pPublisher));
    } else {
        QList<QTKEASignalPublisher*> &list = m_mapSignalPublisher[pPublisher];
        if (nullptr == psSignal) {
            for (int i = 0; i < list.size();) {
                if (list[i]->getTopicName() == strTopic) {
                    // this automatically disconnects the signals
                    delete list.takeAt(i);
                } else {
                    ++i;
                }
            }
        } else {
            for (int i = 0; i < list.size();) {
                if (list[i]->getSignalName() == psSignal) {
                    if (strTopic.isEmpty() || list[i]->getTopicName() == strTopic) {
                        // this automatically disconnects the signals
                        delete list.takeAt(i);
                    }
                } else {
                    ++i;
                }
            }
        }

        if (list.isEmpty()) {
            m_mapSignalPublisher.remove(pPublisher);
        }
    }
}

qlonglong QTKEventAdminService::subscribeSlot(const QObject *pSubscriber, const char *psMember,
                                              const QTKDictionary &properties, Qt::ConnectionType eType)
{
    if (nullptr == pSubscriber) {
        throw QTKInvalidArgumentException("subscriber cannot be nullptr");
    }
    if (nullptr == psMember) {
        throw QTKInvalidArgumentException("slot cannot be nullptr");
    }
    if (eType != Qt::AutoConnection && eType != Qt::DirectConnection && eType != Qt::QueuedConnection && eType != Qt::BlockingQueuedConnection) {
        throw QTKInvalidArgumentException("connection type invalid");
    }

    QTKEASlotHandler *pHandler = new QTKEASlotHandler();
    connect(pHandler, SIGNAL(eventOccured(QTKEvent)), pSubscriber, psMember, eType);
    QTKServiceRegistration serviceReg = m_pContext->registerService<QTKEventHandler>(pHandler, properties);
    pHandler->m_serviceReg = serviceReg;
    qlonglong llId = serviceReg.getReference().getProperty(QTKPluginConstants::SERVICE_ID).toLongLong();
    m_mapSlotHandler.insert(llId, pHandler);
    return llId;
}

void QTKEventAdminService::unsubscribeSlot(qlonglong llSubscriptionId)
{
    QTKEASlotHandler *pHandler = m_mapSlotHandler.take(llSubscriptionId);
    if (pHandler) {
        pHandler->m_serviceReg.unregister();
        delete pHandler;
    }
}

bool QTKEventAdminService::updateProperties(qlonglong llSubscriptionId, const QTKDictionary &properties)
{
    QTKEASlotHandler *pHandler = m_mapSlotHandler.value(llSubscriptionId);
    if (pHandler) {
        pHandler->updateProperties(properties);
        return true;
    }
    return false;
}

void QTKEventAdminService::stop()
{
    m_impl.stop();
}

void QTKEventAdminService::update(HandlerTasksInterface *pManagers, int iTimeout,
                                  const QStringList &listIgnoreTimeout)
{
    m_impl.update(pManagers, iTimeout, listIgnoreTimeout);
}

