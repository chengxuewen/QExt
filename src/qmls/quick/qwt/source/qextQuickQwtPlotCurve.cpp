#include <private/qextQuickQwtPlotCurve_p.h>
#include <private/qextQuickQwtSeriesData_p.h>
#include <private/qextQuickQwtPlot_p.h>

QExtQuickQwtPlotCurvePrivate::QExtQuickQwtPlotCurvePrivate(QExtQuickQwtPlotCurve *q)
    : q_ptr(q)
{
    mQwtPlotCurve->setPen(mQExtQmlPenInfo.pen());
    mQwtPlotCurve->setRenderHint(QwtPlotCurve::RenderAntialiased);
}

QExtQuickQwtPlotCurvePrivate::~QExtQuickQwtPlotCurvePrivate()
{
}

QExtQuickQwtPlotCurvePrivate::Style QExtQuickQwtPlotCurvePrivate::fromQwt(QwtPlotCurve::CurveStyle style)
{
    switch (style)
    {
    case QwtPlotCurve::NoCurve: return Style::NoCurve;
    case QwtPlotCurve::Lines: return Style::Lines;
    case QwtPlotCurve::Sticks: return Style::Sticks;
    case QwtPlotCurve::Steps: return Style::Steps;
    case QwtPlotCurve::Dots: return Style::Dots;
    case QwtPlotCurve::UserCurve: return Style::UserCurve;
    default: break;
    }
    return Style::NoCurve;
}

QExtQuickQwtPlotCurvePrivate::RenderHint QExtQuickQwtPlotCurvePrivate::fromQwt(QwtPlotItem::RenderHint hint)
{
    switch (hint)
    {
    case QwtPlotCurve::RenderAntialiased: return RenderHint::Antialiasing;
    default: break;
    }
    return RenderHint::Antialiasing;
}

QExtQuickQwtPlotCurvePrivate::Attribute QExtQuickQwtPlotCurvePrivate::fromQwt(QwtPlotCurve::CurveAttribute attribute)
{
    switch (attribute)
    {
    case QwtPlotCurve::Fitted: return Attribute::Fitted;
    case QwtPlotCurve::Inverted: return Attribute::Inverted;
    default: break;
    }
    return Attribute::Fitted;
}

QwtPlotCurve::CurveStyle QExtQuickQwtPlotCurvePrivate::toQwt(Style style)
{
    switch (style)
    {
    case Style::NoCurve: return QwtPlotCurve::NoCurve;
    case Style::Lines: return QwtPlotCurve::Lines;
    case Style::Sticks: return QwtPlotCurve::Sticks;
    case Style::Steps: return QwtPlotCurve::Steps;
    case Style::Dots: return QwtPlotCurve::Dots;
    case Style::UserCurve: return QwtPlotCurve::UserCurve;
    default: break;
    }
    return QwtPlotCurve::NoCurve;
}

QwtPlotItem::RenderHint QExtQuickQwtPlotCurvePrivate::toQwt(RenderHint hint)
{
    switch (hint)
    {
    case RenderHint::Antialiasing: return QwtPlotCurve::RenderAntialiased;
    default: break;
    }
    return QwtPlotCurve::RenderAntialiased;
}

QwtPlotCurve::CurveAttribute QExtQuickQwtPlotCurvePrivate::toQwt(Attribute attribute)
{
    switch (attribute)
    {
    case Attribute::Fitted: return QwtPlotCurve::Fitted;
    case Attribute::Inverted: return QwtPlotCurve::Inverted;
    default: break;
    }
    return QwtPlotCurve::Fitted;
}

QExtQuickQwtPlotCurve::QExtQuickQwtPlotCurve(QObject* parent)
    : QExtQuickQwtPlotCurve(new QExtQuickQwtPlotCurvePrivate(this), parent)
{
}

QExtQuickQwtPlotCurve::QExtQuickQwtPlotCurve(const QString &title, QObject *parent)
    : QExtQuickQwtPlotCurve(new QExtQuickQwtPlotCurvePrivate(this), parent)
{
    Q_D(QExtQuickQwtPlotCurve);
    d->mQwtPlotCurve->setTitle(title);
}

