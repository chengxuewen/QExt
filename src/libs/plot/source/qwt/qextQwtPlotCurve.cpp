#include <private/qextQwtPlotCurve_p.h>

QExtPlotCurve::QExtPlotCurve(const QString &title)
    : QwtPlotCurve(title)
{
}

QExtPlotCurve::QExtPlotCurve(const QwtText &title)
    : QwtPlotCurve(title)
{
}

QExtPlotCurve::~QExtPlotCurve()
{
}
