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

#include <private/qextThermometer_p.h>

#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QDebug>


QExtThermometerPrivate::QExtThermometerPrivate(QExtThermometer *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;

    m_precision = 0;
    m_longStep = 10;
    m_shortStep = 2;
    m_space = 10;

    m_animation = false;
    m_animationStep = 1.0;

    m_userValueVisible = false;
    m_userValue = 80;
    m_userValueColor = QColor(255, 107, 107);

    m_backgroundStartColor = QColor(100, 100, 100);
    m_backgroundEndColor = QColor(60, 60, 60);
    m_lineColor = QColor(255, 255, 255);

    m_barBackgroundColor = QColor(230, 230, 230);
    m_barColor = QColor(100, 184, 255);

    m_barPosition = QExtThermometer::BarPosition_Center;
    m_tickPosition = QExtThermometer::TickPosition_Both;

    m_reverse = false;
    m_currentValue = 0;
}

QExtThermometerPrivate::~QExtThermometerPrivate()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}



QExtThermometer::QExtThermometer(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtThermometerPrivate(this))
{
    Q_D(QExtThermometer);
    d->m_timer = new QTimer(this);
    d->m_timer->setInterval(10);
    connect(d->m_timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    this->setFont(QFont("Arial", 9));
}

QExtThermometer::~QExtThermometer()
{

}

void QExtThermometer::resizeEvent(QResizeEvent *)
{
    Q_D(QExtThermometer);
    d->m_radius = qMin(width(), height()) / 5;
    d->m_barWidth = (d->m_radius * 2) / 3;
    d->m_barHeight = height() - d->m_radius * 2;

    if (d->m_barPosition == BarPosition_Left) {
        d->m_targetX = width() / 4;
    } else if (d->m_barPosition == BarPosition_Right) {
        d->m_targetX = width() / 1.3;
    } else if (d->m_barPosition == BarPosition_Center) {
        d->m_targetX = width() / 2;
    }

    this->setValue(d->m_value);
}

void QExtThermometer::paintEvent(QPaintEvent *)
{
    Q_D(QExtThermometer);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);

    if (d->m_tickPosition == TickPosition_Left) {
        this->drawRuler(&painter, 0);
    } else if (d->m_tickPosition == TickPosition_Right) {
        this->drawRuler(&painter, 1);
    } else if (d->m_tickPosition == TickPosition_Both) {
        this->drawRuler(&painter, 0);
        this->drawRuler(&painter, 1);
    }

    this->drawBarBackground(&painter);

    this->drawBar(&painter);

    this->drawValue(&painter);
}

void QExtThermometer::drawBackground(QPainter *painter)
{
    Q_D(QExtThermometer);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, d->m_backgroundStartColor);
    bgGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void QExtThermometer::drawBarBackground(QPainter *painter)
{
    Q_D(QExtThermometer);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_barBackgroundColor);

    int barX = d->m_targetX - d->m_barWidth / 2;
    int barY = d->m_space;
    QRectF barRect(barX, barY, d->m_barWidth, d->m_barHeight);

    int circleX = d->m_targetX - d->m_radius;
    int circleY = height() - d->m_radius * 2 - 2;
    int circleWidth = d->m_radius * 2;
    QRectF circleRect(circleX, circleY, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);
    painter->restore();
}

