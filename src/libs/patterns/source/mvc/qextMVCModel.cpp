#include <qextMVCModel.h>
#include <qextMVCInterface.h>

#include <QList>

QExtMVCModel *QExtMVCModel::m_instance = QEXT_NULLPTR;

QExtMVCModel::QExtMVCModel()
{
}

QExtMVCModel *QExtMVCModel::instance()
{
    if (!m_instance)
    {
        m_instance = new QExtMVCModel();
    }

    return m_instance;
}

void QExtMVCModel::registerProxy(QExtMVCProxyInterface *proxy)
{
    if (proxy == NULL)
    {
        return;
    }

    if (hasProxy(proxy->getProxyName()))
    {
        return;
    }

    m_proxyMap[proxy->getProxyName()] = proxy;
}

QExtMVCProxyInterface *QExtMVCModel::retrieveProxy(const QString &proxyName)
{
    if (!hasProxy(proxyName))
    {
        return NULL;
    }

    return m_proxyMap[proxyName];
}

bool QExtMVCModel::hasProxy(const QString &proxyName)
{
    return m_proxyMap.contains(proxyName);
}

void QExtMVCModel::removeProxy(const QString &proxyName)
{
    m_proxyMap.remove(proxyName);
}
