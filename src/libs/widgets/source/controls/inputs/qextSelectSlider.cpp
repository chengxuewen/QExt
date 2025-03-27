/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2017 逆风微光(QQ:787701109)
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

#include <private/qextSelectSlider_p.h>

#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <qmath.h>

QExtSelectSliderPrivate::QExtSelectSliderPrivate(QExtSelectSlider *q)
    : q_ptr(q)
{
    m_minValue = -100;
    m_maxValue = 100;
    m_leftValue = -10;
    m_rightValue = 10;

    m_rangeValue = 20;
    m_step = 1;

    m_borderWidth = 1;
    m_horizontal = true;

    m_usedColor = QColor(24, 189, 155);
    m_freeColor = QColor(100, 100, 100);
    m_textColor = QColor(255, 255, 255);
    m_rangeTextColor = QColor(255, 255, 255);
    m_sliderColor = QColor(255, 107, 107);
    m_borderColor = QColor(70, 70, 70);
    m_buttonNormalColor = QColor(150, 150, 150);
    m_buttonPressColor = QColor(200, 200, 200);

    m_buttonWidth = 20;
    m_sliderHeight = 30;

    m_posPress = QPoint(0, 0);
    m_posMove = QPoint(0, 0);

    m_sliderPress = false;
    m_leftPress = false;
    m_rightPress = false;
    m_leftButtonPress = false;
    m_rightButtonPress = false;
}

QExtSelectSliderPrivate::~QExtSelectSliderPrivate()
{

}




QExtSelectSlider::QExtSelectSlider(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtSelectSliderPrivate(this))
{
    this->setFont(QFont("Arial", 10));
}

QExtSelectSlider::~QExtSelectSlider()
{

}

void QExtSelectSlider::resizeEvent(QResizeEvent *)
{
    Q_D(QExtSelectSlider);
    d->m_leftBtnRect = QRect(d->m_borderWidth, d->m_sliderHeight, d->m_buttonWidth - d->m_borderWidth * 2, height() - d->m_sliderHeight);
    d->m_rightBtnRect = QRect(this->width() - d->m_buttonWidth + d->m_borderWidth, d->m_sliderHeight, d->m_buttonWidth - d->m_borderWidth * 2, height() - d->m_sliderHeight);
    this->updateUI();
}

void QExtSelectSlider::mousePressEvent(QMouseEvent *e)
{
    Q_D(QExtSelectSlider);
    if(e->button() == Qt::LeftButton)
    {
        d->m_posPress = e->pos();
        d->m_posMove = d->m_posPress;

        d->m_sliderPress = false;
        d->m_leftPress = false;
        d->m_rightPress = false;

        if(d->m_sliderRect.contains(d->m_posPress))
        {
            d->m_sliderPress = true;
            d->m_sliderRectTemp = d->m_sliderRect;
            this->update();
        }
        else if(d->m_leftRect.contains(d->m_posPress))
        {
            d->m_leftPress = true;
            d->m_rightValue = d->m_leftValue + d->m_rangeValue;
            d->m_leftRectTemp = d->m_leftRect;
            this->update();
        }
        else if(d->m_rightRect.contains(d->m_posPress))
        {
            d->m_rightPress = true;
            d->m_rightRectTemp = d->m_rightRect;
            this->update();
        }
        else if(d->m_rightBtnRect.contains(d->m_posPress))
        {
            d->m_rightButtonPress = true;
            d->m_leftValue += d->m_step;
            if(d->m_leftValue > d->m_maxValue - d->m_rangeValue)
            {
                d->m_leftValue = d->m_maxValue - d->m_rangeValue;
            }

            d->m_rightValue = d->m_leftValue + d->m_rangeValue;
            emit this->valueChanged(d->m_leftValue, d->m_rightValue);
            this->updateUI();
        }
        else if(d->m_leftBtnRect.contains(d->m_posPress))
        {
            d->m_leftButtonPress = true;
            d->m_leftValue -= d->m_step;
            if(d->m_leftValue < d->m_minValue)
            {
                d->m_leftValue = d->m_minValue;
            }

            d->m_rightValue = d->m_leftValue + d->m_rangeValue;
            emit this->valueChanged(d->m_leftValue, d->m_rightValue);
            this->updateUI();
        }
    }
}

