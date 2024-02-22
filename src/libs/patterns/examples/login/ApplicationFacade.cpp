#include "ApplicationFacade.h"
#include "LoginCommand.h"
#include "LoginMediator.h"
#include "LoginProxy.h"

ApplicationFacade::ApplicationFacade() : QExtMVCFacade()
{
}

void ApplicationFacade::initializeMediator()
{
    registerMediator(new LoginMediator());
}

void ApplicationFacade::initializeCommand()
{
    registerCommand("login_check", new LoginCommand());
}

void ApplicationFacade::initializeProxy()
{
    registerProxy(new LoginProxy());
}
