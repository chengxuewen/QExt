#include <private/qextBlueprintView_p.h>
#include <qextBlueprintScene.h>

#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QSvgGenerator>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <cmath>

QExtBlueprintViewPrivate::QExtBlueprintViewPrivate(QExtBlueprintView *q)
    : q_ptr(q)
    , m_fineGridColor(60, 60, 60)
    , m_backgroundColor(53, 53, 53)
    , m_coarseGridColor(25, 25, 25)
{
}

QExtBlueprintViewPrivate::~QExtBlueprintViewPrivate()
{

}

void QExtBlueprintViewPrivate::drawGrid(QPainter *painter, double gridStep)
{
    Q_Q(QExtBlueprintView);
    QRect windowRect = q->rect();
    QPointF tl = q->mapToScene(windowRect.topLeft());
    QPointF br = q->mapToScene(windowRect.bottomRight());

    double left = std::floor(tl.x() / gridStep - 0.5);
    double right = std::floor(br.x() / gridStep + 1.0);
    double bottom = std::floor(tl.y() / gridStep - 0.5);
    double top = std::floor(br.y() / gridStep + 1.0);

    // vertical lines
    for (int xi = int(left); xi <= int(right); ++xi)
    {
        QLineF line(xi * gridStep, bottom * gridStep, xi * gridStep, top * gridStep);
        painter->drawLine(line);
    }

    // horizontal lines
    for (int yi = int(bottom); yi <= int(top); ++yi)
    {
        QLineF line(left * gridStep, yi * gridStep, right * gridStep, yi * gridStep);
        painter->drawLine(line);
    }
}


QExtBlueprintView::QExtBlueprintView(QGraphicsScene *scene)
    : QGraphicsView(scene)
    , dd_ptr(new QExtBlueprintViewPrivate(this))
{
    Q_D(QExtBlueprintView);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setRenderHint(QPainter::Antialiasing);
    this->setBackgroundBrush(d->m_backgroundColor);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    this->setScaleRange(0.3, 2);
    // Sets the scene rect to its maximum possible ranges to avoid autu scene range
    // re-calculation when expanding the all QGraphicsItems common rect.
    int maxSize = 32767;
    this->setSceneRect(-maxSize, -maxSize, (maxSize * 2), (maxSize * 2));
}

QExtBlueprintView::~QExtBlueprintView()
{

}

QColor QExtBlueprintView::fineGridColor() const
{
    Q_D(const QExtBlueprintView);
    return d->m_fineGridColor;
}

void QExtBlueprintView::setFineGridColor(const QColor &color)
{
    Q_D(QExtBlueprintView);
    d->m_fineGridColor = color;
}

QColor QExtBlueprintView::backgroundColor() const
{
    Q_D(const QExtBlueprintView);
    return d->m_backgroundColor;
}

void QExtBlueprintView::setBackgroundColor(const QColor &color)
{
    Q_D(QExtBlueprintView);
    d->m_backgroundColor = color;
}

QColor QExtBlueprintView::coarseGridColor() const
{
    Q_D(const QExtBlueprintView);
    return d->m_coarseGridColor;
}

void QExtBlueprintView::setCoarseGridColor(const QColor &color)
{
    Q_D(QExtBlueprintView);
    d->m_coarseGridColor = color;
}

void QExtBlueprintView::centerScene()
{
    QGraphicsScene *scene = this->scene();
    if (scene)
    {
        scene->setSceneRect(QRectF());
        QRectF sceneRect = scene->sceneRect();
        if (sceneRect.width() > this->rect().width() || sceneRect.height() > this->rect().height())
        {
            this->fitInView(sceneRect, Qt::KeepAspectRatio);
        }
        this->centerOn(sceneRect.center());
    }
}

void QExtBlueprintView::setScaleRange(double minimum, double maximum)
{
    Q_D(QExtBlueprintView);
    if (maximum < minimum)
    {
        std::swap(minimum, maximum);
    }
    minimum = std::max(0.0, minimum);
    maximum = std::max(0.0, maximum);

    d->m_scaleRange = QExtBlueprintViewPrivate::ScaleRange(minimum, maximum);
    this->setupScale(this->transform().m11());
}

double QExtBlueprintView::getScale() const
{
    return this->transform().m11();
}

