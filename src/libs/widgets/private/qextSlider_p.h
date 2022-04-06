#ifndef _QEXTSLIDER_P_H
#define _QEXTSLIDER_P_H

#include <qextWidgetGlobal.h>
#include <qextSlider.h>

#include <QColor>

class QEXTTooltip;
class QEXTSlider;
class QEXT_WIDGETS_API QEXTSliderPrivate
{
public:
    explicit QEXTSliderPrivate(QEXTSlider *q);
    virtual ~QEXTSliderPrivate();

    QEXTSlider * const q_ptr;

    int m_borderRadius;
    int m_arrowSize;
    QEXTSlider::ArrowStyleType m_arrowStyle;

    QColor m_backgroundColor;
    QColor m_foregroundColor;

    int m_tooltipWidth;
    int m_tooltipHeight;
    QFont m_tooltipFont;

    bool m_timeVisible;
    bool m_clickEnable;
    QString m_unitText;

    QEXTTooltip *m_tooltip;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSliderPrivate)
    QEXT_DECL_PUBLIC(QEXTSlider)
};

#endif // _QEXTSLIDER_P_H
