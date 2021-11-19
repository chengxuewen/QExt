#ifndef _QEXTDIAL_P_H
#define _QEXTDIAL_P_H

#include <qextWidgetGlobal.h>
#include <qextDial.h>

class QEXTDial;
class QEXT_WIDGETS_API QEXTDialPrivate
{
public:
    explicit QEXTDialPrivate(QEXTDial *q);
    virtual ~QEXTDialPrivate();

    QEXTDial * const q_ptr;

    double m_minValue; //最小值
    double m_maxValue; //最大值
    double m_value;    //目标值
    int m_precision;   //精确度,小数点后几位

    int m_scaleMajor; //大刻度数量
    int m_scaleMinor; //小刻度数量
    int m_startAngle; //开始旋转角度
    int m_endAngle;   //结束旋转角度

    QColor m_darkColor;  //暗黑颜色
    QColor m_lightColor; //明亮颜色
    QColor m_textColor;  //文字颜色

    bool m_valueVisiable;            //是否显示当前值
    QEXTDial::PointerStyleType m_pointerStyle; //指针样式
    bool m_pressed;   //鼠标是否按下

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTDialPrivate)
    Q_DECLARE_PUBLIC(QEXTDial)
};

#endif // _QEXTDIAL_P_H
