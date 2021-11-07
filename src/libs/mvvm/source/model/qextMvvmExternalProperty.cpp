#include <qextMvvmExternalProperty.h>
#include <qextMvvmExternalProperty_p.h>

QEXTMvvmExternalPropertyPrivate::QEXTMvvmExternalPropertyPrivate(QEXTMvvmExternalProperty *q)
    : q_ptr(q)
{

}

QEXTMvvmExternalPropertyPrivate::~QEXTMvvmExternalPropertyPrivate()
{

}



QEXTMvvmExternalProperty::QEXTMvvmExternalProperty()
    : d_ptr(new QEXTMvvmExternalPropertyPrivate(this))
{

}

QEXTMvvmExternalProperty::QEXTMvvmExternalProperty(const QEXTMvvmExternalProperty &other)
    : d_ptr(new QEXTMvvmExternalPropertyPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmExternalProperty);
    d->m_text = other.d_func()->m_text;
    d->m_color = other.d_func()->m_color;
    d->m_identifier = other.d_func()->m_identifier;
}

QEXTMvvmExternalProperty::QEXTMvvmExternalProperty(const QString &text, const QColor &color, const QString &id)
    : d_ptr(new QEXTMvvmExternalPropertyPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmExternalProperty);
    d->m_text = text;
    d->m_color = color;
    d->m_identifier = id;
}

QEXTMvvmExternalProperty::~QEXTMvvmExternalProperty()
{

}

QEXTMvvmExternalProperty QEXTMvvmExternalProperty::undefined()
{
    return QEXTMvvmExternalProperty("Undefined", QColor(Qt::red));
}

QString QEXTMvvmExternalProperty::text() const
{
    QEXT_DECL_DC(QEXTMvvmExternalProperty);
    return d->m_text;
}

QColor QEXTMvvmExternalProperty::color() const
{
    QEXT_DECL_DC(QEXTMvvmExternalProperty);
    return d->m_color;
}

QString QEXTMvvmExternalProperty::identifier() const
{
    QEXT_DECL_DC(QEXTMvvmExternalProperty);
    return d->m_identifier;
}

bool QEXTMvvmExternalProperty::isValid() const
{
    QEXT_DECL_DC(QEXTMvvmExternalProperty);
    return !(d->m_identifier.isEmpty() && d->m_text.isEmpty() && !d->m_color.isValid());
}

QEXTMvvmExternalProperty &QEXTMvvmExternalProperty::operator=(const QEXTMvvmExternalProperty &other)
{
    QEXT_DECL_D(QEXTMvvmExternalProperty);
    if (this != &other)
    {
        d->m_text = other.d_func()->m_text;
        d->m_color = other.d_func()->m_color;
        d->m_identifier = other.d_func()->m_identifier;
    }
    return *this;
}

bool QEXTMvvmExternalProperty::operator==(const QEXTMvvmExternalProperty &other) const
{
    QEXT_DECL_DC(QEXTMvvmExternalProperty);
    if (d->m_identifier == other.d_func()->m_identifier)
    {
        if (d->m_text == other.d_func()->m_text)
        {
            if (d->m_color == other.d_func()->m_color)
            {
                return true;
            }
        }
    }
    return false;
}

bool QEXTMvvmExternalProperty::operator!=(const QEXTMvvmExternalProperty &other) const
{
    return !(*this == other);
}

bool QEXTMvvmExternalProperty::operator<(const QEXTMvvmExternalProperty &other) const
{
    QEXT_DECL_DC(QEXTMvvmExternalProperty);
    return d->m_identifier < other.d_func()->m_identifier
            && d->m_text < other.d_func()->m_text
            && d->m_color.name() < other.d_func()->m_color.name();
}

