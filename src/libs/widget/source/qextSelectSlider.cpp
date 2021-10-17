#pragma execution_character_set("utf-8")

#include <qextSelectSlider.h>

#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <qmath.h>

QEXTSelectSlider::QEXTSelectSlider(QWidget *parent) : QWidget(parent)
{
    minValue = -100;
    maxValue = 100;
    leftValue = -10;
    rightValue = 10;

    rangeValue = 20;
    step = 1;

    borderWidth = 1;
    horizontal = true;

    usedColor = QColor(24, 189, 155);
    freeColor = QColor(100, 100, 100);
    textColor = QColor(255, 255, 255);
    rangeTextColor = QColor(255, 255, 255);
    sliderColor = QColor(255, 107, 107);
    borderColor = QColor(70, 70, 70);
    btnNormalColor = QColor(150, 150, 150);
    btnPressColor = QColor(200, 200, 200);

    btnWidth = 20;
    sliderHeight = 30;

    posPress = QPoint(0, 0);
    posMove = QPoint(0, 0);

    sliderPress = false;
    leftPress = false;
    rightPress = false;
    leftBtnPress = false;
    rightBtnPress = false;

    setFont(QFont("Arial", 10));
}

void QEXTSelectSlider::resizeEvent(QResizeEvent *)
{
    leftBtnRect = QRect(borderWidth, sliderHeight, btnWidth - borderWidth * 2, height() - sliderHeight);
    rightBtnRect = QRect(width() - btnWidth + borderWidth, sliderHeight, btnWidth - borderWidth * 2, height() - sliderHeight);
    updateUI();
}

void QEXTSelectSlider::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        posPress = e->pos();
        posMove = posPress;

        sliderPress = false;
        leftPress = false;
        rightPress = false;

        if(sliderRect.contains(posPress))
        {
            sliderPress = true;
            sliderRectTemp = sliderRect;
            update();
        }
        else if(leftRect.contains(posPress))
        {
            leftPress = true;
            rightValue = leftValue + rangeValue;
            leftRectTemp = leftRect;
            update();
        }
        else if(rightRect.contains(posPress))
        {
            rightPress = true;
            rightRectTemp = rightRect;
            update();
        }
        else if(rightBtnRect.contains(posPress))
        {
            rightBtnPress = true;
            leftValue += step;
            if(leftValue > maxValue - rangeValue)
            {
                leftValue = maxValue - rangeValue;
            }

            rightValue = leftValue + rangeValue;
            emit valueChanged(leftValue, rightValue);
            updateUI();
        }
        else if(leftBtnRect.contains(posPress))
        {
            leftBtnPress = true;
            leftValue -= step;
            if(leftValue < minValue)
            {
                leftValue = minValue;
            }

            rightValue = leftValue + rangeValue;
            emit valueChanged(leftValue, rightValue);
            updateUI();
        }
    }
}

void QEXTSelectSlider::mouseMoveEvent(QMouseEvent *e)
{
    if (sliderPress)
    {
        posMove = e->pos();
        int dx = posMove.x() - posPress.x();
        QRect rc = sliderRectTemp;

        if(rc.left() + dx <= btnWidth)
        {
            //左侧超出
            sliderRect.moveLeft(btnWidth);
            leftValue = minValue;
        }
        else if(rc.right() + dx >= width() - btnWidth)
        {
            //右侧超出
            sliderRect.moveRight(width() - btnWidth);
            leftValue = maxValue - rangeValue;
        }
        else
        {
            //正常拖动
            sliderRect.moveLeft(rc.x() + dx);
            leftValue = minValue + ((double)(sliderRect.x() - btnWidth) / (double)(width() - btnWidth * 2)) * (double)(maxValue - minValue);
        }

        leftRect = QRect(sliderRect.x() - 15, 0, 30, 20);
        rightRect = QRect(sliderRect.right() - 15, 0, 30, 20);
        rightValue = leftValue + rangeValue;

        emit valueChanged(leftValue, rightValue);
        update();
    }
    else if (leftPress)
    {
        posMove = e->pos();
        int dx = posMove.x() - posPress.x();
        QRect rc = leftRectTemp;

        if(rc.x() + dx <= btnWidth - 15)
        {
            //左侧超出
            leftRect.moveLeft(btnWidth - 15);
            leftValue = minValue;
        }
        else if(rc.x() + dx >= rightRect.x())
        {
            //右侧碰到右滑块,不让继续滑
            leftRect.moveLeft(rightRect.x());
            leftValue = rightValue;
        }
        else
        {
            //正常拖动
            leftRect.moveLeft(rc.x() + dx);
            double wPerPix = ((double)(width() - btnWidth * 2)) / ((double)(maxValue - minValue)); //每像素代表的值
            leftValue = minValue + ((double)(leftRect.x() - btnWidth)) / wPerPix;
        }

        sliderRect.setX(leftRect.x() + 15);
        rangeValue = rightValue - leftValue;

        emit valueChanged(leftValue, rightValue);
        emit rangeChanged(rangeValue);
        update();
    }
    else if (rightPress)
    {
        posMove = e->pos();
        int dx = posMove.x() - posPress.x();
        QRect rc = rightRectTemp;

        if(rc.x() + dx <= leftRect.x())
        {
            //左侧碰到左滑块
            rightRect.moveLeft(leftRect.x());
            rangeValue = 0;
        }
        else if(rc.right() + dx >= width() - btnWidth + 15)
        {
            //右侧超出
            rightRect.moveRight(width() - btnWidth + 15);
            rangeValue = maxValue - leftValue;
        }
        else
        {
            //正常拖动
            rightRect.moveLeft(rc.x() + dx);
            double wPerPix = ((double)(width() - btnWidth * 2)) / ((double)(maxValue - minValue));
            rangeValue = (double)(sliderRect.width()) / wPerPix;
        }

        sliderRect.setRight(rightRect.x() + 15);
        rightValue = leftValue + rangeValue;

        emit valueChanged(leftValue, rightValue);
        emit rangeChanged(rangeValue);
        update();
    }
}

