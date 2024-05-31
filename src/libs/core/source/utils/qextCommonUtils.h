#ifndef _QEXTCOMMONUTILS_H
#define _QEXTCOMMONUTILS_H

#include <qextGlobal.h>

class QEXT_CORE_API QExtCommonUtils
{
public:
    QExtCommonUtils();
    virtual ~QExtCommonUtils() {}

    static qint64 applicationPid();
    static qint64 applicationTid();
    static QString executableDir();
    static QString executablePath();
};

#endif // _QEXTCOMMONUTILS_H
