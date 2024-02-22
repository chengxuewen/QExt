#include <qextMVCController.h>
#include <qextMVCInterface.h>
#include <qextMVCView.h>

QExtMVCController *QExtMVCController::m_instance = QEXT_NULLPTR;

QExtMVCController::QExtMVCController()
{
    m_view = QExtMVCView::instance();
}

QExtMVCController *QExtMVCController::instance()
{
    if (!m_instance)
    {
        m_instance = new QExtMVCController;
    }

    return m_instance;
}

void QExtMVCController::registerCommand(const QString &notificationName, QExtMVCCommandInterface *command)
{
    if (command == NULL)
    {
        return;
    }

    if (this->hasCommand(notificationName))
    {
        return;
    }

    m_commandMap[notificationName] = command;

    m_view->registerObserver((QExtMVCObserverInterface *)command, notificationName);
}

void QExtMVCController::excuteCommand(QExtMVCNotificationInterface *notification)
{
    if (!this->hasCommand(notification->getNotificationName()))
    {
        return;
    }

    QExtMVCCommandInterface *command = m_commandMap[notification->getNotificationName()];
    command->excute(notification);
}

bool QExtMVCController::hasCommand(const QString &notificationName)
{
    return m_commandMap.contains(notificationName);
}

void QExtMVCController::removeCommand(const QString &notificationName)
{
    m_commandMap.remove(notificationName);
}
