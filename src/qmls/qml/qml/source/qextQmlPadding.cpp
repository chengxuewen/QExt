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

#include <qextQmlPadding.h>

#include <QDebug>

class QExtQmlPaddingPrivate
{
public:
    explicit QExtQmlPaddingPrivate(QExtQmlPadding *q);
    virtual ~QExtQmlPaddingPrivate();

    QExtQmlPadding * const q_ptr;

    double mTopPadding;
    double mLeftPadding;
    double mRightPadding;
    double mBottomPadding;

private:
    QEXT_DECLARE_PUBLIC(QExtQmlPadding)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlPaddingPrivate)
};

QExtQmlPaddingPrivate::QExtQmlPaddingPrivate(QExtQmlPadding *q)
    : q_ptr(q)
    , mTopPadding(0)
    , mLeftPadding(0)
    , mRightPadding(0)
    , mBottomPadding(0)
{
}

QExtQmlPaddingPrivate::~QExtQmlPaddingPrivate()
{
}

QExtQmlPadding::QExtQmlPadding(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlPaddingPrivate(this))
{
}

QExtQmlPadding::QExtQmlPadding(double padding, QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlPaddingPrivate(this))
{
    this->setPadding(padding);
}

QExtQmlPadding::~QExtQmlPadding()
{

}

double QExtQmlPadding::topPadding() const
{
    Q_D(const QExtQmlPadding);
    return d->mTopPadding;
}

double QExtQmlPadding::leftPadding() const
{
    Q_D(const QExtQmlPadding);
    return d->mLeftPadding;
}

double QExtQmlPadding::rightPadding() const
{
    Q_D(const QExtQmlPadding);
    return d->mRightPadding;
}

double QExtQmlPadding::bottomPadding() const
{
    Q_D(const QExtQmlPadding);
    return d->mBottomPadding;
}

void QExtQmlPadding::setPadding(double padding)
{
    this->setTopPadding(padding);
    this->setLeftPadding(padding);
    this->setRightPadding(padding);
    this->setBottomPadding(padding);
}

void QExtQmlPadding::setTopPadding(double padding)
{
    Q_D(QExtQmlPadding);
    if (padding != d->mTopPadding)
    {
        d->mTopPadding = padding;
        emit this->topPaddingChanged(padding);
    }
}

void QExtQmlPadding::setLeftPadding(double padding)
{
    Q_D(QExtQmlPadding);
    if (padding != d->mLeftPadding)
    {
        d->mLeftPadding = padding;
        emit this->leftPaddingChanged(padding);
    }
}

void QExtQmlPadding::setRightPadding(double padding)
{
    Q_D(QExtQmlPadding);
    if (padding != d->mRightPadding)
    {
        d->mRightPadding = padding;
        emit this->rightPaddingChanged(padding);
    }
}

void QExtQmlPadding::setBottomPadding(double padding)
{
    Q_D(QExtQmlPadding);
    if (padding != d->mBottomPadding)
    {
        d->mBottomPadding = padding;
        emit this->bottomPaddingChanged(padding);
    }
}
