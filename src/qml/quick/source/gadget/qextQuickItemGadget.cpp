/****************************************************************************
**
** Library: QEXTQuick
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

#include <qextQuickItemGadget.h>
#include <qextQuickItemGadget_p.h>

QEXTQuickItemGadgetPrivate::QEXTQuickItemGadgetPrivate(QEXTQuickItemGadget *q)
    : q_ptr(q)
{

}

QEXTQuickItemGadgetPrivate::~QEXTQuickItemGadgetPrivate()
{

}



QEXTQuickItemGadget::QEXTQuickItemGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQuickItemGadgetPrivate(this))
{

}

QEXTQuickItemGadget::~QEXTQuickItemGadget()
{

}

qreal QEXTQuickItemGadget::width() const
{
    Q_D(const QEXTQuickItemGadget);
    return d->m_width;
}

qreal QEXTQuickItemGadget::height() const
{
    Q_D(const QEXTQuickItemGadget);
    return d->m_height;
}

void QEXTQuickItemGadget::setWidth(const qreal &width)
{
    Q_D(QEXTQuickItemGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged(width);
    }
}

void QEXTQuickItemGadget::setHeight(const qreal &height)
{
    Q_D(QEXTQuickItemGadget);
    if (height != d->m_height) {
        d->m_height = height;
        emit this->heightChanged(height);
    }
}
