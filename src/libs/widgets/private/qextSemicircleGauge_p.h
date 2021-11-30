#ifndef _QEXTGAUGESEMICIRCLE_P_H
#define _QEXTGAUGESEMICIRCLE_P_H

#include <qextWidgetGlobal.h>
#include <qextSemicircleGauge.h>

#include <QColor>
#include <QPropertyAnimation>

class QEXTSemicircleGauge;
class QEXT_WIDGETS_API QEXTSemicircleGaugePrivate
{
    Q_DISABLE_COPY(QEXTSemicircleGaugePrivate)
    Q_DECLARE_PUBLIC(QEXTSemicircleGauge)
public:
    explicit QEXTSemicircleGaugePrivate(QEXTSemicircleGauge *q);
    virtual ~QEXTSemicircleGaugePrivate();

    QEXTSemicircleGauge * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;

    int m_scaleMajor;
    int m_scaleMinor;
    int m_startAngle;
    int m_endAngle;

    QColor m_usedColor;
    QColor m_freeColor;

    QColor m_scaleColor;
    QColor m_pointerColor;
    QColor m_textColor;
    QColor m_titleColor;

    bool m_overlayVisiable;
    QColor m_overlayColor;

    QEXTSemicircleGauge::PointerStyleType m_pointerStyle;

    int m_offsetY;
    int m_radiusY;

    double m_currentValue;
    bool m_animationVisiable;
    QPropertyAnimation *m_animation;
};

#endif // _QEXTGAUGESEMICIRCLE_P_H
