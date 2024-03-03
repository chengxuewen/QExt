#ifndef _QEXTGRAPHICSVIEW_H
#define _QEXTGRAPHICSVIEW_H

#include <qextGraphicsItems.h>

#include <QGraphicsView>

class QMouseEvent;

#define RULER_SIZE    16

class QEXT_GRAPHICS_API QExtGraphicsViewCornerBox : public QWidget
{
    Q_OBJECT
public:
    explicit QExtGraphicsViewCornerBox(QWidget *parent);
    ~QExtGraphicsViewCornerBox() QEXT_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;
};

class QExtGraphicsViewRuleBarPrivate;
class QEXT_GRAPHICS_API QExtGraphicsViewRuleBar : public QWidget
{
    Q_OBJECT
public:
    explicit QExtGraphicsViewRuleBar(Qt::Orientation direction, QGraphicsView * view, QWidget * parent = 0  );
    ~QExtGraphicsViewRuleBar() QEXT_OVERRIDE;

    void setRange(double lower, double upper, double maxSize);
    void updatePosition(const QPoint &pos);

protected:
    void paintEvent(QPaintEvent *event) QEXT_OVERRIDE;

    void drawTicker(QPainter * painter);
    void drawPos(QPainter* painter);

    QScopedPointer<QExtGraphicsViewRuleBarPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtGraphicsViewRuleBar)
    QEXT_DISABLE_COPY_MOVE(QExtGraphicsViewRuleBar)
};


class QExtGraphicsViewPrivate;
class QEXT_GRAPHICS_API QExtGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QExtGraphicsView(QGraphicsScene *scene);
    ~QExtGraphicsView() QEXT_OVERRIDE;

    void zoomIn();
    void zoomOut();

    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();

    QString currentFile() const;

    bool isModified() const;
    void setModified(bool value);

signals:
    void positionChanged(int x, int y);

protected:
    void closeEvent(QCloseEvent *event) QEXT_OVERRIDE;

    void mouseMoveEvent(QMouseEvent * event) QEXT_OVERRIDE;
    void resizeEvent(QResizeEvent *event) QEXT_OVERRIDE;
    void scrollContentsBy(int dx, int dy) QEXT_OVERRIDE;
    void updateRuler();

    QScopedPointer<QExtGraphicsViewPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtGraphicsView)
    QEXT_DISABLE_COPY_MOVE(QExtGraphicsView)
};

#endif // _QEXTGRAPHICSVIEW_H
