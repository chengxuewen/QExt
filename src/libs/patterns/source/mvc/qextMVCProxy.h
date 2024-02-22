#ifndef _QEXTMVCPROXY_H
#define _QEXTMVCPROXY_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>
#include <qextMVCNotifier.h>

#include <QString>

class QExtMVCUpdateDataInterface;

class QEXT_PATTERNS_API QExtMVCProxy : public QExtMVCProxyInterface, public QExtMVCNotifier
{
public:
    QString getProxyName();

/*protected:
    bool registerUpdateData(const QString &registerDataType, QExtMVCUpdateDataInterface *updateData);*/

protected:
    static QString PROXY_NAME;
};

#endif // _QEXTMVCPROXY_H
