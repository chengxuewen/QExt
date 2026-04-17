#include <qextQmlPenInfo.h>

class QExtQmlPenInfoPrivate
{
public:
    explicit QExtQmlPenInfoPrivate(QExtQmlPenInfo *q);
    virtual ~QExtQmlPenInfoPrivate();

    QExtQmlPenInfo * const q_ptr;

    QPen mPen;

private:
    QEXT_DECLARE_PUBLIC(QExtQmlPenInfo)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlPenInfoPrivate)
};

QExtQmlPenInfoPrivate::QExtQmlPenInfoPrivate(QExtQmlPenInfo *q)
    : q_ptr(q)
{
}

QExtQmlPenInfoPrivate::~QExtQmlPenInfoPrivate()
{
}

QExtQmlPenInfo::QExtQmlPenInfo(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlPenInfoPrivate(this))
{
}

QExtQmlPenInfo::QExtQmlPenInfo(Qt::PenStyle style, QObject *parent)
    : QExtQmlPenInfo(parent)
{
    this->setStyle(style);
}

QExtQmlPenInfo::QExtQmlPenInfo(const QColor &color, QObject *parent)
    : QExtQmlPenInfo(parent)
{
    this->setColor(color);
}

QExtQmlPenInfo::~QExtQmlPenInfo()
{
}

const QPen &QExtQmlPenInfo::pen() const
{
    Q_D(const QExtQmlPenInfo);
    return d->mPen;
}

void QExtQmlPenInfo::setPen(const QPen &pen)
{
    Q_D(QExtQmlPenInfo);
    if (pen != d->mPen)
    {
        d->mPen = pen;
        emit this->penChanged(d->mPen);
    }
}

qreal QExtQmlPenInfo::width() const
{
    Q_D(const QExtQmlPenInfo);
    return d->mPen.widthF();
}

void QExtQmlPenInfo::setWidth(qreal width)
{
    Q_D(QExtQmlPenInfo);
    if (!qFuzzyCompare(width, d->mPen.widthF()))
    {
        d->mPen.setWidthF(width);
        emit this->penChanged(d->mPen);
        emit this->widthChanged(width);
    }
}

QColor QExtQmlPenInfo::color() const
{
    Q_D(const QExtQmlPenInfo);
    return d->mPen.color();
}

void QExtQmlPenInfo::setColor(const QColor &color)
{
    Q_D(QExtQmlPenInfo);
    if (color != d->mPen.color())
    {
        d->mPen.setColor(color);
        emit this->penChanged(d->mPen);
        emit this->colorChanged(color);
    }
}

Qt::PenStyle QExtQmlPenInfo::style() const
{
    Q_D(const QExtQmlPenInfo);
    return d->mPen.style();
}

void QExtQmlPenInfo::setStyle(Qt::PenStyle style)
{
    Q_D(QExtQmlPenInfo);
    if (style != d->mPen.style())
    {
        d->mPen.setStyle(style);
        emit this->penChanged(d->mPen);
        emit this->styleChanged(style);
    }
}

Qt::PenCapStyle QExtQmlPenInfo::capStyle() const
{
    Q_D(const QExtQmlPenInfo);
    return d->mPen.capStyle();
}

void QExtQmlPenInfo::setCapStyle(Qt::PenCapStyle pcs)
{
    Q_D(QExtQmlPenInfo);
    if (pcs != d->mPen.capStyle())
    {
        d->mPen.setCapStyle(pcs);
        emit this->penChanged(d->mPen);
        emit this->capStyleChanged(pcs);
    }
}

Qt::PenJoinStyle QExtQmlPenInfo::joinStyle() const
{
    Q_D(const QExtQmlPenInfo);
    return d->mPen.joinStyle();
}

void QExtQmlPenInfo::setJoinStyle(Qt::PenJoinStyle pcs)
{
    Q_D(QExtQmlPenInfo);
    if (pcs != d->mPen.joinStyle())
    {
        d->mPen.setJoinStyle(pcs);
        emit this->penChanged(d->mPen);
        emit this->joinStyleChanged(pcs);
    }
}
