#include <qextQwtPlotScaleZoomer.h>

#include <QDebug>
#include <QPointer>

class QExtPlotScaleZoomerPrivate
{
    QExtPlotScaleZoomer * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtPlotScaleZoomer)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotScaleZoomerPrivate)
public:
    explicit QExtPlotScaleZoomerPrivate(QExtPlotScaleZoomer *q);
    virtual ~QExtPlotScaleZoomerPrivate();

    QPointer<QwtPlot> mPlot;
    QPointer<QwtPlotZoomer> mZoomer;
    QExtPlotScalePicker *mLeftPicker;
    QExtPlotScalePicker *mBottomPicker;
};

QExtPlotScaleZoomerPrivate::QExtPlotScaleZoomerPrivate(QExtPlotScaleZoomer *q)
    : q_ptr(q)
{
}

QExtPlotScaleZoomerPrivate::~QExtPlotScaleZoomerPrivate()
{
}

QExtPlotScaleZoomer::QExtPlotScaleZoomer(QwtPlot *plot, QwtPlotZoomer *zoomer)
    : QObject(plot)
    , dd_ptr(new QExtPlotScaleZoomerPrivate(this))
{
    Q_D(QExtPlotScaleZoomer);
    d->mPlot = plot;
    d->mZoomer = zoomer;
    d->mLeftPicker = new QExtPlotScalePicker(plot->axisWidget(QwtPlot::yLeft), plot->canvas());
    connect(d->mLeftPicker, &QExtPlotScalePicker::picked, this, &QExtPlotScaleZoomer::leftPicked);
    d->mBottomPicker = new QExtPlotScalePicker(plot->axisWidget(QwtPlot::xBottom), plot->canvas());
    connect(d->mBottomPicker, &QExtPlotScalePicker::picked, this, &QExtPlotScaleZoomer::bottomPicked);
}

QExtPlotScaleZoomer::~QExtPlotScaleZoomer()
{
}

void QExtPlotScaleZoomer::setPickerPen(QPen pen)
{
    Q_D(QExtPlotScaleZoomer);
    d->mBottomPicker->setPen(pen);
    d->mLeftPicker->setPen(pen);
}

void QExtPlotScaleZoomer::setLeftPickerValueResolution(int value)
{
    Q_D(QExtPlotScaleZoomer);
    d->mLeftPicker->setValueResolution(value);
}

void QExtPlotScaleZoomer::setBottomPickerValueResolution(int value)
{
    Q_D(QExtPlotScaleZoomer);
    d->mBottomPicker->setValueResolution(value);
}

void QExtPlotScaleZoomer::leftPicked(double firstPos, double lastPos)
{
    Q_D(QExtPlotScaleZoomer);
    QRectF zRect;
    if (lastPos > firstPos)
    {
        zRect.setBottom(firstPos);
        zRect.setTop(lastPos);
    }
    else
    {
        zRect.setBottom(lastPos);
        zRect.setTop(firstPos);
    }

    zRect.setLeft(d->mPlot->axisScaleDiv(QwtPlot::xBottom).lowerBound());
    zRect.setRight(d->mPlot->axisScaleDiv(QwtPlot::xBottom).upperBound());
    d->mZoomer->zoom(zRect);
}

void QExtPlotScaleZoomer::bottomPicked(double firstPos, double lastPos)
{
    Q_D(QExtPlotScaleZoomer);
    QRectF zRect;
    if (lastPos > firstPos)
    {
        zRect.setLeft(firstPos);
        zRect.setRight(lastPos);
    }
    else
    {
        zRect.setLeft(lastPos);
        zRect.setRight(firstPos);
    }

    zRect.setBottom(d->mPlot->axisScaleDiv(QwtPlot::yLeft).lowerBound());
    zRect.setTop(d->mPlot->axisScaleDiv(QwtPlot::yLeft).upperBound());
    d->mZoomer->zoom(zRect);
}
