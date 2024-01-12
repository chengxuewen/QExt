#include "LoginCommand.h"
#include "LoginProxy.h"
#include "LoginResult.h"

#include <qextPatternFacade.h>
#include <qextPatternInterface.h>

LoginCommand::LoginCommand()
{
}

void LoginCommand::excute(QExtPatternNotificationInterface *notification)
{
    LoginProxy *loginProxy = (LoginProxy *)QExtPatternFacade::instance()->retrieveProxy("LoginProxy");

    loginProxy->checkLogin((LoginInfo *)notification->getBody());
}
