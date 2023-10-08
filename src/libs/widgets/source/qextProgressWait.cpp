#include <private/qextProgressWait_p.h>

#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QDebug>
#include <qmath.h>

QEXTProgressWaitPrivate::QEXTProgressWaitPrivate(QEXTProgressWait *q)
    : q_ptr(q)
{
    m_clockWise = true;
    m_showPercent = false;
    m_currentValue = 0;
    m_maxValue = 10;
    m_interval = 100;

    m_barStyle = QEXTProgressWait::Style_Line;
    m_background = QColor(255, 255, 255);
    m_foreground = QColor(100, 184, 255);
    m_textColor = QColor(100, 184, 255);
}

QEXTProgressWaitPrivate::~QEXTProgressWaitPrivate()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}



QEXTProgressWait::QEXTProgressWait(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QEXTProgressWaitPrivate(this))
{
    Q_D(QEXTProgressWait);
    d->m_timer = new QTimer(this);
    d->m_timer->setInterval(d->m_interval);
    connect(d->m_timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    d->m_timer->start();

    this->resizeEvent(NULL);
    this->setFont(QFont("Arial", 8));
}

QEXTProgressWait::~QEXTProgressWait()
{

}

void QEXTProgressWait::resizeEvent(QResizeEvent *)
{
    //    if (barStyle == BarStyle_DoubleCircle) {
    //        int radius = 200;
    //        minRadius = radius / 10;
    //        maxRadius = radius / 5;
    //        offsetRadius = radius / 30;
    //        leftRadius = minRadius;
    //        rightRadius = maxRadius;
    //        leftIncrease = true;
    //        rightIncrease = false;
    //    }
}

void QEXTProgressWait::paintEvent(QPaintEvent *)
{
    Q_D(QEXTProgressWait);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    if (d->m_barStyle == Style_Line) {
        this->drawLine(&painter);
    } else if (d->m_barStyle == Style_Dot) {
        this->drawDot(&painter);
    }

    this->drawValue(&painter);
}

void QEXTProgressWait::drawArc(QPainter *painter)
{
    Q_D(QEXTProgressWait);
    painter->save();
    painter->setPen(Qt::NoPen);

    int centerX = 0;
    int centerY = 0;
    int radius = 99;
    int radiusBig = radius / 2;
    int radiusSmall = radius / 6;
    double currentangle = d->m_currentValue * (360 / (d->m_maxValue + 1));

    if (d->m_clockWise) {
        currentangle = -currentangle;
    }

    painter->setBrush(d->m_foreground);
    QPainterPath pathBig1(QPointF(centerX + radius * qCos(degreesToRadians(currentangle)),
                                  centerY - radius * qSin(degreesToRadians(currentangle))));
    pathBig1.arcTo(centerX - radius, centerY - radius, radius * 2, radius * 2, currentangle, 180);
    pathBig1.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle + 180)) - radiusBig,
                   centerY - radiusBig * qSin(degreesToRadians(currentangle + 180)) - radiusBig,
                   radiusBig * 2, radiusBig * 2, currentangle + 180, 180);
    pathBig1.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusBig,
                   centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusBig,
                   radiusBig * 2, radiusBig * 2, currentangle + 180, -180
                   );
    painter->drawPath(pathBig1);

    painter->setBrush(d->m_background);
    QPainterPath pathBig2(QPointF(centerX + radius * qCos(degreesToRadians(currentangle)),
                                  centerY - radius * qSin(degreesToRadians(currentangle))));
    pathBig2.arcTo(centerX - radius, centerY - radius, radius * 2, radius * 2, currentangle, -180);
    pathBig2.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle + 180)) - radiusBig,
                   centerY - radiusBig * qSin(degreesToRadians(currentangle + 180)) - radiusBig,
                   radiusBig * 2, radiusBig * 2, currentangle + 180, 180);
    pathBig2.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusBig,
                   centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusBig,
                   radiusBig * 2, radiusBig * 2, currentangle + 180, -180
                   );
    painter->drawPath(pathBig2);

    painter->setBrush(d->m_foreground);
    QPainterPath pathSmall1;
    pathSmall1.addEllipse(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusSmall,
                          centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusSmall,
                          radiusSmall * 2, radiusSmall * 2);
    painter->drawPath(pathSmall1);

    painter->setBrush(d->m_background);
    QPainterPath pathSmall2;
    pathSmall2.addEllipse(centerX + radiusBig * qCos(degreesToRadians(180 + currentangle)) - radiusSmall,
                          centerY - radiusBig * qSin(degreesToRadians(180 + currentangle)) - radiusSmall,
                          radiusSmall * 2, radiusSmall * 2);
    painter->drawPath(pathSmall2);

    painter->restore();
}

