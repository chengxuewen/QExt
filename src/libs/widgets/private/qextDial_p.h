#ifndef _QEXTDIAL_P_H
#define _QEXTDIAL_P_H

#include <qextWidgetGlobal.h>
#include <qextDial.h>

class QEXTDial;
class QEXT_WIDGETS_API QEXTDialPrivate
{
public:
    explicit QEXTDialPrivate(QEXTDial *q);
    virtual ~QEXTDialPrivate();

    QEXTDial * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    int m_scaleMajor;
    int m_scaleMinor;
    int m_startAngle;
    int m_endAngle;

    QColor m_darkColor;
    QColor m_lightColor;
    QColor m_textColor;

    bool m_valueVisiable;
    QEXTDial::PointerStyleType m_pointerStyle;
    bool m_pressed;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTDialPrivate)
    QEXT_DECL_PUBLIC(QEXTDial)
};

#endif // _QEXTDIAL_P_H
