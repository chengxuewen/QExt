#include <qextPlotScalePicker.h>
#include <qextNumeric.h>

#include <qwt_widget_overlay.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_map.h>
#include <qwt_scale_div.h>
#include <qwt_text.h>

#include <QMouseEvent>
#include <QPainter>
#include <QPointer>
#include <QEvent>
#include <math.h>

// minimum size for pick (in pixels)
#define MIN_PICK_SIZE (2)
#define SNAP_DISTANCE (5)


namespace detail
{
void drawPlotOverlay(QExtPlotScalePicker *picker, QPainter *painter)
{
    picker->drawPlotOverlay(painter);
}
void drawScaleOverlay(QExtPlotScalePicker *picker, QPainter *painter)
{
    picker->drawScaleOverlay(painter);
}
}

class QExtPlotScalePickerOverlay : public QwtWidgetOverlay
{
public:
    typedef void(*DrawOverlayCallback)(QExtPlotScalePicker *picker, QPainter *painter);

    QExtPlotScalePickerOverlay(QWidget *widget, QExtPlotScalePicker *picker, DrawOverlayCallback callback)
        : QwtWidgetOverlay(widget), mPicker(picker), mCallback(callback) {}
    ~QExtPlotScalePickerOverlay() QEXT_OVERRIDE {}

protected:
    void drawOverlay(QPainter *painter) const QEXT_OVERRIDE
    {
        if (mCallback)
        {
            mCallback(mPicker, painter);
        }
    }

private:
    QExtPlotScalePicker *mPicker;
    DrawOverlayCallback mCallback;
};

class QExtPlotScalePickerPrivate
{
    QExtPlotScalePicker * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlotScalePicker)
    QEXT_DISABLE_COPY_MOVE(QExtPlotScalePickerPrivate)
public:
    explicit QExtPlotScalePickerPrivate(QExtPlotScalePicker *q);
    virtual ~QExtPlotScalePickerPrivate();


    QPointer<QWidget> mCanvas;
    QPointer<QwtScaleWidget> mScaleWidget;
    QPointer<QwtWidgetOverlay> mScaleOverlay;
    QPointer<QwtWidgetOverlay> mPickerOverlay;

    QPen mPen;
    int mValueResolution;

    bool mPressed;
    bool mStarted;
    double mFirstPos; // converted to plot coordinates
    double mFirstPosPx; // pixel coordinates
    double mCurrentPosPx; // current position in pixel coordinates
    QList<int> mSnapPoints;
    /// used to restore precision of snappoints that is lost due to rounding
    QMap<int, double> mSnapPointMap;
};

QExtPlotScalePickerPrivate::QExtPlotScalePickerPrivate(QExtPlotScalePicker *q)
    : q_ptr(q)
    , mValueResolution(3)
{
}

QExtPlotScalePickerPrivate::~QExtPlotScalePickerPrivate()
{
}


QExtPlotScalePicker::QExtPlotScalePicker(QwtScaleWidget *scaleWidget, QWidget *canvas)
    : QObject(scaleWidget)
    , dd_ptr(new QExtPlotScalePickerPrivate(this))
{
    Q_D(QExtPlotScalePicker);
    d->mCanvas = canvas;
    d->mScaleWidget = scaleWidget;
    scaleWidget->installEventFilter(this);
    scaleWidget->setMouseTracking(true);
    d->mPickerOverlay = new QExtPlotScalePickerOverlay(canvas, this, detail::drawPlotOverlay);
    d->mScaleOverlay = new QExtPlotScalePickerOverlay(scaleWidget, this, detail::drawScaleOverlay);
    d->mStarted = false;
    d->mPressed = false;
}

QExtPlotScalePicker::~QExtPlotScalePicker()
{
}

int QExtPlotScalePicker::valueResolution() const
{
    Q_D(const QExtPlotScalePicker);
    return d->mValueResolution;
}

void QExtPlotScalePicker::setValueResolution(int value)
{
    Q_D(QExtPlotScalePicker);
    value = qMax(0, value);
    d->mValueResolution = value;
}

