/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
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

#include <private/qextNavigationBar_p.h>

#include <QEvent>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

QExtNavigationBarPrivate::QExtNavigationBarPrivate(QExtNavigationBar *q)
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

    m_barStyle = QExtNavigationBar::BarStyle_Rect;

    m_keyMoveEnable = false;
    m_horizontal = true;
    m_flat = false;

    m_initLen = 10;
    m_step = 0;

    m_isForward = true;
    m_isVirgin = true;
}

QExtNavigationBarPrivate::~QExtNavigationBarPrivate()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
}

int QExtNavigationBarPrivate::initStep(int distance)
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



QExtNavigationBar::QExtNavigationBar(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtNavigationBarPrivate(this))
{
    Q_D(QExtNavigationBar);
    d->m_timer = new QTimer(this);
    d->m_timer->setInterval(10);
    connect(d->m_timer, SIGNAL(timeout()), this, SLOT(slide()));
}

QExtNavigationBar::~QExtNavigationBar()
{

}

void QExtNavigationBar::resizeEvent(QResizeEvent *)
{
    Q_D(QExtNavigationBar);
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

void QExtNavigationBar::mousePressEvent(QMouseEvent *e)
{
    this->moveTo(e->pos());
}

void QExtNavigationBar::keyPressEvent(QKeyEvent *keyEvent)
{
    Q_D(QExtNavigationBar);
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

void QExtNavigationBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);
    this->drawBar(&painter);
    this->drawText(&painter);
}

void QExtNavigationBar::drawBackground(QPainter *painter)
{
    Q_D(QExtNavigationBar);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0, 0), QPoint(0, height()));
    bgGradient.setColorAt(0.0, d->m_backgroundStartColor);
    bgGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRoundedRect(rect(), d->m_backgroundRadius, d->m_backgroundRadius);
    painter->restore();
}

void QExtNavigationBar::drawBar(QPainter *painter)
{
    Q_D(QExtNavigationBar);
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

    painter->restore();
}

void QExtNavigationBar::drawText(QPainter *painter)
{
    Q_D(QExtNavigationBar);
    painter->save();

    QFont textFont;
    textFont.setBold(true);
    painter->setFont(textFont);

    int count = d->m_listItem.count();
    double textLen = 0;
    QString strText;
    d->m_initLen = 0;

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

void QExtNavigationBar::slide()
{
    Q_D(QExtNavigationBar);
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

QColor QExtNavigationBar::backgroundStartColor() const
{
    Q_D(const QExtNavigationBar);
    return d->m_backgroundStartColor;
}

QColor QExtNavigationBar::backgroundEndColor() const
{
    Q_D(const QExtNavigationBar);
    return d->m_backgroundEndColor;
}

QColor QExtNavigationBar::barStartColor() const
{
    Q_D(const QExtNavigationBar);
    return d->m_barStartColor;
}

QColor QExtNavigationBar::barEndColor() const
{
    Q_D(const QExtNavigationBar);
    return d->m_barEndColor;
}

QColor QExtNavigationBar::textNormalColor() const
{
    Q_D(const QExtNavigationBar);
    return d->m_textNormalColor;
}

QColor QExtNavigationBar::textSelectColor() const
{
    Q_D(const QExtNavigationBar);
    return d->m_textSelectColor;
}

QString QExtNavigationBar::items() const
{
    Q_D(const QExtNavigationBar);
    return d->m_items;
}

int QExtNavigationBar::currentIndex() const
{
    Q_D(const QExtNavigationBar);
    return d->m_currentIndex;
}

QString QExtNavigationBar::currentItem() const
{
    Q_D(const QExtNavigationBar);
    return d->m_currentItem;
}

int QExtNavigationBar::backgroundRadius() const
{
    Q_D(const QExtNavigationBar);
    return d->m_backgroundRadius;
}

int QExtNavigationBar::barRadius() const
{
    Q_D(const QExtNavigationBar);
    return d->m_barRadius;
}

int QExtNavigationBar::space() const
{
    Q_D(const QExtNavigationBar);
    return d->m_space;
}

int QExtNavigationBar::lineWidth() const
{
    Q_D(const QExtNavigationBar);
    return d->m_lineWidth;
}

QColor QExtNavigationBar::lineColor() const
{
    Q_D(const QExtNavigationBar);
    return d->m_lineColor;
}

QExtNavigationBar::BarStyleType QExtNavigationBar::barStyle() const
{
    Q_D(const QExtNavigationBar);
    return d->m_barStyle;
}

bool QExtNavigationBar::keyMoveEnable() const
{
    Q_D(const QExtNavigationBar);
    return d->m_keyMoveEnable;
}

bool QExtNavigationBar::isHorizontal() const
{
    Q_D(const QExtNavigationBar);
    return d->m_horizontal;
}

bool QExtNavigationBar::isFlat() const
{
    Q_D(const QExtNavigationBar);
    return d->m_flat;
}

QSize QExtNavigationBar::sizeHint() const
{
    return QSize(500, 30);
}

QSize QExtNavigationBar::minimumSizeHint() const
{
    return QSize(30, 30);
}

void QExtNavigationBar::clearItem()
{
    Q_D(QExtNavigationBar);
    d->m_listItem.clear();
    this->update();
}

void QExtNavigationBar::setBackgroundStartColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->m_backgroundStartColor != color)
    {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QExtNavigationBar::setBackgroundEndColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->m_backgroundEndColor != color)
    {
        d->m_backgroundEndColor = color;
        d->m_oldBackgroundEndColor = color;
        this->update();
    }
}

