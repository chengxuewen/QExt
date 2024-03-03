#ifndef _QEXTGRAPHICSTOOL_H
#define _QEXTGRAPHICSTOOL_H

#include <qextGraphicsItems.h>

class QMenu;
class QFont;
class QColor;
class QPointF;
class QGraphicsScene;
class QGraphicsLineItem;
class QGraphicsTextItem;
class QGraphicsSceneMouseEvent;
class QAbstractGraphicsShapeItem;

class QExtGraphicsItem;
class QExtGraphicsScene;
class QExtGraphicsPolygonItem;

enum DrawShape
{
    selection,
    rotation,
    line,
    rectangle,
    roundrect,
    ellipse,
    bezier,
    polygon,
    polyline,
};

class QEXT_GRAPHICS_API QExtGraphicsTool
{
public:
    QExtGraphicsTool(DrawShape shape);
    virtual ~QExtGraphicsTool() {}

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event ,QExtGraphicsScene *scene);

    static QExtGraphicsTool *findTool(DrawShape drawShape);

    bool m_hoverSizer;
    DrawShape m_drawShape;
    static QPointF sm_down;
    static QPointF sm_last;
    static quint32 sm_nDownFlags;
    static DrawShape sm_drawShape;
    static QList<QExtGraphicsTool *> sm_tools;
};

class QExtGraphicsSelectTool : public QExtGraphicsTool
{
public:
    QExtGraphicsSelectTool();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;

    QPointF m_opposite;
    QPointF m_initialPositions;
    QGraphicsPathItem *m_dashRect;
    QExtGraphicsItemGroup *m_selLayer;
};

class QEXT_GRAPHICS_API QExtGraphicsRotationTool : public QExtGraphicsTool
{
public:
    QExtGraphicsRotationTool();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;

    qreal m_lastAngle;
    QGraphicsPathItem *m_dashRect;
};

class QEXT_GRAPHICS_API QExtGraphicsRectTool : public QExtGraphicsTool
{
public:
    QExtGraphicsRectTool(DrawShape drawShape);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;

    QExtGraphicsItem *m_item;
};

class QEXT_GRAPHICS_API QExtGraphicsPolygonTool : public QExtGraphicsTool
{
public:
    explicit QExtGraphicsPolygonTool(DrawShape shape);
    ~QExtGraphicsPolygonTool() QEXT_OVERRIDE {}

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, QExtGraphicsScene *scene) QEXT_OVERRIDE;

    int m_pointsCount;
    QPointF m_initialPositions;
    QExtGraphicsPolygonItem *m_item;
};

#endif // _QEXTGRAPHICSTOOL_H

