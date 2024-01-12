#ifndef LOGINPROXY_H
#define LOGINPROXY_H

#include <qextPatternProxy.h>

class LoginInfo;

class LoginProxy : public QExtPatternProxy
{
public:
    LoginProxy();

    void checkLogin(LoginInfo *loginInfo);
};

#endif // LOGINPROXY_H
