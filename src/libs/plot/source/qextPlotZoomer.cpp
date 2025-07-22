#include <qextPlotZoomer.h>

#include <qwt_plot.h>
#include <qwt_scale_map.h>
#include <qwt_scale_widget.h>
#include <qwt_widget_overlay.h>

#include <QPen>
#include <QtMath>
#include <QPainter>
#include <QPointer>
#include <QMouseEvent>
#include <QPainterPath>
#include <QApplication>

#include <algorithm>

static const int VALUE_POINT_DIAM = 4;
static const int VALUE_TEXT_MARGIN = VALUE_POINT_DIAM + 2;

const double ValueLabelHeight = 12; // TODO: calculate

class QExtPlotZoomerScaleOverlay : public QwtWidgetOverlay
{
public:
    QExtPlotZoomerScaleOverlay(QWidget *widget, QExtPlotZoomer *zoomer);
    ~QExtPlotZoomerScaleOverlay() QEXT_OVERRIDE {}

protected:
    virtual void drawOverlay(QPainter *painter) const;

private:
    QExtPlotZoomer *mZoomer;
};


QExtPlotZoomerScaleOverlay::QExtPlotZoomerScaleOverlay(QWidget *widget, QExtPlotZoomer *zoomer)
    : QwtWidgetOverlay(widget)
    , mZoomer(zoomer)
{
}

void QExtPlotZoomerScaleOverlay::drawOverlay(QPainter *painter) const
{
    mZoomer->drawScaleOverlay(painter);
}

class QExtPlotZoomerPrivate
{
    QExtPlotZoomer * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlotZoomer)
    QEXT_DISABLE_COPY_MOVE(QExtPlotZoomerPrivate)
public:
    explicit QExtPlotZoomerPrivate(QExtPlotZoomer *q);
    virtual ~QExtPlotZoomerPrivate() {}

    bool mIsPanning;
    QPointF mPanPoint;
    /// displayed channels for value tracking
    QwtPlot *mPlot;

    int mValueResolution;

    bool mShiftModifier;
    bool mPressDragEnable;
    bool mDrawValuesEnable;

    // QVector< const MVChannel * > mDispChannels;

    QPointer<QwtScaleWidget> mScaleWidget;
    // QExtPlotZoomerValueDrawFunc mValueDrawFunc;
    QPointer<QExtPlotZoomerScaleOverlay> mZoomerScaleOverlay;
};

QExtPlotZoomerPrivate::QExtPlotZoomerPrivate(QExtPlotZoomer *q)
    : q_ptr(q)
    , mIsPanning(false)
    , mShiftModifier(false)
    , mPressDragEnable(false)
    , mDrawValuesEnable(true)
{
    mValueResolution = 0;
    // mValueDrawFunc = QEXT_NULLPTR;
}



QExtPlotZoomer::QExtPlotZoomer(QwtPlot *plot)
    : QExtPlotScrollZoomer(plot->canvas())
    , dd_ptr(new QExtPlotZoomerPrivate(this))
{
    Q_D(QExtPlotZoomer);
    d->mPlot = plot;
    d->mScaleWidget = plot->axisWidget(QwtPlot::xBottom);
    d->mZoomerScaleOverlay = new QExtPlotZoomerScaleOverlay(d->mScaleWidget.data(), this);

    this->setTrackerMode(AlwaysOn);
    // set corner widget between the scrollbars with default background color
    auto cornerWidget = new QWidget;
    auto bgColor = cornerWidget->palette().color(QPalette::Window).name();
    auto styleSheet = QString("background-color:%1;").arg(bgColor);
    cornerWidget->setStyleSheet(styleSheet);
    QExtPlotScrollZoomer::setCornerWidget(cornerWidget);
}

QExtPlotZoomer::~QExtPlotZoomer()
{
}

int QExtPlotZoomer::valueResolution() const
{
    Q_D(const QExtPlotZoomer);
    return d->mValueResolution;
}

