#include <qextMVCNotification.h>

QExtMVCNotification::QExtMVCNotification(const QString &notificationName, void *body)
{
    m_notificationName = notificationName;
    m_body = body;
}

QString QExtMVCNotification::getNotificationName()
{
    return m_notificationName;
}

void *QExtMVCNotification::getBody()
{
    return m_body;
}
