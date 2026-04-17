#ifndef _QEXTQUICKQWTPLOTCURVE_P_H
#define _QEXTQUICKQWTPLOTCURVE_P_H

#include <qextQuickQwtPlotCurve.h>
#include <private/qextQuickQwtSeriesData_p.h>

#include <qwt_plot_curve.h>

#include <QPointer>

class QExtQuickQwtPlotCurvePrivate
{
public:
    using Style = QExtQuickQwtPlotCurve::Style;
    using Attribute = QExtQuickQwtPlotCurve::Attribute;
    using RenderHint = QExtQuickQwtPlotCurve::RenderHint;

    explicit QExtQuickQwtPlotCurvePrivate(QExtQuickQwtPlotCurve *q);
    virtual ~QExtQuickQwtPlotCurvePrivate();

    static Style fromQwt(QwtPlotCurve::CurveStyle style);
    static RenderHint fromQwt(QwtPlotCurve::RenderHint hint);
    static Attribute fromQwt(QwtPlotCurve::CurveAttribute attribute);

    static QwtPlotCurve::CurveStyle toQwt(Style style);
    static QwtPlotCurve::RenderHint toQwt(RenderHint hint);
    static QwtPlotCurve::CurveAttribute toQwt(Attribute attribute);

    QExtQmlPenInfo mQExtQmlPenInfo;
    QPointer<QExtQuickQwtPlot> mQwtPlot;
    QScopedPointer<QwtPlotCurve> mQwtPlotCurve{new QwtPlotCurve};

protected:
    QExtQuickQwtPlotCurve * const q_ptr;
    Q_DECLARE_PUBLIC(QExtQuickQwtPlotCurve)
    Q_DISABLE_COPY(QExtQuickQwtPlotCurvePrivate)
};

#endif // _QEXTQUICKQWTPLOTCURVE_P_H
