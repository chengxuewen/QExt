/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
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

#include <private/qextProgressButton_p.h>

#include <QPainter>
#include <QEvent>
#include <QResizeEvent>
#include <QTimer>
#include <QDebug>

QExtProgressButtonPrivate::QExtProgressButtonPrivate(QExtProgressButton *q)
    : q_ptr(q)
{
    m_lineWidth = 8;
    m_lineColor = QColor(250, 250, 250);
    m_borderWidth = 0;
    m_borderColor = QColor(14, 153, 160);
    m_borderRadius = 5;
    m_backgroundColor = QColor(34, 163, 169);
    m_value = 0;
    m_status = 0;
}

QExtProgressButtonPrivate::~QExtProgressButtonPrivate()
{

}



QExtProgressButton::QExtProgressButton(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtProgressButtonPrivate(this))
{
    Q_D(QExtProgressButton);
    d->m_timer = new QTimer(this);
    d->m_timer->setInterval(10);
    connect(d->m_timer, SIGNAL(timeout()), SLOT(progress()));
}

QExtProgressButton::~QExtProgressButton()
{

}

void QExtProgressButton::resizeEvent(QResizeEvent *e)
{
    Q_D(QExtProgressButton);
    d->m_tempWidth = e->size().width();
    this->update();
}

void QExtProgressButton::mousePressEvent(QMouseEvent *)
{
    Q_D(QExtProgressButton);
    if(!d->m_timer->isActive()) {
        d->m_status = 0;
        d->m_value = 0.0;
        d->m_tempWidth = this->width();
        d->m_timer->start();
    }
}

void QExtProgressButton::paintEvent(QPaintEvent *)
{
    Q_D(QExtProgressButton);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if (1 == d->m_status) {
        this->drawProgress(&painter);
    } else {
        this->drawBackground(&painter);
    }
}

void QExtProgressButton::drawBackground(QPainter *painter)
{
    Q_D(QExtProgressButton);
    painter->save();

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPen pen;
    pen.setWidth(d->m_borderWidth);
    pen.setColor(d->m_borderColor);
    painter->setPen(d->m_borderWidth > 0 ? pen : Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);

    QRect rect(((width - d->m_tempWidth) / 2) + d->m_borderWidth, d->m_borderWidth, d->m_tempWidth - (d->m_borderWidth * 2), height - (d->m_borderWidth * 2));
    painter->drawRoundedRect(rect, d->m_borderRadius, d->m_borderRadius);

    QFont font;
    font.setPixelSize(side - 18);
    painter->setFont(font);
    painter->setPen(d->m_lineColor);
    painter->drawText(rect, Qt::AlignCenter, d->m_status == 2 ? "完 成" : "开 始");

    painter->restore();
}

void QExtProgressButton::drawProgress(QPainter *painter)
{
    Q_D(QExtProgressButton);
    painter->save();

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    int radius = 99 - d->m_borderWidth;

    QPen pen;
    pen.setWidth(d->m_borderWidth);
    pen.setColor(d->m_borderColor);
    painter->setPen(d->m_borderWidth > 0 ? pen : Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);

    QRect rectCircle(-radius, -radius, radius * 2, radius * 2);
    painter->translate(width / 2, height / 2);
    painter->scale(side / 200.0, side / 200.0);
    painter->drawEllipse(rectCircle);

    pen.setWidth(d->m_lineWidth);
    pen.setColor(d->m_lineColor);
    painter->setPen(pen);

    int offset = radius - d->m_lineWidth - 5;
    QRectF rectArc(-offset, -offset, offset * 2, offset * 2);
    int startAngle = offset * 16;
    int spanAngle = -d->m_value * 16;
    painter->drawArc(rectArc, startAngle, spanAngle);

    QFont font;
    font.setPixelSize(offset - 15);
    painter->setFont(font);
    QString strValue = QString("%1%").arg((int)d->m_value  * 100 / 360);
    painter->drawText(rectCircle, Qt::AlignCenter, strValue);

    painter->restore();
}

void QExtProgressButton::progress()
{
    Q_D(QExtProgressButton);
    if (0 == d->m_status) {
        d->m_tempWidth -= 5;
        if (d->m_tempWidth < this->height() / 2) {
            d->m_tempWidth = this->height() / 2;
            d->m_status = 1;
        }
    } else if (1 == d->m_status) {
        d->m_value += 1.0;
        if (d->m_value >= 360) {
            d->m_value = 360.0;
            d->m_status = 2;
        }
    } else if (2 == d->m_status) {
        d->m_tempWidth += 5;
        if (d->m_tempWidth > this->width()) {
            d->m_tempWidth = this->width();
            d->m_timer->stop();
        }
    }

    this->update();
}

int QExtProgressButton::lineWidth() const
{
    Q_D(const QExtProgressButton);
    return d->m_lineWidth;
}

QColor QExtProgressButton::lineColor() const
{
    Q_D(const QExtProgressButton);
    return d->m_lineColor;
}

int QExtProgressButton::borderWidth() const
{
    Q_D(const QExtProgressButton);
    return d->m_borderWidth;
}

QColor QExtProgressButton::borderColor() const
{
    Q_D(const QExtProgressButton);
    return d->m_borderColor;
}

int QExtProgressButton::borderRadius() const
{
    Q_D(const QExtProgressButton);
    return d->m_borderRadius;
}

QColor QExtProgressButton::backgroundColor() const
{
    Q_D(const QExtProgressButton);
    return d->m_backgroundColor;
}

QSize QExtProgressButton::sizeHint() const
{
    return QSize(200, 80);
}

QSize QExtProgressButton::minimumSizeHint() const
{
    return QSize(30, 15);
}

void QExtProgressButton::setLineWidth(int width)
{
    Q_D(QExtProgressButton);
    if (d->m_lineWidth != width) {
        d->m_lineWidth = width;
        this->update();
    }
}

void QExtProgressButton::setLineColor(const QColor &color)
{
    Q_D(QExtProgressButton);
    if (d->m_lineColor != color) {
        d->m_lineColor = color;
        this->update();
    }
}

void QExtProgressButton::setBorderWidth(int width)
{
    Q_D(QExtProgressButton);
    if (d->m_borderWidth != width) {
        d->m_borderWidth = width;
        this->update();
    }
}

void QExtProgressButton::setBorderColor(const QColor &color)
{
    Q_D(QExtProgressButton);
    if (d->m_borderColor != color) {
        d->m_borderColor = color;
        this->update();
    }
}

void QExtProgressButton::setBorderRadius(int radius)
{
    Q_D(QExtProgressButton);
    if (d->m_borderRadius != radius) {
        d->m_borderRadius = radius;
        this->update();
    }
}

void QExtProgressButton::setBackgroundColor(const QColor &color)
{
    Q_D(QExtProgressButton);
    if (d->m_backgroundColor != color) {
        d->m_backgroundColor = color;
        this->update();
    }
}
