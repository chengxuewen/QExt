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

#include <private/qextQuickBackgroundGadget_p.h>

#include <QDebug>

QExtQuickBackgroundGadgetPrivate::QExtQuickBackgroundGadgetPrivate(QExtQuickBackgroundGadget *q)
    : q_ptr(q)
{
    m_color = QColor("#FFFFF");
    m_radius = 0;
    m_width = 0;
    m_height = 0;
    m_opacity = 1;
    m_scale = 1;
    m_visible = true;
}

QExtQuickBackgroundGadgetPrivate::~QExtQuickBackgroundGadgetPrivate()
{

}



QExtQuickBackgroundGadget::QExtQuickBackgroundGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickBackgroundGadgetPrivate(this))
{

}

QExtQuickBackgroundGadget::~QExtQuickBackgroundGadget()
{

}

qreal QExtQuickBackgroundGadget::scale() const
{
    Q_D(const QExtQuickBackgroundGadget);
    return d->m_scale;
}

qreal QExtQuickBackgroundGadget::opacity() const
{
    Q_D(const QExtQuickBackgroundGadget);
    return d->m_opacity;
}

qreal QExtQuickBackgroundGadget::radius() const
{
    Q_D(const QExtQuickBackgroundGadget);
    return d->m_radius;
}

QColor QExtQuickBackgroundGadget::color() const
{
    Q_D(const QExtQuickBackgroundGadget);
    return d->m_color;
}

bool QExtQuickBackgroundGadget::isVisible() const
{
    Q_D(const QExtQuickBackgroundGadget);
    return d->m_visible;
}

qreal QExtQuickBackgroundGadget::width() const
{
    Q_D(const QExtQuickBackgroundGadget);
    return d->m_width;
}

qreal QExtQuickBackgroundGadget::height() const
{
    Q_D(const QExtQuickBackgroundGadget);
    return d->m_height;
}

void QExtQuickBackgroundGadget::setWidth(const qreal &width)
{
    Q_D(QExtQuickBackgroundGadget);
    if (width != d->m_width)
    {
        d->m_width = width;
        emit this->widthChanged();
    }
}

void QExtQuickBackgroundGadget::setHeight(const qreal &height)
{
    Q_D(QExtQuickBackgroundGadget);
    if (height != d->m_height)
    {
        d->m_height = height;
        emit this->heightChanged();
    }
}

void QExtQuickBackgroundGadget::setOpacity(const qreal &opacity)
{
    Q_D(QExtQuickBackgroundGadget);
    if (!qFuzzyCompare(d->m_opacity, opacity)) {
        d->m_opacity = opacity;
        emit this->opacityChanged();
    }
}

void QExtQuickBackgroundGadget::setScale(const qreal &scale)
{
    Q_D(QExtQuickBackgroundGadget);
    if (!qFuzzyCompare(d->m_scale, scale))
    {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QExtQuickBackgroundGadget::setRadius(const qreal &radius)
{
    Q_D(QExtQuickBackgroundGadget);
    if (radius != d->m_radius)
    {
        d->m_radius = radius;
        emit this->radiusChanged();
    }
}

void QExtQuickBackgroundGadget::setColor(const QColor &color)
{
    Q_D(QExtQuickBackgroundGadget);
    if (color != d->m_color)
    {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QExtQuickBackgroundGadget::setVisible(const bool &visible)
{
    Q_D(QExtQuickBackgroundGadget);
    if (visible != d->m_visible)
    {
        d->m_visible = visible;
        emit this->visibleChanged();
    }
}
