#include <qextSlider.h>
#include <qextSlider_p.h>
#include <qextTooltip.h>

#include <QEvent>
#include <QDebug>
#include <QMouseEvent>



QEXTSliderPrivate::QEXTSliderPrivate(QEXTSlider *q)
    : q_ptr(q)
{
    m_borderRadius = 5;
    m_arrowSize = 5;
    m_arrowStyle = QEXTSlider::ArrowStyle_Bottom;

    m_backgroundColor = QColor(100, 184, 255);
    m_foregroundColor = QColor(255, 255, 255);

    m_tooltipWidth = 50;
    m_tooltipHeight = 30;
    m_tooltipFont = q_ptr->font();

    m_timeVisiable = false;
    m_clickEnable = true;
    m_unitText = "";

    m_tooltip = new QEXTTooltip;
    m_tooltip->setBorderRadius(m_borderRadius);
    m_tooltip->setArrowSize(m_arrowSize);
    m_tooltip->setArrowPosition((QEXTTooltip::ArrowPositionType)m_arrowStyle);
    m_tooltip->setBackgroundColor(m_backgroundColor);
    m_tooltip->setForegroundColor(m_foregroundColor);
    m_tooltip->resize(m_tooltipWidth, m_tooltipHeight);
    m_tooltip->setFont(m_tooltipFont);

    m_tooltip->setFocusPolicy(Qt::NoFocus);
    m_tooltip->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    m_tooltip->setAttribute(Qt::WA_TranslucentBackground, false);
}

QEXTSliderPrivate::~QEXTSliderPrivate()
{
    m_tooltip->deleteLater();
}



QEXTSlider::QEXTSlider(QWidget *parent)
    : QSlider(parent), d_ptr(new QEXTSliderPrivate(this))
{
    this->setOrientation(Qt::Horizontal);
}

QEXTSlider::~QEXTSlider()
{

}

void QEXTSlider::mousePressEvent(QMouseEvent *e)
{
    Q_D(QEXTSlider);
    //限定必须是鼠标左键按下
    if (e->button() != Qt::LeftButton)
    {
        return;
    }

    if (d->m_clickEnable)
    {
        //获取鼠标的位置
        double pos, value;
        if (this->orientation() == Qt::Horizontal)
        {
            pos = e->pos().x() / (double)width();
            value = pos * (maximum() - minimum()) + minimum();
        }
        else
        {
            pos = e->pos().y() / (double)height();
            value = maximum() - pos * (maximum() - minimum()) + minimum();
        }

        this->setValue(value + 0.5);

        //发送自定义的鼠标单击信号
        emit clicked();
    }

    this->mouseMoveEvent(e);
    d->m_tooltip->setVisible(true);
    QSlider::mousePressEvent(e);
}

void QEXTSlider::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(QEXTSlider);
    d->m_tooltip->setVisible(false);
    QSlider::mouseReleaseEvent(e);
}

void QEXTSlider::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QEXTSlider);
    //限定必须是鼠标左键按下
    if (e->button() & Qt::RightButton)
    {
        return;
    }

    //过滤掉控件外坐标,横向的限制X轴,纵向的限制Y轴
    QPoint pos = e->pos();
    int x = pos.x();
    int y = pos.y();

    if (this->orientation() == Qt::Horizontal)
    {
        if (x < 0 || x > width())
        {
            return;
        }

        x = QCursor::pos().x();
        y = this->mapToGlobal(this->pos()).y();
        x = x - d->m_tooltipWidth / 2 + this->x();
        y = y - (d->m_arrowStyle == ArrowStyle_Top ? -height() : d->m_tooltipHeight);
    }
    else
    {
        if (y < 0 || y > height())
        {
            return;
        }

        x = this->mapToGlobal(this->pos()).x();
        y = QCursor::pos().y();
        x = x - (d->m_arrowStyle == ArrowStyle_Left ? -width() : d->m_tooltipWidth);
        y = y - d->m_tooltipHeight / 2 + this->y();
    }

    QString str = QString("%1").arg(value());

    if (d->m_timeVisiable)
    {
        uint length = value() / 1000;
        str = (QString("%1:%2").arg(length / 60, 2, 10, QChar('0')).arg(length % 60, 2, 10, QChar('0')));
    }

    d->m_tooltip->setText(QString("%1%2").arg(str).arg(d->m_unitText));
    d->m_tooltip->move(this->mapFromParent(QPoint(x, y)));
    QSlider::mouseMoveEvent(e);
}

