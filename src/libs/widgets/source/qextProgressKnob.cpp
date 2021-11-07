#pragma execution_character_set("utf-8")

#include <qextProgressKnob.h>
#include <qextProgressKnob_p.h>

#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QDateTime>
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <qmath.h>


QEXTProgressKnobPrivate::QEXTProgressKnobPrivate(QEXTProgressKnob *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;
    m_precision = 0;

    m_startAngle = 0;
    m_endAngle = 0;

    m_backgroundColor = QColor(30, 30, 30);
    m_progressColor = QColor(100, 184, 255);
    m_progressBackgroundColor = QColor(50, 50, 50);
    m_circleStartColor = QColor(80, 80, 80);
    m_circleEndColor = QColor(50, 50, 50);
    m_textColor = QColor(200, 200, 200);

    m_pointerVisiable = true;
    m_valueVisiable = false;
    m_pointerStyle = QEXTProgressKnob::PointerStyle_Circle;

    m_hover = false;
    m_radiusCoverCircle = 85;
    m_radiusCircle = 80;
}

QEXTProgressKnobPrivate::~QEXTProgressKnobPrivate()
{

}



QEXTProgressKnob::QEXTProgressKnob(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTProgressKnobPrivate(this))
{
    QEXT_DECL_D(QEXTProgressKnob);
    d->m_animation = new QPropertyAnimation(this, "");
    d->m_animation->setStartValue(0);
    d->m_animation->setEndValue(10);
    d->m_animation->setDuration(300);
    connect(d->m_animation, SIGNAL(valueChanged(QVariant)), this, SLOT(updateRadius(QVariant)));
    this->setFont(QFont("Arial", 9));
}

QEXTProgressKnob::~QEXTProgressKnob()
{

}

void QEXTProgressKnob::enterEvent(QEvent *)
{
    QEXT_DECL_D(QEXTProgressKnob);
    d->m_hover = true;
    d->m_animation->stop();
    d->m_animation->start();
}

void QEXTProgressKnob::leaveEvent(QEvent *)
{
    QEXT_DECL_D(QEXTProgressKnob);
    d->m_hover = false;
    d->m_animation->stop();
    d->m_animation->start();
}

void QEXTProgressKnob::mousePressEvent(QMouseEvent *e)
{
    QEXT_DECL_D(QEXTProgressKnob);
    d->m_pressed = true;
    this->setPressedValue(e->pos());
}

void QEXTProgressKnob::mouseReleaseEvent(QMouseEvent *)
{
    QEXT_DECL_D(QEXTProgressKnob);
    d->m_pressed = false;
}

void QEXTProgressKnob::mouseMoveEvent(QMouseEvent *e)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_pressed)
    {
        this->setPressedValue(e->pos());
    }
}

void QEXTProgressKnob::paintEvent(QPaintEvent *)
{
    QEXT_DECL_D(QEXTProgressKnob);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    this->drawBackground(&painter);
    //绘制饼圆
    this->drawColorPie(&painter);
    //绘制覆盖圆 用以遮住饼圆多余部分
    this->drawCoverCircle(&painter);
    //绘制中心圆
    this->drawCircle(&painter);

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

    //绘制当前值
    this->drawValue(&painter);
}

void QEXTProgressKnob::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTProgressKnob::drawColorPie(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    int radius = 95;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - d->m_startAngle - d->m_endAngle;
    double angleCurrent = angleAll * ((d->m_value - d->m_minValue) / (d->m_maxValue - d->m_minValue));
    double angleOther = angleAll - angleCurrent;

    //绘制当前值饼圆
    painter->setBrush(d->m_progressColor);
    painter->drawPie(rect, (270 - d->m_startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    painter->setBrush(d->m_progressBackgroundColor);
    painter->drawPie(rect, (270 - d->m_startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void QEXTProgressKnob::drawCoverCircle(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    int radius = d->m_radiusCoverCircle;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTProgressKnob::drawCircle(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    int radius = d->m_radiusCircle;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, d->m_circleStartColor);
    bgGradient.setColorAt(1.0, d->m_circleEndColor);
    painter->setBrush(bgGradient);

    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTProgressKnob::drawPointerCircle(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (!d->m_pointerVisiable)
    {
        return;
    }

    int radius = 15;
    int offset = d->m_radiusCircle - 60;
    painter->save();
    painter->setPen(Qt::NoPen);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    painter->setBrush(d->m_progressColor);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void QEXTProgressKnob::drawPointerIndicator(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (!d->m_pointerVisiable)
    {
        return;
    }

    int radius = d->m_radiusCircle - 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_progressColor);

    QPolygon pts;
    pts.setPoints(3, -8, 0, 8, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //绘制中心圆点
    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void QEXTProgressKnob::drawPointerIndicatorR(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (!d->m_pointerVisiable)
    {
        return;
    }

    int radius = d->m_radiusCircle - 15;
    painter->save();

    QPen pen;
    pen.setWidth(1);
    pen.setColor(d->m_progressColor);
    painter->setPen(pen);
    painter->setBrush(d->m_progressColor);

    QPolygon pts;
    pts.setPoints(3, -8, 0, 8, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    //绘制中心圆点
    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void QEXTProgressKnob::drawPointerTriangle(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (!d->m_pointerVisiable)
    {
        return;
    }

    int radius = 20;
    int offset = d->m_radiusCircle - 25;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_progressColor);

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QEXTProgressKnob::drawValue(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (!d->m_valueVisiable)
    {
        return;
    }

    int radius = 100;
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    font.setPixelSize(d->m_pointerVisiable ? radius - 50 : radius - 15);
    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)d->m_value, 0, 'f', d->m_precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}

void QEXTProgressKnob::setEasingCurve()
{
    QEXT_DECL_D(QEXTProgressKnob);
    //随机选择一种动画效果
    int index = qrand() % 40;
    d->m_animation->setEasingCurve((QEasingCurve::Type)index);
}

void QEXTProgressKnob::updateRadius(QVariant radius)
{
    QEXT_DECL_D(QEXTProgressKnob);
    //如果鼠标悬停则逐渐变小,鼠标移开则逐渐变大直到恢复
    int step = radius.toInt();

    if (d->m_hover)
    {
        d->m_radiusCoverCircle = 85 - step;
        d->m_radiusCircle = 80 - step;
    }
    else
    {
        d->m_radiusCoverCircle = 75 + step;
        d->m_radiusCircle = 70 + step;
    }

    this->update();
}

void QEXTProgressKnob::setPressedValue(QPointF pressedPoint)
{
    QEXT_DECL_D(QEXTProgressKnob);
    //计算总角度
    double length = 360 - d->m_startAngle - d->m_endAngle;

    //计算最近的刻度
    QPointF point = pressedPoint - rect().center();
    double theta = -atan2(-point.x(), -point.y()) * 180 / M_PI;
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

double QEXTProgressKnob::minValue() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_minValue;
}

double QEXTProgressKnob::maxValue() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_maxValue;
}

double QEXTProgressKnob::value() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_value;
}

int QEXTProgressKnob::precision() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_precision;
}

int QEXTProgressKnob::startAngle() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_startAngle;
}

int QEXTProgressKnob::endAngle() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_endAngle;
}

QColor QEXTProgressKnob::backgroundColor() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_backgroundColor;
}

QColor QEXTProgressKnob::progressColor() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_progressColor;
}

QColor QEXTProgressKnob::progressBackgroundColor() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_progressBackgroundColor;
}

QColor QEXTProgressKnob::circleStartColor() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_circleStartColor;
}

