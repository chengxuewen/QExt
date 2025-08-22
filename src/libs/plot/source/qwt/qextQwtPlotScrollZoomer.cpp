#include <qextQwtPlotScrollZoomer.h>

#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_widget.h>

#include <QEvent>
#include <QDebug>
#include <QStack>
#include <QResizeEvent>

class QExtScrollData
{
public:
    QExtScrollData() : mode(Qt::ScrollBarAsNeeded), scrollBar(NULL), position(QExtPlotScrollZoomer::OppositeToScale) {}
    ~QExtScrollData()
    {
        delete scrollBar;
    }

    Qt::ScrollBarPolicy mode;
    QExtPlotScrollBar *scrollBar;
    QExtPlotScrollZoomer::ScrollBarPosition position;
};

class QExtPlotScrollZoomerPrivate
{
    QExtPlotScrollZoomer * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtPlotScrollZoomer)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotScrollZoomerPrivate)
public:
    explicit QExtPlotScrollZoomerPrivate(QExtPlotScrollZoomer *q);
    virtual ~QExtPlotScrollZoomerPrivate();

    double mXMin;
    double mXMax;
    QRectF mLimitsRect;
    double mHViewSize;

    QWidget *mCornerWidget;
    QExtScrollData *mHScrollData;
    QExtScrollData *mVScrollData;

    bool mInZoom;
    bool mHScrollMove;
    bool mVScrollMove;
    bool mAlignCanvasToScales[QwtPlot::axisCnt];
};

QExtPlotScrollZoomerPrivate::QExtPlotScrollZoomerPrivate(QExtPlotScrollZoomer *q)
    : q_ptr(q)
{
    mXMin = 0.0;
    mXMax = 10000.;
    mHViewSize = 10000;

    for (int axis = 0; axis < QwtPlot::axisCnt; axis++)
    {
        mAlignCanvasToScales[axis] = false;
    }

    mInZoom = false;
    mCornerWidget = QEXT_NULLPTR;
    mHScrollData = new QExtScrollData;
    mVScrollData = new QExtScrollData;
    mHScrollMove = false;
    mVScrollMove = false;
}

QExtPlotScrollZoomerPrivate::~QExtPlotScrollZoomerPrivate()
{
    delete mCornerWidget;
    delete mVScrollData;
    delete mHScrollData;
}

QExtPlotScrollZoomer::QExtPlotScrollZoomer(QWidget *canvas)
    : QwtPlotZoomer(canvas)
    , dd_ptr(new QExtPlotScrollZoomerPrivate(this))
{
}

QExtPlotScrollZoomer::~QExtPlotScrollZoomer()
{
}

QExtPlotScrollBar *QExtPlotScrollZoomer::horizontalScrollBar() const
{
    Q_D(const QExtPlotScrollZoomer);
    return d->mHScrollData->scrollBar;
}

QExtPlotScrollBar *QExtPlotScrollZoomer::verticalScrollBar() const
{
    Q_D(const QExtPlotScrollZoomer);
    return d->mVScrollData->scrollBar;
}

void QExtPlotScrollZoomer::setHScrollBarMode(Qt::ScrollBarPolicy mode)
{
    Q_D(QExtPlotScrollZoomer);
    if (this->hScrollBarMode() != mode)
    {
        d->mHScrollData->mode = mode;
        this->updateScrollBars();
    }
}

void QExtPlotScrollZoomer::setVScrollBarMode(Qt::ScrollBarPolicy mode)
{
    Q_D(QExtPlotScrollZoomer);
    if (this->vScrollBarMode() != mode)
    {
        d->mVScrollData->mode = mode;
        this->updateScrollBars();
    }
}

Qt::ScrollBarPolicy QExtPlotScrollZoomer::vScrollBarMode() const
{
    Q_D(const QExtPlotScrollZoomer);
    return d->mVScrollData->mode;
}

Qt::ScrollBarPolicy QExtPlotScrollZoomer::hScrollBarMode() const
{
    Q_D(const QExtPlotScrollZoomer);
    return d->mHScrollData->mode;
}

