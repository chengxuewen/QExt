#ifndef _QEXTGAUGECAR_P_H
#define _QEXTGAUGECAR_P_H

#include <qextWidgetGlobal.h>
#include <qextCircleGauge.h>

#include <QColor>
#include <QPropertyAnimation>

class QEXTCircleGauge;
class QEXT_WIDGETS_API QEXTCircleGaugePrivate
{
public:
    explicit QEXTCircleGaugePrivate(QEXTCircleGauge *q);
    virtual ~QEXTCircleGaugePrivate();

    QEXTCircleGauge * const q_ptr;

    double m_minValue;                //最小值
    double m_maxValue;                //最大值
    double m_value;                   //目标值
    int m_precision;                  //精确度,小数点后几位

    int m_scaleMajor;                 //大刻度数量
    int m_scaleMinor;                 //小刻度数量
    int m_startAngle;                 //开始旋转角度
    int m_endAngle;                   //结束旋转角度

    QColor m_outerCircleColor;        //外圆背景颜色
    QColor m_innerCircleColor;        //内圆背景颜色

    QColor m_pieColorStart;           //饼圆开始颜色
    QColor m_pieColorMid;             //饼圆中间颜色
    QColor m_pieColorEnd;             //饼圆结束颜色

    QColor m_coverCircleColor;        //覆盖圆背景颜色
    QColor m_scaleColor;              //刻度尺颜色
    QColor m_pointerColor;            //指针颜色
    QColor m_centerCircleColor;       //中心圆颜色
    QColor m_textColor;               //文字颜色

    bool m_overlayVisiable;               //显示遮罩层
    QColor m_overlayColor;            //遮罩层颜色

    int m_circleWidth;                //中间圆宽度
    QEXTCircleGauge::PieStyleType m_pieStyle;              //饼图样式
    QEXTCircleGauge::PointerStyleType m_pointerStyle;      //指针样式

    double m_currentValue;                  //当前值
    bool m_animationEnable;                 //是否启用动画显示
    QPropertyAnimation *m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTCircleGaugePrivate)
    Q_DECLARE_PUBLIC(QEXTCircleGauge)
};

#endif // _QEXTGAUGECAR_P_H