void QExtSelectSlider::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QExtSelectSlider);
    if (d->m_sliderPress)
    {
        d->m_posMove = e->pos();
        int dx = d->m_posMove.x() - d->m_posPress.x();
        QRect rc = d->m_sliderRectTemp;

        if(rc.left() + dx <= d->m_buttonWidth)
        {
            d->m_sliderRect.moveLeft(d->m_buttonWidth);
            d->m_leftValue = d->m_minValue;
        }
        else if(rc.right() + dx >= width() - d->m_buttonWidth)
        {
            d->m_sliderRect.moveRight(width() - d->m_buttonWidth);
            d->m_leftValue = d->m_maxValue - d->m_rangeValue;
        }
        else
        {
            d->m_sliderRect.moveLeft(rc.x() + dx);
            d->m_leftValue = d->m_minValue + ((double)(d->m_sliderRect.x() - d->m_buttonWidth) / (double)(width() - d->m_buttonWidth * 2)) * (double)(d->m_maxValue - d->m_minValue);
        }

        d->m_leftRect = QRect(d->m_sliderRect.x() - 15, 0, 30, 20);
        d->m_rightRect = QRect(d->m_sliderRect.right() - 15, 0, 30, 20);
        d->m_rightValue = d->m_leftValue + d->m_rangeValue;

        emit this->valueChanged(d->m_leftValue, d->m_rightValue);
        this->update();
    }
    else if (d->m_leftPress)
    {
        d->m_posMove = e->pos();
        int dx = d->m_posMove.x() - d->m_posPress.x();
        QRect rc = d->m_leftRectTemp;

        if(rc.x() + dx <= d->m_buttonWidth - 15)
        {
            d->m_leftRect.moveLeft(d->m_buttonWidth - 15);
            d->m_leftValue = d->m_minValue;
        }
        else if(rc.x() + dx >= d->m_rightRect.x())
        {
            d->m_leftRect.moveLeft(d->m_rightRect.x());
            d->m_leftValue = d->m_rightValue;
        }
        else
        {
            d->m_leftRect.moveLeft(rc.x() + dx);
            double wPerPix = ((double)(width() - d->m_buttonWidth * 2)) / ((double)(d->m_maxValue - d->m_minValue)); //每像素代表的值
            d->m_leftValue = d->m_minValue + ((double)(d->m_leftRect.x() - d->m_buttonWidth)) / wPerPix;
        }

        d->m_sliderRect.setX(d->m_leftRect.x() + 15);
        d->m_rangeValue = d->m_rightValue - d->m_leftValue;

        emit this->valueChanged(d->m_leftValue, d->m_rightValue);
        emit this->rangeChanged(d->m_rangeValue);
        this->update();
    }
    else if (d->m_rightPress)
    {
        d->m_posMove = e->pos();
        int dx = d->m_posMove.x() - d->m_posPress.x();
        QRect rc = d->m_rightRectTemp;

        if(rc.x() + dx <= d->m_leftRect.x())
        {
            d->m_rightRect.moveLeft(d->m_leftRect.x());
            d->m_rangeValue = 0;
        }
        else if(rc.right() + dx >= width() - d->m_buttonWidth + 15)
        {
            d->m_rightRect.moveRight(width() - d->m_buttonWidth + 15);
            d->m_rangeValue = d->m_maxValue - d->m_leftValue;
        }
        else
        {
            d->m_rightRect.moveLeft(rc.x() + dx);
            double wPerPix = ((double)(width() - d->m_buttonWidth * 2)) / ((double)(d->m_maxValue - d->m_minValue));
            d->m_rangeValue = (double)(d->m_sliderRect.width()) / wPerPix;
        }

        d->m_sliderRect.setRight(d->m_rightRect.x() + 15);
        d->m_rightValue = d->m_leftValue + d->m_rangeValue;

        emit this->valueChanged(d->m_leftValue, d->m_rightValue);
        emit this->rangeChanged(d->m_rangeValue);
        this->update();
    }
}

