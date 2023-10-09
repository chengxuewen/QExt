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

#include <private/qextProgressRing_p.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <qmath.h>

QExtProgressRingPrivate::QExtProgressRingPrivate(QExtProgressRing *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;
    m_precision = 0;
    m_text = "";

    m_clockWise = true;
    m_showPercent = false;
    m_alarmMode = 0;
    m_startAngle = 90;
    m_ringPadding = 3;
    m_ringWidth = 15;

    m_backgroundColor = QColor(250, 250, 250);
    m_circleColor = QColor(240, 240, 240);
    m_ringColor = QColor(23, 160, 134);
    m_ringBackgroundColor = QColor(250, 250, 250);
    m_textColor = QColor(50, 50, 50);

    m_ringValue1 = 10;
    m_ringValue2 = 30;
    m_ringValue3 = 70;

    m_ringColor1 = QColor(24, 189, 155);
    m_ringColor2 = QColor(255, 192, 0);
    m_ringColor3 = QColor(255, 107, 107);

    m_animationEnable = false;
    m_currentValue = 0;
}

QExtProgressRingPrivate::~QExtProgressRingPrivate()
{

}




QExtProgressRing::QExtProgressRing(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtProgressRingPrivate(this))
{
    Q_D(QExtProgressRing);
    d->m_animation = new QPropertyAnimation(this);
    d->m_animation->setDuration(500);
    connect(d->m_animation, SIGNAL(valueChanged(QVariant)), this, SLOT(updateValue(QVariant)));
    this->setFont(QFont("Arial", 8));
}

QExtProgressRing::~QExtProgressRing()
{

}

void QExtProgressRing::paintEvent(QPaintEvent *)
{
    Q_D(QExtProgressRing);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    this->drawBackground(&painter);

    this->drawRing(&painter);

    if (d->m_ringPadding > 0)
    {
        this->drawPadding(&painter);
    }

    this->drawCircle(&painter);
    this->drawValue(&painter);
}

