#include <qextGuiPen.h>
#include <qextGuiPen_p.h>


QEXTGuiPenPrivate::QEXTGuiPenPrivate(QEXTGuiPen *q)
    : q_ptr(q)
    , m_width(1)
    , m_color()
    , m_valid(false)
{

}

QEXTGuiPenPrivate::~QEXTGuiPenPrivate()
{

}

void QEXTGuiPenPrivate::updateValid()
{
    m_valid = (m_color.alpha() && m_width >= 1) ? true : false;
}



QEXTGuiPen::QEXTGuiPen(QObject *parent)
    : QObject(parent), d_ptr(new QEXTGuiPenPrivate(this))
{

}

QEXTGuiPen::~QEXTGuiPen()
{

}

int QEXTGuiPen::width() const
{
    Q_D(const QEXTGuiPen);
    return d_ptr->m_width;
}

void QEXTGuiPen::setWidth(int width)
{
    Q_D(QEXTGuiPen);
    if (width != d_ptr->m_width)
    {
        d_ptr->m_width = width;
        d_ptr->updateValid();
        emit this->penChanged();
    }
}

QColor QEXTGuiPen::color() const
{
    Q_D(const QEXTGuiPen);
    return d_ptr->m_color;
}

void QEXTGuiPen::setColor(const QColor &color)
{
    Q_D(QEXTGuiPen);
    if (color != d_ptr->m_color)
    {
        d_ptr->m_color = color;
        d_ptr->updateValid();
        emit this->penChanged();
    }
}

bool QEXTGuiPen::isValid() const
{
    Q_D(const QEXTGuiPen);
    return d_ptr->m_valid;
}