void QExtPlotScrollZoomer::setHScrollBarPosition(ScrollBarPosition pos)
{
    Q_D(QExtPlotScrollZoomer);
    if (d->mHScrollData->position != pos)
    {
        d->mHScrollData->position = pos;
        this->updateScrollBars();
    }
}

void QExtPlotScrollZoomer::setVScrollBarPosition(ScrollBarPosition pos)
{
    Q_D(QExtPlotScrollZoomer);
    if (d->mVScrollData->position != pos)
    {
        d->mVScrollData->position = pos;
        this->updateScrollBars();
    }
}

QExtPlotScrollZoomer::ScrollBarPosition QExtPlotScrollZoomer::hScrollBarPosition() const
{
    Q_D(const QExtPlotScrollZoomer);
    return d->mHScrollData->position;
}

QExtPlotScrollZoomer::ScrollBarPosition QExtPlotScrollZoomer::vScrollBarPosition() const
{
    Q_D(const QExtPlotScrollZoomer);
    return d->mVScrollData->position;
}

QWidget *QExtPlotScrollZoomer::cornerWidget() const
{
    Q_D(const QExtPlotScrollZoomer);
    return d->mCornerWidget;
}

void QExtPlotScrollZoomer::setCornerWidget(QWidget *widget)
{
    Q_D(QExtPlotScrollZoomer);
    if (widget != d->mCornerWidget)
    {
        if (this->canvas())
        {
            if (d->mCornerWidget)
            {
                delete d->mCornerWidget;
            }
            d->mCornerWidget = widget;
            if (d->mCornerWidget)
            {
                if (d->mCornerWidget->parent() != this->canvas())
                {
                    d->mCornerWidget->setParent(this->canvas());
                }
            }
            this->updateScrollBars();
        }
    }
}

void QExtPlotScrollZoomer::setHViewSize(double size)
{
    Q_D(QExtPlotScrollZoomer);
    d->mHScrollMove = true;
    d->mHViewSize = size;
    this->setZoomBase();
    d->mHScrollMove = false;
}

void QExtPlotScrollZoomer::setXLimits(double min, double max)
{
    Q_D(QExtPlotScrollZoomer);
    d->mXMin = min;
    d->mXMax = max;
    this->setZoomBase();
}

void QExtPlotScrollZoomer::rescale()
{
    Q_D(QExtPlotScrollZoomer);
    QwtScaleWidget *xScale = plot()->axisWidget(xAxis());
    QwtScaleWidget *yScale = plot()->axisWidget(yAxis());

    if (zoomRectIndex() <= 0)
    {
        if (d->mInZoom)
        {
            xScale->setMinBorderDist(0, 0);
            yScale->setMinBorderDist(0, 0);

            QwtPlotLayout *layout = plot()->plotLayout();

            for (int axis = 0; axis < QwtPlot::axisCnt; axis++)
            {
                layout->setAlignCanvasToScale(axis, d->mAlignCanvasToScales[axis]);
            }

            d->mInZoom = false;
        }
    }
    else
    {
        if (!d->mInZoom)
        {
            /*
             We set a minimum border distance.
             Otherwise the canvas size changes when scrolling,
             between situations where the major ticks are at
             the canvas borders (requiring extra space for the label)
             and situations where all labels can be painted below/top
             or left/right of the canvas.
             */
            int start, end;

            xScale->getBorderDistHint(start, end);
            xScale->setMinBorderDist(start, end);

            yScale->getBorderDistHint(start, end);
            yScale->setMinBorderDist(start, end);

            QwtPlotLayout *layout = plot()->plotLayout();
            for (int axis = 0; axis < QwtPlot::axisCnt; axis++)
            {
                d->mAlignCanvasToScales[axis] = layout->alignCanvasToScale(axis);
            }

            layout->setAlignCanvasToScales(false);

            d->mInZoom = true;
        }
    }

    // NOTE: Below snippet is copied from QwtPlotZoomer::rescale() just so that
    // we can refrain from updating y axis when moving horizontal scrollbar, so
    // that auto-scale isn't disrupted. Also we don't want to jump around in
    // x-axis when moving vertical scroll.
    {
        QwtPlot *plt = plot();
        if (!plt)
        {
            return;
        }

        const QRectF &rect = this->zoomStack()[this->zoomRectIndex()];
        if (rect != scaleRect())
        {
            const bool doReplot = plt->autoReplot();
            plt->setAutoReplot(false);

            if (!d->mVScrollMove)
            {
                double x1 = rect.left();
                double x2 = rect.right();
                if (!plt->axisScaleDiv(xAxis()).isIncreasing())
                {
                    qSwap(x1, x2);
                }

                plt->setAxisScale(xAxis(), x1, x2);
            }

            if (!d->mHScrollMove)
            {
                double y1 = rect.top();
                double y2 = rect.bottom();
                if (!plt->axisScaleDiv(yAxis()).isIncreasing())
                {
                    qSwap(y1, y2);
                }

                plt->setAxisScale(yAxis(), y1, y2);

                plt->setAutoReplot(doReplot);
            }
            plt->replot();
        }
    }
    this->updateScrollBars();
}

