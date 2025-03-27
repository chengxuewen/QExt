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

#include <private/qextArrowCompass_p.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <qmath.h>

QExtArrowCompassPrivate::QExtArrowCompassPrivate(QExtArrowCompass *q)
    : q_ptr(q)
{
    m_value = 0;
    m_precision = 0;

    m_crownColorStart = QColor(125, 32, 36);
    m_crownColorEnd = QColor(227, 77, 77);

    m_backgroundStartColor = QColor(81, 97, 113);
    m_backgroundEndColor = QColor(28, 34, 40);

    m_darkColor = QColor(51, 60, 75);
    m_lightColor = QColor(109, 134, 162);

    m_foregroundColor = QColor(255, 255, 255);
    m_textColor = QColor(20, 20, 20);

    m_northPointerColor = QColor(255, 107, 107);
    m_southPointerColor = QColor(100, 184, 255);

    m_centerStartColor = QColor(230, 230, 230);
    m_centerEndColor = QColor(210, 210, 210);

    m_animationVisible = false;
    m_currentValue = 0;
}

QExtArrowCompassPrivate::~QExtArrowCompassPrivate()
{

}


QExtArrowCompass::QExtArrowCompass(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtArrowCompassPrivate(this))
{
    Q_D(QExtArrowCompass);
    d->m_animation.reset(new QPropertyAnimation(this, ""));
    d->m_animation->setDuration(500);
    d->m_animation->setEasingCurve(QEasingCurve::Linear);
    connect(d->m_animation.data(), SIGNAL(valueChanged(QVariant)), this, SLOT(updateValue(QVariant)));

    this->setFont(QFont("Arial", 9));
}

QExtArrowCompass::~QExtArrowCompass()
{

}

void QExtArrowCompass::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //Draw the preparatory work, enable anti-aliasing, shift the axis center, and scale equally
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    this->drawCrownCircle(&painter);
    this->drawBackgroundCircle(&painter);
    this->drawScale(&painter);
    this->drawScaleNum(&painter);
    this->drawCoverOuterCircle(&painter);
    this->drawCoverInnerCircle(&painter);
    this->drawCoverCenterCircle(&painter);
    this->drawPointer(&painter);
    this->drawCenterCircle(&painter);
    this->drawValue(&painter);
}

void QExtArrowCompass::drawCrownCircle(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_crownColorStart);
    lineGradient.setColorAt(1, d->m_crownColorEnd);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtArrowCompass::drawBackgroundCircle(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_backgroundStartColor);
    lineGradient.setColorAt(1, d->m_backgroundEndColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtArrowCompass::drawScale(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 85;
    painter->save();

    //There are 8 panels in total,4 for NESW letters and 4 for lines
    int steps = 8;
    double angleStep = 360.0 / steps;

    QPen pen;
    pen.setColor(d->m_foregroundColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(4);
    painter->setPen(pen);

    //Draw NESW letters for the integer part of %2 and line scales for the rest
    for (int i = 0; i <= steps; i++)
    {
        if (i % 2 != 0)
        {
            painter->drawLine(0, radius - 10, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void QExtArrowCompass::drawScaleNum(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 88;
    painter->save();
    painter->setPen(d->m_foregroundColor);

    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    painter->setFont(font);

    QRect textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, "N");
    painter->drawText(textRect, Qt::AlignBottom | Qt::AlignHCenter, "S");

    radius -= 2;
    textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, "W");

    radius -= 2;
    textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, "E");

    painter->restore();
}

void QExtArrowCompass::drawCoverOuterCircle(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 68;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_lightColor);
    lineGradient.setColorAt(1, d->m_darkColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtArrowCompass::drawCoverInnerCircle(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_darkColor);
    lineGradient.setColorAt(1, d->m_lightColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtArrowCompass::drawCoverCenterCircle(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.8);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_lightColor);
    lineGradient.setColorAt(1, d->m_darkColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtArrowCompass::drawPointer(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 75;

    QPolygon pts;

    painter->save();
    painter->setOpacity(0.7);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_northPointerColor);
    pts.setPoints(3, -10, 0, 10, 0, 0, radius);
    painter->rotate(d->m_currentValue + 180);
    painter->drawConvexPolygon(pts);
    painter->restore();

    painter->save();
    painter->setOpacity(0.7);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_southPointerColor);
    pts.setPoints(3, -10, 0, 10, 0, 0, radius);
    painter->rotate(d->m_currentValue);
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void QExtArrowCompass::drawCenterCircle(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 12;
    painter->save();
    painter->setOpacity(1.0);
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_centerStartColor);
    lineGradient.setColorAt(1, d->m_centerEndColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtArrowCompass::drawValue(QPainter *painter)
{
    Q_D(QExtArrowCompass);
    int radius = 100;
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    font.setPixelSize(11);
    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)d->m_value, 0, 'f', d->m_precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}


void QExtArrowCompass::updateValue(const QVariant &value)
{
    Q_D(QExtArrowCompass);
    const double animationValue = value.toDouble();
    if (animationValue != d->m_currentValue)
    {
        d->m_currentValue = animationValue;
        this->update();
    }
}

double QExtArrowCompass::value() const
{
    Q_D(const QExtArrowCompass);
    return d->m_value;
}

int QExtArrowCompass::precision() const
{
    Q_D(const QExtArrowCompass);
    return d->m_precision;
}

bool QExtArrowCompass::animationEnable() const
{
    Q_D(const QExtArrowCompass);
    return d->m_animationVisible;
}

int QExtArrowCompass::animationDuration() const
{
    Q_D(const QExtArrowCompass);
    return d->m_animation->duration();
}

QEasingCurve::Type QExtArrowCompass::animationEasingCurve() const
{
    Q_D(const QExtArrowCompass);
    return d->m_animation->easingCurve().type();
}

QColor QExtArrowCompass::crownStartColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_crownColorStart;
}

QColor QExtArrowCompass::crownEndColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_crownColorEnd;
}

QColor QExtArrowCompass::backgroundStartColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_backgroundStartColor;
}

QColor QExtArrowCompass::backgroundEndColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_backgroundEndColor;
}

