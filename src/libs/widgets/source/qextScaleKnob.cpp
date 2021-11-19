#include <qextScaleKnob.h>
#include <qextScaleKnob_p.h>

#include <QMouseEvent>
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <qmath.h>



QEXTScaleKnobPrivate::QEXTScaleKnobPrivate(QEXTScaleKnob *q)
    : q_ptr(q)
{
    m_minValue = -100.0;
    m_maxValue = 100.0;
    m_value = 0;
    m_precision = 1;

    m_scaleStep = 20;
    m_startAngle = 45;
    m_endAngle = 45;

    m_borderColor = QColor(0, 0, 0);
    m_backgroundColor = QColor(50, 50, 50);
    m_textColor = QColor(0, 0, 0);
    m_percentColor = QColor(100, 184, 255);

    m_rangeBisectionEnable = true;
    m_valueVisiable = false;
    m_pointerStyle = QEXTScaleKnob::PointerStyle_Line;

}

QEXTScaleKnobPrivate::~QEXTScaleKnobPrivate()
{

}



QEXTScaleKnob::QEXTScaleKnob(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTScaleKnobPrivate(this))
{
    this->setFont(QFont("Arial", 9));
}

QEXTScaleKnob::~QEXTScaleKnob()
{

}

void QEXTScaleKnob::mousePressEvent(QMouseEvent *e)
{
    Q_D(QEXTScaleKnob);
    d->m_pressed = true;
    this->setPressedValue(e->pos());
}

void QEXTScaleKnob::mouseReleaseEvent(QMouseEvent *)
{
    Q_D(QEXTScaleKnob);
    d->m_pressed = false;
}

void QEXTScaleKnob::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QEXTScaleKnob);
    if (d->m_pressed)
    {
        this->setPressedValue(e->pos());
    }
}

void QEXTScaleKnob::paintEvent(QPaintEvent *)
{
    Q_D(QEXTScaleKnob);
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
    //绘制背景圆
    this->drawBackgroundCircle(&painter);
    //绘制中心圆
    this->drawCenterCircle(&painter);

    //根据指示器形状绘制指示器
    if (d->m_pointerStyle == PointerStyle_Line)
    {
        this->drawPointerLine(&painter);
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

void QEXTScaleKnob::drawScale(QPainter *painter)
{
    Q_D(QEXTScaleKnob);
    int radius = 96;
    int offset = 10;
    painter->save();

    painter->rotate(d->m_startAngle);
    double angleStep = (360.0 - d->m_startAngle - d->m_endAngle) / d->m_scaleStep;
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);

    QPen pen;
    pen.setWidthF(5.0);
    pen.setCapStyle(Qt::RoundCap);

    double rotate = 0;
    for (int i = 0; i <= d->m_scaleStep; i++)
    {
        if (d->m_rangeBisectionEnable)
        {
            bool right = i >= (d->m_scaleStep / 2);
            if (!right)
            {
                pen.setColor((rotate < degRotate) ? d->m_textColor : d->m_percentColor);
            }
            else
            {
                pen.setColor((rotate <= degRotate) ? d->m_percentColor : d->m_textColor);
            }

            //矫正左侧值为最小值时第一格颜色
            if (d->m_value == d->m_minValue && !right)
            {
                pen.setColor(d->m_percentColor);
            }

            //矫正左侧值时中间格颜色
            if (d->m_value <= ((d->m_maxValue - d->m_minValue) / 2 + d->m_minValue) && i == (d->m_scaleStep / 2))
            {
                pen.setColor(d->m_percentColor);
            }

            //矫正中间值中间格颜色
            if (d->m_value == ((d->m_maxValue - d->m_minValue) / 2 + d->m_minValue))
            {
                pen.setColor(d->m_textColor);
            }
        }
        else
        {
            if (rotate <= degRotate)
            {
                pen.setColor(d->m_percentColor);
            }
            else
            {
                pen.setColor(d->m_textColor);
            }

            //矫正左侧值为最小值时第一格颜色
            if (d->m_value == d->m_minValue)
            {
                pen.setColor(d->m_textColor);
            }
        }

        painter->setPen(pen);
        painter->drawLine(0, radius - offset, 0, radius);
        painter->rotate(angleStep);
        rotate += angleStep;
    }

    painter->restore();
}

void QEXTScaleKnob::drawBackgroundCircle(QPainter *painter)
{
    Q_D(QEXTScaleKnob);
    int radius = 75;
    painter->save();

    QPen pen;
    pen.setWidthF(5.0);
    pen.setColor(d->m_borderColor);

    painter->setPen(pen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void QEXTScaleKnob::drawCenterCircle(QPainter *painter)
{
    Q_D(QEXTScaleKnob);
    int radius = 15;
    painter->save();

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void QEXTScaleKnob::drawPointerLine(QPainter *painter)
{
    Q_D(QEXTScaleKnob);
    int radius = 62;
    painter->save();

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    painter->setPen(QPen(color, 10, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void QEXTScaleKnob::drawPointerIndicator(QPainter *painter)
{
    Q_D(QEXTScaleKnob);
    int radius = 65;
    int offset = 8;
    painter->save();
    painter->setOpacity(0.8);

    QPolygon pts;
    pts.setPoints(3, -offset, 0, offset, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    painter->setPen(color);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QEXTScaleKnob::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(QEXTScaleKnob);
    int radius = 62;
    int offset = 8;
    painter->save();
    painter->setOpacity(0.6);

    QPolygon pts;
    pts.setPoints(3, -offset, 0, offset, 0, 0, radius);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    QPen pen;
    pen.setColor(color);
    painter->setPen(pen);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(offset - 1);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void QEXTScaleKnob::drawPointerTriangle(QPainter *painter)
{
    Q_D(QEXTScaleKnob);
    int radius = 25;
    int offset = 40;
    painter->save();

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(d->m_startAngle);
    double degRotate = (360.0 - d->m_startAngle - d->m_endAngle) / (d->m_maxValue - d->m_minValue) * (d->m_value - d->m_minValue);
    painter->rotate(degRotate);

    QColor color = d->m_percentColor;
    if (d->m_rangeBisectionEnable)
    {
        bool center = (d->m_value == (d->m_maxValue - d->m_minValue) / 2 + d->m_minValue);
        color = center ? d->m_borderColor : d->m_percentColor;
    }

    painter->setPen(color);
    painter->setBrush(color);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void QEXTScaleKnob::drawValue(QPainter *painter)
{
    Q_D(QEXTScaleKnob);
    if (!d->m_valueVisiable)
    {
        return;
    }

    int radius = 100;
    painter->save();

    QString strValue = QString::number(d->m_value, 'f', d->m_precision);
    painter->setPen(Qt::white);
    QFont font;

#if 0
    font.setPixelSize(radius * 0.5);
    painter->setFont(font);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, strValue);
#else
    font.setPixelSize(radius * 0.3);
    painter->setFont(font);
    QRect rect(-radius, -radius, radius * 2, radius * 1.65);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignBottom, strValue);
#endif

    painter->restore();
}

void QEXTScaleKnob::setPressedValue(QPointF pressedPoint)
{
    Q_D(QEXTScaleKnob);
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

double QEXTScaleKnob::minValue() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_minValue;
}

double QEXTScaleKnob::maxValue() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_maxValue;
}

double QEXTScaleKnob::value() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_value;
}

int QEXTScaleKnob::precision() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_precision;
}

int QEXTScaleKnob::scaleStep() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_scaleStep;
}

int QEXTScaleKnob::startAngle() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_startAngle;
}

int QEXTScaleKnob::endAngle() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_endAngle;
}

QColor QEXTScaleKnob::borderColor() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_borderColor;
}

QColor QEXTScaleKnob::backgroundColor() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_backgroundColor;
}

