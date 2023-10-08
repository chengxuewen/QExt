#ifndef _QEXTRANGESLIDER_P_H
#define _QEXTRANGESLIDER_P_H

#include <qextRangeSlider.h>

class QEXTRangeSlider;
class QEXTRangeSliderPrivate
{
public:
    explicit QEXTRangeSliderPrivate(QEXTRangeSlider *q);
    virtual ~QEXTRangeSliderPrivate();

    QEXTRangeSlider * const q_ptr;

    int m_minValue;
    int m_maxValue;
    int m_leftValue;
    int m_rightValue;

    int m_borderWidth;
    bool m_horizontal;
    bool m_textVisible;

    QColor m_usedColor;
    QColor m_freeColor;
    QColor m_textColor;
    QColor m_rangeTextColor;
    QColor m_sliderColor;
    QColor m_borderColor;

    QEXTRangeSlider::SliderStyle m_sliderStyle;
    QEXTRangeSlider::SliderBgPercent m_sliderBackgroundPercent;
    QEXTRangeSlider::SliderPercent m_sliderPercent;

    bool m_leftPressed;
    bool m_rightPressed;

    int m_sliderLen;
    QRect m_leftSliderRect;
    QRect m_rightSliderRect;
};

#endif // _QEXTRANGESLIDER_P_H
