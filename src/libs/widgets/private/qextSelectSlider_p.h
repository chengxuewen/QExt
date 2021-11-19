#ifndef _QEXTSELECTSLIDER_P_H
#define _QEXTSELECTSLIDER_P_H

#include <qextWidgetGlobal.h>

#include <QColor>
#include <QPoint>
#include <QRect>

class QEXTSelectSlider;
class QEXT_WIDGETS_API QEXTSelectSliderPrivate
{
public:
    explicit QEXTSelectSliderPrivate(QEXTSelectSlider *q);
    virtual ~QEXTSelectSliderPrivate();

    QEXTSelectSlider * const q_ptr;


    int m_maxValue;
    int m_minValue;
    int m_leftValue;
    int m_rightValue;                 //范围值右边

    int m_rangeValue;                 //当前范围值 最大值-最小值
    int m_step;                       //单步步长

    int m_borderWidth;                //滑块边框宽度
    bool m_horizontal;                //是否横向

    QColor m_usedColor;               //范围值颜色
    QColor m_freeColor;               //范围值外颜色
    QColor m_textColor;               //文字颜色
    QColor m_rangeTextColor;          //范围文字颜色
    QColor m_sliderColor;             //滑块颜色
    QColor m_borderColor;             //滑块边框颜色
    QColor m_buttonNormalColor;          //按钮正常颜色
    QColor m_buttonPressColor;           //按钮按下颜色

    int m_buttonWidth;                   //左右步进按钮宽度
    int m_sliderHeight;               //控制滑块高度

    QPoint m_posPress;                //鼠标按下时的坐标
    QPoint m_posMove;                 //鼠标拖动后的坐标

    bool m_sliderPress;
    bool m_leftPress;
    bool m_rightPress;
    bool m_leftButtonPress;
    bool m_rightButtonPress;

    QRect m_sliderRect;
    QRect m_leftRect;
    QRect m_rightRect;
    QRect m_leftBtnRect;
    QRect m_rightBtnRect;

    QRect m_sliderRectTemp;
    QRect m_leftRectTemp;
    QRect m_rightRectTemp;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSelectSliderPrivate)
    Q_DECLARE_PUBLIC(QEXTSelectSlider)
};

#endif // _QEXTSELECTSLIDER_P_H
