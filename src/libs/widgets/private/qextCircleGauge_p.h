#ifndef _QEXTGAUGECAR_P_H
#define _QEXTGAUGECAR_P_H

#include <qextWidgetGlobal.h>
#include <qextCircleGauge.h>

#include <QColor>
#include <QPropertyAnimation>

class QEXTCircleGauge;
class QEXT_WIDGETS_API QEXTCircleGaugePrivate
{
public:
    explicit QEXTCircleGaugePrivate(QEXTCircleGauge *q);
    virtual ~QEXTCircleGaugePrivate();

    QEXTCircleGauge * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    int m_scaleMajor;
    int m_scaleMinor;
    int m_startAngle;
    int m_endAngle;

    QColor m_outerCircleColor;
    QColor m_innerCircleColor;

    QColor m_pieColorStart;
    QColor m_pieColorMid;
    QColor m_pieColorEnd;

    QColor m_coverCircleColor;
    QColor m_scaleColor;
    QColor m_pointerColor;
    QColor m_centerCircleColor;
    QColor m_textColor;

    bool m_overlayVisible;
    QColor m_overlayColor;

    int m_circleWidth;
    QEXTCircleGauge::PieStyleType m_pieStyle;
    QEXTCircleGauge::PointerStyleType m_pointerStyle;

    double m_currentValue;
    bool m_animationEnable;
    QPropertyAnimation *m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTCircleGaugePrivate)
    QEXT_DECL_PUBLIC(QEXTCircleGauge)
};

#endif // _QEXTGAUGECAR_P_H