void QExtPlotScrollZoomer::setZoomBase(bool doReplot)
{
    Q_D(QExtPlotScrollZoomer);
    QwtPlotZoomer::setZoomBase(doReplot);
    auto zb = this->zoomBase();
    auto zs = this->zoomStack();
    zb.setRight(d->mXMax);
    if ((d->mXMax - d->mXMin) < d->mHViewSize)
    {
        zb.setLeft(d->mXMin);
    }
    else
    {
        zb.setLeft(d->mXMax - d->mHViewSize);
    }
    zs[0] = zb;
    this->setZoomStack(zs);
}

void QExtPlotScrollZoomer::moveTo(const QPointF &pos)
{
    Q_D(QExtPlotScrollZoomer);

    double x = pos.x();
    double y = pos.y();

    if (x < d->mXMin)
    {
        x = d->mXMin;
    }
    if (x > d->mXMax - this->zoomRect().width())
    {
        x = d->mXMax - this->zoomRect().width();
    }

    if (y < this->zoomBase().top())
    {
        y = this->zoomBase().top();
    }
    if (y > this->zoomBase().bottom() - this->zoomRect().height())
    {
        y = this->zoomBase().bottom() - this->zoomRect().height();
    }

    if (x != this->zoomRect().left() || y != this->zoomRect().top())
    {
        auto zs = this->zoomStack();
        zs[zoomRectIndex()].moveTo(x, y);
        this->setZoomStack(zs, this->zoomRectIndex());
        this->rescale();
    }
}

void QExtPlotScrollZoomer::scrollBarMoved(Qt::Orientation orientation, double min, double max)
{
    Q_UNUSED(max);
    Q_D(QExtPlotScrollZoomer);

    if (Qt::Horizontal == orientation)
    {
        d->mHScrollMove = true;
        this->moveTo(QPointF(min, this->zoomRect().top()));
        d->mHScrollMove = false;
    }
    else
    {
        d->mVScrollMove = true;
        this->moveTo(QPointF(this->zoomRect().left(), min));
        d->mVScrollMove = false;
    }

    Q_EMIT this->zoomed(this->zoomRect());
}

bool QExtPlotScrollZoomer::eventFilter(QObject *object, QEvent *event)
{
    Q_D(QExtPlotScrollZoomer);
    if (object == this->canvas())
    {
        switch (event->type())
        {
        case QEvent::Resize:
        {
            int left, top, right, bottom;
            this->canvas()->getContentsMargins(&left, &top, &right, &bottom);

            QRect rect;
            rect.setSize(static_cast<QResizeEvent *>(event)->size());
            rect.adjust(left, top, -right, -bottom);

            this->layoutScrollBars(rect);
            break;
        }
        case QEvent::Show:
        {
            this->layoutScrollBars(this->canvas()->contentsRect());
            break;
        }
        case QEvent::ChildRemoved:
        {
            const QObject *child = static_cast<QChildEvent *>(event)->child();

            if (child == d->mCornerWidget)
            {
                d->mCornerWidget = NULL;
            }
            else if (child == d->mHScrollData->scrollBar)
            {
                d->mHScrollData->scrollBar = NULL;
            }
            else if (child == d->mVScrollData->scrollBar)
            {
                d->mVScrollData->scrollBar = NULL;
            }
            break;
        }
        default:
            break;
        }
    }
    return QwtPlotZoomer::eventFilter(object, event);
}