void QExtSelectSlider::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(QExtSelectSlider);
    if(e->button() == Qt::LeftButton)
    {
        d->m_sliderPress = false;
        d->m_leftButtonPress = false;
        d->m_rightButtonPress = false;
        this->update();
    }
}

void QExtSelectSlider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);

    this->drawValue(&painter);

    this->drawButton(&painter);

    this->drawSlider(&painter);
}

void QExtSelectSlider::drawBackground(QPainter *painter)
{
    Q_D(QExtSelectSlider);
    painter->save();

    QPen pen;
    pen.setWidthF(d->m_borderWidth);
    pen.setColor(d->m_borderColor);
    painter->setPen(pen);

    painter->setBrush(d->m_freeColor);
    painter->drawRect(d->m_borderWidth, d->m_sliderHeight, width() - d->m_borderWidth * 2, height() - d->m_sliderHeight - d->m_borderWidth);

    painter->restore();
}

void QExtSelectSlider::drawValue(QPainter *painter)
{
    Q_D(QExtSelectSlider);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_usedColor);
    painter->drawRect(d->m_sliderRect);

    painter->setPen(d->m_textColor);
    painter->drawText(d->m_sliderRect, Qt::AlignCenter, QString::number(d->m_rangeValue));

    painter->restore();
}

void QExtSelectSlider::drawButton(QPainter *painter)
{
    Q_D(QExtSelectSlider);
    painter->save();

    QPolygon polygon;

    polygon.clear();
    polygon << QPoint(d->m_leftBtnRect.x() + d->m_leftBtnRect.width() / 4, d->m_leftBtnRect.y() + d->m_leftBtnRect.height() / 2);
    polygon << QPoint(d->m_leftBtnRect.x() + d->m_leftBtnRect.width() * 3 / 4, d->m_leftBtnRect.y() + d->m_leftBtnRect.height() / 2 - 5);
    polygon << QPoint(d->m_leftBtnRect.x() + d->m_leftBtnRect.width() * 3 / 4, d->m_leftBtnRect.y() + d->m_leftBtnRect.height() / 2 + 5);

    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_leftButtonPress ? d->m_buttonPressColor : d->m_buttonNormalColor);
    painter->drawConvexPolygon(polygon);

    polygon.clear();
    polygon << QPoint(d->m_rightBtnRect.x() + d->m_rightBtnRect.width() / 4, d->m_rightBtnRect.y() + d->m_rightBtnRect.height() / 2 - 5);
    polygon << QPoint(d->m_rightBtnRect.x() + d->m_rightBtnRect.width() / 4, d->m_rightBtnRect.y() + d->m_rightBtnRect.height() / 2 + 5);
    polygon << QPoint(d->m_rightBtnRect.x() + d->m_rightBtnRect.width() * 3 / 4, d->m_rightBtnRect.y() + d->m_rightBtnRect.height() / 2);

    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_rightButtonPress ? d->m_buttonPressColor : d->m_buttonNormalColor);
    painter->drawConvexPolygon(polygon);

    painter->restore();
}

void QExtSelectSlider::drawSlider(QPainter *painter)
{
    Q_D(QExtSelectSlider);
    painter->save();

    painter->setPen(d->m_sliderColor.lighter(100));
    painter->setBrush(d->m_sliderColor);
    painter->drawRect(d->m_leftRect);
    painter->drawLine(d->m_leftRect.x(), 20, d->m_leftRect.x() + 15, 30);
    painter->drawLine(d->m_leftRect.right(), 20, d->m_leftRect.x() + 15, 30);
    painter->setPen(d->m_rangeTextColor);
    painter->drawText(d->m_leftRect, Qt::AlignCenter, QString::number(d->m_leftValue));

    painter->setPen(d->m_sliderColor.lighter(100));
    painter->setBrush(d->m_sliderColor);
    painter->drawRect(d->m_rightRect);
    painter->drawLine(d->m_rightRect.x(), 20, d->m_rightRect.x() + 15, 30);
    painter->drawLine(d->m_rightRect.right(), 20, d->m_rightRect.x() + 15, 30);
    painter->setPen(d->m_rangeTextColor);
    painter->drawText(d->m_rightRect, Qt::AlignCenter, QString::number(d->m_rightValue));

    painter->restore();
}

