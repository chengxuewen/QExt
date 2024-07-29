#ifndef _QEXTBPGRAPHICSVIEW_H
#define _QEXTBPGRAPHICSVIEW_H

#include <qextBlueprintGlobal.h>

#include <QGraphicsView>

class QExtBPBasicGraphicsScene;

/**
 * @brief A central view able to render objects from `BasicGraphicsScene`.
 */
class QExtBPGraphicsViewPrivate;
class QEXT_BLUEPRINT_API QExtBPGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    struct ScaleRange
    {
        double minimum = 0;
        double maximum = 0;
    };

    QExtBPGraphicsView(QWidget *parent = QEXT_NULLPTR);
    QExtBPGraphicsView(QExtBPBasicGraphicsScene *scene, QWidget *parent = QEXT_NULLPTR);
    ~QExtBPGraphicsView() QEXT_OVERRIDE;

    QAction *clearSelectionAction() const;

    QAction *deleteSelectionAction() const;

    void setScene(QExtBPBasicGraphicsScene *scene);

    void centerScene();

    /// @brief max=0/min=0 indicates infinite zoom in/out
    void setScaleRange(double minimum = 0, double maximum = 0);

    void setScaleRange(ScaleRange range);

    double getScale() const;

public Q_SLOTS:
    void scaleUp();

    void scaleDown();

    void setupScale(double scale);

    void onDeleteSelectedObjects();

    void onDuplicateSelectedObjects();

    void onCopySelectedObjects();

    void onPasteObjects();

Q_SIGNALS:
    void scaleChanged(double scale);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void drawBackground(QPainter *painter, const QRectF &r) override;

    void showEvent(QShowEvent *event) override;

protected:
    QExtBPBasicGraphicsScene *nodeScene();

    /// Computes scene position for pasting the copied/duplicated node groups.
    QPointF scenePastePosition();

    QScopedPointer<QExtBPGraphicsViewPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtBPGraphicsView)
    QEXT_DISABLE_COPY_MOVE(QExtBPGraphicsView)
};

#endif // _QEXTBPGRAPHICSVIEW_H
