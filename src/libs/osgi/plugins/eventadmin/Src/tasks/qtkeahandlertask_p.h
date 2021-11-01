#ifndef QTKEAHANDLERTASK_P_H
#define QTKEAHANDLERTASK_P_H

#include "../qtkeventadminactivator_p.h"
#include "../handler/qtkeablacklistinghandlertasks_p.h"

#include <QTKPluginFramework/QTKServiceReference>
#include <QTKPluginFramework/Service/Event/QTKEvent>
#include <QTKPluginFramework/Service/Event/QTKEventHandler>

#include <QAtomicInt>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

template<class BlacklistingHandlerTasks>
class QTKEAHandlerTask
{
    typedef QTKEAHandlerTask<BlacklistingHandlerTasks> Self;

public:
    QTKEAHandlerTask(const QTKServiceReference &eventHandlerRef,
                     const QTKEvent &event, BlacklistingHandlerTasks *pHandlerTasks);
    QTKEAHandlerTask(const Self &task);

    QTKEAHandlerTask& operator=(const Self &task);

    QString getHandlerClassName() const;

    void execute();

    void blackListHandler();

private:
    class QTKGetAndUngetEventHandler;

    // The service reference of the handler
    QTKServiceReference m_eventHandlerRef;
    // The event to deliver to the handler
    QTKEvent m_event;
    // Used to blacklist the service or get the service object for the reference
    BlacklistingHandlerTasks *m_pHandlerTasks;
};

template<class BlacklistingHandlerTasks>
class QTKEAHandlerTask<BlacklistingHandlerTasks>::QTKGetAndUngetEventHandler
{
public:
    QTKGetAndUngetEventHandler(BlacklistingHandlerTasks *pHandlerTasks, const QTKServiceReference &serviceRef)
        : m_pHandlerTasks(pHandlerTasks),
          m_pCurrentHandler(nullptr),
          m_currentServiceRef(serviceRef)
    {
        m_pCurrentHandler = pHandlerTasks->getEventHandler(m_currentServiceRef);
    }

    ~QTKGetAndUngetEventHandler()
    {
        m_pHandlerTasks->ungetEventHandler(m_pCurrentHandler, m_currentServiceRef);
    }

    QObject *getObject() const
    {
        return dynamic_cast<QObject*>(m_pCurrentHandler);
    }

    QTKEventHandler *getHandler() const
    {
        return m_pCurrentHandler;
    }

private:
    BlacklistingHandlerTasks *m_pHandlerTasks;
    QTKEventHandler *m_pCurrentHandler;
    QTKServiceReference m_currentServiceRef;
};

template<class BlacklistingHandlerTasks>
QTKEAHandlerTask<BlacklistingHandlerTasks>::QTKEAHandlerTask(const QTKServiceReference &eventHandlerRef,
                                                             const QTKEvent &event, BlacklistingHandlerTasks *pHandlerTasks)
    : m_eventHandlerRef(eventHandlerRef),
      m_event(event),
      m_pHandlerTasks(pHandlerTasks)
{

}

template<class BlacklistingHandlerTasks>
QTKEAHandlerTask<BlacklistingHandlerTasks>::QTKEAHandlerTask(const Self &task)
    : m_eventHandlerRef(task.m_eventHandlerRef),
      m_event(task.m_event),
      m_pHandlerTasks(task.m_pHandlerTasks)
{

}

template<class BlacklistingHandlerTasks>
QTKEAHandlerTask<BlacklistingHandlerTasks> &QTKEAHandlerTask<BlacklistingHandlerTasks>::operator=(const Self &task)
{
    m_eventHandlerRef = task.m_eventHandlerRef;
    m_event = task.m_event;
    m_pHandlerTasks = task.m_pHandlerTasks;
    return *this;
}

template<class BlacklistingHandlerTasks>
QString QTKEAHandlerTask<BlacklistingHandlerTasks>::getHandlerClassName() const
{
    QObject *pHandler = QTKGetAndUngetEventHandler(m_pHandlerTasks, m_eventHandlerRef).getObject();
    return pHandler->metaObject()->className();
}

template<class BlacklistingHandlerTasks>
void QTKEAHandlerTask<BlacklistingHandlerTasks>::execute()
{
    // Get the service object
    QTKEventHandler *const pHandler = QTKGetAndUngetEventHandler(m_pHandlerTasks, m_eventHandlerRef).getHandler();
    try {
        pHandler->handleEvent(m_event);
    } catch (const std::exception &e) {
        // The spec says that we must catch exceptions and log them:
        QTK_WARN_SR_EXC(QTKEventAdminActivator::getLogService(), m_eventHandlerRef, &e)
                << "Exception during event dispatch [" << m_event.getTopic() << "| Plugin("
                << m_eventHandlerRef.getPlugin()->getSymbolicName() << ")]";
    }
}

template<class BlacklistingHandlerTasks>
void QTKEAHandlerTask<BlacklistingHandlerTasks>::blackListHandler()
{
    m_pHandlerTasks->blackListRef(m_eventHandlerRef);
}

#endif // QTKEAHANDLERTASK_P_H
