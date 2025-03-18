/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
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

#include <private/qextScaleKnob_p.h>

#include <QMouseEvent>
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <qmath.h>

QExtScaleKnobPrivate::QExtScaleKnobPrivate(QExtScaleKnob *q)
    : q_ptr(q)
{
    m_minValue = -100.0;
    m_maxValue = 100.0;
    m_value = 0;
    m_precision = 1;

    m_scaleStep = 20;
    m_startAngle = 45;
    m_endAngle = 45;

    m_borderColor = QColor(0, 0, 0);
    m_backgroundColor = QColor(50, 50, 50);
    m_textColor = QColor(0, 0, 0);
    m_percentColor = QColor(100, 184, 255);

    m_rangeBisectionEnable = true;
    m_valueVisible = false;
    m_pointerStyle = QExtScaleKnob::PointerStyle_Line;

}

QExtScaleKnobPrivate::~QExtScaleKnobPrivate()
{

}



QExtScaleKnob::QExtScaleKnob(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtScaleKnobPrivate(this))
{
    this->setFont(QFont("Arial", 9));
}

QExtScaleKnob::~QExtScaleKnob()
{

}

void QExtScaleKnob::mousePressEvent(QMouseEvent *e)
{
    Q_D(QExtScaleKnob);
    d->m_pressed = true;
    this->setPressedValue(e->pos());
}

void QExtScaleKnob::mouseReleaseEvent(QMouseEvent *)
{
    Q_D(QExtScaleKnob);
    d->m_pressed = false;
}

void QExtScaleKnob::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QExtScaleKnob);
    if (d->m_pressed)
    {
        this->setPressedValue(e->pos());
    }
}

void QExtScaleKnob::paintEvent(QPaintEvent *)
{
    Q_D(QExtScaleKnob);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    this->drawScale(&painter);

    this->drawBackgroundCircle(&painter);
    this->drawCenterCircle(&painter);

    if (d->m_pointerStyle == PointerStyle_Line)
    {
        this->drawPointerLine(&painter);
    }
    else if (d->m_pointerStyle == PointerStyle_Indicator)
    {
        this->drawPointerIndicator(&painter);
    }
    else if (d->m_pointerStyle == PointerStyle_IndicatorR)
    {
        this->drawPointerIndicatorR(&painter);
    }
    else if (d->m_pointerStyle == PointerStyle_Triangle)
    {
        this->drawPointerTriangle(&painter);
    }

    this->drawValue(&painter);
}

void QExtScaleKnob::drawScale(QPainter *painter)
{
    Q_D(QExtScaleKnob);
    int radius = 96;
    int offset = 10;
    painter->save();

    painter->rotate(d->m_startAngle);
    double angleStep = (360.0 - d->m_startAngle - d->m_endAngle) / d->m_scaleStep;
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);

    QPen pen;
    pen.setWidthF(5.0);
    pen.setCapStyle(Qt::RoundCap);

    double rotate = 0;
    for (int i = 0; i <= d->m_scaleStep; i++)
    {
        if (d->m_rangeBisectionEnable)
        {
            bool right = i >= (d->m_scaleStep / 2);
            if (!right)
            {
                pen.setColor((rotate < degRotate) ? d->m_textColor : d->m_percentColor);
            }
            else
            {
                pen.setColor((rotate <= degRotate) ? d->m_percentColor : d->m_textColor);
            }

            if (d->m_value == d->m_minValue && !right)
            {
                pen.setColor(d->m_percentColor);
            }

            if (d->m_value <= ((d->m_maxValue - d->m_minValue) / 2 + d->m_minValue) && i == (d->m_scaleStep / 2))
            {
                pen.setColor(d->m_percentColor);
            }

            if (d->m_value == ((d->m_maxValue - d->m_minValue) / 2 + d->m_minValue))
            {
                pen.setColor(d->m_textColor);
            }
        }
        else
        {
            if (rotate <= degRotate)
            {
                pen.setColor(d->m_percentColor);
            }
            else
            {
                pen.setColor(d->m_textColor);
            }

            if (d->m_value == d->m_minValue)
            {
                pen.setColor(d->m_textColor);
            }
        }

        painter->setPen(pen);
        painter->drawLine(0, radius - offset, 0, radius);
        painter->rotate(angleStep);
        rotate += angleStep;
    }

    painter->restore();
}

