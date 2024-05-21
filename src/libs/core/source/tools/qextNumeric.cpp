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
