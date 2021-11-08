#pragma execution_character_set("utf-8")

#include <qextProgressRing.h>
#include <qextProgressRing_p.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <qmath.h>


QEXTProgressRingPrivate::QEXTProgressRingPrivate(QEXTProgressRing *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;
    m_precision = 0;
    m_text = "";

    m_clockWise = true;
    m_showPercent = false;
    m_alarmMode = 0;
    m_startAngle = 90;
    m_ringPadding = 3;
    m_ringWidth = 15;

    m_backgroundColor = QColor(250, 250, 250);
    m_circleColor = QColor(240, 240, 240);
    m_ringColor = QColor(23, 160, 134);
    m_ringBackgroundColor = QColor(250, 250, 250);
    m_textColor = QColor(50, 50, 50);

    m_ringValue1 = 10;
    m_ringValue2 = 30;
    m_ringValue3 = 70;

    m_ringColor1 = QColor(24, 189, 155);
    m_ringColor2 = QColor(255, 192, 0);
    m_ringColor3 = QColor(255, 107, 107);

    m_animationEnable = false;
    m_currentValue = 0;
}

QEXTProgressRingPrivate::~QEXTProgressRingPrivate()
{

}




QEXTProgressRing::QEXTProgressRing(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTProgressRingPrivate(this))
{
    QEXT_DECL_D(QEXTProgressRing);
    d->m_animation = new QPropertyAnimation(this);
    d->m_animation->setDuration(500);
    connect(d->m_animation, SIGNAL(valueChanged(QVariant)), this, SLOT(updateValue(QVariant)));
    this->setFont(QFont("Arial", 8));
}

QEXTProgressRing::~QEXTProgressRing()
{

}

void QEXTProgressRing::paintEvent(QPaintEvent *)
{
    QEXT_DECL_D(QEXTProgressRing);
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
    //绘制进度
    this->drawRing(&painter);

    //绘制间隔,重新绘制一个圆遮住,产生间距效果
    if (d->m_ringPadding > 0)
    {
        this->drawPadding(&painter);
    }

    //绘制中间圆
    this->drawCircle(&painter);
    //绘制当前值
    this->drawValue(&painter);
}

void QEXTProgressRing::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressRing);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    //这里有个技巧,如果没有间距则设置成圆环的背景色
    painter->setBrush(d->m_ringPadding == 0 ? d->m_ringBackgroundColor : d->m_backgroundColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTProgressRing::drawRing(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressRing);
    int radius = 99 - d->m_ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_ringColor);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0;
    double angleCurrent = angleAll * ((d->m_currentValue - d->m_minValue) / (d->m_maxValue - d->m_minValue));
    double angleOther = angleAll - angleCurrent;

    //如果逆时针
    if (!d->m_clockWise)
    {
        angleCurrent = -angleCurrent;
        angleOther = -angleOther;
    }

    //动态设置当前进度颜色
    QColor color = d->m_ringColor;
    if (d->m_alarmMode == 1)
    {
        if (d->m_currentValue >= d->m_ringValue3)
        {
            color = d->m_ringColor3;
        }
        else if (d->m_currentValue >= d->m_ringValue2)
        {
            color = d->m_ringColor2;
        }
        else
        {
            color = d->m_ringColor1;
        }
    }
    else if (d->m_alarmMode == 2)
    {
        if (d->m_currentValue <= d->m_ringValue1)
        {
            color = d->m_ringColor1;
        }
        else if (d->m_currentValue <= d->m_ringValue2)
        {
            color = d->m_ringColor2;
        }
        else
        {
            color = d->m_ringColor3;
        }
    }

    //绘制当前值饼圆
    painter->setBrush(color);
    painter->drawPie(rect, (d->m_startAngle - angleCurrent) * 16, angleCurrent * 16);

    //绘制剩余值饼圆
    painter->setBrush(d->m_ringBackgroundColor);
    painter->drawPie(rect, (d->m_startAngle - angleCurrent - angleOther) * 16, angleOther * 16);

    painter->restore();
}

