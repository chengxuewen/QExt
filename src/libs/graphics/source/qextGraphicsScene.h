#ifndef _QEXTGRAPHICSSCENE_H
#define _QEXTGRAPHICSSCENE_H

#include <qextGraphicsItems.h>
#include <qextGraphicsTool.h>

#include <QGraphicsScene>

class QMenu;
class QFont;
class QColor;
class QPointF;
class QPainter;
class QKeyEvent;
class QGraphicsTextItem;
class QGraphicsLineItem;
class QGraphicsSceneMouseEvent;

enum AlignType
{
    UP_ALIGN=0,
    HORZ_ALIGN,
    VERT_ALIGN,
    DOWN_ALIGN,
    LEFT_ALIGN,
    RIGHT_ALIGN,
    CENTER_ALIGN,
    HORZEVEN_ALIGN,
    VERTEVEN_ALIGN,
    WIDTH_ALIGN,
    HEIGHT_ALIGN,
    ALL_ALIGN
};

class QEXT_GRAPHICS_API QExtGraphicsGridTool
{
public:
    QExtGraphicsGridTool(const QSize &grid = QSize(3200, 2400), const QSize &space = QSize(20, 20));
    void paintGrid(QPainter *painter, const QRect &rect);

protected:
    QSize m_sizeGrid;
    QSize m_sizeGridSpace;
};

class QExtGraphicsItemGroup;
class QExtGraphicsScenePrivate;
class QEXT_GRAPHICS_API QExtGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QExtGraphicsScene(QObject *parent = 0);
    ~QExtGraphicsScene() QEXT_OVERRIDE;

    QGraphicsView *view() const;
    void setView(QGraphicsView *view);

    void align(AlignType alignType);

    void mouseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    QExtGraphicsItemGroup *createGroup(const QList<QGraphicsItem *> &items ,bool isAdd = true);

    void destroyGroup(QGraphicsItemGroup *group);

signals:
    void itemAdded(QGraphicsItem *item);
    void itemRotate(QGraphicsItem *item, const qreal oldAngle);
    void itemMoved(QGraphicsItem *item, const QPointF &oldPosition);
    void itemResize(QGraphicsItem *item, int handle, const QPointF &scale);
    void itemControl(QGraphicsItem *item, int handle, const QPointF &newPos , const QPointF &lastPos_);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) QEXT_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvet) QEXT_OVERRIDE;

    void keyPressEvent(QKeyEvent *event) QEXT_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) QEXT_OVERRIDE;

    QScopedPointer<QExtGraphicsScenePrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtGraphicsScene)
    QEXT_DISABLE_COPY_MOVE(QExtGraphicsScene)
};

#endif // _QEXTGRAPHICSSCENE_H

