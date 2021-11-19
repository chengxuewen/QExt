#include <qextTooltip.h>
#include <qextTooltip_p.h>

#include <QPainter>
#include <QEvent>
#include <QDebug>



QEXTTooltipPrivate::QEXTTooltipPrivate(QEXTTooltip *q)
    : q_ptr(q)
{
    m_borderRadius = 5;
    m_backgroundColor = QColor(100, 184, 255);
    m_foregroundColor = QColor(255, 255, 255);

    m_arrowVisiable = true;
    m_arrowSize = 5;
    m_arrowPosition = QEXTTooltip::ArrowPosition_Right;

    m_triangleVisiable = false;
    m_triangleLen = 5;
    m_trianglePosition = QEXTTooltip::TrianglePosition_Left;
    m_triangleColor = QColor(255, 255, 255);

    m_backgroundRect = q_ptr->geometry();
}

QEXTTooltipPrivate::~QEXTTooltipPrivate()
{

}



QEXTTooltip::QEXTTooltip(QWidget *parent)
    : QLabel(parent), d_ptr(new QEXTTooltipPrivate(this))
{
    this->setFont(QFont("Microsoft Yahei", 10));
}

QEXTTooltip::~QEXTTooltip()
{

}

void QEXTTooltip::mousePressEvent(QMouseEvent *)
{
    emit this->clicked();
}

void QEXTTooltip::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    this->drawBackground(&painter);
    //绘制文字
    this->drawText(&painter);
    //绘制倒三角
    this->drawTriangle(&painter);
}

void QEXTTooltip::drawBackground(QPainter *painter)
{
    Q_D(QEXTTooltip);
    int width = this->width();
    int height = this->height();
    int endX = width - d->m_arrowSize;
    int endY = height - d->m_arrowSize;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);

    QPolygon pts;
    if (d->m_arrowPosition == ArrowPosition_Right)
    {
        d->m_backgroundRect = QRect(0, 0, endX, height);
        pts.setPoints(3, endX, height / 2 - d->m_arrowSize, endX, height / 2 + d->m_arrowSize, width, height / 2);
    }
    else if (d->m_arrowPosition == ArrowPosition_Left)
    {
        d->m_backgroundRect = QRect(d->m_arrowSize, 0, width - d->m_arrowSize, height);
        pts.setPoints(3, d->m_arrowSize, height / 2 - d->m_arrowSize, d->m_arrowSize, height / 2 + d->m_arrowSize, 0, height / 2);
    }
    else if (d->m_arrowPosition == ArrowPosition_Bottom)
    {
        d->m_backgroundRect = QRect(0, 0, width, endY);
        pts.setPoints(3, width / 2 - d->m_arrowSize, endY, width / 2 + d->m_arrowSize, endY, width / 2, height);
    }
    else if (d->m_arrowPosition == ArrowPosition_Top)
    {
        d->m_backgroundRect = QRect(0, d->m_arrowSize, width, height - d->m_arrowSize);
        pts.setPoints(3, width / 2 - d->m_arrowSize, d->m_arrowSize, width / 2 + d->m_arrowSize, d->m_arrowSize, width / 2, 0);
    }

    //绘制圆角矩形和三角箭头
    if (!d->m_arrowVisiable)
    {
        d->m_backgroundRect = this->rect();
        painter->drawRoundedRect(d->m_backgroundRect, d->m_borderRadius, d->m_borderRadius);
    }
    else
    {
        painter->drawRoundedRect(d->m_backgroundRect, d->m_borderRadius, d->m_borderRadius);
        painter->drawPolygon(pts);
    }

    painter->restore();
}

void QEXTTooltip::drawText(QPainter *painter)
{
    Q_D(QEXTTooltip);
    painter->save();
    painter->setPen(d->m_foregroundColor);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(d->m_backgroundRect, Qt::AlignCenter, this->text());
    painter->restore();
}

