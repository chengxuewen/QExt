#include "qtkeasignalpublisher_p.h"
#include "qtkeventadminservice_p.h"

QTKEASignalPublisher::QTKEASignalPublisher(QTKEventAdminService *pEventAdmin, const QString &strSignal,
                                           const QString &strTopic)
    : m_pEventAdmin(pEventAdmin),
      m_strSignal(strSignal),
      m_strTopic(strTopic)
{
}

QString QTKEASignalPublisher::getSignalName() const
{
    return m_strSignal;
}

QString QTKEASignalPublisher::getTopicName() const
{
    return m_strTopic;
}

void QTKEASignalPublisher::publishSyncSignal(const QTKDictionary &eventProps)
{
    QTKDictionary props(eventProps);
    props.insert(QTKEventConstants::EVENT_TOPICS, m_strTopic);
    QTKEvent event(m_strTopic, props);
    m_pEventAdmin->sendEvent(event);
}

void QTKEASignalPublisher::publishAsyncSignal(const QTKDictionary &eventProps)
{
    QTKDictionary props(eventProps);
    props.insert(QTKEventConstants::EVENT_TOPICS, m_strTopic);
    QTKEvent event(m_strTopic, props);
    m_pEventAdmin->postEvent(event);
}
