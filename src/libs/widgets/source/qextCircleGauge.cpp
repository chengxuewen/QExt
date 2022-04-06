#include <qextCircleGauge.h>
#include <qextCircleGauge_p.h>

#include <QPainter>
#include <QVariant>
#include <QTimer>
#include <QDebug>
#include <QPainterPath>
#include <qmath.h>


QEXTCircleGaugePrivate::QEXTCircleGaugePrivate(QEXTCircleGauge *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;
    m_precision = 0;

    m_scaleMajor = 10;
    m_scaleMinor = 10;
    m_startAngle = 45;
    m_endAngle = 45;

    m_outerCircleColor = QColor(80, 80, 80);
    m_innerCircleColor = QColor(60, 60, 60);

    m_pieColorStart = QColor(24, 189, 155);
    m_pieColorMid = QColor(218, 218, 0);
    m_pieColorEnd = QColor(255, 107, 107);

    m_coverCircleColor = QColor(100, 100, 100);
    m_scaleColor = QColor(255, 255, 255);
    m_pointerColor = QColor(255, 107, 107);
    m_centerCircleColor = QColor(250, 250, 250);
    m_textColor = QColor(0, 0, 0);

    m_overlayVisible = true;
    m_overlayColor = QColor(255, 255, 255, 60);

    m_circleWidth = 15;
    m_pieStyle = QEXTCircleGauge::PieStyle_Three;
    m_pointerStyle = QEXTCircleGauge::PointerStyle_Indicator;

    m_currentValue = 0;
    m_animationEnable = false;
}

QEXTCircleGaugePrivate::~QEXTCircleGaugePrivate()
{

}



QEXTCircleGauge::QEXTCircleGauge(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTCircleGaugePrivate(this))
{
    Q_D(QEXTCircleGauge);
    d->m_animation = new QPropertyAnimation(this, "");
    d->m_animation->setDuration(500);
    d->m_animation->setEasingCurve(QEasingCurve::Linear);
    connect(d->m_animation, SIGNAL(valueChanged(QVariant)), this, SLOT(updateValue(QVariant)));

    this->setFont(QFont("Arial", 8));
}

QEXTCircleGauge::~QEXTCircleGauge()
{

}

void QEXTCircleGauge::paintEvent(QPaintEvent *)
{
    Q_D(QEXTCircleGauge);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    this->drawOuterCircle(&painter);
    this->drawInnerCircle(&painter);
    this->drawColorPie(&painter);
    this->drawCoverCircle(&painter);
    this->drawScale(&painter);
    this->drawScaleNum(&painter);

    if (d->m_pointerStyle == PointerStyle_Circle)
    {
        this->drawPointerCircle(&painter);
    }
    else if (d->m_pointerStyle == PointerStyle_Indicator)
    {
        this->drawPointerIndicator(&painter);
    }
    else if (d->m_pointerStyle == PointerStyle_IndicatorR)
    {
        this->drawPointerIndicatorR(&painter);
    }
    else if (d->m_pointerStyle == PointerStyle_Triangle)
    {
        this->drawPointerTriangle(&painter);
    }

    this->drawRoundCircle(&painter);
    this->drawCenterCircle(&painter);
    this->drawValue(&painter);
    this->drawOverlay(&painter);
}

