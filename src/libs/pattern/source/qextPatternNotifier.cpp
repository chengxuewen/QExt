#include <qextPatternNotifier.h>
#include <qextPatternInterface.h>
#include <qextPatternFacade.h>

QExtPatternNotifier::QExtPatternNotifier()
{
    m_facade = QExtPatternFacade::instance();
}

void QExtPatternNotifier::sendNotification(const QString &notificationName, void *body)
{
    m_facade->sendNotification(notificationName, body);
}
