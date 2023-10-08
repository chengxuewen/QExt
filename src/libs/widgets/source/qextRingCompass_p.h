#ifndef _QEXTRINGCOMPASSGAUGE_P_H
#define _QEXTRINGCOMPASSGAUGE_P_H

#include <qextRingCompass.h>

#include <QColor>

class QEXTRingCompass;
class QEXT_WIDGETS_API QEXTRingCompassPrivate
{
public:
    explicit QEXTRingCompassPrivate(QEXTRingCompass *q);
    virtual ~QEXTRingCompassPrivate();

    QEXTRingCompass * const q_ptr;

    double m_value;
    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_borderColor;
    int m_borderWidth;

    QColor m_northDotColor;
    QColor m_otherDotColor;
    QColor m_pointerColor;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTRingCompassPrivate)
    QEXT_DECL_PUBLIC(QEXTRingCompass)
};

#endif // _QEXTRINGCOMPASSGAUGE_P_H
