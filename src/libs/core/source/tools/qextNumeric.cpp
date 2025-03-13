#include <qextNumeric.h>

#include <cmath>
#include <QDebug>

QExtNumeric::QExtNumeric()
{
}

double QExtNumeric::reducePrecision(double value, short places)
{
    const double scale = std::pow(10.0, places);
    return std::round(value * scale) / scale;
}

QString QExtNumeric::doubleFixedString(double value, int precision)
{
    const QString valueText = QString::number(value, 'f', precision);
    int index = valueText.size();
    for (QString::const_reverse_iterator iter = valueText.rbegin(); iter != valueText.rend(); ++iter)
    {
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
    qDebug() << "valueText=" << valueText << ", left:" << valueText.left(index) << ", index=" << index;
    return valueText.left(index);
}
