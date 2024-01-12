#ifndef LOGINRESULT_H
#define LOGINRESULT_H

#include <qextPatternUpdateData.h>

class LoginResult : public QExtPatternUpdateData
{
public:
    LoginResult();

public:
    bool result;
};

#endif // LOGINRESULT_H
