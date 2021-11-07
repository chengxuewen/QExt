#pragma execution_character_set("utf-8")

#include <qextRingCompass.h>
#include <qextRingCompass_p.h>

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <qmath.h>


QEXTRingCompassPrivate::QEXTRingCompassPrivate(QEXTRingCompass *q)
    : q_ptr(q)
{
    m_value = 0;
    m_backgroundColor = QColor(40, 45, 48);
    m_textColor = QColor(187, 191, 194);
    m_borderColor = QColor(34, 163, 169);
    m_borderWidth = 5;

    m_northDotColor = QColor(214, 77, 84);
    m_otherDotColor = QColor(37, 40, 49);
    m_pointerColor = QColor(214, 77, 84);
}

QEXTRingCompassPrivate::~QEXTRingCompassPrivate()
{

}




QEXTRingCompass::QEXTRingCompass(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTRingCompassPrivate(this))
{
    this->setFont(QFont("Microsoft Yahei", 9));
}

QEXTRingCompass::~QEXTRingCompass()
{

}

void QEXTRingCompass::paintEvent(QPaintEvent *)
{
    QEXT_DECL_D(QEXTRingCompass);
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
    //绘制四个方向点
    this->drawFourDots(&painter);
    //绘制四个方向文字
    this->drawFourText(&painter);
    //绘制指针
    this->drawPointer(&painter);
    //绘制当前值
    this->drawValue(&painter);
}

void QEXTRingCompass::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTRingCompass);
    int radius = 85;
    painter->save();

    QRectF rect(-radius + d->m_borderWidth / 2, -radius + d->m_borderWidth / 2, radius * 2 - d->m_borderWidth, radius * 2 - d->m_borderWidth);
    //可以自行修改画笔的后三个参数,形成各种各样的效果,例如Qt::FlatCap改为Qt::RoundCap可以产生圆角效果
    QPen pen(d->m_borderColor, d->m_borderWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    //绘制圆
    painter->setPen(pen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawEllipse(rect);
    painter->restore();
}

void QEXTRingCompass::drawFourDots(QPainter *painter)
{
    QEXT_DECL_D(QEXTRingCompass);
    int radius = 85;
    int offset = 5;
    painter->save();

    QRectF rect(-radius + d->m_borderWidth / 2, -radius + d->m_borderWidth / 2, radius * 2 - d->m_borderWidth, radius * 2 - d->m_borderWidth);

    //绘制正北点
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_northDotColor);
    painter->drawEllipse(QPointF(0, -rect.height() / 2 - 10), offset, offset);

    //绘制其他方向点
    painter->setBrush(d->m_otherDotColor);
    painter->drawEllipse(QPointF(0, rect.height() / 2 + 10), offset, offset);
    painter->drawEllipse(QPointF(-rect.width() / 2 - 10, 0), offset, offset);
    painter->drawEllipse(QPointF(rect.width() / 2 + 10, 0), offset, offset);

    painter->restore();
}

void QEXTRingCompass::drawFourText(QPainter *painter)
{
    QEXT_DECL_D(QEXTRingCompass);
    int radius = 85;
    int offset = 5;
    painter->save();

    QRectF rect(-radius + d->m_borderWidth / 2, -radius + d->m_borderWidth / 2, radius * 2 - d->m_borderWidth, radius * 2 - d->m_borderWidth);

    QFont font;
    font.setPixelSize(15);
    painter->setFont(font);
    painter->setPen(d->m_northDotColor);
    QFontMetrics fm = painter->fontMetrics();

    QString str1 = "北";
    QRectF titleRect(-fm.width(str1) / 2, -rect.height() / 2 + offset, fm.width(str1), fm.height());
    painter->drawText(titleRect, Qt::AlignCenter, str1);

    painter->setPen(d->m_textColor);
    painter->rotate(-90);
    QString str2 = "西";
    QRectF titleRect2(-fm.width(str2) / 2, -rect.height() / 2 + offset, fm.width(str2), fm.height());
    painter->drawText(titleRect2, Qt::AlignCenter, str2);

    painter->rotate(-90);
    QString str3 = "南";
    QRectF titleRect3(-fm.width(str3) / 2, -rect.height() / 2 + offset, fm.width(str3), fm.height());
    painter->drawText(titleRect3, Qt::AlignCenter, str3);

    painter->rotate(-90);
    QString str4 = "东";
    QRectF titleRect4(-fm.width(str4) / 2, -rect.height() / 2 + offset, fm.width(str4), fm.height());
    painter->drawText(titleRect4, Qt::AlignCenter, str4);

    painter->restore();
}