void QEXTCircleGauge::drawOuterCircle(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_outerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTCircleGauge::drawInnerCircle(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_innerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTCircleGauge::drawColorPie(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    if (d->m_pieStyle == PieStyle_Three)
    {
        //Calculate the total range Angle, automatically calculate the three-color ring range Angle according to the proportion
        double angleAll = 360.0 - d->m_startAngle - d->m_endAngle;
        double angleStart = angleAll * 0.7;
        double angleMid = angleAll * 0.15;
        double angleEnd = angleAll * 0.15;

        //Increase the offset so that there appears to be no disconnection
        int offset = 3;

        //Draw the opening pie circle
        painter->setBrush(d->m_pieColorStart);
        painter->drawPie(rect, (270 - d->m_startAngle - angleStart) * 16, angleStart * 16);

        //Draw the middle pie circle
        painter->setBrush(d->m_pieColorMid);
        painter->drawPie(rect, (270 - d->m_startAngle - angleStart - angleMid) * 16 + offset, angleMid * 16);

        //Draw the end pie circle
        painter->setBrush(d->m_pieColorEnd);
        painter->drawPie(rect, (270 - d->m_startAngle - angleStart - angleMid - angleEnd) * 16 + offset * 2, angleEnd * 16);
    }
    else if (d->m_pieStyle == PieStyle_Current)
    {
        //Calculate the total range Angle, current value range Angle, residual value range Angle
        double angleAll = 360.0 - d->m_startAngle - d->m_endAngle;
        double angleCurrent = angleAll * ((d->m_currentValue - d->m_minValue) / (d->m_maxValue - d->m_minValue));
        double angleOther = angleAll - angleCurrent;

        //Draws the current value pie circle
        painter->setBrush(d->m_pieColorStart);
        painter->drawPie(rect, (270 - d->m_startAngle - angleCurrent) * 16, angleCurrent * 16);

        //Draws the remaining value pie circle
        painter->setBrush(d->m_pieColorEnd);
        painter->drawPie(rect, (270 - d->m_startAngle - angleCurrent - angleOther) * 16, angleOther * 16);
    }

    painter->restore();
}

void QEXTCircleGauge::drawCoverCircle(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 50;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_coverCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTCircleGauge::drawScale(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 72;
    painter->save();

    painter->rotate(d->m_startAngle);
    int steps = (d->m_scaleMajor * d->m_scaleMinor);
    double angleStep = (360.0 - d->m_startAngle - d->m_endAngle) / steps;

    QPen pen;
    pen.setColor(d->m_scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++)
    {
        if (i % d->m_scaleMinor == 0)
        {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        }
        else
        {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void QEXTCircleGauge::drawScaleNum(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 82;
    painter->save();
    painter->setPen(d->m_scaleColor);

    double startRad = (360 - d->m_startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - d->m_startAngle - d->m_endAngle) * (M_PI / 180) / d->m_scaleMajor;

    for (int i = 0; i <= d->m_scaleMajor; i++)
    {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((d->m_maxValue - d->m_minValue) / d->m_scaleMajor) + d->m_minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', d->m_precision);
        QRect strRect = fontMetrics().boundingRect(strValue);
        double textWidth = strRect.width();
        double textHeight = strRect.height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void QEXTCircleGauge::drawPointerCircle(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 6;
    int offset = 30;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_currentValue - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void QEXTCircleGauge::drawPointerIndicator(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 75;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_currentValue - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QEXTCircleGauge::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 75;
    painter->save();
    painter->setOpacity(1.0);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(d->m_pointerColor);
    painter->setPen(pen);
    painter->setBrush(d->m_pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_currentValue - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //Add drawing a rounded line that overlaps with the previous triangle to form a rounded pointer
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void QEXTCircleGauge::drawPointerTriangle(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 10;
    int offset = 38;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0 + offset, 5, 0 + offset, 0, radius + offset);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_currentValue - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QEXTCircleGauge::drawRoundCircle(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = d->m_circleWidth + 3;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTCircleGauge::drawCenterCircle(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = d->m_circleWidth;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_centerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTCircleGauge::drawValue(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    int radius = 100;
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    font.setPixelSize(18);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)d->m_currentValue, 0, 'f', d->m_precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void QEXTCircleGauge::drawOverlay(QPainter *painter)
{
    Q_D(QEXTCircleGauge);
    if (!d->m_overlayVisible)
    {
        return;
    }

    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //The highlight shape is a small circle subtracted from a large circle
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    d->m_overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, d->m_overlayColor);
    d->m_overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, d->m_overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

void QEXTCircleGauge::updateValue(const QVariant &value)
{
    Q_D(QEXTCircleGauge);
    const double animationValue = value.toDouble();
    if (animationValue != d->m_currentValue)
    {
        d->m_currentValue = animationValue;
    }
    this->update();
}

double QEXTCircleGauge::minValue() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_minValue;
}

double QEXTCircleGauge::maxValue() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_maxValue;
}

double QEXTCircleGauge::value() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_value;
}

int QEXTCircleGauge::precision() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_precision;
}

int QEXTCircleGauge::scaleMajor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_scaleMajor;
}

int QEXTCircleGauge::scaleMinor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_scaleMinor;
}

int QEXTCircleGauge::startAngle() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_startAngle;
}

int QEXTCircleGauge::endAngle() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_endAngle;
}

bool QEXTCircleGauge::animationEnable() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_animationEnable;
}

int QEXTCircleGauge::animationDuration() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_animation->duration();
}

QEasingCurve::Type QEXTCircleGauge::animationEasingCurve() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_animation->easingCurve().type();
}

QColor QEXTCircleGauge::outerCircleColor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_outerCircleColor;
}

QColor QEXTCircleGauge::innerCircleColor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_innerCircleColor;
}