bool QExtPlotScalePicker::eventFilter(QObject *object, QEvent *event)
{
    Q_D(QExtPlotScalePicker);
    if (event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::MouseButtonRelease ||
        event->type() == QEvent::MouseMove)
    {
        this->updateSnapPoints();

        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        int posPx = this->positionPx(mouseEvent);

        // do snapping unless Shift is pressed
        if (!(mouseEvent->modifiers() & Qt::ShiftModifier))
        {
            for (auto &&sp : d->mSnapPoints)
            {
                if (std::abs(posPx - sp) <= SNAP_DISTANCE)
                {
                    posPx = sp;
                    break;
                }
            }
        }

        double pos = this->position(posPx);
        d->mCurrentPosPx = posPx;

        if (event->type() == QEvent::MouseButtonPress && mouseEvent->button() == Qt::LeftButton)
        {
            d->mPressed = true; // not yet started
            d->mFirstPos = pos;
            d->mFirstPosPx = posPx;
        }
        else if (event->type() == QEvent::MouseMove)
        {
            // make sure pick size is big enough, so that just
            // clicking won't trigger pick
            if (!d->mStarted && d->mPressed && (fabs(posPx - d->mFirstPosPx) > MIN_PICK_SIZE))
            {
                d->mStarted = true;
            }
            d->mPickerOverlay->updateOverlay();
            d->mScaleOverlay->updateOverlay();
        }
        else // event->type() == QEvent::MouseButtonRelease
        {
            d->mPressed = false;
            if (d->mStarted)
            {
                // finalize
                d->mStarted = false;
                if (d->mFirstPos != pos) // ignore 0 width zoom
                {
                    emit picked(d->mFirstPos, pos);
                }
            }
            d->mPickerOverlay->updateOverlay();
            d->mScaleOverlay->updateOverlay();
        }
        return true;
    }
    else if (event->type() == QEvent::Leave)
    {
        d->mScaleOverlay->updateOverlay();
        d->mPickerOverlay->updateOverlay();
        return true;
    }
    else
    {
        return QObject::eventFilter(object, event);
    }
}

const int TEXT_MARGIN = 4;

void QExtPlotScalePicker::drawPlotOverlay(QPainter *painter)
{
    Q_D(QExtPlotScalePicker);
    const double FILL_ALPHA = 0.2;

    painter->save();
    painter->setPen(d->mPen);

    if (d->mStarted)
    {
        QColor color = d->mPen.color();
        color.setAlphaF(FILL_ALPHA);
        painter->setBrush(color);

        QRect rect;
        QwtText text = this->trackerText();
        auto tSize = text.textSize(painter->font());

        if (d->mScaleWidget->alignment() == QwtScaleDraw::BottomScale ||
            d->mScaleWidget->alignment() == QwtScaleDraw::TopScale)
        {
            int canvasHeight = painter->device()->height();
            int pickWidth = d->mCurrentPosPx - d->mFirstPosPx;
            rect = QRect(this->posCanvasPx(d->mFirstPosPx), 0, pickWidth, canvasHeight);
        }
        else // vertical
        {
            int canvasWidth = painter->device()->width();
            int pickHeight = d->mCurrentPosPx - d->mFirstPosPx;
            rect = QRect(0, this->posCanvasPx(d->mFirstPosPx), canvasWidth, pickHeight);
        }
        painter->drawRect(rect);
        text.draw(painter, this->pickTrackerTextRect(painter, rect, tSize));
    }
    else if (d->mScaleWidget->underMouse())
    {
        // draw tracker text centered on cursor
        QwtText text = this->trackerText();
        auto tsize = text.textSize(painter->font());
        text.draw(painter, this->trackerTextRect(painter, d->mCurrentPosPx, tsize));
    }
    painter->restore();
}

QwtText QExtPlotScalePicker::trackerText() const
{
    Q_D(const QExtPlotScalePicker);
    double pos;
    // use stored value if snapped to restore precision
    if (d->mSnapPointMap.contains(d->mCurrentPosPx))
    {
        pos = d->mSnapPointMap[d->mCurrentPosPx];
    }
    else
    {
        pos = this->position(d->mCurrentPosPx);
    }
    pos = QExtNumeric::reducePrecision(pos, d->mValueResolution);

    QwtText text(QString("%1").arg(pos));
    text.setColor(d->mScaleWidget->palette().windowText().color());
    return text;
}

