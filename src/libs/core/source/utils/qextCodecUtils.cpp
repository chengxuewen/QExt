#include <qextCodecUtils.h>

#include <QDebug>

QExtCodecUtils::QExtCodecUtils()
{
}

bool QExtCodecUtils::isHexCode(char value)
{
    return value >= 0 && value <= 15;
}

bool QExtCodecUtils::isHexChar(char value)
{
    return (value >= '0' && value <= '9') || (value >= 'a' && value <= 'f') || (value >= 'A' && value <= 'F');
}

bool QExtCodecUtils::isHexString(const char *chs, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (!QExtCodecUtils::isHexChar(chs[i]))
        {
            return false;
        }
    }
    return true;
}

bool QExtCodecUtils::isHexString(const QString &string)
{
    for (int i = 0; i < string.size(); ++i)
    {
        char ch = string.at(i).toLower().toLatin1();
        if (!QExtCodecUtils::isHexChar(ch))
        {
            return false;
        }
    }
    return true;
}

char QExtCodecUtils::hexCharToHexCode(char value, bool *ok)
{
    if (ok)
    {
        *ok = true;
    }
    if (value >= '0' && value <= '9')
    {
        return value - '0';
    }
    else if (value >= 'a' && value <= 'f')
    {
        return value - 'a' + 10;
    }
    else if (value >= 'A' && value <= 'F')
    {
        return value - 'A' + 10;
    }
    else
    {
        if (ok)
        {
            *ok = false;
        }
        return -1;
    }
}

QByteArray QExtCodecUtils::hexStringToHexByteArray(const char *chs, size_t len, bool *ok)
{
    if (ok)
    {
        *ok = false;
    }

    /*len must be even*/
    if (len % 2 != 0)
    {
        return QByteArray();
    }

    QByteArray hexByteArray;
    for (size_t i = 0; i < len / 2; ++i)
    {
        char chH = QChar(chs[i * 2]).toLower().toLatin1();
        char chL = QChar(chs[i * 2 + 1]).toLower().toLatin1();
        bool chHOk = true;
        bool chLOk = true;
        chH = QExtCodecUtils::hexCharToHexCode(chH, &chHOk);
        chL = QExtCodecUtils::hexCharToHexCode(chL, &chLOk);
        if (!chHOk || !chLOk)
        {
            return QByteArray();
        }
        char byte = (chH << 4) + chL;
        hexByteArray.append(byte);
    }

    if (ok)
    {
        *ok = true;
    }
    return hexByteArray;
}

QByteArray QExtCodecUtils::hexStringToHexByteArray(const QString &string, bool *ok)
{
    if (ok)
    {
        *ok = false;
    }

    /*len must be even*/
    if (string.size() % 2 != 0)
    {
        return QByteArray();
    }

    QByteArray hexByteArray;
    for (int i = 0; i < string.size() / 2; ++i)
    {
        char chH = string.at(i * 2).toLower().toLatin1();
        char chL = string.at(i * 2 + 1).toLower().toLatin1();
        bool chHOk = true;
        bool chLOk = true;
        chH = QExtCodecUtils::hexCharToHexCode(chH, &chHOk);
        chL = QExtCodecUtils::hexCharToHexCode(chL, &chLOk);
        if (!chHOk || !chLOk)
        {
            return QByteArray();
        }
        char byte = (chH << 4) + chL;
        hexByteArray.append(byte);
    }

    if (ok)
    {
        *ok = true;
    }
    return hexByteArray;
}

char QExtCodecUtils::hexCodeToHexChar(char value, bool *ok)
{
    if (ok)
    {
        *ok = true;
    }
    if (value >= 0 && value <= 9)
    {
        return value + '0';
    }
    else if (value >= 10 && value <= 15)
    {
        return value + 'a' - 10;
    }
    else
    {
        if (ok)
        {
            *ok = false;
        }
        return -1;
    }
}

QString QExtCodecUtils::hexByteArrayToHexString(const char *chs, size_t len)
{
    QString hexString;
    for (size_t i = 0; i < len; ++i)
    {
        char chH = (chs[i] >> 4) & 0x0f;
        char chL = chs[i] & 0x0f;
        hexString.append(QString::number(chH, 16));
        hexString.append(QString::number(chL, 16));
    }
    return hexString;
}

QString QExtCodecUtils::hexByteArrayToHexString(const QByteArray &value)
{
    QString hexString;
    for (int i = 0; i < value.size(); ++i)
    {
        char ch = value.at(i);
        char chH = (ch >> 4) & 0x0f;
        char chL = ch & 0x0f;
        hexString.append(QString::number(chH, 16));
        hexString.append(QString::number(chL, 16));
    }
    return hexString;
}

