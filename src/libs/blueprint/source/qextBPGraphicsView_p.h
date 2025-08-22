#ifndef _QEXTBPGRAPHICSVIEW_P_H
#define _QEXTBPGRAPHICSVIEW_P_H

#include <qextBPGraphicsView.h>

#include <QPointer>

class QExtBPGraphicsViewPrivate
{
public:
    explicit QExtBPGraphicsViewPrivate(QExtBPGraphicsView *q);
    virtual ~QExtBPGraphicsViewPrivate();

    void drawGrid(QPainter *painter, double gridStep);

    QExtBPGraphicsView * const q_ptr;

    QPointer<QAction> m_pasteAction;
    QPointer<QAction> m_copySelectionAction;
    QPointer<QAction> m_clearSelectionAction;
    QPointer<QAction> m_deleteSelectionAction;
    QPointer<QAction> m_duplicateSelectionAction;

    QPointF m_clickPos;
    QExtBPGraphicsView::ScaleRange m_scaleRange;

private:
    QEXT_DECLARE_PUBLIC(QExtBPGraphicsView)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPGraphicsViewPrivate)
};

#endif // _QEXTBPGRAPHICSVIEW_P_H