QExtQuickQwtPlotCurve::QExtQuickQwtPlotCurve(QExtQuickQwtPlotCurvePrivate *d, QObject *parent)
    : QObject(parent)
    , dd_ptr(d)
{
    connect(&d->mQExtQmlPenInfo, &QExtQmlPenInfo::penChanged, this, [d, this](const QPen &pen)
    {
        d->mQwtPlotCurve->setPen(pen);
        emit this->penChanged(d->mQExtQmlPenInfo);
    });
    d->mQwtPlotCurve->setPen(d->mQExtQmlPenInfo.pen());
}

QExtQuickQwtPlotCurve::~QExtQuickQwtPlotCurve()
{
    Q_D(QExtQuickQwtPlotCurve);
    this->resetData();
}

QExtQuickQwtPlot *QExtQuickQwtPlotCurve::plot() const
{
    Q_D(const QExtQuickQwtPlotCurve);
    return d->mQwtPlot.data();
}

void QExtQuickQwtPlotCurve::setPlot(QExtQuickQwtPlot *plot)
{
    Q_D(QExtQuickQwtPlotCurve);
    if (plot != d->mQwtPlot.data())
    {
        d->mQwtPlot = plot;
        d->mQwtPlotCurve->attach(plot ? plot->d_func()->qwtPlot() : nullptr);
        emit this->plotChanged(plot);
    }
}

QExtQmlPenInfo *QExtQuickQwtPlotCurve::pen()
{
    Q_D(QExtQuickQwtPlotCurve);
    return &d->mQExtQmlPenInfo;
}

const QExtQmlPenInfo *QExtQuickQwtPlotCurve::pen() const
{
    Q_D(const QExtQuickQwtPlotCurve);
    return &d->mQExtQmlPenInfo;
}

QColor QExtQuickQwtPlotCurve::penColor() const
{
    Q_D(const QExtQuickQwtPlotCurve);
    return d->mQExtQmlPenInfo.color();
}

void QExtQuickQwtPlotCurve::setPenColor(const QColor &color)
{
    Q_D(QExtQuickQwtPlotCurve);
    d->mQExtQmlPenInfo.setColor(color);
}

QExtQuickQwtPlotCurve::Style QExtQuickQwtPlotCurve::style() const
{
    Q_D(const QExtQuickQwtPlotCurve);
    return d->fromQwt(d->mQwtPlotCurve->style());
}

void QExtQuickQwtPlotCurve::setStyle(Style style)
{
    Q_D(QExtQuickQwtPlotCurve);
    if (this->style() != style)
    {
        d->mQwtPlotCurve->setStyle(d->toQwt(style));
        emit this->styleChanged(style);
    }
}

bool QExtQuickQwtPlotCurve::antialiasing() const
{
    return this->testRenderHint(RenderHint::Antialiasing);
}

void QExtQuickQwtPlotCurve::setAntialiasing(bool on)
{
    if (this->antialiasing() != on)
    {
        this->setRenderHint(RenderHint::Antialiasing, on);
    }
}

bool QExtQuickQwtPlotCurve::testRenderHint(RenderHint hint) const
{
    Q_D(const QExtQuickQwtPlotCurve);
    return d->mQwtPlotCurve->testRenderHint(d->toQwt(hint));
}

void QExtQuickQwtPlotCurve::setRenderHint(RenderHint hint, bool on)
{
    Q_D(QExtQuickQwtPlotCurve);
    if (this->testRenderHint(hint) != on)
    {
        d->mQwtPlotCurve->setRenderHint(d->toQwt(hint), on);
        emit this->renderHintChanged(hint, on);
        if (RenderHint::Antialiasing == hint)
        {
            emit this->antialiasingChanged(on);
        }
    }
}

bool QExtQuickQwtPlotCurve::testAttribute(Attribute attribute) const
{
    Q_D(const QExtQuickQwtPlotCurve);
    return d->mQwtPlotCurve->testCurveAttribute(d->toQwt(attribute));
}

void QExtQuickQwtPlotCurve::setAttribute(Attribute attribute, bool on)
{
    Q_D(QExtQuickQwtPlotCurve);
    if (this->testAttribute(attribute) != on)
    {
        d->mQwtPlotCurve->setCurveAttribute(d->toQwt(attribute), on);
        emit this->attributeChanged(attribute, on);
    }
}

void QExtQuickQwtPlotCurve::onDataChanged()
{
    Q_D(QExtQuickQwtPlotCurve);
    d->mQwtPlotCurve->setData(new QExtQuickQwtSeriesDataAdaptor(this->data()));
    emit this->seriesDataChanged(this->data());
}