void QExtProgressRing::drawBackground(QPainter *painter)
{
    Q_D(QExtProgressRing);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_ringPadding == 0 ? d->m_ringBackgroundColor : d->m_backgroundColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtProgressRing::drawRing(QPainter *painter)
{
    Q_D(QExtProgressRing);
    int radius = 99 - d->m_ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_ringColor);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    double angleAll = 360.0;
    double angleCurrent = angleAll * ((d->m_currentValue - d->m_minValue) / (d->m_maxValue - d->m_minValue));
    double angleOther = angleAll - angleCurrent;

    if (!d->m_clockWise)
    {
        angleCurrent = -angleCurrent;
        angleOther = -angleOther;
    }

    QColor color = d->m_ringColor;
    if (d->m_alarmMode == 1)
    {
        if (d->m_currentValue >= d->m_ringValue3)
        {
            color = d->m_ringColor3;
        }
        else if (d->m_currentValue >= d->m_ringValue2)
        {
            color = d->m_ringColor2;
        }
        else
        {
            color = d->m_ringColor1;
        }
    }
    else if (d->m_alarmMode == 2)
    {
        if (d->m_currentValue <= d->m_ringValue1)
        {
            color = d->m_ringColor1;
        }
        else if (d->m_currentValue <= d->m_ringValue2)
        {
            color = d->m_ringColor2;
        }
        else
        {
            color = d->m_ringColor3;
        }
    }

    painter->setBrush(color);
    painter->drawPie(rect, (d->m_startAngle - angleCurrent) * 16, angleCurrent * 16);

    painter->setBrush(d->m_ringBackgroundColor);
    painter->drawPie(rect, (d->m_startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void QExtProgressRing::drawPadding(QPainter *painter)
{
    Q_D(QExtProgressRing);
    int radius = 99 - d->m_ringWidth - d->m_ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtProgressRing::drawCircle(QPainter *painter)
{
    Q_D(QExtProgressRing);
    int radius = 99 - d->m_ringWidth - (d->m_ringPadding * 2);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtProgressRing::drawValue(QPainter *painter)
{
    Q_D(QExtProgressRing);
    int radius = 99 - d->m_ringWidth - (d->m_ringPadding * 2);
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    int fontSize = radius - (d->m_showPercent ? 20 : 6);
    font.setPixelSize(fontSize);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue;
    if (d->m_showPercent)
    {
        double percent = (d->m_currentValue * 100) / (d->m_maxValue - d->m_minValue);
        strValue = QString("%1%").arg(percent, 0, 'f', d->m_precision);
    }
    else
    {
        strValue = QString("%1").arg(d->m_currentValue, 0, 'f', d->m_precision);
    }

    strValue = d->m_text.isEmpty() ? strValue : d->m_text;
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void QExtProgressRing::updateValue(const QVariant &value)
{
    Q_D(QExtProgressRing);
    const double animationValue = value.toDouble();
    if (animationValue != d->m_currentValue)
    {
        d->m_currentValue = animationValue;
        this->update();
    }
}

double QExtProgressRing::minValue() const
{
    Q_D(const QExtProgressRing);
    return d->m_minValue;
}

double QExtProgressRing::maxValue() const
{
    Q_D(const QExtProgressRing);
    return d->m_maxValue;
}

double QExtProgressRing::getValue() const
{
    Q_D(const QExtProgressRing);
    return d->m_value;
}

int QExtProgressRing::precision() const
{
    Q_D(const QExtProgressRing);
    return d->m_precision;
}

QString QExtProgressRing::text() const
{
    Q_D(const QExtProgressRing);
    return d->m_text;
}

bool QExtProgressRing::clipCenter() const
{
    Q_D(const QExtProgressRing);
    return d->m_clipCenter;
}

bool QExtProgressRing::clockWise() const
{
    Q_D(const QExtProgressRing);
    return d->m_clockWise;
}

bool QExtProgressRing::percentVisible() const
{
    Q_D(const QExtProgressRing);
    return d->m_showPercent;
}

int QExtProgressRing::alarmMode() const
{
    Q_D(const QExtProgressRing);
    return d->m_alarmMode;
}

int QExtProgressRing::startAngle() const
{
    Q_D(const QExtProgressRing);
    return d->m_startAngle;
}

int QExtProgressRing::ringPadding() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringPadding;
}

int QExtProgressRing::ringWidth() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringWidth;
}

bool QExtProgressRing::animationEnable() const
{
    Q_D(const QExtProgressRing);
    return d->m_animationEnable;
}

int QExtProgressRing::animationDuration() const
{
    Q_D(const QExtProgressRing);
    return d->m_animation->duration();
}

QEasingCurve::Type QExtProgressRing::animationEasingCurve() const
{
    Q_D(const QExtProgressRing);
    return d->m_animation->easingCurve().type();
}

QColor QExtProgressRing::backgroundColor() const
{
    Q_D(const QExtProgressRing);
    return d->m_backgroundColor;
}

QColor QExtProgressRing::textColor() const
{
    Q_D(const QExtProgressRing);
    return d->m_textColor;
}

QColor QExtProgressRing::ringColor() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringColor;
}

QColor QExtProgressRing::ringBackgroundColor() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringBackgroundColor;
}

QColor QExtProgressRing::circleColor() const
{
    Q_D(const QExtProgressRing);
    return d->m_circleColor;
}

int QExtProgressRing::ringValue1() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringValue1;
}

int QExtProgressRing::ringValue2() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringValue2;
}

int QExtProgressRing::ringValue3() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringValue3;
}

QColor QExtProgressRing::ringColor1() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringColor1;
}

QColor QExtProgressRing::ringColor2() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringColor2;
}

QColor QExtProgressRing::ringColor3() const
{
    Q_D(const QExtProgressRing);
    return d->m_ringColor3;
}

QSize QExtProgressRing::sizeHint() const
{
    return QSize(200, 200);
}

