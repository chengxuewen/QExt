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

#include <private/qextSemicircleGauge_p.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QPainterPath>
#include <qmath.h>

QExtSemicircleGaugePrivate::QExtSemicircleGaugePrivate(QExtSemicircleGauge *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;

    m_scaleMajor = 10;
    m_scaleMinor = 5;
    m_startAngle = 0;
    m_endAngle = 0;

    m_usedColor = QColor(100, 184, 255);
    m_freeColor = QColor(100, 100, 100);

    m_scaleColor = QColor(50, 50, 50);
    m_pointerColor = QColor(255, 107, 107);
    m_textColor = QColor(250, 250, 250);
    m_titleColor = QColor(50, 50, 50);

    m_overlayVisible = false;
    m_overlayColor = QColor(70, 70, 70, 60);

    m_pointerStyle = QExtSemicircleGauge::PointerStyle_Triangle;

    m_offsetY = 17;
    m_radiusY = 20;

    m_currentValue = 0;
    m_animationVisible = false;
}

QExtSemicircleGaugePrivate::~QExtSemicircleGaugePrivate()
{

}




QExtSemicircleGauge::QExtSemicircleGauge(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtSemicircleGaugePrivate(this))
{
    Q_D(QExtSemicircleGauge);
    d->m_animation = new QPropertyAnimation(this);
    d->m_animation->setDuration(500);
    d->m_animation->setEasingCurve(QEasingCurve::Linear);
    connect(d->m_animation, SIGNAL(valueChanged(QVariant)), this, SLOT(updateValue(QVariant)));

    this->setFont(QFont("Arial", 8));
}

QExtSemicircleGauge::~QExtSemicircleGauge()
{
}

void QExtSemicircleGauge::paintEvent(QPaintEvent *)
{
    Q_D(QExtSemicircleGauge);
    int width = this->width();
    int height = this->height();

    int side = qMax(width, height) / 2;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2.0, height / 1.0);
    painter.scale(side / 100.0, side / 100.0);

    this->drawArc(&painter);

    this->drawScale(&painter);
    this->drawScaleNum(&painter);

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

    this->drawRoundCircle(&painter);
    this->drawCenterCircle(&painter);
    this->drawValue(&painter);
    this->drawOverlay(&painter);
}

