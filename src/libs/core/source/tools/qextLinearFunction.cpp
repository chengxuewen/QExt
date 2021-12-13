#include <qextLinearFunction.h>

#include <algorithm>
#include <cmath>

class QEXTLinearFunctionPrivate
{
    Q_DECLARE_PUBLIC(QEXTLinearFunction)
    Q_DISABLE_COPY(QEXTLinearFunctionPrivate)
public:
    explicit QEXTLinearFunctionPrivate(QEXTLinearFunction *q);
    virtual ~QEXTLinearFunctionPrivate() {}

    QEXTLinearFunction * const q_ptr;

    double m_k;
    double m_c;
    bool m_isVLine;
    bool m_isHLine;
};


QEXTLinearFunctionPrivate::QEXTLinearFunctionPrivate(QEXTLinearFunction *q)
    : q_ptr(q)
{

}

QEXTLinearFunction::QEXTLinearFunction(double x1, double y1, double x2, double y2)
    : dd_ptr(new QEXTLinearFunctionPrivate(this))
{
    dd_ptr->m_isVLine = (x1 == x2) ? true : false;
    dd_ptr->m_isHLine = (y1 == y2) ? true : false;
    if (dd_ptr->m_isHLine && dd_ptr->m_isVLine)
    {
        throw QString("QEXTLinearFunction():point1 == point2, point1 can not equal to point2!");
    }
    dd_ptr->m_k = (y1 - y2) / (x1 - x2);
    dd_ptr->m_c = (y1 * x2 - y2 * x1) / (x2 - x1);
}

QEXTLinearFunction::QEXTLinearFunction(double x, double y, double k)
    : dd_ptr(new QEXTLinearFunctionPrivate(this))
{
    dd_ptr->m_isHLine = (0 == k) ? true : false;
    dd_ptr->m_isVLine = false;
    dd_ptr->m_k = k;
    dd_ptr->m_c = y - x * dd_ptr->m_k;
}

QEXTLinearFunction::QEXTLinearFunction(const QEXTLinearFunction &other)
    : dd_ptr(new QEXTLinearFunctionPrivate(this))
{
    dd_ptr->m_isHLine = other.d_func()->m_isHLine;
    dd_ptr->m_isVLine = other.d_func()->m_isVLine;
    dd_ptr->m_k = other.d_func()->m_k;
    dd_ptr->m_c = other.d_func()->m_c;
}

QEXTLinearFunction::~QEXTLinearFunction()
{

}

bool QEXTLinearFunction::operator==(const QEXTLinearFunction &other) const
{
    Q_D(const QEXTLinearFunction);
    if (d->m_isHLine == other.d_func()->m_isHLine)
    {
        if (d->m_isVLine == other.d_func()->m_isVLine)
        {
            return (d->m_k == other.d_func()->m_k) && (d->m_c == other.d_func()->m_c);
        }
    }
    return false;
}

bool QEXTLinearFunction::operator!=(const QEXTLinearFunction &other) const
{
    return !(*this == other);
}

QEXTLinearFunction &QEXTLinearFunction::operator=(const QEXTLinearFunction &other)
{
    if (this != &other)
    {
        Q_D(QEXTLinearFunction);
        d->m_isHLine = other.d_func()->m_isHLine;
        d->m_isVLine = other.d_func()->m_isVLine;
        d->m_k = other.d_func()->m_k;
        d->m_c = other.d_func()->m_c;
    }
    return *this;
}

double QEXTLinearFunction::distance(double x1, double y1, double x2, double y2)
{
    if (x1 == x2)
    {
        return std::abs(y1 - y2);
    }
    else if (y1 == y2)
    {
        return std::abs(x1 - x2);
    }
    else
    {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }
}

double QEXTLinearFunction::x(double y) const
{
    Q_D(const QEXTLinearFunction);
    if (d->m_isHLine)
    {
        throw QString("STLinearFunction::xValue():linear IsHLine,can not find x data");
        return 0;
    }
    else if (d->m_isVLine)
    {
        throw QString("STLinearFunction::xValue():linear IsVLine,can not find x data");
        return 0;
    }
    else
    {
        return (y - d->m_c) / d->m_k;
    }
}

double QEXTLinearFunction::y(double x) const
{
    Q_D(const QEXTLinearFunction);
    return d->m_k * x + d->m_c;
}

double QEXTLinearFunction::c() const
{
    Q_D(const QEXTLinearFunction);
    return d->m_c;
}

double QEXTLinearFunction::k() const
{
    Q_D(const QEXTLinearFunction);
    return d->m_k;
}

bool QEXTLinearFunction::isHorizontalLine() const
{
    Q_D(const QEXTLinearFunction);
    return d->m_isHLine;
}

bool QEXTLinearFunction::isVerticalLine() const
{
    Q_D(const QEXTLinearFunction);
    return d->m_isVLine;
}

QVector<QPair<double, double> > QEXTLinearFunction::distancePoints(double x, double y, double distance) const
{
    Q_D(const QEXTLinearFunction);
    QVector<QPair<double, double> > points;
    if (d->m_isHLine)
    {
        points.append(QPair<double, double>(x - distance, y));
        points.append(QPair<double, double>(x + distance, y));
    }
    else if (d->m_isVLine)
    {
        points.append(QPair<double, double>(x, y - distance));
        points.append(QPair<double, double>(x, y + distance));
    }
    else
    {
        double a = pow(d->m_k, 2) + 1;     // A=k^2+1
        double b = 2 * ((d->m_c - y) * d->m_k - x);    // B=2[(b-y0)k-x0]
        // C=(b-y0)^2+x0^2-L^2
        double c = pow(d->m_c - y, 2) + pow(x, 2) - pow(distance, 2);
        // x1,x2= [-B±√(B^2-4AC)]/2A
        double x1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
        double x2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
        double y1 = d->m_k * x1 + d->m_c;
        double y2 = d->m_k * x2 + d->m_c;
        points.append(QPair<double, double>(x1, y1));
        points.append(QPair<double, double>(x2, y2));
    }
    return points;
}

bool QEXTLinearFunction::distancePoint(double originX, double originY, double rangeX, double rangeY,
                                     double distance, double &x, double &y) const
{
    QVector<QPair<double, double> > points = this->distancePoints(originX, originY, distance);
    double leftX = std::min(originX, rangeX);
    double rightX = std::max(originX, rangeX);
    double topY = std::min(originY, rangeY);
    double bottomY = std::max(originY, rangeY);
    QVector<QPair<double, double> >::const_iterator iter;
    for (iter = points.begin(); iter != points.end(); ++iter)
    {
        if (iter->first >= leftX && iter->first <= rightX && iter->second >= topY && iter->second <= bottomY)
        {
            x = iter->first;
            y = iter->second;
            return true;
        }
    }
    return false;
}

QEXTLinearFunction QEXTLinearFunction::verticalLinearFunction(double x, double y) const
{
    Q_D(const QEXTLinearFunction);
    if (d->m_isHLine)
    {
        return QEXTLinearFunction(x, y, x, std::abs(y) + 10);
    }
    else if (d->m_isVLine)
    {
        return QEXTLinearFunction(x, y, 0);
    }
    else
    {
        return QEXTLinearFunction(x, y, -1 / d->m_k);
    }
}



