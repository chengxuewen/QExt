#pragma execution_character_set("utf-8")

#include <qextSelectSlider.h>
#include <qextSelectSlider_p.h>

#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <qmath.h>


QEXTSelectSliderPrivate::QEXTSelectSliderPrivate(QEXTSelectSlider *q)
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

QEXTSelectSliderPrivate::~QEXTSelectSliderPrivate()
{

}




QEXTSelectSlider::QEXTSelectSlider(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTSelectSliderPrivate(this))
{
    this->setFont(QFont("Arial", 10));
}

QEXTSelectSlider::~QEXTSelectSlider()
{

}

void QEXTSelectSlider::resizeEvent(QResizeEvent *)
{
    QEXT_DECL_D(QEXTSelectSlider);
    d->m_leftBtnRect = QRect(d->m_borderWidth, d->m_sliderHeight, d->m_buttonWidth - d->m_borderWidth * 2, height() - d->m_sliderHeight);
    d->m_rightBtnRect = QRect(this->width() - d->m_buttonWidth + d->m_borderWidth, d->m_sliderHeight, d->m_buttonWidth - d->m_borderWidth * 2, height() - d->m_sliderHeight);
    this->updateUI();
}

void QEXTSelectSlider::mousePressEvent(QMouseEvent *e)
{
    QEXT_DECL_D(QEXTSelectSlider);
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

void QEXTSelectSlider::mouseMoveEvent(QMouseEvent *e)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_sliderPress)
    {
        d->m_posMove = e->pos();
        int dx = d->m_posMove.x() - d->m_posPress.x();
        QRect rc = d->m_sliderRectTemp;

        if(rc.left() + dx <= d->m_buttonWidth)
        {
            //左侧超出
            d->m_sliderRect.moveLeft(d->m_buttonWidth);
            d->m_leftValue = d->m_minValue;
        }
        else if(rc.right() + dx >= width() - d->m_buttonWidth)
        {
            //右侧超出
            d->m_sliderRect.moveRight(width() - d->m_buttonWidth);
            d->m_leftValue = d->m_maxValue - d->m_rangeValue;
        }
        else
        {
            //正常拖动
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
            //左侧超出
            d->m_leftRect.moveLeft(d->m_buttonWidth - 15);
            d->m_leftValue = d->m_minValue;
        }
        else if(rc.x() + dx >= d->m_rightRect.x())
        {
            //右侧碰到右滑块,不让继续滑
            d->m_leftRect.moveLeft(d->m_rightRect.x());
            d->m_leftValue = d->m_rightValue;
        }
        else
        {
            //正常拖动
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
            //左侧碰到左滑块
            d->m_rightRect.moveLeft(d->m_leftRect.x());
            d->m_rangeValue = 0;
        }
        else if(rc.right() + dx >= width() - d->m_buttonWidth + 15)
        {
            //右侧超出
            d->m_rightRect.moveRight(width() - d->m_buttonWidth + 15);
            d->m_rangeValue = d->m_maxValue - d->m_leftValue;
        }
        else
        {
            //正常拖动
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

void QEXTSelectSlider::mouseReleaseEvent(QMouseEvent *e)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if(e->button() == Qt::LeftButton)
    {
        d->m_sliderPress = false;
        d->m_leftButtonPress = false;
        d->m_rightButtonPress = false;
        this->update();
    }
}

void QEXTSelectSlider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    this->drawBackground(&painter);
    //绘制范围值
    this->drawValue(&painter);
    //绘制左右按钮
    this->drawButton(&painter);
    //绘制左右滑块
    this->drawSlider(&painter);
}

void QEXTSelectSlider::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTSelectSlider);
    painter->save();

    QPen pen;
    pen.setWidthF(d->m_borderWidth);
    pen.setColor(d->m_borderColor);
    painter->setPen(pen);

    painter->setBrush(d->m_freeColor);
    painter->drawRect(d->m_borderWidth, d->m_sliderHeight, width() - d->m_borderWidth * 2, height() - d->m_sliderHeight - d->m_borderWidth);

    painter->restore();
}

void QEXTSelectSlider::drawValue(QPainter *painter)
{
    QEXT_DECL_D(QEXTSelectSlider);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_usedColor);
    painter->drawRect(d->m_sliderRect);

    painter->setPen(d->m_textColor);
    painter->drawText(d->m_sliderRect, Qt::AlignCenter, QString::number(d->m_rangeValue));

    painter->restore();
}