void QExtPlotZoomer::setValueResolution(int value)
{
    Q_D(QExtPlotZoomer);
    value = qMax(0, value);
    d->mValueResolution = value;
}

bool QExtPlotZoomer::isPressDragEnable() const
{
    Q_D(const QExtPlotZoomer);
    return d->mPressDragEnable;
}

void QExtPlotZoomer::setPressDragEnable(bool enable)
{
    Q_D(QExtPlotZoomer);
    d->mPressDragEnable = enable;
    this->updateCursor();
}

bool QExtPlotZoomer::isDrawValuesEnable() const
{
    Q_D(const QExtPlotZoomer);
    return d->mDrawValuesEnable;
}

void QExtPlotZoomer::setDrawValuesEnable(bool enable)
{
    Q_D(QExtPlotZoomer);
    d->mDrawValuesEnable = enable;
}

void QExtPlotZoomer::zoom(int up)
{
    QExtPlotScrollZoomer::zoom(up);
    if (this->zoomRectIndex() == 0)
    {
        emit this->unzoomed();
    }
}

void QExtPlotZoomer::zoom(const QRectF &rect)
{
    // set the zoom base when user zooms in to first level
    if (this->zoomRectIndex() == 0)
    {
        this->setZoomBase(false);
    }

    QExtPlotScrollZoomer::zoom(rect);
}

// void QExtPlotZoomer::setDispChannels(QVector< const MVChannel * > channels)
// {
//     Q_D(QExtPlotZoomer);
//     d->mDispChannels = channels;
// }

// void QExtPlotZoomer::setValueDrawFunc(QExtPlotZoomerValueDrawFunc func)
// {
//     Q_D(QExtPlotZoomer);
//     d->mValueDrawFunc = func;
// }

void QExtPlotZoomer::drawScaleOverlay(QPainter *painter)
{
    Q_D(QExtPlotZoomer);
#if 0
    if (d->mDispChannels.length())
    {
        painter->save();

        auto tpos = this->trackerPosition();
        if (tpos.x() >= 0)
        {
            double x = MVCommonUtils::reducePrecision(this->invTransform(tpos).x(), d->mValueResolution);
            double position = d->mScaleWidget->scaleDraw()->scaleMap().transform(x);
            QString text = QString("%1").arg(x);
            painter->setPen(d->mScaleWidget->palette().text().color());
            QFontMetrics fm(painter->font());
            QRect rect = fm.boundingRect(text);
            rect.setX(position - rect.width() / 2);
            rect.setY(rect.height());
            painter->drawText(rect, Qt::AlignVCenter | Qt::TextDontClip, text);
        }
        painter->restore();
    }
#endif
}

QPointF QExtPlotZoomer::transToValue(const QPoint &point) const
{
    return this->invTransform(point);
}

QPoint QExtPlotZoomer::transToPos(const QPointF &point) const
{
    return this->transform(point);
}

QwtText QExtPlotZoomer::trackerTextF(const QPointF &pos) const
{
    Q_D(const QExtPlotZoomer);
    QwtText b = QExtPlotScrollZoomer::trackerTextF(pos);

    const QPolygon pa = this->selection();
    if (!this->isActive() || pa.count() < 2)
    {
        return b;
    }

    auto foreground = d->mPlot->palette().color(QPalette::Normal, QPalette::Foreground);
    const QRectF rect = this->invTransform(QRect(pa.first(), pa.last()).normalized());
    QString sizeText = QString(" [%1, %2]").arg(rect.width(), 0, 'g', 4).arg(rect.height(), 0, 'g', 4);
    b.setText(b.text() + sizeText);
    b.setColor(foreground);
    return b;
}

void QExtPlotZoomer::drawRubberBand(QPainter *painter) const
{
    Q_D(const QExtPlotZoomer);
    const double FILL_ALPHA = 0.2;
    auto foreground = d->mPlot->palette().color(QPalette::Normal, QPalette::Foreground);
    painter->setPen(foreground);
    foreground.setAlphaF(FILL_ALPHA);
    painter->setBrush(foreground);
    QExtPlotScrollZoomer::drawRubberBand(painter);
}

