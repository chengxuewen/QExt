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

#include <private/qextProgressWait_p.h>

#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QDebug>
#include <qmath.h>

QExtProgressWaitPrivate::QExtProgressWaitPrivate(QExtProgressWait *q)
    : q_ptr(q)
{
    m_clockWise = true;
    m_showPercent = false;
    m_currentValue = 0;
    m_maxValue = 10;
    m_interval = 100;

    m_barStyle = QExtProgressWait::Style_Line;
    m_background = QColor(255, 255, 255);
    m_foreground = QColor(100, 184, 255);
    m_textColor = QColor(100, 184, 255);
}

QExtProgressWaitPrivate::~QExtProgressWaitPrivate()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}



QExtProgressWait::QExtProgressWait(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtProgressWaitPrivate(this))
{
    Q_D(QExtProgressWait);
    d->m_timer = new QTimer(this);
    d->m_timer->setInterval(d->m_interval);
    connect(d->m_timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    d->m_timer->start();

    this->resizeEvent(NULL);
    this->setFont(QFont("Arial", 8));
}

QExtProgressWait::~QExtProgressWait()
{

}

void QExtProgressWait::resizeEvent(QResizeEvent *)
{
    //    if (barStyle == BarStyle_DoubleCircle) {
    //        int radius = 200;
    //        minRadius = radius / 10;
    //        maxRadius = radius / 5;
    //        offsetRadius = radius / 30;
    //        leftRadius = minRadius;
    //        rightRadius = maxRadius;
    //        leftIncrease = true;
    //        rightIncrease = false;
    //    }
}

void QExtProgressWait::paintEvent(QPaintEvent *)
{
    Q_D(QExtProgressWait);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    if (d->m_barStyle == Style_Line) {
        this->drawLine(&painter);
    } else if (d->m_barStyle == Style_Dot) {
        this->drawDot(&painter);
    }

    this->drawValue(&painter);
}

void QExtProgressWait::drawArc(QPainter *painter)
{
    Q_D(QExtProgressWait);
    painter->save();
    painter->setPen(Qt::NoPen);

    int centerX = 0;
    int centerY = 0;
    int radius = 99;
    int radiusBig = radius / 2;
    int radiusSmall = radius / 6;
    double currentangle = d->m_currentValue * (360 / (d->m_maxValue + 1));

    if (d->m_clockWise) {
        currentangle = -currentangle;
    }

    painter->setBrush(d->m_foreground);
    QPainterPath pathBig1(QPointF(centerX + radius * qCos(degreesToRadians(currentangle)),
                                  centerY - radius * qSin(degreesToRadians(currentangle))));
    pathBig1.arcTo(centerX - radius, centerY - radius, radius * 2, radius * 2, currentangle, 180);
    pathBig1.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle + 180)) - radiusBig,
                   centerY - radiusBig * qSin(degreesToRadians(currentangle + 180)) - radiusBig,
                   radiusBig * 2, radiusBig * 2, currentangle + 180, 180);
    pathBig1.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusBig,
                   centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusBig,
                   radiusBig * 2, radiusBig * 2, currentangle + 180, -180
                   );
    painter->drawPath(pathBig1);

    painter->setBrush(d->m_background);
    QPainterPath pathBig2(QPointF(centerX + radius * qCos(degreesToRadians(currentangle)),
                                  centerY - radius * qSin(degreesToRadians(currentangle))));
    pathBig2.arcTo(centerX - radius, centerY - radius, radius * 2, radius * 2, currentangle, -180);
    pathBig2.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle + 180)) - radiusBig,
                   centerY - radiusBig * qSin(degreesToRadians(currentangle + 180)) - radiusBig,
                   radiusBig * 2, radiusBig * 2, currentangle + 180, 180);
    pathBig2.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusBig,
                   centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusBig,
                   radiusBig * 2, radiusBig * 2, currentangle + 180, -180
                   );
    painter->drawPath(pathBig2);

    painter->setBrush(d->m_foreground);
    QPainterPath pathSmall1;
    pathSmall1.addEllipse(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusSmall,
                          centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusSmall,
                          radiusSmall * 2, radiusSmall * 2);
    painter->drawPath(pathSmall1);

    painter->setBrush(d->m_background);
    QPainterPath pathSmall2;
    pathSmall2.addEllipse(centerX + radiusBig * qCos(degreesToRadians(180 + currentangle)) - radiusSmall,
                          centerY - radiusBig * qSin(degreesToRadians(180 + currentangle)) - radiusSmall,
                          radiusSmall * 2, radiusSmall * 2);
    painter->drawPath(pathSmall2);

    painter->restore();
}

