#pragma execution_character_set("utf-8")

#include <qextProgressPie.h>

#include <QPainter>
#include <QDebug>

QEXTProgressPie::QEXTProgressPie(QWidget *parent) : QWidget(parent)
{
    bgColor = Qt::transparent;
    textColor = QColor(255, 255, 255);
    baseColor = QColor(100, 100, 100);
    innerBgColor = QColor(40, 45, 48);
    borderColor = QColor(255, 255, 255);
    progressColor = QColor(34, 163, 169);

    value = 0;
    minValue = 0;
    maxValue = 100;
    precision = 0;

    nullPosition = 90;
    outlinePenWidth = 1;
    dataPenWidth = 2;

    barStyle = BarStyle_Donut;
    format = "%p";
    clockWise = true;

    setFont(QFont("Arial", 8));
}

void QEXTProgressPie::paintEvent(QPaintEvent *)
{
    //半径取宽高的最小值
    double outerRadius = qMin(width(), height());
    //绘制区域在画面区域的基础上上下左右各减少一个像素,使得看起来完整
    QRectF baseRect(2, 2, outerRadius - 4, outerRadius - 4);

    //先将需要绘制的图形绘制到一张图片上,最后将图片绘制到屏幕
    QImage buffer(outerRadius, outerRadius, QImage::Format_ARGB32_Premultiplied);
    buffer.fill(Qt::transparent);

    QPainter painter(&buffer);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制数据颜色集合
    rebuildDataBrushIfNeeded();
    //绘制背景
    drawBg(&painter, buffer.rect());
    //绘制外框
    drawBase(&painter, baseRect);
    //绘制当前进度
    drawProgress(&painter, baseRect);

    //绘制中心
    double innerRadius(0);
    QRectF innerRect;
    calculateInnerRect(baseRect, outerRadius, innerRect, innerRadius);
    drawInnerBackground(&painter, innerRect);

    //绘制当前值
    drawValue(&painter, innerRect, innerRadius);
    painter.end();

    //绘制背景
    QPainter p(this);
    p.setRenderHints(QPainter::SmoothPixmapTransform);
    p.setPen(Qt::NoPen);
    p.setBrush(bgColor);
    p.drawRect(this->rect());

    //改成居中绘制图片
    int pixX = rect().center().x() - buffer.width() / 2;
    int pixY = rect().center().y() - buffer.height() / 2;
    QPoint point(pixX, pixY);
    p.drawImage(point, buffer);
}

void QEXTProgressPie::drawBg(QPainter *painter, const QRectF &baseRect)
{
    painter->fillRect(baseRect,  Qt::transparent);
}

void QEXTProgressPie::drawBase(QPainter *painter, const QRectF &baseRect)
{
    switch (barStyle) {
    case BarStyle_Donut:
        painter->setPen(QPen(baseColor, outlinePenWidth));
        painter->setBrush(baseColor);
        painter->drawEllipse(baseRect);
        break;

    case BarStyle_Pie:
        painter->setPen(QPen(baseColor, outlinePenWidth));
        painter->setBrush(baseColor);
        painter->drawEllipse(baseRect);
        break;

    case BarStyle_Line:
        painter->setPen(QPen(baseColor, outlinePenWidth));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(baseRect.adjusted(outlinePenWidth / 2, outlinePenWidth / 2, -outlinePenWidth / 2, -outlinePenWidth / 2));
        break;
    }
}

void QEXTProgressPie::drawProgress(QPainter *painter, const QRectF &baseRect)
{
    if (value == minValue) {
        return;
    }

    double arcLength = 360.0 / (maxValue - minValue) * value;

    //逆时针为顺时针分负数
    if (!clockWise) {
        arcLength = -arcLength;
    }

    if (barStyle == BarStyle_Line) {
        painter->setPen(QPen(progressColor, dataPenWidth));
        painter->setBrush(Qt::NoBrush);
        painter->drawArc(baseRect.adjusted(outlinePenWidth / 2, outlinePenWidth / 2, -outlinePenWidth / 2, -outlinePenWidth / 2),
                         nullPosition * 16, -arcLength * 16);
        return;
    }

    QPainterPath dataPath;
    dataPath.setFillRule(Qt::WindingFill);

    dataPath.moveTo(baseRect.center());
    dataPath.arcTo(baseRect, nullPosition, -arcLength);
    dataPath.lineTo(baseRect.center());

    painter->setBrush(progressColor);
    painter->setPen(QPen(borderColor, dataPenWidth));
    painter->drawPath(dataPath);
}

void QEXTProgressPie::calculateInnerRect(const QRectF &/*baseRect*/, double outerRadius, QRectF &innerRect, double &innerRadius)
{
    if (barStyle == BarStyle_Line) {
        innerRadius = outerRadius - outlinePenWidth;
    } else {
        innerRadius = outerRadius * 0.75;
    }

    double delta = (outerRadius - innerRadius) / 2;
    innerRect = QRectF(delta, delta, innerRadius, innerRadius);
}

void QEXTProgressPie::drawInnerBackground(QPainter *painter, const QRectF &innerRect)
{
    if (barStyle == BarStyle_Donut) {
        painter->setBrush(innerBgColor);
        painter->drawEllipse(innerRect);
    }
}

