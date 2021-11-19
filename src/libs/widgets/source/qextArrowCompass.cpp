#include <qextArrowCompass.h>
#include <qextArrowCompass_p.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <qmath.h>



QEXTArrowCompassPrivate::QEXTArrowCompassPrivate(QEXTArrowCompass *q)
    : q_ptr(q)
{
    m_value = 0;
    m_precision = 0;

    m_crownColorStart = QColor(125, 32, 36);
    m_crownColorEnd = QColor(227, 77, 77);

    m_backgroundStartColor = QColor(81, 97, 113);
    m_backgroundEndColor = QColor(28, 34, 40);

    m_darkColor = QColor(51, 60, 75);
    m_lightColor = QColor(109, 134, 162);

    m_foregroundColor = QColor(255, 255, 255);
    m_textColor = QColor(20, 20, 20);

    m_northPointerColor = QColor(255, 107, 107);
    m_southPointerColor = QColor(100, 184, 255);

    m_centerStartColor = QColor(230, 230, 230);
    m_centerEndColor = QColor(210, 210, 210);

    m_animationVisiable = false;
    m_currentValue = 0;
}

QEXTArrowCompassPrivate::~QEXTArrowCompassPrivate()
{

}


QEXTArrowCompass::QEXTArrowCompass(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTArrowCompassPrivate(this))
{
    Q_D(QEXTArrowCompass);
    d->m_animation = new QPropertyAnimation(this, "");
    d->m_animation->setDuration(500);
    d->m_animation->setEasingCurve(QEasingCurve::Linear);
    connect(d->m_animation, SIGNAL(valueChanged(QVariant)), this, SLOT(updateValue(QVariant)));

    this->setFont(QFont("Arial", 9));
}

QEXTArrowCompass::~QEXTArrowCompass()
{

}

void QEXTArrowCompass::paintEvent(QPaintEvent *)
{
    Q_D(QEXTArrowCompass);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外边框圆
    this->drawCrownCircle(&painter);
    //绘制背景圆
    this->drawBackgroundCircle(&painter);
    //绘制刻度
    this->drawScale(&painter);
    //绘制东南西北标识
    this->drawScaleNum(&painter);
    //绘制覆盖圆外圆
    this->drawCoverOuterCircle(&painter);
    //绘制覆盖圆内圆
    this->drawCoverInnerCircle(&painter);
    //绘制覆盖圆中心圆
    this->drawCoverCenterCircle(&painter);
    //绘制南北指针
    this->drawPointer(&painter);
    //绘制中心圆
    this->drawCenterCircle(&painter);
    //绘制当前值
    this->drawValue(&painter);
}

void QEXTArrowCompass::drawCrownCircle(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_crownColorStart);
    lineGradient.setColorAt(1, d->m_crownColorEnd);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTArrowCompass::drawBackgroundCircle(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_backgroundStartColor);
    lineGradient.setColorAt(1, d->m_backgroundEndColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTArrowCompass::drawScale(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 85;
    painter->save();

    //总共8格,4格为NESW字母,4格为线条
    int steps = 8;
    double angleStep = 360.0 / steps;

    QPen pen;
    pen.setColor(d->m_foregroundColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(4);
    painter->setPen(pen);

    //%2整数部分绘制NESW字母,其余绘制线条刻度
    for (int i = 0; i <= steps; i++)
    {
        if (i % 2 != 0)
        {
            painter->drawLine(0, radius - 10, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void QEXTArrowCompass::drawScaleNum(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 88;
    painter->save();
    painter->setPen(d->m_foregroundColor);

    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    painter->setFont(font);

    QRect textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, "N");
    painter->drawText(textRect, Qt::AlignBottom | Qt::AlignHCenter, "S");

    radius -= 2;
    textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, "W");

    radius -= 2;
    textRect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, "E");

    painter->restore();
}

void QEXTArrowCompass::drawCoverOuterCircle(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 68;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_lightColor);
    lineGradient.setColorAt(1, d->m_darkColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTArrowCompass::drawCoverInnerCircle(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_darkColor);
    lineGradient.setColorAt(1, d->m_lightColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTArrowCompass::drawCoverCenterCircle(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.8);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_lightColor);
    lineGradient.setColorAt(1, d->m_darkColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTArrowCompass::drawPointer(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 75;

    QPolygon pts;

    painter->save();
    painter->setOpacity(0.7);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_northPointerColor);
    pts.setPoints(3, -10, 0, 10, 0, 0, radius);
    painter->rotate(d->m_currentValue + 180);
    painter->drawConvexPolygon(pts);
    painter->restore();

    painter->save();
    painter->setOpacity(0.7);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_southPointerColor);
    pts.setPoints(3, -10, 0, 10, 0, 0, radius);
    painter->rotate(d->m_currentValue);
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void QEXTArrowCompass::drawCenterCircle(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 12;
    painter->save();
    painter->setOpacity(1.0);
    painter->setPen(Qt::NoPen);
    QLinearGradient lineGradient(0, -radius, 0, radius);
    lineGradient.setColorAt(0, d->m_centerStartColor);
    lineGradient.setColorAt(1, d->m_centerEndColor);
    painter->setBrush(lineGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void QEXTArrowCompass::drawValue(QPainter *painter)
{
    Q_D(QEXTArrowCompass);
    int radius = 100;
    painter->save();
    painter->setPen(d->m_textColor);

    QFont font;
    font.setPixelSize(11);
    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)d->m_value, 0, 'f', d->m_precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}


void QEXTArrowCompass::updateValue(const QVariant &value)
{
    Q_D(QEXTArrowCompass);
    const double animationValue = value.toDouble();
    if (animationValue != d->m_currentValue)
    {
        d->m_currentValue = animationValue;
        this->update();
    }
}

double QEXTArrowCompass::value() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_value;
}

int QEXTArrowCompass::precision() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_precision;
}

bool QEXTArrowCompass::animationEnable() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_animationVisiable;
}

int QEXTArrowCompass::animationDuration() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_animation->duration();
}

QEasingCurve::Type QEXTArrowCompass::animationEasingCurve() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_animation->easingCurve().type();
}

