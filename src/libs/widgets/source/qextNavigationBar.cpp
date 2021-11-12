#pragma execution_character_set("utf-8")

#include <qextNavigationBar.h>
#include <qextNavigationBar_p.h>

#include <QEvent>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>


QEXTNavigationBarPrivate::QEXTNavigationBarPrivate(QEXTNavigationBar *q)
    : q_ptr(q)
{
    m_backgroundStartColor = QColor(121, 121, 121);
    m_backgroundEndColor = QColor(78, 78, 78);
    m_oldBackgroundEndColor = m_backgroundEndColor;

    m_barStartColor = QColor(46, 132, 243);
    m_barEndColor = QColor(39, 110, 203);
    m_oldBarEndColor = m_barEndColor;

    m_textNormalColor = QColor(230, 230, 230);
    m_textSelectColor = QColor(255, 255, 255);

    m_items = "";
    m_currentIndex = -1;
    m_currentItem = "";

    m_backgroundRadius = 0;
    m_barRadius = 0;
    m_space = 25;

    m_lineWidth = 3;
    m_lineColor = QColor(255, 107, 107);

    m_barStyle = QEXTNavigationBar::BarStyle_Rect;

    m_keyMoveEnable = false;
    m_horizontal = true;
    m_flat = false;

    m_initLen = 10;
    m_step = 0;

    m_isForward = true;
    m_isVirgin = true;
}

QEXTNavigationBarPrivate::~QEXTNavigationBarPrivate()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
}

int QEXTNavigationBarPrivate::initStep(int distance)
{
    int n = 1;

    while (1)
    {
        if (n * n > distance)
        {
            break;
        }
        else
        {
            n++;
        }
    }

    return n * 1.4;
}



QEXTNavigationBar::QEXTNavigationBar(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTNavigationBarPrivate(this))
{
    QEXT_DECL_D(QEXTNavigationBar);
    d->m_timer = new QTimer(this);
    d->m_timer->setInterval(10);
    connect(d->m_timer, SIGNAL(timeout()), this, SLOT(slide()));
}

QEXTNavigationBar::~QEXTNavigationBar()
{

}

void QEXTNavigationBar::resizeEvent(QResizeEvent *)
{
    QEXT_DECL_D(QEXTNavigationBar);
    int index = 0;
    int count = d->m_listItem.count();
    if (count == 0)
    {
        return;
    }

    if (count > 0 && d->m_currentItem.isEmpty())
    {
        d->m_currentIndex = 0;
        d->m_currentItem = d->m_listItem.at(0).first;
    }

    for (int i = 0; i < count; i++)
    {
        if (d->m_listItem.at(i).first == d->m_currentItem)
        {
            index = i;
            break;
        }
    }

    this->moveTo(index);
}

void QEXTNavigationBar::mousePressEvent(QMouseEvent *e)
{
    this->moveTo(e->pos());
}

void QEXTNavigationBar::keyPressEvent(QKeyEvent *keyEvent)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (!d->m_keyMoveEnable)
    {
        return;
    }

    if (keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Up)
    {
        this->movePrevious();
    }
    else if (keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_Down)
    {
        this->moveNext();
    }
}

void QEXTNavigationBar::paintEvent(QPaintEvent *)
{
    QEXT_DECL_D(QEXTNavigationBar);
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景色
    this->drawBackground(&painter);
    //绘制当前条目选中背景
    this->drawBar(&painter);
    //绘制条目文字
    this->drawText(&painter);
}

void QEXTNavigationBar::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTNavigationBar);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0, 0), QPoint(0, height()));
    bgGradient.setColorAt(0.0, d->m_backgroundStartColor);
    bgGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRoundedRect(rect(), d->m_backgroundRadius, d->m_backgroundRadius);
    painter->restore();
}

