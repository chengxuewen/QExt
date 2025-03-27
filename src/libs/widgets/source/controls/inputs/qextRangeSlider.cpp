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

#include <private/qextRangeSlider_p.h>

#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <qmath.h>


QExtRangeSliderPrivate::QExtRangeSliderPrivate(QExtRangeSlider *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_leftValue = 40;
    m_rightValue = 60;

    m_borderWidth = 3;
    m_horizontal = true;
    m_textVisible = false;

    m_usedColor = QColor(24, 189, 155);
    m_freeColor = QColor(70, 70, 70);
    m_textColor = QColor(80, 80, 80);
    m_rangeTextColor = QColor(200, 200, 200);
    m_sliderColor = QColor(250, 250, 250);
    m_borderColor = QColor(255, 107, 107);

    m_sliderStyle = QExtRangeSlider::SliderStyle_Line;
    m_sliderBackgroundPercent = QExtRangeSlider::SliderBgPercent_0_2;
    m_sliderPercent = QExtRangeSlider::SliderPercent_0_3;

    m_leftPressed = false;
    m_rightPressed = false;
}

QExtRangeSliderPrivate::~QExtRangeSliderPrivate()
{

}



QExtRangeSlider::QExtRangeSlider(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtRangeSliderPrivate(this))
{
    this->setFont(QFont("Arial", 8));
}

QExtRangeSlider::~QExtRangeSlider()
{

}

void QExtRangeSlider::mousePressEvent(QMouseEvent *e)
{
    Q_D(QExtRangeSlider);
    if (e->button() & Qt::LeftButton) {
        if (d->m_leftSliderRect.contains(e->pos())) {
            d->m_leftPressed = true;
            this->update();
        } else if (d->m_rightSliderRect.contains(e->pos())) {
            d->m_rightPressed = true;
            this->update();
        }
    }
}

void QExtRangeSlider::mouseReleaseEvent(QMouseEvent *)
{
    Q_D(QExtRangeSlider);
    d->m_leftPressed = false;
    d->m_rightPressed = false;
    this->update();
}

void QExtRangeSlider::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QExtRangeSlider);
    if (d->m_leftPressed) {
        if (e->pos().x() >= rect().x()) {
            int width = this->width();
            double increment = (double)width / (d->m_maxValue - d->m_minValue);
            int value = e->pos().x() / increment;

            if (value >= d->m_minValue && value <= d->m_rightValue) {
                d->m_leftValue = value;
                emit valueChanged(d->m_leftValue, d->m_rightValue);
                this->update();
            }

        }
    } else if (d->m_rightPressed) {
        if (e->pos().x() <= rect().width()) {
            int width = this->width();
            double increment = (double)width / (d->m_maxValue - d->m_minValue);
            int value = e->pos().x() / increment;

            if (value >= d->m_leftValue && value <= d->m_maxValue) {
                d->m_rightValue = value;
                emit valueChanged(d->m_leftValue, d->m_rightValue);
                this->update();
            }
        }
    }
}

void QExtRangeSlider::paintEvent(QPaintEvent *)
{
    Q_D(const QExtRangeSlider);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    drawSliderBackground(&painter);

    if (d->m_sliderStyle == SliderStyle_Line) {
        this->drawSliderLine(&painter);
    } else if (d->m_sliderStyle == SliderStyle_Circle) {
        this->drawSliderCircle(&painter);
    }

    this->drawValue(&painter);
}

void QExtRangeSlider::drawSliderBackground(QPainter *painter)
{
    Q_D(const QExtRangeSlider);
    painter->save();

    int width = this->width();
    int height = this->height();
    int penWidth = height * ((double)d->m_sliderBackgroundPercent / 10);
    int radius = penWidth / 2;

    int offset = 1;

    QPen pen;
    pen.setWidth(penWidth);
    pen.setColor(d->m_freeColor);
    pen.setCapStyle(Qt::RoundCap);

    painter->setPen(pen);
    painter->drawLine(radius + offset, height / 2, width - radius - offset, height / 2);

    painter->restore();
}

void QExtRangeSlider::drawSliderLine(QPainter *painter)
{
    Q_D(QExtRangeSlider);
    painter->save();
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();
    d->m_sliderLen = height * ((double)d->m_sliderPercent / 10);

    double increment = (double)width / (d->m_maxValue - d->m_minValue);
    int initY = 0;

    d->m_leftSliderRect = QRect(d->m_leftValue * increment, initY, d->m_sliderLen, height);
    d->m_rightSliderRect = QRect(d->m_rightValue * increment, initY, d->m_sliderLen, height);

    int penWidth = height * ((double)d->m_sliderBackgroundPercent / 10);

    painter->setBrush(d->m_usedColor);
    painter->drawRect(d->m_leftSliderRect.x(), (height - penWidth) / 2, d->m_rightSliderRect.x() - d->m_leftSliderRect.x(), penWidth);

    QPen pen = QPen();
    pen.setWidth(d->m_sliderLen);
    pen.setColor(d->m_usedColor);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    painter->drawLine(d->m_leftSliderRect.x(), d->m_sliderLen, d->m_leftSliderRect.x(), height - d->m_sliderLen);

    painter->drawLine(d->m_rightSliderRect.x(), d->m_sliderLen, d->m_rightSliderRect.x(), height - d->m_sliderLen);

    painter->restore();
}

