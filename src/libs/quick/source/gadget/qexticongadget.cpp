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

#include <qexticongadget.h>
#include <qexticongadget_p.h>



QEXTIconGadgetPrivate::QEXTIconGadgetPrivate(QEXTIconGadget *qq)
    : QEXTObjectPrivate(qq)
{
    m_width = 18;
    m_height = 18;
    m_type = 0;
    m_position = 0;
}

QEXTIconGadgetPrivate::~QEXTIconGadgetPrivate()
{

}



QEXTIconGadget::QEXTIconGadget(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTIconGadgetPrivate(this)))
{

}

QEXTIconGadget::~QEXTIconGadget()
{

}

qreal QEXTIconGadget::width() const
{
    QEXT_DECL_DC(QEXTIconGadget);
    return d->m_width;
}

qreal QEXTIconGadget::height() const
{
    QEXT_DECL_DC(QEXTIconGadget);
    return d->m_height;
}

QColor QEXTIconGadget::color() const
{
    QEXT_DECL_DC(QEXTIconGadget);
    return d->m_color;
}

qreal QEXTIconGadget::scale() const
{
    QEXT_DECL_DC(QEXTIconGadget);
    return d->m_scale;
}

QString QEXTIconGadget::source() const
{
    QEXT_DECL_DC(QEXTIconGadget);
    return d->m_source;
}

int QEXTIconGadget::type() const
{
    QEXT_DECL_DC(QEXTIconGadget);
    return d->m_type;
}

int QEXTIconGadget::position() const
{
    QEXT_DECL_DC(QEXTIconGadget);
    return d->m_position;
}

void QEXTIconGadget::setWidth(const qreal &width)
{
    QEXT_DECL_D(QEXTIconGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged();
    }
}

void QEXTIconGadget::setPosition(const int &position)
{
    QEXT_DECL_D(QEXTIconGadget);
    if (position != d->m_position) {
        d->m_position = position;
        emit this->positionChanged(position);
    }
}

void QEXTIconGadget::setHeight(const qreal &height)
{
    QEXT_DECL_D(QEXTIconGadget);
    if (height != d->m_height) {
        d->m_height = height;
        emit this->heightChanged();
    }
}

void QEXTIconGadget::setColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIconGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTIconGadget::setScale(const qreal &scale)
{
    QEXT_DECL_D(QEXTIconGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTIconGadget::setSource(const QString &source)
{
    QEXT_DECL_D(QEXTIconGadget);
    if (source != d->m_source) {
        d->m_source = source;
        emit this->sourceChanged();
    }
}

void QEXTIconGadget::setType(const int &type)
{
    QEXT_DECL_D(QEXTIconGadget);
    if (type != d->m_type) {
        d->m_type = type;
        emit this->typeChanged(type);
    }
}