QRegion QExtPlotZoomer::rubberBandMask() const
{
    const QPolygon pa = this->selection();
    if (pa.count() < 2)
    {
        return QRegion();
    }
    const QRect r = QRect(pa.first(), pa.last()).normalized().adjusted(0, 0, 1, 1);
    return QRegion(r);
}

void QExtPlotZoomer::drawTracker(QPainter *painter) const
{
    Q_D(const QExtPlotZoomer);
    if (this->isActive())
    {
        QwtPlotZoomer::drawTracker(painter);
    }
    // else if (d->mValueDrawFunc)
    // {
    //     d->mValueDrawFunc(this, painter);
    // }
    // else if (d->mDispChannels.length())
    // {
    //     this->drawValues(painter);
    //     d->mZoomerScaleOverlay->updateOverlay();
    // }
}

// QList< const MVChannel * > QExtPlotZoomer::visChannels() const
// {
//     Q_D(const QExtPlotZoomer);
//     QList< const MVChannel * > result;

//     for (unsigned ci = 0; ci < (unsigned)d->mDispChannels.length(); ci++)
//     {
//         result.append(d->mDispChannels[ci]);
//     }

//     return result;
// }

void QExtPlotZoomer::drawValues(QPainter *painter) const
{
    Q_D(const QExtPlotZoomer);
    if (!d->mDrawValuesEnable)
    {
        return;
    }
    auto tpos = this->trackerPosition();
    if (tpos.x() < 0)
    {
        return; // cursor not on window
    }

#if 0
    // find values for current cursor X position
    double xValue = this->invTransform(tpos).x();
    double yValue = this->invTransform(tpos).y();
    // auto channels = this->visChannels();
    // QList< MVChannelValue > values;
    // for (auto &&ch : channels)
    // {
    //     auto value = ch->findValue(xValue, yValue);
    //     auto findValue = value.value;
    //     if (!std::isnan(findValue))
    //     {
    //         auto point = this->transform(QPointF(xValue, findValue));
    //         values.append({ ch, value.text, xValue, findValue, double(point.x()), double(point.y())});
    //     }
    // }

    // TODO should keep?
    if (values.isEmpty())
    {
        return;
    }
    // mvLayoutValues(values);

    painter->save();

    // draw vertical line
    auto foreground = d->mPlot->palette().color(QPalette::Normal, QPalette::Foreground);
    auto linePen = this->rubberBandPen();
    linePen.setStyle(Qt::DotLine);
    linePen.setColor(foreground);
    painter->setPen(linePen);
    const QRect pRect = this->pickArea().boundingRect().toRect();
    int px = tpos.x();
    painter->drawLine(px, pRect.top(), px, pRect.bottom());

    // draw sample values
    for (auto &&value : values)
    {
        auto ch = value.ch;
        auto point = QPointF(value.xPos, value.yPos);

        auto chColor = ch->color();
        const auto lightness = chColor.lightness();
        const auto fixColor = lightness > 128 ? chColor.darker() : chColor.lighter();

        painter->setPen(Qt::NoPen);
        painter->setBrush(fixColor);
        painter->drawEllipse(point, VALUE_POINT_DIAM, VALUE_POINT_DIAM);

        //        painter->setPen(rubberBandPen());
        QFontMetrics fontMetrics(d->mPlot->font());
        const auto textRect = fontMetrics.boundingRect(value.valueText);
        // qDebug() << "textRect=" << textRect;
        painter->setPen(d->mPlot->palette().windowText().color());
        painter->setBrush(d->mPlot->palette().background());
        painter->drawRoundedRect(QRectF(point.x() + VALUE_TEXT_MARGIN / 2, value.yPos - textRect.height() / 2,
                                        textRect.width() + VALUE_TEXT_MARGIN + 1, textRect.height()), 2, 2);
        // We give a very small (1x1) rectangle but disable clipping
        painter->drawText(QRectF(point.x() + VALUE_TEXT_MARGIN, value.yPos, 1, 1),
                          Qt::AlignVCenter | Qt::TextDontClip, value.valueText);
    }

    painter->restore();
#endif
}