QColor QEXTProgressKnob::circleEndColor() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_circleEndColor;
}

QColor QEXTProgressKnob::textColor() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_textColor;
}

bool QEXTProgressKnob::pointerVisiable() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_pointerVisiable;
}

bool QEXTProgressKnob::valueVisiable() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_valueVisiable;
}

QEXTProgressKnob::PointerStyle QEXTProgressKnob::pointerStyle() const
{
    QEXT_DECL_DC(QEXTProgressKnob);
    return d->m_pointerStyle;
}

QSize QEXTProgressKnob::sizeHint() const
{
    return QSize(200, 200);
}

QSize QEXTProgressKnob::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QEXTProgressKnob::setRange(double minValue, double maxValue)
{
    QEXT_DECL_D(QEXTProgressKnob);
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

void QEXTProgressKnob::setRange(int minValue, int maxValue)
{
    QEXT_DECL_D(QEXTProgressKnob);
    this->setRange((double)minValue, (double)maxValue);
}

void QEXTProgressKnob::setMinValue(double minValue)
{
    QEXT_DECL_D(QEXTProgressKnob);
    this->setRange(minValue, d->m_maxValue);
}

void QEXTProgressKnob::setMaxValue(double maxValue)
{
    QEXT_DECL_D(QEXTProgressKnob);
    this->setRange(d->m_minValue, maxValue);
}

void QEXTProgressKnob::setValue(double value)
{
    QEXT_DECL_D(QEXTProgressKnob);
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

void QEXTProgressKnob::setValue(int value)
{
    QEXT_DECL_D(QEXTProgressKnob);
    this->setValue((double)value);
}

void QEXTProgressKnob::setPrecision(int precision)
{
    QEXT_DECL_D(QEXTProgressKnob);
    //最大精确度为 3
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        update();
    }
}

void QEXTProgressKnob::setStartAngle(int angle)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_startAngle != angle)
    {
        d->m_startAngle = angle;
        this->update();
    }
}

void QEXTProgressKnob::setEndAngle(int angle)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_endAngle != angle)
    {
        d->m_endAngle = angle;
        this->update();
    }
}

void QEXTProgressKnob::setBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTProgressKnob::setProgressColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_progressColor != color)
    {
        d->m_progressColor = color;
        this->update();
    }
}

void QEXTProgressKnob::setProgressBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_progressBackgroundColor != color)
    {
        d->m_progressBackgroundColor = color;
        this->update();
    }
}

void QEXTProgressKnob::setCircleStartColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_circleStartColor != color)
    {
        d->m_circleStartColor = color;
        this->update();
    }
}

void QEXTProgressKnob::setCircleEndColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_circleEndColor != color)
    {
        d->m_circleEndColor = color;
        this->update();
    }
}

void QEXTProgressKnob::setTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTProgressKnob::setPointerVisiable(bool visiable)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_pointerVisiable != visiable)
    {
        d->m_pointerVisiable = visiable;
        this->update();
    }
}

void QEXTProgressKnob::setValueVisiable(bool visiable)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_valueVisiable != visiable)
    {
        d->m_valueVisiable = visiable;
        this->update();
    }
}

void QEXTProgressKnob::setPointerStyle(PointerStyle pointerStyle)
{
    QEXT_DECL_D(QEXTProgressKnob);
    if (d->m_pointerStyle != pointerStyle)
    {
        d->m_pointerStyle = pointerStyle;
        this->update();
    }
}
