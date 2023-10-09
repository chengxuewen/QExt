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

#include <private/qextDial_p.h>

#include <QPainter>
#include <QPointF>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <qmath.h>

QExtDialPrivate::QExtDialPrivate(QExtDial *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;
    m_precision = 0;

    m_scaleMajor = 10;
    m_scaleMinor = 5;
    m_startAngle = 45;
    m_endAngle = 45;

    m_darkColor = QColor(100, 100, 100);
    m_lightColor = QColor(250, 250, 250);
    m_textColor = QColor(0, 0, 0);

    m_valueVisible = true;
    m_pointerStyle = QExtDial::PointerStyle_Triangle;
}

QExtDialPrivate::~QExtDialPrivate()
{

}



QExtDial::QExtDial(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtDialPrivate(this))
{
    this->setFont(QFont("Arial", 9));
}

QExtDial::~QExtDial()
{

}

void QExtDial::mousePressEvent(QMouseEvent *e)
{
    Q_D(QExtDial);
    d->m_pressed = true;
    this->setPressedValue(e->pos());
}

void QExtDial::mouseReleaseEvent(QMouseEvent *)
{
    Q_D(QExtDial);
    d->m_pressed = false;
}

void QExtDial::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QExtDial);
    if (d->m_pressed)
    {
        this->setPressedValue(e->pos());
    }
}