QSize QExtProgressRing::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QExtProgressRing::setRange(double minValue, double maxValue)
{
    Q_D(QExtProgressRing);
    if (minValue >= maxValue)
    {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    if (d->m_value < minValue || d->m_value > maxValue)
    {
        setValue(d->m_value);
    }

    this->update();
}

void QExtProgressRing::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QExtProgressRing::setMinValue(double minValue)
{
    Q_D(QExtProgressRing);
    this->setRange(minValue, d->m_maxValue);
}

void QExtProgressRing::setMaxValue(double maxValue)
{
    Q_D(QExtProgressRing);
    this->setRange(d->m_minValue, maxValue);
}

void QExtProgressRing::setValue(double value)
{
    Q_D(QExtProgressRing);
    if (value == d->m_value)
    {
        return;
    }

    if (value < d->m_minValue)
    {
        value = d->m_minValue;
    }
    else if (value > d->m_maxValue)
    {
        value = d->m_maxValue;
    }

    d->m_value = value;
    emit this->valueChanged(value);

    if (!d->m_animationEnable)
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

void QExtProgressRing::setValue(int value)
{
    this->setValue((double)value);
}

void QExtProgressRing::setPrecision(int precision)
{
    Q_D(QExtProgressRing);
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        this->update();
    }
}

void QExtProgressRing::setText(const QString &text)
{
    Q_D(QExtProgressRing);
    if (d->m_text != text)
    {
        d->m_text = text;
        this->update();
    }
}

void QExtProgressRing::setClipCenter(bool clipCenter)
{
    Q_D(QExtProgressRing);
    if (d->m_clipCenter != clipCenter)
    {
        d->m_clipCenter = clipCenter;
        this->update();
    }
}

void QExtProgressRing::setClockWise(bool clockWise)
{
    Q_D(QExtProgressRing);
    if (d->m_clockWise != clockWise)
    {
        d->m_clockWise = clockWise;
        this->update();
    }
}

void QExtProgressRing::setPercentVisible(bool visiable)
{
    Q_D(QExtProgressRing);
    if (d->m_showPercent != visiable)
    {
        d->m_showPercent = visiable;
        this->update();
    }
}

void QExtProgressRing::setAlarmMode(int alarmMode)
{
    Q_D(QExtProgressRing);
    if (d->m_alarmMode != alarmMode)
    {
        d->m_alarmMode = alarmMode;
        this->update();
    }
}

void QExtProgressRing::setStartAngle(int startAngle)
{
    Q_D(QExtProgressRing);
    if (d->m_startAngle != startAngle)
    {
        d->m_startAngle = startAngle;
        this->update();
    }
}

void QExtProgressRing::setRingPadding(int padding)
{
    Q_D(QExtProgressRing);
    if (d->m_ringPadding != padding)
    {
        d->m_ringPadding = padding;
        this->update();
    }
}

void QExtProgressRing::setRingWidth(int width)
{
    Q_D(QExtProgressRing);
    if (d->m_ringWidth != width)
    {
        d->m_ringWidth = width;
        this->update();
    }
}

void QExtProgressRing::setAnimationEnable(bool enable)
{
    Q_D(QExtProgressRing);
    if (d->m_animationEnable != enable)
    {
        d->m_animationEnable = enable;
        this->update();
    }
}

void QExtProgressRing::setAnimationDuration(int duration)
{
    Q_D(QExtProgressRing);
    if (d->m_animation->duration() != duration)
    {
        d->m_animation->setDuration(duration);
        this->update();
    }
}

void QExtProgressRing::setAnimationEasingCurve(QEasingCurve::Type easingCurve)
{
    Q_D(QExtProgressRing);
    d->m_animation->setEasingCurve(easingCurve);
}

void QExtProgressRing::setBackgroundColor(const QColor &color)
{
    Q_D(QExtProgressRing);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QExtProgressRing::setTextColor(const QColor &color)
{
    Q_D(QExtProgressRing);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QExtProgressRing::setRingColor(const QColor &color)
{
    Q_D(QExtProgressRing);
    if (d->m_ringColor != color)
    {
        d->m_ringColor = color;
        this->update();
    }
}

void QExtProgressRing::setRingBgColor(const QColor &color)
{
    Q_D(QExtProgressRing);
    if (d->m_ringBackgroundColor != color)
    {
        d->m_ringBackgroundColor = color;
        this->update();
    }
}

void QExtProgressRing::setCircleColor(const QColor &color)
{
    Q_D(QExtProgressRing);
    if (d->m_circleColor != color)
    {
        d->m_circleColor = color;
        this->update();
    }
}

void QExtProgressRing::setRingValue1(int value)
{
    Q_D(QExtProgressRing);
    if (d->m_ringValue1 != value)
    {
        d->m_ringValue1 = value;
        this->update();
    }
}

void QExtProgressRing::setRingValue2(int value)
{
    Q_D(QExtProgressRing);
    if (d->m_ringValue2 != value)
    {
        d->m_ringValue2 = value;
        this->update();
    }
}

void QExtProgressRing::setRingValue3(int value)
{
    Q_D(QExtProgressRing);
    if (d->m_ringValue3 != value)
    {
        d->m_ringValue3 = value;
        this->update();
    }
}

void QExtProgressRing::setRingColor1(const QColor &color)
{
    Q_D(QExtProgressRing);
    if (d->m_ringColor1 != color)
    {
        d->m_ringColor1 = color;
        this->update();
    }
}

void QExtProgressRing::setRingColor2(const QColor &color)
{
    Q_D(QExtProgressRing);
    if (d->m_ringColor2 != color)
    {
        d->m_ringColor2 = color;
        this->update();
    }
}

void QExtProgressRing::setRingColor3(const QColor &color)
{
    Q_D(QExtProgressRing);
    if (d->m_ringColor3 != color)
    {
        d->m_ringColor3 = color;
        this->update();
    }
}
