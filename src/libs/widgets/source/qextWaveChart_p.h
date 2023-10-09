/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2022~Present ChengXueWen. Contact: 1398831004@qq.com.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTWAVECHART_P_H
#define _QEXTWAVECHART_P_H

#include <qextWaveChart.h>

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

class QExtWaveChart;
class QEXT_WIDGETS_API QExtWaveChartPrivate
{
public:
    explicit QExtWaveChartPrivate(QExtWaveChart *q);
    virtual ~QExtWaveChartPrivate();

    QExtWaveChart * const q_ptr;

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
    QEXT_DECL_DISABLE_COPY_MOVE(QExtWaveChartPrivate)
    QEXT_DECL_PUBLIC(QExtWaveChart)
};


#endif // _QEXTWAVECHART_P_H
