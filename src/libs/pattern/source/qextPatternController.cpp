#include <qextPatternController.h>
#include <qextPatternInterface.h>
#include <qextPatternView.h>

QExtPatternController *QExtPatternController::m_instance;

QExtPatternController::QExtPatternController()
{
    m_view = QExtPatternView::instance();
}

QExtPatternController *QExtPatternController::instance()
{
    if (m_instance == NULL)
    {
        m_instance = new QExtPatternController();
    }

    return m_instance;
}

void QExtPatternController::registerCommand(const QString &notificationName, QExtPatternCommandInterface *command)
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

    m_view->registerObserver((QExtPatternObserverInterface *)command, notificationName);
}

void QExtPatternController::excuteCommand(QExtPatternNotificationInterface *notification)
{
    if (!this->hasCommand(notification->getNotificationName()))
    {
        return;
    }

    QExtPatternCommandInterface *command = m_commandMap[notification->getNotificationName()];
    command->excute(notification);
}

bool QExtPatternController::hasCommand(const QString &notificationName)
{
    return m_commandMap.contains(notificationName);
}

void QExtPatternController::removeCommand(const QString &notificationName)
{
    m_commandMap.remove(notificationName);
}
