#include "qtkhelloimpl.h"

#include <QTKPluginFramework/QTKPluginContext>

#include <QDebug>

QTKHelloImpl::QTKHelloImpl(QTKPluginContext *pContext)
{
    pContext->registerService<QTKHelloService>(this);

}

QTKHelloImpl::~QTKHelloImpl()
{

}

QString QTKHelloImpl::sayHello()
{
    QString strText = QTK_HELLO_SERVICE_HELLO_STRING;
    qDebug() << strText;
    return strText;
}
