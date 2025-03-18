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

#include <private/qextProgressPie_p.h>

#include <QPainter>
#include <QPainterPath>
#include <QDebug>


QExtProgressPiePrivate::QExtProgressPiePrivate(QExtProgressPie *q)
    : q_ptr(q)
{
    m_backgroundColor = Qt::transparent;
    m_textColor = QColor(255, 255, 255);
    m_baseColor = QColor(100, 100, 100);
    m_innerBackgroundColor = QColor(40, 45, 48);
    m_borderColor = QColor(255, 255, 255);
    m_progressColor = QColor(34, 163, 169);

    m_value = 0;
    m_minValue = 0;
    m_maxValue = 100;
    m_precision = 0;

    m_nullPosition = 90;
    m_outlinePenWidth = 1;
    m_dataPenWidth = 2;

    m_barStyle = QExtProgressPie::BarStyle_Pie;
    m_format = "%p";
    m_clockWise = true;
}

QExtProgressPiePrivate::~QExtProgressPiePrivate()
{

}



QExtProgressPie::QExtProgressPie(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtProgressPiePrivate(this))
{
    this->setFont(QFont("Arial", 8));
}

QExtProgressPie::~QExtProgressPie()
{

}

void QExtProgressPie::paintEvent(QPaintEvent *)
{
    Q_D(QExtProgressPie);
    double outerRadius = qMin(width(), height());
    QRectF baseRect(2, 2, outerRadius - 4, outerRadius - 4);

    QImage buffer(outerRadius, outerRadius, QImage::Format_ARGB32_Premultiplied);
    buffer.fill(Qt::transparent);

    QPainter painter(&buffer);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    rebuildDataBrushIfNeeded();
    this->drawBackground(&painter, buffer.rect());
    this->drawBase(&painter, baseRect);
    this->drawProgress(&painter, baseRect);

    QRectF innerRect;
    double innerRadius(0);
    calculateInnerRect(baseRect, outerRadius, innerRect, innerRadius);
    this->drawValue(&painter, innerRect, innerRadius);
    painter.end();

    QPainter p(this);
    p.setRenderHints(QPainter::SmoothPixmapTransform);
    p.setPen(Qt::NoPen);
    p.setBrush(d->m_backgroundColor);
    p.drawRect(this->rect());

    int pixX = rect().center().x() - buffer.width() / 2;
    int pixY = rect().center().y() - buffer.height() / 2;
    QPoint point(pixX, pixY);
    p.drawImage(point, buffer);
}

void QExtProgressPie::drawBackground(QPainter *painter, const QRectF &baseRect)
{
    painter->fillRect(baseRect,  Qt::transparent);
}

void QExtProgressPie::drawBase(QPainter *painter, const QRectF &baseRect)
{
    Q_D(QExtProgressPie);
    //    switch (barStyle) {
    //    case BarStyle_Donut:
    //        painter->setPen(QPen(baseColor, outlinePenWidth));
    //        painter->setBrush(baseColor);
    //        painter->drawEllipse(baseRect);
    //        break;

    //    case BarStyle_Pie:
    painter->setPen(QPen(d->m_baseColor, d->m_outlinePenWidth));
    painter->setBrush(d->m_baseColor);
    painter->drawEllipse(baseRect);
    //        break;

    //    case BarStyle_Line:
    //        painter->setPen(QPen(baseColor, outlinePenWidth));
    //        painter->setBrush(Qt::NoBrush);
    //        painter->drawEllipse(baseRect.adjusted(outlinePenWidth / 2, outlinePenWidth / 2, -outlinePenWidth / 2, -outlinePenWidth / 2));
    //        break;
    //    }
}

void QExtProgressPie::drawProgress(QPainter *painter, const QRectF &baseRect)
{
    Q_D(QExtProgressPie);
    if (d->m_value == d->m_minValue) {
        return;
    }

    double arcLength = 360.0 / (d->m_maxValue - d->m_minValue) * d->m_value;

    if (!d->m_clockWise) {
        arcLength = -arcLength;
    }

    //    if (barStyle == BarStyle_Line) {
    //        painter->setPen(QPen(progressColor, dataPenWidth));
    //        painter->setBrush(Qt::NoBrush);
    //        painter->drawArc(baseRect.adjusted(outlinePenWidth / 2, outlinePenWidth / 2, -outlinePenWidth / 2, -outlinePenWidth / 2),
    //                         nullPosition * 16, -arcLength * 16);
    //        return;
    //    }

    QPainterPath dataPath;
    dataPath.setFillRule(Qt::WindingFill);

    dataPath.moveTo(baseRect.center());
    dataPath.arcTo(baseRect, d->m_nullPosition, -arcLength);
    dataPath.lineTo(baseRect.center());

    painter->setBrush(d->m_progressColor);
    painter->setPen(QPen(d->m_borderColor, d->m_dataPenWidth));
    painter->drawPath(dataPath);
}

