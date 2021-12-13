#ifndef _QEXTKNOB_P_H
#define _QEXTKNOB_P_H

#include <qextWidgetGlobal.h>
#include <qextProgressKnob.h>

class QPropertyAnimation;
class QEXTProgressKnob;
class QEXT_WIDGETS_API QEXTProgressKnobPrivate
{
public:
    explicit QEXTProgressKnobPrivate(QEXTProgressKnob *q);
    virtual ~QEXTProgressKnobPrivate();

    QEXTProgressKnob * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    int m_startAngle;
    int m_endAngle;

    QColor m_backgroundColor;
    QColor m_progressColor;
    QColor m_progressBackgroundColor;
    QColor m_circleStartColor;
    QColor m_circleEndColor;
    QColor m_textColor;

    bool m_pointerVisiable;
    bool m_valueVisiable;
    QEXTProgressKnob::PointerStyle m_pointerStyle;

    bool m_pressed;
    bool m_hover;
    bool m_animationEnable;
    int m_radiusCoverCircle;
    int m_radiusCircle;
    QPropertyAnimation *m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressKnobPrivate)
    QEXT_DECL_PUBLIC(QEXTProgressKnob)
};

#endif // _QEXTKNOB_P_H
