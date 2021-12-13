#include <qextQuickBackgroundGadget.h>
#include <qextQuickBackgroundGadget_p.h>

#include <QDebug>

QEXTQuickBackgroundGadgetPrivate::QEXTQuickBackgroundGadgetPrivate(QEXTQuickBackgroundGadget *q)
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

QEXTQuickBackgroundGadgetPrivate::~QEXTQuickBackgroundGadgetPrivate()
{

}



QEXTQuickBackgroundGadget::QEXTQuickBackgroundGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQuickBackgroundGadgetPrivate(this))
{

}

QEXTQuickBackgroundGadget::~QEXTQuickBackgroundGadget()
{

}

qreal QEXTQuickBackgroundGadget::scale() const
{
    Q_D(const QEXTQuickBackgroundGadget);
    return d->m_scale;
}

qreal QEXTQuickBackgroundGadget::opacity() const
{
    Q_D(const QEXTQuickBackgroundGadget);
    return d->m_opacity;
}

qreal QEXTQuickBackgroundGadget::radius() const
{
    Q_D(const QEXTQuickBackgroundGadget);
    return d->m_radius;
}

QColor QEXTQuickBackgroundGadget::color() const
{
    Q_D(const QEXTQuickBackgroundGadget);
    return d->m_color;
}

bool QEXTQuickBackgroundGadget::isVisible() const
{
    Q_D(const QEXTQuickBackgroundGadget);
    return d->m_visible;
}

qreal QEXTQuickBackgroundGadget::width() const
{
    Q_D(const QEXTQuickBackgroundGadget);
    return d->m_width;
}

qreal QEXTQuickBackgroundGadget::height() const
{
    Q_D(const QEXTQuickBackgroundGadget);
    return d->m_height;
}

void QEXTQuickBackgroundGadget::setWidth(const qreal &width)
{
    Q_D(QEXTQuickBackgroundGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged();
    }
}

void QEXTQuickBackgroundGadget::setHeight(const qreal &height)
{
    Q_D(QEXTQuickBackgroundGadget);
    if (height != d->m_height) {
        d->m_height = height;
        emit this->heightChanged();
    }
}

void QEXTQuickBackgroundGadget::setOpacity(const qreal &opacity)
{
    Q_D(QEXTQuickBackgroundGadget);
    if (!qFuzzyCompare(d->m_opacity, opacity)) {
        d->m_opacity = opacity;
        emit this->opacityChanged();
    }
}

void QEXTQuickBackgroundGadget::setScale(const qreal &scale)
{
    Q_D(QEXTQuickBackgroundGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTQuickBackgroundGadget::setRadius(const qreal &radius)
{
    Q_D(QEXTQuickBackgroundGadget);
    if (radius != d->m_radius) {
        d->m_radius = radius;
        emit this->radiusChanged();
    }
}

void QEXTQuickBackgroundGadget::setColor(const QColor &color)
{
    Q_D(QEXTQuickBackgroundGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTQuickBackgroundGadget::setVisible(const bool &visible)
{
    Q_D(QEXTQuickBackgroundGadget);
    if (visible != d->m_visible) {
        d->m_visible = visible;
        emit this->visibleChanged();
    }
}