void QEXTProgressRing::drawPadding(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressRing);
    int radius = 99 - d->m_ringWidth - d->m_ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTProgressRing::drawCircle(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressRing);
    //文字的区域要减去进度的宽度及间距
    int radius = 99 - d->m_ringWidth - (d->m_ringPadding * 2);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTProgressRing::drawValue(QPainter *painter)
{
    QEXT_DECL_D(QEXTProgressRing);
    //文字的区域要减去进度的宽度及间距
    int radius = 99 - d->m_ringWidth - (d->m_ringPadding * 2);
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    int fontSize = radius - (d->m_showPercent ? 20 : 6);
    font.setPixelSize(fontSize);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue;
    if (d->m_showPercent)
    {
        double percent = (d->m_currentValue * 100) / (d->m_maxValue - d->m_minValue);
        strValue = QString("%1%").arg(percent, 0, 'f', d->m_precision);
    }
    else
    {
        strValue = QString("%1").arg(d->m_currentValue, 0, 'f', d->m_precision);
    }

    //如果定义了显示的文字则优先显示
    strValue = d->m_text.isEmpty() ? strValue : d->m_text;
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void QEXTProgressRing::updateValue(const QVariant &value)
{
    QEXT_DECL_D(QEXTProgressRing);
    const double animationValue = value.toDouble();
    if (animationValue != d->m_currentValue)
    {
        d->m_currentValue = animationValue;
        this->update();
    }
}

double QEXTProgressRing::minValue() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_minValue;
}

double QEXTProgressRing::maxValue() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_maxValue;
}

double QEXTProgressRing::getValue() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_value;
}

int QEXTProgressRing::precision() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_precision;
}

QString QEXTProgressRing::text() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_text;
}

bool QEXTProgressRing::clipCenter() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_clipCenter;
}

bool QEXTProgressRing::clockWise() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_clockWise;
}

bool QEXTProgressRing::percentVisiable() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_showPercent;
}

int QEXTProgressRing::alarmMode() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_alarmMode;
}

int QEXTProgressRing::startAngle() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_startAngle;
}

int QEXTProgressRing::ringPadding() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringPadding;
}

int QEXTProgressRing::ringWidth() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringWidth;
}

bool QEXTProgressRing::animationEnable() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_animationEnable;
}

int QEXTProgressRing::animationDuration() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_animation->duration();
}

QEasingCurve::Type QEXTProgressRing::animationEasingCurve() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_animation->easingCurve().type();
}

QColor QEXTProgressRing::backgroundColor() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_backgroundColor;
}

QColor QEXTProgressRing::textColor() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_textColor;
}

QColor QEXTProgressRing::ringColor() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringColor;
}

QColor QEXTProgressRing::ringBackgroundColor() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringBackgroundColor;
}

QColor QEXTProgressRing::circleColor() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_circleColor;
}

int QEXTProgressRing::ringValue1() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringValue1;
}

int QEXTProgressRing::ringValue2() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringValue2;
}

int QEXTProgressRing::ringValue3() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringValue3;
}

QColor QEXTProgressRing::ringColor1() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringColor1;
}

QColor QEXTProgressRing::ringColor2() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringColor2;
}

QColor QEXTProgressRing::ringColor3() const
{
    QEXT_DECL_DC(QEXTProgressRing);
    return d->m_ringColor3;
}

QSize QEXTProgressRing::sizeHint() const
{
    return QSize(200, 200);
}

QSize QEXTProgressRing::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QEXTProgressRing::setRange(double minValue, double maxValue)
{
    QEXT_DECL_D(QEXTProgressRing);
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
        setValue(d->m_value);
    }

    this->update();
}

void QEXTProgressRing::setRange(int minValue, int maxValue)
{
    QEXT_DECL_D(QEXTProgressRing);
    this->setRange((double)minValue, (double)maxValue);
}

void QEXTProgressRing::setMinValue(double minValue)
{
    QEXT_DECL_D(QEXTProgressRing);
    this->setRange(minValue, d->m_maxValue);
}

void QEXTProgressRing::setMaxValue(double maxValue)
{
    QEXT_DECL_D(QEXTProgressRing);
    this->setRange(d->m_minValue, maxValue);
}

