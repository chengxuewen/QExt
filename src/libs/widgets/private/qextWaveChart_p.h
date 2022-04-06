#ifndef _QEXTWAVECHART_P_H
#define _QEXTWAVECHART_P_H

#include <qextWidgetGlobal.h>

#include <QRectF>
#include <QColor>
#include <QVector>
#include <QPainterPath>

class QEXT_WIDGETS_API QEXTSmoothCurveCreator
{
public:
    static QPainterPath createSmoothCurve(const QVector<QPointF> &points);

private:
    static void calculateFirstControlPoints(double *&result, const double *rhs, int n);
    static void calculateControlPoints(const QVector<QPointF> &knots,
                                       QVector<QPointF> *firstControlPoints,
                                       QVector<QPointF> *secondControlPoints);
};

class QEXTWaveChart;
class QEXT_WIDGETS_API QEXTWaveChartPrivate
{
public:
    explicit QEXTWaveChartPrivate(QEXTWaveChart *q);
    virtual ~QEXTWaveChartPrivate();

    QEXTWaveChart * const q_ptr;

    QRectF m_plotAreaRect;
    QVector<double> m_dataList;

    double m_minValue;
    double m_maxValue;
    double m_yAxisStep;
    double m_xAxisStep;
    double m_hLineStep;
    double m_vLineStep;

    double m_space;
    QString m_title;
    bool m_smooth;
    bool m_titleVisible;
    bool m_hLineVisible;
    bool m_vLineVisible;
    bool m_pointVisible;
    bool m_pointBackgroundVisible;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;
    QColor m_textColor;
    QColor m_pointColor;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTWaveChartPrivate)
    QEXT_DECL_PUBLIC(QEXTWaveChart)
};


#endif // _QEXTWAVECHART_P_H
