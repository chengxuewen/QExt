#include <qextPatternModel.h>
#include <qextPatternInterface.h>

#include <QList>

QExtPatternModel *QExtPatternModel::m_instance;

QExtPatternModel::QExtPatternModel()
{
}

QExtPatternModel *QExtPatternModel::instance()
{
    if (m_instance == NULL)
    {
        m_instance = new QExtPatternModel();
    }

    return m_instance;
}

void QExtPatternModel::registerProxy(QExtPatternProxyInterface *proxy)
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

QExtPatternProxyInterface *QExtPatternModel::retrieveProxy(const QString &proxyName)
{
    if (!hasProxy(proxyName))
    {
        return NULL;
    }

    return m_proxyMap[proxyName];
}

bool QExtPatternModel::hasProxy(const QString &proxyName)
{
    return m_proxyMap.contains(proxyName);
}

void QExtPatternModel::removeProxy(const QString &proxyName)
{
    m_proxyMap.remove(proxyName);
}