void QEXTSelectSlider::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        sliderPress = false;
        leftBtnPress = false;
        rightBtnPress = false;
        update();
    }
}

void QEXTSelectSlider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制范围值
    drawValue(&painter);
    //绘制左右按钮
    drawBtn(&painter);
    //绘制左右滑块
    drawSlider(&painter);
}

void QEXTSelectSlider::drawBg(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setWidthF(borderWidth);
    pen.setColor(borderColor);
    painter->setPen(pen);

    painter->setBrush(freeColor);
    painter->drawRect(borderWidth, sliderHeight, width() - borderWidth * 2, height() - sliderHeight - borderWidth);

    painter->restore();
}

void QEXTSelectSlider::drawValue(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(usedColor);
    painter->drawRect(sliderRect);

    painter->setPen(textColor);
    painter->drawText(sliderRect, Qt::AlignCenter, QString::number(rangeValue));

    painter->restore();
}

void QEXTSelectSlider::drawBtn(QPainter *painter)
{
    painter->save();

    QPolygon polygon;

    //左侧三角箭头
    polygon.clear();
    polygon << QPoint(leftBtnRect.x() + leftBtnRect.width() / 4, leftBtnRect.y() + leftBtnRect.height() / 2);
    polygon << QPoint(leftBtnRect.x() + leftBtnRect.width() * 3 / 4, leftBtnRect.y() + leftBtnRect.height() / 2 - 5);
    polygon << QPoint(leftBtnRect.x() + leftBtnRect.width() * 3 / 4, leftBtnRect.y() + leftBtnRect.height() / 2 + 5);

    painter->setPen(Qt::NoPen);
    painter->setBrush(leftBtnPress ? btnPressColor : btnNormalColor);
    painter->drawConvexPolygon(polygon);

    //右侧三角箭头
    polygon.clear();
    polygon << QPoint(rightBtnRect.x() + rightBtnRect.width() / 4, rightBtnRect.y() + rightBtnRect.height() / 2 - 5);
    polygon << QPoint(rightBtnRect.x() + rightBtnRect.width() / 4, rightBtnRect.y() + rightBtnRect.height() / 2 + 5);
    polygon << QPoint(rightBtnRect.x() + rightBtnRect.width() * 3 / 4, rightBtnRect.y() + rightBtnRect.height() / 2);

    painter->setPen(Qt::NoPen);
    painter->setBrush(rightBtnPress ? btnPressColor : btnNormalColor);
    painter->drawConvexPolygon(polygon);

    painter->restore();
}

void QEXTSelectSlider::drawSlider(QPainter *painter)
{
    painter->save();

    //左侧滑块
    painter->setPen(sliderColor.light(100));
    painter->setBrush(sliderColor);
    painter->drawRect(leftRect);
    painter->drawLine(leftRect.x(), 20, leftRect.x() + 15, 30);
    painter->drawLine(leftRect.right(), 20, leftRect.x() + 15, 30);
    painter->setPen(rangeTextColor);
    painter->drawText(leftRect, Qt::AlignCenter, QString::number(leftValue));

    //右侧滑块
    painter->setPen(sliderColor.light(100));
    painter->setBrush(sliderColor);
    painter->drawRect(rightRect);
    painter->drawLine(rightRect.x(), 20, rightRect.x() + 15, 30);
    painter->drawLine(rightRect.right(), 20, rightRect.x() + 15, 30);
    painter->setPen(rangeTextColor);
    painter->drawText(rightRect, Qt::AlignCenter, QString::number(rightValue));

    painter->restore();
}

void QEXTSelectSlider::updateUI()
{
    double w1 = ((double)(width() - btnWidth * 2)) / ((double)(maxValue - minValue));
    sliderRect = QRect(btnWidth + (leftValue - minValue) * w1, sliderHeight + borderWidth / 2, rangeValue * w1 - borderWidth, height() - sliderHeight - borderWidth * 2);

    //主滑块右侧越界，保持页宽和滑块右侧不动，把左侧的起点左移
    if(sliderRect.right() > width() - btnWidth)
    {
        sliderRect.moveLeft(width() - btnWidth - sliderRect.width());
        leftValue = minValue + (double)(sliderRect.x() - btnWidth) * w1;
    }

    leftRect = QRect(sliderRect.x() - 15, 0, 30, 20);
    rightRect = QRect(sliderRect.right() - 15, 0, 30, 20);

    update();
}

