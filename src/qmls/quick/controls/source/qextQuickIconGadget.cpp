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

#include <qextQuickIconGadget.h>

class QExtQuickIconGadgetPrivate
{
public:
    explicit QExtQuickIconGadgetPrivate(QExtQuickIconGadget *q);
    virtual ~QExtQuickIconGadgetPrivate();

    QExtQuickIconGadget * const q_ptr;

    qreal m_width;
    qreal m_height;
    int m_type;
    int m_position;
    qreal m_scale;
    QColor m_color;
    QString m_source;

private:
    QEXT_DECL_PUBLIC(QExtQuickIconGadget)
    QEXT_DISABLE_COPY_MOVE(QExtQuickIconGadgetPrivate)
};

QExtQuickIconGadgetPrivate::QExtQuickIconGadgetPrivate(QExtQuickIconGadget *q)
    : q_ptr(q)
{
    m_width = 18;
    m_height = 18;
    m_type = 0;
    m_position = 0;
}

QExtQuickIconGadgetPrivate::~QExtQuickIconGadgetPrivate()
{

}



QExtQuickIconGadget::QExtQuickIconGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickIconGadgetPrivate(this))
{

}

QExtQuickIconGadget::~QExtQuickIconGadget()
{

}

qreal QExtQuickIconGadget::width() const
{
    Q_D(const QExtQuickIconGadget);
    return d->m_width;
}

qreal QExtQuickIconGadget::height() const
{
    Q_D(const QExtQuickIconGadget);
    return d->m_height;
}

QColor QExtQuickIconGadget::color() const
{
    Q_D(const QExtQuickIconGadget);
    return d->m_color;
}

qreal QExtQuickIconGadget::scale() const
{
    Q_D(const QExtQuickIconGadget);
    return d->m_scale;
}

QString QExtQuickIconGadget::source() const
{
    Q_D(const QExtQuickIconGadget);
    return d->m_source;
}

int QExtQuickIconGadget::type() const
{
    Q_D(const QExtQuickIconGadget);
    return d->m_type;
}

int QExtQuickIconGadget::position() const
{
    Q_D(const QExtQuickIconGadget);
    return d->m_position;
}

void QExtQuickIconGadget::setWidth(const qreal &width)
{
    Q_D(QExtQuickIconGadget);
    if (width != d->m_width)
    {
        d->m_width = width;
        emit this->widthChanged();
    }
}

void QExtQuickIconGadget::setPosition(const int &position)
{
    Q_D(QExtQuickIconGadget);
    if (position != d->m_position)
    {
        d->m_position = position;
        emit this->positionChanged(position);
    }
}

void QExtQuickIconGadget::setHeight(const qreal &height)
{
    Q_D(QExtQuickIconGadget);
    if (height != d->m_height)
    {
        d->m_height = height;
        emit this->heightChanged();
    }
}

void QExtQuickIconGadget::setColor(const QColor &color)
{
    Q_D(QExtQuickIconGadget);
    if (color != d->m_color)
    {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QExtQuickIconGadget::setScale(const qreal &scale)
{
    Q_D(QExtQuickIconGadget);
    if (!qFuzzyCompare(d->m_scale, scale))
    {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QExtQuickIconGadget::setSource(const QString &source)
{
    Q_D(QExtQuickIconGadget);
    if (source != d->m_source)
    {
        d->m_source = source;
        emit this->sourceChanged();
    }
}

void QExtQuickIconGadget::setType(const int &type)
{
    Q_D(QExtQuickIconGadget);
    if (type != d->m_type)
    {
        d->m_type = type;
        emit this->typeChanged(type);
    }
}
