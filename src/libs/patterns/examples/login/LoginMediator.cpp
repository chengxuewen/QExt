#include "LoginMediator.h"
#include "LoginInfo.h"
#include "LoginResult.h"

#include <qextMVCInterface.h>

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

void LoginMediator::handleNotification(QExtMVCNotificationInterface *notification)
{
    if (notification->getNotificationName() == "login_success")
    {
        m_viewComponent->update((QExtMVCUpdateDataInterface *)notification->getBody());
    }
}

void LoginMediator::doLogin(LoginInfo *loginInfo)
{
    sendNotification("login_check", loginInfo);
}