void QEXTProgressWait::drawDot(QPainter *painter)
{
    Q_D(QEXTProgressWait);
    painter->save();
    painter->setPen(Qt::NoPen);

    int radius = 99;
    int minRadius = radius / 6;
    double angleStep = 360.0 / d->m_maxValue;
    double alpha = (double)1 / d->m_maxValue;

    if (!d->m_clockWise) {
        angleStep = -angleStep;
    }

    int centerX = 0;
    int centerY = 0;
    double centerRadius = radius / 1.2;

    for (int i = 0; i < d->m_maxValue; i++) {
        double angle = (d->m_currentValue + i) * angleStep;
        double initX = centerRadius * qCos(degreesToRadians(angle)) + centerX;
        double initY = centerRadius * qSin(degreesToRadians(angle)) + centerY;

        int value = i * alpha * 255;
        value = value < 30 ? 30 : value;

        d->m_foreground.setAlpha(value);
        painter->setBrush(d->m_foreground);
        painter->drawEllipse(initX - minRadius, initY - minRadius, minRadius * 2, minRadius * 2);
    }

    painter->restore();
}

void QEXTProgressWait::drawPie(QPainter *painter)
{
    Q_D(QEXTProgressWait);
    int radius = 99;
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    int startAngle = (360 / (d->m_maxValue + 1)) * d->m_currentValue * 16;

    int spanAngle = 60 * 16;

    painter->setBrush(d->m_foreground);

    if (d->m_clockWise) {
        startAngle = -startAngle;
    }

    painter->drawPie(-radius, -radius, radius * 2, radius * 2, startAngle, spanAngle);

    painter->restore();
}

void QEXTProgressWait::drawLine(QPainter *painter)
{
    Q_D(QEXTProgressWait);
    int radius = 95;

    int initY = 50;

    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidth(10);
    pen.setCapStyle(Qt::RoundCap);

    double angleStep = 360.0 / d->m_maxValue;
    double alpha = (double)1 / d->m_maxValue;

    if (!d->m_clockWise) {
        angleStep = -angleStep;
    }

    for (int i = 0; i <= d->m_maxValue; i++) {
        int value = (d->m_currentValue - i) * alpha * 255;
        if (value < 0) {
            value = value + 255;
        }

        value = value < 30 ? 30 : value;

        d->m_foreground.setAlpha(value);
        pen.setColor(d->m_foreground);
        painter->setPen(pen);
        painter->drawLine(0, initY, 0, radius);
        painter->rotate(angleStep);
    }

    painter->restore();
}

void QEXTProgressWait::drawRing(QPainter *painter)
{
    Q_D(QEXTProgressWait);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);
    int arcHeight = 30;
    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));

    int startAngle = (360 / (d->m_maxValue + 1)) * d->m_currentValue;

    int spanAngle = 90;
    QPainterPath currentPath;

    if (d->m_clockWise) {
        currentPath.arcTo(rect, -startAngle, spanAngle);
    } else {
        currentPath.arcTo(rect, startAngle, spanAngle);
    }

    if (d->m_clockWise) {
        startAngle = startAngle - spanAngle;
    } else {
        startAngle = startAngle + spanAngle;
    }

    spanAngle = 360 - spanAngle;
    QPainterPath otherPath;

    if (d->m_clockWise) {
        otherPath.arcTo(rect, -startAngle, spanAngle);
    } else {
        otherPath.arcTo(rect, startAngle, spanAngle);
    }

    painter->setBrush(d->m_foreground);
    painter->drawPath(currentPath - subPath);
    painter->setBrush(d->m_background);
    painter->drawPath(otherPath - subPath);

    painter->restore();
}

void QEXTProgressWait::drawSingleCircle(QPainter *painter)
{
    Q_D(QEXTProgressWait);
    int radius = d->m_currentValue * 10;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_foreground);
    painter->drawEllipse(QPoint(0, 0), radius, radius);
    painter->restore();
}

void QEXTProgressWait::drawDoubleCircle(QPainter *painter)
{
    Q_D(QEXTProgressWait);
    if (d->m_leftRadius <= d->m_minRadius) {
        d->m_leftIncrease = true;
    } else if (d->m_leftRadius >= d->m_maxRadius) {
        d->m_leftIncrease = false;
    }

    if (d->m_rightRadius <= d->m_minRadius) {
        d->m_rightIncrease = true;
    } else if (d->m_rightRadius >= d->m_maxRadius) {
        d->m_rightIncrease = false;
    }

    if (d->m_leftIncrease) {
        d->m_leftRadius += d->m_offsetRadius;
    } else {
        d->m_leftRadius -= d->m_offsetRadius;
    }

    if (d->m_rightIncrease) {
        d->m_rightRadius += d->m_offsetRadius;
    } else {
        d->m_rightRadius -= d->m_offsetRadius;
    }

    int radius = 50;

    painter->save();
    painter->setPen(Qt::NoPen);

    painter->setBrush(d->m_foreground);
    painter->drawEllipse(QPointF(-radius, 0), d->m_leftRadius, d->m_leftRadius);

    painter->setBrush(d->m_background);
    painter->drawEllipse(QPointF(radius, 0), d->m_rightRadius, d->m_rightRadius);

    painter->restore();
}

