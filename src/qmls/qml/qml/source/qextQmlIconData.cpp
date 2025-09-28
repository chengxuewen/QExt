/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
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

#include <qextQmlIconData.h>

class QExtQmlIconDataPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlIconDataPrivate)
    QEXT_DECLARE_PUBLIC(QExtQmlIconData)
public:
    explicit QExtQmlIconDataPrivate(QExtQmlIconData *q);
    virtual ~QExtQmlIconDataPrivate();

    QExtQmlIconData * const q_ptr;

    qreal mWidth;
    qreal mHeight;
    int mType;
    int mPosition;
    qreal mScale;
    QColor mColor;
    QString mSource;
};

QExtQmlIconDataPrivate::QExtQmlIconDataPrivate(QExtQmlIconData *q)
    : q_ptr(q)
{
    mWidth = 18;
    mHeight = 18;
    mType = 0;
    mPosition = 0;
}

QExtQmlIconDataPrivate::~QExtQmlIconDataPrivate()
{
}

QExtQmlIconData::QExtQmlIconData(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlIconDataPrivate(this))
{

}

QExtQmlIconData::~QExtQmlIconData()
{

}

qreal QExtQmlIconData::width() const
{
    Q_D(const QExtQmlIconData);
    return d->mWidth;
}

qreal QExtQmlIconData::height() const
{
    Q_D(const QExtQmlIconData);
    return d->mHeight;
}

QColor QExtQmlIconData::color() const
{
    Q_D(const QExtQmlIconData);
    return d->mColor;
}

qreal QExtQmlIconData::scale() const
{
    Q_D(const QExtQmlIconData);
    return d->mScale;
}

QString QExtQmlIconData::source() const
{
    Q_D(const QExtQmlIconData);
    return d->mSource;
}

int QExtQmlIconData::type() const
{
    Q_D(const QExtQmlIconData);
    return d->mType;
}

int QExtQmlIconData::position() const
{
    Q_D(const QExtQmlIconData);
    return d->mPosition;
}

void QExtQmlIconData::setWidth(const qreal &width)
{
    Q_D(QExtQmlIconData);
    if (width != d->mWidth)
    {
        d->mWidth = width;
        emit this->widthChanged();
    }
}

void QExtQmlIconData::setPosition(const int &position)
{
    Q_D(QExtQmlIconData);
    if (position != d->mPosition)
    {
        d->mPosition = position;
        emit this->positionChanged(position);
    }
}

void QExtQmlIconData::setHeight(const qreal &height)
{
    Q_D(QExtQmlIconData);
    if (height != d->mHeight)
    {
        d->mHeight = height;
        emit this->heightChanged();
    }
}

void QExtQmlIconData::setColor(const QColor &color)
{
    Q_D(QExtQmlIconData);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
    }
}

void QExtQmlIconData::setScale(const qreal &scale)
{
    Q_D(QExtQmlIconData);
    if (!qFuzzyCompare(d->mScale, scale))
    {
        d->mScale = scale;
        emit this->scaleChanged();
    }
}

void QExtQmlIconData::setSource(const QString &source)
{
    Q_D(QExtQmlIconData);
    if (source != d->mSource)
    {
        d->mSource = source;
        emit this->sourceChanged();
    }
}

void QExtQmlIconData::setType(const int &type)
{
    Q_D(QExtQmlIconData);
    if (type != d->mType)
    {
        d->mType = type;
        emit this->typeChanged(type);
    }
}
