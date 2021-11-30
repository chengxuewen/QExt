#include <qextThermometer.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>

QEXTThermometer::QEXTThermometer(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    precision = 0;
    longStep = 10;
    shortStep = 2;
    space = 10;

    animation = false;
    animationStep = 1.0;

    showUserValue = false;
    userValue = 80;
    userValueColor = QColor(255, 107, 107);

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(255, 255, 255);

    barBgColor = QColor(230, 230, 230);
    barColor = QColor(100, 184, 255);

    barPosition = BarPosition_Center;
    tickPosition = TickPosition_Both;

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 9));
    resizeEvent(NULL);
}

QEXTThermometer::~QEXTThermometer()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void QEXTThermometer::resizeEvent(QResizeEvent *)
{
    radius = qMin(width(), height()) / 5;
    barWidth = (radius * 2) / 3;
    barHeight = height() - radius * 2;

    if (barPosition == BarPosition_Left) {
        targetX = width() / 4;
    } else if (barPosition == BarPosition_Right) {
        targetX = width() / 1.3;
    } else if (barPosition == BarPosition_Center) {
        targetX = width() / 2;
    }

    setValue(value);
}

void QEXTThermometer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    drawBg(&painter);

    if (tickPosition == TickPosition_Left) {
        drawRuler(&painter, 0);
    } else if (tickPosition == TickPosition_Right) {
        drawRuler(&painter, 1);
    } else if (tickPosition == TickPosition_Both) {
        drawRuler(&painter, 0);
        drawRuler(&painter, 1);
    }

    drawBarBg(&painter);

    drawBar(&painter);

    drawValue(&painter);
}

void QEXTThermometer::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void QEXTThermometer::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBgColor);

    int barX = targetX - barWidth / 2;
    int barY = space;
    QRectF barRect(barX, barY, barWidth, barHeight);

    int circleX = targetX - radius;
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2;
    QRectF circleRect(circleX, circleY, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);
    painter->restore();
}

void QEXTThermometer::drawRuler(QPainter *painter, int type)
{
    painter->save();
    painter->setPen(lineColor);

    int barPercent = barWidth / 8;

    if (barPercent < 2) {
        barPercent = 2;
    }

    double length = height() - 2 * space - 2 * radius;

    double increment = length / (maxValue - minValue);

    int longLineLen = 10;
    int shortLineLen = 7;

    int offset = barWidth / 2 + 5;

    if (type == 0) {
        offset = -offset;
        longLineLen = -longLineLen;
        shortLineLen = -shortLineLen;
    }

    double initX = targetX + offset;
    double initY = space + barPercent;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - 2 * radius - 5);
    painter->drawLine(topPot, bottomPot);

    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double fontHeight = painter->fontMetrics().height();

            if (type == 0) {
                QRect textRect(initX - 45, initY - fontHeight / 3, 30, 15);
                painter->drawText(textRect, Qt::AlignRight, strValue);
            } else if (type == 1) {
                QRect textRect(initX + longLineLen + 5, initY - fontHeight / 3, 30, 15);
                painter->drawText(textRect, Qt::AlignLeft, strValue);
            }
        } else {
            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void QEXTThermometer::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);

    int barPercent = barWidth / 8;
    int circlePercent = radius / 6;

    if (barPercent < 2) {
        barPercent = 2;
    }

    if (circlePercent < 2) {
        circlePercent = 2;
    }

    double length = height() - 2 * space - 2 * radius;

    double increment = length / (maxValue - minValue);

    int rulerHeight = height() - 1 * space - 2 * radius;

    int barX = targetX - barWidth / 2;
    int barY = rulerHeight - (currentValue - minValue) * increment;
    barRect = QRectF(barX + barPercent, barY + barPercent, barWidth - barPercent * 2, barHeight + radius - barY);

    int circleX = targetX - radius;
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2 - circlePercent * 2;
    circleRect = QRectF(circleX + circlePercent, circleY + circlePercent, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);

    if (showUserValue) {
        if (tickPosition == TickPosition_Left || tickPosition == TickPosition_Both) {
            QPolygon pts;
            int offset = 15;
            double initX = targetX - (barWidth / 2 + 5);
            double initY = rulerHeight - (userValue - minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX - offset, initY - offset / 2));
            pts.append(QPoint(initX - offset, initY + offset / 2));
            painter->setBrush(userValueColor);
            painter->drawPolygon(pts);
        }

        if (tickPosition == TickPosition_Right || tickPosition == TickPosition_Both) {
            QPolygon pts;
            int offset = 15;
            double initX = targetX + (barWidth / 2 + 5);
            double initY = rulerHeight - (userValue - minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX + offset, initY - offset / 2));
            pts.append(QPoint(initX + offset, initY + offset / 2));
            painter->setBrush(userValueColor);
            painter->drawPolygon(pts);
        }
    }

    painter->restore();
}

