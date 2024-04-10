#ifndef _QEXTBLUEPRINTVIEW_P_H
#define _QEXTBLUEPRINTVIEW_P_H

#include <qextBlueprintView.h>

#include <QPair>

class QExtBlueprintViewPrivate
{
public:
    struct ScaleRange
    {
        ScaleRange(double min = 0, double max = 0) : minimum(min), maximum(max) {}

        double minimum;
        double maximum;
    };

    explicit QExtBlueprintViewPrivate(QExtBlueprintView *q);
    virtual ~QExtBlueprintViewPrivate();

    void drawGrid(QPainter *painter, double gridStep);

    QExtBlueprintView * const q_ptr;

    QPointF m_clickPos;
    ScaleRange m_scaleRange;

    QColor m_fineGridColor;
    QColor m_backgroundColor;
    QColor m_coarseGridColor;

private:
    QEXT_DECL_PUBLIC(QExtBlueprintView)
    QEXT_DISABLE_COPY_MOVE(QExtBlueprintViewPrivate)
};

#endif // _QEXTBLUEPRINTVIEW_P_H
