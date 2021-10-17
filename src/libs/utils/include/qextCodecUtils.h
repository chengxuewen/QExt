#ifndef QEXTCODECUTILS_H
#define QEXTCODECUTILS_H

#include <qextUtilsGlobal.h>

#include <QObject>

class QEXT_UTILS_API QEXTCodecUtils
{
public:
    QEXTCodecUtils();
    virtual ~QEXTCodecUtils() {}

    static bool isHexStringValid(const QString &string);
    static QByteArray hexStringToHexCode(const QString &string);
    static QString hexCodeToHexString(const QByteArray &data);
};

#endif // QEXTCODECUTILS_H