void QExtSelectSlider::updateUI()
{
    Q_D(QExtSelectSlider);
    double w1 = ((double)(width() - d->m_buttonWidth * 2)) / ((double)(d->m_maxValue - d->m_minValue));
    d->m_sliderRect = QRect(d->m_buttonWidth + (d->m_leftValue - d->m_minValue) * w1, d->m_sliderHeight + d->m_borderWidth / 2, d->m_rangeValue * w1 - d->m_borderWidth, height() - d->m_sliderHeight - d->m_borderWidth * 2);

    if(d->m_sliderRect.right() > width() - d->m_buttonWidth)
    {
        d->m_sliderRect.moveLeft(width() - d->m_buttonWidth - d->m_sliderRect.width());
        d->m_leftValue = d->m_minValue + (double)(d->m_sliderRect.x() - d->m_buttonWidth) * w1;
    }

    d->m_leftRect = QRect(d->m_sliderRect.x() - 15, 0, 30, 20);
    d->m_rightRect = QRect(d->m_sliderRect.right() - 15, 0, 30, 20);

    this->update();
}

int QExtSelectSlider::minValue() const
{
    Q_D(const QExtSelectSlider);
    return d->m_minValue;
}

int QExtSelectSlider::maxValue() const
{
    Q_D(const QExtSelectSlider);
    return d->m_maxValue;
}

int QExtSelectSlider::leftValue() const
{
    Q_D(const QExtSelectSlider);
    return d->m_leftValue;
}

int QExtSelectSlider::rightValue() const
{
    Q_D(const QExtSelectSlider);
    return d->m_rightValue;
}

int QExtSelectSlider::rangeValue() const
{
    Q_D(const QExtSelectSlider);
    return d->m_rangeValue;
}

int QExtSelectSlider::step() const
{
    Q_D(const QExtSelectSlider);
    return d->m_step;
}

int QExtSelectSlider::borderWidth() const
{
    Q_D(const QExtSelectSlider);
    return d->m_borderWidth;
}

bool QExtSelectSlider::isHorizontal() const
{
    Q_D(const QExtSelectSlider);
    return d->m_horizontal;
}

QColor QExtSelectSlider::usedColor() const
{
    Q_D(const QExtSelectSlider);
    return d->m_usedColor;
}

QColor QExtSelectSlider::freeColor() const
{
    Q_D(const QExtSelectSlider);
    return d->m_freeColor;
}

QColor QExtSelectSlider::textColor() const
{
    Q_D(const QExtSelectSlider);
    return d->m_textColor;
}

QColor QExtSelectSlider::rangeTextColor() const
{
    Q_D(const QExtSelectSlider);
    return d->m_rangeTextColor;
}

QColor QExtSelectSlider::sliderColor() const
{
    Q_D(const QExtSelectSlider);
    return d->m_sliderColor;
}

QColor QExtSelectSlider::borderColor() const
{
    Q_D(const QExtSelectSlider);
    return d->m_borderColor;
}

QColor QExtSelectSlider::buttonNormalColor() const
{
    Q_D(const QExtSelectSlider);
    return d->m_buttonNormalColor;
}

QColor QExtSelectSlider::buttonPressColor() const
{
    Q_D(const QExtSelectSlider);
    return d->m_buttonPressColor;
}

QSize QExtSelectSlider::sizeHint() const
{
    return QSize(450, 60);
}

QSize QExtSelectSlider::minimumSizeHint() const
{
    return QSize(100, 50);
}

