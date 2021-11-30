#ifndef _QEXTSELECTSLIDER_P_H
#define _QEXTSELECTSLIDER_P_H

#include <qextWidgetGlobal.h>

#include <QColor>
#include <QPoint>
#include <QRect>

class QEXTSelectSlider;
class QEXT_WIDGETS_API QEXTSelectSliderPrivate
{
    Q_DISABLE_COPY(QEXTSelectSliderPrivate)
    Q_DECLARE_PUBLIC(QEXTSelectSlider)
public:
    explicit QEXTSelectSliderPrivate(QEXTSelectSlider *q);
    virtual ~QEXTSelectSliderPrivate();

    QEXTSelectSlider * const q_ptr;


    int m_maxValue;
    int m_minValue;
    int m_leftValue;
    int m_rightValue;

    int m_rangeValue;
    int m_step;

    int m_borderWidth;
    bool m_horizontal;

    QColor m_usedColor;
    QColor m_freeColor;
    QColor m_textColor;
    QColor m_rangeTextColor;
    QColor m_sliderColor;
    QColor m_borderColor;
    QColor m_buttonNormalColor;
    QColor m_buttonPressColor;

    int m_buttonWidth;
    int m_sliderHeight;

    QPoint m_posPress;
    QPoint m_posMove;

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
};

#endif // _QEXTSELECTSLIDER_P_H