QRect QExtPlotZoomer::trackerRect(const QFont &font) const
{
    if (this->isActive())
    {
        return QwtPlotZoomer::trackerRect(font);
    }
    else
    {
        return this->valueTrackerRect(font);
    }
}

QRect QExtPlotZoomer::valueTrackerRect(const QFont &font) const
{
    Q_D(const QExtPlotZoomer);
    // TODO: consider using actual tracker values for width calculation
    const int textWidth = qCeil(QwtText("-8.8888888").textSize(font).width());
    // const int width = textWidth + VALUE_POINT_DIAM + VALUE_TEXT_MARGIN;
    const int x = this->trackerPosition().x() - VALUE_POINT_DIAM;
    const auto pickRect = this->pickArea().boundingRect();

    const auto canvasRect = d->mPlot->canvas()->rect();
    return QRect(0, 0, canvasRect.width(), pickRect.height());
}

void QExtPlotZoomer::widgetMousePressEvent(QMouseEvent *mouseEvent)
{
    Q_D(QExtPlotZoomer);
    if ((d->mShiftModifier || d->mPressDragEnable) && !d->mIsPanning)
    {
        d->mIsPanning = true;
        d->mPanPoint = invTransform(mouseEvent->pos());
        this->updateCursor();
    }
    else
    {
        QExtPlotScrollZoomer::widgetMousePressEvent(mouseEvent);
    }
}

void QExtPlotZoomer::widgetMouseMoveEvent(QMouseEvent *mouseEvent)
{
    Q_D(QExtPlotZoomer);
    if (d->mIsPanning)
    {
        auto cur_point = invTransform(mouseEvent->pos());
        auto delta = cur_point - d->mPanPoint;
        this->moveBy(-delta.x(), -delta.y());
        d->mPanPoint = invTransform(mouseEvent->pos());
    }
    else
    {
        QExtPlotScrollZoomer::widgetMouseMoveEvent(mouseEvent);
    }
}

void QExtPlotZoomer::widgetMouseReleaseEvent(QMouseEvent *mouseEvent)
{
    Q_D(QExtPlotZoomer);
    if (d->mIsPanning)
    {
        d->mIsPanning = false;
        this->updateCursor();
    }
    else
    {
        QExtPlotScrollZoomer::widgetMouseReleaseEvent(mouseEvent);
    }
}

void QExtPlotZoomer::widgetMouseDoubleClickEvent(QMouseEvent *mouseEvent)
{
    this->zoom(0);
    QExtPlotScrollZoomer::widgetMouseDoubleClickEvent(mouseEvent);
}

void QExtPlotZoomer::widgetKeyPressEvent(QKeyEvent *keyEvent)
{
    Q_D(QExtPlotZoomer);
    if ((keyEvent->modifiers() & Qt::ShiftModifier) && !d->mShiftModifier)
    {
        d->mShiftModifier = true;
        this->updateCursor();
    }
    QExtPlotScrollZoomer::widgetKeyPressEvent(keyEvent);
}

void QExtPlotZoomer::widgetKeyReleaseEvent(QKeyEvent *keyEvent)
{
    Q_D(QExtPlotZoomer);
    if (!(keyEvent->modifiers() & Qt::ShiftModifier) && d->mShiftModifier)
    {
        d->mShiftModifier = false;
        this->updateCursor();
    }
    QExtPlotScrollZoomer::widgetKeyReleaseEvent(keyEvent);
}

void QExtPlotZoomer::updateCursor()
{
    Q_D(QExtPlotZoomer);
    if (d->mPressDragEnable || d->mIsPanning)
    {
        this->parentWidget()->setCursor(Qt::ClosedHandCursor);
    }
    else if (!this->isEnabled())
    {
        this->parentWidget()->setCursor(Qt::SizeVerCursor);
    }
    else
    {
        this->parentWidget()->setCursor(Qt::CrossCursor);
    }
}

