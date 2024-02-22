#ifndef APPLICATIONFACADE_H
#define APPLICATIONFACADE_H

#include <qextMVCFacade.h>

class ApplicationFacade : public QExtMVCFacade
{
public:
    ApplicationFacade();

protected:
    void initializeMediator();
    void initializeCommand();
    void initializeProxy();
};

#endif // APPLICATIONFACADE_H