void QExtSelectSlider::setRange(int minValue, int maxValue)
{
    Q_D(QExtSelectSlider);
    if (minValue >= maxValue)
    {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    if (d->m_leftValue < minValue)
    {
        d->m_leftValue = minValue;
    }

    if (d->m_rightValue > maxValue)
    {
        d->m_rightValue = maxValue;
    }

    if (d->m_leftValue < minValue || d->m_rightValue > maxValue)
    {
        this->setCurrentRange(d->m_leftValue, d->m_rightValue);
    }

    this->updateUI();
}

void QExtSelectSlider::setMinValue(int minValue)
{
    Q_D(QExtSelectSlider);
    this->setRange(minValue, d->m_maxValue);
}

void QExtSelectSlider::setMaxValue(int maxValue)
{
    Q_D(QExtSelectSlider);
    this->setRange(d->m_minValue, maxValue);
}

void QExtSelectSlider::setCurrentRange(int leftValue, int rightValue)
{
    Q_D(QExtSelectSlider);
    if (leftValue > rightValue)
    {
        return;
    }

    if (leftValue < d->m_minValue || rightValue > d->m_maxValue)
    {
        return;
    }

    d->m_leftValue = leftValue;
    d->m_rightValue = rightValue;
    d->m_rangeValue = rightValue - leftValue;
    emit valueChanged(leftValue, rightValue);

    this->updateUI();
}

void QExtSelectSlider::setLeftValue(int leftValue)
{
    Q_D(QExtSelectSlider);
    this->setCurrentRange(leftValue, d->m_rightValue);
}

void QExtSelectSlider::setRightValue(int rightValue)
{
    Q_D(QExtSelectSlider);
    this->setCurrentRange(d->m_leftValue, rightValue);
}

void QExtSelectSlider::setRangeValue(int rangeValue)
{
    Q_D(QExtSelectSlider);
    if (d->m_rangeValue != rangeValue)
    {
        d->m_rangeValue = rangeValue;
        setRightValue(d->m_leftValue + rangeValue);
    }
}

void QExtSelectSlider::setStep(int step)
{
    Q_D(QExtSelectSlider);
    if (d->m_step != step)
    {
        d->m_step = step;
    }
}

void QExtSelectSlider::setBorderWidth(int borderWidth)
{
    Q_D(QExtSelectSlider);
    if (d->m_borderWidth != borderWidth)
    {
        d->m_borderWidth = borderWidth;
        this->update();
    }
}

void QExtSelectSlider::setHorizontal(bool horizontal)
{
    Q_D(QExtSelectSlider);
    if (d->m_horizontal != horizontal)
    {
        d->m_horizontal = horizontal;
        this->update();
    }
}

void QExtSelectSlider::setUsedColor(const QColor &usedColor)
{
    Q_D(QExtSelectSlider);
    if (d->m_usedColor != usedColor)
    {
        d->m_usedColor = usedColor;
        this->update();
    }
}

void QExtSelectSlider::setFreeColor(const QColor &freeColor)
{
    Q_D(QExtSelectSlider);
    if (d->m_freeColor != freeColor)
    {
        d->m_freeColor = freeColor;
        this->update();
    }
}

void QExtSelectSlider::setTextColor(const QColor &textColor)
{
    Q_D(QExtSelectSlider);
    if (d->m_textColor != textColor)
    {
        d->m_textColor = textColor;
        this->update();
    }
}

void QExtSelectSlider::setRangeTextColor(const QColor &rangeTextColor)
{
    Q_D(QExtSelectSlider);
    if (d->m_rangeTextColor != rangeTextColor)
    {
        d->m_rangeTextColor = rangeTextColor;
        this->update();
    }
}

void QExtSelectSlider::setSliderColor(const QColor &sliderColor)
{
    Q_D(QExtSelectSlider);
    if (d->m_sliderColor != sliderColor)
    {
        d->m_sliderColor = sliderColor;
        this->update();
    }
}

void QExtSelectSlider::setBorderColor(const QColor &borderColor)
{
    Q_D(QExtSelectSlider);
    if (d->m_borderColor != borderColor)
    {
        d->m_borderColor = borderColor;
        this->update();
    }
}

void QExtSelectSlider::setButtonNormalColor(const QColor &btnNormalColor)
{
    Q_D(QExtSelectSlider);
    if (d->m_buttonNormalColor != btnNormalColor)
    {
        d->m_buttonNormalColor = btnNormalColor;
        this->update();
    }
}

void QExtSelectSlider::setButtonPressColor(const QColor &btnPressColor)
{
    Q_D(QExtSelectSlider);
    if (d->m_buttonPressColor != btnPressColor)
    {
        d->m_buttonPressColor = btnPressColor;
        this->update();
    }
}