int QEXTSlider::borderRadius() const
{
    Q_D(const QEXTSlider);
    return d->m_borderRadius;
}

int QEXTSlider::arrowSize() const
{
    Q_D(const QEXTSlider);
    return d->m_arrowSize;
}

QEXTSlider::ArrowStyleType QEXTSlider::arrowStyle() const
{
    Q_D(const QEXTSlider);
    return d->m_arrowStyle;
}

QColor QEXTSlider::backgroundColor() const
{
    Q_D(const QEXTSlider);
    return d->m_backgroundColor;
}

QColor QEXTSlider::foregroundColor() const
{
    Q_D(const QEXTSlider);
    return d->m_foregroundColor;
}

int QEXTSlider::toolTipWidth() const
{
    Q_D(const QEXTSlider);
    return d->m_tooltipWidth;
}

int QEXTSlider::toolTipHeight() const
{
    Q_D(const QEXTSlider);
    return d->m_tooltipHeight;
}

QFont QEXTSlider::toolTipFont() const
{
    Q_D(const QEXTSlider);
    return d->m_tooltipFont;
}

bool QEXTSlider::timeVisiable() const
{
    Q_D(const QEXTSlider);
    return d->m_timeVisiable;
}

bool QEXTSlider::clickEnable() const
{
    Q_D(const QEXTSlider);
    return d->m_clickEnable;
}

QString QEXTSlider::unitText() const
{
    Q_D(const QEXTSlider);
    return d->m_unitText;
}

QEXTTooltip *QEXTSlider::tooltip() const
{
    Q_D(const QEXTSlider);
    return d->m_tooltip;
}

void QEXTSlider::setBorderRadius(int radius)
{
    Q_D(QEXTSlider);
    if (d->m_borderRadius != radius)
    {
        d->m_borderRadius = radius;
        d->m_tooltip->setBorderRadius(radius);
    }
}

void QEXTSlider::setArrowSize(int size)
{
    Q_D(QEXTSlider);
    if (d->m_arrowSize != size)
    {
        d->m_arrowSize = size;
        d->m_tooltip->setArrowSize(size);
    }
}

void QEXTSlider::setArrowStyle(const QEXTSlider::ArrowStyleType &style)
{
    Q_D(QEXTSlider);
    if (d->m_arrowStyle != style)
    {
        d->m_arrowStyle = style;
        d->m_tooltip->setArrowPosition((QEXTTooltip::ArrowPositionType)style);
    }
}

void QEXTSlider::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTSlider);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        d->m_tooltip->setBackgroundColor(color);
    }
}

void QEXTSlider::setForegroundColor(const QColor &color)
{
    Q_D(QEXTSlider);
    if (d->m_foregroundColor != color)
    {
        d->m_foregroundColor = color;
        d->m_tooltip->setForegroundColor(color);
    }
}

void QEXTSlider::setToolTipWidth(int width)
{
    Q_D(QEXTSlider);
    if (d->m_tooltipWidth != width)
    {
        d->m_tooltipWidth = width;
        d->m_tooltip->resize(width, d->m_tooltipHeight);
    }
}

void QEXTSlider::setToolTipHeight(int height)
{
    Q_D(QEXTSlider);
    if (d->m_tooltipHeight != height)
    {
        d->m_tooltipHeight = height;
        d->m_tooltip->resize(d->m_tooltipWidth, height);
    }
}

void QEXTSlider::setToolTipFont(const QFont &font)
{
    Q_D(QEXTSlider);
    if (d->m_tooltipFont != font)
    {
        d->m_tooltipFont = font;
        d->m_tooltip->setFont(font);
    }
}

void QEXTSlider::setTimeVisiable(bool visiable)
{
    Q_D(QEXTSlider);
    if (d->m_timeVisiable != visiable)
    {
        d->m_timeVisiable = visiable;
    }
}

void QEXTSlider::setClickEnable(bool enable)
{
    Q_D(QEXTSlider);
    if (d->m_clickEnable != enable)
    {
        d->m_clickEnable = enable;
    }
}

void QEXTSlider::setUnitText(const QString &unit)
{
    Q_D(QEXTSlider);
    if (d->m_unitText != unit)
    {
        d->m_unitText = unit;
    }
}
