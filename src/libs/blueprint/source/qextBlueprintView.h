#ifndef _QEXTBLUEPRINTVIEW_H
#define _QEXTBLUEPRINTVIEW_H

#include <qextBlueprintGlobal.h>

#include <QGraphicsView>

class QMouseEvent;

class QExtBlueprintViewPrivate;
class QEXT_BLUEPRINT_API QExtBlueprintView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QExtBlueprintView(QGraphicsScene *scene);
    ~QExtBlueprintView() QEXT_OVERRIDE;

    QColor fineGridColor() const;
    void setFineGridColor(const QColor &color);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QColor coarseGridColor() const;
    void setCoarseGridColor(const QColor &color);

    // QAction *clearSelectionAction() const;

    // QAction *deleteSelectionAction() const;

    // void setScene(BasicGraphicsScene *scene);

    void centerScene();

    // @brief max=0/min=0 indicates infinite zoom in/out
    void setScaleRange(double minimum = 0, double maximum = 0);
    double getScale() const;

public Q_SLOTS:
    void scaleUp();

    void scaleDown();

    void setupScale(double scale);

    // void onDeleteSelectedObjects();

    // void onDuplicateSelectedObjects();

    // void onCopySelectedObjects();

    // void onPasteObjects();

Q_SIGNALS:
    void scaleChanged(double scale);

protected:
    void contextMenuEvent(QContextMenuEvent *event) QEXT_OVERRIDE;
    void drawBackground(QPainter *painter, const QRectF &rect) QEXT_OVERRIDE;

    void wheelEvent(QWheelEvent *event) QEXT_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) QEXT_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) QEXT_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) QEXT_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) QEXT_OVERRIDE;

    void showEvent(QShowEvent *event) QEXT_OVERRIDE;
    void closeEvent(QCloseEvent *event) QEXT_OVERRIDE;
    void resizeEvent(QResizeEvent *event) QEXT_OVERRIDE;
    void scrollContentsBy(int dx, int dy) QEXT_OVERRIDE;

    QScopedPointer<QExtBlueprintViewPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtBlueprintView)
    QEXT_DISABLE_COPY_MOVE(QExtBlueprintView)
};

#endif // _QEXTBLUEPRINTVIEW_H