QExtPlotScrollBar *QExtPlotScrollZoomer::scrollBar(Qt::Orientation orientation)
{
    Q_D(QExtPlotScrollZoomer);
    QExtPlotScrollBar *&sb = (orientation == Qt::Vertical) ? d->mVScrollData->scrollBar : d->mHScrollData->scrollBar;

    if (sb == NULL)
    {
        sb = new QExtPlotScrollBar(orientation, canvas());
        sb->hide();
        connect(sb, SIGNAL(valueChangedWithRange(Qt::Orientation,double,double)),
                this, SLOT(scrollBarMoved(Qt::Orientation, double, double)));
    }
    return sb;
}

void QExtPlotScrollZoomer::layoutScrollBars(const QRect &rect)
{
    Q_D(QExtPlotScrollZoomer);
    int hPos = this->xAxis();
    if (this->hScrollBarPosition() == OppositeToScale)
    {
        hPos = this->oppositeAxis(hPos);
    }

    int vPos = this->yAxis();
    if (this->vScrollBarPosition() == OppositeToScale)
    {
        vPos = this->oppositeAxis(vPos);
    }

    QExtPlotScrollBar *hScrollBar = this->horizontalScrollBar();
    QExtPlotScrollBar *vScrollBar = this->verticalScrollBar();

    const int hdim = hScrollBar ? hScrollBar->extent() : 0;
    const int vdim = vScrollBar ? vScrollBar->extent() : 0;

    if (hScrollBar && hScrollBar->isVisible())
    {
        int x = rect.x();
        int y = (hPos == QwtPlot::xTop) ? rect.top() : rect.bottom() - hdim + 1;
        int w = rect.width();

        if (vScrollBar && vScrollBar->isVisible())
        {
            if (vPos == QwtPlot::yLeft)
            {
                x += vdim;
            }
            w -= vdim;
        }

        hScrollBar->setGeometry(x, y, w, hdim);
    }
    if (vScrollBar && vScrollBar->isVisible())
    {
        int pos = yAxis();
        if (this->vScrollBarPosition() == OppositeToScale)
        {
            pos = this->oppositeAxis(pos);
        }

        int x = (vPos == QwtPlot::yLeft) ? rect.left() : rect.right() - vdim + 1;
        int y = rect.y();

        int h = rect.height();

        if (hScrollBar && hScrollBar->isVisible())
        {
            if (hPos == QwtPlot::xTop)
            {
                y += hdim;
            }

            h -= hdim;
        }

        vScrollBar->setGeometry(x, y, vdim, h);
    }
    if (hScrollBar && hScrollBar->isVisible() && vScrollBar && vScrollBar->isVisible())
    {
        if (d->mCornerWidget)
        {
            QRect cornerRect(vScrollBar->pos().x(), hScrollBar->pos().y(), vdim, hdim);
            d->mCornerWidget->setGeometry(cornerRect);
        }
    }
}

