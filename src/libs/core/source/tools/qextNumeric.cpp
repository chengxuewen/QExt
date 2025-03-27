#include <qextNumeric.h>

#include <cmath>
#include <QDebug>
#include <QLocale>

QExtNumeric::QExtNumeric()
{
}

double QExtNumeric::reducePrecision(double value, short places)
{
    const double scale = std::pow(10.0, places);
    return std::round(value * scale) / scale;
}

QString QExtNumeric::doubleTrimmedText(const QString &text)
{
    int index = text.size();
    for (QString::const_reverse_iterator iter = text.rbegin(); iter != text.rend(); ++iter)
    {
        if ('0' != *iter)
        {
            if ((*iter < 48) || (*iter > 57))
            {
                index--;
            }
            break;
        }
        index--;
    }
    // qDebug() << "text=" << text << ", left:" << text.left(index) << ", index=" << index;
    return text.left(index);
}

QString QExtNumeric::doubleTrimmedText(double value, int precision)
{
    const QString text = QLocale::system().toString(value, 'f', precision).trimmed();
    return QExtNumeric::doubleTrimmedText(text);
}