void QExtBlueprintView::scaleUp()
{
    Q_D(QExtBlueprintView);
    double const step = 1.2;
    double const factor = std::pow(step, 1.0);

    if (d->m_scaleRange.maximum > 0)
    {
        QTransform t = transform();
        t.scale(factor, factor);
        if (t.m11() >= d->m_scaleRange.maximum)
        {
            this->setupScale(t.m11());
            return;
        }
    }

    this->scale(factor, factor);
    Q_EMIT this->scaleChanged(this->transform().m11());
}

void QExtBlueprintView::scaleDown()
{
    Q_D(QExtBlueprintView);
    double const step = 1.2;
    double const factor = std::pow(step, -1.0);

    if (d->m_scaleRange.minimum > 0)
    {
        QTransform t = this->transform();
        t.scale(factor, factor);
        if (t.m11() <= d->m_scaleRange.minimum)
        {
            this->setupScale(t.m11());
            return;
        }
    }

    this->scale(factor, factor);
    Q_EMIT this->scaleChanged(transform().m11());
}

void QExtBlueprintView::setupScale(double scale)
{
    Q_D(QExtBlueprintView);
    scale = std::max(d->m_scaleRange.minimum, std::min(d->m_scaleRange.maximum, scale));
    if (scale <= 0)
    {
        return;
    }
    if (scale == this->transform().m11())
    {
        return;
    }

    QTransform matrix;
    matrix.scale(scale, scale);
    this->setTransform(matrix, false);

    Q_EMIT this->scaleChanged(scale);
}

void QExtBlueprintView::contextMenuEvent(QContextMenuEvent *event)
{
    // QGraphicsView::contextMenuEvent(event);
    if (this->itemAt(event->pos()))
    {
        QGraphicsView::contextMenuEvent(event);
        return;
    }

    auto const scenePos = this->mapToScene(event->pos());
    // QMenu *menu = nodeScene()->createSceneMenu(scenePos);

    // if (menu) {
    //     menu->exec(event->globalPos());
    // }
}

void QExtBlueprintView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_D(QExtBlueprintView);
    QGraphicsView::drawBackground(painter, rect);

    QPen pfine(d->m_fineGridColor, 1.0);
    painter->setPen(pfine);
    d->drawGrid(painter, 15);

    QPen p(d->m_coarseGridColor, 1.0);
    painter->setPen(p);
    d->drawGrid(painter, 150);
}

void QExtBlueprintView::wheelEvent(QWheelEvent *event)
{
    // QGraphicsView::wheelEvent(event);
    QPoint delta = event->angleDelta();

    if (delta.y() == 0)
    {
        event->ignore();
        return;
    }

    double const d = delta.y() / std::abs(delta.y());

    if (d > 0.0)
    {
        this->scaleUp();
    }
    else
    {
        this->scaleDown();
    }
}

void QExtBlueprintView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Shift:
        this->setDragMode(QGraphicsView::RubberBandDrag);
        break;
    default:
        break;
    }
    QGraphicsView::keyPressEvent(event);
}

void QExtBlueprintView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Shift:
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        break;
    default:
        break;
    }
    QGraphicsView::keyReleaseEvent(event);
}

void QExtBlueprintView::closeEvent(QCloseEvent *event)
{
    QGraphicsView::closeEvent(event);
}

void QExtBlueprintView::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QExtBlueprintView);
    QGraphicsView::mouseMoveEvent(event);
    if (this->scene()->mouseGrabberItem() == nullptr && event->buttons() == Qt::LeftButton)
    {
        // Make sure shift is not being pressed
        if ((event->modifiers() & Qt::ShiftModifier) == 0)
        {
            QPointF difference = d->m_clickPos - this->mapToScene(event->pos());
            this->setSceneRect(this->sceneRect().translated(difference.x(), difference.y()));
        }
    }
}

void QExtBlueprintView::mousePressEvent(QMouseEvent *event)
{
    Q_D(QExtBlueprintView);
    QGraphicsView::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        d->m_clickPos = this->mapToScene(event->pos());
    }
}

void QExtBlueprintView::showEvent(QShowEvent *event)
{
    QGraphicsView::showEvent(event);
    this->centerScene();
}

void QExtBlueprintView::resizeEvent(QResizeEvent *event)
{
    Q_D(QExtBlueprintView);
    QGraphicsView::resizeEvent(event);
}

void QExtBlueprintView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx, dy);
}
