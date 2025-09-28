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

#include <qextQmlIconInfo.h>

class QExtQmlIconInfoPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlIconInfoPrivate)
    QEXT_DECLARE_PUBLIC(QExtQmlIconInfo)
public:
    explicit QExtQmlIconInfoPrivate(QExtQmlIconInfo *q);
    virtual ~QExtQmlIconInfoPrivate();

    QExtQmlIconInfo * const q_ptr;

    qreal mWidth;
    qreal mHeight;
    int mType;
    int mPosition;
    qreal mScale;
    QColor mColor;
    QString mSource;
};

QExtQmlIconInfoPrivate::QExtQmlIconInfoPrivate(QExtQmlIconInfo *q)
    : q_ptr(q)
{
    mWidth = 18;
    mHeight = 18;
    mType = 0;
    mPosition = 0;
}

QExtQmlIconInfoPrivate::~QExtQmlIconInfoPrivate()
{
}

QExtQmlIconInfo::QExtQmlIconInfo(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlIconInfoPrivate(this))
{

}

QExtQmlIconInfo::~QExtQmlIconInfo()
{

}

qreal QExtQmlIconInfo::width() const
{
    Q_D(const QExtQmlIconInfo);
    return d->mWidth;
}

qreal QExtQmlIconInfo::height() const
{
    Q_D(const QExtQmlIconInfo);
    return d->mHeight;
}

QColor QExtQmlIconInfo::color() const
{
    Q_D(const QExtQmlIconInfo);
    return d->mColor;
}

qreal QExtQmlIconInfo::scale() const
{
    Q_D(const QExtQmlIconInfo);
    return d->mScale;
}

QString QExtQmlIconInfo::source() const
{
    Q_D(const QExtQmlIconInfo);
    return d->mSource;
}

int QExtQmlIconInfo::type() const
{
    Q_D(const QExtQmlIconInfo);
    return d->mType;
}

int QExtQmlIconInfo::position() const
{
    Q_D(const QExtQmlIconInfo);
    return d->mPosition;
}

void QExtQmlIconInfo::setWidth(const qreal &width)
{
    Q_D(QExtQmlIconInfo);
    if (width != d->mWidth)
    {
        d->mWidth = width;
        emit this->widthChanged();
    }
}

void QExtQmlIconInfo::setPosition(const int &position)
{
    Q_D(QExtQmlIconInfo);
    if (position != d->mPosition)
    {
        d->mPosition = position;
        emit this->positionChanged(position);
    }
}

void QExtQmlIconInfo::setHeight(const qreal &height)
{
    Q_D(QExtQmlIconInfo);
    if (height != d->mHeight)
    {
        d->mHeight = height;
        emit this->heightChanged();
    }
}

void QExtQmlIconInfo::setColor(const QColor &color)
{
    Q_D(QExtQmlIconInfo);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
    }
}

void QExtQmlIconInfo::setScale(const qreal &scale)
{
    Q_D(QExtQmlIconInfo);
    if (!qFuzzyCompare(d->mScale, scale))
    {
        d->mScale = scale;
        emit this->scaleChanged();
    }
}

void QExtQmlIconInfo::setSource(const QString &source)
{
    Q_D(QExtQmlIconInfo);
    if (source != d->mSource)
    {
        d->mSource = source;
        emit this->sourceChanged();
    }
}

void QExtQmlIconInfo::setType(const int &type)
{
    Q_D(QExtQmlIconInfo);
    if (type != d->mType)
    {
        d->mType = type;
        emit this->typeChanged(type);
    }
}
