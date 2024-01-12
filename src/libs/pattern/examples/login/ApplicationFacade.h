#ifndef APPLICATIONFACADE_H
#define APPLICATIONFACADE_H

#include <qextPatternFacade.h>

class ApplicationFacade : public QExtPatternFacade
{
public:
    ApplicationFacade();

protected:
    void initializeMediator();
    void initializeCommand();
    void initializeProxy();
};

#endif // APPLICATIONFACADE_H