void QEXTNavigationBar::drawBar(QPainter *painter)
{
    QEXT_DECL_D(QEXTNavigationBar);
    painter->save();
    QPen pen;

    QLinearGradient barGradient(d->m_barRect.topLeft(), d->m_barRect.bottomLeft());
    barGradient.setColorAt(0.0, d->m_barStartColor);
    barGradient.setColorAt(1.0, d->m_barEndColor);
    painter->setBrush(barGradient);

    if (d->m_barStyle == BarStyle_Rect)
    {
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(d->m_barRect, d->m_barRadius, d->m_barRadius);
        painter->restore();
        return;
    }
    else
    {
        pen.setWidthF(d->m_lineWidth);
        pen.setBrush(barGradient);
        painter->setPen(pen);
        painter->drawRoundedRect(d->m_barRect, d->m_barRadius, d->m_barRadius);
    }

    pen.setColor(d->m_lineColor);
    painter->setPen(pen);

    double offset = (double)d->m_lineWidth / 2;
    if (d->m_barStyle == BarStyle_Line_Top)
    {
        painter->drawLine(d->m_barRect.left(), d->m_barRect.top() + offset, d->m_barRect.right(), d->m_barRect.top() + offset);
    }
    else if (d->m_barStyle == BarStyle_Line_Right)
    {
        painter->drawLine(d->m_barRect.right() - offset, d->m_barRect.top(), d->m_barRect.right() - offset, d->m_barRect.bottom());
    }
    else if (d->m_barStyle == BarStyle_Line_Bottom)
    {
        painter->drawLine(d->m_barRect.left(), d->m_barRect.bottom() - offset, d->m_barRect.right(), d->m_barRect.bottom() - offset);
    }
    else if (d->m_barStyle == BarStyle_Line_Left)
    {
        painter->drawLine(d->m_barRect.left() + offset, d->m_barRect.top(), d->m_barRect.left() + offset, d->m_barRect.bottom());
    }

    //这里还可以增加右边倒三角形

    painter->restore();
}

void QEXTNavigationBar::drawText(QPainter *painter)
{
    QEXT_DECL_D(QEXTNavigationBar);
    painter->save();

    QFont textFont;
    textFont.setBold(true);
    painter->setFont(textFont);

    int count = d->m_listItem.count();
    double textLen = 0;
    QString strText;
    d->m_initLen = 0;

    //横向导航时,字符区域取条目元素中最长的字符宽度
    QString longText = "";
    QStringList list = d->m_items.split(";");
    foreach (QString str, list)
    {
        if (str.length() > longText.length())
        {
            longText = str;
        }
    }

    if (d->m_horizontal)
    {
        textLen  = painter->fontMetrics().width(longText);
    }
    else
    {
        textLen  = painter->fontMetrics().height();
    }

    //逐个绘制元素队列中的文字及文字背景
    for (int i = 0; i < count; i++)
    {
        strText = d->m_listItem.at(i).first;

        QPointF left(d->m_initLen, 0);
        QPointF right(d->m_initLen + textLen + d->m_space, height());

        if (!d->m_horizontal)
        {
            left = QPointF(0, d->m_initLen);
            right = QPointF(width(), d->m_initLen + textLen + d->m_space);
        }

        QRectF textRect(left, right);
        d->m_listItem[i].second = textRect;

        if (d->m_isVirgin)
        {
            d->m_barRect = textRect;
            d->m_isVirgin = false;
        }

        //当前选中区域的文字显示选中文字颜色
        if (textRect == d->m_listItem.at(d->m_currentIndex).second)
        {
            painter->setPen(d->m_textSelectColor);
        }
        else
        {
            painter->setPen(d->m_textNormalColor);
        }

        painter->drawText(textRect, Qt::AlignCenter, strText);
        d->m_initLen += textLen + d->m_space;
    }

    painter->restore();
}

void QEXTNavigationBar::slide()
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_step > 1)
    {
        d->m_step--;
    }

    if (d->m_horizontal)
    {
        d->m_barLen = d->m_barRect.topLeft().x();
    }
    else
    {
        d->m_barLen = d->m_barRect.topLeft().y();
    }

    if (d->m_isForward)
    {
        d->m_barLen += d->m_step;
        if (d->m_barLen >= d->m_targetLen)
        {
            d->m_barLen = d->m_targetLen;
            d->m_timer->stop();
        }
    }
    else
    {
        d->m_barLen -= d->m_step;
        if (d->m_barLen <= d->m_targetLen)
        {
            d->m_barLen = d->m_targetLen;
            d->m_timer->stop();
        }
    }

    if (d->m_horizontal)
    {
        d->m_barRect = QRectF(QPointF(d->m_barLen, 0), QPointF(d->m_barLen + d->m_barRect.width(), height()));
    }
    else
    {
        d->m_barRect = QRectF(QPointF(0, d->m_barLen), QPointF(width(), d->m_barLen + d->m_barRect.height()));
    }

    this->update();
}