QColor QEXTCircleGauge::pieColorStart() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_pieColorStart;
}

QColor QEXTCircleGauge::pieColorMid() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_pieColorMid;
}

QColor QEXTCircleGauge::pieColorEnd() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_pieColorEnd;
}

QColor QEXTCircleGauge::coverCircleColor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_coverCircleColor;
}

QColor QEXTCircleGauge::scaleColor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_scaleColor;
}

QColor QEXTCircleGauge::pointerColor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_pointerColor;
}

QColor QEXTCircleGauge::centerCircleColor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_centerCircleColor;
}

QColor QEXTCircleGauge::textColor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_textColor;
}

bool QEXTCircleGauge::overlayVisible() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_overlayVisible;
}

QColor QEXTCircleGauge::overlayColor() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_overlayColor;
}

int QEXTCircleGauge::circleWidth() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_circleWidth;
}

QEXTCircleGauge::PieStyleType QEXTCircleGauge::pieStyle() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_pieStyle;
}

QEXTCircleGauge::PointerStyleType QEXTCircleGauge::pointerStyle() const
{
    Q_D(const QEXTCircleGauge);
    return d->m_pointerStyle;
}

QSize QEXTCircleGauge::sizeHint() const
{
    return QSize(200, 200);
}

QSize QEXTCircleGauge::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QEXTCircleGauge::setRange(double minValue, double maxValue)
{
    Q_D(QEXTCircleGauge);
    //If the minimum value is greater than or equal to the maximum value, this parameter is not specified
    if (minValue >= maxValue)
    {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    //If the target value is not in the range, reset the target value
    if (d->m_value < minValue || d->m_value > maxValue)
    {
        setValue(d->m_value);
    }

    update();
}

void QEXTCircleGauge::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void QEXTCircleGauge::setMinValue(double minValue)
{
    Q_D(QEXTCircleGauge);
    setRange(minValue, d->m_maxValue);
}

void QEXTCircleGauge::setMaxValue(double maxValue)
{
    Q_D(QEXTCircleGauge);
    setRange(d->m_minValue, maxValue);
}

void QEXTCircleGauge::setValue(double value)
{
    Q_D(QEXTCircleGauge);
    if (value == d->m_value)
    {
        return;
    }

    if (value < d->m_minValue)
    {
        value = d->m_minValue;
    }
    else if (value > d->m_maxValue)
    {
        value = d->m_maxValue;
    }

    d->m_value = value;
    emit this->valueChanged(value);

    if (!d->m_animationEnable)
    {
        d->m_currentValue = d->m_value;
        this->update();
    }
    else
    {
        d->m_animation->setStartValue(d->m_currentValue);
        d->m_animation->setEndValue(value);
        d->m_animation->start();
    }
}

void QEXTCircleGauge::setValue(int value)
{
    this->setValue((double)value);
}

void QEXTCircleGauge::setPrecision(int precision)
{
    Q_D(QEXTCircleGauge);
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        update();
    }
}

void QEXTCircleGauge::setScaleMajor(int scaleMajor)
{
    Q_D(QEXTCircleGauge);
    if (d->m_scaleMajor != scaleMajor)
    {
        d->m_scaleMajor = scaleMajor;
        update();
    }
}

