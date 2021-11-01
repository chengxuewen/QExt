#ifndef QTKHELLOSERVICE_H
#define QTKHELLOSERVICE_H

#include "qtkhello_global.h"

#include <QtPlugin>

const char QTK_HELLO_SERVICE_HELLO_STRING[] = "Hello World!";

class QTK_HELLO_EXPORT QTKHelloService
{
public:
    QTKHelloService() {}
    virtual ~QTKHelloService() {}

    virtual QString sayHello() = 0;
};

Q_DECLARE_INTERFACE(QTKHelloService, "org.qtk.service.demos.HelloService")

#endif // QTKHELLOSERVICE_H
