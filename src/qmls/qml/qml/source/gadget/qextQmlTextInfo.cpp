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

#include <qextQmlTextInfo.h>

class QExtQmlTextInfoPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlTextInfoPrivate)
    QEXT_DECLARE_PUBLIC(QExtQmlTextInfo)
public:
    explicit QExtQmlTextInfoPrivate(QExtQmlTextInfo *q);
    virtual ~QExtQmlTextInfoPrivate();

    QExtQmlTextInfo * const q_ptr;

    QString mText;
    QColor mColor;
    qreal mScale;
    QFont mFont;

private:
};

QExtQmlTextInfoPrivate::QExtQmlTextInfoPrivate(QExtQmlTextInfo *q)
    : q_ptr(q)
{
    mText = "";
    mColor = Qt::black;
    mScale = 1;
    mFont = QFont();
}

QExtQmlTextInfoPrivate::~QExtQmlTextInfoPrivate()
{
}

QExtQmlTextInfo::QExtQmlTextInfo(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlTextInfoPrivate(this))
{

}

QExtQmlTextInfo::~QExtQmlTextInfo()
{

}

QString QExtQmlTextInfo::text() const
{
    Q_D(const QExtQmlTextInfo);
    return d->mText;
}

QColor QExtQmlTextInfo::color() const
{
    Q_D(const QExtQmlTextInfo);
    return d->mColor;
}

qreal QExtQmlTextInfo::scale() const
{
    Q_D(const QExtQmlTextInfo);
    return d->mScale;
}

QFont QExtQmlTextInfo::font() const
{
    Q_D(const QExtQmlTextInfo);
    return d->mFont;
}

void QExtQmlTextInfo::setText(const QString &text)
{
    Q_D(QExtQmlTextInfo);
    if (text != d->mText)
    {
        d->mText = text;
        emit this->textChanged();
    }
}

void QExtQmlTextInfo::setColor(const QColor &color)
{
    Q_D(QExtQmlTextInfo);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
    }
}

void QExtQmlTextInfo::setScale(const qreal &scale)
{
    Q_D(QExtQmlTextInfo);
    if (!qFuzzyCompare(d->mScale, scale))
    {
        d->mScale = scale;
        emit this->scaleChanged();
    }
}

void QExtQmlTextInfo::setFont(const QFont &font)
{
    Q_D(QExtQmlTextInfo);
    if (font != d->mFont)
    {
        d->mFont = font;
        emit this->fontChanged();
    }
}
