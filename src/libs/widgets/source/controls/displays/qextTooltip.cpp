/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2022~Present ChengXueWen. Contact: 1398831004@qq.com.
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

#include <private/qextTooltip_p.h>

#include <QPainter>
#include <QEvent>
#include <QDebug>

QExtTooltipPrivate::QExtTooltipPrivate(QExtTooltip *q)
    : q_ptr(q)
{
    m_borderRadius = 5;
    m_backgroundColor = QColor(100, 184, 255);
    m_foregroundColor = QColor(255, 255, 255);

    m_arrowVisible = true;
    m_arrowSize = 5;
    m_arrowPosition = QExtTooltip::ArrowPosition_Right;

    m_triangleVisible = false;
    m_triangleLen = 5;
    m_trianglePosition = QExtTooltip::TrianglePosition_Left;
    m_triangleColor = QColor(255, 255, 255);

    m_backgroundRect = q_ptr->geometry();
}

QExtTooltipPrivate::~QExtTooltipPrivate()
{

}



QExtTooltip::QExtTooltip(QWidget *parent)
    : QLabel(parent), dd_ptr(new QExtTooltipPrivate(this))
{
    this->setFont(QFont("Microsoft Yahei", 10));
}

QExtTooltip::~QExtTooltip()
{

}

void QExtTooltip::mousePressEvent(QMouseEvent *)
{
    emit this->clicked();
}

void QExtTooltip::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);

    this->drawText(&painter);

    this->drawTriangle(&painter);
}

void QExtTooltip::drawBackground(QPainter *painter)
{
    Q_D(QExtTooltip);
    int width = this->width();
    int height = this->height();
    int endX = width - d->m_arrowSize;
    int endY = height - d->m_arrowSize;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);

    QPolygon pts;
    if (d->m_arrowPosition == ArrowPosition_Right)
    {
        d->m_backgroundRect = QRect(0, 0, endX, height);
        pts.setPoints(3, endX, height / 2 - d->m_arrowSize, endX, height / 2 + d->m_arrowSize, width, height / 2);
    }
    else if (d->m_arrowPosition == ArrowPosition_Left)
    {
        d->m_backgroundRect = QRect(d->m_arrowSize, 0, width - d->m_arrowSize, height);
        pts.setPoints(3, d->m_arrowSize, height / 2 - d->m_arrowSize, d->m_arrowSize, height / 2 + d->m_arrowSize, 0, height / 2);
    }
    else if (d->m_arrowPosition == ArrowPosition_Bottom)
    {
        d->m_backgroundRect = QRect(0, 0, width, endY);
        pts.setPoints(3, width / 2 - d->m_arrowSize, endY, width / 2 + d->m_arrowSize, endY, width / 2, height);
    }
    else if (d->m_arrowPosition == ArrowPosition_Top)
    {
        d->m_backgroundRect = QRect(0, d->m_arrowSize, width, height - d->m_arrowSize);
        pts.setPoints(3, width / 2 - d->m_arrowSize, d->m_arrowSize, width / 2 + d->m_arrowSize, d->m_arrowSize, width / 2, 0);
    }

    if (!d->m_arrowVisible)
    {
        d->m_backgroundRect = this->rect();
        painter->drawRoundedRect(d->m_backgroundRect, d->m_borderRadius, d->m_borderRadius);
    }
    else
    {
        painter->drawRoundedRect(d->m_backgroundRect, d->m_borderRadius, d->m_borderRadius);
        painter->drawPolygon(pts);
    }

    painter->restore();
}

void QExtTooltip::drawText(QPainter *painter)
{
    Q_D(QExtTooltip);
    painter->save();
    painter->setPen(d->m_foregroundColor);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(d->m_backgroundRect, Qt::AlignCenter, this->text());
    painter->restore();
}