void QExtSemicircleGauge::drawArc(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 99;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    int penWidth = 10;
    QRectF rect(-radius + penWidth / 2, -radius + penWidth / 2, radius * 2 - penWidth, radius * 2 - penWidth);
    QPen pen(d->m_usedColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    double angleAll = 180.0 - d->m_startAngle - d->m_endAngle;
    double angleCurrent = angleAll * ((d->m_currentValue - d->m_minValue) / (d->m_maxValue - d->m_minValue));
    double angleOther = angleAll - angleCurrent;

    painter->setPen(pen);
    painter->drawArc(rect, (180 - d->m_startAngle - angleCurrent) * 16, angleCurrent * 16);

    pen.setColor(d->m_freeColor);
    painter->setPen(pen);
    painter->drawArc(rect, (180 - d->m_startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void QExtSemicircleGauge::drawScale(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 67;
    painter->save();

    painter->rotate(d->m_startAngle + 90);
    int steps = (d->m_scaleMajor * d->m_scaleMinor);
    double angleStep = (180.0 - d->m_startAngle - d->m_endAngle) / steps;

    QPen pen;
    pen.setColor(d->m_scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++)
    {
        if (i % d->m_scaleMinor == 0)
        {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        }
        else
        {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void QExtSemicircleGauge::drawScaleNum(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 76;
    painter->save();
    painter->setPen(d->m_scaleColor);

    double startRad = (180 - d->m_startAngle) * (M_PI / 180);
    double deltaRad = (180 - d->m_startAngle - d->m_endAngle) * (M_PI / 180) / d->m_scaleMajor;

    for (int i = 0; i <= d->m_scaleMajor; i++)
    {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((d->m_maxValue - d->m_minValue) / d->m_scaleMajor) + d->m_minValue;

        QString strValue = QString("%1").arg(value);
        QRect strRect = this->fontMetrics().boundingRect(strValue);
        double textWidth = strRect.width();
        double textHeight = strRect.height() - d->m_offsetY;
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void QExtSemicircleGauge::drawPointerCircle(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 8;
    int offset = 32;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);

    painter->rotate(d->m_startAngle + 90);
    double degRotate = (180.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_currentValue - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void QExtSemicircleGauge::drawPointerIndicator(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 85;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, d->m_radiusY, 5, d->m_radiusY, 0, radius);

    painter->rotate(d->m_startAngle + 90);
    double degRotate = (180.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_currentValue - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QExtSemicircleGauge::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 85;
    painter->save();
    painter->setOpacity(0.6);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(d->m_pointerColor);
    painter->setPen(pen);
    painter->setBrush(d->m_pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, d->m_radiusY, 5, d->m_radiusY, 0, radius);

    painter->rotate(d->m_startAngle + 90);
    double degRotate = (180.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_currentValue - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void QExtSemicircleGauge::drawPointerTriangle(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 10;
    int offset = 45;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0 + offset, 5, 0 + offset, 0, radius + offset);

    painter->rotate(d->m_startAngle + 90);
    double degRotate = (180.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_currentValue - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QExtSemicircleGauge::drawRoundCircle(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 18;
    painter->save();
    painter->setOpacity(0.6);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);
    painter->drawEllipse(-radius, -radius - d->m_radiusY, radius * 2, radius * 2);
    painter->restore();
}

void QExtSemicircleGauge::drawCenterCircle(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 13;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);
    painter->drawEllipse(-radius, -radius - d->m_radiusY, radius * 2, radius * 2);
    painter->restore();
}

void QExtSemicircleGauge::drawValue(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    int radius = 100;
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    font.setPixelSize(12);
    painter->setFont(font);

    QRectF textRect(-radius, -radius - d->m_radiusY, radius * 2, radius * 2);
    QString strValue = QString::number(d->m_currentValue, 'f', 0);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void QExtSemicircleGauge::drawOverlay(QPainter *painter)
{
    Q_D(QExtSemicircleGauge);
    if (!d->m_overlayVisible)
    {
        return;
    }

    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    d->m_overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, d->m_overlayColor);
    d->m_overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, d->m_overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

void QExtSemicircleGauge::updateValue(const QVariant &value)
{
    Q_D(QExtSemicircleGauge);
    const double animationValue = value.toDouble();
    if (animationValue != d->m_currentValue)
    {
        d->m_currentValue = animationValue;
    }
    this->update();
}

double QExtSemicircleGauge::minValue() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_minValue;
}

double QExtSemicircleGauge::maxValue() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_maxValue;
}

double QExtSemicircleGauge::value() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_value;
}

int QExtSemicircleGauge::scaleMajor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_scaleMajor;
}

int QExtSemicircleGauge::scaleMinor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_scaleMinor;
}

int QExtSemicircleGauge::startAngle() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_startAngle;
}

int QExtSemicircleGauge::endAngle() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_endAngle;
}

bool QExtSemicircleGauge::animationEnable() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_animationVisible;
}

int QExtSemicircleGauge::animationDuration() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_animation->duration();
}

QEasingCurve::Type QExtSemicircleGauge::animationEasingCurve() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_animation->easingCurve().type();
}

QColor QExtSemicircleGauge::usedColor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_usedColor;
}

QColor QExtSemicircleGauge::freeColor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_freeColor;
}

QColor QExtSemicircleGauge::scaleColor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_scaleColor;
}

QColor QExtSemicircleGauge::pointerColor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_pointerColor;
}

QColor QExtSemicircleGauge::textColor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_textColor;
}

QColor QExtSemicircleGauge::titleColor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_titleColor;
}

bool QExtSemicircleGauge::overlayVisible() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_overlayVisible;
}

QColor QExtSemicircleGauge::overlayColor() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_overlayColor;
}

QExtSemicircleGauge::PointerStyleType QExtSemicircleGauge::pointerStyle() const
{
    Q_D(const QExtSemicircleGauge);
    return d->m_pointerStyle;
}

QSize QExtSemicircleGauge::sizeHint() const
{
    return QSize(200, 100);
}

