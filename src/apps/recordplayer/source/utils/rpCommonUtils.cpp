#include <rpCommonUtils.h>

#include <QCryptographicHash>
#include <QCoreApplication>
#include <QEvent>
#include <QDebug>
#include <QDir>

#include <math.h>

QString RPCommonUtils::toUnicodeHexString(const QString &string)
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

QString RPCommonUtils::fromUnicodeHexString(const QString &string)
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

double RPCommonUtils::reducePrecision(double value, short places)
{
    double dRetval = value;
    double dMod = 0.0000001;
    if (value < 0.0)
    {
        dMod = -0.0000001;
    }
    dRetval += (5.0 / pow(10.0, places + 1.0));
    dRetval *= pow(10.0, places);
    dRetval = floor(dRetval + dMod);
    dRetval /= pow(10.0, places);
    return (dRetval);
}

QString RPCommonUtils::doubleFixedString(double value, int precision)
{
    QString valueText = std::move(QString::number(value, 'f', precision));
    auto index = valueText.size();
    for (auto iter = valueText.rbegin(); iter != valueText.rend(); ++iter)
    {
        // qDebug() << "ch=" << *iter;
        if ('0' != *iter)
        {
            if ('.' == *iter)
            {
                index--;
            }
            break;
        }
        index--;
    }
    // qDebug() << "valueText=" << valueText.left(index) << ", index=" << index;
    return valueText.left(index);
}

bool RPCommonUtils::isValueEqual(double val1, double val2)
{
    return std::abs(val1 - val2) < std::numeric_limits<double>::epsilon();
}

QString RPCommonUtils::writableLocation(QStandardPaths::StandardLocation location)
{
    QString locationPath;
    QString rootPath = QStandardPaths::writableLocation(location);
    QString execPath = QCoreApplication::applicationDirPath();
    // get MD5 code
    QString md5String = QCryptographicHash::hash(execPath.toUtf8(), QCryptographicHash::Md5).toHex();
    locationPath = rootPath + "/" + md5String;
    // fprintf(stderr, "%s\n", locationPath.toLatin1().data());
    QDir dir(locationPath);
    if (!dir.exists())
    {
        if (!dir.mkpath(locationPath))
        {
            qFatal("mkdir %s failed!", locationPath.toLatin1().data());
        }
    }
    QFile noteFile(locationPath + "/note.txt");
    if (noteFile.open(QFile::WriteOnly))
    {
        QTextStream stream(&noteFile);
        stream << execPath;
        noteFile.close();
    }
    return locationPath;
}
