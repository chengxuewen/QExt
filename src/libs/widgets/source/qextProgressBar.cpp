/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
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

#include <private/qextProgressBar_p.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>

QExtProgressBarPrivate::QExtProgressBarPrivate(QExtProgressBar *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;

    m_precision = 0;
    m_step = 0;
    m_space = 5;
    m_radius = 5;

    m_backgroundStartColor = QColor(100, 100, 100);
    m_backgroundEndColor = QColor(60, 60, 60);

    m_lineColor = QColor(230, 230, 230);
    m_textColor = QColor(0, 0, 0);

    m_barBackgroundColor = QColor(250, 250, 250);
    m_barColor = QColor(100, 184, 255);
}

QExtProgressBarPrivate::~QExtProgressBarPrivate()
{

}



QExtProgressBar::QExtProgressBar(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtProgressBarPrivate(this))
{    
    this->setFont(QFont("Arial", 8));
}

QExtProgressBar::~QExtProgressBar()
{

}

void QExtProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBar(&painter);
}

void QExtProgressBar::drawBackground(QPainter *painter)
{
    Q_D(QExtProgressBar);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, d->m_backgroundStartColor);
    bgGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void QExtProgressBar::drawBar(QPainter *painter)
{
    Q_D(QExtProgressBar);
    painter->save();

    QFont font;
    font.setPixelSize((width() / 10) * 0.35);
    painter->setFont(font);

    double currentValue = (double)(d->m_value - d->m_minValue) * 100 / (d->m_maxValue - d->m_minValue);
    QString strValue = QString("%1%").arg(currentValue, 0, 'f', d->m_precision);
    QString strMaxValue = QString("%1%").arg(d->m_maxValue, 0, 'f', d->m_precision);

    int textWidth = painter->fontMetrics().boundingRect(strMaxValue).width() + 10;

    QPointF textTopLeft(width() - d->m_space - textWidth, d->m_space);
    QPointF textBottomRight(width() - d->m_space, height() - d->m_space);
    QRectF textRect(textTopLeft, textBottomRight);
    painter->setPen(d->m_barBackgroundColor);
    painter->setBrush(d->m_barBackgroundColor);
    painter->drawRoundedRect(textRect, d->m_radius, d->m_radius);

    painter->setPen(d->m_textColor);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    QRectF barBgRect(QPointF(d->m_space, d->m_space), QPointF(width() - d->m_space * 2 - textWidth, height() - d->m_space));
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_barBackgroundColor);
    painter->drawRoundedRect(barBgRect, d->m_radius, d->m_radius);

    double length = width() - d->m_space  - d->m_space * 2 - textWidth;

    double increment = length / (d->m_maxValue - d->m_minValue);
    QRectF barRect(QPointF(d->m_space, d->m_space), QPointF(d->m_space + increment * (d->m_value - d->m_minValue), height() - d->m_space));
    painter->setBrush(d->m_barColor);
    painter->drawRoundedRect(barRect, d->m_radius, d->m_radius);

    painter->setPen(d->m_lineColor);
    int initX = 5;
    int lineCount = barBgRect.width() / d->m_step;
    double lineX = (double)barBgRect.width() / lineCount;

    while (lineCount > 0) {
        QPointF topPot(initX + lineX, d->m_space + 1);
        QPointF bottomPot(initX + lineX, height() - d->m_space - 1);
        painter->drawLine(topPot, bottomPot);
        initX += lineX;
        lineCount--;
    }

    painter->restore();
}

double QExtProgressBar::minValue() const
{
    Q_D(const QExtProgressBar);
    return d->m_minValue;
}

double QExtProgressBar::maxValue() const
{
    Q_D(const QExtProgressBar);
    return d->m_maxValue;
}

double QExtProgressBar::value() const
{
    Q_D(const QExtProgressBar);
    return d->m_value;
}

int QExtProgressBar::precision() const
{
    Q_D(const QExtProgressBar);
    return d->m_precision;
}

int QExtProgressBar::step() const
{
    Q_D(const QExtProgressBar);
    return d->m_step;
}

int QExtProgressBar::space() const
{
    Q_D(const QExtProgressBar);
    return d->m_space;
}

