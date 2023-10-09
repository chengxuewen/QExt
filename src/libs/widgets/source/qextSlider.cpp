/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
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

#include <private/qextSlider_p.h>
#include <qextTooltip.h>

#include <QEvent>
#include <QDebug>
#include <QMouseEvent>

QExtSliderPrivate::QExtSliderPrivate(QExtSlider *q)
    : q_ptr(q)
{
    m_borderRadius = 5;
    m_arrowSize = 5;
    m_arrowStyle = QExtSlider::ArrowStyle_Bottom;

    m_backgroundColor = QColor(100, 184, 255);
    m_foregroundColor = QColor(255, 255, 255);

    m_tooltipWidth = 50;
    m_tooltipHeight = 30;
    m_tooltipFont = q_ptr->font();

    m_timeVisible = false;
    m_clickEnable = true;
    m_unitText = "";

    m_tooltip = new QExtTooltip;
    m_tooltip->setBorderRadius(m_borderRadius);
    m_tooltip->setArrowSize(m_arrowSize);
    m_tooltip->setArrowPosition((QExtTooltip::ArrowPositionType)m_arrowStyle);
    m_tooltip->setBackgroundColor(m_backgroundColor);
    m_tooltip->setForegroundColor(m_foregroundColor);
    m_tooltip->resize(m_tooltipWidth, m_tooltipHeight);
    m_tooltip->setFont(m_tooltipFont);

    m_tooltip->setFocusPolicy(Qt::NoFocus);
    m_tooltip->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    m_tooltip->setAttribute(Qt::WA_TranslucentBackground, false);
}

QExtSliderPrivate::~QExtSliderPrivate()
{
    m_tooltip->deleteLater();
}



QExtSlider::QExtSlider(QWidget *parent)
    : QSlider(parent), dd_ptr(new QExtSliderPrivate(this))
{
    this->setOrientation(Qt::Horizontal);
}

QExtSlider::~QExtSlider()
{

}

void QExtSlider::mousePressEvent(QMouseEvent *e)
{
    Q_D(QExtSlider);
    if (e->button() != Qt::LeftButton)
    {
        return;
    }

    if (d->m_clickEnable)
    {
        double pos, value;
        if (this->orientation() == Qt::Horizontal)
        {
            pos = e->pos().x() / (double)width();
            value = pos * (maximum() - minimum()) + minimum();
        }
        else
        {
            pos = e->pos().y() / (double)height();
            value = maximum() - pos * (maximum() - minimum()) + minimum();
        }

        this->setValue(value + 0.5);

        emit clicked();
    }

    this->mouseMoveEvent(e);
    d->m_tooltip->setVisible(true);
    QSlider::mousePressEvent(e);
}

void QExtSlider::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(QExtSlider);
    d->m_tooltip->setVisible(false);
    QSlider::mouseReleaseEvent(e);
}

void QExtSlider::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QExtSlider);
    if (e->button() & Qt::RightButton)
    {
        return;
    }

    QPoint pos = e->pos();
    int x = pos.x();
    int y = pos.y();

    if (this->orientation() == Qt::Horizontal)
    {
        if (x < 0 || x > width())
        {
            return;
        }

        x = QCursor::pos().x();
        y = this->mapToGlobal(this->pos()).y();
        x = x - d->m_tooltipWidth / 2 + this->x();
        y = y - (d->m_arrowStyle == ArrowStyle_Top ? -height() : d->m_tooltipHeight);
    }
    else
    {
        if (y < 0 || y > height())
        {
            return;
        }

        x = this->mapToGlobal(this->pos()).x();
        y = QCursor::pos().y();
        x = x - (d->m_arrowStyle == ArrowStyle_Left ? -width() : d->m_tooltipWidth);
        y = y - d->m_tooltipHeight / 2 + this->y();
    }

    QString str = QString("%1").arg(value());

    if (d->m_timeVisible)
    {
        uint length = value() / 1000;
        str = (QString("%1:%2").arg(length / 60, 2, 10, QChar('0')).arg(length % 60, 2, 10, QChar('0')));
    }

    d->m_tooltip->setText(QString("%1%2").arg(str).arg(d->m_unitText));
    d->m_tooltip->move(this->mapFromParent(QPoint(x, y)));
    QSlider::mouseMoveEvent(e);
}