void QExtDial::paintEvent(QPaintEvent *)
{
    Q_D(QExtDial);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    this->drawScale(&painter);
    this->drawScaleNum(&painter);
    this->drawBorderCircle(&painter);
    this->drawBackgroundCircle(&painter);

    if (d->m_pointerStyle == PointerStyle_Circle)
    {
        this->drawPointerCircle(&painter);
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

    this->drawCenterCircle(&painter);
    this->drawValue(&painter);
}

void QExtDial::drawScale(QPainter *painter)
{
    Q_D(QExtDial);
    int radius = 80;
    painter->save();

    painter->rotate(d->m_startAngle);
    int steps = (d->m_scaleMajor * d->m_scaleMinor);
    double angleStep = (360.0 - d->m_startAngle - d->m_endAngle) / steps;

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(d->m_textColor);

    for (int i = 0; i <= steps; i++)
    {
        if (i % d->m_scaleMinor == 0)
        {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius);
        }
        else
        {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius - 3);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void QExtDial::drawScaleNum(QPainter *painter)
{
    Q_D(QExtDial);
    int radius = 90;
    painter->save();
    painter->setPen(d->m_textColor);

    double startRad = (360 - d->m_startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - d->m_startAngle - d->m_endAngle) * (M_PI / 180) / d->m_scaleMajor;

    for (int i = 0; i <= d->m_scaleMajor; i++)
    {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((d->m_maxValue - d->m_minValue) / d->m_scaleMajor) + d->m_minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', d->m_precision);
        QRect strRect = fontMetrics().boundingRect(strValue);;
        double textWidth = strRect.width();
        double textHeight = strRect.height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void QExtDial::drawBorderCircle(QPainter *painter)
{
    Q_D(QExtDial);
    int radius = 70;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, d->m_darkColor);
    bgGradient.setColorAt(1.0, d->m_lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtDial::drawBackgroundCircle(QPainter *painter)
{
    Q_D(QExtDial);
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, d->m_lightColor);
    bgGradient.setColorAt(1.0, d->m_darkColor);
    painter->setBrush(bgGradient);

    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtDial::drawPointerCircle(QPainter *painter)
{
    Q_D(QExtDial);
    int radius = 15;
    int offset = 10;
    painter->save();
    painter->setPen(Qt::NoPen);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QLinearGradient bgGradient(0, 0, radius * 2, radius * 2);
    bgGradient.setColorAt(0.0, d->m_darkColor);
    bgGradient.setColorAt(1.0, d->m_lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->setPen(QPen(d->m_darkColor, 2, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, radius * 2 + offset, 0, radius * 2 + 10 + offset);

    painter->restore();
}

void QExtDial::drawPointerIndicator(QPainter *painter)
{
    Q_D(QExtDial);
    int radius = 55;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_darkColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QExtDial::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(QExtDial);
    int radius = 55;
    painter->save();
    painter->setOpacity(0.6);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(d->m_darkColor);

    painter->setPen(pen);
    painter->setBrush(d->m_darkColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //Add drawing a rounded line that overlaps with the previous triangle to form a rounded pointer
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void QExtDial::drawPointerTriangle(QPainter *painter)
{
    Q_D(QExtDial);
    int radius = 10;
    int offset = 45;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_darkColor);

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QExtDial::drawCenterCircle(QPainter *painter)
{
    Q_D(QExtDial);
    if (!d->m_valueVisible)
    {
        return;
    }

    int radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, d->m_darkColor);
    bgGradient.setColorAt(1.0, d->m_lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QExtDial::drawValue(QPainter *painter)
{
    Q_D(QExtDial);
    if (!d->m_valueVisible)
    {
        return;
    }

    int radius = 100;
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    font.setPixelSize(12);
    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)d->m_value, 0, 'f', d->m_precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}

void QExtDial::setPressedValue(QPointF point)
{
    Q_D(QExtDial);
    //Calculate total Angle
    double length = 360 - d->m_startAngle - d->m_endAngle;

    //Calculate the nearest scale
    QPointF recentPoint = point - rect().center();
    double theta = -atan2(-recentPoint.x(), -recentPoint.y()) * 180 / M_PI;
    theta = theta + length / 2;

    //Calculate how much each Angle is moving
    double increment = (d->m_maxValue - d->m_minValue) / length;
    double currentValue = (theta * increment) + d->m_minValue;

    //Filter values outside the arc
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

double QExtDial::minValue() const
{
    Q_D(const QExtDial);
    return d->m_minValue;
}

double QExtDial::maxValue() const
{
    Q_D(const QExtDial);
    return d->m_maxValue;
}

double QExtDial::value() const
{
    Q_D(const QExtDial);
    return d->m_value;
}

int QExtDial::precision() const
{
    Q_D(const QExtDial);
    return d->m_precision;
}

int QExtDial::scaleMajor() const
{
    Q_D(const QExtDial);
    return d->m_scaleMajor;
}

int QExtDial::scaleMinor() const
{
    Q_D(const QExtDial);
    return d->m_scaleMinor;
}

int QExtDial::startAngle() const
{
    Q_D(const QExtDial);
    return d->m_startAngle;
}

int QExtDial::endAngle() const
{
    Q_D(const QExtDial);
    return d->m_endAngle;
}

QColor QExtDial::darkColor() const
{
    Q_D(const QExtDial);
    return d->m_darkColor;
}

QColor QExtDial::lightColor() const
{
    Q_D(const QExtDial);
    return d->m_lightColor;
}

QColor QExtDial::textColor() const
{
    Q_D(const QExtDial);
    return d->m_textColor;
}

bool QExtDial::valueVisible() const
{
    Q_D(const QExtDial);
    return d->m_valueVisible;
}

QExtDial::PointerStyleType QExtDial::pointerStyle() const
{
    Q_D(const QExtDial);
    return d->m_pointerStyle;
}

QSize QExtDial::sizeHint() const
{
    return QSize(200, 200);
}

QSize QExtDial::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QExtDial::setRange(double minValue, double maxValue)
{
    Q_D(QExtDial);
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

void QExtDial::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QExtDial::setMinValue(double minValue)
{
    Q_D(QExtDial);
    this->setRange(minValue, d->m_maxValue);
}

void QExtDial::setMaxValue(double maxValue)
{
    Q_D(QExtDial);
    this->setRange(d->m_minValue, maxValue);
}

void QExtDial::setValue(double value)
{
    Q_D(QExtDial);
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

void QExtDial::setValue(int value)
{
    this->setValue((double)value);
}

void QExtDial::setPrecision(int precision)
{
    Q_D(QExtDial);
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        this->update();
    }
}

void QExtDial::setScaleMajor(int scaleMajor)
{
    Q_D(QExtDial);
    if (d->m_scaleMajor != scaleMajor)
    {
        d->m_scaleMajor = scaleMajor;
        this->update();
    }
}

void QExtDial::setScaleMinor(int scaleMinor)
{
    Q_D(QExtDial);
    if (d->m_scaleMinor != scaleMinor)
    {
        d->m_scaleMinor = scaleMinor;
        this->update();
    }
}

void QExtDial::setStartAngle(int angle)
{
    Q_D(QExtDial);
    if (d->m_startAngle != angle)
    {
        d->m_startAngle = angle;
        this->update();
    }
}

void QExtDial::setEndAngle(int angle)
{
    Q_D(QExtDial);
    if (d->m_endAngle != angle)
    {
        d->m_endAngle = angle;
        this->update();
    }
}

void QExtDial::setDarkColor(const QColor &color)
{
    Q_D(QExtDial);
    if (d->m_darkColor != color)
    {
        d->m_darkColor = color;
        this->update();
    }
}

void QExtDial::setLightColor(const QColor &color)
{
    Q_D(QExtDial);
    if (d->m_lightColor != color)
    {
        d->m_lightColor = color;
        this->update();
    }
}

void QExtDial::setTextColor(const QColor &color)
{
    Q_D(QExtDial);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QExtDial::setShowValue(bool visiable)
{
    Q_D(QExtDial);
    if (d->m_valueVisible != visiable)
    {
        d->m_valueVisible = visiable;
        this->update();
    }
}

void QExtDial::setPointerStyle(const QExtDial::PointerStyleType &style)
{
    Q_D(QExtDial);
    if (d->m_pointerStyle != style)
    {
        d->m_pointerStyle = style;
        this->update();
    }
}
