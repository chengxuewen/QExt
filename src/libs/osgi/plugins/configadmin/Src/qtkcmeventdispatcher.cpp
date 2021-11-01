#include "qtkcmeventdispatcher_p.h"

#include <QTKPluginFramework/Service/Log/QTKLogService>
#include <QTKPluginFramework/Service/Config/QTKConfigurationListener>

#include <QRunnable>

class QTKDispatchEventRunnable : public QRunnable
{
public:
    QTKDispatchEventRunnable(QTKServiceTracker<QTKConfigurationListener*> *pTracker,
                             QTKLogService* log, const QTKConfigurationEvent& event,
                             const QTKServiceReference& ref)
        : m_pTracker(pTracker), m_pLog(log), m_event(event), m_serviceRef(ref)
    {

    }

    void run()
    {
        QTKConfigurationListener *pListener = m_pTracker->getService(m_serviceRef);
        if (pListener == nullptr) {
            return;
        }

        try {
            pListener->configurationEvent(m_event);
        } catch (const std::exception &e) {
            m_pLog->log(QTKLogService::LOG_ERROR, e.what());
        } catch (...) {
            m_pLog->log(QTKLogService::LOG_ERROR, "Unspecified exception");
        }
    }

private:
    QTKServiceTracker<QTKConfigurationListener*>* m_pTracker;
    QTKLogService *m_pLog;
    QTKConfigurationEvent m_event;
    QTKServiceReference m_serviceRef;
};

QTKCMEventDispatcher::QTKCMEventDispatcher(QTKPluginContext* context, QTKLogService* log)
    : tracker(context), queue("QTKConfigurationListener Event Queue"), log(log)
{

}

void QTKCMEventDispatcher::start()
{
    tracker.open();
}

void QTKCMEventDispatcher::stop()
{
    tracker.close();
    {
        QMutexLocker lock(&mutex);
        configAdminReference = 0;
    }
}


void QTKCMEventDispatcher::setServiceReference(const QTKServiceReference& reference)
{
    QMutexLocker lock(&mutex);
    if (!configAdminReference)
    {
        configAdminReference = reference;
    }
}

void QTKCMEventDispatcher::dispatchEvent(QTKConfigurationEvent::Type type, const QString& factoryPid, const QString& pid)
{
    const QTKConfigurationEvent event = createConfigurationEvent(type, factoryPid, pid);
    if (event.isNull())
        return;

    QList<QTKServiceReference> refs = tracker.getServiceReferences();

    foreach (QTKServiceReference ref, refs)
    {
        queue.put(new QTKDispatchEventRunnable(&tracker, log, event, ref));
    }
}

QTKConfigurationEvent QTKCMEventDispatcher::createConfigurationEvent(QTKConfigurationEvent::Type type, const QString& factoryPid, const QString& pid)
{
    if (!configAdminReference)
    {
        return QTKConfigurationEvent();
    }

    return QTKConfigurationEvent(configAdminReference, type, factoryPid, pid);
}