void QExtThermometer::drawRuler(QPainter *painter, int type)
{
    Q_D(QExtThermometer);
    painter->save();
    painter->setPen(d->m_lineColor);

    int barPercent = d->m_barWidth / 8;

    if (barPercent < 2) {
        barPercent = 2;
    }

    double length = height() - 2 * d->m_space - 2 * d->m_radius;

    double increment = length / (d->m_maxValue - d->m_minValue);

    int longLineLen = 10;
    int shortLineLen = 7;

    int offset = d->m_barWidth / 2 + 5;

    if (type == 0) {
        offset = -offset;
        longLineLen = -longLineLen;
        shortLineLen = -shortLineLen;
    }

    double initX = d->m_targetX + offset;
    double initY = d->m_space + barPercent;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - 2 * d->m_radius - 5);
    painter->drawLine(topPot, bottomPot);

    for (int i = d->m_maxValue; i >= d->m_minValue; i = i - d->m_shortStep) {
        if (i % d->m_longStep == 0) {
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', d->m_precision);
            double fontHeight = painter->fontMetrics().height();

            if (type == 0) {
                QRect textRect(initX - 45, initY - fontHeight / 3, 30, 15);
                painter->drawText(textRect, Qt::AlignRight, strValue);
            } else if (type == 1) {
                QRect textRect(initX + longLineLen + 5, initY - fontHeight / 3, 30, 15);
                painter->drawText(textRect, Qt::AlignLeft, strValue);
            }
        } else {
            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * d->m_shortStep;
    }

    painter->restore();
}

void QExtThermometer::drawBar(QPainter *painter)
{
    Q_D(QExtThermometer);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_barColor);

    int barPercent = d->m_barWidth / 8;
    int circlePercent = d->m_radius / 6;

    if (barPercent < 2) {
        barPercent = 2;
    }

    if (circlePercent < 2) {
        circlePercent = 2;
    }

    double length = height() - 2 * d->m_space - 2 * d->m_radius;

    double increment = length / (d->m_maxValue - d->m_minValue);

    int rulerHeight = height() - 1 * d->m_space - 2 * d->m_radius;

    int barX = d->m_targetX - d->m_barWidth / 2;
    int barY = rulerHeight - (d->m_currentValue - d->m_minValue) * increment;
    d->m_barRect = QRectF(barX + barPercent, barY + barPercent, d->m_barWidth - barPercent * 2, d->m_barHeight + d->m_radius - barY);

    int circleX = d->m_targetX - d->m_radius;
    int circleY = height() - d->m_radius * 2 - 2;
    int circleWidth = d->m_radius * 2 - circlePercent * 2;
    d->m_circleRect = QRectF(circleX + circlePercent, circleY + circlePercent, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(d->m_barRect);
    path.addEllipse(d->m_circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);

    if (d->m_userValueVisible) {
        if (d->m_tickPosition == TickPosition_Left || d->m_tickPosition == TickPosition_Both) {
            QPolygon pts;
            int offset = 15;
            double initX = d->m_targetX - (d->m_barWidth / 2 + 5);
            double initY = rulerHeight - (d->m_userValue - d->m_minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX - offset, initY - offset / 2));
            pts.append(QPoint(initX - offset, initY + offset / 2));
            painter->setBrush(d->m_userValueColor);
            painter->drawPolygon(pts);
        }

        if (d->m_tickPosition == TickPosition_Right || d->m_tickPosition == TickPosition_Both) {
            QPolygon pts;
            int offset = 15;
            double initX = d->m_targetX + (d->m_barWidth / 2 + 5);
            double initY = rulerHeight - (d->m_userValue - d->m_minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX + offset, initY - offset / 2));
            pts.append(QPoint(initX + offset, initY + offset / 2));
            painter->setBrush(d->m_userValueColor);
            painter->drawPolygon(pts);
        }
    }

    painter->restore();
}

void QExtThermometer::drawValue(QPainter *painter)
{
    Q_D(QExtThermometer);
    painter->save();

    QFont font;
    font.setPixelSize(d->m_circleRect.width() * 0.55);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(d->m_circleRect, Qt::AlignCenter, QString("%1").arg(d->m_currentValue));

    painter->restore();
}

double QExtThermometer::minValue() const
{
    Q_D(const QExtThermometer);
    return d->m_minValue;
}

double QExtThermometer::maxValue() const
{
    Q_D(const QExtThermometer);
    return d->m_maxValue;
}