QColor QEXTNavigationBar::backgroundStartColor() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_backgroundStartColor;
}

QColor QEXTNavigationBar::backgroundEndColor() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_backgroundEndColor;
}

QColor QEXTNavigationBar::barStartColor() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_barStartColor;
}

QColor QEXTNavigationBar::barEndColor() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_barEndColor;
}

QColor QEXTNavigationBar::textNormalColor() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_textNormalColor;
}

QColor QEXTNavigationBar::textSelectColor() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_textSelectColor;
}

QString QEXTNavigationBar::items() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_items;
}

int QEXTNavigationBar::currentIndex() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_currentIndex;
}

QString QEXTNavigationBar::currentItem() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_currentItem;
}

int QEXTNavigationBar::backgroundRadius() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_backgroundRadius;
}

int QEXTNavigationBar::barRadius() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_barRadius;
}

int QEXTNavigationBar::space() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_space;
}

int QEXTNavigationBar::lineWidth() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_lineWidth;
}

QColor QEXTNavigationBar::lineColor() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_lineColor;
}

QEXTNavigationBar::BarStyleType QEXTNavigationBar::barStyle() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_barStyle;
}

bool QEXTNavigationBar::keyMoveEnable() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_keyMoveEnable;
}

bool QEXTNavigationBar::isHorizontal() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_horizontal;
}

bool QEXTNavigationBar::isFlat() const
{
    QEXT_DECL_DC(QEXTNavigationBar);
    return d->m_flat;
}

QSize QEXTNavigationBar::sizeHint() const
{
    return QSize(500, 30);
}

QSize QEXTNavigationBar::minimumSizeHint() const
{
    return QSize(30, 30);
}

void QEXTNavigationBar::clearItem()
{
    QEXT_DECL_D(QEXTNavigationBar);
    d->m_listItem.clear();
    this->update();
}

void QEXTNavigationBar::setBackgroundStartColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_backgroundStartColor != color)
    {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QEXTNavigationBar::setBackgroundEndColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_backgroundEndColor != color)
    {
        d->m_backgroundEndColor = color;
        d->m_oldBackgroundEndColor = color;
        this->update();
    }
}

void QEXTNavigationBar::setBarStartColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_barStartColor != color)
    {
        d->m_barStartColor = color;
        this->update();
    }
}

void QEXTNavigationBar::setBarEndColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_barEndColor != color)
    {
        d->m_barEndColor = color;
        d->m_oldBarEndColor = color;
        this->update();
    }
}

void QEXTNavigationBar::setTextNormalColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_textNormalColor != color)
    {
        d->m_textNormalColor = color;
        this->update();
    }
}

void QEXTNavigationBar::setTextSelectColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_textSelectColor != color)
    {
        d->m_textSelectColor = color;
        this->update();
    }
}

void QEXTNavigationBar::setItems(const QString &items)
{
    QEXT_DECL_D(QEXTNavigationBar);
    d->m_items = items;
    d->m_listItem.clear();

    QStringList list = items.split(";");
    foreach (QString str, list)
    {
        d->m_listItem.push_back(qMakePair(str, QRectF()));
    }

    this->update();
}

void QEXTNavigationBar::setCurrentIndex(int index)
{
    this->moveTo(index);
}

void QEXTNavigationBar::setCurrentItem(const QString &item)
{
    this->moveTo(item);
}

void QEXTNavigationBar::setBackgroundRadius(int radius)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_backgroundRadius != radius)
    {
        d->m_backgroundRadius = radius;
        this->update();
    }
}

void QEXTNavigationBar::setBarRadius(int radius)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_barRadius != radius)
    {
        d->m_barRadius = radius;
        this->update();
    }
}

void QEXTNavigationBar::setSpace(int space)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_space != space)
    {
        d->m_space = space;
        this->update();
    }
}

