#include <private/qextBPGraphicsView_p.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPBasicGraphicsScene.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPStyleCollection.h>
#include <qextBPUndoCommands.h>

#include <QtWidgets/QGraphicsScene>

#include <QtGui/QBrush>
#include <QtGui/QPen>

#include <QtWidgets/QMenu>

#include <QtCore/QDebug>
#include <QtCore/QPointF>
#include <QtCore/QRectF>

#include <QtOpenGL>
#include <QtWidgets>

#include <cmath>
#include <iostream>


QExtBPGraphicsViewPrivate::QExtBPGraphicsViewPrivate(QExtBPGraphicsView *q)
    : q_ptr(q)
{
}

QExtBPGraphicsViewPrivate::~QExtBPGraphicsViewPrivate()
{
}

void QExtBPGraphicsViewPrivate::drawGrid(QPainter *painter, double gridStep)
{
    Q_Q(QExtBPGraphicsView);
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

QExtBPGraphicsView::QExtBPGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
    , dd_ptr(new QExtBPGraphicsViewPrivate(this))
{
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setRenderHint(QPainter::Antialiasing);

    const auto &flowViewStyle = QExtBPStyleCollection::flowViewStyle();

    this->setBackgroundBrush(flowViewStyle.BackgroundColor);

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

QExtBPGraphicsView::QExtBPGraphicsView(QExtBPBasicGraphicsScene *scene, QWidget *parent)
    : QExtBPGraphicsView(parent)
{
    this->setScene(scene);
}

QExtBPGraphicsView::~QExtBPGraphicsView()
{

}

QAction *QExtBPGraphicsView::clearSelectionAction() const
{
    Q_D(const QExtBPGraphicsView);
    return d->m_clearSelectionAction.data();
}

QAction *QExtBPGraphicsView::deleteSelectionAction() const
{
    Q_D(const QExtBPGraphicsView);
    return d->m_deleteSelectionAction.data();
}

void QExtBPGraphicsView::setScene(QExtBPBasicGraphicsScene *scene)
{
    Q_D(QExtBPGraphicsView);
    QGraphicsView::setScene(scene);

    {
        // setup actions
        delete d->m_clearSelectionAction.data();
        d->m_clearSelectionAction = new QAction(tr("Clear Selection"), this);
        d->m_clearSelectionAction->setShortcut(Qt::Key_Escape);
        connect(d->m_clearSelectionAction.data(), SIGNAL(triggered(bool)), scene, SLOT(clearSelection()));
        this->addAction(d->m_clearSelectionAction.data());
    }

    {
        delete d->m_deleteSelectionAction.data();
        d->m_deleteSelectionAction = new QAction(tr("Delete Selection"), this);
        d->m_deleteSelectionAction->setShortcutContext(Qt::ShortcutContext::WidgetShortcut);
        d->m_deleteSelectionAction->setShortcut(QKeySequence(QKeySequence::Delete));
        connect(d->m_deleteSelectionAction.data(), SIGNAL(triggered(bool)), this, SLOT(onDeleteSelectedObjects()));
        this->addAction(d->m_deleteSelectionAction.data());
    }

    {
        delete d->m_duplicateSelectionAction.data();
        d->m_duplicateSelectionAction = new QAction(tr("Duplicate Selection"), this);
        d->m_duplicateSelectionAction->setShortcutContext(Qt::ShortcutContext::WidgetShortcut);
        d->m_duplicateSelectionAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));
        connect(d->m_duplicateSelectionAction.data(), SIGNAL(triggered(bool)), this, SLOT(onDuplicateSelectedObjects()));
        this->addAction(d->m_duplicateSelectionAction.data());
    }

    {
        delete d->m_copySelectionAction.data();
        d->m_copySelectionAction = new QAction(tr("Copy Selection"), this);
        d->m_copySelectionAction->setShortcutContext(Qt::ShortcutContext::WidgetShortcut);
        d->m_copySelectionAction->setShortcut(QKeySequence(QKeySequence::Copy));
        connect(d->m_copySelectionAction.data(), SIGNAL(triggered(bool)), this, SLOT(onCopySelectedObjects()));
        this->addAction(d->m_copySelectionAction.data());
    }

    {
        delete d->m_pasteAction.data();
        d->m_pasteAction = new QAction(tr("Copy Selection"), this);
        d->m_pasteAction->setShortcutContext(Qt::ShortcutContext::WidgetShortcut);
        d->m_pasteAction->setShortcut(QKeySequence(QKeySequence::Paste));
        connect(d->m_pasteAction.data(), SIGNAL(triggered(bool)), this, SLOT(onPasteObjects()));
        this->addAction(d->m_pasteAction.data());
    }

    QAction *undoAction = scene->undoStack().createUndoAction(this, tr("&Undo"));
    undoAction->setShortcuts(QKeySequence::Undo);
    this->addAction(undoAction);

    QAction *redoAction = scene->undoStack().createRedoAction(this, tr("&Redo"));
    redoAction->setShortcuts(QKeySequence::Redo);
    this->addAction(redoAction);
}

void QExtBPGraphicsView::centerScene()
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

double QExtBPGraphicsView::getScale() const
{
    return this->transform().m11();
}

