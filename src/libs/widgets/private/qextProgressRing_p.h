#ifndef _QEXTPROGRESSRING_P_H
#define _QEXTPROGRESSRING_P_H

#include <qextWidgetGlobal.h>

#include <QColor>
#include <QPropertyAnimation>

class QEXTProgressRing;
class QEXT_WIDGETS_API QEXTProgressRingPrivate
{
public:
    explicit QEXTProgressRingPrivate(QEXTProgressRing *q);
    virtual ~QEXTProgressRingPrivate();

    QEXTProgressRing * const q_ptr;

    double m_minValue;                //最小值
    double m_maxValue;                //最大值
    double m_value;                   //目标值
    int m_precision;                  //精确度,小数点后几位
    QString m_text;                   //用于直接显示文字

    bool m_clipCenter;                //中间部分是否扣掉成透明
    bool m_clockWise;                 //顺时针逆时针
    bool m_showPercent;               //显示百分比

    int m_alarmMode;                  //警戒报警模式,进度为不同的颜色
    int m_startAngle;                 //起始角度
    int m_ringPadding;                //圆环间距
    int m_ringWidth;                  //圆环宽度

    QColor m_backgroundColor;                 //背景颜色
    QColor m_textColor;               //文字颜色
    QColor m_ringColor;               //圆环颜色
    QColor m_ringBackgroundColor;             //圆环进度背景
    QColor m_circleColor;             //中心圆颜色

    int m_ringValue1;                 //环形值1
    int m_ringValue2;                 //环形值2
    int m_ringValue3;                 //环形值3

    QColor m_ringColor1;              //环形颜色1
    QColor m_ringColor2;              //环形颜色2
    QColor m_ringColor3;              //环形颜色3

    bool m_animationEnable;                 //是否启用动画显示
    double m_currentValue;            //当前值
    QPropertyAnimation *m_animation;                  //定时器绘制动画

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressRingPrivate)
    QEXT_DECL_PUBLIC(QEXTProgressRing)
};


#endif // _QEXTPROGRESSRING_P_H