void QExtRangeSlider::drawSliderCircle(QPainter *painter)
{
    Q_D(QExtRangeSlider);
    painter->save();
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();
    d->m_sliderLen = height * ((double)d->m_sliderPercent / 10);

    if (d->m_sliderLen >= height / 2) {
        d->m_sliderLen = height / 2 - 1;
    }
    double increment = (double)width / (d->m_maxValue - d->m_minValue);

    int initY = (height - d->m_sliderLen * 2) / 2;
    int side = d->m_sliderLen * 2;
    int borderSide = side + d->m_borderWidth * 2;

    d->m_leftSliderRect = QRect(d->m_leftValue * increment - d->m_sliderLen, initY, side, side);
    d->m_rightSliderRect = QRect(d->m_rightValue * increment - d->m_sliderLen, initY, side, side);

    int penWidth = height * ((double)d->m_sliderBackgroundPercent / 10);
    painter->setBrush(d->m_usedColor);
    painter->drawRect(d->m_leftSliderRect.x() + d->m_sliderLen, (height - penWidth) / 2, d->m_rightSliderRect.x() - d->m_leftSliderRect.x(), penWidth);

    painter->setBrush(d->m_borderColor);
    painter->drawEllipse(d->m_leftSliderRect.x() - d->m_borderWidth, d->m_leftSliderRect.y() - d->m_borderWidth, borderSide, borderSide);
    painter->setBrush(d->m_sliderColor);
    painter->drawEllipse(d->m_leftSliderRect);

    painter->setBrush(d->m_borderColor);
    painter->drawEllipse(d->m_rightSliderRect.x() - d->m_borderWidth, d->m_rightSliderRect.y() - d->m_borderWidth, borderSide, borderSide);
    painter->setBrush(d->m_sliderColor);
    painter->drawEllipse(d->m_rightSliderRect);

    painter->restore();
}

void QExtRangeSlider::drawValue(QPainter *painter)
{
    Q_D(QExtRangeSlider);
    if (!d->m_textVisible) {
        return;
    }

    painter->save();

    QFont font;
    font.setPixelSize(d->m_leftSliderRect.width() / 1.6);
    painter->setFont(font);

    painter->setPen(d->m_textColor);

    painter->drawText(d->m_leftSliderRect, Qt::AlignCenter, QString::number(d->m_leftValue));

    painter->drawText(d->m_rightSliderRect, Qt::AlignCenter, QString::number(d->m_rightValue));

    painter->restore();
}

int QExtRangeSlider::minValue() const
{
    Q_D(const QExtRangeSlider);
    return d->m_minValue;
}

int QExtRangeSlider::maxValue() const
{
    Q_D(const QExtRangeSlider);
    return d->m_maxValue;
}

int QExtRangeSlider::leftValue() const
{
    Q_D(const QExtRangeSlider);
    return d->m_leftValue;
}

int QExtRangeSlider::rightValue() const
{
    Q_D(const QExtRangeSlider);
    return d->m_rightValue;
}

int QExtRangeSlider::borderWidth() const
{
    Q_D(const QExtRangeSlider);
    return d->m_borderWidth;
}

bool QExtRangeSlider::horizontal() const
{
    Q_D(const QExtRangeSlider);
    return d->m_horizontal;
}

bool QExtRangeSlider::isTextVisible() const
{
    Q_D(const QExtRangeSlider);
    return d->m_textVisible;
}

QColor QExtRangeSlider::usedColor() const
{
    Q_D(const QExtRangeSlider);
    return d->m_usedColor;
}

QColor QExtRangeSlider::freeColor() const
{
    Q_D(const QExtRangeSlider);
    return d->m_freeColor;
}

QColor QExtRangeSlider::textColor() const
{
    Q_D(const QExtRangeSlider);
    return d->m_textColor;
}

QColor QExtRangeSlider::rangeTextColor() const
{
    Q_D(const QExtRangeSlider);
    return d->m_rangeTextColor;
}

QColor QExtRangeSlider::sliderColor() const
{
    Q_D(const QExtRangeSlider);
    return d->m_sliderColor;
}

QColor QExtRangeSlider::borderColor() const
{
    Q_D(const QExtRangeSlider);
    return d->m_borderColor;
}

QExtRangeSlider::SliderStyle QExtRangeSlider::sliderStyle() const
{
    Q_D(const QExtRangeSlider);
    return d->m_sliderStyle;
}

