#ifndef _QEXTKNOB_P_H
#define _QEXTKNOB_P_H

#include <qextWidgetGlobal.h>
#include <qextProgressKnob.h>

class QPropertyAnimation;
class QEXTProgressKnob;
class QEXT_WIDGETS_API QEXTProgressKnobPrivate
{
public:
    explicit QEXTProgressKnobPrivate(QEXTProgressKnob *q);
    virtual ~QEXTProgressKnobPrivate();

    QEXTProgressKnob * const q_ptr;

    double m_minValue;                  //最小值
    double m_maxValue;                  //最大值
    double m_value;                     //目标值
    int m_precision;                    //精确度,小数点后几位

    int m_startAngle;                   //开始旋转角度
    int m_endAngle;                     //结束旋转角度

    QColor m_backgroundColor;           //背景色
    QColor m_progressColor;             //当前进度颜色
    QColor m_progressBackgroundColor;   //进度背景颜色
    QColor m_circleStartColor;          //中间圆渐变开始颜色
    QColor m_circleEndColor;            //中间圆渐变结束颜色
    QColor m_textColor;                 //文字颜色

    bool m_pointerVisiable;                 //是否显示指示器
    bool m_valueVisiable;                   //是否显示当前值
    QEXTProgressKnob::PointerStyle m_pointerStyle;  //指针样式

    bool m_pressed;                     //鼠标是否按下
    bool m_hover;                       //是否鼠标悬停
    bool m_animationEnable;             //悬停动画使能
    int m_radiusCoverCircle;            //覆盖圆半径
    int m_radiusCircle;                 //中间圆半径
    QPropertyAnimation *m_animation;    //动画对象


private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressKnobPrivate)
    Q_DECLARE_PUBLIC(QEXTProgressKnob)
};

#endif // _QEXTKNOB_P_H
