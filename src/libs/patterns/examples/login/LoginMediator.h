#ifndef LOGINMEDIATOR_H
#define LOGINMEDIATOR_H

#include <qextMVCMediator.h>

class LoginInfo;

class LoginMediator : public QExtMVCMediator
{
public:
    LoginMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(QExtMVCNotificationInterface *notification);

    // special
    void doLogin(LoginInfo *loginInfo);

private:
    QList<QString> m_notificationInterests;
};

#endif // LOGINMEDIATOR_H