QRectF QExtPlotScalePicker::trackerTextRect(QPainter *painter, int posPx, QSizeF textSize) const
{
    Q_D(const QExtPlotScalePicker);
    int canvasPosPx = posCanvasPx(posPx);
    QPointF topLeft;

    if (d->mScaleWidget->alignment() == QwtScaleDraw::BottomScale ||
        d->mScaleWidget->alignment() == QwtScaleDraw::TopScale)
    {
        int left = canvasPosPx - textSize.width() / 2;
        int canvasWidth = painter->device()->width();
        left = std::max(TEXT_MARGIN, left);
        left = std::min(double(left), canvasWidth - textSize.width() - TEXT_MARGIN);
        int top = 0;
        if (d->mScaleWidget->alignment() == QwtScaleDraw::BottomScale)
        {
            top = painter->device()->height() - textSize.height();
        }
        topLeft = QPointF(left, top);
    }
    else                        // left/right scales
    {
        int top = canvasPosPx - textSize.height() / 2;
        int canvasHeight = painter->device()->height();
        top = std::max(0, top);
        top = std::min(double(top), canvasHeight - textSize.height());
        int left = TEXT_MARGIN;
        if (d->mScaleWidget->alignment() == QwtScaleDraw::RightScale)
        {
            left = painter->device()->width() - textSize.width();
        }
        topLeft = QPointF(left, top);
    }
    return QRectF(topLeft, textSize);
}

QRectF QExtPlotScalePicker::pickTrackerTextRect(QPainter *painter, QRect pickRect, QSizeF textSize) const
{
    Q_D(const QExtPlotScalePicker);
    qreal left = 0;
    int pickLength = d->mCurrentPosPx - d->mFirstPosPx;
    QPointF topLeft;

    if (d->mScaleWidget->alignment() == QwtScaleDraw::BottomScale ||
        d->mScaleWidget->alignment() == QwtScaleDraw::TopScale)
    {
        int canvasWidth = painter->device()->width();

        if (pickLength > 0)
        {
            left = pickRect.right() + TEXT_MARGIN;
        }
        else
        {
            left = pickRect.right() - (textSize.width() + TEXT_MARGIN);
        }

        // make sure text is not off the canvas
        if (left < TEXT_MARGIN)
        {
            left = std::max(0, pickRect.right()) + TEXT_MARGIN;
        }
        else if (left + textSize.width() + TEXT_MARGIN > canvasWidth)
        {
            left = std::min(pickRect.right(), canvasWidth) - (textSize.width() + TEXT_MARGIN);
        }

        if (d->mScaleWidget->alignment() == QwtScaleDraw::BottomScale)
        {
            int canvasHeight = painter->device()->height();
            topLeft = QPointF(left, canvasHeight - textSize.height());
        }
        else                // top scale
        {
            topLeft = QPointF(left, 0);
        }
    }
    else                        // left/right scale
    {
        int canvasHeight = painter->device()->height();

        int top = 0;
        if (pickLength > 0)
        {
            top = pickRect.bottom();
        }
        else
        {
            top = pickRect.bottom() - textSize.height();
        }

        // make sure text is not off the canvas
        if (top < 0)
        {
            top = std::max(0, pickRect.bottom());
        }
        else if (top + textSize.height() > canvasHeight)
        {
            top = std::min(canvasHeight, pickRect.bottom()) - textSize.height();
        }

        if (d->mScaleWidget->alignment() == QwtScaleDraw::LeftScale)
        {
            topLeft = QPointF(TEXT_MARGIN, top);
        }
        else                    // right scale
        {
            int canvasWidth = painter->device()->width();
            topLeft = QPointF(canvasWidth - textSize.width() - TEXT_MARGIN, top);
        }
    }
    return QRectF(topLeft, textSize);
}

