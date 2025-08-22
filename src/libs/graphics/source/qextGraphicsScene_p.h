#ifndef _QEXTGRAPHICSSCENE_P_H
#define _QEXTGRAPHICSSCENE_P_H

#include <qextGraphicsScene.h>

class QExtGraphicsScenePrivate
{
    QExtGraphicsScene * const q_ptr;
public:
    explicit QExtGraphicsScenePrivate(QExtGraphicsScene *q);
    virtual ~QExtGraphicsScenePrivate();

    qreal m_dx;
    qreal m_dy;
    bool m_moved;
    QGraphicsView *m_view;
    QExtGraphicsGridTool *m_grid;

private:
    QEXT_DECLARE_PUBLIC(QExtGraphicsScene)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsScenePrivate)
};

#endif // _QEXTGRAPHICSSCENE_P_H
