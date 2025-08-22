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

#include <qextQuickPadding.h>

class QExtQuickPaddingPrivate
{
public:
    explicit QExtQuickPaddingPrivate(QExtQuickPadding *q);
    virtual ~QExtQuickPaddingPrivate();

    QExtQuickPadding * const q_ptr;

    double m_topPadding;
    double m_leftPadding;
    double m_rightPadding;
    double m_bottomPadding;

private:
    QEXT_DECLARE_PUBLIC(QExtQuickPadding)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickPaddingPrivate)
};

QExtQuickPaddingPrivate::QExtQuickPaddingPrivate(QExtQuickPadding *q)
    : q_ptr(q)
    , m_topPadding(0)
    , m_leftPadding(0)
    , m_rightPadding(0)
    , m_bottomPadding(0)
{
}

QExtQuickPaddingPrivate::~QExtQuickPaddingPrivate()
{
}

QExtQuickPadding::QExtQuickPadding(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickPaddingPrivate(this))
{
}

QExtQuickPadding::QExtQuickPadding(double padding, QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickPaddingPrivate(this))
{
    this->setPadding(padding);
}

QExtQuickPadding::~QExtQuickPadding()
{

}

double QExtQuickPadding::topPadding() const
{
    Q_D(const QExtQuickPadding);
    return d->m_topPadding;
}

double QExtQuickPadding::leftPadding() const
{
    Q_D(const QExtQuickPadding);
    return d->m_leftPadding;
}

double QExtQuickPadding::rightPadding() const
{
    Q_D(const QExtQuickPadding);
    return d->m_rightPadding;
}

double QExtQuickPadding::bottomPadding() const
{
    Q_D(const QExtQuickPadding);
    return d->m_bottomPadding;
}

void QExtQuickPadding::setPadding(double padding)
{
    this->setTopPadding(padding);
    this->setLeftPadding(padding);
    this->setRightPadding(padding);
    this->setBottomPadding(padding);
}

void QExtQuickPadding::setTopPadding(double padding)
{
    Q_D(QExtQuickPadding);
    if (padding != d->m_topPadding)
    {
        d->m_topPadding = padding;
        emit this->topPaddingChanged(padding);
    }
}

void QExtQuickPadding::setLeftPadding(double padding)
{
    Q_D(QExtQuickPadding);
    if (padding != d->m_leftPadding)
    {
        d->m_leftPadding = padding;
        emit this->leftPaddingChanged(padding);
    }
}

void QExtQuickPadding::setRightPadding(double padding)
{
    Q_D(QExtQuickPadding);
    if (padding != d->m_rightPadding)
    {
        d->m_rightPadding = padding;
        emit this->rightPaddingChanged(padding);
    }
}

void QExtQuickPadding::setBottomPadding(double padding)
{
    Q_D(QExtQuickPadding);
    if (padding != d->m_bottomPadding)
    {
        d->m_bottomPadding = padding;
        emit this->bottomPaddingChanged(padding);
    }
}