void QEXTThermometer::drawValue(QPainter *painter)
{
    painter->save();

    QFont font;
    font.setPixelSize(circleRect.width() * 0.55);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(circleRect, Qt::AlignCenter, QString("%1").arg(currentValue));

    painter->restore();
}

double QEXTThermometer::getMinValue() const
{
    return this->minValue;
}

double QEXTThermometer::getMaxValue() const
{
    return this->maxValue;
}

double QEXTThermometer::getValue() const
{
    return this->value;
}

int QEXTThermometer::getPrecision() const
{
    return this->precision;
}

int QEXTThermometer::getLongStep() const
{
    return this->longStep;
}

int QEXTThermometer::getShortStep() const
{
    return this->shortStep;
}

int QEXTThermometer::getSpace() const
{
    return this->space;
}

bool QEXTThermometer::getAnimation() const
{
    return this->animation;
}

double QEXTThermometer::getAnimationStep() const
{
    return this->animationStep;
}

bool QEXTThermometer::getShowUserValue() const
{
    return this->showUserValue;
}

double QEXTThermometer::getUserValue() const
{
    return this->userValue;
}

QColor QEXTThermometer::getUserValueColor() const
{
    return this->userValueColor;
}

QColor QEXTThermometer::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor QEXTThermometer::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor QEXTThermometer::getLineColor() const
{
    return this->lineColor;
}

QColor QEXTThermometer::getBarBgColor() const
{
    return this->barBgColor;
}

QColor QEXTThermometer::getBarColor() const
{
    return this->barColor;
}

QEXTThermometer::BarPosition QEXTThermometer::getBarPosition() const
{
    return this->barPosition;
}

QEXTThermometer::TickPosition QEXTThermometer::getTickPosition() const
{
    return this->tickPosition;
}

QSize QEXTThermometer::sizeHint() const
{
    return QSize(130, 350);
}

QSize QEXTThermometer::minimumSizeHint() const
{
    return QSize(20, 50);
}

void QEXTThermometer::setRange(double minValue, double maxValue)
{
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    if (value < minValue || value > maxValue) {
        setValue(value);
    }

    update();
}

void QEXTThermometer::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void QEXTThermometer::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void QEXTThermometer::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void QEXTThermometer::setValue(double value)
{
    if (value == this->value) {
        return;
    }

    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    if (value > this->value) {
        reverse = false;
    } else if (value < this->value) {
        reverse = true;
    }

    this->value = value;
    emit valueChanged(value);

    if (!animation) {
        currentValue = this->value;
        update();
    } else {
        timer->start();
    }
}

void QEXTThermometer::setValue(int value)
{
    setValue((double)value);
}

void QEXTThermometer::setPrecision(int precision)
{
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void QEXTThermometer::setLongStep(int longStep)
{
    if (longStep < shortStep) {
        return;
    }

    if (this->longStep != longStep) {
        this->longStep = longStep;
        update();
    }
}

void QEXTThermometer::setShortStep(int shortStep)
{
    if (longStep < shortStep) {
        return;
    }

    if (this->shortStep != shortStep) {
        this->shortStep = shortStep;
        update();
    }
}

void QEXTThermometer::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void QEXTThermometer::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        update();
    }
}

void QEXTThermometer::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        update();
    }
}

void QEXTThermometer::setShowUserValue(bool showUserValue)
{
    if (this->showUserValue != showUserValue) {
        this->showUserValue = showUserValue;
        update();
    }
}

void QEXTThermometer::setUserValue(double userValue)
{
    if (userValue < minValue || userValue > maxValue) {
        return;
    }

    if (this->userValue != userValue) {
        this->userValue = userValue;
        update();
    }
}

void QEXTThermometer::setUserValue(int userValue)
{
    setUserValue((double)userValue);
}

void QEXTThermometer::setUserValueColor(const QColor &userValueColor)
{
    if (this->userValueColor != userValueColor) {
        this->userValueColor = userValueColor;
        update();
    }
}

void QEXTThermometer::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void QEXTThermometer::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void QEXTThermometer::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void QEXTThermometer::setBarBgColor(const QColor &barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        update();
    }
}

void QEXTThermometer::setBarColor(const QColor &barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        update();
    }
}

void QEXTThermometer::setBarPosition(const QEXTThermometer::BarPosition &barPosition)
{
    if (this->barPosition != barPosition) {
        this->barPosition = barPosition;
        update();
    }
}

void QEXTThermometer::setTickPosition(const QEXTThermometer::TickPosition &tickPosition)
{
    if (this->tickPosition != tickPosition) {
        this->tickPosition = tickPosition;
        update();
    }
}

void QEXTThermometer::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    update();
}
