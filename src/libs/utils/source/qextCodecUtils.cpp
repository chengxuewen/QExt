#include <qextCodecUtils.h>

#include <QDebug>

QEXTCodecUtils::QEXTCodecUtils()
{

}

bool QEXTCodecUtils::isHexChar(char value)
{
    return (value >= '0' && value <= '9') || (value >= 'a' && value <= 'f');
}

bool QEXTCodecUtils::isHexString(void *value, size_t len)
{
    char *chs = (char *)value;
    for (size_t i = 0; i < len; ++i)
    {
        if (!QEXTCodecUtils::isHexChar(chs[i]))
        {
            return false;
        }
    }
    return true;
}

bool QEXTCodecUtils::isHexString(const QString &string)
{
    if (string.size() % 2 != 0)
    {
        return false;
    }
    for (size_t i = 0; i < string.size(); ++i)
    {
        char ch = string.at(i).toLower().toLatin1();
        if (!QEXTCodecUtils::isHexChar(ch))
        {
            return false;
        }
    }
    return true;
}

char QEXTCodecUtils::hexCharToHexCode(char value)
{
    if (value >= '0' && value <= '9')
    {
        return value - '0';
    }
    else if (value >= 'a' && value <= 'f')
    {
        return value - 'a' + 10;
    }
    else
    {
        return -1;
    }
}

QByteArray QEXTCodecUtils::hexStringToHexCode(void *value, size_t len)
{
    QByteArray byteArray;
    char *chs = (char *)value;
    if (len % 2 == 0)
    {
        for (size_t i = 0; i < len / 2; ++i)
        {
            char ch1 = QChar(chs[i * 2]).toLower().toLatin1();
            char ch2 = QChar(chs[i * 2 + 1]).toLower().toLatin1();
            ch1 = QEXTCodecUtils::hexCharToHexCode(ch1);
            ch2 = QEXTCodecUtils::hexCharToHexCode(ch2);
            if (ch1 < 0 || ch2 < 0)
            {
                return QByteArray();
            }
            char byte = (ch2 << 4) + ch1;
            byteArray.prepend(byte);
        }
    }
    return byteArray;
}

QByteArray QEXTCodecUtils::hexStringToHexCode(const QString &string)
{
    QByteArray byteArray;
    if (string.size() % 2 == 0)
    {
        for (size_t i = 0; i < string.size() / 2; ++i)
        {
            char ch1 = string.at(i * 2).toLower().toLatin1();
            char ch2 = string.at(i * 2 + 1).toLower().toLatin1();
            ch1 = QEXTCodecUtils::hexCharToHexCode(ch1);
            ch2 = QEXTCodecUtils::hexCharToHexCode(ch2);
            if (ch1 < 0 || ch2 < 0)
            {
                return QByteArray();
            }
            char byte = (ch1 << 4) + ch2;
            byteArray.append(byte);
        }
    }
    return byteArray;
}

QString QEXTCodecUtils::hexCodeToHexString(void *value, size_t len)
{
    QString string;
    char *chs = (char *)value;
    for (size_t i = 0; i < len; ++i)
    {
        char ch1 = chs[i] & 0x0f;
        if (ch1 >= 0 && ch1 <= 15)
        {
            string.prepend(QString::number(ch1, 16));
        }
        else
        {
            string.prepend("x");
        }

        char ch2 = (chs[i] >> 4) & 0x0f;
        if (ch2 >= 0 && ch2 <= 15)
        {
            string.prepend(QString::number(ch2, 16));
        }
        else
        {
            string.prepend("x");
        }
    }
    return string;
}

QString QEXTCodecUtils::hexCodeToHexString(const QByteArray &data)
{
    QString string;
    for (size_t i = 0; i < data.size(); ++i)
    {
        char value = data.at(i);
        char ch1 = (value >> 4) & 0x0f;
        if (ch1 >= 0 && ch1 <= 15)
        {
            string.append(QString::number(ch1, 16));
        }
        else
        {
            string.append("x");
        }

        char ch2 = value & 0x0f;
        if (ch2 >= 0 && ch2 <= 15)
        {
            string.append(QString::number(ch2, 16));
        }
        else
        {
            string.append("x");
        }
    }
    return string;
}
