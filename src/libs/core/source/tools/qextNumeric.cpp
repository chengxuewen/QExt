#include <qextNumeric.h>

#include <cmath>

QExtNumeric::QExtNumeric()
{

}

double QExtNumeric::reducePrecision(double value, short places)
{
    double scale = std::pow(10.0, places);
    return std::round(value * scale) / scale;
}

QString QExtNumeric::doubleFixedString(double value, int precision)
{
    QString valueText = QString::number(value, 'f', precision);
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
