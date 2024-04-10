#ifndef _QEXTBLUEPRINTSCENE_H
#define _QEXTBLUEPRINTSCENE_H

#include <qextBlueprintGlobal.h>

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

class QExtBlueprintScenePrivate;
class QEXT_BLUEPRINT_API QExtBlueprintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QExtBlueprintScene(QObject *parent = QEXT_NULLPTR);
    ~QExtBlueprintScene() QEXT_OVERRIDE;

    QGraphicsView *view() const;
    void setView(QGraphicsView *view);

// Q_SIGNALS:


// Q_SLOTS:

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) QEXT_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvet) QEXT_OVERRIDE;

    void keyPressEvent(QKeyEvent *event) QEXT_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) QEXT_OVERRIDE;

    QScopedPointer<QExtBlueprintScenePrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtBlueprintScene)
    QEXT_DISABLE_COPY_MOVE(QExtBlueprintScene)
};

#endif // _QEXTBLUEPRINTSCENE_H

