/****************************************************************************
**
** Library: QEXTQmlQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#include <qextQmlQuickItemGadget.h>
#include <qextQmlQuickItemGadget_p.h>

QEXTQmlQuickItemGadgetPrivate::QEXTQmlQuickItemGadgetPrivate(QEXTQmlQuickItemGadget *q)
    : q_ptr(q)
{

}

QEXTQmlQuickItemGadgetPrivate::~QEXTQmlQuickItemGadgetPrivate()
{

}



QEXTQmlQuickItemGadget::QEXTQmlQuickItemGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQmlQuickItemGadgetPrivate(this))
{

}

QEXTQmlQuickItemGadget::~QEXTQmlQuickItemGadget()
{

}

qreal QEXTQmlQuickItemGadget::width() const
{
    Q_D(const QEXTQmlQuickItemGadget);
    return d->m_width;
}

qreal QEXTQmlQuickItemGadget::height() const
{
    Q_D(const QEXTQmlQuickItemGadget);
    return d->m_height;
}

void QEXTQmlQuickItemGadget::setWidth(const qreal &width)
{
    Q_D(QEXTQmlQuickItemGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged(width);
    }
}

void QEXTQmlQuickItemGadget::setHeight(const qreal &height)
{
    Q_D(QEXTQmlQuickItemGadget);
    if (height != d->m_height) {
        d->m_height = height;
        emit this->heightChanged(height);
    }
}
