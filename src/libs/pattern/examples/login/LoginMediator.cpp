#include "LoginMediator.h"
#include "LoginInfo.h"
#include "LoginResult.h"

#include <qextPatternInterface.h>

#include <QDebug>

LoginMediator::LoginMediator()
{
    MEDIATOR_NAME = "LoginMediator";

    m_notificationInterests.append("login_success");
    m_notificationInterests.append("login_error");
}

QList<QString> LoginMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

void LoginMediator::handleNotification(QExtPatternNotificationInterface *notification)
{
    if (notification->getNotificationName() == "login_success")
    {
        m_viewComponent->update((QExtPatternUpdateDataInterface *)notification->getBody());
    }
}

void LoginMediator::doLogin(LoginInfo *loginInfo)
{
    sendNotification("login_check", loginInfo);
}