void QEXTTooltip::drawTriangle(QPainter *painter)
{
    Q_D(QEXTTooltip);
    if (!d->m_triangleVisiable)
    {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_triangleColor);

    //绘制在右侧中间,根据设定的倒三角的边长设定三个点位置
    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;

    QPolygon pts;
    if (d->m_trianglePosition == TrianglePosition_Left)
    {
        pts.setPoints(3, d->m_triangleLen, midHeight, 0, midHeight - d->m_triangleLen, 0, midHeight + d->m_triangleLen);
    }
    else if (d->m_trianglePosition == TrianglePosition_Right)
    {
        pts.setPoints(3, width - d->m_triangleLen, midHeight, width, midHeight - d->m_triangleLen, width, midHeight + d->m_triangleLen);
    }
    else if (d->m_trianglePosition == TrianglePosition_Top)
    {
        pts.setPoints(3, midWidth, d->m_triangleLen, midWidth - d->m_triangleLen, 0, midWidth + d->m_triangleLen, 0);
    }
    else if (d->m_trianglePosition == TrianglePosition_Bottom)
    {
        pts.setPoints(3, midWidth, height - d->m_triangleLen, midWidth - d->m_triangleLen, height, midWidth + d->m_triangleLen, height);
    }

    painter->drawPolygon(pts);

    painter->restore();
}

int QEXTTooltip::borderRadius() const
{
    Q_D(const QEXTTooltip);
    return d->m_borderRadius;
}

QColor QEXTTooltip::backgroundColor() const
{
    Q_D(const QEXTTooltip);
    return d->m_backgroundColor;
}

QColor QEXTTooltip::foregroundColor() const
{
    Q_D(const QEXTTooltip);
    return d->m_foregroundColor;
}

bool QEXTTooltip::arrowVisiable() const
{
    Q_D(const QEXTTooltip);
    return d->m_arrowVisiable;
}

int QEXTTooltip::arrowSize() const
{
    Q_D(const QEXTTooltip);
    return d->m_arrowSize;
}

QEXTTooltip::ArrowPositionType QEXTTooltip::arrowPosition() const
{
    Q_D(const QEXTTooltip);
    return d->m_arrowPosition;
}

bool QEXTTooltip::triangleVisiable() const
{
    Q_D(const QEXTTooltip);
    return d->m_triangleVisiable;
}

int QEXTTooltip::triangleLen() const
{
    Q_D(const QEXTTooltip);
    return d->m_triangleLen;
}

QEXTTooltip::TrianglePositionType QEXTTooltip::trianglePosition() const
{
    Q_D(const QEXTTooltip);
    return d->m_trianglePosition;
}

QColor QEXTTooltip::triangleColor() const
{
    Q_D(const QEXTTooltip);
    return d->m_triangleColor;
}

QSize QEXTTooltip::sizeHint() const
{
    return QSize(100, 30);
}

QSize QEXTTooltip::minimumSizeHint() const
{
    return QSize(20, 10);
}

void QEXTTooltip::setBorderRadius(int radius)
{
    Q_D(QEXTTooltip);
    if (d->m_borderRadius != radius)
    {
        d->m_borderRadius = radius;
        this->update();
    }
}

void QEXTTooltip::setArrowVisiable(bool visiable)
{
    Q_D(QEXTTooltip);
    if (d->m_arrowVisiable != visiable)
    {
        d->m_arrowVisiable = visiable;
        this->update();
    }
}

void QEXTTooltip::setArrowSize(int size)
{
    Q_D(QEXTTooltip);
    if (d->m_arrowSize != size)
    {
        d->m_arrowSize = size;
        this->update();
    }
}

void QEXTTooltip::setArrowPosition(const QEXTTooltip::ArrowPositionType &position)
{
    Q_D(QEXTTooltip);
    if (d->m_arrowPosition != position)
    {
        d->m_arrowPosition = position;
        this->update();
    }
}

void QEXTTooltip::setTriangleVisiable(bool visiable)
{
    Q_D(QEXTTooltip);
    if (d->m_triangleVisiable != visiable)
    {
        d->m_triangleVisiable = visiable;
        this->update();
    }
}

void QEXTTooltip::setTriangleLen(int len)
{
    Q_D(QEXTTooltip);
    if (d->m_triangleLen != len)
    {
        d->m_triangleLen = len;
        this->update();
    }
}

void QEXTTooltip::setTrianglePosition(const QEXTTooltip::TrianglePositionType &position)
{
    Q_D(QEXTTooltip);
    if (d->m_trianglePosition != position)
    {
        d->m_trianglePosition = position;
        this->update();
    }
}

void QEXTTooltip::setTriangleColor(const QColor &color)
{
    Q_D(QEXTTooltip);
    if (d->m_triangleColor != color)
    {
        d->m_triangleColor = color;
        this->update();
    }
}

void QEXTTooltip::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTTooltip);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTTooltip::setForegroundColor(const QColor &color)
{
    Q_D(QEXTTooltip);
    if (d->m_foregroundColor != color)
    {
        d->m_foregroundColor = color;
        this->update();
    }
}