void QExtPlotScalePicker::drawScaleOverlay(QPainter *painter)
{
    Q_D(QExtPlotScalePicker);

    painter->save();
    // rotate & adjust coordinate system for vertical drawing
    if (d->mScaleWidget->alignment() == QwtScaleDraw::LeftScale ||
        d->mScaleWidget->alignment() == QwtScaleDraw::RightScale) // vertical
    {
        int width = painter->device()->width();
        painter->rotate(90);
        painter->translate(0, -width);
    }

    // draw the indicators
    if (d->mStarted)
    {
        this->drawTriangle(painter, d->mFirstPosPx);
    }
    if (d->mStarted || d->mScaleWidget->underMouse())
    {
        this->drawTriangle(painter, d->mCurrentPosPx);
    }

    painter->restore();
}

void QExtPlotScalePicker::drawTriangle(QPainter *painter, int position)
{
    Q_D(QExtPlotScalePicker);
    const double tan60 = 1.732;
    const double trsize = 10;
    const int TRIANGLE_NUM_POINTS = 3;
    const int MARGIN = 2;
    const QPointF points[TRIANGLE_NUM_POINTS] =
        {
            {0, 0},
            {-trsize / tan60, trsize},
            {trsize / tan60, trsize}
        };

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->mScaleWidget->palette().windowText());
    painter->setRenderHint(QPainter::Antialiasing);

    painter->translate(position, MARGIN);
    painter->drawPolygon(points, TRIANGLE_NUM_POINTS);

    painter->restore();
}

void QExtPlotScalePicker::setPen(QPen pen)
{
    Q_D(QExtPlotScalePicker);
    d->mPen = pen;
}

// convert the position of the click to the plot coordinates
double QExtPlotScalePicker::position(double posPx) const
{
    Q_D(const QExtPlotScalePicker);
    return d->mScaleWidget->scaleDraw()->scaleMap().invTransform(posPx);
}

int QExtPlotScalePicker::positionPx(QMouseEvent *mouseEvent)
{
    Q_D(QExtPlotScalePicker);
    double pos;
    if (d->mScaleWidget->alignment() == QwtScaleDraw::BottomScale ||
        d->mScaleWidget->alignment() == QwtScaleDraw::TopScale)
    {
        pos = mouseEvent->pos().x();
    }
    else // left or right scale
    {
        pos = mouseEvent->pos().y();
    }

    //    qDebug() << "pos=" << pos;
    return pos;
}

/*
 * Scale widget and canvas widget is not always aligned. Especially
 * when zooming scaleWidget moves around. This causes irregularities
 * when drawing the tracker lines. This function maps scale widgets
 * pixel coordinate to canvas' coordinate.
 */
double QExtPlotScalePicker::posCanvasPx(double pos) const
{
    Q_D(const QExtPlotScalePicker);
    // assumption: scale.width < canvas.width && scale.x > canvas.x
    if (d->mScaleWidget->alignment() == QwtScaleDraw::BottomScale ||
        d->mScaleWidget->alignment() == QwtScaleDraw::TopScale)
    {
        return pos + (d->mScaleWidget->x() - d->mCanvas->x());
    }
    else // left or right scale
    {
        return pos + (d->mScaleWidget->y() - d->mCanvas->y());
    }
    return pos;
}

void QExtPlotScalePicker::updateSnapPoints()
{
    Q_D(QExtPlotScalePicker);
    auto allTicks = d->mScaleWidget->scaleDraw()->scaleDiv().ticks(QwtScaleDiv::MajorTick) +
                    d->mScaleWidget->scaleDraw()->scaleDiv().ticks(QwtScaleDiv::MediumTick) +
                    d->mScaleWidget->scaleDraw()->scaleDiv().ticks(QwtScaleDiv::MinorTick);

    d->mSnapPoints.clear();
    d->mSnapPointMap.clear();
    for(auto t : allTicks)
    {
        // `round` is used because `allTicks` is double but `snapPoints` is int
        int p = round(d->mScaleWidget->scaleDraw()->scaleMap().transform(t));
        d->mSnapPoints << p;
        d->mSnapPointMap[p] = t;
    }
}