int QExtSlider::borderRadius() const
{
    Q_D(const QExtSlider);
    return d->m_borderRadius;
}

int QExtSlider::arrowSize() const
{
    Q_D(const QExtSlider);
    return d->m_arrowSize;
}

QExtSlider::ArrowStyleType QExtSlider::arrowStyle() const
{
    Q_D(const QExtSlider);
    return d->m_arrowStyle;
}

QColor QExtSlider::backgroundColor() const
{
    Q_D(const QExtSlider);
    return d->m_backgroundColor;
}

QColor QExtSlider::foregroundColor() const
{
    Q_D(const QExtSlider);
    return d->m_foregroundColor;
}

int QExtSlider::toolTipWidth() const
{
    Q_D(const QExtSlider);
    return d->m_tooltipWidth;
}

int QExtSlider::toolTipHeight() const
{
    Q_D(const QExtSlider);
    return d->m_tooltipHeight;
}

QFont QExtSlider::toolTipFont() const
{
    Q_D(const QExtSlider);
    return d->m_tooltipFont;
}

bool QExtSlider::timeVisible() const
{
    Q_D(const QExtSlider);
    return d->m_timeVisible;
}

bool QExtSlider::clickEnable() const
{
    Q_D(const QExtSlider);
    return d->m_clickEnable;
}

QString QExtSlider::unitText() const
{
    Q_D(const QExtSlider);
    return d->m_unitText;
}

QExtTooltip *QExtSlider::tooltip() const
{
    Q_D(const QExtSlider);
    return d->m_tooltip;
}

void QExtSlider::setBorderRadius(int radius)
{
    Q_D(QExtSlider);
    if (d->m_borderRadius != radius)
    {
        d->m_borderRadius = radius;
        d->m_tooltip->setBorderRadius(radius);
    }
}

void QExtSlider::setArrowSize(int size)
{
    Q_D(QExtSlider);
    if (d->m_arrowSize != size)
    {
        d->m_arrowSize = size;
        d->m_tooltip->setArrowSize(size);
    }
}

void QExtSlider::setArrowStyle(const QExtSlider::ArrowStyleType &style)
{
    Q_D(QExtSlider);
    if (d->m_arrowStyle != style)
    {
        d->m_arrowStyle = style;
        d->m_tooltip->setArrowPosition((QExtTooltip::ArrowPositionType)style);
    }
}

void QExtSlider::setBackgroundColor(const QColor &color)
{
    Q_D(QExtSlider);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        d->m_tooltip->setBackgroundColor(color);
    }
}

void QExtSlider::setForegroundColor(const QColor &color)
{
    Q_D(QExtSlider);
    if (d->m_foregroundColor != color)
    {
        d->m_foregroundColor = color;
        d->m_tooltip->setForegroundColor(color);
    }
}

void QExtSlider::setToolTipWidth(int width)
{
    Q_D(QExtSlider);
    if (d->m_tooltipWidth != width)
    {
        d->m_tooltipWidth = width;
        d->m_tooltip->resize(width, d->m_tooltipHeight);
    }
}

void QExtSlider::setToolTipHeight(int height)
{
    Q_D(QExtSlider);
    if (d->m_tooltipHeight != height)
    {
        d->m_tooltipHeight = height;
        d->m_tooltip->resize(d->m_tooltipWidth, height);
    }
}

void QExtSlider::setToolTipFont(const QFont &font)
{
    Q_D(QExtSlider);
    if (d->m_tooltipFont != font)
    {
        d->m_tooltipFont = font;
        d->m_tooltip->setFont(font);
    }
}

void QExtSlider::setTimeVisible(bool visiable)
{
    Q_D(QExtSlider);
    if (d->m_timeVisible != visiable)
    {
        d->m_timeVisible = visiable;
    }
}

void QExtSlider::setClickEnable(bool enable)
{
    Q_D(QExtSlider);
    if (d->m_clickEnable != enable)
    {
        d->m_clickEnable = enable;
    }
}

void QExtSlider::setUnitText(const QString &unit)
{
    Q_D(QExtSlider);
    if (d->m_unitText != unit)
    {
        d->m_unitText = unit;
    }
}