void QEXTSelectSlider::drawButton(QPainter *painter)
{
    QEXT_DECL_D(QEXTSelectSlider);
    painter->save();

    QPolygon polygon;

    //左侧三角箭头
    polygon.clear();
    polygon << QPoint(d->m_leftBtnRect.x() + d->m_leftBtnRect.width() / 4, d->m_leftBtnRect.y() + d->m_leftBtnRect.height() / 2);
    polygon << QPoint(d->m_leftBtnRect.x() + d->m_leftBtnRect.width() * 3 / 4, d->m_leftBtnRect.y() + d->m_leftBtnRect.height() / 2 - 5);
    polygon << QPoint(d->m_leftBtnRect.x() + d->m_leftBtnRect.width() * 3 / 4, d->m_leftBtnRect.y() + d->m_leftBtnRect.height() / 2 + 5);

    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_leftButtonPress ? d->m_buttonPressColor : d->m_buttonNormalColor);
    painter->drawConvexPolygon(polygon);

    //右侧三角箭头
    polygon.clear();
    polygon << QPoint(d->m_rightBtnRect.x() + d->m_rightBtnRect.width() / 4, d->m_rightBtnRect.y() + d->m_rightBtnRect.height() / 2 - 5);
    polygon << QPoint(d->m_rightBtnRect.x() + d->m_rightBtnRect.width() / 4, d->m_rightBtnRect.y() + d->m_rightBtnRect.height() / 2 + 5);
    polygon << QPoint(d->m_rightBtnRect.x() + d->m_rightBtnRect.width() * 3 / 4, d->m_rightBtnRect.y() + d->m_rightBtnRect.height() / 2);

    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_rightButtonPress ? d->m_buttonPressColor : d->m_buttonNormalColor);
    painter->drawConvexPolygon(polygon);

    painter->restore();
}

void QEXTSelectSlider::drawSlider(QPainter *painter)
{
    QEXT_DECL_D(QEXTSelectSlider);
    painter->save();

    //左侧滑块
    painter->setPen(d->m_sliderColor.light(100));
    painter->setBrush(d->m_sliderColor);
    painter->drawRect(d->m_leftRect);
    painter->drawLine(d->m_leftRect.x(), 20, d->m_leftRect.x() + 15, 30);
    painter->drawLine(d->m_leftRect.right(), 20, d->m_leftRect.x() + 15, 30);
    painter->setPen(d->m_rangeTextColor);
    painter->drawText(d->m_leftRect, Qt::AlignCenter, QString::number(d->m_leftValue));

    //右侧滑块
    painter->setPen(d->m_sliderColor.light(100));
    painter->setBrush(d->m_sliderColor);
    painter->drawRect(d->m_rightRect);
    painter->drawLine(d->m_rightRect.x(), 20, d->m_rightRect.x() + 15, 30);
    painter->drawLine(d->m_rightRect.right(), 20, d->m_rightRect.x() + 15, 30);
    painter->setPen(d->m_rangeTextColor);
    painter->drawText(d->m_rightRect, Qt::AlignCenter, QString::number(d->m_rightValue));

    painter->restore();
}

void QEXTSelectSlider::updateUI()
{
    QEXT_DECL_D(QEXTSelectSlider);
    double w1 = ((double)(width() - d->m_buttonWidth * 2)) / ((double)(d->m_maxValue - d->m_minValue));
    d->m_sliderRect = QRect(d->m_buttonWidth + (d->m_leftValue - d->m_minValue) * w1, d->m_sliderHeight + d->m_borderWidth / 2, d->m_rangeValue * w1 - d->m_borderWidth, height() - d->m_sliderHeight - d->m_borderWidth * 2);

    //主滑块右侧越界，保持页宽和滑块右侧不动，把左侧的起点左移
    if(d->m_sliderRect.right() > width() - d->m_buttonWidth)
    {
        d->m_sliderRect.moveLeft(width() - d->m_buttonWidth - d->m_sliderRect.width());
        d->m_leftValue = d->m_minValue + (double)(d->m_sliderRect.x() - d->m_buttonWidth) * w1;
    }

    d->m_leftRect = QRect(d->m_sliderRect.x() - 15, 0, 30, 20);
    d->m_rightRect = QRect(d->m_sliderRect.right() - 15, 0, 30, 20);

    this->update();
}

int QEXTSelectSlider::minValue() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_minValue;
}

int QEXTSelectSlider::maxValue() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_maxValue;
}

int QEXTSelectSlider::leftValue() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_leftValue;
}

int QEXTSelectSlider::rightValue() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_rightValue;
}

