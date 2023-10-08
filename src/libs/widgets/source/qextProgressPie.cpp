#include <private/qextProgressPie_p.h>

#include <QPainter>
#include <QPainterPath>
#include <QDebug>


QEXTProgressPiePrivate::QEXTProgressPiePrivate(QEXTProgressPie *q)
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

    m_barStyle = QEXTProgressPie::BarStyle_Pie;
    m_format = "%p";
    m_clockWise = true;
}

QEXTProgressPiePrivate::~QEXTProgressPiePrivate()
{

}



QEXTProgressPie::QEXTProgressPie(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QEXTProgressPiePrivate(this))
{
    this->setFont(QFont("Arial", 8));
}

QEXTProgressPie::~QEXTProgressPie()
{

}

void QEXTProgressPie::paintEvent(QPaintEvent *)
{
    Q_D(QEXTProgressPie);
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

void QEXTProgressPie::drawBackground(QPainter *painter, const QRectF &baseRect)
{
    painter->fillRect(baseRect,  Qt::transparent);
}

void QEXTProgressPie::drawBase(QPainter *painter, const QRectF &baseRect)
{
    Q_D(QEXTProgressPie);
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

void QEXTProgressPie::drawProgress(QPainter *painter, const QRectF &baseRect)
{
    Q_D(QEXTProgressPie);
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

void QEXTProgressPie::calculateInnerRect(const QRectF &/*baseRect*/, double outerRadius, QRectF &innerRect, double &innerRadius)
{
    //    if (barStyle == BarStyle_Line) {
    //        innerRadius = outerRadius - outlinePenWidth;
    //    } else {
    innerRadius = outerRadius * 0.75;
    //    }

    double delta = (outerRadius - innerRadius) / 2;
    innerRect = QRectF(delta, delta, innerRadius, innerRadius);
}

//void QEXTProgressPie::drawInnerBackground(QPainter *painter, const QRectF &innerRect)
//{
////    if (barStyle == BarStyle_Donut) {
//        painter->setBrush(innerBgColor);
//        painter->drawEllipse(innerRect);
////    }
//}

void QEXTProgressPie::drawValue(QPainter *painter, const QRectF &innerRect, double innerRadius)
{
    Q_D(QEXTProgressPie);
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

void QEXTProgressPie::rebuildDataBrushIfNeeded()
{
    Q_D(QEXTProgressPie);
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

QColor QEXTProgressPie::backgroundColor() const
{
    Q_D(const QEXTProgressPie);
    return d->m_backgroundColor;
}

QColor QEXTProgressPie::textColor() const
{
    Q_D(const QEXTProgressPie);
    return d->m_textColor;
}

QColor QEXTProgressPie::baseColor() const
{
    Q_D(const QEXTProgressPie);
    return d->m_baseColor;
}

QColor QEXTProgressPie::innerBgColor() const
{
    Q_D(const QEXTProgressPie);
    return d->m_innerBackgroundColor;
}

QColor QEXTProgressPie::borderColor() const
{
    Q_D(const QEXTProgressPie);
    return d->m_borderColor;
}

QColor QEXTProgressPie::progressColor() const
{
    Q_D(const QEXTProgressPie);
    return d->m_progressColor;
}

double QEXTProgressPie::value() const
{
    Q_D(const QEXTProgressPie);
    return d->m_value;
}

double QEXTProgressPie::minValue() const
{
    Q_D(const QEXTProgressPie);
    return d->m_minValue;
}

double QEXTProgressPie::maxValue() const
{
    Q_D(const QEXTProgressPie);
    return d->m_maxValue;
}

int QEXTProgressPie::precision() const
{
    Q_D(const QEXTProgressPie);
    return d->m_precision;
}

double QEXTProgressPie::nullPosition() const
{
    Q_D(const QEXTProgressPie);
    return d->m_nullPosition;
}

double QEXTProgressPie::outlinePenWidth() const
{
    Q_D(const QEXTProgressPie);
    return d->m_outlinePenWidth;
}

double QEXTProgressPie::dataPenWidth() const
{
    Q_D(const QEXTProgressPie);
    return d->m_dataPenWidth;
}

QEXTProgressPie::BarStyle QEXTProgressPie::barStyle() const
{
    Q_D(const QEXTProgressPie);
    return d->m_barStyle;
}

QString QEXTProgressPie::format() const
{
    Q_D(const QEXTProgressPie);
    return d->m_format;
}

bool QEXTProgressPie::clockWise() const
{
    Q_D(const QEXTProgressPie);
    return d->m_clockWise;
}

QGradientStops QEXTProgressPie::gradientData() const
{
    Q_D(const QEXTProgressPie);
    return d->m_gradientData;
}

QSize QEXTProgressPie::sizeHint() const
{
    return QSize(100, 100);
}

QSize QEXTProgressPie::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QEXTProgressPie::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTProgressPie);
    if (d->m_backgroundColor != color) {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTProgressPie::setTextColor(const QColor &color)
{
    Q_D(QEXTProgressPie);
    if (d->m_textColor != color) {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTProgressPie::setBaseColor(const QColor &color)
{
    Q_D(QEXTProgressPie);
    if (d->m_baseColor != color) {
        d->m_baseColor = color;
        this->update();
    }
}

void QEXTProgressPie::setInnerBackgroundColor(const QColor &color)
{
    Q_D(QEXTProgressPie);
    if (d->m_innerBackgroundColor != color) {
        d->m_innerBackgroundColor = color;
        this->update();
    }
}

void QEXTProgressPie::setBorderColor(const QColor &color)
{
    Q_D(QEXTProgressPie);
    if (d->m_borderColor != color) {
        d->m_borderColor = color;
        this->update();
    }
}

void QEXTProgressPie::setProgressColor(const QColor &color)
{
    Q_D(QEXTProgressPie);
    if (d->m_progressColor != color) {
        d->m_progressColor = color;
        this->update();
    }
}

void QEXTProgressPie::setRange(double minValue, double maxValue)
{
    Q_D(QEXTProgressPie);
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

void QEXTProgressPie::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QEXTProgressPie::setMinValue(double minValue)
{
    Q_D(QEXTProgressPie);
    this->setRange(minValue, d->m_maxValue);
}

void QEXTProgressPie::setMaxValue(double maxValue)
{
    Q_D(QEXTProgressPie);
    this->setRange(d->m_minValue, maxValue);
}

void QEXTProgressPie::setValue(double value)
{
    Q_D(QEXTProgressPie);
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

void QEXTProgressPie::setValue(int value)
{
    this->setValue(double(value));
}

void QEXTProgressPie::setPrecision(int precision)
{
    Q_D(QEXTProgressPie);
    if (precision >= 0 && d->m_precision != precision) {
        d->m_precision = precision;
        this->update();
    }
}

void QEXTProgressPie::setNullPosition(double nullPosition)
{
    Q_D(QEXTProgressPie);
    if (d->m_nullPosition != nullPosition) {
        d->m_nullPosition = nullPosition;
        this->update();
    }
}

void QEXTProgressPie::setBarStyle(BarStyle barStyle)
{
    Q_D(QEXTProgressPie);
    if (d->m_barStyle != barStyle) {
        d->m_barStyle = barStyle;
        this->update();
    }
}

void QEXTProgressPie::setFormat(const QString &format)
{
    Q_D(QEXTProgressPie);
    if (d->m_format != format) {
        d->m_format = format;
        this->update();
    }
}

void QEXTProgressPie::setOutlinePenWidth(double width)
{
    Q_D(QEXTProgressPie);
    if (d->m_outlinePenWidth != width) {
        d->m_outlinePenWidth = width;
        this->update();
    }
}

void QEXTProgressPie::setDataPenWidth(double width)
{
    Q_D(QEXTProgressPie);
    if (d->m_dataPenWidth != width) {
        d->m_dataPenWidth = width;
        this->update();
    }
}

void QEXTProgressPie::setClockWise(bool clockWise)
{
    Q_D(QEXTProgressPie);
    if (d->m_clockWise != clockWise) {
        d->m_clockWise = clockWise;
        this->update();
    }
}

void QEXTProgressPie::setGradientData(const QGradientStops &gradientData)
{
    Q_D(QEXTProgressPie);
    if (d->m_gradientData != gradientData) {
        d->m_gradientData = gradientData;
        this->update();
    }
}