void QEXTCircleGauge::setScaleMinor(int scaleMinor)
{
    Q_D(QEXTCircleGauge);
    if (d->m_scaleMinor != scaleMinor)
    {
        d->m_scaleMinor = scaleMinor;
        update();
    }
}

void QEXTCircleGauge::setStartAngle(int startAngle)
{
    Q_D(QEXTCircleGauge);
    if (d->m_startAngle != startAngle)
    {
        d->m_startAngle = startAngle;
        update();
    }
}

void QEXTCircleGauge::setEndAngle(int endAngle)
{
    Q_D(QEXTCircleGauge);
    if (d->m_endAngle != endAngle)
    {
        d->m_endAngle = endAngle;
        update();
    }
}

void QEXTCircleGauge::setAnimation(bool animation)
{
    Q_D(QEXTCircleGauge);
    if (d->m_animationEnable != animation)
    {
        d->m_animationEnable = animation;
        update();
    }
}

void QEXTCircleGauge::setAnimationDuration(int duration)
{
    Q_D(QEXTCircleGauge);
    if (duration <= 0)
    {
        qCritical() << "QEXTCircleGauge::setAnimationDuration():duration must greater than 0";
        return;
    }
    if (d->m_animation->duration() != duration)
    {
        d->m_animation->setDuration(duration);
    }
}

void QEXTCircleGauge::setAnimationEasingCurve(QEasingCurve::Type easingCurve)
{
    Q_D(QEXTCircleGauge);
    d->m_animation->setEasingCurve(easingCurve);
}

void QEXTCircleGauge::setOuterCircleColor(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_outerCircleColor != color)
    {
        d->m_outerCircleColor = color;
        update();
    }
}

void QEXTCircleGauge::setInnerCircleColor(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_innerCircleColor != color)
    {
        d->m_innerCircleColor = color;
        update();
    }
}

void QEXTCircleGauge::setPieColorStart(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_pieColorStart != color)
    {
        d->m_pieColorStart = color;
        update();
    }
}

void QEXTCircleGauge::setPieColorMid(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_pieColorMid != color)
    {
        d->m_pieColorMid = color;
        update();
    }
}

void QEXTCircleGauge::setPieColorEnd(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_pieColorEnd != color)
    {
        d->m_pieColorEnd = color;
        update();
    }
}

void QEXTCircleGauge::setCoverCircleColor(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_coverCircleColor != color)
    {
        d->m_coverCircleColor = color;
        update();
    }
}

void QEXTCircleGauge::setScaleColor(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_scaleColor != color)
    {
        d->m_scaleColor = color;
        update();
    }
}

void QEXTCircleGauge::setPointerColor(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_pointerColor != color)
    {
        d->m_pointerColor = color;
        update();
    }
}

void QEXTCircleGauge::setCenterCircleColor(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_centerCircleColor != color)
    {
        d->m_centerCircleColor = color;
        update();
    }
}

void QEXTCircleGauge::setTextColor(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        update();
    }
}

void QEXTCircleGauge::setOverlayVisible(bool visiable)
{
    Q_D(QEXTCircleGauge);
    if (d->m_overlayVisible != visiable)
    {
        d->m_overlayVisible = visiable;
        update();
    }
}

void QEXTCircleGauge::setOverlayColor(const QColor &color)
{
    Q_D(QEXTCircleGauge);
    if (d->m_overlayColor != color)
    {
        d->m_overlayColor = color;
        update();
    }
}

void QEXTCircleGauge::setCircleWidth(int width)
{
    Q_D(QEXTCircleGauge);
    if (d->m_circleWidth != width)
    {
        d->m_circleWidth = width;
        update();
    }
}

void QEXTCircleGauge::setPieStyle(const QEXTCircleGauge::PieStyleType &style)
{
    Q_D(QEXTCircleGauge);
    if (d->m_pieStyle != style)
    {
        d->m_pieStyle = style;
        update();
    }
}

void QEXTCircleGauge::setPointerStyle(const QEXTCircleGauge::PointerStyleType &style)
{
    Q_D(QEXTCircleGauge);
    if (d->m_pointerStyle != style)
    {
        d->m_pointerStyle = style;
        update();
    }
}