double QExtThermometer::value() const
{
    Q_D(const QExtThermometer);
    return d->m_value;
}

int QExtThermometer::precision() const
{
    Q_D(const QExtThermometer);
    return d->m_precision;
}

int QExtThermometer::longStep() const
{
    Q_D(const QExtThermometer);
    return d->m_longStep;
}

int QExtThermometer::shortStep() const
{
    Q_D(const QExtThermometer);
    return d->m_shortStep;
}

int QExtThermometer::space() const
{
    Q_D(const QExtThermometer);
    return d->m_space;
}

bool QExtThermometer::animationEnable() const
{
    Q_D(const QExtThermometer);
    return d->m_animation;
}

double QExtThermometer::animationStep() const
{
    Q_D(const QExtThermometer);
    return d->m_animationStep;
}

bool QExtThermometer::userValueVisible() const
{
    Q_D(const QExtThermometer);
    return d->m_userValueVisible;
}

double QExtThermometer::userValue() const
{
    Q_D(const QExtThermometer);
    return d->m_userValue;
}

QColor QExtThermometer::userValueColor() const
{
    Q_D(const QExtThermometer);
    return d->m_userValueColor;
}

QColor QExtThermometer::backgroundStartColor() const
{
    Q_D(const QExtThermometer);
    return d->m_backgroundStartColor;
}

QColor QExtThermometer::backgroundEndColor() const
{
    Q_D(const QExtThermometer);
    return d->m_backgroundEndColor;
}

QColor QExtThermometer::lineColor() const
{
    Q_D(const QExtThermometer);
    return d->m_lineColor;
}

QColor QExtThermometer::barBackgroundColor() const
{
    Q_D(const QExtThermometer);
    return d->m_barBackgroundColor;
}

QColor QExtThermometer::barColor() const
{
    Q_D(const QExtThermometer);
    return d->m_barColor;
}

QExtThermometer::BarPosition QExtThermometer::barPosition() const
{
    Q_D(const QExtThermometer);
    return d->m_barPosition;
}

QExtThermometer::TickPosition QExtThermometer::tickPosition() const
{
    Q_D(const QExtThermometer);
    return d->m_tickPosition;
}

QSize QExtThermometer::sizeHint() const
{
    return QSize(130, 350);
}

QSize QExtThermometer::minimumSizeHint() const
{
    return QSize(20, 50);
}

