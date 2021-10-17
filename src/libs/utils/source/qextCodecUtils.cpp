#include <qextCodecUtils.h>

#include <QDebug>

QEXTCodecUtils::QEXTCodecUtils()
{

}

bool QEXTCodecUtils::isHexStringValid(const QString &string)
{
    for (int i = 0; i < string.size(); ++i)
    {
        char ch = string.at(i).toLower().toLatin1();
        bool isDigital = (ch >= '0' && ch <= '9');
        bool isLetter = (ch >= 'a' && ch <= 'f');
        if (!isDigital && !isLetter)
        {
            return false;
        }
    }
    return true;
}

QByteArray QEXTCodecUtils::hexStringToHexCode(const QString &string)
{
    QByteArray byteArray;
    if (QEXTCodecUtils::isHexStringValid(string))
    {
        for (int i = 0; i < string.size(); ++i)
        {
            QChar qChar = string.at(i).toLower();
            char ch = qChar.toLatin1();
            if (ch >= '0' && ch <= '9')
            {
                byteArray.append(ch - '0');
            }
            else if (ch >= 'a' && ch <= 'f')
            {
                byteArray.append(ch - 'a' + 10);
            }
            else
            {
                qCritical() << "QEXTCodecUtils::hexStringToHex():char invalid";
            }
        }
    }
    return byteArray;
}

QString QEXTCodecUtils::hexCodeToHexString(const QByteArray &data)
{
    QString string;
    for (int i = 0; i < data.size(); ++i)
    {
        int value = data.at(i);
        if (value >= 0 && value <= 15)
        {
            string.append(QString::number(value, 16));
        }
        else
        {
            string.append("x");
        }
    }
    return string;
}