QSize QExtSemicircleGauge::minimumSizeHint() const
{
    return QSize(50, 25);
}

void QExtSemicircleGauge::setRange(double minValue, double maxValue)
{
    Q_D(QExtSemicircleGauge);
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

void QExtSemicircleGauge::setMinValue(double minValue)
{
    Q_D(QExtSemicircleGauge);
    this->setRange(minValue, d->m_maxValue);
}

void QExtSemicircleGauge::setMaxValue(double maxValue)
{
    Q_D(QExtSemicircleGauge);
    this->setRange(d->m_minValue, maxValue);
}

void QExtSemicircleGauge::setValue(double value)
{
    Q_D(QExtSemicircleGauge);
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

void QExtSemicircleGauge::setValue(int value)
{
    this->setValue((double)value);
}

void QExtSemicircleGauge::setScaleMajor(int scaleMajor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_scaleMajor != scaleMajor)
    {
        d->m_scaleMajor = scaleMajor;
        this->update();
    }
}

void QExtSemicircleGauge::setScaleMinor(int scaleMinor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_scaleMinor != scaleMinor)
    {
        d->m_scaleMinor = scaleMinor;
        this->update();
    }
}

void QExtSemicircleGauge::setStartAngle(int startAngle)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_startAngle != startAngle)
    {
        d->m_startAngle = startAngle;
        this->update();
    }
}

void QExtSemicircleGauge::setEndAngle(int endAngle)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_endAngle != endAngle)
    {
        d->m_endAngle = endAngle;
        this->update();
    }
}

void QExtSemicircleGauge::setAnimationEnable(bool enable)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_animationVisible != enable)
    {
        d->m_animationVisible = enable;
        this->update();
    }
}

void QExtSemicircleGauge::setAnimationDuration(int duration)
{
    Q_D(QExtSemicircleGauge);
    if (duration <= 0)
    {
        qCritical() << "QExtSemicircleGauge::setAnimationDuration():duration must greater than 0";
        return;
    }
    if (d->m_animation->duration() != duration)
    {
        d->m_animation->setDuration(duration);
        this->update();
    }
}

void QExtSemicircleGauge::setAnimationEasingCurve(QEasingCurve::Type easingCurve)
{
    Q_D(QExtSemicircleGauge);
    d->m_animation->setEasingCurve(easingCurve);
}

void QExtSemicircleGauge::setUsedColor(const QColor &usedColor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_usedColor != usedColor)
    {
        d->m_usedColor = usedColor;
        this->update();
    }
}

void QExtSemicircleGauge::setFreeColor(const QColor &freeColor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_freeColor != freeColor)
    {
        d->m_freeColor = freeColor;
        this->update();
    }
}

void QExtSemicircleGauge::setScaleColor(const QColor &scaleColor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_scaleColor != scaleColor)
    {
        d->m_scaleColor = scaleColor;
        this->update();
    }
}

void QExtSemicircleGauge::setPointerColor(const QColor &pointerColor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_pointerColor != pointerColor)
    {
        d->m_pointerColor = pointerColor;
        this->update();
    }
}

void QExtSemicircleGauge::setTextColor(const QColor &textColor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_textColor != textColor)
    {
        d->m_textColor = textColor;
        this->update();
    }
}

void QExtSemicircleGauge::setTitleColor(const QColor &titleColor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_titleColor != titleColor)
    {
        d->m_titleColor = titleColor;
        this->update();
    }
}

void QExtSemicircleGauge::setOverlayVisible(bool visiable)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_overlayVisible != visiable)
    {
        d->m_overlayVisible = visiable;
        this->update();
    }
}

void QExtSemicircleGauge::setOverlayColor(const QColor &overlayColor)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_overlayColor != overlayColor)
    {
        d->m_overlayColor = overlayColor;
        this->update();
    }
}

void QExtSemicircleGauge::setPointerStyle(const QExtSemicircleGauge::PointerStyleType &pointerStyle)
{
    Q_D(QExtSemicircleGauge);
    if (d->m_pointerStyle != pointerStyle)
    {
        d->m_pointerStyle = pointerStyle;
        this->update();
    }
}
