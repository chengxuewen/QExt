#include <qextStringUtils.h>

QString QExtStringUtils::toUnicodesString(const QString &string)
{
    QString hexString;
    for (int i = 0; i < string.size(); ++i)
    {
        if (0 != i)
        {
            hexString.append(",");
        }
        hexString.append(QString::number(string.at(i).unicode()));
    }
    return hexString;
}

QString QExtStringUtils::fromUnicodesString(const QString &string)
{
    bool ok = true;
    QString rawString;
    const auto hexStrings = string.split(",");
    for (auto &&hexString : hexStrings)
    {
        auto unicode = hexString.toUShort(&ok);
        if (ok)
        {
            rawString.append(QChar(unicode));
        }
    }
    return rawString;
}
