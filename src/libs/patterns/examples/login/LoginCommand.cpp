#include "LoginCommand.h"
#include "LoginProxy.h"
#include "LoginResult.h"

#include <qextMVCFacade.h>
#include <qextMVCInterface.h>

LoginCommand::LoginCommand()
{
}

void LoginCommand::excute(QExtMVCNotificationInterface *notification)
{
    LoginProxy *loginProxy = (LoginProxy *)QExtMVCFacade::instance()->retrieveProxy("LoginProxy");

    loginProxy->checkLogin((LoginInfo *)notification->getBody());
}