void QEXTProgressRing::setValue(double value)
{
    QEXT_DECL_D(QEXTProgressRing);
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

    if (!d->m_animationEnable)
    {
        d->m_currentValue = d->m_value;
        this->update();
    }
    else
    {
        d->m_animation->setStartValue(d->m_currentValue);
        d->m_animation->setEndValue(d->m_value);
        d->m_animation->start();
    }
}

void QEXTProgressRing::setValue(int value)
{
    QEXT_DECL_D(QEXTProgressRing);
    this->setValue((double)value);
}

void QEXTProgressRing::setPrecision(int precision)
{
    QEXT_DECL_D(QEXTProgressRing);
    //最大精确度为 3
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        this->update();
    }
}

void QEXTProgressRing::setText(const QString &text)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_text != text)
    {
        d->m_text = text;
        this->update();
    }
}

void QEXTProgressRing::setClipCenter(bool clipCenter)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_clipCenter != clipCenter)
    {
        d->m_clipCenter = clipCenter;
        this->update();
    }
}

void QEXTProgressRing::setClockWise(bool clockWise)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_clockWise != clockWise)
    {
        d->m_clockWise = clockWise;
        this->update();
    }
}

void QEXTProgressRing::setPercentVisiable(bool visiable)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_showPercent != visiable)
    {
        d->m_showPercent = visiable;
        this->update();
    }
}

void QEXTProgressRing::setAlarmMode(int alarmMode)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_alarmMode != alarmMode)
    {
        d->m_alarmMode = alarmMode;
        this->update();
    }
}

void QEXTProgressRing::setStartAngle(int startAngle)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_startAngle != startAngle)
    {
        d->m_startAngle = startAngle;
        this->update();
    }
}

void QEXTProgressRing::setRingPadding(int padding)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringPadding != padding)
    {
        d->m_ringPadding = padding;
        this->update();
    }
}

void QEXTProgressRing::setRingWidth(int width)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringWidth != width)
    {
        d->m_ringWidth = width;
        this->update();
    }
}

void QEXTProgressRing::setAnimationEnable(bool enable)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_animationEnable != enable)
    {
        d->m_animationEnable = enable;
        this->update();
    }
}

void QEXTProgressRing::setAnimationDuration(int duration)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_animation->duration() != duration)
    {
        d->m_animation->setDuration(duration);
        this->update();
    }
}

void QEXTProgressRing::setAnimationEasingCurve(QEasingCurve::Type easingCurve)
{
    QEXT_DECL_D(QEXTProgressRing);
    d->m_animation->setEasingCurve(easingCurve);
}

void QEXTProgressRing::setBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTProgressRing::setTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTProgressRing::setRingColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringColor != color)
    {
        d->m_ringColor = color;
        this->update();
    }
}

void QEXTProgressRing::setRingBgColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringBackgroundColor != color)
    {
        d->m_ringBackgroundColor = color;
        this->update();
    }
}

void QEXTProgressRing::setCircleColor(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_circleColor != color)
    {
        d->m_circleColor = color;
        this->update();
    }
}

void QEXTProgressRing::setRingValue1(int value)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringValue1 != value)
    {
        d->m_ringValue1 = value;
        this->update();
    }
}

void QEXTProgressRing::setRingValue2(int value)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringValue2 != value)
    {
        d->m_ringValue2 = value;
        this->update();
    }
}

void QEXTProgressRing::setRingValue3(int value)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringValue3 != value)
    {
        d->m_ringValue3 = value;
        this->update();
    }
}

void QEXTProgressRing::setRingColor1(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringColor1 != color)
    {
        d->m_ringColor1 = color;
        this->update();
    }
}

void QEXTProgressRing::setRingColor2(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringColor2 != color)
    {
        d->m_ringColor2 = color;
        this->update();
    }
}

void QEXTProgressRing::setRingColor3(const QColor &color)
{
    QEXT_DECL_D(QEXTProgressRing);
    if (d->m_ringColor3 != color)
    {
        d->m_ringColor3 = color;
        this->update();
    }
}
