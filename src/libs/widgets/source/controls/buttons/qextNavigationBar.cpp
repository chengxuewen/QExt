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
    mBackgroundStartColor = QColor(121, 121, 121);
    mBackgroundEndColor = QColor(78, 78, 78);
    mOldBackgroundEndColor = mBackgroundEndColor;

    mBarStartColor = QColor(46, 132, 243);
    mBarEndColor = QColor(39, 110, 203);
    mOldBarEndColor = mBarEndColor;

    mTextNormalColor = QColor(230, 230, 230);
    mTextSelectColor = QColor(255, 255, 255);

    mItems = "";
    mCurrentIndex = -1;
    mCurrentItem = "";

    mBackgroundRadius = 0;
    mBarRadius = 0;
    mSpace = 25;

    mLineWidth = 3;
    mLineColor = QColor(255, 107, 107);

    mBarStyle = QExtNavigationBar::BarStyle_Rect;

    mKeyMoveEnable = false;
    mHorizontal = true;
    mFlat = false;

    mInitLen = 10;
    mStep = 0;

    mIsForward = true;
    mIsVirgin = true;
}

QExtNavigationBarPrivate::~QExtNavigationBarPrivate()
{
    if (mTimer->isActive())
    {
        mTimer->stop();
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
    d->mTimer = new QTimer(this);
    d->mTimer->setInterval(10);
    connect(d->mTimer, SIGNAL(timeout()), this, SLOT(slide()));
}

QExtNavigationBar::~QExtNavigationBar()
{

}

void QExtNavigationBar::resizeEvent(QResizeEvent *)
{
    Q_D(QExtNavigationBar);
    int index = 0;
    int count = d->mListItem.count();
    if (count == 0)
    {
        return;
    }

    if (count > 0 && d->mCurrentItem.isEmpty())
    {
        d->mCurrentIndex = 0;
        d->mCurrentItem = d->mListItem.at(0).first;
    }

    for (int i = 0; i < count; i++)
    {
        if (d->mListItem.at(i).first == d->mCurrentItem)
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
    if (!d->mKeyMoveEnable)
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
    bgGradient.setColorAt(0.0, d->mBackgroundStartColor);
    bgGradient.setColorAt(1.0, d->mBackgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRoundedRect(rect(), d->mBackgroundRadius, d->mBackgroundRadius);
    painter->restore();
}

void QExtNavigationBar::drawBar(QPainter *painter)
{
    Q_D(QExtNavigationBar);
    painter->save();
    QPen pen;

    QLinearGradient barGradient(d->mBarRect.topLeft(), d->mBarRect.bottomLeft());
    barGradient.setColorAt(0.0, d->mBarStartColor);
    barGradient.setColorAt(1.0, d->mBarEndColor);
    painter->setBrush(barGradient);

    if (d->mBarStyle == BarStyle_Rect)
    {
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(d->mBarRect, d->mBarRadius, d->mBarRadius);
        painter->restore();
        return;
    }
    else
    {
        pen.setWidthF(d->mLineWidth);
        pen.setBrush(barGradient);
        painter->setPen(pen);
        painter->drawRoundedRect(d->mBarRect, d->mBarRadius, d->mBarRadius);
    }

    pen.setColor(d->mLineColor);
    painter->setPen(pen);

    double offset = (double)d->mLineWidth / 2;
    if (d->mBarStyle == BarStyle_Line_Top)
    {
        painter->drawLine(d->mBarRect.left(), d->mBarRect.top() + offset, d->mBarRect.right(), d->mBarRect.top() + offset);
    }
    else if (d->mBarStyle == BarStyle_Line_Right)
    {
        painter->drawLine(d->mBarRect.right() - offset, d->mBarRect.top(), d->mBarRect.right() - offset, d->mBarRect.bottom());
    }
    else if (d->mBarStyle == BarStyle_Line_Bottom)
    {
        painter->drawLine(d->mBarRect.left(), d->mBarRect.bottom() - offset, d->mBarRect.right(), d->mBarRect.bottom() - offset);
    }
    else if (d->mBarStyle == BarStyle_Line_Left)
    {
        painter->drawLine(d->mBarRect.left() + offset, d->mBarRect.top(), d->mBarRect.left() + offset, d->mBarRect.bottom());
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

    int count = d->mListItem.count();
    double textLen = 0;
    QString strText;
    d->mInitLen = 0;

    QString longText = "";
    QStringList list = d->mItems.split(";");
    foreach (QString str, list)
    {
        if (str.length() > longText.length())
        {
            longText = str;
        }
    }

    if (d->mHorizontal)
    {
        textLen = painter->fontMetrics().boundingRect(longText).width();
    }
    else
    {
        textLen = painter->fontMetrics().height();
    }

    for (int i = 0; i < count; i++)
    {
        strText = d->mListItem.at(i).first;

        QPointF left(d->mInitLen, 0);
        QPointF right(d->mInitLen + textLen + d->mSpace, height());

        if (!d->mHorizontal)
        {
            left = QPointF(0, d->mInitLen);
            right = QPointF(width(), d->mInitLen + textLen + d->mSpace);
        }

        QRectF textRect(left, right);
        d->mListItem[i].second = textRect;

        if (d->mIsVirgin)
        {
            d->mBarRect = textRect;
            d->mIsVirgin = false;
        }

        if (textRect == d->mListItem.at(d->mCurrentIndex).second)
        {
            painter->setPen(d->mTextSelectColor);
        }
        else
        {
            painter->setPen(d->mTextNormalColor);
        }

        painter->drawText(textRect, Qt::AlignCenter, strText);
        d->mInitLen += textLen + d->mSpace;
    }

    painter->restore();
}

void QExtNavigationBar::slide()
{
    Q_D(QExtNavigationBar);
    if (d->mStep > 1)
    {
        d->mStep--;
    }

    if (d->mHorizontal)
    {
        d->mBarLen = d->mBarRect.topLeft().x();
    }
    else
    {
        d->mBarLen = d->mBarRect.topLeft().y();
    }

    if (d->mIsForward)
    {
        d->mBarLen += d->mStep;
        if (d->mBarLen >= d->mTargetLen)
        {
            d->mBarLen = d->mTargetLen;
            d->mTimer->stop();
        }
    }
    else
    {
        d->mBarLen -= d->mStep;
        if (d->mBarLen <= d->mTargetLen)
        {
            d->mBarLen = d->mTargetLen;
            d->mTimer->stop();
        }
    }

    if (d->mHorizontal)
    {
        d->mBarRect = QRectF(QPointF(d->mBarLen, 0), QPointF(d->mBarLen + d->mBarRect.width(), height()));
    }
    else
    {
        d->mBarRect = QRectF(QPointF(0, d->mBarLen), QPointF(width(), d->mBarLen + d->mBarRect.height()));
    }

    this->update();
}

QColor QExtNavigationBar::backgroundStartColor() const
{
    Q_D(const QExtNavigationBar);
    return d->mBackgroundStartColor;
}

QColor QExtNavigationBar::backgroundEndColor() const
{
    Q_D(const QExtNavigationBar);
    return d->mBackgroundEndColor;
}

QColor QExtNavigationBar::barStartColor() const
{
    Q_D(const QExtNavigationBar);
    return d->mBarStartColor;
}

QColor QExtNavigationBar::barEndColor() const
{
    Q_D(const QExtNavigationBar);
    return d->mBarEndColor;
}

QColor QExtNavigationBar::textNormalColor() const
{
    Q_D(const QExtNavigationBar);
    return d->mTextNormalColor;
}

QColor QExtNavigationBar::textSelectColor() const
{
    Q_D(const QExtNavigationBar);
    return d->mTextSelectColor;
}

QString QExtNavigationBar::items() const
{
    Q_D(const QExtNavigationBar);
    return d->mItems;
}

int QExtNavigationBar::currentIndex() const
{
    Q_D(const QExtNavigationBar);
    return d->mCurrentIndex;
}

QString QExtNavigationBar::currentItem() const
{
    Q_D(const QExtNavigationBar);
    return d->mCurrentItem;
}

int QExtNavigationBar::backgroundRadius() const
{
    Q_D(const QExtNavigationBar);
    return d->mBackgroundRadius;
}

int QExtNavigationBar::barRadius() const
{
    Q_D(const QExtNavigationBar);
    return d->mBarRadius;
}

int QExtNavigationBar::space() const
{
    Q_D(const QExtNavigationBar);
    return d->mSpace;
}

int QExtNavigationBar::lineWidth() const
{
    Q_D(const QExtNavigationBar);
    return d->mLineWidth;
}

QColor QExtNavigationBar::lineColor() const
{
    Q_D(const QExtNavigationBar);
    return d->mLineColor;
}

QExtNavigationBar::BarStyleType QExtNavigationBar::barStyle() const
{
    Q_D(const QExtNavigationBar);
    return d->mBarStyle;
}

bool QExtNavigationBar::keyMoveEnable() const
{
    Q_D(const QExtNavigationBar);
    return d->mKeyMoveEnable;
}

bool QExtNavigationBar::isHorizontal() const
{
    Q_D(const QExtNavigationBar);
    return d->mHorizontal;
}

bool QExtNavigationBar::isFlat() const
{
    Q_D(const QExtNavigationBar);
    return d->mFlat;
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
    d->mListItem.clear();
    this->update();
}

void QExtNavigationBar::setBackgroundStartColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->mBackgroundStartColor != color)
    {
        d->mBackgroundStartColor = color;
        this->update();
    }
}

void QExtNavigationBar::setBackgroundEndColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->mBackgroundEndColor != color)
    {
        d->mBackgroundEndColor = color;
        d->mOldBackgroundEndColor = color;
        this->update();
    }
}