void QExtProgressPie::calculateInnerRect(const QRectF &/*baseRect*/, double outerRadius, QRectF &innerRect, double &innerRadius)
{
    //    if (barStyle == BarStyle_Line) {
    //        innerRadius = outerRadius - outlinePenWidth;
    //    } else {
    innerRadius = outerRadius * 0.75;
    //    }

    double delta = (outerRadius - innerRadius) / 2;
    innerRect = QRectF(delta, delta, innerRadius, innerRadius);
}

//void QExtProgressPie::drawInnerBackground(QPainter *painter, const QRectF &innerRect)
//{
////    if (barStyle == BarStyle_Donut) {
//        painter->setBrush(innerBgColor);
//        painter->drawEllipse(innerRect);
////    }
//}

void QExtProgressPie::drawValue(QPainter *painter, const QRectF &innerRect, double innerRadius)
{
    Q_D(QExtProgressPie);
    if (d->m_format.isEmpty()) {
        return;
    }

    QFont font;
    font.setPixelSize(innerRadius * qMax(0.05, (0.35 - (double)d->m_precision * 0.08)));
    painter->setFont(font);

    QRectF textRect(innerRect);
    painter->setPen(d->m_textColor);

    QString strValue;
    if (d->m_format == "%v") {
        strValue = QString::number(d->m_value, 'f', d->m_precision);
    } else if (d->m_format == "%p") {
        double procent = (d->m_value - d->m_minValue) / (d->m_maxValue - d->m_minValue) * 100.0;
        strValue = QString::number(procent, 'f', d->m_precision) + "%";
    } else if (d->m_format == "%m") {
        strValue = QString::number(d->m_maxValue - d->m_minValue + 1, 'f', d->m_precision) + "m";
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);
}

void QExtProgressPie::rebuildDataBrushIfNeeded()
{
    Q_D(QExtProgressPie);
    if (d->m_gradientData.count() == 0) {
        return;
    }

    QConicalGradient dataBrush;
    dataBrush.setCenter(0.5, 0.5);
    dataBrush.setCoordinateMode(QGradient::StretchToDeviceMode);

    for (int i = 0; i < d->m_gradientData.count(); i++) {
        dataBrush.setColorAt(1.0 - d->m_gradientData.at(i).first, d->m_gradientData.at(i).second);
    }

    dataBrush.setAngle(d->m_nullPosition);
    QPalette p(palette());
    p.setBrush(QPalette::Highlight, dataBrush);
    this->setPalette(p);
}

QColor QExtProgressPie::backgroundColor() const
{
    Q_D(const QExtProgressPie);
    return d->m_backgroundColor;
}

QColor QExtProgressPie::textColor() const
{
    Q_D(const QExtProgressPie);
    return d->m_textColor;
}

QColor QExtProgressPie::baseColor() const
{
    Q_D(const QExtProgressPie);
    return d->m_baseColor;
}

QColor QExtProgressPie::innerBgColor() const
{
    Q_D(const QExtProgressPie);
    return d->m_innerBackgroundColor;
}

QColor QExtProgressPie::borderColor() const
{
    Q_D(const QExtProgressPie);
    return d->m_borderColor;
}

QColor QExtProgressPie::progressColor() const
{
    Q_D(const QExtProgressPie);
    return d->m_progressColor;
}

double QExtProgressPie::value() const
{
    Q_D(const QExtProgressPie);
    return d->m_value;
}

double QExtProgressPie::minValue() const
{
    Q_D(const QExtProgressPie);
    return d->m_minValue;
}

double QExtProgressPie::maxValue() const
{
    Q_D(const QExtProgressPie);
    return d->m_maxValue;
}

int QExtProgressPie::precision() const
{
    Q_D(const QExtProgressPie);
    return d->m_precision;
}

double QExtProgressPie::nullPosition() const
{
    Q_D(const QExtProgressPie);
    return d->m_nullPosition;
}

double QExtProgressPie::outlinePenWidth() const
{
    Q_D(const QExtProgressPie);
    return d->m_outlinePenWidth;
}

double QExtProgressPie::dataPenWidth() const
{
    Q_D(const QExtProgressPie);
    return d->m_dataPenWidth;
}

QExtProgressPie::BarStyle QExtProgressPie::barStyle() const
{
    Q_D(const QExtProgressPie);
    return d->m_barStyle;
}

QString QExtProgressPie::format() const
{
    Q_D(const QExtProgressPie);
    return d->m_format;
}