int QEXTSelectSlider::rangeValue() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_rangeValue;
}

int QEXTSelectSlider::step() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_step;
}

int QEXTSelectSlider::borderWidth() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_borderWidth;
}

bool QEXTSelectSlider::horizontal() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_horizontal;
}

QColor QEXTSelectSlider::usedColor() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_usedColor;
}

QColor QEXTSelectSlider::freeColor() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_freeColor;
}

QColor QEXTSelectSlider::textColor() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_textColor;
}

QColor QEXTSelectSlider::rangeTextColor() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_rangeTextColor;
}

QColor QEXTSelectSlider::sliderColor() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_sliderColor;
}

QColor QEXTSelectSlider::borderColor() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_borderColor;
}

QColor QEXTSelectSlider::buttonNormalColor() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_buttonNormalColor;
}

QColor QEXTSelectSlider::buttonPressColor() const
{
    QEXT_DECL_DC(QEXTSelectSlider);
    return d->m_buttonPressColor;
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
    QEXT_DECL_D(QEXTSelectSlider);
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue)
    {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
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

void QEXTSelectSlider::setMinValue(int minValue)
{
    QEXT_DECL_D(QEXTSelectSlider);
    this->setRange(minValue, d->m_maxValue);
}

void QEXTSelectSlider::setMaxValue(int maxValue)
{
    QEXT_DECL_D(QEXTSelectSlider);
    this->setRange(d->m_minValue, maxValue);
}

void QEXTSelectSlider::setCurrentRange(int leftValue, int rightValue)
{
    QEXT_DECL_D(QEXTSelectSlider);
    //左边值不能大于右边值
    if (leftValue > rightValue)
    {
        return;
    }

    //左边值不能小于最小值,右边值不能大于最大值
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

void QEXTSelectSlider::setLeftValue(int leftValue)
{
    QEXT_DECL_D(QEXTSelectSlider);
    this->setCurrentRange(leftValue, d->m_rightValue);
}

void QEXTSelectSlider::setRightValue(int rightValue)
{
    QEXT_DECL_D(QEXTSelectSlider);
    this->setCurrentRange(d->m_leftValue, rightValue);
}

void QEXTSelectSlider::setRangeValue(int rangeValue)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_rangeValue != rangeValue)
    {
        d->m_rangeValue = rangeValue;
        setRightValue(d->m_leftValue + rangeValue);
    }
}

void QEXTSelectSlider::setStep(int step)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_step != step)
    {
        d->m_step = step;
    }
}

void QEXTSelectSlider::setBorderWidth(int borderWidth)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_borderWidth != borderWidth)
    {
        d->m_borderWidth = borderWidth;
        this->update();
    }
}

void QEXTSelectSlider::setHorizontal(bool horizontal)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_horizontal != horizontal)
    {
        d->m_horizontal = horizontal;
        this->update();
    }
}

void QEXTSelectSlider::setUsedColor(const QColor &usedColor)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_usedColor != usedColor)
    {
        d->m_usedColor = usedColor;
        this->update();
    }
}

void QEXTSelectSlider::setFreeColor(const QColor &freeColor)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_freeColor != freeColor)
    {
        d->m_freeColor = freeColor;
        this->update();
    }
}

void QEXTSelectSlider::setTextColor(const QColor &textColor)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_textColor != textColor)
    {
        d->m_textColor = textColor;
        this->update();
    }
}

void QEXTSelectSlider::setRangeTextColor(const QColor &rangeTextColor)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_rangeTextColor != rangeTextColor)
    {
        d->m_rangeTextColor = rangeTextColor;
        this->update();
    }
}

void QEXTSelectSlider::setSliderColor(const QColor &sliderColor)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_sliderColor != sliderColor)
    {
        d->m_sliderColor = sliderColor;
        this->update();
    }
}

void QEXTSelectSlider::setBorderColor(const QColor &borderColor)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_borderColor != borderColor)
    {
        d->m_borderColor = borderColor;
        this->update();
    }
}

void QEXTSelectSlider::setButtonNormalColor(const QColor &btnNormalColor)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_buttonNormalColor != btnNormalColor)
    {
        d->m_buttonNormalColor = btnNormalColor;
        this->update();
    }
}

void QEXTSelectSlider::setButtonPressColor(const QColor &btnPressColor)
{
    QEXT_DECL_D(QEXTSelectSlider);
    if (d->m_buttonPressColor != btnPressColor)
    {
        d->m_buttonPressColor = btnPressColor;
        this->update();
    }
}
