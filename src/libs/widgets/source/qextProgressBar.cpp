#include <qextProgressBar.h>
#include <QPainter>
#include <QTimer>
#include <QDebug>

QEXTProgressBar::QEXTProgressBar(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;

    precision = 0;
    step = 0;
    space = 5;
    radius = 5;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);

    lineColor = QColor(230, 230, 230);
    textColor = QColor(0, 0, 0);

    barBgColor = QColor(250, 250, 250);
    barColor = QColor(100, 184, 255);

    setFont(QFont("Arial", 8));
}

void QEXTProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    drawBar(&painter);
}

void QEXTProgressBar::drawBg(QPainter *painter)
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

void QEXTProgressBar::drawBar(QPainter *painter)
{
    painter->save();

    QFont font;
    font.setPixelSize((width() / 10) * 0.35);
    painter->setFont(font);

    double currentValue = (double)(value - minValue) * 100 / (maxValue - minValue);
    QString strValue = QString("%1%").arg(currentValue, 0, 'f', precision);
    QString strMaxValue = QString("%1%").arg(maxValue, 0, 'f', precision);

    int textWidth = painter->fontMetrics().width(strMaxValue) + 10;

    QPointF textTopLeft(width() - space - textWidth, space);
    QPointF textBottomRight(width() - space, height() - space);
    QRectF textRect(textTopLeft, textBottomRight);
    painter->setPen(barBgColor);
    painter->setBrush(barBgColor);
    painter->drawRoundedRect(textRect, radius, radius);

    painter->setPen(textColor);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    QRectF barBgRect(QPointF(space, space), QPointF(width() - space * 2 - textWidth, height() - space));
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBgColor);
    painter->drawRoundedRect(barBgRect, radius, radius);

    double length = width() - space  - space * 2 - textWidth;

    double increment = length / (maxValue - minValue);
    QRectF barRect(QPointF(space, space), QPointF(space + increment * (value - minValue), height() - space));
    painter->setBrush(barColor);
    painter->drawRoundedRect(barRect, radius, radius);

    painter->setPen(lineColor);
    int initX = 5;
    int lineCount = barBgRect.width() / step;
    double lineX = (double)barBgRect.width() / lineCount;

    while (lineCount > 0) {
        QPointF topPot(initX + lineX, space + 1);
        QPointF bottomPot(initX + lineX, height() - space - 1);
        painter->drawLine(topPot, bottomPot);
        initX += lineX;
        lineCount--;
    }

    painter->restore();
}

double QEXTProgressBar::getMinValue() const
{
    return this->minValue;
}

double QEXTProgressBar::getMaxValue() const
{
    return this->maxValue;
}

double QEXTProgressBar::getValue() const
{
    return this->value;
}

int QEXTProgressBar::getPrecision() const
{
    return this->precision;
}

int QEXTProgressBar::getStep() const
{
    return this->step;
}

int QEXTProgressBar::getSpace() const
{
    return this->space;
}

int QEXTProgressBar::getRadius() const
{
    return this->radius;
}

QColor QEXTProgressBar::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor QEXTProgressBar::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor QEXTProgressBar::getLineColor() const
{
    return this->lineColor;
}

QColor QEXTProgressBar::getTextColor() const
{
    return this->textColor;
}

QColor QEXTProgressBar::getBarBgColor() const
{
    return this->barBgColor;
}

QColor QEXTProgressBar::getBarColor() const
{
    return this->barColor;
}

QSize QEXTProgressBar::sizeHint() const
{
    return QSize(300, 30);
}

QSize QEXTProgressBar::minimumSizeHint() const
{
    return QSize(50, 20);
}

void QEXTProgressBar::setRange(double minValue, double maxValue)
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

void QEXTProgressBar::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void QEXTProgressBar::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void QEXTProgressBar::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void QEXTProgressBar::setValue(double value)
{
    if (value == this->value) {
        return;
    }

    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    this->value = value;
    emit valueChanged(value);
    update();
}

void QEXTProgressBar::setValue(int value)
{
    setValue((double)value);
}

void QEXTProgressBar::setPrecision(int precision)
{
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void QEXTProgressBar::setStep(int step)
{
    if (this->step != step) {
        this->step = step;
        update();
    }
}

void QEXTProgressBar::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void QEXTProgressBar::setRadius(int radius)
{
    if (this->radius != radius) {
        this->radius = radius;
        update();
    }
}

void QEXTProgressBar::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void QEXTProgressBar::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        update();
    }
}

void QEXTProgressBar::setLineColor(QColor lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void QEXTProgressBar::setTextColor(QColor textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void QEXTProgressBar::setBarBgColor(QColor barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        update();
    }
}

void QEXTProgressBar::setBarColor(QColor barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        update();
    }
}
