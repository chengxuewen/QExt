#include <qextMVCProxy.h>
#include <qextMVCInterface.h>

QString QExtMVCProxy::PROXY_NAME = "Proxy";

QString QExtMVCProxy::getProxyName()
{
    return PROXY_NAME;
}

/*bool Proxy::registerUpdateData(const QString &registerDataType, QExtMVCUpdateDataInterface *updateData)
{

    updateData->setType(registerDataType);
}*/
