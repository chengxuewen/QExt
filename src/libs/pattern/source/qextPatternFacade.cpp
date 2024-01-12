#include <qextPatternFacade.h>
#include <qextPatternInterface.h>
#include <qextPatternNotification.h>
#include <qextPatternController.h>
#include <qextPatternModel.h>
#include <qextPatternView.h>

QExtPatternFacade *QExtPatternFacade::m_instance;

QExtPatternFacade::QExtPatternFacade()
{
    m_view = QExtPatternView::instance();
    m_model = QExtPatternModel::instance();
    m_controller = QExtPatternController::instance();

    this->initializeMediator();
    this->initializeCommand();
    this->initializeProxy();
}

QExtPatternFacade *QExtPatternFacade::instance()
{
    if (m_instance)
    {
        m_instance = new QExtPatternFacade();
    }
    return m_instance;
}

void QExtPatternFacade::initializeMediator()
{
}

void QExtPatternFacade::initializeCommand()
{
}

void QExtPatternFacade::initializeProxy()
{
}

void QExtPatternFacade::registerObserver(QExtPatternObserverInterface *observer, const QString &notificationName)
{
    m_view->registerObserver(observer, notificationName);
}

void QExtPatternFacade::removeObserver(const QString &notificationName)
{
    m_view->removeObserver(notificationName);
}

void QExtPatternFacade::notifyObservers(QExtPatternNotificationInterface *notification)
{
    m_view->notifyObservers(notification);
}

void QExtPatternFacade::registerMediator(QExtPatternMediatorInterface *mediator)
{
    m_view->registerMediator(mediator);
}

QExtPatternMediatorInterface *QExtPatternFacade::retrieveMediator(const QString &mediatorName)
{
    return m_view->retrieveMediator(mediatorName);
}

bool QExtPatternFacade::hasMediator(const QString &mediatorName)
{
    return m_view->hasMediator(mediatorName);
}

void QExtPatternFacade::removeMediator(const QString &mediatorName)
{
    m_view->removeMediator(mediatorName);
}

void QExtPatternFacade::registerCommand(const QString &notificationName, QExtPatternCommandInterface *command)
{
    m_controller->registerCommand(notificationName, command);
}

bool QExtPatternFacade::hasCommand(const QString &notificationName)
{
    return m_controller->hasCommand(notificationName);
}

void QExtPatternFacade::removeCommand(const QString &notificationName)
{
    m_controller->removeCommand(notificationName);
}

void QExtPatternFacade::registerProxy(QExtPatternProxyInterface *proxy)
{
    m_model->registerProxy(proxy);
}

QExtPatternProxyInterface *QExtPatternFacade::retrieveProxy(const QString &proxyName)
{
    return m_model->retrieveProxy(proxyName);
}

bool QExtPatternFacade::hasProxy(const QString &proxyName)
{
    return m_model->hasProxy(proxyName);
}

void QExtPatternFacade::removeProxy(const QString &proxyName)
{
    m_model->removeProxy(proxyName);
}

void QExtPatternFacade::sendNotification(const QString &notificationName, void *body)
{
    m_view->notifyObservers(new QExtPatternNotification(notificationName, body));
}

void QExtPatternFacade::startUp()
{
    this->initializeCommand();
    this->initializeProxy();
    this->initializeMediator();
}
