#include <qextMVCMediator.h>
#include <qextMVCInterface.h>

QString QExtMVCMediator::MEDIATOR_NAME = "Mediator";

void QExtMVCMediator::registerViewComponent(QExtMVCViewComponentInterface *viewComponent)
{
    if (viewComponent == NULL)
    {
        return;
    }

    m_viewComponent = viewComponent;
}

QString QExtMVCMediator::getMediatorName()
{
    return MEDIATOR_NAME;
}

void QExtMVCMediator::notifyObserver(QExtMVCNotificationInterface *notification)
{
    handleNotification(notification);
}