QExtRangeSlider::SliderBgPercent QExtRangeSlider::sliderBgPercent() const
{
    Q_D(const QExtRangeSlider);
    return d->m_sliderBackgroundPercent;
}

QExtRangeSlider::SliderPercent QExtRangeSlider::sliderPercent() const
{
    Q_D(const QExtRangeSlider);
    return d->m_sliderPercent;
}

QSize QExtRangeSlider::sizeHint() const
{
    return QSize(300, 50);
}

QSize QExtRangeSlider::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QExtRangeSlider::setRange(int minValue, int maxValue)
{
    Q_D(QExtRangeSlider);
    if (minValue >= maxValue) {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    if (d->m_leftValue < minValue) {
        d->m_leftValue = minValue;
    }

    if (d->m_rightValue > maxValue) {
        d->m_rightValue = maxValue;
    }

    if (d->m_leftValue < minValue || d->m_rightValue > maxValue) {
        setCurrentRange(d->m_leftValue, d->m_rightValue);
    }

    this->update();
}

void QExtRangeSlider::setMinValue(int minValue)
{
    Q_D(QExtRangeSlider);
    this->setRange(minValue, d->m_maxValue);
}

void QExtRangeSlider::setMaxValue(int maxValue)
{
    Q_D(QExtRangeSlider);
    this->setRange(d->m_minValue, maxValue);
}

void QExtRangeSlider::setCurrentRange(int leftValue, int rightValue)
{
    Q_D(QExtRangeSlider);
    if (leftValue > rightValue) {
        return;
    }

    if (leftValue < d->m_minValue || rightValue > d->m_maxValue) {
        return;
    }

    d->m_leftValue = leftValue;
    d->m_rightValue = rightValue;
    emit this->valueChanged(leftValue, rightValue);

    this->update();
}

void QExtRangeSlider::setLeftValue(int leftValue)
{
    Q_D(QExtRangeSlider);
    this->setCurrentRange(leftValue, d->m_rightValue);
}

void QExtRangeSlider::setRightValue(int rightValue)
{
    Q_D(QExtRangeSlider);
    this->setCurrentRange(d->m_leftValue, rightValue);
}

void QExtRangeSlider::setBorderWidth(int borderWidth)
{
    Q_D(QExtRangeSlider);
    if (d->m_borderWidth != borderWidth) {
        d->m_borderWidth = borderWidth;
        this->update();
    }
}

void QExtRangeSlider::setHorizontal(bool horizontal)
{
    Q_D(QExtRangeSlider);
    if (d->m_horizontal != horizontal) {
        d->m_horizontal = horizontal;
        this->update();
    }
}

void QExtRangeSlider::setTextVisible(bool visiable)
{
    Q_D(QExtRangeSlider);
    if (d->m_textVisible != visiable) {
        d->m_textVisible = visiable;
        this->update();
    }
}

void QExtRangeSlider::setUsedColor(const QColor &color)
{
    Q_D(QExtRangeSlider);
    if (d->m_usedColor != color) {
        d->m_usedColor = color;
        this->update();
    }
}

void QExtRangeSlider::setFreeColor(const QColor &color)
{
    Q_D(QExtRangeSlider);
    if (d->m_freeColor != color) {
        d->m_freeColor = color;
        this->update();
    }
}

void QExtRangeSlider::setTextColor(const QColor &color)
{
    Q_D(QExtRangeSlider);
    if (d->m_textColor != color) {
        d->m_textColor = color;
        this->update();
    }
}

void QExtRangeSlider::setRangeTextColor(const QColor &color)
{
    Q_D(QExtRangeSlider);
    if (d->m_rangeTextColor != color) {
        d->m_rangeTextColor = color;
        this->update();
    }
}

void QExtRangeSlider::setSliderColor(const QColor &color)
{
    Q_D(QExtRangeSlider);
    if (d->m_sliderColor != color) {
        d->m_sliderColor = color;
        this->update();
    }
}

void QExtRangeSlider::setBorderColor(const QColor &color)
{
    Q_D(QExtRangeSlider);
    if (d->m_borderColor != color) {
        d->m_borderColor = color;
        this->update();
    }
}

void QExtRangeSlider::setSliderStyle(const QExtRangeSlider::SliderStyle &sliderStyle)
{
    Q_D(QExtRangeSlider);
    if (d->m_sliderStyle != sliderStyle) {
        d->m_sliderStyle = sliderStyle;
        this->update();
    }
}

void QExtRangeSlider::setSliderBackgroundPercent(const QExtRangeSlider::SliderBgPercent &percent)
{
    Q_D(QExtRangeSlider);
    if (d->m_sliderBackgroundPercent != percent) {
        d->m_sliderBackgroundPercent = percent;
        this->update();
    }
}

void QExtRangeSlider::setSliderPercent(const QExtRangeSlider::SliderPercent &percent)
{
    Q_D(QExtRangeSlider);
    if (d->m_sliderPercent != percent) {
        d->m_sliderPercent = percent;
        this->update();
    }
}

