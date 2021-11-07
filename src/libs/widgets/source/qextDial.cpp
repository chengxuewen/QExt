#pragma execution_character_set("utf-8")

#include <qextDial.h>
#include <qextDial_p.h>

#include <QPainter>
#include <QPointF>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <qmath.h>


QEXTDialPrivate::QEXTDialPrivate(QEXTDial *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;
    m_precision = 0;

    m_scaleMajor = 10;
    m_scaleMinor = 5;
    m_startAngle = 45;
    m_endAngle = 45;

    m_darkColor = QColor(100, 100, 100);
    m_lightColor = QColor(250, 250, 250);
    m_textColor = QColor(0, 0, 0);

    m_valueVisiable = true;
    m_pointerStyle = QEXTDial::PointerStyle_Triangle;
}

QEXTDialPrivate::~QEXTDialPrivate()
{

}



QEXTDial::QEXTDial(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTDialPrivate(this))
{
    this->setFont(QFont("Arial", 9));
}

QEXTDial::~QEXTDial()
{

}

void QEXTDial::mousePressEvent(QMouseEvent *e)
{
    QEXT_DECL_D(QEXTDial);
    d->m_pressed = true;
    this->setPressedValue(e->pos());
}

void QEXTDial::mouseReleaseEvent(QMouseEvent *)
{
    QEXT_DECL_D(QEXTDial);
    d->m_pressed = false;
}

void QEXTDial::mouseMoveEvent(QMouseEvent *e)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_pressed)
    {
        this->setPressedValue(e->pos());
    }
}

void QEXTDial::paintEvent(QPaintEvent *)
{
    QEXT_DECL_D(QEXTDial);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制刻度线
    this->drawScale(&painter);
    //绘制刻度值
    this->drawScaleNum(&painter);
    //绘制边界凹凸圆
    this->drawBorderCircle(&painter);
    //绘制背景圆
    this->drawBackgroundCircle(&painter);

    //根据指示器形状绘制指示器
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

    //绘制当前值中心背景圆
    this->drawCenterCircle(&painter);
    //绘制当前值
    this->drawValue(&painter);
}

void QEXTDial::drawScale(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    int radius = 80;
    painter->save();

    painter->rotate(d->m_startAngle);
    int steps = (d->m_scaleMajor * d->m_scaleMinor);
    double angleStep = (360.0 - d->m_startAngle - d->m_endAngle) / steps;

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(d->m_textColor);

    for (int i = 0; i <= steps; i++)
    {
        if (i % d->m_scaleMinor == 0)
        {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius);
        }
        else
        {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 8, 0, radius - 3);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void QEXTDial::drawScaleNum(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    int radius = 90;
    painter->save();
    painter->setPen(d->m_textColor);

    double startRad = (360 - d->m_startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - d->m_startAngle - d->m_endAngle) * (M_PI / 180) / d->m_scaleMajor;

    for (int i = 0; i <= d->m_scaleMajor; i++)
    {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((d->m_maxValue - d->m_minValue) / d->m_scaleMajor) + d->m_minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', d->m_precision);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void QEXTDial::drawBorderCircle(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    int radius = 70;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, d->m_darkColor);
    bgGradient.setColorAt(1.0, d->m_lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTDial::drawBackgroundCircle(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, d->m_lightColor);
    bgGradient.setColorAt(1.0, d->m_darkColor);
    painter->setBrush(bgGradient);

    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTDial::drawPointerCircle(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    int radius = 15;
    int offset = 10;
    painter->save();
    painter->setPen(Qt::NoPen);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QLinearGradient bgGradient(0, 0, radius * 2, radius * 2);
    bgGradient.setColorAt(0.0, d->m_darkColor);
    bgGradient.setColorAt(1.0, d->m_lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->setPen(QPen(d->m_darkColor, 2, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, radius * 2 + offset, 0, radius * 2 + 10 + offset);

    painter->restore();
}

void QEXTDial::drawPointerIndicator(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    int radius = 55;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_darkColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QEXTDial::drawPointerIndicatorR(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    int radius = 55;
    painter->save();
    painter->setOpacity(0.6);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(d->m_darkColor);

    painter->setPen(pen);
    painter->setBrush(d->m_darkColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void QEXTDial::drawPointerTriangle(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    int radius = 10;
    int offset = 45;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_darkColor);

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QEXTDial::drawCenterCircle(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    if (!d->m_valueVisiable)
    {
        return;
    }

    int radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, d->m_darkColor);
    bgGradient.setColorAt(1.0, d->m_lightColor);
    painter->setBrush(bgGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTDial::drawValue(QPainter *painter)
{
    QEXT_DECL_D(QEXTDial);
    if (!d->m_valueVisiable)
    {
        return;
    }

    int radius = 100;
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    font.setPixelSize(12);
    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)d->m_value, 0, 'f', d->m_precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}

void QEXTDial::setPressedValue(QPointF point)
{
    QEXT_DECL_D(QEXTDial);
    //计算总角度
    double length = 360 - d->m_startAngle - d->m_endAngle;

    //计算最近的刻度
    QPointF recentPoint = point - rect().center();
    double theta = -atan2(-recentPoint.x(), -recentPoint.y()) * 180 / M_PI;
    theta = theta + length / 2;

    //计算每一个角度对应值移动多少
    double increment = (d->m_maxValue - d->m_minValue) / length;
    double currentValue = (theta * increment) + d->m_minValue;

    //过滤圆弧外的值
    if (currentValue <= d->m_minValue)
    {
        currentValue = d->m_minValue;
    }
    else if (currentValue >= d->m_maxValue)
    {
        currentValue = d->m_maxValue;
    }

    this->setValue(currentValue);
}

double QEXTDial::minValue() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_minValue;
}

double QEXTDial::maxValue() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_maxValue;
}

double QEXTDial::value() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_value;
}

int QEXTDial::precision() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_precision;
}

int QEXTDial::scaleMajor() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_scaleMajor;
}

int QEXTDial::scaleMinor() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_scaleMinor;
}

int QEXTDial::startAngle() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_startAngle;
}

int QEXTDial::endAngle() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_endAngle;
}

QColor QEXTDial::darkColor() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_darkColor;
}

