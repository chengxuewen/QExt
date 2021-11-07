#pragma execution_character_set("utf-8")

#include <qextRulerSlider.h>

#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QTimer>
#include <QDebug>

QEXTRulerSlider::QEXTRulerSlider(QWidget *parent) :	QWidget(parent)
{    
    minValue = 0.0;
    maxValue = 100.0;
    value = 0.0;

    precision = 0;
    longStep = 10;
    shortStep = 1;
    space = 20;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(255, 255, 255);

    sliderColorTop = QColor(100, 184, 255);
    sliderColorBottom = QColor(235, 235, 235);

    tipBgColor = QColor(255, 255, 255);
    tipTextColor = QColor(50, 50, 50);

    pressed = false;
    currentValue = 0;
    sliderLastPot = QPointF(space, longLineHeight / 2);

    setFont(QFont("Arial", 8));
}

void QEXTRulerSlider::resizeEvent(QResizeEvent *)
{
    longLineHeight = height() / 5;
    shortLineHeight = height() / 7;
    sliderTopHeight = height() / 7;
    sliderBottomHeight = height() / 6;

    if (this->isVisible()) {
        setValue(currentValue);
    }
}

void QEXTRulerSlider::showEvent(QShowEvent *)
{
    resizeEvent(NULL);
}

void QEXTRulerSlider::wheelEvent(QWheelEvent *e)
{
    //滚动的角度,*8就是鼠标滚动的距离
    int degrees = e->delta() / 8;

    //滚动的步数,*15就是鼠标滚动的角度
    int steps = degrees / 15;

    //如果是正数代表为左边移动,负数代表为右边移动
    if (e->orientation() == Qt::Vertical) {
        double value = currentValue - steps;

        if (steps > 0) {
            if (value > minValue) {
                setValue(value);
            } else {
                setValue(minValue);
            }
        } else {
            if (value < maxValue) {
                setValue(value);
            } else {
                setValue(maxValue);
            }
        }
    }
}

void QEXTRulerSlider::mousePressEvent(QMouseEvent *e)
{
    if (e->button() & Qt::LeftButton) {
        if (sliderRect.contains(e->pos())) {
            pressed = true;
            update();
        }
    }
}

void QEXTRulerSlider::mouseReleaseEvent(QMouseEvent *e)
{
    pressed = false;
    update();
}

void QEXTRulerSlider::mouseMoveEvent(QMouseEvent *e)
{
    if (pressed) {
        if (e->pos().x() >= lineLeftPot.x() && e->pos().x() <= lineRightPot.x()) {
            double totalLineWidth = lineRightPot.x() - lineLeftPot.x();
            double dx = e->pos().x() - lineLeftPot.x();
            double ratio = (double)dx / totalLineWidth;
            sliderLastPot = QPointF(e->pos().x(), sliderTopPot.y());

            currentValue = (maxValue - minValue) * ratio + minValue;
            this->value = currentValue;
            emit valueChanged(currentValue);
            update();
        }
    }
}

void QEXTRulerSlider::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制标尺
    drawRule(&painter);
    //绘制滑块
    drawSlider(&painter);
    //绘制当前值的提示
    drawTip(&painter);
}

void QEXTRulerSlider::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, 0, 0, height());
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void QEXTRulerSlider::drawRule(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    //绘制横向标尺底部线,居中
    double initX = space;
    double initY = (double)height() / 2;
    lineLeftPot = QPointF(initX, initY);
    lineRightPot = QPointF(width() - initX, initY);
    painter->drawLine(lineLeftPot, lineRightPot);

    //绘制纵向标尺刻度
    double length = width() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);

    //根据范围值绘制刻度值及刻度值
    for (int i = minValue; i <= maxValue; i = i + shortStep) {
        if (i % longStep == 0) {
            QPointF topPot(initX, initY - longLineHeight);
            QPointF bottomPot(initX, initY);
            painter->drawLine(topPot, bottomPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();
            QPointF textPot(initX - textWidth / 2, initY + textHeight);
            painter->drawText(textPot, strValue);
        } else {
            QPointF topPot(initX, initY - shortLineHeight);
            QPointF bottomPot(initX, initY);
            painter->drawLine(topPot, bottomPot);
        }

        initX += increment * shortStep;
    }

    painter->restore();
}