void QEXTProgressPie::drawValue(QPainter *painter, const QRectF &innerRect, double innerRadius)
{
    if (format.isEmpty()) {
        return;
    }

    QFont font;
    font.setPixelSize(innerRadius * qMax(0.05, (0.35 - (double)precision * 0.08)));
    painter->setFont(font);

    QRectF textRect(innerRect);
    painter->setPen(textColor);

    QString strValue;
    if (format == "%v") {
        strValue = QString::number(value, 'f', precision);
    } else if (format == "%p") {
        double procent = (value - minValue) / (maxValue - minValue) * 100.0;
        strValue = QString::number(procent, 'f', precision) + "%";
    } else if (format == "%m") {
        strValue = QString::number(maxValue - minValue + 1, 'f', precision) + "m";
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);
}

void QEXTProgressPie::rebuildDataBrushIfNeeded()
{
    if (gradientData.count() == 0) {
        return;
    }

    QConicalGradient dataBrush;
    dataBrush.setCenter(0.5, 0.5);
    dataBrush.setCoordinateMode(QGradient::StretchToDeviceMode);

    for (int i = 0; i < gradientData.count(); i++) {
        dataBrush.setColorAt(1.0 - gradientData.at(i).first, gradientData.at(i).second);
    }

    dataBrush.setAngle(nullPosition);
    QPalette p(palette());
    p.setBrush(QPalette::Highlight, dataBrush);
    setPalette(p);
}

QColor QEXTProgressPie::getBgColor() const
{
    return this->bgColor;
}

QColor QEXTProgressPie::getTextColor() const
{
    return this->textColor;
}

QColor QEXTProgressPie::getBaseColor() const
{
    return this->baseColor;
}

QColor QEXTProgressPie::getInnerBgColor() const
{
    return this->innerBgColor;
}

QColor QEXTProgressPie::getBorderColor() const
{
    return this->borderColor;
}

QColor QEXTProgressPie::getProgressColor() const
{
    return this->progressColor;
}

double QEXTProgressPie::getValue() const
{
    return this->value;
}

double QEXTProgressPie::getMinValue() const
{
    return this->minValue;
}

double QEXTProgressPie::getMaxValue() const
{
    return this->maxValue;
}

int QEXTProgressPie::getPrecision() const
{
    return this->precision;
}

double QEXTProgressPie::getNullPosition() const
{
    return this->nullPosition;
}

double QEXTProgressPie::getOutlinePenWidth() const
{
    return this->outlinePenWidth;
}

double QEXTProgressPie::getDataPenWidth() const
{
    return this->dataPenWidth;
}

QEXTProgressPie::BarStyle QEXTProgressPie::getBarStyle() const
{
    return this->barStyle;
}

QString QEXTProgressPie::getFormat() const
{
    return this->format;
}

bool QEXTProgressPie::getClockWise() const
{
    return this->clockWise;
}

QGradientStops QEXTProgressPie::getGradientData() const
{
    return this->gradientData;
}

QSize QEXTProgressPie::sizeHint() const
{
    return QSize(100, 100);
}

QSize QEXTProgressPie::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QEXTProgressPie::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        this->update();
    }
}

void QEXTProgressPie::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void QEXTProgressPie::setBaseColor(const QColor &baseColor)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;
        this->update();
    }
}

void QEXTProgressPie::setInnerBgColor(const QColor &innerBgColor)
{
    if (this->innerBgColor != innerBgColor) {
        this->innerBgColor = innerBgColor;
        this->update();
    }
}

void QEXTProgressPie::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        this->update();
    }
}

void QEXTProgressPie::setProgressColor(const QColor &progressColor)
{
    if (this->progressColor != progressColor) {
        this->progressColor = progressColor;
        this->update();
    }
}

void QEXTProgressPie::setRange(double minValue, double maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;

    if (this->maxValue < this->minValue) {
        qSwap(this->maxValue, this->minValue);
    }

    if (value < this->minValue) {
        value = this->minValue;
    } else if (value > this->maxValue) {
        value = this->maxValue;
    }

    this->update();
}

void QEXTProgressPie::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void QEXTProgressPie::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void QEXTProgressPie::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void QEXTProgressPie::setValue(double value)
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

    this->value = value;
    this->update();
}

void QEXTProgressPie::setValue(int value)
{
    setValue(double(value));
}

void QEXTProgressPie::setPrecision(int precision)
{
    if (precision >= 0 && this->precision != precision) {
        this->precision = precision;
        this->update();
    }
}

void QEXTProgressPie::setNullPosition(double nullPosition)
{
    if (this->nullPosition != nullPosition) {
        this->nullPosition = nullPosition;
        this->update();
    }
}

void QEXTProgressPie::setBarStyle(const QEXTProgressPie::BarStyle &barStyle)
{
    if (this->barStyle != barStyle) {
        this->barStyle = barStyle;
        this->update();
    }
}

void QEXTProgressPie::setFormat(const QString &format)
{
    if (this->format != format) {
        this->format = format;
        this->update();
    }
}

void QEXTProgressPie::setOutlinePenWidth(double outlinePenWidth)
{
    if (this->outlinePenWidth != outlinePenWidth) {
        this->outlinePenWidth = outlinePenWidth;
        this->update();
    }
}

void QEXTProgressPie::setDataPenWidth(double dataPenWidth)
{
    if (this->dataPenWidth != dataPenWidth) {
        this->dataPenWidth = dataPenWidth;
        this->update();
    }
}

void QEXTProgressPie::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise) {
        this->clockWise = clockWise;
        this->update();
    }
}

void QEXTProgressPie::setGradientData(const QGradientStops &gradientData)
{
    if (this->gradientData != gradientData) {
        this->gradientData = gradientData;
        this->update();
    }
}