void QExtPlotScrollZoomer::updateScrollBars()
{
    Q_D(QExtPlotScrollZoomer);
    if (!this->canvas())
    {
        return;
    }

    const int xAxis = QwtPlotZoomer::xAxis();
    const int yAxis = QwtPlotZoomer::yAxis();

    int xScrollBarAxis = xAxis;
    if (this->hScrollBarPosition() == OppositeToScale)
    {
        xScrollBarAxis = this->oppositeAxis(xScrollBarAxis);
    }

    int yScrollBarAxis = yAxis;
    if (this->vScrollBarPosition() == OppositeToScale)
    {
        yScrollBarAxis = this->oppositeAxis(yScrollBarAxis);
    }

    QwtPlotLayout *layout = this->plot()->plotLayout();

    bool showHScrollBar = this->needScrollBar(Qt::Horizontal);
    if (showHScrollBar)
    {
        QExtPlotScrollBar *sb = this->scrollBar(Qt::Horizontal);
        sb->setPalette(plot()->palette());
        sb->setInverted(!plot()->axisScaleDiv(xAxis).isIncreasing());
        sb->setBase(d->mXMin, d->mXMax);
        sb->moveSlider(zoomRect().left(), zoomRect().right());

        if (!sb->isVisibleTo(this->canvas()))
        {
            sb->show();
            layout->setCanvasMargin(layout->canvasMargin(xScrollBarAxis) + sb->extent(), xScrollBarAxis);
        }
    }
    else
    {
        if (this->horizontalScrollBar())
        {
            this->horizontalScrollBar()->hide();
            layout->setCanvasMargin(layout->canvasMargin(xScrollBarAxis) - this->horizontalScrollBar()->extent(), xScrollBarAxis);
        }
    }

    bool showVScrollBar = this->needScrollBar(Qt::Vertical);
    if (showVScrollBar)
    {
        QExtPlotScrollBar *sb = scrollBar(Qt::Vertical);
        sb->setPalette(plot()->palette());
        sb->setInverted(plot()->axisScaleDiv(yAxis).isIncreasing());
        sb->setBase(zoomBase().top(), this->zoomBase().bottom());
        sb->moveSlider(zoomRect().top(), this->zoomRect().bottom());

        if (!sb->isVisibleTo(canvas()))
        {
            sb->show();
            layout->setCanvasMargin(layout->canvasMargin(yScrollBarAxis) + sb->extent(), yScrollBarAxis);
        }
    }
    else
    {
        if (verticalScrollBar())
        {
            verticalScrollBar()->hide();
            layout->setCanvasMargin(layout->canvasMargin(yScrollBarAxis) - this->verticalScrollBar()->extent(), yScrollBarAxis);
        }
    }

    if (showHScrollBar && showVScrollBar)
    {
        if (d->mCornerWidget == NULL)
        {
            d->mCornerWidget = new QWidget(this->canvas());
            d->mCornerWidget->setAutoFillBackground(true);
            d->mCornerWidget->setPalette(plot()->palette());
        }
        d->mCornerWidget->show();
    }
    else
    {
        if (d->mCornerWidget)
        {
            d->mCornerWidget->hide();
        }
    }

    this->layoutScrollBars(this->canvas()->contentsRect());
    this->plot()->updateLayout();
}

bool QExtPlotScrollZoomer::needScrollBar(Qt::Orientation orientation) const
{
    Q_D(const QExtPlotScrollZoomer);
    Qt::ScrollBarPolicy mode;
    double zoomMin, zoomMax, baseMin, baseMax;

    if (Qt::Horizontal == orientation)
    {
        mode = d->mHScrollData->mode;
        baseMin = d->mXMin;
        baseMax = d->mXMax;
        zoomMin = this->zoomRect().left();
        zoomMax = this->zoomRect().right();
    }
    else
    {
        mode = d->mVScrollData->mode;
        baseMin = this->zoomBase().top();
        baseMax = this->zoomBase().bottom();
        zoomMin = this->zoomRect().top();
        zoomMax = this->zoomRect().bottom();
    }

    bool needed = false;
    switch (mode)
    {
    case Qt::ScrollBarAlwaysOn:
        needed = true;
        break;
    case Qt::ScrollBarAlwaysOff:
        needed = false;
        break;
    default:
    {
        if (baseMin < zoomMin || baseMax > zoomMax)
        {
            needed = true;
        }
        break;
    }
    }
    return needed;
}

int QExtPlotScrollZoomer::oppositeAxis(int axis) const
{
    switch (axis)
    {
    case QwtPlot::xBottom:
        return QwtPlot::xTop;
    case QwtPlot::xTop:
        return QwtPlot::xBottom;
    case QwtPlot::yLeft:
        return QwtPlot::yRight;
    case QwtPlot::yRight:
        return QwtPlot::yLeft;
    default:
        break;
    }

    return axis;
}
