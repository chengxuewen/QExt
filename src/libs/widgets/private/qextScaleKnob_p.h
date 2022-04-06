#ifndef _QEXTSCALEKNOB_P_H
#define _QEXTSCALEKNOB_P_H

#include <qextWidgetGlobal.h>
#include <qextScaleKnob.h>

class QEXTScaleKnob;
class QEXT_WIDGETS_API QEXTScaleKnobPrivate
{
public:
    explicit QEXTScaleKnobPrivate(QEXTScaleKnob *q);
    virtual ~QEXTScaleKnobPrivate();

    QEXTScaleKnob * const q_ptr;


    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    int m_scaleStep;
    int m_startAngle;
    int m_endAngle;

    QColor m_borderColor;
    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_percentColor;

    bool m_rangeBisectionEnable;
    bool m_valueVisible;
    QEXTScaleKnob::PointerStyle m_pointerStyle;
    bool m_pressed;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTScaleKnobPrivate)
    QEXT_DECL_PUBLIC(QEXTScaleKnob)
};

#endif // _QEXTSCALEKNOB_P_H