QString QExtCodecUtils::hexUInt8ToHexString(uint8_t value)
{
    static const size_t len = sizeof(uint8_t);
    char chs[len];
    memcpy(chs, &value, len);
    QString hexString;
    for (size_t i = 0; i < len; ++i)
    {
        char chH = (chs[i] >> 4) & 0x0f;
        char chL = chs[i] & 0x0f;
        hexString.prepend(QString::number(chL, 16));
        hexString.prepend(QString::number(chH, 16));
    }
    return hexString;
}

QString QExtCodecUtils::hexUInt16ToHexString(uint16_t value)
{
    static const size_t len = sizeof(uint16_t);
    char chs[len];
    memcpy(chs, &value, len);
    QString hexString;
    for (size_t i = 0; i < len; ++i)
    {
        char chH = (chs[i] >> 4) & 0x0f;
        char chL = chs[i] & 0x0f;
        hexString.prepend(QString::number(chL, 16));
        hexString.prepend(QString::number(chH, 16));
    }
    return hexString;
}

QString QExtCodecUtils::hexUInt32ToHexString(uint32_t value)
{
    static const size_t len = sizeof(uint32_t);
    char chs[len];
    memcpy(chs, &value, len);
    QString hexString;
    for (size_t i = 0; i < len; ++i)
    {
        char chH = (chs[i] >> 4) & 0x0f;
        char chL = chs[i] & 0x0f;
        hexString.prepend(QString::number(chL, 16));
        hexString.prepend(QString::number(chH, 16));
    }
    return hexString;
}

QString QExtCodecUtils::hexUInt64ToHexString(uint64_t value)
{
    static const size_t len = sizeof(uint64_t);
    char chs[len];
    memcpy(chs, &value, len);
    QString hexString;
    for (size_t i = 0; i < len; ++i)
    {
        char chH = (chs[i] >> 4) & 0x0f;
        char chL = chs[i] & 0x0f;
        hexString.prepend(QString::number(chL, 16));
        hexString.prepend(QString::number(chH, 16));
    }
    return hexString;
}

uint8_t QExtCodecUtils::hexByteArrayToUInt8(const char *chs, size_t len)
{
    uint8_t intValue = 0;
    size_t intSize = sizeof(uint8_t);
    uint8_t *ui8s = (uint8_t *) &intValue;
    size_t minLen = qMin(len, intSize);
    for (size_t i = 0; i < minLen; ++i)
    {
        ui8s[i] = chs[len - 1 - i];
    }
    return intValue;
}

uint8_t QExtCodecUtils::hexByteArrayToUInt8(const QByteArray &value)
{
    return QExtCodecUtils::hexByteArrayToUInt8(const_cast<char *>(value.data()), value.size());
}

uint16_t QExtCodecUtils::hexByteArrayToUInt16(const char *chs, size_t len)
{
    uint16_t intValue = 0;
    size_t intSize = sizeof(uint16_t);
    uint8_t *ui8s = (uint8_t *) &intValue;
    size_t minLen = qMin(len, intSize);
    for (size_t i = 0; i < minLen; ++i)
    {
        ui8s[i] = chs[len - 1 - i];
    }
    return intValue;
}

uint16_t QExtCodecUtils::hexByteArrayToUInt16(const QByteArray &value)
{
    return QExtCodecUtils::hexByteArrayToUInt16(const_cast<char *>(value.data()), value.size());
}

uint32_t QExtCodecUtils::hexByteArrayToUInt32(const char *chs, size_t len)
{
    uint32_t intValue = 0;
    size_t intSize = sizeof(uint32_t);
    uint8_t *ui8s = (uint8_t *) &intValue;
    size_t minLen = qMin(len, intSize);
    for (size_t i = 0; i < minLen; ++i)
    {
        ui8s[i] = chs[len - 1 - i];
    }
    return intValue;
}

uint32_t QExtCodecUtils::hexByteArrayToUInt32(const QByteArray &value)
{
    return QExtCodecUtils::hexByteArrayToUInt32(const_cast<char *>(value.data()), value.size());
}

uint64_t QExtCodecUtils::hexByteArrayToUInt64(const char *chs, size_t len)
{
    uint64_t intValue = 0;
    size_t intSize = sizeof(uint64_t);
    uint8_t *ui8s = (uint8_t *) &intValue;
    size_t minLen = qMin(len, intSize);
    for (size_t i = 0; i < minLen; ++i)
    {
        ui8s[i] = chs[len - 1 - i];
    }
    return intValue;
}

uint64_t QExtCodecUtils::hexByteArrayToUInt64(const QByteArray &value)
{
    return QExtCodecUtils::hexByteArrayToUInt64(const_cast<char *>(value.data()), value.size());
}
