#include <qextMVCNotifier.h>
#include <qextMVCInterface.h>
#include <qextMVCFacade.h>

QExtMVCNotifier::QExtMVCNotifier()
{
    m_facade = QExtMVCFacade::instance();
}

void QExtMVCNotifier::sendNotification(const QString &notificationName, void *body)
{
    m_facade->sendNotification(notificationName, body);
}
