#ifndef _QEXTMVCMODEL_H
#define _QEXTMVCMODEL_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>

#include <QMap>
#include <QString>

class QEXT_PATTERNS_API QExtMVCModel : public QExtMVCModelInterface
{
public:
    static QExtMVCModel *instance();

    void registerProxy(QExtMVCProxyInterface *proxy);

    QExtMVCProxyInterface *retrieveProxy(const QString &proxyName);

    bool hasProxy(const QString &proxyName);

    void removeProxy(const QString &proxyName);

private:
    QExtMVCModel();

private:
    QMap<QString, QExtMVCProxyInterface *> m_proxyMap;
    static QExtMVCModel *m_instance;
};

#endif // _QEXTMVCMODEL_H