QColor QEXTArrowCompass::crownStartColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_crownColorStart;
}

QColor QEXTArrowCompass::crownEndColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_crownColorEnd;
}

QColor QEXTArrowCompass::backgroundStartColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_backgroundStartColor;
}

QColor QEXTArrowCompass::backgroundEndColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_backgroundEndColor;
}

QColor QEXTArrowCompass::darkColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_darkColor;
}

QColor QEXTArrowCompass::lightColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_lightColor;
}

QColor QEXTArrowCompass::foregroundColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_foregroundColor;
}

QColor QEXTArrowCompass::textColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_textColor;
}

QColor QEXTArrowCompass::northPointerColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_northPointerColor;
}

QColor QEXTArrowCompass::southPointerColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_southPointerColor;
}

QColor QEXTArrowCompass::centerStartColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_centerStartColor;
}

QColor QEXTArrowCompass::centerEndColor() const
{
    Q_D(const QEXTArrowCompass);
    return d->m_centerEndColor;
}

QSize QEXTArrowCompass::sizeHint() const
{
    return QSize(200, 200);
}

QSize QEXTArrowCompass::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QEXTArrowCompass::setValue(double value)
{
    Q_D(QEXTArrowCompass);
    //值和当前值一致则无需处理
    if (value == d->m_value)
    {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < 0)
    {
        value = 0;
    }
    else if (value > 360)
    {
        value = 360;
    }

    d->m_value = value;
    emit this->valueChanged(value);

    if (!d->m_animationVisiable)
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

void QEXTArrowCompass::setValue(int value)
{
    this->setValue((double)value);
}

void QEXTArrowCompass::setPrecision(int precision)
{
    Q_D(QEXTArrowCompass);
    //最大精确度为 3
    if (precision <= 3 && d->m_precision != precision)
    {
        d->m_precision = precision;
        this->update();
    }
}

void QEXTArrowCompass::setAnimationEnable(bool enable)
{
    Q_D(QEXTArrowCompass);
    if (d->m_animationVisiable != enable)
    {
        d->m_animationVisiable = enable;
        this->update();
    }
}

void QEXTArrowCompass::setAnimationDuration(int duration)
{
    Q_D(QEXTArrowCompass);
    if (duration <= 0)
    {
        qCritical() << "QEXTArrowCompass::setAnimationDuration():duration must greater than 0";
        return;
    }
    if (d->m_animation->duration() != duration)
    {
        d->m_animation->setDuration(duration);
    }
}

void QEXTArrowCompass::setAnimationEasingCurve(QEasingCurve::Type easingCurve)
{
    Q_D(QEXTArrowCompass);
    d->m_animation->setEasingCurve(easingCurve);
}

void QEXTArrowCompass::setCrownStartColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_crownColorStart != color)
    {
        d->m_crownColorStart = color;
        this->update();
    }
}

void QEXTArrowCompass::setCrownEndColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_crownColorEnd != color)
    {
        d->m_crownColorEnd = color;
        this->update();
    }
}

void QEXTArrowCompass::setBackgroundStartColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_backgroundStartColor != color)
    {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setBackgroundEndColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_backgroundEndColor != color)
    {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setDarkColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_darkColor != color)
    {
        d->m_darkColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setLightColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_lightColor != color)
    {
        d->m_lightColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setForegroundColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_foregroundColor != color)
    {
        d->m_foregroundColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setTextColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setNorthPointerColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_northPointerColor != color)
    {
        d->m_northPointerColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setSouthPointerColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_southPointerColor != color)
    {
        d->m_southPointerColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setCenterStartColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_centerStartColor != color)
    {
        d->m_centerStartColor = color;
        this->update();
    }
}

void QEXTArrowCompass::setCenterEndColor(const QColor &color)
{
    Q_D(QEXTArrowCompass);
    if (d->m_centerEndColor != color)
    {
        d->m_centerEndColor = color;
        this->update();
    }
}