void QExtProgressWait::drawDot(QPainter *painter)
{
    Q_D(QExtProgressWait);
    painter->save();
    painter->setPen(Qt::NoPen);

    int radius = 99;
    int minRadius = radius / 6;
    double angleStep = 360.0 / d->m_maxValue;
    double alpha = (double)1 / d->m_maxValue;

    if (!d->m_clockWise) {
        angleStep = -angleStep;
    }

    int centerX = 0;
    int centerY = 0;
    double centerRadius = radius / 1.2;

    for (int i = 0; i < d->m_maxValue; i++) {
        double angle = (d->m_currentValue + i) * angleStep;
        double initX = centerRadius * qCos(degreesToRadians(angle)) + centerX;
        double initY = centerRadius * qSin(degreesToRadians(angle)) + centerY;

        int value = i * alpha * 255;
        value = value < 30 ? 30 : value;

        d->m_foreground.setAlpha(value);
        painter->setBrush(d->m_foreground);
        painter->drawEllipse(initX - minRadius, initY - minRadius, minRadius * 2, minRadius * 2);
    }

    painter->restore();
}

void QExtProgressWait::drawPie(QPainter *painter)
{
    Q_D(QExtProgressWait);
    int radius = 99;
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    int startAngle = (360 / (d->m_maxValue + 1)) * d->m_currentValue * 16;

    int spanAngle = 60 * 16;

    painter->setBrush(d->m_foreground);

    if (d->m_clockWise) {
        startAngle = -startAngle;
    }

    painter->drawPie(-radius, -radius, radius * 2, radius * 2, startAngle, spanAngle);

    painter->restore();
}

void QExtProgressWait::drawLine(QPainter *painter)
{
    Q_D(QExtProgressWait);
    int radius = 95;

    int initY = 50;

    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidth(10);
    pen.setCapStyle(Qt::RoundCap);

    double angleStep = 360.0 / d->m_maxValue;
    double alpha = (double)1 / d->m_maxValue;

    if (!d->m_clockWise) {
        angleStep = -angleStep;
    }

    for (int i = 0; i <= d->m_maxValue; i++) {
        int value = (d->m_currentValue - i) * alpha * 255;
        if (value < 0) {
            value = value + 255;
        }

        value = value < 30 ? 30 : value;

        d->m_foreground.setAlpha(value);
        pen.setColor(d->m_foreground);
        painter->setPen(pen);
        painter->drawLine(0, initY, 0, radius);
        painter->rotate(angleStep);
    }

    painter->restore();
}

void QExtProgressWait::drawRing(QPainter *painter)
{
    Q_D(QExtProgressWait);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);
    int arcHeight = 30;
    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));

    int startAngle = (360 / (d->m_maxValue + 1)) * d->m_currentValue;

    int spanAngle = 90;
    QPainterPath currentPath;

    if (d->m_clockWise) {
        currentPath.arcTo(rect, -startAngle, spanAngle);
    } else {
        currentPath.arcTo(rect, startAngle, spanAngle);
    }

    if (d->m_clockWise) {
        startAngle = startAngle - spanAngle;
    } else {
        startAngle = startAngle + spanAngle;
    }

    spanAngle = 360 - spanAngle;
    QPainterPath otherPath;

    if (d->m_clockWise) {
        otherPath.arcTo(rect, -startAngle, spanAngle);
    } else {
        otherPath.arcTo(rect, startAngle, spanAngle);
    }

    painter->setBrush(d->m_foreground);
    painter->drawPath(currentPath - subPath);
    painter->setBrush(d->m_background);
    painter->drawPath(otherPath - subPath);

    painter->restore();
}

void QExtProgressWait::drawSingleCircle(QPainter *painter)
{
    Q_D(QExtProgressWait);
    int radius = d->m_currentValue * 10;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_foreground);
    painter->drawEllipse(QPoint(0, 0), radius, radius);
    painter->restore();
}

void QExtProgressWait::drawDoubleCircle(QPainter *painter)
{
    Q_D(QExtProgressWait);
    if (d->m_leftRadius <= d->m_minRadius) {
        d->m_leftIncrease = true;
    } else if (d->m_leftRadius >= d->m_maxRadius) {
        d->m_leftIncrease = false;
    }

    if (d->m_rightRadius <= d->m_minRadius) {
        d->m_rightIncrease = true;
    } else if (d->m_rightRadius >= d->m_maxRadius) {
        d->m_rightIncrease = false;
    }

    if (d->m_leftIncrease) {
        d->m_leftRadius += d->m_offsetRadius;
    } else {
        d->m_leftRadius -= d->m_offsetRadius;
    }

    if (d->m_rightIncrease) {
        d->m_rightRadius += d->m_offsetRadius;
    } else {
        d->m_rightRadius -= d->m_offsetRadius;
    }

    int radius = 50;

    painter->save();
    painter->setPen(Qt::NoPen);

    painter->setBrush(d->m_foreground);
    painter->drawEllipse(QPointF(-radius, 0), d->m_leftRadius, d->m_leftRadius);

    painter->setBrush(d->m_background);
    painter->drawEllipse(QPointF(radius, 0), d->m_rightRadius, d->m_rightRadius);

    painter->restore();
}

