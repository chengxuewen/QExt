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

#include <qextbordergadget.h>
#include <qextbordergadget_p.h>



QEXTBorderGadgetPrivate::QEXTBorderGadgetPrivate(QEXTBorderGadget *qq)
    : QEXTObjectPrivate(qq)
{
    m_color = "#5D5D5D";
    m_width = 0;
    m_leftWidth = 1;
    m_rightWidth = 1;
    m_topWidth = 1;
    m_bottomWidth = 1;
    m_valid = false;
}

QEXTBorderGadgetPrivate::~QEXTBorderGadgetPrivate()
{

}

bool QEXTBorderGadgetPrivate::hasValid()
{
    QEXT_Q(QEXTBorderGadget);
    bool valid = m_width > 0 || m_bottomWidth > 0 || m_topWidth > 0 || m_leftWidth > 0 || m_rightWidth > 0;
    if (valid != m_valid) {
        m_valid = valid;
        emit q->validChanged();
    }
    return valid;
}



QEXTBorderGadget::QEXTBorderGadget(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTBorderGadgetPrivate(this)))
{

}

QEXTBorderGadget::~QEXTBorderGadget()
{

}

QColor QEXTBorderGadget::color() const
{
    QEXT_DC(QEXTBorderGadget);
    return d->m_color;
}

qreal QEXTBorderGadget::width() const
{
    QEXT_DC(QEXTBorderGadget);
    return d->m_width;
}

qreal QEXTBorderGadget::leftWidth() const
{
    QEXT_DC(QEXTBorderGadget);
    return d->m_leftWidth;
}

qreal QEXTBorderGadget::rightWidth() const
{
    QEXT_DC(QEXTBorderGadget);
    return d->m_rightWidth;
}

qreal QEXTBorderGadget::topWidth() const
{
    QEXT_DC(QEXTBorderGadget);
    return d->m_topWidth;
}

qreal QEXTBorderGadget::bottomWidth() const
{
    QEXT_DC(QEXTBorderGadget);
    return d->m_bottomWidth;
}

bool QEXTBorderGadget::isValid() const
{
    QEXT_DC(QEXTBorderGadget);
    return d->m_valid;
}

void QEXTBorderGadget::setLeftWidth(qreal leftWidth)
{
    QEXT_D(QEXTBorderGadget);
    if (leftWidth != d->m_leftWidth) {
        d->m_leftWidth = leftWidth;
        emit this->leftWidthChanged();
        d->hasValid();
    }
}

void QEXTBorderGadget::setRightWidth(qreal rightWidth)
{
    QEXT_D(QEXTBorderGadget);
    if (rightWidth != d->m_rightWidth) {
        d->m_rightWidth = rightWidth;
        emit this->rightWidthChanged();
        d->hasValid();
    }
}

void QEXTBorderGadget::setTopWidth(qreal topWidth)
{
    QEXT_D(QEXTBorderGadget);
    if (topWidth != d->m_topWidth) {
        d->m_topWidth = topWidth;
        emit this->topWidthChanged();
        d->hasValid();
    }
}

void QEXTBorderGadget::setBottomWidth(qreal bottomWidth)
{
    QEXT_D(QEXTBorderGadget);
    if (bottomWidth != d->m_bottomWidth) {
        d->m_bottomWidth = bottomWidth;
        emit this->bottomWidthChanged();
        d->hasValid();
    }
}

void QEXTBorderGadget::setColor(QColor color)
{
    QEXT_D(QEXTBorderGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
        d->hasValid();
    }
}

void QEXTBorderGadget::setWidth(qreal width)
{
    QEXT_D(QEXTBorderGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged();
        d->hasValid();
    }
}
