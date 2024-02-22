#include <qextMVCFacade.h>
#include <qextMVCInterface.h>
#include <qextMVCNotification.h>
#include <qextMVCController.h>
#include <qextMVCModel.h>
#include <qextMVCView.h>

QExtMVCFacade *QExtMVCFacade::m_instance = QEXT_NULLPTR;

QExtMVCFacade::QExtMVCFacade()
{
    m_view = QExtMVCView::instance();
    m_model = QExtMVCModel::instance();
    m_controller = QExtMVCController::instance();
}

QExtMVCFacade *QExtMVCFacade::instance()
{
    if (!m_instance)
    {
        m_instance = new QExtMVCFacade();
    }
    return m_instance;
}

void QExtMVCFacade::initializeMediator()
{
}

void QExtMVCFacade::initializeCommand()
{
}

void QExtMVCFacade::initializeProxy()
{
}

void QExtMVCFacade::registerObserver(QExtMVCObserverInterface *observer, const QString &notificationName)
{
    m_view->registerObserver(observer, notificationName);
}

void QExtMVCFacade::removeObserver(const QString &notificationName)
{
    m_view->removeObserver(notificationName);
}

void QExtMVCFacade::notifyObservers(QExtMVCNotificationInterface *notification)
{
    m_view->notifyObservers(notification);
}

void QExtMVCFacade::registerMediator(QExtMVCMediatorInterface *mediator)
{
    m_view->registerMediator(mediator);
}

QExtMVCMediatorInterface *QExtMVCFacade::retrieveMediator(const QString &mediatorName)
{
    return m_view->retrieveMediator(mediatorName);
}

bool QExtMVCFacade::hasMediator(const QString &mediatorName)
{
    return m_view->hasMediator(mediatorName);
}

void QExtMVCFacade::removeMediator(const QString &mediatorName)
{
    m_view->removeMediator(mediatorName);
}

void QExtMVCFacade::registerCommand(const QString &notificationName, QExtMVCCommandInterface *command)
{
    m_controller->registerCommand(notificationName, command);
}

bool QExtMVCFacade::hasCommand(const QString &notificationName)
{
    return m_controller->hasCommand(notificationName);
}

void QExtMVCFacade::removeCommand(const QString &notificationName)
{
    m_controller->removeCommand(notificationName);
}

void QExtMVCFacade::registerProxy(QExtMVCProxyInterface *proxy)
{
    m_model->registerProxy(proxy);
}

QExtMVCProxyInterface *QExtMVCFacade::retrieveProxy(const QString &proxyName)
{
    return m_model->retrieveProxy(proxyName);
}

bool QExtMVCFacade::hasProxy(const QString &proxyName)
{
    return m_model->hasProxy(proxyName);
}

void QExtMVCFacade::removeProxy(const QString &proxyName)
{
    m_model->removeProxy(proxyName);
}

void QExtMVCFacade::sendNotification(const QString &notificationName, void *body)
{
    m_view->notifyObservers(new QExtMVCNotification(notificationName, body));
}

void QExtMVCFacade::startUp()
{
    this->initializeCommand();
    this->initializeProxy();
    this->initializeMediator();
}
