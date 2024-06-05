/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

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
