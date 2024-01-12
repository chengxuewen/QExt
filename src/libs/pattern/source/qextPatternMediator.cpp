#include <qextPatternMediator.h>
#include <qextPatternInterface.h>

QString QExtPatternMediator::MEDIATOR_NAME = "Mediator";

void QExtPatternMediator::registerViewComponent(QExtPatternViewComponentInterface *viewComponent)
{
    if (viewComponent == NULL)
    {
        return;
    }

    m_viewComponent = viewComponent;
}

QString QExtPatternMediator::getMediatorName()
{
    return MEDIATOR_NAME;
}

void QExtPatternMediator::notifyObserver(QExtPatternNotificationInterface *notification)
{
    handleNotification(notification);
}
