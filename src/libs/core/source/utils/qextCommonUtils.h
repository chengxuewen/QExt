#ifndef _QEXTCOMMONUTILS_H
#define _QEXTCOMMONUTILS_H

#include <qextGlobal.h>

#include <QStandardPaths>

class QEXT_CORE_API QExtCommonUtils
{
public:
    QExtCommonUtils();
    virtual ~QExtCommonUtils() {}

    static qint64 applicationPid();
    static qint64 applicationTid();
    static QString executableDir();
    static QString executablePath();

    static QString writableLocation(QStandardPaths::StandardLocation location);
    static QString appDataLocation() { return QExtCommonUtils::writableLocation(QStandardPaths::AppDataLocation); }
    static QString appConfigLocation() { return QExtCommonUtils::writableLocation(QStandardPaths::AppConfigLocation); }
};

#endif // _QEXTCOMMONUTILS_H
