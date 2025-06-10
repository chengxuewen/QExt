#ifndef _QEXTPLOT_P_H
#define _QEXTPLOT_P_H

#include <qextPlot.h>

#include <qwt_text.h>
#include <qwt_plot_grid.h>

class QExtPlotPrivate
{
    QExtPlot * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlot)
    QEXT_DISABLE_COPY_MOVE(QExtPlotPrivate)
public:
    explicit QExtPlotPrivate(QExtPlot *q);
    virtual ~QExtPlotPrivate();

    double mXMin;
    double mXMax;
    double mYMin;
    double mYMax;
    double mPlotWidth;

    QwtPlotGrid mGrid;
};

#endif // _QEXTPLOT_P_H
