#include <private/qextQuickItemGadget_p.h>

QExtQuickItemGadgetPrivate::QExtQuickItemGadgetPrivate(QExtQuickItemGadget *q)
    : q_ptr(q)
{

}

QExtQuickItemGadgetPrivate::~QExtQuickItemGadgetPrivate()
{

}



QExtQuickItemGadget::QExtQuickItemGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickItemGadgetPrivate(this))
{

}

QExtQuickItemGadget::~QExtQuickItemGadget()
{

}

qreal QExtQuickItemGadget::width() const
{
    Q_D(const QExtQuickItemGadget);
    return d->m_width;
}

qreal QExtQuickItemGadget::height() const
{
    Q_D(const QExtQuickItemGadget);
    return d->m_height;
}

void QExtQuickItemGadget::setWidth(const qreal &width)
{
    Q_D(QExtQuickItemGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged(width);
    }
}

void QExtQuickItemGadget::setHeight(const qreal &height)
{
    Q_D(QExtQuickItemGadget);
    if (height != d->m_height) {
        d->m_height = height;
        emit this->heightChanged(height);
    }
}
