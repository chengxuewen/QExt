#ifndef QEXTWAVECHART_P_H
#define QEXTWAVECHART_P_H

#include <qextWidgetGlobal.h>
#include <qextObject_p.h>

#include <QRectF>
#include <QColor>
#include <QVector>
#include <QPainterPath>

class QEXT_WIDGET_API QEXTSmoothCurveCreator
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
class QEXT_WIDGET_API QEXTWaveChartPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTWaveChartPrivate(QEXTWaveChart *qq);
    ~QEXTWaveChartPrivate();

    QRectF m_plotAreaRect;               //绘制数据区域
    QVector<double> m_dataList;       //数据集合

    double m_minValue;                //最小值
    double m_maxValue;                //最大值
    double m_yAxisStep;
    double m_xAxisStep;
    double m_hLineStep;
    double m_vLineStep;

    double m_space;                   //间隔
    QString m_title;                  //标题
    bool m_smooth;                    //是否平滑
    bool m_titleVisiable;
    bool m_hLineVisiable;
    bool m_vLineVisiable;
    bool m_pointVisiable;                 //是否显示坐标点
    bool m_pointBackgroundVisiable;               //是否显示坐标背景

    QColor m_backgroundStartColor;            //背景渐变开始颜色
    QColor m_backgroundEndColor;              //背景渐变结束颜色
    QColor m_textColor;               //文字颜色
    QColor m_pointColor;              //坐标点颜色

private:
    QEXT_DECL_PUBLIC(QEXTWaveChart)
    QEXT_DISABLE_COPY_MOVE(QEXTWaveChartPrivate)
};


#endif // QEXTWAVECHART_P_H
