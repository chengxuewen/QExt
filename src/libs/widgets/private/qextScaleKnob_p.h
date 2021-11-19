#ifndef _QEXTSCALEKNOB_P_H
#define _QEXTSCALEKNOB_P_H

#include <qextWidgetGlobal.h>
#include <qextScaleKnob.h>

class QEXTScaleKnob;
class QEXT_WIDGETS_API QEXTScaleKnobPrivate
{
public:
    explicit QEXTScaleKnobPrivate(QEXTScaleKnob *q);
    virtual ~QEXTScaleKnobPrivate();

    QEXTScaleKnob * const q_ptr;


    double m_minValue;                //最小值
    double m_maxValue;                //最大值
    double m_value;                   //目标值
    int m_precision;                  //精确度,小数点后几位

    int m_scaleStep;                       //刻度数量
    int m_startAngle;                 //开始旋转角度
    int m_endAngle;                   //结束旋转角度

    QColor m_borderColor;             //边框颜色
    QColor m_backgroundColor;                 //背景颜色
    QColor m_textColor;               //文字颜色
    QColor m_percentColor;            //进度颜色

    bool m_rangeBisectionEnable;             //是否对半等分范围值
    bool m_valueVisiable;                 //是否显示当前值
    QEXTScaleKnob::PointerStyle m_pointerStyle;      //指针样式
    bool m_pressed;     //鼠标是否按下


private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTScaleKnobPrivate)
    Q_DECLARE_PUBLIC(QEXTScaleKnob)
};

#endif // _QEXTSCALEKNOB_P_H
