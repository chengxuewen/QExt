#include <private/qextQuickBorderGadget_p.h>

QExtQuickBorderGadgetPrivate::QExtQuickBorderGadgetPrivate(QExtQuickBorderGadget *q)
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

QExtQuickBorderGadgetPrivate::~QExtQuickBorderGadgetPrivate()
{

}

bool QExtQuickBorderGadgetPrivate::hasValid()
{
    Q_Q(QExtQuickBorderGadget);
    bool valid = m_width > 0 || m_bottomWidth > 0 || m_topWidth > 0 || m_leftWidth > 0 || m_rightWidth > 0;
    if (valid != m_valid) {
        m_valid = valid;
        emit q->validChanged();
    }
    return valid;
}



QExtQuickBorderGadget::QExtQuickBorderGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickBorderGadgetPrivate(this))
{

}

QExtQuickBorderGadget::~QExtQuickBorderGadget()
{

}

QColor QExtQuickBorderGadget::color() const
{
    Q_D(const QExtQuickBorderGadget);
    return d->m_color;
}

qreal QExtQuickBorderGadget::width() const
{
    Q_D(const QExtQuickBorderGadget);
    return d->m_width;
}

qreal QExtQuickBorderGadget::leftWidth() const
{
    Q_D(const QExtQuickBorderGadget);
    return d->m_leftWidth;
}

qreal QExtQuickBorderGadget::rightWidth() const
{
    Q_D(const QExtQuickBorderGadget);
    return d->m_rightWidth;
}

qreal QExtQuickBorderGadget::topWidth() const
{
    Q_D(const QExtQuickBorderGadget);
    return d->m_topWidth;
}

qreal QExtQuickBorderGadget::bottomWidth() const
{
    Q_D(const QExtQuickBorderGadget);
    return d->m_bottomWidth;
}

bool QExtQuickBorderGadget::isValid() const
{
    Q_D(const QExtQuickBorderGadget);
    return d->m_valid;
}

void QExtQuickBorderGadget::setLeftWidth(qreal leftWidth)
{
    Q_D(QExtQuickBorderGadget);
    if (leftWidth != d->m_leftWidth) {
        d->m_leftWidth = leftWidth;
        emit this->leftWidthChanged();
        d->hasValid();
    }
}

void QExtQuickBorderGadget::setRightWidth(qreal rightWidth)
{
    Q_D(QExtQuickBorderGadget);
    if (rightWidth != d->m_rightWidth) {
        d->m_rightWidth = rightWidth;
        emit this->rightWidthChanged();
        d->hasValid();
    }
}

void QExtQuickBorderGadget::setTopWidth(qreal topWidth)
{
    Q_D(QExtQuickBorderGadget);
    if (topWidth != d->m_topWidth) {
        d->m_topWidth = topWidth;
        emit this->topWidthChanged();
        d->hasValid();
    }
}

void QExtQuickBorderGadget::setBottomWidth(qreal bottomWidth)
{
    Q_D(QExtQuickBorderGadget);
    if (bottomWidth != d->m_bottomWidth) {
        d->m_bottomWidth = bottomWidth;
        emit this->bottomWidthChanged();
        d->hasValid();
    }
}

void QExtQuickBorderGadget::setColor(QColor color)
{
    Q_D(QExtQuickBorderGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
        d->hasValid();
    }
}

void QExtQuickBorderGadget::setWidth(qreal width)
{
    Q_D(QExtQuickBorderGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged();
        d->hasValid();
    }
}
