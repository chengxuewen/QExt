#ifndef LOGINRESULT_H
#define LOGINRESULT_H

#include <qextMVCUpdateData.h>

class LoginResult : public QExtMVCUpdateData
{
public:
    LoginResult();

public:
    bool result;
};

#endif // LOGINRESULT_H
