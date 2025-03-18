/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
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

#include <private/qextLed_p.h>

#include <QPainter>
#include <QPainterPath>
#include <QRadialGradient>


QExtLedPrivate::QExtLedPrivate(QExtLed *q)
    : q_ptr(q)
{
    m_color = QColor(107, 223, 51);
    m_on = true;
}

QExtLedPrivate::~QExtLedPrivate()
{

}



QExtLed::QExtLed(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtLedPrivate(this))
{

}

QExtLed::~QExtLed()
{

}

QColor QExtLed::color() const
{
    Q_D(const QExtLed);
    return d->m_color;
}

QSize QExtLed::sizeHint() const
{
    return QSize(20,20);
}

QSize QExtLed::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QExtLed::setColor(const QColor &color)
{
    Q_D(QExtLed);
    if (d->m_color != color)
    {
        d->m_color = color;
        this->update();
        emit this->colorChanged(d->m_color);
    }
}

bool QExtLed::isOn() const
{
    Q_D(const QExtLed);
    return d->m_on;
}

void QExtLed::setOn(bool on)
{
    Q_D(QExtLed);
    if (on != d->m_on)
    {
        d->m_on = on;
        this->update();
        emit this->stateChanged(on);
    }
}

void QExtLed::turnOn()
{
    setOn(true);
}

void QExtLed::turnOff()
{
    this->setOn(false);
}

void QExtLed::toggle()
{
    Q_D(QExtLed);
    this->setOn(!d->m_on);
}

void QExtLed::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    Q_D(QExtLed);
    const qreal r = std::min(width(), height()) / 2; // maximum radius including glow
    const qreal glowOffset = std::max(2., r/5.);
    const qreal borderOffset = std::max(1., r/10.);
    const qreal shineOffset = std::max(1., r/20.);
    const QPointF center(width()/2, height()/2);

    const qreal gr = r;
    const qreal br = gr - glowOffset;   // border shape radius
    const qreal ir = br - borderOffset; // inner fill radius
    const qreal sr = ir - shineOffset;

    QColor borderColor(130,130,130);
    QColor shineColor(255, 255, 255, d->m_on ? 200 : 50);
    QColor fillColor(d->m_color);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    // draw border
    painter.setPen(Qt::NoPen);
    painter.setBrush(borderColor);
    painter.drawEllipse(center, br, br);

    // draw infill
    if (!d->m_on) fillColor = fillColor.darker();
    painter.setBrush(fillColor);
    painter.drawEllipse(center, ir, ir);

    // draw glow
    if (d->m_on)
    {
        QColor glowColor(d->m_color);
        glowColor.setAlphaF(0.5);
        QRadialGradient glowGradient(center, gr, center);
        glowGradient.setColorAt(0, glowColor);
        glowGradient.setColorAt((r-glowOffset)/r, glowColor);
        glowGradient.setColorAt(1, Qt::transparent);
        painter.setBrush(glowGradient);
        painter.drawEllipse(center, gr, gr);
    }

    // draw shine
    QRadialGradient shineGradient(center, sr, center-QPoint(sr/2,sr/2));
    shineGradient.setColorAt(0, shineColor);
    shineGradient.setColorAt(1, Qt::transparent);
    painter.setBrush(shineGradient);
    painter.drawEllipse(center, sr, sr);
}
