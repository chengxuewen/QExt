#ifndef _QEXTPLOTCURVE_H
#define _QEXTPLOTCURVE_H

#include <qextPlotGlobal.h>

#include <qwt_plot_curve.h>

class QExtPlotCurve : public QwtPlotCurve
{
public:
    explicit QExtPlotCurve(const QString &title = QString());
    explicit QExtPlotCurve(const QwtText &title );
    ~QExtPlotCurve() QEXT_OVERRIDE;

private:
    QEXT_DISABLE_COPY_MOVE(QExtPlotCurve)
};

#endif // _QEXTPLOTCURVE_H
