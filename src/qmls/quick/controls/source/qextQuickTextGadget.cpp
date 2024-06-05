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

#include <private/qextQuickTextGadget_p.h>

QExtQuickTextGadgetPrivate::QExtQuickTextGadgetPrivate(QExtQuickTextGadget *q)
    : q_ptr(q)
{
    m_text = "";
    m_color = Qt::black;
    m_scale = 1;
    m_font = QFont();
    m_fontSize = 12;
}

QExtQuickTextGadgetPrivate::~QExtQuickTextGadgetPrivate()
{

}



QExtQuickTextGadget::QExtQuickTextGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickTextGadgetPrivate(this))
{

}

QExtQuickTextGadget::~QExtQuickTextGadget()
{

}

QString QExtQuickTextGadget::text() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_text;
}

QColor QExtQuickTextGadget::color() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_color;
}

qreal QExtQuickTextGadget::scale() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_scale;
}

QFont QExtQuickTextGadget::font() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_font;
}

int QExtQuickTextGadget::fontSize() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_fontSize;
}

void QExtQuickTextGadget::setFontSize(const int &size)
{
    Q_D(QExtQuickTextGadget);
    if (size != d->m_fontSize) {
        d->m_fontSize = size;
        emit this->fontSizeChanged(size);
    }
}

void QExtQuickTextGadget::setText(const QString &text)
{
    Q_D(QExtQuickTextGadget);
    if (text != d->m_text) {
        d->m_text = text;
        emit this->textChanged();
    }
}

void QExtQuickTextGadget::setColor(const QColor &color)
{
    Q_D(QExtQuickTextGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QExtQuickTextGadget::setScale(const qreal &scale)
{
    Q_D(QExtQuickTextGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QExtQuickTextGadget::setFont(const QFont &font)
{
    Q_D(QExtQuickTextGadget);
    if (font != d->m_font) {
        d->m_font = font;
        emit this->fontChanged();
    }
}
