#include <qextPatternProxy.h>
#include <qextPatternInterface.h>

QString QExtPatternProxy::PROXY_NAME = "Proxy";

QString QExtPatternProxy::getProxyName()
{
    return PROXY_NAME;
}

/*bool Proxy::registerUpdateData(const QString &registerDataType, QExtPatternUpdateDataInterface *updateData)
{

    updateData->setType(registerDataType);
}*/