void QEXTNavigationBar::setLineWidth(int width)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_lineWidth != width)
    {
        d->m_lineWidth = width;
        this->update();
    }
}

void QEXTNavigationBar::setLineColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_lineColor != color)
    {
        d->m_lineColor = color;
        this->update();
    }
}

void QEXTNavigationBar::setBarStyle(const QEXTNavigationBar::BarStyleType &style)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_barStyle != style)
    {
        d->m_barStyle = style;
        this->update();
    }
}

void QEXTNavigationBar::setKeyMoveEnable(bool enable)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_keyMoveEnable != enable)
    {
        d->m_keyMoveEnable = enable;
        if (enable)
        {
            this->setFocusPolicy(Qt::StrongFocus);
        }
        else
        {
            this->setFocusPolicy(Qt::NoFocus);
        }
    }
}

void QEXTNavigationBar::setHorizontal(bool horizontal)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_horizontal != horizontal)
    {
        d->m_horizontal = horizontal;
        this->update();
    }
}

void QEXTNavigationBar::setFlat(bool flat)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_flat != flat)
    {
        //扁平后将初始颜色赋值给结束颜色达到扁平的效果,如果取消扁平则再次恢复原有的颜色
        if (flat)
        {
            d->m_backgroundEndColor = d->m_backgroundStartColor;
            d->m_barEndColor = d->m_barStartColor;
        }
        else
        {
            d->m_backgroundEndColor = d->m_oldBackgroundEndColor;
            d->m_barEndColor = d->m_oldBarEndColor;
        }

        d->m_flat = flat;
        this->update();
    }
}

void QEXTNavigationBar::moveFirst()
{
    QEXT_DECL_D(QEXTNavigationBar);
    int index = 0;
    if (d->m_currentIndex != index)
    {
        this->moveTo(index);
    }
}

void QEXTNavigationBar::moveLast()
{
    QEXT_DECL_D(QEXTNavigationBar);
    int index = d->m_listItem.count() - 1;
    if (d->m_currentIndex != index)
    {
        this->moveTo(index);
    }
}

void QEXTNavigationBar::movePrevious()
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_currentIndex > 0)
    {
        d->m_currentIndex--;
        moveTo(d->m_currentIndex);
    }
}

void QEXTNavigationBar::moveNext()
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (d->m_currentIndex < d->m_listItem.count() - 1)
    {
        d->m_currentIndex++;
        this->moveTo(d->m_currentIndex);
    }
}

void QEXTNavigationBar::moveTo(int index)
{
    QEXT_DECL_D(QEXTNavigationBar);
    if (index >= 0 && d->m_listItem.count() > index)
    {
        QRectF rec = d->m_listItem.at(index).second;
        QPoint pos = QPoint(rec.x(), rec.y());
        this->moveTo(pos);
    }
}

void QEXTNavigationBar::moveTo(const QString &item)
{
    QEXT_DECL_D(QEXTNavigationBar);
    int count = d->m_listItem.count();
    for (int i = 0; i < count; i++)
    {
        if (d->m_listItem.at(i).first == item)
        {
            this->moveTo(i);
            break;
        }
    }
}

void QEXTNavigationBar::moveTo(const QPointF &point)
{
    QEXT_DECL_D(QEXTNavigationBar);
    int count = d->m_listItem.count();
    for (int i = 0; i < count; i++)
    {
        if (d->m_listItem.at(i).second.contains(point))
        {
            d->m_currentIndex = i;
            d->m_currentItem = d->m_listItem.at(i).first;
            d->m_targetRect = d->m_listItem.at(i).second;

            if (d->m_horizontal)
            {
                d->m_targetLen = d->m_targetRect.topLeft().x();
                d->m_barLen = d->m_barRect.topLeft().x();
            }
            else
            {
                d->m_targetLen = d->m_targetRect.topLeft().y();
                d->m_barLen = d->m_barRect.topLeft().y();
            }

            d->m_isForward = (d->m_targetLen > d->m_barLen);
            int distance = d->m_targetLen - d->m_barLen;
            distance = qAbs(distance);

            //重新获取每次移动的步长
            d->m_step = d->initStep(distance);
            d->m_timer->start();
            emit this->currentItemChanged(d->m_currentIndex, d->m_currentItem);
        }
    }
}