int QEXTSelectSlider::getMinValue() const
{
    return this->minValue;
}

int QEXTSelectSlider::getMaxValue() const
{
    return this->maxValue;
}

int QEXTSelectSlider::getLeftValue() const
{
    return this->leftValue;
}

int QEXTSelectSlider::getRightValue() const
{
    return this->rightValue;
}

int QEXTSelectSlider::getRangeValue() const
{
    return this->rangeValue;
}

int QEXTSelectSlider::getStep() const
{
    return this->step;
}

int QEXTSelectSlider::getBorderWidth() const
{
    return this->borderWidth;
}

bool QEXTSelectSlider::getHorizontal() const
{
    return this->horizontal;
}

QColor QEXTSelectSlider::getUsedColor() const
{
    return this->usedColor;
}

QColor QEXTSelectSlider::getFreeColor() const
{
    return this->freeColor;
}

QColor QEXTSelectSlider::getTextColor() const
{
    return this->textColor;
}

QColor QEXTSelectSlider::getRangeTextColor() const
{
    return this->rangeTextColor;
}

QColor QEXTSelectSlider::getSliderColor() const
{
    return this->sliderColor;
}

QColor QEXTSelectSlider::getBorderColor() const
{
    return this->borderColor;
}

QColor QEXTSelectSlider::getBtnNormalColor() const
{
    return this->btnNormalColor;
}

QColor QEXTSelectSlider::getBtnPressColor() const
{
    return this->btnPressColor;
}

QSize QEXTSelectSlider::sizeHint() const
{
    return QSize(450, 60);
}

QSize QEXTSelectSlider::minimumSizeHint() const
{
    return QSize(100, 50);
}

void QEXTSelectSlider::setRange(int minValue, int maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue)
    {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (leftValue < minValue)
    {
        leftValue = minValue;
    }

    if (rightValue > maxValue)
    {
        rightValue = maxValue;
    }

    if (leftValue < minValue || rightValue > maxValue)
    {
        setCurrentRange(leftValue, rightValue);
    }

    updateUI();
}

void QEXTSelectSlider::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void QEXTSelectSlider::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void QEXTSelectSlider::setCurrentRange(int leftValue, int rightValue)
{
    //左边值不能大于右边值
    if (leftValue > rightValue)
    {
        return;
    }

    //左边值不能小于最小值,右边值不能大于最大值
    if (leftValue < minValue || rightValue > maxValue)
    {
        return;
    }

    this->leftValue = leftValue;
    this->rightValue = rightValue;
    this->rangeValue = rightValue - leftValue;
    emit valueChanged(leftValue, rightValue);

    updateUI();
}

void QEXTSelectSlider::setLeftValue(int leftValue)
{
    setCurrentRange(leftValue, rightValue);
}

void QEXTSelectSlider::setRightValue(int rightValue)
{
    setCurrentRange(leftValue, rightValue);
}

void QEXTSelectSlider::setRangeValue(int rangeValue)
{
    if (this->rangeValue != rangeValue)
    {
        this->rangeValue = rangeValue;
        setRightValue(leftValue + rangeValue);
    }
}

void QEXTSelectSlider::setStep(int step)
{
    if (this->step != step)
    {
        this->step = step;
    }
}

void QEXTSelectSlider::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth)
    {
        this->borderWidth = borderWidth;
        update();
    }
}

void QEXTSelectSlider::setHorizontal(bool horizontal)
{
    if (this->horizontal != horizontal)
    {
        this->horizontal = horizontal;
        update();
    }
}

void QEXTSelectSlider::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor)
    {
        this->usedColor = usedColor;
        update();
    }
}

void QEXTSelectSlider::setFreeColor(const QColor &freeColor)
{
    if (this->freeColor != freeColor)
    {
        this->freeColor = freeColor;
        update();
    }
}

void QEXTSelectSlider::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor)
    {
        this->textColor = textColor;
        update();
    }
}

void QEXTSelectSlider::setRangeTextColor(const QColor &rangeTextColor)
{
    if (this->rangeTextColor != rangeTextColor)
    {
        this->rangeTextColor = rangeTextColor;
        update();
    }
}

void QEXTSelectSlider::setSliderColor(const QColor &sliderColor)
{
    if (this->sliderColor != sliderColor)
    {
        this->sliderColor = sliderColor;
        update();
    }
}

void QEXTSelectSlider::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor)
    {
        this->borderColor = borderColor;
        update();
    }
}

void QEXTSelectSlider::setBtnNormalColor(const QColor &btnNormalColor)
{
    if (this->btnNormalColor != btnNormalColor)
    {
        this->btnNormalColor = btnNormalColor;
        update();
    }
}

void QEXTSelectSlider::setBtnPressColor(const QColor &btnPressColor)
{
    if (this->btnPressColor != btnPressColor)
    {
        this->btnPressColor = btnPressColor;
        update();
    }
}
