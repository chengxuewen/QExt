#include <qextQmlQuickBackgroundGadget.h>
#include <qextQmlQuickBackgroundGadget_p.h>

#include <QDebug>

QEXTQmlQuickBackgroundGadgetPrivate::QEXTQmlQuickBackgroundGadgetPrivate(QEXTQmlQuickBackgroundGadget *q)
    : q_ptr(q)
{
    m_color = QColor("#FFFFF");
    m_radius = 0;
    m_width = 0;
    m_height = 0;
    m_opacity = 1;
    m_scale = 1;
    m_visible = true;
}

QEXTQmlQuickBackgroundGadgetPrivate::~QEXTQmlQuickBackgroundGadgetPrivate()
{

}



QEXTQmlQuickBackgroundGadget::QEXTQmlQuickBackgroundGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQmlQuickBackgroundGadgetPrivate(this))
{

}

QEXTQmlQuickBackgroundGadget::~QEXTQmlQuickBackgroundGadget()
{

}

qreal QEXTQmlQuickBackgroundGadget::scale() const
{
    Q_D(const QEXTQmlQuickBackgroundGadget);
    return d->m_scale;
}

qreal QEXTQmlQuickBackgroundGadget::opacity() const
{
    Q_D(const QEXTQmlQuickBackgroundGadget);
    return d->m_opacity;
}

qreal QEXTQmlQuickBackgroundGadget::radius() const
{
    Q_D(const QEXTQmlQuickBackgroundGadget);
    return d->m_radius;
}

QColor QEXTQmlQuickBackgroundGadget::color() const
{
    Q_D(const QEXTQmlQuickBackgroundGadget);
    return d->m_color;
}

bool QEXTQmlQuickBackgroundGadget::isVisible() const
{
    Q_D(const QEXTQmlQuickBackgroundGadget);
    return d->m_visible;
}

qreal QEXTQmlQuickBackgroundGadget::width() const
{
    Q_D(const QEXTQmlQuickBackgroundGadget);
    return d->m_width;
}

qreal QEXTQmlQuickBackgroundGadget::height() const
{
    Q_D(const QEXTQmlQuickBackgroundGadget);
    return d->m_height;
}

void QEXTQmlQuickBackgroundGadget::setWidth(const qreal &width)
{
    Q_D(QEXTQmlQuickBackgroundGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged();
    }
}

void QEXTQmlQuickBackgroundGadget::setHeight(const qreal &height)
{
    Q_D(QEXTQmlQuickBackgroundGadget);
    if (height != d->m_height) {
        d->m_height = height;
        emit this->heightChanged();
    }
}

void QEXTQmlQuickBackgroundGadget::setOpacity(const qreal &opacity)
{
    Q_D(QEXTQmlQuickBackgroundGadget);
    if (!qFuzzyCompare(d->m_opacity, opacity)) {
        d->m_opacity = opacity;
        emit this->opacityChanged();
    }
}

void QEXTQmlQuickBackgroundGadget::setScale(const qreal &scale)
{
    Q_D(QEXTQmlQuickBackgroundGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTQmlQuickBackgroundGadget::setRadius(const qreal &radius)
{
    Q_D(QEXTQmlQuickBackgroundGadget);
    if (radius != d->m_radius) {
        d->m_radius = radius;
        emit this->radiusChanged();
    }
}

void QEXTQmlQuickBackgroundGadget::setColor(const QColor &color)
{
    Q_D(QEXTQmlQuickBackgroundGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTQmlQuickBackgroundGadget::setVisible(const bool &visible)
{
    Q_D(QEXTQmlQuickBackgroundGadget);
    if (visible != d->m_visible) {
        d->m_visible = visible;
        emit this->visibleChanged();
    }
}