void QEXTProgressWait::drawValue(QPainter *painter)
{
    Q_D(QEXTProgressWait);
    if (!d->m_showPercent) {
        return;
    }

    int radius = 100;
    painter->save();
    QFont font;
    font.setPixelSize(40);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(d->m_textColor);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignCenter, QString("%1%").arg(d->m_currentValue * (100 / d->m_maxValue)));
    painter->restore();
}

double QEXTProgressWait::degreesToRadians(double degrees)
{
    return degrees * (M_PI / 180);
}

void QEXTProgressWait::updateValue()
{
    Q_D(QEXTProgressWait);
    if (d->m_currentValue < d->m_maxValue) {
        d->m_currentValue++;
    } else {
        d->m_currentValue = 0;
    }

    this->update();
}

bool QEXTProgressWait::clockWise() const
{
    Q_D(const QEXTProgressWait);
    return d->m_clockWise;
}

bool QEXTProgressWait::showPercent() const
{
    Q_D(const QEXTProgressWait);
    return d->m_showPercent;
}

int QEXTProgressWait::currentValue() const
{
    Q_D(const QEXTProgressWait);
    return d->m_currentValue;
}

int QEXTProgressWait::maxValue() const
{
    Q_D(const QEXTProgressWait);
    return d->m_maxValue;
}

int QEXTProgressWait::interval() const
{
    Q_D(const QEXTProgressWait);
    return d->m_interval;
}

QEXTProgressWait::Style QEXTProgressWait::barStyle() const
{
    Q_D(const QEXTProgressWait);
    return d->m_barStyle;
}

QColor QEXTProgressWait::backgroundColor() const
{
    Q_D(const QEXTProgressWait);
    return d->m_background;
}

QColor QEXTProgressWait::foregroundColor() const
{
    Q_D(const QEXTProgressWait);
    return d->m_foreground;
}

QColor QEXTProgressWait::textColor() const
{
    Q_D(const QEXTProgressWait);
    return d->m_textColor;
}

QSize QEXTProgressWait::sizeHint() const
{
    return QSize(100, 100);
}

QSize QEXTProgressWait::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QEXTProgressWait::setClockWise(bool clockWise)
{
    Q_D(QEXTProgressWait);
    if (d->m_clockWise != clockWise) {
        d->m_clockWise = clockWise;
        this->update();
    }
}

void QEXTProgressWait::setShowPercent(bool showPercent)
{
    Q_D(QEXTProgressWait);
    if (d->m_showPercent != showPercent) {
        d->m_showPercent = showPercent;
        this->update();
    }
}

void QEXTProgressWait::setCurrentValue(int currentValue)
{
    Q_D(QEXTProgressWait);
    if (d->m_currentValue != currentValue) {
        d->m_currentValue = currentValue;
        this->update();
    }
}

void QEXTProgressWait::setMaxValue(int maxValue)
{
    Q_D(QEXTProgressWait);
    if (d->m_maxValue != maxValue) {
        d->m_maxValue = maxValue;
        d->m_currentValue = 0;
        this->update();
    }
}

void QEXTProgressWait::setInterval(int interval)
{
    Q_D(QEXTProgressWait);
    if (d->m_interval != interval) {
        d->m_interval = interval;
        d->m_timer->setInterval(interval);
        this->update();
    }
}

void QEXTProgressWait::setBarStyle(const QEXTProgressWait::Style &barStyle)
{
    Q_D(QEXTProgressWait);
    if (d->m_barStyle != barStyle) {
        d->m_barStyle = barStyle;
        this->update();
    }
}

void QEXTProgressWait::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTProgressWait);
    if (d->m_background != color) {
        d->m_background = color;
        this->update();
    }
}

void QEXTProgressWait::setForegroundColor(const QColor &color)
{
    Q_D(QEXTProgressWait);
    if (d->m_foreground != color) {
        d->m_foreground = color;
        this->update();
    }
}

void QEXTProgressWait::setTextColor(const QColor &color)
{
    Q_D(QEXTProgressWait);
    if (d->m_textColor != color) {
        d->m_textColor = color;
        this->update();
    }
}
