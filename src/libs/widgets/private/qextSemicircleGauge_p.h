#ifndef _QEXTGAUGESEMICIRCLE_P_H
#define _QEXTGAUGESEMICIRCLE_P_H

#include <qextWidgetGlobal.h>
#include <qextSemicircleGauge.h>

#include <QColor>
#include <QPropertyAnimation>

class QEXTSemicircleGauge;
class QEXT_WIDGETS_API QEXTSemicircleGaugePrivate
{
public:
    explicit QEXTSemicircleGaugePrivate(QEXTSemicircleGauge *q);
    virtual ~QEXTSemicircleGaugePrivate();

    QEXTSemicircleGauge * const q_ptr;

    double m_minValue;                //最小值
    double m_maxValue;                //最大值
    double m_value;                   //目标值

    int m_scaleMajor;                 //大刻度数量
    int m_scaleMinor;                 //小刻度数量
    int m_startAngle;                 //开始旋转角度
    int m_endAngle;                   //结束旋转角度

    QColor m_usedColor;               //当前值颜色
    QColor m_freeColor;               //剩余值颜色

    QColor m_scaleColor;              //刻度尺颜色
    QColor m_pointerColor;            //指针颜色
    QColor m_textColor;               //文字颜色
    QColor m_titleColor;              //标题颜色

    bool m_overlayVisiable;               //显示遮罩层
    QColor m_overlayColor;            //遮罩层颜色

    QEXTSemicircleGauge::PointerStyleType m_pointerStyle;      //指针样式

    int m_offsetY;                    //半圆仪效果Y坐标偏移量
    int m_radiusY;                    //半圆仪效果中心点Y坐标偏移量

    double m_currentValue;            //当前值
    bool m_animationVisiable;                 //是否启用动画显示
    QPropertyAnimation *m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSemicircleGaugePrivate)
    QEXT_DECL_PUBLIC(QEXTSemicircleGauge)
};

#endif // _QEXTGAUGESEMICIRCLE_P_H
