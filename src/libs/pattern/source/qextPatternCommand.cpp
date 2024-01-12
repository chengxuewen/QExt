#include <qextPatternCommand.h>

void QExtPatternCommand::excute(QExtPatternNotificationInterface *notification)
{
}

void QExtPatternCommand::notifyObserver(QExtPatternNotificationInterface *notification)
{
    excute(notification);
}
