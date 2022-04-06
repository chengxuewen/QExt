#ifndef _QEXTARROWCOMPASS_P_H
#define _QEXTARROWCOMPASS_P_H

#include <qextWidgetGlobal.h>

#include <QColor>
#include <QPropertyAnimation>

class QEXTArrowCompass;
class QEXT_WIDGETS_API QEXTArrowCompassPrivate
{
public:
    explicit QEXTArrowCompassPrivate(QEXTArrowCompass *q);
    virtual ~QEXTArrowCompassPrivate();

    QEXTArrowCompass * const q_ptr;

    double m_value;
    int m_precision;

    QColor m_crownColorStart;
    QColor m_crownColorEnd;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;

    QColor m_darkColor;
    QColor m_lightColor;

    QColor m_foregroundColor;
    QColor m_textColor;

    QColor m_northPointerColor;
    QColor m_southPointerColor;

    QColor m_centerStartColor;
    QColor m_centerEndColor;

    bool m_animationVisible;
    double m_currentValue;
    QScopedPointer<QPropertyAnimation> m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTArrowCompassPrivate)
    QEXT_DECL_PUBLIC(QEXTArrowCompass)
};

#endif // _QEXTARROWCOMPASS_P_H