void QEXTRulerSlider::drawSlider(QPainter *painter)
{
    painter->save();

    //绘制滑块上部分三角形
    sliderTopPot = QPointF(sliderLastPot.x(), lineLeftPot.y() - longLineHeight / 4);
    sliderLeftPot = QPointF(sliderTopPot.x() - width() / 100, sliderTopPot.y() + sliderTopHeight);
    sliderRightPot = QPointF(sliderTopPot.x() + width() / 100, sliderTopPot.y() + sliderTopHeight);

    painter->setPen(sliderColorTop);
    painter->setBrush(sliderColorTop);

    QVector<QPointF> potVec;
    potVec.append(sliderTopPot);
    potVec.append(sliderLeftPot);
    potVec.append(sliderRightPot);
    painter->drawPolygon(potVec);

    //绘制滑块下部分矩形
    double indicatorLength = sliderRightPot.x() - sliderLeftPot.x();

    QPointF handleBottomRightPot(sliderLeftPot.x() + indicatorLength, sliderLeftPot.y() + sliderBottomHeight);
    sliderRect = QRectF(sliderLeftPot, handleBottomRightPot);

    QPointF tipRectTopLeftPot(sliderRect.topRight().x() + 2, sliderRect.topRight().y());
    QString strValue = QString("%1").arg(currentValue, 0, 'f', precision);

    double textLength = fontMetrics().width(strValue);
    double textHeight = fontMetrics().height();
    QPointF tipRectBottomRightPot(tipRectTopLeftPot.x() + textLength + 10, tipRectTopLeftPot.y() + textHeight + 5);
    tipRect = QRectF(tipRectTopLeftPot, tipRectBottomRightPot);

    painter->setPen(sliderColorBottom);
    painter->setBrush(sliderColorBottom);
    painter->drawRect(sliderRect);
    painter->restore();
}

void QEXTRulerSlider::drawTip(QPainter *painter)
{
    if (!pressed) {
        return;
    }

    painter->save();
    painter->setPen(tipTextColor);
    painter->setBrush(tipBgColor);
    painter->drawRect(tipRect);
    QString strValue = QString("%1").arg(currentValue, 0, 'f', precision);
    painter->drawText(tipRect, Qt::AlignCenter, strValue);
    painter->restore();
}

double QEXTRulerSlider::getMinValue() const
{
    return this->minValue;
}

double QEXTRulerSlider::getMaxValue() const
{
    return this->maxValue;
}

double QEXTRulerSlider::getValue() const
{
    return this->value;
}

int QEXTRulerSlider::getPrecision() const
{
    return this->precision;
}

int QEXTRulerSlider::getLongStep() const
{
    return this->longStep;
}

int QEXTRulerSlider::getShortStep() const
{
    return this->shortStep;
}

int QEXTRulerSlider::getSpace() const
{
    return this->space;
}

QColor QEXTRulerSlider::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor QEXTRulerSlider::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor QEXTRulerSlider::getLineColor() const
{
    return this->lineColor;
}

QColor QEXTRulerSlider::getSliderColorTop() const
{
    return this->sliderColorTop;
}

QColor QEXTRulerSlider::getSliderColorBottom() const
{
    return this->sliderColorBottom;
}

QColor QEXTRulerSlider::getTipBgColor() const
{
    return this->tipBgColor;
}

QColor QEXTRulerSlider::getTipTextColor() const
{
    return this->tipTextColor;
}

QSize QEXTRulerSlider::sizeHint() const
{
    return QSize(500, 70);
}

QSize QEXTRulerSlider::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QEXTRulerSlider::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;
    setValue(minValue);
}

void QEXTRulerSlider::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void QEXTRulerSlider::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void QEXTRulerSlider::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void QEXTRulerSlider::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    double lineWidth = width() - 2 * space;
    double ratio = (double)(value - minValue) / (maxValue - minValue);
    double x = lineWidth * ratio;
    double newX = x + space;
    double y = space + longLineHeight - 10;
    sliderLastPot = QPointF(newX, y);

    this->value = value;
    this->currentValue = value;
    emit valueChanged(value);
    update();
}

void QEXTRulerSlider::setValue(int value)
{
    setValue((double)value);
}

void QEXTRulerSlider::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void QEXTRulerSlider::setLongStep(int longStep)
{
    //短步长不能超过长步长
    if (longStep < shortStep) {
        return;
    }

    if (this->longStep != longStep) {
        this->longStep = longStep;
        update();
    }
}

void QEXTRulerSlider::setShortStep(int shortStep)
{
    //短步长不能超过长步长
    if (longStep < shortStep) {
        return;
    }

    if (this->shortStep != shortStep) {
        this->shortStep = shortStep;
        update();
    }
}

void QEXTRulerSlider::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void QEXTRulerSlider::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void QEXTRulerSlider::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void QEXTRulerSlider::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void QEXTRulerSlider::setSliderColorTop(const QColor &sliderColorTop)
{
    if (this->sliderColorTop != sliderColorTop) {
        this->sliderColorTop = sliderColorTop;
        update();
    }
}

void QEXTRulerSlider::setSliderColorBottom(const QColor &sliderColorBottom)
{
    if (this->sliderColorBottom != sliderColorBottom) {
        this->sliderColorBottom = sliderColorBottom;
        update();
    }
}

void QEXTRulerSlider::setTipBgColor(const QColor &tipBgColor)
{
    if (this->tipBgColor != tipBgColor) {
        this->tipBgColor = tipBgColor;
        update();
    }
}

void QEXTRulerSlider::setTipTextColor(const QColor &tipTextColor)
{
    if (this->tipTextColor != tipTextColor) {
        this->tipTextColor = tipTextColor;
        update();
    }
}
