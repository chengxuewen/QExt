#ifndef LOGINPROXY_H
#define LOGINPROXY_H

#include <qextMVCProxy.h>

class LoginInfo;

class LoginProxy : public QExtMVCProxy
{
public:
    LoginProxy();

    void checkLogin(LoginInfo *loginInfo);
};

#endif // LOGINPROXY_H