void QEXTRingCompass::drawPointer(QPainter *painter)
{
    QEXT_DECL_D(QEXTRingCompass);
    int radius = 45;
    painter->save();

    QPolygon polygon;
    polygon.append(QPoint(radius, 0));
    polygon.append(QPoint(-radius, 0));
    polygon.append(QPoint(0, -radius - 10));
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_pointerColor);

    QPainterPath painterPath;
    painterPath.addPolygon(polygon);

    QPainterPath painterPath2;
    painterPath2.addEllipse(QPoint(0, 0), radius, radius);

    QPainterPath painterPath3;
    painterPath3.addEllipse(QPoint(0, 0), radius - 6, radius - 6);

    painter->rotate(d->m_value);
    painter->drawPath(painterPath2 - painterPath3);
    painter->fillPath(painterPath + painterPath2 - painterPath3, QBrush(d->m_pointerColor));
    painter->restore();
}

void QEXTRingCompass::drawValue(QPainter *painter)
{
    QEXT_DECL_D(QEXTRingCompass);
    int radius = 100;
    painter->save();

    QFont font;
    font.setPixelSize(26);
    painter->setFont(font);
    painter->setPen(d->m_textColor);

    //画数值
    QString strValue = QString("%1°").arg(QString::number(d->m_value, 'f', 0));
    QRectF rectValue(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rectValue, Qt::AlignCenter, strValue);

    //画方向
    QString strPosition;
    if(d->m_value >= 0 && d->m_value < 90)
    {
        if(d->m_value == 0)
        {
            strPosition = "正北";
        }
        else
        {
            strPosition = "东北";
        }
    }
    else if(d->m_value >= 90 && d->m_value < 180)
    {
        if(d->m_value == 90)
        {
            strPosition = "正东";
        }
        else
        {
            strPosition = "东南";
        }
    }
    else if(d->m_value >= 180 && d->m_value < 270)
    {
        if(d->m_value == 180)
        {
            strPosition = "正南";
        }
        else
        {
            strPosition = "西南";
        }
    }
    else if(d->m_value >= 270 && d->m_value < 360)
    {
        if(d->m_value == 270)
        {
            strPosition = "正西";
        }
        else
        {
            strPosition = "西北";
        }
    }

    font.setPixelSize(10);
    painter->setFont(font);
    painter->setPen(Qt::gray);
    QRectF rectPosition(-radius, 12, radius * 2, radius * 2);
    painter->drawText(rectPosition, Qt::AlignHCenter | Qt::AlignTop, strPosition);
    painter->restore();
}

double QEXTRingCompass::value() const
{
    QEXT_DECL_DC(QEXTRingCompass);
    return d->m_value;
}

QColor QEXTRingCompass::backgroundColor() const
{
    QEXT_DECL_DC(QEXTRingCompass);
    return d->m_backgroundColor;
}

QColor QEXTRingCompass::textColor() const
{
    QEXT_DECL_DC(QEXTRingCompass);
    return d->m_textColor;
}

QColor QEXTRingCompass::borderColor() const
{
    QEXT_DECL_DC(QEXTRingCompass);
    return d->m_borderColor;
}

int QEXTRingCompass::borderWidth() const
{
    QEXT_DECL_DC(QEXTRingCompass);
    return d->m_borderWidth;
}

QColor QEXTRingCompass::northDotColor() const
{
    QEXT_DECL_DC(QEXTRingCompass);
    return d->m_northDotColor;
}

QColor QEXTRingCompass::otherDotColor() const
{
    QEXT_DECL_DC(QEXTRingCompass);
    return d->m_otherDotColor;
}

QColor QEXTRingCompass::pointerColor() const
{
    QEXT_DECL_DC(QEXTRingCompass);
    return d->m_pointerColor;
}

QSize QEXTRingCompass::sizeHint() const
{
    return QSize(200, 200);
}

QSize QEXTRingCompass::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QEXTRingCompass::setValue(double value)
{
    QEXT_DECL_D(QEXTRingCompass);
    if(d->m_value != value)
    {
        d->m_value = qAbs((int)value % 360);
        this->update();
    }
}

void QEXTRingCompass::setBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTRingCompass);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTRingCompass::setTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTRingCompass);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTRingCompass::setBorderColor(const QColor &color)
{
    QEXT_DECL_D(QEXTRingCompass);
    if (d->m_borderColor != color)
    {
        d->m_borderColor = color;
        this->update();
    }
}

void QEXTRingCompass::setBorderWidth(int width)
{
    QEXT_DECL_D(QEXTRingCompass);
    if (d->m_borderWidth != width)
    {
        d->m_borderWidth = width;
        this->update();
    }
}

void QEXTRingCompass::setNorthDotColor(const QColor &color)
{
    QEXT_DECL_D(QEXTRingCompass);
    if (d->m_northDotColor != color)
    {
        d->m_northDotColor = color;
        this->update();
    }
}

void QEXTRingCompass::setOtherDotColor(const QColor &color)
{
    QEXT_DECL_D(QEXTRingCompass);
    if (d->m_otherDotColor != color)
    {
        d->m_otherDotColor = color;
        this->update();
    }
}

void QEXTRingCompass::setPointerColor(const QColor &color)
{
    QEXT_DECL_D(QEXTRingCompass);
    if (d->m_pointerColor != color)
    {
        d->m_pointerColor = color;
        this->update();
    }
}
