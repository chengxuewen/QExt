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

#include <qextQmlBorder.h>

class QExtQmlBorderPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlBorderPrivate)
    QEXT_DECLARE_PUBLIC(QExtQmlBorder)
public:
    explicit QExtQmlBorderPrivate(QExtQmlBorder *q);
    ~QExtQmlBorderPrivate();

    bool updateValid();

    QExtQmlBorder * const q_ptr;

    QColor mColor;
    qreal mWidth;
    qreal mLeftWidth;
    qreal mRightWidth;
    qreal mTopWidth;
    qreal mBottomWidth;
    bool mValid;
};

QExtQmlBorderPrivate::QExtQmlBorderPrivate(QExtQmlBorder *q)
    : q_ptr(q)
{
    mColor = "#5D5D5D";
    mWidth = 0;
    mLeftWidth = 1;
    mRightWidth = 1;
    mTopWidth = 1;
    mBottomWidth = 1;
    mValid = false;
}

QExtQmlBorderPrivate::~QExtQmlBorderPrivate()
{
}

bool QExtQmlBorderPrivate::updateValid()
{
    Q_Q(QExtQmlBorder);
    const bool valid = mWidth > 0 || mBottomWidth > 0 || mTopWidth > 0 || mLeftWidth > 0 || mRightWidth > 0;
    if (valid != mValid)
    {
        mValid = valid;
        emit q->validChanged();
    }
    return valid;
}



QExtQmlBorder::QExtQmlBorder(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlBorderPrivate(this))
{
}

QExtQmlBorder::~QExtQmlBorder()
{
}

QColor QExtQmlBorder::color() const
{
    Q_D(const QExtQmlBorder);
    return d->mColor;
}

qreal QExtQmlBorder::width() const
{
    Q_D(const QExtQmlBorder);
    return d->mWidth;
}

qreal QExtQmlBorder::leftWidth() const
{
    Q_D(const QExtQmlBorder);
    return d->mLeftWidth;
}

qreal QExtQmlBorder::rightWidth() const
{
    Q_D(const QExtQmlBorder);
    return d->mRightWidth;
}

qreal QExtQmlBorder::topWidth() const
{
    Q_D(const QExtQmlBorder);
    return d->mTopWidth;
}

qreal QExtQmlBorder::bottomWidth() const
{
    Q_D(const QExtQmlBorder);
    return d->mBottomWidth;
}

bool QExtQmlBorder::isValid() const
{
    Q_D(const QExtQmlBorder);
    return d->mValid;
}

void QExtQmlBorder::setLeftWidth(qreal leftWidth)
{
    Q_D(QExtQmlBorder);
    if (leftWidth != d->mLeftWidth)
    {
        d->mLeftWidth = leftWidth;
        emit this->leftWidthChanged();
        d->updateValid();
    }
}

void QExtQmlBorder::setRightWidth(qreal rightWidth)
{
    Q_D(QExtQmlBorder);
    if (rightWidth != d->mRightWidth)
    {
        d->mRightWidth = rightWidth;
        emit this->rightWidthChanged();
        d->updateValid();
    }
}

void QExtQmlBorder::setTopWidth(qreal topWidth)
{
    Q_D(QExtQmlBorder);
    if (topWidth != d->mTopWidth)
    {
        d->mTopWidth = topWidth;
        emit this->topWidthChanged();
        d->updateValid();
    }
}

void QExtQmlBorder::setBottomWidth(qreal bottomWidth)
{
    Q_D(QExtQmlBorder);
    if (bottomWidth != d->mBottomWidth)
    {
        d->mBottomWidth = bottomWidth;
        emit this->bottomWidthChanged();
        d->updateValid();
    }
}

void QExtQmlBorder::setColor(QColor color)
{
    Q_D(QExtQmlBorder);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
        d->updateValid();
    }
}

void QExtQmlBorder::setWidth(qreal width)
{
    Q_D(QExtQmlBorder);
    if (width != d->mWidth)
    {
        d->mWidth = width;
        emit this->widthChanged();
        d->updateValid();
    }
}
