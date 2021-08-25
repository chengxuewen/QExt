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

#include <qextscrollbargadget.h>
#include <qextscrollbargadget_p.h>



QEXTScrollbarGadgetPrivate::QEXTScrollbarGadgetPrivate(QEXTScrollbarGadget *qq)
    : QEXTObjectPrivate(qq)
{
    m_horizontal = true;
    m_vertical = true;
    m_autoHide = true;
}

QEXTScrollbarGadgetPrivate::~QEXTScrollbarGadgetPrivate()
{

}



QEXTScrollbarGadget::QEXTScrollbarGadget(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTScrollbarGadgetPrivate(this)))
{

}

QEXTScrollbarGadget::~QEXTScrollbarGadget()
{

}

bool QEXTScrollbarGadget::isHorizontal() const
{
    QEXT_DECL_DC(QEXTScrollbarGadget);
    return d->m_horizontal;
}

bool QEXTScrollbarGadget::isVertical() const
{
    QEXT_DECL_DC(QEXTScrollbarGadget);
    return d->m_vertical;
}

bool QEXTScrollbarGadget::isAutoHide() const
{
    QEXT_DECL_DC(QEXTScrollbarGadget);
    return d->m_autoHide;
}

void QEXTScrollbarGadget::setHorizontal(const bool &horizontal)
{
    QEXT_DECL_D(QEXTScrollbarGadget);
    if (horizontal != d->m_horizontal) {
        d->m_horizontal = horizontal;
        emit this->horizontalChanged();
    }
}

void QEXTScrollbarGadget::setVertical(const bool &vertical)
{
    QEXT_DECL_D(QEXTScrollbarGadget);
    if (vertical != d->m_vertical) {
        d->m_vertical = vertical;
        emit this->verticalChanged();
    }
}

void QEXTScrollbarGadget::setAutoHide(const bool &autoHide)
{
    QEXT_DECL_D(QEXTScrollbarGadget);
    if (autoHide != d->m_autoHide) {
        d->m_autoHide = autoHide;
        emit this->autoHideChanged();
    }
}
