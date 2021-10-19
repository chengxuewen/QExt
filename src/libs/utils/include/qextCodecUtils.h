#ifndef QEXTCODECUTILS_H
#define QEXTCODECUTILS_H

#include <qextUtilsGlobal.h>

#include <QObject>

class QEXT_UTILS_API QEXTCodecUtils
{
public:
    QEXTCodecUtils();
    virtual ~QEXTCodecUtils() {}

    static bool isHexChar(char value);
    static bool isHexString(void *value, size_t len);
    static bool isHexString(const QString &string);
    static char hexCharToHexCode(char value);
    static QByteArray hexStringToHexCode(void *value, size_t len);
    static QByteArray hexStringToHexCode(const QString &string);

    static QString hexCodeToHexString(void *value, size_t len);
    static QString hexCodeToHexString(const QByteArray &data);

};

#endif // QEXTCODECUTILS_H
