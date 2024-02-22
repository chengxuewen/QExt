#ifndef LOGINCOMMAND_H
#define LOGINCOMMAND_H

#include <qextMVCCommand.h>

class LoginCommand : public QExtMVCCommand
{
public:
    LoginCommand();

    void excute(QExtMVCNotificationInterface *notification);
};

#endif // LOGINCOMMAND_H
