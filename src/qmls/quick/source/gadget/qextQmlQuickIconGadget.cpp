#include <qextQmlQuickIconGadget.h>
#include <qextQmlQuickIconGadget_p.h>

QEXTQmlQuickIconGadgetPrivate::QEXTQmlQuickIconGadgetPrivate(QEXTQmlQuickIconGadget *q)
    : q_ptr(q)
{
    m_width = 18;
    m_height = 18;
    m_type = 0;
    m_position = 0;
}

QEXTQmlQuickIconGadgetPrivate::~QEXTQmlQuickIconGadgetPrivate()
{

}



QEXTQmlQuickIconGadget::QEXTQmlQuickIconGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQmlQuickIconGadgetPrivate(this))
{

}

QEXTQmlQuickIconGadget::~QEXTQmlQuickIconGadget()
{

}

qreal QEXTQmlQuickIconGadget::width() const
{
    Q_D(const QEXTQmlQuickIconGadget);
    return d->m_width;
}

qreal QEXTQmlQuickIconGadget::height() const
{
    Q_D(const QEXTQmlQuickIconGadget);
    return d->m_height;
}

QColor QEXTQmlQuickIconGadget::color() const
{
    Q_D(const QEXTQmlQuickIconGadget);
    return d->m_color;
}

qreal QEXTQmlQuickIconGadget::scale() const
{
    Q_D(const QEXTQmlQuickIconGadget);
    return d->m_scale;
}

QString QEXTQmlQuickIconGadget::source() const
{
    Q_D(const QEXTQmlQuickIconGadget);
    return d->m_source;
}

int QEXTQmlQuickIconGadget::type() const
{
    Q_D(const QEXTQmlQuickIconGadget);
    return d->m_type;
}

int QEXTQmlQuickIconGadget::position() const
{
    Q_D(const QEXTQmlQuickIconGadget);
    return d->m_position;
}

void QEXTQmlQuickIconGadget::setWidth(const qreal &width)
{
    Q_D(QEXTQmlQuickIconGadget);
    if (width != d->m_width)
    {
        d->m_width = width;
        emit this->widthChanged();
    }
}

void QEXTQmlQuickIconGadget::setPosition(const int &position)
{
    Q_D(QEXTQmlQuickIconGadget);
    if (position != d->m_position)
    {
        d->m_position = position;
        emit this->positionChanged(position);
    }
}

void QEXTQmlQuickIconGadget::setHeight(const qreal &height)
{
    Q_D(QEXTQmlQuickIconGadget);
    if (height != d->m_height)
    {
        d->m_height = height;
        emit this->heightChanged();
    }
}

void QEXTQmlQuickIconGadget::setColor(const QColor &color)
{
    Q_D(QEXTQmlQuickIconGadget);
    if (color != d->m_color)
    {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTQmlQuickIconGadget::setScale(const qreal &scale)
{
    Q_D(QEXTQmlQuickIconGadget);
    if (!qFuzzyCompare(d->m_scale, scale))
    {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTQmlQuickIconGadget::setSource(const QString &source)
{
    Q_D(QEXTQmlQuickIconGadget);
    if (source != d->m_source)
    {
        d->m_source = source;
        emit this->sourceChanged();
    }
}

void QEXTQmlQuickIconGadget::setType(const int &type)
{
    Q_D(QEXTQmlQuickIconGadget);
    if (type != d->m_type)
    {
        d->m_type = type;
        emit this->typeChanged(type);
    }
}