void QExtBPGraphicsView::setScaleRange(double minimum, double maximum)
{
    Q_D(QExtBPGraphicsView);
    if (maximum < minimum)
    {
        std::swap(minimum, maximum);
    }
    minimum = std::max(0.0, minimum);
    maximum = std::max(0.0, maximum);

    d->m_scaleRange.minimum = minimum;
    d->m_scaleRange.maximum = maximum;
    this->setupScale(this->transform().m11());
}

void QExtBPGraphicsView::setScaleRange(ScaleRange range)
{
    this->setScaleRange(range.minimum, range.maximum);
}

void QExtBPGraphicsView::scaleUp()
{
    Q_D(QExtBPGraphicsView);
    const double step = 1.2;
    const double factor = std::pow(step, 1.0);

    if (d->m_scaleRange.maximum > 0)
    {
        QTransform t = this->transform();
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

void QExtBPGraphicsView::scaleDown()
{
    Q_D(QExtBPGraphicsView);
    const double step = 1.2;
    const double factor = std::pow(step, -1.0);

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
    Q_EMIT this->scaleChanged(this->transform().m11());
}

void QExtBPGraphicsView::setupScale(double scale)
{
    Q_D(QExtBPGraphicsView);
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

void QExtBPGraphicsView::onDeleteSelectedObjects()
{
    QExtBPBasicGraphicsScene *nodeScene = this->nodeScene();
    nodeScene->undoStack().push(new QExtBPDeleteCommand(nodeScene));
}

void QExtBPGraphicsView::onDuplicateSelectedObjects()
{
    const QPointF pastePosition = this->scenePastePosition();
    QExtBPBasicGraphicsScene *nodeScene = this->nodeScene();
    nodeScene->undoStack().push(new CopyCommand(nodeScene));
    nodeScene->undoStack().push(new QExtBPPasteCommand(nodeScene, pastePosition));
}

void QExtBPGraphicsView::onCopySelectedObjects()
{
    QExtBPBasicGraphicsScene *nodeScene = this->nodeScene();
    nodeScene->undoStack().push(new CopyCommand(nodeScene));
}

void QExtBPGraphicsView::onPasteObjects()
{
    const QPointF pastePosition = scenePastePosition();
    QExtBPBasicGraphicsScene *nodeScene = this->nodeScene();
    nodeScene->undoStack().push(new QExtBPPasteCommand(nodeScene, pastePosition));
}

void QExtBPGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    if (this->itemAt(event->pos()))
    {
        QGraphicsView::contextMenuEvent(event);
        return;
    }

    const QPointF scenePos = this->mapToScene(event->pos());
    QMenu *menu = this->nodeScene()->createSceneMenu(scenePos);
    if (menu)
    {
        menu->exec(event->globalPos());
    }
}

void QExtBPGraphicsView::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();
    if (delta.y() == 0)
    {
        event->ignore();
        return;
    }

    const double d = delta.y() / std::abs(delta.y());
    if (d > 0.0)
    {
        this->scaleUp();
    }
    else
    {
        this->scaleDown();
    }
}

void QExtBPGraphicsView::keyPressEvent(QKeyEvent *event)
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

void QExtBPGraphicsView::keyReleaseEvent(QKeyEvent *event)
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

void QExtBPGraphicsView::mousePressEvent(QMouseEvent *event)
{
    Q_D(QExtBPGraphicsView);
    QGraphicsView::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        d->m_clickPos = this->mapToScene(event->pos());
    }
}

void QExtBPGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QExtBPGraphicsView);
    QGraphicsView::mouseMoveEvent(event);
    if (this->scene()->mouseGrabberItem() == QEXT_NULLPTR && event->buttons() == Qt::LeftButton)
    {
        // Make sure shift is not being pressed
        if ((event->modifiers() & Qt::ShiftModifier) == 0)
        {
            const QPointF difference = d->m_clickPos - this->mapToScene(event->pos());
            this->setSceneRect(this->sceneRect().translated(difference.x(), difference.y()));
        }
    }
}

void QExtBPGraphicsView::drawBackground(QPainter *painter, const QRectF &r)
{
    Q_D(QExtBPGraphicsView);
    QGraphicsView::drawBackground(painter, r);

    const QExtBPGraphicsViewStyle &flowViewStyle = QExtBPStyleCollection::flowViewStyle();
    QPen pfine(flowViewStyle.FineGridColor, 1.0);
    painter->setPen(pfine);
    d->drawGrid(painter, 15);

    QPen p(flowViewStyle.CoarseGridColor, 1.0);
    painter->setPen(p);
    d->drawGrid(painter, 150);
}

void QExtBPGraphicsView::showEvent(QShowEvent *event)
{
    QGraphicsView::showEvent(event);
    this->centerScene();
}

QExtBPBasicGraphicsScene *QExtBPGraphicsView::nodeScene()
{
    return dynamic_cast<QExtBPBasicGraphicsScene *>(this->scene());
}

QPointF QExtBPGraphicsView::scenePastePosition()
{
    QPoint origin = this->mapFromGlobal(QCursor::pos());

    QRect const viewRect = this->rect();
    if (!viewRect.contains(origin))
    {
        origin = viewRect.center();
    }
    return this->mapToScene(origin);
}
