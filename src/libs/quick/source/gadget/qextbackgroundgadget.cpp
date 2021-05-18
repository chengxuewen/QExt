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

#include <qextbackgroundgadget.h>
#include <qextbackgroundgadget_p.h>

#include <QDebug>


QEXTBackgroundGadgetPrivate::QEXTBackgroundGadgetPrivate(QEXTBackgroundGadget *qq)
    : QEXTObjectPrivate(qq)
{
    m_color = QColor("#FFFFF");
    m_radius = 0;
    m_width = 0;
    m_height = 0;
    m_opacity = 1;
    m_scale = 1;
    m_visible = true;
}

QEXTBackgroundGadgetPrivate::~QEXTBackgroundGadgetPrivate()
{

}



QEXTBackgroundGadget::QEXTBackgroundGadget(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTBackgroundGadgetPrivate(this)))
{

}

QEXTBackgroundGadget::~QEXTBackgroundGadget()
{

}

qreal QEXTBackgroundGadget::scale() const
{
    QEXT_DC(QEXTBackgroundGadget);
    return d->m_scale;
}

qreal QEXTBackgroundGadget::opacity() const
{
    QEXT_DC(QEXTBackgroundGadget);
    return d->m_opacity;
}

qreal QEXTBackgroundGadget::radius() const
{
    QEXT_DC(QEXTBackgroundGadget);
    return d->m_radius;
}

QColor QEXTBackgroundGadget::color() const
{
    QEXT_DC(QEXTBackgroundGadget);
    return d->m_color;
}

bool QEXTBackgroundGadget::isVisible() const
{
    QEXT_DC(QEXTBackgroundGadget);
    return d->m_visible;
}

qreal QEXTBackgroundGadget::width() const
{
    QEXT_DC(QEXTBackgroundGadget);
    return d->m_width;
}

qreal QEXTBackgroundGadget::height() const
{
    QEXT_DC(QEXTBackgroundGadget);
    return d->m_height;
}

void QEXTBackgroundGadget::setWidth(const qreal &width)
{
    QEXT_D(QEXTBackgroundGadget);
    if (width != d->m_width) {
        d->m_width = width;
        emit this->widthChanged();
    }
}

void QEXTBackgroundGadget::setHeight(const qreal &height)
{
    QEXT_D(QEXTBackgroundGadget);
    if (height != d->m_height) {
        d->m_height = height;
        emit this->heightChanged();
    }
}

void QEXTBackgroundGadget::setOpacity(const qreal &opacity)
{
    QEXT_D(QEXTBackgroundGadget);
    if (!qFuzzyCompare(d->m_opacity, opacity)) {
        d->m_opacity = opacity;
        emit this->opacityChanged();
    }
}

void QEXTBackgroundGadget::setScale(const qreal &scale)
{
    QEXT_D(QEXTBackgroundGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTBackgroundGadget::setRadius(const qreal &radius)
{
    QEXT_D(QEXTBackgroundGadget);
    if (radius != d->m_radius) {
        d->m_radius = radius;
        emit this->radiusChanged();
    }
}

void QEXTBackgroundGadget::setColor(const QColor &color)
{
    QEXT_D(QEXTBackgroundGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTBackgroundGadget::setVisible(const bool &visible)
{
    QEXT_D(QEXTBackgroundGadget);
    if (visible != d->m_visible) {
        d->m_visible = visible;
        emit this->visibleChanged();
    }
}
