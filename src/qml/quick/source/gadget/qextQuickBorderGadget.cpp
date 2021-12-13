#include <qextQuickBorderGadget.h>
#include <qextQuickBorderGadget_p.h>

QEXTQuickBorderGadgetPrivate::QEXTQuickBorderGadgetPrivate(QEXTQuickBorderGadget *q)
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

QEXTQuickBorderGadgetPrivate::~QEXTQuickBorderGadgetPrivate()
{

}

bool QEXTQuickBorderGadgetPrivate::hasValid()
{
    Q_Q(QEXTQuickBorderGadget);
    bool valid = m_width > 0 || m_bottomWidth > 0 || m_topWidth > 0 || m_leftWidth > 0 || m_rightWidth > 0;
    if (valid != m_valid) {
        m_valid = valid;
        emit q->validChanged();
    }
    return valid;
}



QEXTQuickBorderGadget::QEXTQuickBorderGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQuickBorderGadgetPrivate(this))
{

}

QEXTQuickBorderGadget::~QEXTQuickBorderGadget()
{

}

QColor QEXTQuickBorderGadget::color() const
{
    Q_D(const QEXTQuickBorderGadget);
    return d->m_color;
}

qreal QEXTQuickBorderGadget::width() const
{
    Q_D(const QEXTQuickBorderGadget);
    return d->m_width;
}

qreal QEXTQuickBorderGadget::leftWidth() const
{
    Q_D(const QEXTQuickBorderGadget);
    return d->m_leftWidth;
}

qreal QEXTQuickBorderGadget::rightWidth() const
{
    Q_D(const QEXTQuickBorderGadget);
    return d->m_rightWidth;
}

qreal QEXTQuickBorderGadget::topWidth() const
{
    Q_D(const QEXTQuickBorderGadget);
    return d->m_topWidth;
}

qreal QEXTQuickBorderGadget::bottomWidth() const
{
    Q_D(const QEXTQuickBorderGadget);
    return d->m_bottomWidth;
}

bool QEXTQuickBorderGadget::isValid() const
{
    Q_D(const QEXTQuickBorderGadget);
    return d->m_valid;
}

void QEXTQuickBorderGadget::setLeftWidth(qreal leftWidth)
{
    Q_D(QEXTQuickBorderGadget);
    if (leftWidth != d->m_leftWidth) {
        d->m_leftWidth = leftWidth;
        emit this->leftWidthChanged();
        d->hasValid();
    }
}

void QEXTQuickBorderGadget::setRightWidth(qreal rightWidth)
{
    Q_D(QEXTQuickBorderGadget);
    if (rightWidth != d->m_rightWidth) {
        d->m_rightWidth = rightWidth;
        emit this->rightWidthChanged();
        d->hasValid();
    }
}

void QEXTQuickBorderGadget::setTopWidth(qreal topWidth)
{
    Q_D(QEXTQuickBorderGadget);
    if (topWidth != d->m_topWidth) {
        d->m_topWidth = topWidth;
        emit this->topWidthChanged();
        d->hasValid();
    }
}

void QEXTQuickBorderGadget::setBottomWidth(qreal bottomWidth)
{
    Q_D(QEXTQuickBorderGadget);
    if (bottomWidth != d->m_bottomWidth) {
        d->m_bottomWidth = bottomWidth;
        emit this->bottomWidthChanged();
        d->hasValid();
    }
}

void QEXTQuickBorderGadget::setColor(QColor color)
{
    Q_D(QEXTQuickBorderGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
        d->hasValid();
    }
}

void QEXTQuickBorderGadget::setWidth(qreal width)
{
    Q_D(QEXTQuickBorderGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged();
        d->hasValid();
    }
}
