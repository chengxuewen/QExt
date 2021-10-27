#ifndef _QEXTLINEARFUNCTION_H
#define _QEXTLINEARFUNCTION_H

#include <qextGlobal.h>

#include <QObject>
#include <QScopedPointer>

#include <cmath>
#include <list>
#include <string>
#include <vector>
#include <utility>

class QEXTLinearFunctionPrivate;
class QEXT_CORE_API QEXTLinearFunction
{
public:
    QEXTLinearFunction(double x1, double y1, double x2, double y2);
    QEXTLinearFunction(double x, double y, double k);
    QEXTLinearFunction(const QEXTLinearFunction &other);
    ~QEXTLinearFunction();

    bool operator==(const QEXTLinearFunction &other) const;
    bool operator!=(const QEXTLinearFunction &other) const;
    QEXTLinearFunction &operator=(const QEXTLinearFunction &other);

    double x(double y) const;
    double y(double x) const;
    double c() const;
    double k() const;
    bool isHorizontalLine() const;
    bool isVerticalLine() const;

    std::vector<std::pair<double, double> > distancePoints(double x, double y, double distance) const;

    bool distancePoint(double originX, double originY, double rangeX, double rangeY,
                       double distance, double &x, double &y) const;

    QEXTLinearFunction verticalLinearFunction(double x, double y) const;

    static double distance(double x1, double y1, double x2, double y2);

protected:
    QScopedPointer<QEXTLinearFunctionPrivate> d_ptr;

private:
    QEXT_DECL_PRIVATE(QEXTLinearFunction)
};



#endif // _QEXTLINEARFUNCTION_H