void QExtProgressWait::drawValue(QPainter *painter)
{
    Q_D(QExtProgressWait);
    if (!d->m_showPercent) {
        return;
    }

    int radius = 100;
    painter->save();
    QFont font;
    font.setPixelSize(40);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(d->m_textColor);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignCenter, QString("%1%").arg(d->m_currentValue * (100 / d->m_maxValue)));
    painter->restore();
}

double QExtProgressWait::degreesToRadians(double degrees)
{
    return degrees * (M_PI / 180);
}

void QExtProgressWait::updateValue()
{
    Q_D(QExtProgressWait);
    if (d->m_currentValue < d->m_maxValue) {
        d->m_currentValue++;
    } else {
        d->m_currentValue = 0;
    }

    this->update();
}

bool QExtProgressWait::clockWise() const
{
    Q_D(const QExtProgressWait);
    return d->m_clockWise;
}

bool QExtProgressWait::showPercent() const
{
    Q_D(const QExtProgressWait);
    return d->m_showPercent;
}

int QExtProgressWait::currentValue() const
{
    Q_D(const QExtProgressWait);
    return d->m_currentValue;
}

int QExtProgressWait::maxValue() const
{
    Q_D(const QExtProgressWait);
    return d->m_maxValue;
}

int QExtProgressWait::interval() const
{
    Q_D(const QExtProgressWait);
    return d->m_interval;
}

QExtProgressWait::Style QExtProgressWait::barStyle() const
{
    Q_D(const QExtProgressWait);
    return d->m_barStyle;
}

QColor QExtProgressWait::backgroundColor() const
{
    Q_D(const QExtProgressWait);
    return d->m_background;
}

QColor QExtProgressWait::foregroundColor() const
{
    Q_D(const QExtProgressWait);
    return d->m_foreground;
}

QColor QExtProgressWait::textColor() const
{
    Q_D(const QExtProgressWait);
    return d->m_textColor;
}

QSize QExtProgressWait::sizeHint() const
{
    return QSize(100, 100);
}

QSize QExtProgressWait::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QExtProgressWait::setClockWise(bool clockWise)
{
    Q_D(QExtProgressWait);
    if (d->m_clockWise != clockWise) {
        d->m_clockWise = clockWise;
        this->update();
    }
}

void QExtProgressWait::setShowPercent(bool showPercent)
{
    Q_D(QExtProgressWait);
    if (d->m_showPercent != showPercent) {
        d->m_showPercent = showPercent;
        this->update();
    }
}

void QExtProgressWait::setCurrentValue(int currentValue)
{
    Q_D(QExtProgressWait);
    if (d->m_currentValue != currentValue) {
        d->m_currentValue = currentValue;
        this->update();
    }
}

void QExtProgressWait::setMaxValue(int maxValue)
{
    Q_D(QExtProgressWait);
    if (d->m_maxValue != maxValue) {
        d->m_maxValue = maxValue;
        d->m_currentValue = 0;
        this->update();
    }
}

void QExtProgressWait::setInterval(int interval)
{
    Q_D(QExtProgressWait);
    if (d->m_interval != interval) {
        d->m_interval = interval;
        d->m_timer->setInterval(interval);
        this->update();
    }
}

void QExtProgressWait::setBarStyle(const QExtProgressWait::Style &barStyle)
{
    Q_D(QExtProgressWait);
    if (d->m_barStyle != barStyle) {
        d->m_barStyle = barStyle;
        this->update();
    }
}

void QExtProgressWait::setBackgroundColor(const QColor &color)
{
    Q_D(QExtProgressWait);
    if (d->m_background != color) {
        d->m_background = color;
        this->update();
    }
}

void QExtProgressWait::setForegroundColor(const QColor &color)
{
    Q_D(QExtProgressWait);
    if (d->m_foreground != color) {
        d->m_foreground = color;
        this->update();
    }
}

void QExtProgressWait::setTextColor(const QColor &color)
{
    Q_D(QExtProgressWait);
    if (d->m_textColor != color) {
        d->m_textColor = color;
        this->update();
    }
}
