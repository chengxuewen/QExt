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

#include <qextQmlBorderInfo.h>

class QExtQmlBorderInfoPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlBorderInfoPrivate)
    QEXT_DECLARE_PUBLIC(QExtQmlBorderInfo)
public:
    explicit QExtQmlBorderInfoPrivate(QExtQmlBorderInfo *q);
    ~QExtQmlBorderInfoPrivate();

    bool updateValid();

    QExtQmlBorderInfo * const q_ptr;

    QColor mColor;
    qreal mWidth;
    qreal mLeftWidth;
    qreal mRightWidth;
    qreal mTopWidth;
    qreal mBottomWidth;
    bool mValid;
};

QExtQmlBorderInfoPrivate::QExtQmlBorderInfoPrivate(QExtQmlBorderInfo *q)
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

QExtQmlBorderInfoPrivate::~QExtQmlBorderInfoPrivate()
{
}

bool QExtQmlBorderInfoPrivate::updateValid()
{
    Q_Q(QExtQmlBorderInfo);
    const bool valid = mWidth > 0 || mBottomWidth > 0 || mTopWidth > 0 || mLeftWidth > 0 || mRightWidth > 0;
    if (valid != mValid)
    {
        mValid = valid;
        emit q->validChanged();
    }
    return valid;
}



QExtQmlBorderInfo::QExtQmlBorderInfo(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlBorderInfoPrivate(this))
{
}

QExtQmlBorderInfo::~QExtQmlBorderInfo()
{
}

QColor QExtQmlBorderInfo::color() const
{
    Q_D(const QExtQmlBorderInfo);
    return d->mColor;
}

qreal QExtQmlBorderInfo::width() const
{
    Q_D(const QExtQmlBorderInfo);
    return d->mWidth;
}

qreal QExtQmlBorderInfo::leftWidth() const
{
    Q_D(const QExtQmlBorderInfo);
    return d->mLeftWidth;
}

qreal QExtQmlBorderInfo::rightWidth() const
{
    Q_D(const QExtQmlBorderInfo);
    return d->mRightWidth;
}

qreal QExtQmlBorderInfo::topWidth() const
{
    Q_D(const QExtQmlBorderInfo);
    return d->mTopWidth;
}

qreal QExtQmlBorderInfo::bottomWidth() const
{
    Q_D(const QExtQmlBorderInfo);
    return d->mBottomWidth;
}

bool QExtQmlBorderInfo::isValid() const
{
    Q_D(const QExtQmlBorderInfo);
    return d->mValid;
}

void QExtQmlBorderInfo::setLeftWidth(qreal leftWidth)
{
    Q_D(QExtQmlBorderInfo);
    if (leftWidth != d->mLeftWidth)
    {
        d->mLeftWidth = leftWidth;
        emit this->leftWidthChanged();
        d->updateValid();
    }
}

void QExtQmlBorderInfo::setRightWidth(qreal rightWidth)
{
    Q_D(QExtQmlBorderInfo);
    if (rightWidth != d->mRightWidth)
    {
        d->mRightWidth = rightWidth;
        emit this->rightWidthChanged();
        d->updateValid();
    }
}

void QExtQmlBorderInfo::setTopWidth(qreal topWidth)
{
    Q_D(QExtQmlBorderInfo);
    if (topWidth != d->mTopWidth)
    {
        d->mTopWidth = topWidth;
        emit this->topWidthChanged();
        d->updateValid();
    }
}

void QExtQmlBorderInfo::setBottomWidth(qreal bottomWidth)
{
    Q_D(QExtQmlBorderInfo);
    if (bottomWidth != d->mBottomWidth)
    {
        d->mBottomWidth = bottomWidth;
        emit this->bottomWidthChanged();
        d->updateValid();
    }
}

void QExtQmlBorderInfo::setColor(QColor color)
{
    Q_D(QExtQmlBorderInfo);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
        d->updateValid();
    }
}

void QExtQmlBorderInfo::setWidth(qreal width)
{
    Q_D(QExtQmlBorderInfo);
    if (width != d->mWidth)
    {
        d->mWidth = width;
        emit this->widthChanged();
        d->updateValid();
    }
}
