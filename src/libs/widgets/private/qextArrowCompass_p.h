#ifndef _QEXTARROWCOMPASS_P_H
#define _QEXTARROWCOMPASS_P_H

#include <qextWidgetGlobal.h>

#include <QColor>
#include <QPropertyAnimation>

class QEXTArrowCompass;
class QEXT_WIDGETS_API QEXTArrowCompassPrivate
{
public:
    explicit QEXTArrowCompassPrivate(QEXTArrowCompass *q);
    virtual ~QEXTArrowCompassPrivate();

    QEXTArrowCompass * const q_ptr;

    double m_value;                   //目标值
    int m_precision;                  //精确度,小数点后几位

    QColor m_crownColorStart;         //外边框渐变开始颜色
    QColor m_crownColorEnd;           //外边框渐变结束颜色

    QColor m_backgroundStartColor;            //背景渐变开始颜色
    QColor m_backgroundEndColor;              //背景渐变结束颜色

    QColor m_darkColor;               //加深颜色
    QColor m_lightColor;              //明亮颜色

    QColor m_foregroundColor;              //前景色
    QColor m_textColor;               //文字颜色

    QColor m_northPointerColor;       //北方指针颜色
    QColor m_southPointerColor;       //南方指针颜色

    QColor m_centerStartColor;        //中心圆渐变开始颜色
    QColor m_centerEndColor;          //中心圆渐变结束颜色

    bool m_animationVisiable;                 //是否启用动画显示
    double m_currentValue;            //当前值
    QPropertyAnimation *m_animation;                  //绘制动画

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTArrowCompassPrivate)
    QEXT_DECL_PUBLIC(QEXTArrowCompass)
};

#endif // _QEXTARROWCOMPASS_P_H
