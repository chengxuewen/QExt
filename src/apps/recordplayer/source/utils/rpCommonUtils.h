#ifndef _RPCOMMONUTILS_H
#define _RPCOMMONUTILS_H

#include <QObject>
#include <QStandardPaths>

#include <rpConstants.h>

struct RPCommonUtils
{
    static QString toUnicodeHexString(const QString &string);
    static QString fromUnicodeHexString(const QString &string);

    static double reducePrecision(double dVal, short iPlaces);
    static QString doubleFixedString(double value, int precision = 6);

    static bool isValueEqual(double val1, double val2);

    static QString writableLocation(QStandardPaths::StandardLocation location);
    static QString appDataLocation() { return RPCommonUtils::writableLocation(QStandardPaths::AppDataLocation); }
    static QString appConfigLocation() { return RPCommonUtils::writableLocation(QStandardPaths::AppConfigLocation); }
};

#endif // _RPCOMMONUTILS_H
