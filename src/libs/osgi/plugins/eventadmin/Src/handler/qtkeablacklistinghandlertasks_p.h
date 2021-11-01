#ifndef QTKEABLACKLISTINGHANDLERTASKS_P_H
#define QTKEABLACKLISTINGHANDLERTASKS_P_H

#include "../qtkeventadminactivator_p.h"
#include "qtkeahandlertasks_p.h"
#include "qtkeatopichandlerfilters_p.h"
#include "qtkeafilters_p.h"
#include "qtkeablacklist_p.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>
#include <QTKPluginFramework/Service/Event/QTKEventHandler>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

template<class BlackList, class TopicHandlerFilters, class Filters>
class QTKEABlacklistingHandlerTasks
        : public QTKEAHandlerTasks<QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters> >
{
    typedef QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters> Self;

public:
    QTKEABlacklistingHandlerTasks(QTKPluginContext *pContext,
                                  QTKEABlackList<BlackList> *pBlackList,
                                  QTKEATopicHandlerFilters<TopicHandlerFilters> *pTopicHandlerFilters,
                                  QTKEAFilters<Filters> *pFilters);

    ~QTKEABlacklistingHandlerTasks();

    QList<QTKEAHandlerTask<Self> > createHandlerTasks(const QTKEvent &event);

    void blackListRef(const QTKServiceReference &handlerRef);

    QTKEventHandler *getEventHandler(const QTKServiceReference &handlerRef);

    void ungetEventHandler(QTKEventHandler *pHandler, const QTKServiceReference &handlerRef);

private:
    struct NullEventHandler : public QTKEventHandler
    {
        void handleEvent(const QTKEvent &/*event*/) {
            // This is a null object that is supposed to do nothing at this
            // point. This is used once a QTKEventHandler is requested for a
            // servicereference that is either stale (i.e., unregistered) or
            // blacklisted.
        }
    };

    void checkNull(void *pObject, const QString &strName);

    NullEventHandler m_nullEventHandler;
    // The blacklist that holds blacklisted event handler service references
    QTKEABlackList<BlackList> *const m_pListblack;
    // The context of the plugin used to get the actual event handler services
    QTKPluginContext *const m_pContext;
    // Used to create the filters that can determine applicable event handlers for
    // a given event
    QTKEATopicHandlerFilters<TopicHandlerFilters> *m_pTopicHandlerFilters;
    // Used to create the filters that are used to determine whether an applicable
    // event handler is interested in a particular event
    QTKEAFilters<Filters> *m_pFilters;
};



template<class BlackList, class TopicHandlerFilters, class Filters>
QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters>::
QTKEABlacklistingHandlerTasks(QTKPluginContext* pContext,
                              QTKEABlackList<BlackList>* pBlackList,
                              QTKEATopicHandlerFilters<TopicHandlerFilters>* pTopicHandlerFilters,
                              QTKEAFilters<Filters>* pFilters)
    : m_pListblack(pBlackList), m_pContext(pContext),
      m_pTopicHandlerFilters(pTopicHandlerFilters), m_pFilters(pFilters)
{
    checkNull(pContext, "Context");
    checkNull(pBlackList, "BlackList");
    checkNull(pTopicHandlerFilters, "TopicHandlerFilters");
    checkNull(pFilters, "Filters");
}

template<class BlackList, class TopicHandlerFilters, class Filters>
QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters>::
~QTKEABlacklistingHandlerTasks()
{
    delete m_pFilters;
    delete m_pTopicHandlerFilters;
    delete m_pListblack;
}

template<class BlackList, class TopicHandlerFilters, class Filters>
QList<QTKEAHandlerTask<QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters> > >
QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters>::
createHandlerTasks(const QTKEvent& event)
{
    QList<QTKEAHandlerTask<Self> > result;
    QList<QTKServiceReference> handlerRefs;

    try
    {
        handlerRefs = m_pContext->getServiceReferences<QTKEventHandler>(
                    m_pTopicHandlerFilters->createFilterForTopic(event.getTopic()));
    }
    catch (const QTKInvalidArgumentException& e)
    {
        QTK_WARN_EXC(QTKEventAdminActivator::getLogService(), &e)
                << "Invalid EVENT_TOPIC [" << event.getTopic() << "]";
    }

    for (int i = 0; i < handlerRefs.size(); ++i)
    {
        const QTKServiceReference& ref = handlerRefs.at(i);
        if (!m_pListblack->contains(ref)
                //TODO security
                //&& ref.getPlugin()->hasPermission(
                //  PermissionsUtil.createSubscribePermission(event.getTopic()))
                )
        {
            try
            {
                if (event.matches(m_pFilters->createFilter(
                                      ref.getProperty(QTKEventConstants::EVENT_FILTER).toString())))
                {
                    result.push_back(QTKEAHandlerTask<Self>(ref, event, this));
                }
            }
            catch (const QTKInvalidArgumentException& e)
            {
                QTK_WARN_SR_EXC(QTKEventAdminActivator::getLogService(), ref, &e)
                        << "Invalid EVENT_FILTER - Blacklisting ServiceReference ["
                        << ref << " | Plugin(" << ref.getPlugin() << ")]";

                m_pListblack->add(ref);
            }
        }
    }

    return result;
}

template<class BlackList, class TopicHandlerFilters, class Filters>
void
QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters>::
blackListRef(const QTKServiceReference& handlerRef)
{
    m_pListblack->add(handlerRef);

    QTK_WARN(QTKEventAdminActivator::getLogService())
            << "Blacklisting ServiceReference [" << handlerRef << " | Plugin("
            << handlerRef.getPlugin() << ")] due to timeout!";
}

template<class BlackList, class TopicHandlerFilters, class Filters>
QTKEventHandler*
QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters>::
getEventHandler(const QTKServiceReference& handlerRef)
{
    QTKEventHandler* result = (m_pListblack->contains(handlerRef)) ? 0
                                                                : m_pContext->getService<QTKEventHandler>(handlerRef);

    return (result ? result : &m_nullEventHandler);
}

template<class BlackList, class TopicHandlerFilters, class Filters>
void
QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters>::
ungetEventHandler(QTKEventHandler* pHandler,
                  const QTKServiceReference& handlerRef)
{
    if(&m_nullEventHandler != pHandler)
    {
        // Is the handler not unregistered or blacklisted?
        if(!m_pListblack->contains(handlerRef) &&
                (handlerRef.getPlugin()))
        {
            m_pContext->ungetService(handlerRef);
        }
    }
}

template<class BlackList, class TopicHandlerFilters, class Filters>
void
QTKEABlacklistingHandlerTasks<BlackList, TopicHandlerFilters, Filters>::
checkNull(void* pObject, const QString& strName)
{
    if(pObject == 0)
    {
        throw QTKInvalidArgumentException(qPrintable(strName + " may not be null"));
    }
}


#endif // QTKEABLACKLISTINGHANDLERTASKS_P_H