void QExtThermometer::setRange(double minValue, double maxValue)
{
    Q_D(QExtThermometer);
    if (minValue >= maxValue) {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    if (d->m_value < minValue || d->m_value > maxValue) {
        setValue(d->m_value);
    }

    this->update();
}

void QExtThermometer::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QExtThermometer::setMinValue(double minValue)
{
    Q_D(QExtThermometer);
    this->setRange(minValue, d->m_maxValue);
}

void QExtThermometer::setMaxValue(double maxValue)
{
    Q_D(QExtThermometer);
    this->setRange(d->m_minValue, maxValue);
}

void QExtThermometer::setValue(double value)
{
    Q_D(QExtThermometer);
    if (value == d->m_value) {
        return;
    }

    if (value < d->m_minValue) {
        value = d->m_minValue;
    } else if (value > d->m_maxValue) {
        value = d->m_maxValue;
    }

    if (value > d->m_value) {
        d->m_reverse = false;
    } else if (value < d->m_value) {
        d->m_reverse = true;
    }

    d->m_value = value;
    emit this->valueChanged(value);

    if (!d->m_animation) {
        d->m_currentValue = d->m_value;
        this->update();
    } else {
        d->m_timer->start();
    }
}

void QExtThermometer::setValue(int value)
{
    this->setValue((double)value);
}

void QExtThermometer::setPrecision(int precision)
{
    Q_D(QExtThermometer);
    if (precision <= 3 && d->m_precision != precision) {
        d->m_precision = precision;
        this->update();
    }
}

void QExtThermometer::setLongStep(int longStep)
{
    Q_D(QExtThermometer);
    if (longStep < d->m_shortStep) {
        return;
    }

    if (d->m_longStep != longStep) {
        d->m_longStep = longStep;
        this->update();
    }
}

void QExtThermometer::setShortStep(int shortStep)
{
    Q_D(QExtThermometer);
    if (d->m_longStep < shortStep) {
        return;
    }

    if (d->m_shortStep != shortStep) {
        d->m_shortStep = shortStep;
        this->update();
    }
}

void QExtThermometer::setSpace(int space)
{
    Q_D(QExtThermometer);
    if (d->m_space != space) {
        d->m_space = space;
        this->update();
    }
}

void QExtThermometer::setAnimationEnable(bool enable)
{
    Q_D(QExtThermometer);
    if (d->m_animation != enable) {
        d->m_animation = enable;
        this->update();
    }
}

void QExtThermometer::setAnimationStep(double animationStep)
{
    Q_D(QExtThermometer);
    if (d->m_animationStep != animationStep) {
        d->m_animationStep = animationStep;
        this->update();
    }
}

void QExtThermometer::setUserValueVisible(bool visiable)
{
    Q_D(QExtThermometer);
    if (d->m_userValueVisible != visiable) {
        d->m_userValueVisible = visiable;
        this->update();
    }
}

void QExtThermometer::setUserValue(double userValue)
{
    Q_D(QExtThermometer);
    if (userValue < d->m_minValue || userValue > d->m_maxValue) {
        return;
    }

    if (d->m_userValue != userValue) {
        d->m_userValue = userValue;
        this->update();
    }
}

void QExtThermometer::setUserValue(int userValue)
{
    this->setUserValue((double)userValue);
}

void QExtThermometer::setUserValueColor(const QColor &color)
{
    Q_D(QExtThermometer);
    if (d->m_userValueColor != color) {
        d->m_userValueColor = color;
        this->update();
    }
}

void QExtThermometer::setBgColorStart(const QColor &color)
{
    Q_D(QExtThermometer);
    if (d->m_backgroundStartColor != color) {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QExtThermometer::setBgColorEnd(const QColor &color)
{
    Q_D(QExtThermometer);
    if (d->m_backgroundEndColor != color) {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QExtThermometer::setLineColor(const QColor &color)
{
    Q_D(QExtThermometer);
    if (d->m_lineColor != color) {
        d->m_lineColor = color;
        this->update();
    }
}

void QExtThermometer::setBarBackgroundColor(const QColor &color)
{
    Q_D(QExtThermometer);
    if (d->m_barBackgroundColor != color) {
        d->m_barBackgroundColor = color;
        this->update();
    }
}

void QExtThermometer::setBarColor(const QColor &color)
{
    Q_D(QExtThermometer);
    if (d->m_barColor != color) {
        d->m_barColor = color;
        this->update();
    }
}

void QExtThermometer::setBarPosition(const QExtThermometer::BarPosition &position)
{
    Q_D(QExtThermometer);
    if (d->m_barPosition != position) {
        d->m_barPosition = position;
        this->update();
    }
}

void QExtThermometer::setTickPosition(const QExtThermometer::TickPosition &position)
{
    Q_D(QExtThermometer);
    if (d->m_tickPosition != position) {
        d->m_tickPosition = position;
        this->update();
    }
}

void QExtThermometer::updateValue()
{
    Q_D(QExtThermometer);
    if (!d->m_reverse) {
        if (d->m_currentValue >= d->m_value) {
            d->m_currentValue = d->m_value;
            d->m_timer->stop();
        } else {
            d->m_currentValue += d->m_animationStep;
        }
    } else {
        if (d->m_currentValue <= d->m_value) {
            d->m_currentValue = d->m_value;
            d->m_timer->stop();
        } else {
            d->m_currentValue -= d->m_animationStep;
        }
    }

    this->update();
}
