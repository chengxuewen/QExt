#ifndef LOGINMEDIATOR_H
#define LOGINMEDIATOR_H

#include <qextPatternMediator.h>

class LoginInfo;

class LoginMediator : public QExtPatternMediator
{
public:
    LoginMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(QExtPatternNotificationInterface *notification);

    // special
    void doLogin(LoginInfo *loginInfo);

private:
    QList<QString> m_notificationInterests;
};

#endif // LOGINMEDIATOR_H
