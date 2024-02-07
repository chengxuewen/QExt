#ifndef _QEXTCODECUTILS_H
#define _QEXTCODECUTILS_H

#include <qextGlobal.h>

#include <QObject>

#include <stdint.h>

class QEXT_CORE_API QExtCodecUtils
{
public:
    QExtCodecUtils();
    virtual ~QExtCodecUtils() {}

    static bool isHexCode(char value);
    static bool isHexChar(char value);
    static bool isHexString(const char *chs, size_t len);
    static bool isHexString(const QString &string);

    static char hexCharToHexCode(char value, bool *ok = QEXT_NULLPTR);
    static QByteArray hexStringToHexByteArray(const char *chs, size_t len, bool *ok = QEXT_NULLPTR);
    static QByteArray hexStringToHexByteArray(const QString &string, bool *ok = QEXT_NULLPTR);

    static char hexCodeToHexChar(char value, bool *ok = QEXT_NULLPTR);
    static QString hexByteArrayToHexString(const char *chs, size_t len);
    static QString hexByteArrayToHexString(const QByteArray &value);
    static QString hexUInt8ToHexString(uint8_t value);
    static QString hexUInt16ToHexString(uint16_t value);
    static QString hexUInt32ToHexString(uint32_t value);
    static QString hexUInt64ToHexString(uint64_t value);

    static uint8_t hexByteArrayToUInt8(const char *chs, size_t len);
    static uint8_t hexByteArrayToUInt8(const QByteArray &value);
    static uint16_t hexByteArrayToUInt16(const char *chs, size_t len);
    static uint16_t hexByteArrayToUInt16(const QByteArray &value);
    static uint32_t hexByteArrayToUInt32(const char *chs, size_t len);
    static uint32_t hexByteArrayToUInt32(const QByteArray &value);
    static uint64_t hexByteArrayToUInt64(const char *chs, size_t len);
    static uint64_t hexByteArrayToUInt64(const QByteArray &value);


};

#endif // _QEXTCODECUTILS_H
