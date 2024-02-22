#include <qextMVCCommand.h>

void QExtMVCCommand::excute(QExtMVCNotificationInterface *notification)
{
}

void QExtMVCCommand::notifyObserver(QExtMVCNotificationInterface *notification)
{
    excute(notification);
}
