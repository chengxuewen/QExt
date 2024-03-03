#ifndef _QEXTGRAPHICSHANDLES_H
#define _QEXTGRAPHICSHANDLES_H

#include <qextGraphicsGlobal.h>

#include <QList>
#include <QGraphicsRectItem>

class QColor;
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;

enum SelectionHandleState { SelectionHandleOff, SelectionHandleInactive, SelectionHandleActive };
// enum { Handle_None = 0 , LeftTop , Top, RightTop, Right, RightBottom, Bottom, LeftBottom, Left };

class QExtGraphicsSizeHandlePrivate;
class QEXT_GRAPHICS_API QExtGraphicsSizeHandle : public QGraphicsRectItem
{
public:
    enum HandleEnum
    {
        Handle_None = 0,
        Handle_LeftTop,
        Handle_Top,
        Handle_RightTop,
        Handle_Right,
        Handle_RightBottom,
        Handle_Bottom,
        Handle_LeftBottom,
        Handle_Left
    };
    QEXT_STATIC_CONSTANT(int, HandleEnumNum = 9);

    QExtGraphicsSizeHandle(QGraphicsItem *parent, int dir, bool control = false);
    QExtGraphicsSizeHandle(QExtGraphicsSizeHandlePrivate *d, QGraphicsItem *parent, bool control = false);
    ~QExtGraphicsSizeHandle() QEXT_OVERRIDE;

    int dir() const;
    void setState(SelectionHandleState state);
    void move(qreal x, qreal y);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) QEXT_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) QEXT_OVERRIDE;

    QScopedPointer<QExtGraphicsSizeHandlePrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtGraphicsSizeHandle)
    QEXT_DISABLE_COPY_MOVE(QExtGraphicsSizeHandle)
};

#endif // _QEXTGRAPHICSHANDLES_H
