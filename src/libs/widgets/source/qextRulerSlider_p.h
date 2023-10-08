#ifndef _QEXTRULERSLIDER_P_H
#define _QEXTRULERSLIDER_P_H

#include <qextRulerSlider.h>

class QEXTRulerSlider;
class QEXTRulerSliderPrivate
{
public:
    explicit QEXTRulerSliderPrivate(QEXTRulerSlider *q);
    virtual ~QEXTRulerSliderPrivate();

    QEXTRulerSlider * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    int m_longStep;
    int m_shortStep;
    int m_space;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;
    QColor m_lineColor;

    QColor m_sliderTopColor;
    QColor m_sliderBottomColor;

    QColor m_tipBackgroundColor;
    QColor m_tipTextColor;

    bool m_pressed;
    double m_currentValue;

    double m_longLineHeight;
    double m_shortLineHeight;
    double m_sliderTopHeight;
    double m_sliderBottomHeight;

    QPointF m_sliderLastPot;
    QPointF m_sliderTopPot;
    QPointF m_sliderLeftPot;
    QPointF m_sliderRightPot;

    QRectF m_sliderRect;
    QRectF m_tipRect;
    QPointF m_lineLeftPot;
    QPointF m_lineRightPot;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTRulerSliderPrivate)
    QEXT_DECL_PUBLIC(QEXTRulerSlider)
};

#endif // _QEXTRULERSLIDER_P_H
