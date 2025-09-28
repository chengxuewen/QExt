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

#include <qextQmlTextData.h>

class QExtQmlTextDataPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlTextDataPrivate)
    QEXT_DECLARE_PUBLIC(QExtQmlTextData)
public:
    explicit QExtQmlTextDataPrivate(QExtQmlTextData *q);
    virtual ~QExtQmlTextDataPrivate();

    QExtQmlTextData * const q_ptr;

    QString mText;
    QColor mColor;
    qreal mScale;
    QFont mFont;
    int mFontSize;

private:
};

QExtQmlTextDataPrivate::QExtQmlTextDataPrivate(QExtQmlTextData *q)
    : q_ptr(q)
{
    mText = "";
    mColor = Qt::black;
    mScale = 1;
    mFont = QFont();
    mFontSize = 12;
}

QExtQmlTextDataPrivate::~QExtQmlTextDataPrivate()
{
}

QExtQmlTextData::QExtQmlTextData(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlTextDataPrivate(this))
{

}

QExtQmlTextData::~QExtQmlTextData()
{

}

QString QExtQmlTextData::text() const
{
    Q_D(const QExtQmlTextData);
    return d->mText;
}

QColor QExtQmlTextData::color() const
{
    Q_D(const QExtQmlTextData);
    return d->mColor;
}

qreal QExtQmlTextData::scale() const
{
    Q_D(const QExtQmlTextData);
    return d->mScale;
}

QFont QExtQmlTextData::font() const
{
    Q_D(const QExtQmlTextData);
    return d->mFont;
}

int QExtQmlTextData::fontSize() const
{
    Q_D(const QExtQmlTextData);
    return d->mFontSize;
}

void QExtQmlTextData::setFontSize(const int &size)
{
    Q_D(QExtQmlTextData);
    if (size != d->mFontSize)
    {
        d->mFontSize = size;
        emit this->fontSizeChanged(size);
    }
}

void QExtQmlTextData::setText(const QString &text)
{
    Q_D(QExtQmlTextData);
    if (text != d->mText)
    {
        d->mText = text;
        emit this->textChanged();
    }
}

void QExtQmlTextData::setColor(const QColor &color)
{
    Q_D(QExtQmlTextData);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
    }
}

void QExtQmlTextData::setScale(const qreal &scale)
{
    Q_D(QExtQmlTextData);
    if (!qFuzzyCompare(d->mScale, scale))
    {
        d->mScale = scale;
        emit this->scaleChanged();
    }
}

void QExtQmlTextData::setFont(const QFont &font)
{
    Q_D(QExtQmlTextData);
    if (font != d->mFont)
    {
        d->mFont = font;
        emit this->fontChanged();
    }
}
