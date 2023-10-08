#ifndef _QEXTTHERMOMETER_P_H
#define _QEXTTHERMOMETER_P_H

#include <qextThermometer.h>

class QEXTThermometer;
class QEXT_WIDGETS_API QEXTThermometerPrivate
{
public:
    explicit QEXTThermometerPrivate(QEXTThermometer *q);
    virtual ~QEXTThermometerPrivate();

    QEXTThermometer * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;

    int m_precision;
    int m_longStep;
    int m_shortStep;
    int m_space;

    bool m_animation;
    double m_animationStep;

    bool m_userValueVisible;
    double m_userValue;
    QColor m_userValueColor;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;
    QColor m_lineColor;
    QColor m_barBackgroundColor;
    QColor m_barColor;

    QEXTThermometer::BarPosition m_barPosition;
    QEXTThermometer::TickPosition m_tickPosition;

    int m_barWidth;
    int m_barHeight;
    int m_radius;
    int m_targetX;
    QRectF m_barRect;
    QRectF m_circleRect;

    bool m_reverse;
    double m_currentValue;
    QTimer *m_timer;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTThermometerPrivate)
    QEXT_DECL_PUBLIC(QEXTThermometer)
};

#endif // _QEXTTHERMOMETER_P_H