int QExtProgressBar::radius() const
{
    Q_D(const QExtProgressBar);
    return d->m_radius;
}

QColor QExtProgressBar::backgroundStartColor() const
{
    Q_D(const QExtProgressBar);
    return d->m_backgroundStartColor;
}

QColor QExtProgressBar::backgroundEndColor() const
{
    Q_D(const QExtProgressBar);
    return d->m_backgroundEndColor;
}

QColor QExtProgressBar::lineColor() const
{
    Q_D(const QExtProgressBar);
    return d->m_lineColor;
}

QColor QExtProgressBar::textColor() const
{
    Q_D(const QExtProgressBar);
    return d->m_textColor;
}

QColor QExtProgressBar::barBackgroundColor() const
{
    Q_D(const QExtProgressBar);
    return d->m_barBackgroundColor;
}

QColor QExtProgressBar::barColor() const
{
    Q_D(const QExtProgressBar);
    return d->m_barColor;
}

QSize QExtProgressBar::sizeHint() const
{
    return QSize(300, 30);
}

QSize QExtProgressBar::minimumSizeHint() const
{
    return QSize(50, 20);
}

void QExtProgressBar::setRange(double minValue, double maxValue)
{
    Q_D(QExtProgressBar);
    if (minValue >= maxValue) {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    if (d->m_value < minValue || d->m_value > maxValue) {
        this->setValue(d->m_value);
    }

    this->update();
}

void QExtProgressBar::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QExtProgressBar::setMinValue(double minValue)
{
    Q_D(QExtProgressBar);
    this->setRange(minValue, d->m_maxValue);
}

void QExtProgressBar::setMaxValue(double maxValue)
{
    Q_D(QExtProgressBar);
    this->setRange(d->m_minValue, maxValue);
}

void QExtProgressBar::setValue(double value)
{
    Q_D(QExtProgressBar);
    if (value == d->m_value) {
        return;
    }

    if (value < d->m_minValue) {
        value = d->m_minValue;
    } else if (value > d->m_maxValue) {
        value = d->m_maxValue;
    }

    d->m_value = value;
    emit this->valueChanged(value);
    this->update();
}

void QExtProgressBar::setValue(int value)
{
    this->setValue((double)value);
}

void QExtProgressBar::setPrecision(int precision)
{
    Q_D(QExtProgressBar);
    if (precision <= 3 && d->m_precision != precision) {
        d->m_precision = precision;
        this->update();
    }
}

void QExtProgressBar::setStep(int step)
{
    Q_D(QExtProgressBar);
    if (d->m_step != step) {
        d->m_step = step;
        this->update();
    }
}

void QExtProgressBar::setSpace(int space)
{
    Q_D(QExtProgressBar);
    if (d->m_space != space) {
        d->m_space = space;
        this->update();
    }
}

void QExtProgressBar::setRadius(int radius)
{
    Q_D(QExtProgressBar);
    if (d->m_radius != radius) {
        d->m_radius = radius;
        this->update();
    }
}

void QExtProgressBar::setBgColorStart(const QColor &color)
{
    Q_D(QExtProgressBar);
    if (d->m_backgroundStartColor != color) {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QExtProgressBar::setBgColorEnd(const QColor &color)
{
    Q_D(QExtProgressBar);
    if (d->m_backgroundEndColor != color) {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QExtProgressBar::setLineColor(const QColor &color)
{
    Q_D(QExtProgressBar);
    if (d->m_lineColor != color) {
        d->m_lineColor = color;
        this->update();
    }
}

void QExtProgressBar::setTextColor(const QColor &color)
{
    Q_D(QExtProgressBar);
    if (d->m_textColor != color) {
        d->m_textColor = color;
        this->update();
    }
}

void QExtProgressBar::setBarBgColor(const QColor &color)
{
    Q_D(QExtProgressBar);
    if (d->m_barBackgroundColor != color) {
        d->m_barBackgroundColor = color;
        this->update();
    }
}

void QExtProgressBar::setBarColor(const QColor &color)
{
    Q_D(QExtProgressBar);
    if (d->m_barColor != color) {
        d->m_barColor = color;
        this->update();
    }
}
