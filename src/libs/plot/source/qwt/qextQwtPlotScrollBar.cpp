#include <qextQwtPlotScrollBar.h>
#include <qextOnceFlag.h>

#include <QStyleOptionSlider>
#include <QDebug>

class QExtPlotScrollBarPrivate
{
    QExtPlotScrollBar * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlotScrollBar)
    QEXT_DISABLE_COPY_MOVE(QExtPlotScrollBarPrivate)
public:
    explicit QExtPlotScrollBarPrivate(QExtPlotScrollBar *q);
    virtual ~QExtPlotScrollBarPrivate();

    int mBaseTicks;
    bool mInverted;
    double mMinBase;
    double mMaxBase;
    QExtOnceFlag mInitFlag;
};

QExtPlotScrollBarPrivate::QExtPlotScrollBarPrivate(QExtPlotScrollBar *q)
    : q_ptr(q)
{
}

QExtPlotScrollBarPrivate::~QExtPlotScrollBarPrivate()
{
}


QExtPlotScrollBar::QExtPlotScrollBar(QWidget *parent)
    : QScrollBar(parent)
    , dd_ptr(new QExtPlotScrollBarPrivate(this))
{
    this->init();
}

QExtPlotScrollBar::QExtPlotScrollBar(Qt::Orientation orientation, QWidget *parent)
    : QScrollBar(orientation, parent)
    , dd_ptr(new QExtPlotScrollBarPrivate(this))
{
    this->init();
}

QExtPlotScrollBar::QExtPlotScrollBar(double minBase, double maxBase, Qt::Orientation orientation, QWidget *parent)
    : QScrollBar(orientation, parent)
    , dd_ptr(new QExtPlotScrollBarPrivate(this))
{
    this->init(minBase, maxBase);
}

QExtPlotScrollBar::~QExtPlotScrollBar()
{
}

bool QExtPlotScrollBar::isInverted() const
{
    Q_D(const QExtPlotScrollBar);
    return d->mInverted;
}

void QExtPlotScrollBar::setInverted(bool inverted)
{
    Q_D(QExtPlotScrollBar);
    if (d->mInverted != inverted)
    {
        d->mInverted = inverted;
        this->moveSlider(this->minSliderValue(), this->maxSliderValue());
    }
}

double QExtPlotScrollBar::minBaseValue() const
{
    Q_D(const QExtPlotScrollBar);
    return d->mMinBase;
}

double QExtPlotScrollBar::maxBaseValue() const
{
    Q_D(const QExtPlotScrollBar);
    return d->mMaxBase;
}

double QExtPlotScrollBar::minSliderValue() const
{
    double min, dummy;
    this->sliderRange(this->value(), min, dummy);
    return min;
}

double QExtPlotScrollBar::maxSliderValue() const
{
    double max, dummy;
    this->sliderRange(this->value(), dummy, max);
    return max;
}

int QExtPlotScrollBar::extent() const
{
    QStyleOptionSlider opt;
    opt.init(this);
    opt.subControls = QStyle::SC_None;
    opt.activeSubControls = QStyle::SC_None;
    opt.orientation = this->orientation();
    opt.minimum = this->minimum();
    opt.maximum = this->maximum();
    opt.sliderPosition = this->sliderPosition();
    opt.sliderValue = this->value();
    opt.singleStep = this->singleStep();
    opt.pageStep = this->pageStep();
    opt.upsideDown = this->invertedAppearance();
    if (this->orientation() == Qt::Horizontal)
    {
        opt.state |= QStyle::State_Horizontal;
    }
    return this->style()->pixelMetric(QStyle::PM_ScrollBarExtent, &opt, this);
}

void QExtPlotScrollBar::init()
{
    Q_D(QExtPlotScrollBar);
    if (d->mInitFlag.enter())
    {
        d->mInverted = this->orientation() == Qt::Vertical;
        d->mBaseTicks = 1000000;
        d->mMinBase = 0.0;
        d->mMaxBase = 1.0;
        this->moveSlider(d->mMinBase, d->mMaxBase);

        connect(this, SIGNAL(sliderMoved(int)), SLOT(catchSliderMoved(int)));
        connect(this, SIGNAL(valueChanged(int)), SLOT(catchValueChanged(int)));
        d->mInitFlag.leave();
    }
}

void QExtPlotScrollBar::setBase(double min, double max)
{
    Q_D(QExtPlotScrollBar);
    if (min != d->mMinBase || max != d->mMaxBase)
    {
        d->mMinBase = min;
        d->mMaxBase = max;

        this->moveSlider(minSliderValue(), maxSliderValue());
    }
}

void QExtPlotScrollBar::moveSlider(double min, double max)
{
    Q_D(QExtPlotScrollBar);
    const int sliderTicks = qRound((max - min) / (d->mMaxBase - d->mMinBase) * d->mBaseTicks);

    // setRange initiates a valueChanged of the scrollbars
    // in some situations. So we block
    // and unblock the signals.

    this->blockSignals(true);

    this->setRange(sliderTicks / 2, d->mBaseTicks - sliderTicks / 2);
    int steps = sliderTicks / 200;
    if (steps <= 0)
    {
        steps = 1;
    }

    this->setSingleStep(steps);
    this->setPageStep(sliderTicks);

    int tick = this->mapToTick(min + (max - min) / 2);
    if (this->isInverted())
    {
        tick = d->mBaseTicks - tick;
    }

    this->setSliderPosition(tick);
    this->blockSignals(false);
}

void QExtPlotScrollBar::catchValueChanged(int value)
{
    double min, max;
    this->sliderRange(value, min, max);
    Q_EMIT this->valueChangedWithRange(this->orientation(), min, max);
}

void QExtPlotScrollBar::catchSliderMoved(int value)
{
    double min, max;
    this->sliderRange(value, min, max);
    Q_EMIT this->sliderMovedWithRange(this->orientation(), min, max);
}

void QExtPlotScrollBar::sliderRange(int value, double &min, double &max) const
{
    Q_D(const QExtPlotScrollBar);
    if (this->isInverted())
    {
        value = d->mBaseTicks - value;
    }

    const int visibleTicks = this->pageStep();

    min = this->mapFromTick(value - visibleTicks / 2);
    max = this->mapFromTick(value + visibleTicks / 2);
}

double QExtPlotScrollBar::mapFromTick(int tick) const
{
    Q_D(const QExtPlotScrollBar);
    return d->mMinBase + (d->mMaxBase - d->mMinBase) * tick / d->mBaseTicks;
}

int QExtPlotScrollBar::mapToTick(double value) const
{
    Q_D(const QExtPlotScrollBar);
    const double pos = (value - d->mMinBase) / (d->mMaxBase - d->mMinBase) * d->mBaseTicks;
    return static_cast<int>(pos);
}