QColor QEXTScaleKnob::textColor() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_textColor;
}

QColor QEXTScaleKnob::percentColor() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_percentColor;
}

bool QEXTScaleKnob::isRangeBisectionEnable() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_rangeBisectionEnable;
}

bool QEXTScaleKnob::isValueVisiable() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_valueVisiable;
}

QEXTScaleKnob::PointerStyle QEXTScaleKnob::pointerStyle() const
{
    Q_D(const QEXTScaleKnob);
    return d->m_pointerStyle;
}

QSize QEXTScaleKnob::sizeHint() const
{
    return QSize(200, 200);
}

QSize QEXTScaleKnob::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QEXTScaleKnob::setRange(double minValue, double maxValue)
{
    Q_D(QEXTScaleKnob);
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

void QEXTScaleKnob::setRange(int minValue, int maxValue)
{
    Q_D(QEXTScaleKnob);
    this->setRange((double)minValue, (double)maxValue);
}

void QEXTScaleKnob::setMinValue(double minValue)
{
    Q_D(QEXTScaleKnob);
    this->setRange(minValue, d->m_maxValue);
}

void QEXTScaleKnob::setMaxValue(double maxValue)
{
    Q_D(QEXTScaleKnob);
    this->setRange(d->m_minValue, maxValue);
}

void QEXTScaleKnob::setValue(double value)
{
    Q_D(QEXTScaleKnob);
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

void QEXTScaleKnob::setValue(int value)
{
    Q_D(QEXTScaleKnob);
    this->setValue((double)value);
}

void QEXTScaleKnob::setPrecision(int precision)
{
    Q_D(QEXTScaleKnob);
    //最大精确度为 3
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        this->update();
    }
}

void QEXTScaleKnob::setScaleStep(int step)
{
    Q_D(QEXTScaleKnob);
    if (d->m_scaleStep != step)
    {
        d->m_scaleStep = step;
        this->update();
    }
}

void QEXTScaleKnob::setStartAngle(int angle)
{
    Q_D(QEXTScaleKnob);
    if (d->m_startAngle != angle)
    {
        d->m_startAngle = angle;
        this->update();
    }
}

void QEXTScaleKnob::setEndAngle(int angle)
{
    Q_D(QEXTScaleKnob);
    if (d->m_endAngle != angle)
    {
        d->m_endAngle = angle;
        this->update();
    }
}

void QEXTScaleKnob::setBorderColor(const QColor &color)
{
    Q_D(QEXTScaleKnob);
    if (d->m_borderColor != color)
    {
        d->m_borderColor = color;
        this->update();
    }
}

void QEXTScaleKnob::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTScaleKnob);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTScaleKnob::setTextColor(const QColor &color)
{
    Q_D(QEXTScaleKnob);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTScaleKnob::setPercentColor(const QColor &color)
{
    Q_D(QEXTScaleKnob);
    if (d->m_percentColor != color)
    {
        d->m_percentColor = color;
        this->update();
    }
}

void QEXTScaleKnob::setRangeBisectionEnable(bool enable)
{
    Q_D(QEXTScaleKnob);
    if (d->m_rangeBisectionEnable != enable)
    {
        d->m_rangeBisectionEnable = enable;
        this->update();
    }
}

void QEXTScaleKnob::setValueVisiable(bool visiable)
{
    Q_D(QEXTScaleKnob);
    if (d->m_valueVisiable != visiable)
    {
        d->m_valueVisiable = visiable;
        this->update();
    }
}

void QEXTScaleKnob::setPointerStyle(const QEXTScaleKnob::PointerStyle &style)
{
    Q_D(QEXTScaleKnob);
    if (d->m_pointerStyle != style)
    {
        d->m_pointerStyle = style;
        this->update();
    }
}
