#include <qextQuickIconGadget.h>
#include <qextQuickIconGadget_p.h>

QEXTQuickIconGadgetPrivate::QEXTQuickIconGadgetPrivate(QEXTQuickIconGadget *q)
    : q_ptr(q)
{
    m_width = 18;
    m_height = 18;
    m_type = 0;
    m_position = 0;
}

QEXTQuickIconGadgetPrivate::~QEXTQuickIconGadgetPrivate()
{

}



QEXTQuickIconGadget::QEXTQuickIconGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQuickIconGadgetPrivate(this))
{

}

QEXTQuickIconGadget::~QEXTQuickIconGadget()
{

}

qreal QEXTQuickIconGadget::width() const
{
    Q_D(const QEXTQuickIconGadget);
    return d->m_width;
}

qreal QEXTQuickIconGadget::height() const
{
    Q_D(const QEXTQuickIconGadget);
    return d->m_height;
}

QColor QEXTQuickIconGadget::color() const
{
    Q_D(const QEXTQuickIconGadget);
    return d->m_color;
}

qreal QEXTQuickIconGadget::scale() const
{
    Q_D(const QEXTQuickIconGadget);
    return d->m_scale;
}

QString QEXTQuickIconGadget::source() const
{
    Q_D(const QEXTQuickIconGadget);
    return d->m_source;
}

int QEXTQuickIconGadget::type() const
{
    Q_D(const QEXTQuickIconGadget);
    return d->m_type;
}

int QEXTQuickIconGadget::position() const
{
    Q_D(const QEXTQuickIconGadget);
    return d->m_position;
}

void QEXTQuickIconGadget::setWidth(const qreal &width)
{
    Q_D(QEXTQuickIconGadget);
    if (width != d->m_width)
    {
        d->m_width = width;
        emit this->widthChanged();
    }
}

void QEXTQuickIconGadget::setPosition(const int &position)
{
    Q_D(QEXTQuickIconGadget);
    if (position != d->m_position)
    {
        d->m_position = position;
        emit this->positionChanged(position);
    }
}

void QEXTQuickIconGadget::setHeight(const qreal &height)
{
    Q_D(QEXTQuickIconGadget);
    if (height != d->m_height)
    {
        d->m_height = height;
        emit this->heightChanged();
    }
}

void QEXTQuickIconGadget::setColor(const QColor &color)
{
    Q_D(QEXTQuickIconGadget);
    if (color != d->m_color)
    {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTQuickIconGadget::setScale(const qreal &scale)
{
    Q_D(QEXTQuickIconGadget);
    if (!qFuzzyCompare(d->m_scale, scale))
    {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTQuickIconGadget::setSource(const QString &source)
{
    Q_D(QEXTQuickIconGadget);
    if (source != d->m_source)
    {
        d->m_source = source;
        emit this->sourceChanged();
    }
}

void QEXTQuickIconGadget::setType(const int &type)
{
    Q_D(QEXTQuickIconGadget);
    if (type != d->m_type)
    {
        d->m_type = type;
        emit this->typeChanged(type);
    }
}
