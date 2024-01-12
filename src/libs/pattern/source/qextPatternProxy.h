#ifndef _QEXTPATTERNPROXY_H
#define _QEXTPATTERNPROXY_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>
#include <qextPatternNotifier.h>

#include <QString>

class QExtPatternUpdateDataInterface;

class QEXT_PATTERN_API QExtPatternProxy : public QExtPatternProxyInterface, public QExtPatternNotifier
{
public:
    QString getProxyName();

/*protected:
    bool registerUpdateData(const QString &registerDataType, QExtPatternUpdateDataInterface *updateData);*/

protected:
    static QString PROXY_NAME;
};

#endif // _QEXTPATTERNPROXY_H
