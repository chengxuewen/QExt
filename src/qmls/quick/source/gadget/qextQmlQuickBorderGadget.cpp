#include <qextQmlQuickBorderGadget.h>
#include <qextQmlQuickBorderGadget_p.h>

QEXTQmlQuickBorderGadgetPrivate::QEXTQmlQuickBorderGadgetPrivate(QEXTQmlQuickBorderGadget *q)
    : q_ptr(q)
{
    m_color = "#5D5D5D";
    m_width = 0;
    m_leftWidth = 1;
    m_rightWidth = 1;
    m_topWidth = 1;
    m_bottomWidth = 1;
    m_valid = false;
}

QEXTQmlQuickBorderGadgetPrivate::~QEXTQmlQuickBorderGadgetPrivate()
{

}

bool QEXTQmlQuickBorderGadgetPrivate::hasValid()
{
    Q_Q(QEXTQmlQuickBorderGadget);
    bool valid = m_width > 0 || m_bottomWidth > 0 || m_topWidth > 0 || m_leftWidth > 0 || m_rightWidth > 0;
    if (valid != m_valid) {
        m_valid = valid;
        emit q->validChanged();
    }
    return valid;
}



QEXTQmlQuickBorderGadget::QEXTQmlQuickBorderGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQmlQuickBorderGadgetPrivate(this))
{

}

QEXTQmlQuickBorderGadget::~QEXTQmlQuickBorderGadget()
{

}

QColor QEXTQmlQuickBorderGadget::color() const
{
    Q_D(const QEXTQmlQuickBorderGadget);
    return d->m_color;
}

qreal QEXTQmlQuickBorderGadget::width() const
{
    Q_D(const QEXTQmlQuickBorderGadget);
    return d->m_width;
}

qreal QEXTQmlQuickBorderGadget::leftWidth() const
{
    Q_D(const QEXTQmlQuickBorderGadget);
    return d->m_leftWidth;
}

qreal QEXTQmlQuickBorderGadget::rightWidth() const
{
    Q_D(const QEXTQmlQuickBorderGadget);
    return d->m_rightWidth;
}

qreal QEXTQmlQuickBorderGadget::topWidth() const
{
    Q_D(const QEXTQmlQuickBorderGadget);
    return d->m_topWidth;
}

qreal QEXTQmlQuickBorderGadget::bottomWidth() const
{
    Q_D(const QEXTQmlQuickBorderGadget);
    return d->m_bottomWidth;
}

bool QEXTQmlQuickBorderGadget::isValid() const
{
    Q_D(const QEXTQmlQuickBorderGadget);
    return d->m_valid;
}

void QEXTQmlQuickBorderGadget::setLeftWidth(qreal leftWidth)
{
    Q_D(QEXTQmlQuickBorderGadget);
    if (leftWidth != d->m_leftWidth) {
        d->m_leftWidth = leftWidth;
        emit this->leftWidthChanged();
        d->hasValid();
    }
}

void QEXTQmlQuickBorderGadget::setRightWidth(qreal rightWidth)
{
    Q_D(QEXTQmlQuickBorderGadget);
    if (rightWidth != d->m_rightWidth) {
        d->m_rightWidth = rightWidth;
        emit this->rightWidthChanged();
        d->hasValid();
    }
}

void QEXTQmlQuickBorderGadget::setTopWidth(qreal topWidth)
{
    Q_D(QEXTQmlQuickBorderGadget);
    if (topWidth != d->m_topWidth) {
        d->m_topWidth = topWidth;
        emit this->topWidthChanged();
        d->hasValid();
    }
}

void QEXTQmlQuickBorderGadget::setBottomWidth(qreal bottomWidth)
{
    Q_D(QEXTQmlQuickBorderGadget);
    if (bottomWidth != d->m_bottomWidth) {
        d->m_bottomWidth = bottomWidth;
        emit this->bottomWidthChanged();
        d->hasValid();
    }
}

void QEXTQmlQuickBorderGadget::setColor(QColor color)
{
    Q_D(QEXTQmlQuickBorderGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
        d->hasValid();
    }
}

void QEXTQmlQuickBorderGadget::setWidth(qreal width)
{
    Q_D(QEXTQmlQuickBorderGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged();
        d->hasValid();
    }
}
