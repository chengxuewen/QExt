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

    static QString defaultDataLocation();
    static void setDefaultDataLocation(const QString &path);

    static QString defaultConfigLocation();
    static void setDefaultConfigLocation(const QString &path);

    static QString writableLocation(QStandardPaths::StandardLocation location);

    static QString writableUniqueLocation(QStandardPaths::StandardLocation location);
    static QString appUniqueDataLocation()
    {
        return QExtCommonUtils::writableUniqueLocation(QStandardPaths::AppDataLocation);
    }
    static QString appUniqueConfigLocation()
    {
        return QExtCommonUtils::writableUniqueLocation(QStandardPaths::AppConfigLocation);
    }
};

#endif // _QEXTCOMMONUTILS_H
