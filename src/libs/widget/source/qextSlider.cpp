#pragma execution_character_set("utf-8")

#include <qextSlider.h>
#include <qextTooltip.h>

#include <QEvent>
#include <QDebug>
#include <QMouseEvent>

QEXTSlider::QEXTSlider(QWidget *parent) : QSlider(parent)
{
    borderRadius = 5;
    arrowSize = 5;
    arrowStyle = ArrowStyle_Bottom;

    background = QColor(100, 184, 255);
    foreground = QColor(255, 255, 255);

    labTipWidth = 50;
    labTipHeight = 30;
    labTipFont = this->font();

    showTime = false;
    clickEnable = true;
    unit = "";

    labTip = new QEXTTooltip;
    labTip->setBorderRadius(borderRadius);
    labTip->setArrowSize(arrowSize);
    labTip->setArrowPosition((QEXTTooltip::ArrowPosition)arrowStyle);
    labTip->setBackground(background);
    labTip->setForeground(foreground);
    labTip->resize(labTipWidth, labTipHeight);
    labTip->setFont(labTipFont);

    labTip->setFocusPolicy(Qt::NoFocus);
    labTip->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    labTip->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setOrientation(Qt::Horizontal);
}

QEXTSlider::~QEXTSlider()
{
    labTip->deleteLater();
}

void QEXTSlider::mousePressEvent(QMouseEvent *e)
{
    //限定必须是鼠标左键按下
    if (e->button() != Qt::LeftButton) {
        return;
    }

    if (clickEnable) {
        //获取鼠标的位置
        double pos, value;
        if (orientation() == Qt::Horizontal) {
            pos = e->pos().x() / (double)width();
            value = pos * (maximum() - minimum()) + minimum();
        } else {
            pos = e->pos().y() / (double)height();
            value = maximum() - pos * (maximum() - minimum()) + minimum();
        }

        setValue(value + 0.5);

        //发送自定义的鼠标单击信号
        emit clicked();
    }

    mouseMoveEvent(e);
    labTip->setVisible(true);
    QSlider::mousePressEvent(e);
}

void QEXTSlider::mouseReleaseEvent(QMouseEvent *e)
{
    labTip->setVisible(false);
    QSlider::mouseReleaseEvent(e);
}

void QEXTSlider::mouseMoveEvent(QMouseEvent *e)
{
    //限定必须是鼠标左键按下
    if (e->button() & Qt::RightButton) {
        return;
    }

    //过滤掉控件外坐标,横向的限制X轴,纵向的限制Y轴
    QPoint pos = e->pos();
    int x = pos.x();
    int y = pos.y();

    if (orientation() == Qt::Horizontal) {
        if (x < 0 || x > width()) {
            return;
        }

        x = QCursor::pos().x();
        y = mapToGlobal(this->pos()).y();
        x = x - labTipWidth / 2 + this->x();
        y = y - (arrowStyle == ArrowStyle_Top ? -height() : labTipHeight);
    } else {
        if (y < 0 || y > height()) {
            return;
        }

        x = mapToGlobal(this->pos()).x();
        y = QCursor::pos().y();
        x = x - (arrowStyle == ArrowStyle_Left ? -width() : labTipWidth);
        y = y - labTipHeight / 2 + this->y();
    }

    QString str = QString("%1").arg(value());

    if (showTime) {
        uint length = value() / 1000;
        str = (QString("%1:%2").arg(length / 60, 2, 10, QChar('0')).arg(length % 60, 2, 10, QChar('0')));
    }

    labTip->setText(QString("%1%2").arg(str).arg(unit));
    labTip->move(this->mapFromParent(QPoint(x, y)));
    QSlider::mouseMoveEvent(e);
}

int QEXTSlider::getBorderRadius() const
{
    return this->borderRadius;
}

int QEXTSlider::getArrowSize() const
{
    return this->arrowSize;
}

QEXTSlider::ArrowStyle QEXTSlider::getArrowStyle() const
{
    return this->arrowStyle;
}

QColor QEXTSlider::getBackground() const
{
    return this->background;
}

QColor QEXTSlider::getForeground() const
{
    return this->foreground;
}

int QEXTSlider::getLabTipWidth() const
{
    return this->labTipWidth;
}

int QEXTSlider::getLabTipHeight() const
{
    return this->labTipHeight;
}

QFont QEXTSlider::getLabTipFont() const
{
    return this->labTipFont;
}

bool QEXTSlider::getShowTime() const
{
    return this->showTime;
}

bool QEXTSlider::getClickEnable() const
{
    return this->clickEnable;
}

QString QEXTSlider::getUnit() const
{
    return this->unit;
}

void QEXTSlider::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        labTip->setBorderRadius(borderRadius);
    }
}

void QEXTSlider::setArrowSize(int arrowSize)
{
    if (this->arrowSize != arrowSize) {
        this->arrowSize = arrowSize;
        labTip->setArrowSize(arrowSize);
    }
}

void QEXTSlider::setArrowStyle(const QEXTSlider::ArrowStyle &arrowStyle)
{
    if (this->arrowStyle != arrowStyle) {
        this->arrowStyle = arrowStyle;
        labTip->setArrowPosition((QEXTTooltip::ArrowPosition)arrowStyle);
    }
}

void QEXTSlider::setBackground(const QColor &background)
{
    if (this->background != background) {
        this->background = background;
        labTip->setBackground(background);
    }
}

void QEXTSlider::setForeground(const QColor &foreground)
{
    if (this->foreground != foreground) {
        this->foreground = foreground;
        labTip->setForeground(foreground);
    }
}

void QEXTSlider::setLabTipWidth(int labTipWidth)
{
    if (this->labTipWidth != labTipWidth) {
        this->labTipWidth = labTipWidth;
        labTip->resize(labTipWidth, labTipHeight);
    }
}

void QEXTSlider::setLabTipHeight(int labTipHeight)
{
    if (this->labTipHeight != labTipHeight) {
        this->labTipHeight = labTipHeight;
        labTip->resize(labTipWidth, labTipHeight);
    }
}

void QEXTSlider::setLabTipFont(const QFont &labTipFont)
{
    if (this->labTipFont != labTipFont) {
        this->labTipFont = labTipFont;
        labTip->setFont(labTipFont);
    }
}

void QEXTSlider::setShowTime(bool showTime)
{
    if (this->showTime != showTime) {
        this->showTime = showTime;
    }
}

void QEXTSlider::setClickEnable(bool clickEnable)
{
    if (this->clickEnable != clickEnable) {
        this->clickEnable = clickEnable;
    }
}

void QEXTSlider::setUnit(const QString &unit)
{
    if (this->unit != unit) {
        this->unit = unit;
    }
}