void QExtNavigationBar::setBarStartColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->m_barStartColor != color)
    {
        d->m_barStartColor = color;
        this->update();
    }
}

void QExtNavigationBar::setBarEndColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->m_barEndColor != color)
    {
        d->m_barEndColor = color;
        d->m_oldBarEndColor = color;
        this->update();
    }
}

void QExtNavigationBar::setTextNormalColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->m_textNormalColor != color)
    {
        d->m_textNormalColor = color;
        this->update();
    }
}

void QExtNavigationBar::setTextSelectColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->m_textSelectColor != color)
    {
        d->m_textSelectColor = color;
        this->update();
    }
}

void QExtNavigationBar::setItems(const QString &items)
{
    Q_D(QExtNavigationBar);
    d->m_items = items;
    d->m_listItem.clear();

    QStringList list = items.split(";");
    foreach (QString str, list)
    {
        d->m_listItem.push_back(qMakePair(str, QRectF()));
    }

    this->update();
}

void QExtNavigationBar::setCurrentIndex(int index)
{
    this->moveTo(index);
}

void QExtNavigationBar::setCurrentItem(const QString &item)
{
    this->moveTo(item);
}

void QExtNavigationBar::setBackgroundRadius(int radius)
{
    Q_D(QExtNavigationBar);
    if (d->m_backgroundRadius != radius)
    {
        d->m_backgroundRadius = radius;
        this->update();
    }
}

void QExtNavigationBar::setBarRadius(int radius)
{
    Q_D(QExtNavigationBar);
    if (d->m_barRadius != radius)
    {
        d->m_barRadius = radius;
        this->update();
    }
}

void QExtNavigationBar::setSpace(int space)
{
    Q_D(QExtNavigationBar);
    if (d->m_space != space)
    {
        d->m_space = space;
        this->update();
    }
}

void QExtNavigationBar::setLineWidth(int width)
{
    Q_D(QExtNavigationBar);
    if (d->m_lineWidth != width)
    {
        d->m_lineWidth = width;
        this->update();
    }
}

void QExtNavigationBar::setLineColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->m_lineColor != color)
    {
        d->m_lineColor = color;
        this->update();
    }
}

void QExtNavigationBar::setBarStyle(const QExtNavigationBar::BarStyleType &style)
{
    Q_D(QExtNavigationBar);
    if (d->m_barStyle != style)
    {
        d->m_barStyle = style;
        this->update();
    }
}

void QExtNavigationBar::setKeyMoveEnable(bool enable)
{
    Q_D(QExtNavigationBar);
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

void QExtNavigationBar::setHorizontal(bool horizontal)
{
    Q_D(QExtNavigationBar);
    if (d->m_horizontal != horizontal)
    {
        d->m_horizontal = horizontal;
        this->update();
    }
}

void QExtNavigationBar::setFlat(bool flat)
{
    Q_D(QExtNavigationBar);
    if (d->m_flat != flat)
    {
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

void QExtNavigationBar::moveFirst()
{
    Q_D(QExtNavigationBar);
    int index = 0;
    if (d->m_currentIndex != index)
    {
        this->moveTo(index);
    }
}

void QExtNavigationBar::moveLast()
{
    Q_D(QExtNavigationBar);
    int index = d->m_listItem.count() - 1;
    if (d->m_currentIndex != index)
    {
        this->moveTo(index);
    }
}

void QExtNavigationBar::movePrevious()
{
    Q_D(QExtNavigationBar);
    if (d->m_currentIndex > 0)
    {
        d->m_currentIndex--;
        moveTo(d->m_currentIndex);
    }
}

void QExtNavigationBar::moveNext()
{
    Q_D(QExtNavigationBar);
    if (d->m_currentIndex < d->m_listItem.count() - 1)
    {
        d->m_currentIndex++;
        this->moveTo(d->m_currentIndex);
    }
}

void QExtNavigationBar::moveTo(int index)
{
    Q_D(QExtNavigationBar);
    if (index >= 0 && d->m_listItem.count() > index)
    {
        QRectF rec = d->m_listItem.at(index).second;
        QPoint pos = QPoint(rec.x(), rec.y());
        this->moveTo(pos);
    }
}

void QExtNavigationBar::moveTo(const QString &item)
{
    Q_D(QExtNavigationBar);
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

void QExtNavigationBar::moveTo(const QPointF &point)
{
    Q_D(QExtNavigationBar);
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

            d->m_step = d->initStep(distance);
            d->m_timer->start();
            emit this->currentItemChanged(d->m_currentIndex, d->m_currentItem);
        }
    }
}
