#include <qextPatternNotification.h>

QExtPatternNotification::QExtPatternNotification(const QString &notificationName, void *body)
{
    m_notificationName = notificationName;
    m_body = body;
}

QString QExtPatternNotification::getNotificationName()
{
    return m_notificationName;
}

void *QExtPatternNotification::getBody()
{
    return m_body;
}
