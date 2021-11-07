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


    int m_maxValue;                   //最小值
    int m_minValue;                   //最大值
    int m_leftValue;                  //范围值左边
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

    bool m_sliderPress;               //主滑块按下
    bool m_leftPress;                 //左控制滑块按下
    bool m_rightPress;                //右控制滑块按下
    bool m_leftButtonPress;              //左单步按钮按下
    bool m_rightButtonPress;             //右单步按钮按下

    QRect m_sliderRect;               //主滑块rect
    QRect m_leftRect;                 //左控制滑块rect
    QRect m_rightRect;                //右控制滑块rect
    QRect m_leftBtnRect;              //左单步按钮rect
    QRect m_rightBtnRect;             //右单步按钮rect

    QRect m_sliderRectTemp;           //主滑块初始rect
    QRect m_leftRectTemp;             //左控制滑块初始rect
    QRect m_rightRectTemp;            //右控制滑块初始rect


private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSelectSliderPrivate)
    QEXT_DECL_PUBLIC(QEXTSelectSlider)
};

#endif // _QEXTSELECTSLIDER_P_H
