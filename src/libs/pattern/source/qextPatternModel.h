#ifndef _QEXTPATTERNMODEL_H
#define _QEXTPATTERNMODEL_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>

#include <QMap>
#include <QString>

class QEXT_PATTERN_API QExtPatternModel : public QExtPatternModelInterface
{
public:
    static QExtPatternModel *instance();

    void registerProxy(QExtPatternProxyInterface *proxy);

    QExtPatternProxyInterface *retrieveProxy(const QString &proxyName);

    bool hasProxy(const QString &proxyName);

    void removeProxy(const QString &proxyName);

private:
    QExtPatternModel();

private:
    QMap<QString, QExtPatternProxyInterface *> m_proxyMap;
    static QExtPatternModel *m_instance;
};

#endif // _QEXTPATTERNMODEL_H