void QExtNavigationBar::setBarStartColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->mBarStartColor != color)
    {
        d->mBarStartColor = color;
        this->update();
    }
}

void QExtNavigationBar::setBarEndColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->mBarEndColor != color)
    {
        d->mBarEndColor = color;
        d->mOldBarEndColor = color;
        this->update();
    }
}

void QExtNavigationBar::setTextNormalColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->mTextNormalColor != color)
    {
        d->mTextNormalColor = color;
        this->update();
    }
}

void QExtNavigationBar::setTextSelectColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->mTextSelectColor != color)
    {
        d->mTextSelectColor = color;
        this->update();
    }
}

void QExtNavigationBar::setItems(const QString &items)
{
    Q_D(QExtNavigationBar);
    d->mItems = items;
    d->mListItem.clear();

    QStringList list = items.split(";");
    foreach (QString str, list)
    {
        d->mListItem.push_back(qMakePair(str, QRectF()));
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
    if (d->mBackgroundRadius != radius)
    {
        d->mBackgroundRadius = radius;
        this->update();
    }
}

void QExtNavigationBar::setBarRadius(int radius)
{
    Q_D(QExtNavigationBar);
    if (d->mBarRadius != radius)
    {
        d->mBarRadius = radius;
        this->update();
    }
}

void QExtNavigationBar::setSpace(int space)
{
    Q_D(QExtNavigationBar);
    if (d->mSpace != space)
    {
        d->mSpace = space;
        this->update();
    }
}

void QExtNavigationBar::setLineWidth(int width)
{
    Q_D(QExtNavigationBar);
    if (d->mLineWidth != width)
    {
        d->mLineWidth = width;
        this->update();
    }
}

void QExtNavigationBar::setLineColor(const QColor &color)
{
    Q_D(QExtNavigationBar);
    if (d->mLineColor != color)
    {
        d->mLineColor = color;
        this->update();
    }
}

void QExtNavigationBar::setBarStyle(const QExtNavigationBar::BarStyleType &style)
{
    Q_D(QExtNavigationBar);
    if (d->mBarStyle != style)
    {
        d->mBarStyle = style;
        this->update();
    }
}

void QExtNavigationBar::setKeyMoveEnable(bool enable)
{
    Q_D(QExtNavigationBar);
    if (d->mKeyMoveEnable != enable)
    {
        d->mKeyMoveEnable = enable;
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
    if (d->mHorizontal != horizontal)
    {
        d->mHorizontal = horizontal;
        this->update();
    }
}

void QExtNavigationBar::setFlat(bool flat)
{
    Q_D(QExtNavigationBar);
    if (d->mFlat != flat)
    {
        if (flat)
        {
            d->mBackgroundEndColor = d->mBackgroundStartColor;
            d->mBarEndColor = d->mBarStartColor;
        }
        else
        {
            d->mBackgroundEndColor = d->mOldBackgroundEndColor;
            d->mBarEndColor = d->mOldBarEndColor;
        }

        d->mFlat = flat;
        this->update();
    }
}

void QExtNavigationBar::moveFirst()
{
    Q_D(QExtNavigationBar);
    int index = 0;
    if (d->mCurrentIndex != index)
    {
        this->moveTo(index);
    }
}

void QExtNavigationBar::moveLast()
{
    Q_D(QExtNavigationBar);
    int index = d->mListItem.count() - 1;
    if (d->mCurrentIndex != index)
    {
        this->moveTo(index);
    }
}

void QExtNavigationBar::movePrevious()
{
    Q_D(QExtNavigationBar);
    if (d->mCurrentIndex > 0)
    {
        d->mCurrentIndex--;
        moveTo(d->mCurrentIndex);
    }
}

void QExtNavigationBar::moveNext()
{
    Q_D(QExtNavigationBar);
    if (d->mCurrentIndex < d->mListItem.count() - 1)
    {
        d->mCurrentIndex++;
        this->moveTo(d->mCurrentIndex);
    }
}

void QExtNavigationBar::moveTo(int index)
{
    Q_D(QExtNavigationBar);
    if (index >= 0 && d->mListItem.count() > index)
    {
        QRectF rec = d->mListItem.at(index).second;
        QPoint pos = QPoint(rec.x(), rec.y());
        this->moveTo(pos);
    }
}

void QExtNavigationBar::moveTo(const QString &item)
{
    Q_D(QExtNavigationBar);
    int count = d->mListItem.count();
    for (int i = 0; i < count; i++)
    {
        if (d->mListItem.at(i).first == item)
        {
            this->moveTo(i);
            break;
        }
    }
}

void QExtNavigationBar::moveTo(const QPointF &point)
{
    Q_D(QExtNavigationBar);
    int count = d->mListItem.count();
    for (int i = 0; i < count; i++)
    {
        if (d->mListItem.at(i).second.contains(point))
        {
            d->mCurrentIndex = i;
            d->mCurrentItem = d->mListItem.at(i).first;
            d->mTargetRect = d->mListItem.at(i).second;

            if (d->mHorizontal)
            {
                d->mTargetLen = d->mTargetRect.topLeft().x();
                d->mBarLen = d->mBarRect.topLeft().x();
            }
            else
            {
                d->mTargetLen = d->mTargetRect.topLeft().y();
                d->mBarLen = d->mBarRect.topLeft().y();
            }

            d->mIsForward = (d->mTargetLen > d->mBarLen);
            int distance = d->mTargetLen - d->mBarLen;
            distance = qAbs(distance);

            d->mStep = d->initStep(distance);
            d->mTimer->start();
            emit this->currentItemChanged(d->mCurrentIndex, d->mCurrentItem);
        }
    }
}
