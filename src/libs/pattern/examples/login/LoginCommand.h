#ifndef LOGINCOMMAND_H
#define LOGINCOMMAND_H

#include <qextPatternCommand.h>

class LoginCommand : public QExtPatternCommand
{
public:
    LoginCommand();

    void excute(QExtPatternNotificationInterface *notification);
};

#endif // LOGINCOMMAND_H