QColor QExtArrowCompass::darkColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_darkColor;
}

QColor QExtArrowCompass::lightColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_lightColor;
}

QColor QExtArrowCompass::foregroundColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_foregroundColor;
}

QColor QExtArrowCompass::textColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_textColor;
}

QColor QExtArrowCompass::northPointerColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_northPointerColor;
}

QColor QExtArrowCompass::southPointerColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_southPointerColor;
}

QColor QExtArrowCompass::centerStartColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_centerStartColor;
}

QColor QExtArrowCompass::centerEndColor() const
{
    Q_D(const QExtArrowCompass);
    return d->m_centerEndColor;
}

QSize QExtArrowCompass::sizeHint() const
{
    return QSize(200, 200);
}

QSize QExtArrowCompass::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QExtArrowCompass::setValue(double value)
{
    Q_D(QExtArrowCompass);
    if (value == d->m_value)
    {
        return;
    }

    if (value < 0)
    {
        value = 0;
    }
    else if (value > 360)
    {
        value = 360;
    }

    d->m_value = value;
    emit this->valueChanged(value);

    if (!d->m_animationVisible)
    {
        d->m_currentValue = d->m_value;
        this->update();
    }
    else
    {
        d->m_animation->setStartValue(d->m_currentValue);
        d->m_animation->setEndValue(d->m_value);
        d->m_animation->start();
    }
}

void QExtArrowCompass::setValue(int value)
{
    this->setValue((double)value);
}

void QExtArrowCompass::setPrecision(int precision)
{
    Q_D(QExtArrowCompass);
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        this->update();
    }
}

void QExtArrowCompass::setAnimationEnable(bool enable)
{
    Q_D(QExtArrowCompass);
    if (d->m_animationVisible != enable)
    {
        d->m_animationVisible = enable;
        this->update();
    }
}

void QExtArrowCompass::setAnimationDuration(int duration)
{
    Q_D(QExtArrowCompass);
    if (duration <= 0)
    {
        qCritical() << "QExtArrowCompass::setAnimationDuration():duration must greater than 0";
        return;
    }
    if (d->m_animation->duration() != duration)
    {
        d->m_animation->setDuration(duration);
    }
}

void QExtArrowCompass::setAnimationEasingCurve(QEasingCurve::Type easingCurve)
{
    Q_D(QExtArrowCompass);
    d->m_animation->setEasingCurve(easingCurve);
}

void QExtArrowCompass::setCrownStartColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_crownColorStart != color)
    {
        d->m_crownColorStart = color;
        this->update();
    }
}

void QExtArrowCompass::setCrownEndColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_crownColorEnd != color)
    {
        d->m_crownColorEnd = color;
        this->update();
    }
}

void QExtArrowCompass::setBackgroundStartColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_backgroundStartColor != color)
    {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QExtArrowCompass::setBackgroundEndColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_backgroundEndColor != color)
    {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QExtArrowCompass::setDarkColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_darkColor != color)
    {
        d->m_darkColor = color;
        this->update();
    }
}

void QExtArrowCompass::setLightColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_lightColor != color)
    {
        d->m_lightColor = color;
        this->update();
    }
}

void QExtArrowCompass::setForegroundColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_foregroundColor != color)
    {
        d->m_foregroundColor = color;
        this->update();
    }
}

void QExtArrowCompass::setTextColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QExtArrowCompass::setNorthPointerColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_northPointerColor != color)
    {
        d->m_northPointerColor = color;
        this->update();
    }
}

void QExtArrowCompass::setSouthPointerColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_southPointerColor != color)
    {
        d->m_southPointerColor = color;
        this->update();
    }
}

void QExtArrowCompass::setCenterStartColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_centerStartColor != color)
    {
        d->m_centerStartColor = color;
        this->update();
    }
}

void QExtArrowCompass::setCenterEndColor(const QColor &color)
{
    Q_D(QExtArrowCompass);
    if (d->m_centerEndColor != color)
    {
        d->m_centerEndColor = color;
        this->update();
    }
}