void QExtScaleKnob::drawBackgroundCircle(QPainter *painter)
{
    Q_D(QExtScaleKnob);
    int radius = 75;
    painter->save();

    QPen pen;
    pen.setWidthF(5.0);
    pen.setColor(d->m_borderColor);

    painter->setPen(pen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void QExtScaleKnob::drawCenterCircle(QPainter *painter)
{
    Q_D(QExtScaleKnob);
    int radius = 15;
    painter->save();

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void QExtScaleKnob::drawPointerLine(QPainter *painter)
{
    Q_D(QExtScaleKnob);
    int radius = 62;
    painter->save();

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    painter->setPen(QPen(color, 10, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void QExtScaleKnob::drawPointerIndicator(QPainter *painter)
{
    Q_D(QExtScaleKnob);
    int radius = 65;
    int offset = 8;
    painter->save();
    painter->setOpacity(0.8);

    QPolygon pts;
    pts.setPoints(3, -offset, 0, offset, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    painter->setPen(color);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QExtScaleKnob::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(QExtScaleKnob);
    int radius = 62;
    int offset = 8;
    painter->save();
    painter->setOpacity(0.6);

    QPolygon pts;
    pts.setPoints(3, -offset, 0, offset, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    QPen pen;
    pen.setColor(color);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(offset - 1);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void QExtScaleKnob::drawPointerTriangle(QPainter *painter)
{
    Q_D(QExtScaleKnob);
    int radius = 25;
    int offset = 40;
    painter->save();

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    painter->setPen(color);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QExtScaleKnob::drawValue(QPainter *painter)
{
    Q_D(QExtScaleKnob);
    if (!d->m_valueVisible)
    {
        return;
    }

    int radius = 100;
    painter->save();

    QString strValue = QString::number(d->m_value, 'f', d->m_precision);
    painter->setPen(Qt::white);
    QFont font;

#if 0
    font.setPixelSize(radius * 0.5);
    painter->setFont(font);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, strValue);
#else
    font.setPixelSize(radius * 0.3);
    painter->setFont(font);
    QRect rect(-radius, -radius, radius * 2, radius * 1.65);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignBottom, strValue);
#endif

    painter->restore();
}

void QExtScaleKnob::setPressedValue(QPointF pressedPoint)
{
    Q_D(QExtScaleKnob);
    double length = 360 - d->m_startAngle - d->m_endAngle;

    QPointF point = pressedPoint - rect().center();
    double theta = -atan2(-point.x(), -point.y()) * 180 / M_PI;
    theta = theta + length / 2;

    double increment = (d->m_maxValue - d->m_minValue) / length;
    double currentValue = (theta * increment) + d->m_minValue;

    if (currentValue <= d->m_minValue)
    {
        currentValue = d->m_minValue;
    }
    else if (currentValue >= d->m_maxValue)
    {
        currentValue = d->m_maxValue;
    }

    this->setValue(currentValue);
}

double QExtScaleKnob::minValue() const
{
    Q_D(const QExtScaleKnob);
    return d->m_minValue;
}

double QExtScaleKnob::maxValue() const
{
    Q_D(const QExtScaleKnob);
    return d->m_maxValue;
}

double QExtScaleKnob::value() const
{
    Q_D(const QExtScaleKnob);
    return d->m_value;
}

int QExtScaleKnob::precision() const
{
    Q_D(const QExtScaleKnob);
    return d->m_precision;
}

int QExtScaleKnob::scaleStep() const
{
    Q_D(const QExtScaleKnob);
    return d->m_scaleStep;
}

int QExtScaleKnob::startAngle() const
{
    Q_D(const QExtScaleKnob);
    return d->m_startAngle;
}

int QExtScaleKnob::endAngle() const
{
    Q_D(const QExtScaleKnob);
    return d->m_endAngle;
}

QColor QExtScaleKnob::borderColor() const
{
    Q_D(const QExtScaleKnob);
    return d->m_borderColor;
}

QColor QExtScaleKnob::backgroundColor() const
{
    Q_D(const QExtScaleKnob);
    return d->m_backgroundColor;
}

QColor QExtScaleKnob::textColor() const
{
    Q_D(const QExtScaleKnob);
    return d->m_textColor;
}

QColor QExtScaleKnob::percentColor() const
{
    Q_D(const QExtScaleKnob);
    return d->m_percentColor;
}

bool QExtScaleKnob::isRangeBisectionEnable() const
{
    Q_D(const QExtScaleKnob);
    return d->m_rangeBisectionEnable;
}

bool QExtScaleKnob::isValueVisible() const
{
    Q_D(const QExtScaleKnob);
    return d->m_valueVisible;
}

QExtScaleKnob::PointerStyle QExtScaleKnob::pointerStyle() const
{
    Q_D(const QExtScaleKnob);
    return d->m_pointerStyle;
}

QSize QExtScaleKnob::sizeHint() const
{
    return QSize(200, 200);
}

QSize QExtScaleKnob::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QExtScaleKnob::setRange(double minValue, double maxValue)
{
    Q_D(QExtScaleKnob);
    if (minValue >= maxValue)
    {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    if (d->m_value < minValue || d->m_value > maxValue)
    {
        this->setValue(d->m_value);
    }

    this->update();
}

void QExtScaleKnob::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QExtScaleKnob::setMinValue(double minValue)
{
    Q_D(QExtScaleKnob);
    this->setRange(minValue, d->m_maxValue);
}

void QExtScaleKnob::setMaxValue(double maxValue)
{
    Q_D(QExtScaleKnob);
    this->setRange(d->m_minValue, maxValue);
}

void QExtScaleKnob::setValue(double value)
{
    Q_D(QExtScaleKnob);
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
    this->update();
}

void QExtScaleKnob::setValue(int value)
{
    this->setValue((double)value);
}

void QExtScaleKnob::setPrecision(int precision)
{
    Q_D(QExtScaleKnob);
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        this->update();
    }
}

void QExtScaleKnob::setScaleStep(int step)
{
    Q_D(QExtScaleKnob);
    if (d->m_scaleStep != step)
    {
        d->m_scaleStep = step;
        this->update();
    }
}

void QExtScaleKnob::setStartAngle(int angle)
{
    Q_D(QExtScaleKnob);
    if (d->m_startAngle != angle)
    {
        d->m_startAngle = angle;
        this->update();
    }
}

void QExtScaleKnob::setEndAngle(int angle)
{
    Q_D(QExtScaleKnob);
    if (d->m_endAngle != angle)
    {
        d->m_endAngle = angle;
        this->update();
    }
}

void QExtScaleKnob::setBorderColor(const QColor &color)
{
    Q_D(QExtScaleKnob);
    if (d->m_borderColor != color)
    {
        d->m_borderColor = color;
        this->update();
    }
}

void QExtScaleKnob::setBackgroundColor(const QColor &color)
{
    Q_D(QExtScaleKnob);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QExtScaleKnob::setTextColor(const QColor &color)
{
    Q_D(QExtScaleKnob);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QExtScaleKnob::setPercentColor(const QColor &color)
{
    Q_D(QExtScaleKnob);
    if (d->m_percentColor != color)
    {
        d->m_percentColor = color;
        this->update();
    }
}

void QExtScaleKnob::setRangeBisectionEnable(bool enable)
{
    Q_D(QExtScaleKnob);
    if (d->m_rangeBisectionEnable != enable)
    {
        d->m_rangeBisectionEnable = enable;
        this->update();
    }
}

void QExtScaleKnob::setValueVisible(bool visiable)
{
    Q_D(QExtScaleKnob);
    if (d->m_valueVisible != visiable)
    {
        d->m_valueVisible = visiable;
        this->update();
    }
}

void QExtScaleKnob::setPointerStyle(const QExtScaleKnob::PointerStyle &style)
{
    Q_D(QExtScaleKnob);
    if (d->m_pointerStyle != style)
    {
        d->m_pointerStyle = style;
        this->update();
    }
}
