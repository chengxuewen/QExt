#ifndef _QEXTTOOLTIP_P_H
#define _QEXTTOOLTIP_P_H

#include <qextWidgetGlobal.h>
#include <qextTooltip.h>

class QEXTTooltip;
class QEXT_WIDGETS_API QEXTTooltipPrivate
{
public:
    explicit QEXTTooltipPrivate(QEXTTooltip *q);
    virtual ~QEXTTooltipPrivate();

    QEXTTooltip * const q_ptr;

    int m_borderRadius;
    QColor m_backgroundColor;
    QColor m_foregroundColor;

    bool m_arrowVisible;
    int m_arrowSize;
    QEXTTooltip::ArrowPositionType m_arrowPosition;

    bool m_triangleVisible;
    int m_triangleLen;
    QEXTTooltip::TrianglePositionType m_trianglePosition;
    QColor m_triangleColor;

    QRect m_backgroundRect;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTTooltipPrivate)
    QEXT_DECL_PUBLIC(QEXTTooltip)
};

#endif // _QEXTTOOLTIP_P_H