void QExtTooltip::drawTriangle(QPainter *painter)
{
    Q_D(QExtTooltip);
    if (!d->m_triangleVisible)
    {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_triangleColor);

    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;

    QPolygon pts;
    if (d->m_trianglePosition == TrianglePosition_Left)
    {
        pts.setPoints(3, d->m_triangleLen, midHeight, 0, midHeight - d->m_triangleLen, 0, midHeight + d->m_triangleLen);
    }
    else if (d->m_trianglePosition == TrianglePosition_Right)
    {
        pts.setPoints(3, width - d->m_triangleLen, midHeight, width, midHeight - d->m_triangleLen, width, midHeight + d->m_triangleLen);
    }
    else if (d->m_trianglePosition == TrianglePosition_Top)
    {
        pts.setPoints(3, midWidth, d->m_triangleLen, midWidth - d->m_triangleLen, 0, midWidth + d->m_triangleLen, 0);
    }
    else if (d->m_trianglePosition == TrianglePosition_Bottom)
    {
        pts.setPoints(3, midWidth, height - d->m_triangleLen, midWidth - d->m_triangleLen, height, midWidth + d->m_triangleLen, height);
    }

    painter->drawPolygon(pts);

    painter->restore();
}

int QExtTooltip::borderRadius() const
{
    Q_D(const QExtTooltip);
    return d->m_borderRadius;
}

QColor QExtTooltip::backgroundColor() const
{
    Q_D(const QExtTooltip);
    return d->m_backgroundColor;
}

QColor QExtTooltip::foregroundColor() const
{
    Q_D(const QExtTooltip);
    return d->m_foregroundColor;
}

bool QExtTooltip::arrowVisible() const
{
    Q_D(const QExtTooltip);
    return d->m_arrowVisible;
}

int QExtTooltip::arrowSize() const
{
    Q_D(const QExtTooltip);
    return d->m_arrowSize;
}

QExtTooltip::ArrowPositionType QExtTooltip::arrowPosition() const
{
    Q_D(const QExtTooltip);
    return d->m_arrowPosition;
}

bool QExtTooltip::triangleVisible() const
{
    Q_D(const QExtTooltip);
    return d->m_triangleVisible;
}

int QExtTooltip::triangleLen() const
{
    Q_D(const QExtTooltip);
    return d->m_triangleLen;
}

QExtTooltip::TrianglePositionType QExtTooltip::trianglePosition() const
{
    Q_D(const QExtTooltip);
    return d->m_trianglePosition;
}

QColor QExtTooltip::triangleColor() const
{
    Q_D(const QExtTooltip);
    return d->m_triangleColor;
}

QSize QExtTooltip::sizeHint() const
{
    return QSize(100, 30);
}

QSize QExtTooltip::minimumSizeHint() const
{
    return QSize(20, 10);
}

void QExtTooltip::setBorderRadius(int radius)
{
    Q_D(QExtTooltip);
    if (d->m_borderRadius != radius)
    {
        d->m_borderRadius = radius;
        this->update();
    }
}

void QExtTooltip::setArrowVisible(bool visiable)
{
    Q_D(QExtTooltip);
    if (d->m_arrowVisible != visiable)
    {
        d->m_arrowVisible = visiable;
        this->update();
    }
}

void QExtTooltip::setArrowSize(int size)
{
    Q_D(QExtTooltip);
    if (d->m_arrowSize != size)
    {
        d->m_arrowSize = size;
        this->update();
    }
}

void QExtTooltip::setArrowPosition(const QExtTooltip::ArrowPositionType &position)
{
    Q_D(QExtTooltip);
    if (d->m_arrowPosition != position)
    {
        d->m_arrowPosition = position;
        this->update();
    }
}

void QExtTooltip::setTriangleVisible(bool visiable)
{
    Q_D(QExtTooltip);
    if (d->m_triangleVisible != visiable)
    {
        d->m_triangleVisible = visiable;
        this->update();
    }
}

void QExtTooltip::setTriangleLen(int len)
{
    Q_D(QExtTooltip);
    if (d->m_triangleLen != len)
    {
        d->m_triangleLen = len;
        this->update();
    }
}

void QExtTooltip::setTrianglePosition(const QExtTooltip::TrianglePositionType &position)
{
    Q_D(QExtTooltip);
    if (d->m_trianglePosition != position)
    {
        d->m_trianglePosition = position;
        this->update();
    }
}

void QExtTooltip::setTriangleColor(const QColor &color)
{
    Q_D(QExtTooltip);
    if (d->m_triangleColor != color)
    {
        d->m_triangleColor = color;
        this->update();
    }
}

void QExtTooltip::setBackgroundColor(const QColor &color)
{
    Q_D(QExtTooltip);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QExtTooltip::setForegroundColor(const QColor &color)
{
    Q_D(QExtTooltip);
    if (d->m_foregroundColor != color)
    {
        d->m_foregroundColor = color;
        this->update();
    }
}

