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

#include <qextQmlPaddingInfo.h>

#include <QDebug>

class QExtQmlPaddingInfoPrivate
{
public:
    explicit QExtQmlPaddingInfoPrivate(QExtQmlPaddingInfo *q);
    virtual ~QExtQmlPaddingInfoPrivate();

    QExtQmlPaddingInfo * const q_ptr;

    double mTopPadding;
    double mLeftPadding;
    double mRightPadding;
    double mBottomPadding;

private:
    QEXT_DECLARE_PUBLIC(QExtQmlPaddingInfo)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlPaddingInfoPrivate)
};

QExtQmlPaddingInfoPrivate::QExtQmlPaddingInfoPrivate(QExtQmlPaddingInfo *q)
    : q_ptr(q)
    , mTopPadding(0)
    , mLeftPadding(0)
    , mRightPadding(0)
    , mBottomPadding(0)
{
}

QExtQmlPaddingInfoPrivate::~QExtQmlPaddingInfoPrivate()
{
}

QExtQmlPaddingInfo::QExtQmlPaddingInfo(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlPaddingInfoPrivate(this))
{
}

QExtQmlPaddingInfo::QExtQmlPaddingInfo(double padding, QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlPaddingInfoPrivate(this))
{
    this->setPadding(padding);
}

QExtQmlPaddingInfo::~QExtQmlPaddingInfo()
{

}

double QExtQmlPaddingInfo::topPadding() const
{
    Q_D(const QExtQmlPaddingInfo);
    return d->mTopPadding;
}

double QExtQmlPaddingInfo::leftPadding() const
{
    Q_D(const QExtQmlPaddingInfo);
    return d->mLeftPadding;
}

double QExtQmlPaddingInfo::rightPadding() const
{
    Q_D(const QExtQmlPaddingInfo);
    return d->mRightPadding;
}

double QExtQmlPaddingInfo::bottomPadding() const
{
    Q_D(const QExtQmlPaddingInfo);
    return d->mBottomPadding;
}

void QExtQmlPaddingInfo::setPadding(double padding)
{
    this->setTopPadding(padding);
    this->setLeftPadding(padding);
    this->setRightPadding(padding);
    this->setBottomPadding(padding);
}

void QExtQmlPaddingInfo::setTopPadding(double padding)
{
    Q_D(QExtQmlPaddingInfo);
    if (padding != d->mTopPadding)
    {
        d->mTopPadding = padding;
        emit this->topPaddingChanged(padding);
    }
}

void QExtQmlPaddingInfo::setLeftPadding(double padding)
{
    Q_D(QExtQmlPaddingInfo);
    if (padding != d->mLeftPadding)
    {
        d->mLeftPadding = padding;
        emit this->leftPaddingChanged(padding);
    }
}

void QExtQmlPaddingInfo::setRightPadding(double padding)
{
    Q_D(QExtQmlPaddingInfo);
    if (padding != d->mRightPadding)
    {
        d->mRightPadding = padding;
        emit this->rightPaddingChanged(padding);
    }
}

void QExtQmlPaddingInfo::setBottomPadding(double padding)
{
    Q_D(QExtQmlPaddingInfo);
    if (padding != d->mBottomPadding)
    {
        d->mBottomPadding = padding;
        emit this->bottomPaddingChanged(padding);
    }
}