QColor QEXTDial::lightColor() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_lightColor;
}

QColor QEXTDial::textColor() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_textColor;
}

bool QEXTDial::valueVisiable() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_valueVisiable;
}

QEXTDial::PointerStyleType QEXTDial::pointerStyle() const
{
    QEXT_DECL_DC(QEXTDial);
    return d->m_pointerStyle;
}

QSize QEXTDial::sizeHint() const
{
    return QSize(200, 200);
}

QSize QEXTDial::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QEXTDial::setRange(double minValue, double maxValue)
{
    QEXT_DECL_D(QEXTDial);
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue)
    {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (d->m_value < minValue || d->m_value > maxValue)
    {
        this->setValue(d->m_value);
    }

    this->update();
}

void QEXTDial::setRange(int minValue, int maxValue)
{
    QEXT_DECL_D(QEXTDial);
    this->setRange((double)minValue, (double)maxValue);
}

void QEXTDial::setMinValue(double minValue)
{
    QEXT_DECL_D(QEXTDial);
    this->setRange(minValue, d->m_maxValue);
}

void QEXTDial::setMaxValue(double maxValue)
{
    QEXT_DECL_D(QEXTDial);
    this->setRange(d->m_minValue, maxValue);
}

void QEXTDial::setValue(double value)
{
    QEXT_DECL_D(QEXTDial);
    //值和当前值一致则无需处理
    if (value == d->m_value)
    {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
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
    this->update();
}

void QEXTDial::setValue(int value)
{
    QEXT_DECL_D(QEXTDial);
    this->setValue((double)value);
}

void QEXTDial::setPrecision(int precision)
{
    QEXT_DECL_D(QEXTDial);
    //最大精确度为 3
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        this->update();
    }
}

void QEXTDial::setScaleMajor(int scaleMajor)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_scaleMajor != scaleMajor)
    {
        d->m_scaleMajor = scaleMajor;
        this->update();
    }
}

void QEXTDial::setScaleMinor(int scaleMinor)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_scaleMinor != scaleMinor)
    {
        d->m_scaleMinor = scaleMinor;
        this->update();
    }
}

void QEXTDial::setStartAngle(int angle)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_startAngle != angle)
    {
        d->m_startAngle = angle;
        this->update();
    }
}

void QEXTDial::setEndAngle(int angle)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_endAngle != angle)
    {
        d->m_endAngle = angle;
        this->update();
    }
}

void QEXTDial::setDarkColor(const QColor &color)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_darkColor != color)
    {
        d->m_darkColor = color;
        this->update();
    }
}

void QEXTDial::setLightColor(const QColor &color)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_lightColor != color)
    {
        d->m_lightColor = color;
        this->update();
    }
}

void QEXTDial::setTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTDial::setShowValue(bool visiable)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_valueVisiable != visiable)
    {
        d->m_valueVisiable = visiable;
        this->update();
    }
}

void QEXTDial::setPointerStyle(const QEXTDial::PointerStyleType &style)
{
    QEXT_DECL_D(QEXTDial);
    if (d->m_pointerStyle != style)
    {
        d->m_pointerStyle = style;
        this->update();
    }
}