bool QExtProgressPie::clockWise() const
{
    Q_D(const QExtProgressPie);
    return d->m_clockWise;
}

QGradientStops QExtProgressPie::gradientData() const
{
    Q_D(const QExtProgressPie);
    return d->m_gradientData;
}

QSize QExtProgressPie::sizeHint() const
{
    return QSize(100, 100);
}

QSize QExtProgressPie::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QExtProgressPie::setBackgroundColor(const QColor &color)
{
    Q_D(QExtProgressPie);
    if (d->m_backgroundColor != color) {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QExtProgressPie::setTextColor(const QColor &color)
{
    Q_D(QExtProgressPie);
    if (d->m_textColor != color) {
        d->m_textColor = color;
        this->update();
    }
}

void QExtProgressPie::setBaseColor(const QColor &color)
{
    Q_D(QExtProgressPie);
    if (d->m_baseColor != color) {
        d->m_baseColor = color;
        this->update();
    }
}

void QExtProgressPie::setInnerBackgroundColor(const QColor &color)
{
    Q_D(QExtProgressPie);
    if (d->m_innerBackgroundColor != color) {
        d->m_innerBackgroundColor = color;
        this->update();
    }
}

void QExtProgressPie::setBorderColor(const QColor &color)
{
    Q_D(QExtProgressPie);
    if (d->m_borderColor != color) {
        d->m_borderColor = color;
        this->update();
    }
}

void QExtProgressPie::setProgressColor(const QColor &color)
{
    Q_D(QExtProgressPie);
    if (d->m_progressColor != color) {
        d->m_progressColor = color;
        this->update();
    }
}

void QExtProgressPie::setRange(double minValue, double maxValue)
{
    Q_D(QExtProgressPie);
    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    if (d->m_maxValue < d->m_minValue) {
        qSwap(d->m_maxValue, d->m_minValue);
    }

    if (d->m_value < d->m_minValue) {
        d->m_value = d->m_minValue;
    } else if (d->m_value > d->m_maxValue) {
        d->m_value = d->m_maxValue;
    }

    this->update();
}

void QExtProgressPie::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QExtProgressPie::setMinValue(double minValue)
{
    Q_D(QExtProgressPie);
    this->setRange(minValue, d->m_maxValue);
}

void QExtProgressPie::setMaxValue(double maxValue)
{
    Q_D(QExtProgressPie);
    this->setRange(d->m_minValue, maxValue);
}

void QExtProgressPie::setValue(double value)
{
    Q_D(QExtProgressPie);
    if (value == d->m_value) {
        return;
    }

    if (value < d->m_minValue) {
        value = d->m_minValue;
    } else if (value > d->m_maxValue) {
        value = d->m_maxValue;
    }

    d->m_value = value;
    this->update();
}

void QExtProgressPie::setValue(int value)
{
    this->setValue(double(value));
}

void QExtProgressPie::setPrecision(int precision)
{
    Q_D(QExtProgressPie);
    if (precision >= 0 && d->m_precision != precision) {
        d->m_precision = precision;
        this->update();
    }
}

void QExtProgressPie::setNullPosition(double nullPosition)
{
    Q_D(QExtProgressPie);
    if (d->m_nullPosition != nullPosition) {
        d->m_nullPosition = nullPosition;
        this->update();
    }
}

void QExtProgressPie::setBarStyle(BarStyle barStyle)
{
    Q_D(QExtProgressPie);
    if (d->m_barStyle != barStyle) {
        d->m_barStyle = barStyle;
        this->update();
    }
}

void QExtProgressPie::setFormat(const QString &format)
{
    Q_D(QExtProgressPie);
    if (d->m_format != format) {
        d->m_format = format;
        this->update();
    }
}

void QExtProgressPie::setOutlinePenWidth(double width)
{
    Q_D(QExtProgressPie);
    if (d->m_outlinePenWidth != width) {
        d->m_outlinePenWidth = width;
        this->update();
    }
}

void QExtProgressPie::setDataPenWidth(double width)
{
    Q_D(QExtProgressPie);
    if (d->m_dataPenWidth != width) {
        d->m_dataPenWidth = width;
        this->update();
    }
}

void QExtProgressPie::setClockWise(bool clockWise)
{
    Q_D(QExtProgressPie);
    if (d->m_clockWise != clockWise) {
        d->m_clockWise = clockWise;
        this->update();
    }
}

void QExtProgressPie::setGradientData(const QGradientStops &gradientData)
{
    Q_D(QExtProgressPie);
    if (d->m_gradientData != gradientData) {
        d->m_gradientData = gradientData;
        this->update();
    }
}
