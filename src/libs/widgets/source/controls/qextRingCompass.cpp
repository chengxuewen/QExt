/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <private/qextRingCompass_p.h>

#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QDebug>
#include <qmath.h>

QExtRingCompassPrivate::QExtRingCompassPrivate(QExtRingCompass *q)
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

QExtRingCompassPrivate::~QExtRingCompassPrivate()
{

}




QExtRingCompass::QExtRingCompass(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtRingCompassPrivate(this))
{
    this->setFont(QFont("Microsoft Yahei", 9));
}

QExtRingCompass::~QExtRingCompass()
{

}

void QExtRingCompass::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    this->drawBackground(&painter);

    this->drawFourDots(&painter);
    this->drawFourText(&painter);
    this->drawPointer(&painter);
    this->drawValue(&painter);
}

void QExtRingCompass::drawBackground(QPainter *painter)
{
    Q_D(QExtRingCompass);
    int radius = 85;
    painter->save();

    QRectF rect(-radius + d->m_borderWidth / 2, -radius + d->m_borderWidth / 2, radius * 2 - d->m_borderWidth, radius * 2 - d->m_borderWidth);

    QPen pen(d->m_borderColor, d->m_borderWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle);

    painter->setPen(pen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawEllipse(rect);
    painter->restore();
}

void QExtRingCompass::drawFourDots(QPainter *painter)
{
    Q_D(QExtRingCompass);
    int radius = 85;
    int offset = 5;
    painter->save();

    QRectF rect(-radius + d->m_borderWidth / 2, -radius + d->m_borderWidth / 2, radius * 2 - d->m_borderWidth, radius * 2 - d->m_borderWidth);

    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_northDotColor);
    painter->drawEllipse(QPointF(0, -rect.height() / 2 - 10), offset, offset);

    painter->setBrush(d->m_otherDotColor);
    painter->drawEllipse(QPointF(0, rect.height() / 2 + 10), offset, offset);
    painter->drawEllipse(QPointF(-rect.width() / 2 - 10, 0), offset, offset);
    painter->drawEllipse(QPointF(rect.width() / 2 + 10, 0), offset, offset);

    painter->restore();
}

void QExtRingCompass::drawFourText(QPainter *painter)
{
    Q_D(QExtRingCompass);
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
    QRect str1Rect = fm.boundingRect(str1);
    QRectF titleRect(-str1Rect.width() / 2, -rect.height() / 2 + offset, str1Rect.width(), fm.height());
    painter->drawText(titleRect, Qt::AlignCenter, str1);

    painter->setPen(d->m_textColor);
    painter->rotate(-90);
    QString str2 = "西";
    QRect str2Rect = fm.boundingRect(str2);
    QRectF titleRect2(-str2Rect.width() / 2, -rect.height() / 2 + offset, str2Rect.width(), fm.height());
    painter->drawText(titleRect2, Qt::AlignCenter, str2);

    painter->rotate(-90);
    QString str3 = "南";
    QRect str3Rect = fm.boundingRect(str3);
    QRectF titleRect3(-str3Rect.width() / 2, -rect.height() / 2 + offset, str3Rect.width(), fm.height());
    painter->drawText(titleRect3, Qt::AlignCenter, str3);

    painter->rotate(-90);
    QString str4 = "东";
    QRect str4Rect = fm.boundingRect(str4);
    QRectF titleRect4(-str4Rect.width() / 2, -rect.height() / 2 + offset, str4Rect.width(), fm.height());
    painter->drawText(titleRect4, Qt::AlignCenter, str4);

    painter->restore();
}

void QExtRingCompass::drawPointer(QPainter *painter)
{
    Q_D(QExtRingCompass);
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

void QExtRingCompass::drawValue(QPainter *painter)
{
    Q_D(QExtRingCompass);
    int radius = 100;
    painter->save();

    QFont font;
    font.setPixelSize(26);
    painter->setFont(font);
    painter->setPen(d->m_textColor);

    QString strValue = QString("%1°").arg(QString::number(d->m_value, 'f', 0));
    QRectF rectValue(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rectValue, Qt::AlignCenter, strValue);

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

double QExtRingCompass::value() const
{
    Q_D(const QExtRingCompass);
    return d->m_value;
}

QColor QExtRingCompass::backgroundColor() const
{
    Q_D(const QExtRingCompass);
    return d->m_backgroundColor;
}

QColor QExtRingCompass::textColor() const
{
    Q_D(const QExtRingCompass);
    return d->m_textColor;
}

QColor QExtRingCompass::borderColor() const
{
    Q_D(const QExtRingCompass);
    return d->m_borderColor;
}

int QExtRingCompass::borderWidth() const
{
    Q_D(const QExtRingCompass);
    return d->m_borderWidth;
}

QColor QExtRingCompass::northDotColor() const
{
    Q_D(const QExtRingCompass);
    return d->m_northDotColor;
}

QColor QExtRingCompass::otherDotColor() const
{
    Q_D(const QExtRingCompass);
    return d->m_otherDotColor;
}

QColor QExtRingCompass::pointerColor() const
{
    Q_D(const QExtRingCompass);
    return d->m_pointerColor;
}

QSize QExtRingCompass::sizeHint() const
{
    return QSize(200, 200);
}

QSize QExtRingCompass::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QExtRingCompass::setValue(double value)
{
    Q_D(QExtRingCompass);
    if(d->m_value != value)
    {
        d->m_value = qAbs((int)value % 360);
        this->update();
    }
}

void QExtRingCompass::setBackgroundColor(const QColor &color)
{
    Q_D(QExtRingCompass);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QExtRingCompass::setTextColor(const QColor &color)
{
    Q_D(QExtRingCompass);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}

void QExtRingCompass::setBorderColor(const QColor &color)
{
    Q_D(QExtRingCompass);
    if (d->m_borderColor != color)
    {
        d->m_borderColor = color;
        this->update();
    }
}

void QExtRingCompass::setBorderWidth(int width)
{
    Q_D(QExtRingCompass);
    if (d->m_borderWidth != width)
    {
        d->m_borderWidth = width;
        this->update();
    }
}

void QExtRingCompass::setNorthDotColor(const QColor &color)
{
    Q_D(QExtRingCompass);
    if (d->m_northDotColor != color)
    {
        d->m_northDotColor = color;
        this->update();
    }
}

void QExtRingCompass::setOtherDotColor(const QColor &color)
{
    Q_D(QExtRingCompass);
    if (d->m_otherDotColor != color)
    {
        d->m_otherDotColor = color;
        this->update();
    }
}

void QExtRingCompass::setPointerColor(const QColor &color)
{
    Q_D(QExtRingCompass);
    if (d->m_pointerColor != color)
    {
        d->m_pointerColor = color;
        this->update();
    }
}
