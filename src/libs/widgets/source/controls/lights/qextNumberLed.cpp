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

#include <private/qextNumberLed_p.h>

#include <QDebug>
#include <QColor>
#include <QPainter>

QExtNumberLedPrivate::QExtNumberLedPrivate(QExtNumberLed *q)
    : q_ptr(q)
{
    m_number = 0;
    m_space = 20;

    m_backgroundStartColor = QColor(100, 100, 100);
    m_backgroundEndColor = QColor(60, 60, 60);

    m_numberStartColor = QColor(100, 184, 255);
    m_numberEndColor = QColor(79, 148, 205);

    m_symbol = QExtNumberLed::Symbol_None;

    m_dotVisible = false;
    m_colonVisible = false;
}

QExtNumberLedPrivate::~QExtNumberLedPrivate()
{

}


QExtNumberLed::QExtNumberLed(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtNumberLedPrivate(this))
{

}

QExtNumberLed::~QExtNumberLed()
{

}

int QExtNumberLed::number() const
{
    Q_D(const QExtNumberLed);
    return d->m_number;
}

int QExtNumberLed::space() const
{
    Q_D(const QExtNumberLed);
    return d->m_space;
}

QColor QExtNumberLed::backgroundStartColor() const
{
    Q_D(const QExtNumberLed);
    return d->m_backgroundStartColor;
}

QColor QExtNumberLed::backgroundEndColor() const
{
    Q_D(const QExtNumberLed);
    return d->m_backgroundEndColor;
}

QColor QExtNumberLed::numberStartColor() const
{
    Q_D(const QExtNumberLed);
    return d->m_numberStartColor;
}

QColor QExtNumberLed::numberEndColor() const
{
    Q_D(const QExtNumberLed);
    return d->m_numberEndColor;
}

QExtNumberLed::Symbol QExtNumberLed::symbolType() const
{
    Q_D(const QExtNumberLed);
    return d->m_symbol;
}

QSize QExtNumberLed::sizeHint() const
{
    return QSize(150, 200);
}

QSize QExtNumberLed::minimumSizeHint() const
{
    return QSize(20, 30);
}

void QExtNumberLed::setNumber(int number)
{
    Q_D(QExtNumberLed);
    if (number < 0 || number > 9)
    {
        qCritical() << "QExtNumberLed::setNumber():iNumber must be in range of 0~9!";
        return;
    }
    if (number != d->m_number) {
        d->m_number = number;
        this->update();
    }
}

void QExtNumberLed::setSpace(int space)
{
    Q_D(QExtNumberLed);
    if (space < 0) {
        qCritical() << "QExtNumberLed::setNumber():iNumber must br greate than zero!";
        return;
    }
    if (space != d->m_space) {
        d->m_space = space;
        this->update();
    }
}

void QExtNumberLed::setBackgroundStartColor(const QColor &color)
{
    Q_D(QExtNumberLed);
    if (color != d->m_backgroundStartColor) {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QExtNumberLed::setBackgroundEndColor(const QColor &color)
{
    Q_D(QExtNumberLed);
    if (color != d->m_backgroundEndColor) {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QExtNumberLed::setNumberStartColor(const QColor &color)
{
    Q_D(QExtNumberLed);
    if (color != d->m_numberStartColor) {
        d->m_numberStartColor = color;
        this->update();
    }
}

void QExtNumberLed::setNumberEndColor(const QColor &color)
{
    Q_D(QExtNumberLed);
    if (color != d->m_numberEndColor) {
        d->m_numberEndColor = color;
        this->update();
    }
}

void QExtNumberLed::setSymbolType(const QExtNumberLed::Symbol &type)
{
    Q_D(QExtNumberLed);
    if (type != d->m_symbol) {
        d->m_symbol = type;
        this->update();
    }
}

void QExtNumberLed::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);
    this->drawNumber(&painter);
}

void QExtNumberLed::drawBackground(QPainter *painter)
{
    Q_D(QExtNumberLed);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, this->height()));
    bgGradient.setColorAt(0.0, d->m_backgroundStartColor);
    bgGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRect(this->rect());
    painter->restore();
}

void QExtNumberLed::drawNumber(QPainter *painter)
{
    Q_D(QExtNumberLed);
    painter->save();
    painter->setPen(Qt::NoPen);

    double recWidth = this->width() / 10;
    double recHeight = this->height() / 30;
    double recRadius = qMin(recWidth, recHeight) * 2;
    double recSpace = this->width() / 30;
    double margin = qMax(recWidth, recHeight);

    QPointF topLeft(margin, margin);
    QPointF topRight(this->width() - margin * 2 - recRadius, margin);
    QPointF midLeft(margin, this->height() / 2);
    QPointF midRight(this->width() - margin * 2 - recRadius, this->height() / 2);
    QPointF bottomLeft(margin, this->height() - margin);
    QPointF bottomRight(this->width() - margin * 2 - recRadius, this->height() - margin);

    QVector<QPointF> topLeftRectVec;
    topLeftRectVec.append(QPointF(topLeft.x(), topLeft.y()));
    topLeftRectVec.append(QPointF(topLeft.x() + recWidth, topLeft.y() + recHeight * 2));
    topLeftRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() - recHeight - recSpace));
    topLeftRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y() - recSpace));
    topLeftRectVec.append(QPointF(midLeft.x(), midLeft.y() - recHeight - recSpace));

    QVector<QPointF> topRectVec;
    topRectVec.append(QPointF(topLeft.x() + recSpace, topLeft.y()));
    topRectVec.append(QPointF(topLeft.x() + recWidth + recSpace, topLeft.y() + recHeight * 2));
    topRectVec.append(QPointF(topRight.x() - recWidth - recSpace, topRight.y() + recHeight * 2));
    topRectVec.append(QPointF(topRight.x() - recSpace, topRight.y()));

    QVector<QPointF> topRightRectVec;
    topRightRectVec.append(QPointF(topRight.x() - recWidth, topRight.y() + recHeight * 2));
    topRightRectVec.append(QPointF(topRight.x(), topRight.y()));
    topRightRectVec.append(QPointF(midRight.x(), midRight.y() - recHeight - recSpace));
    topRightRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y() - recSpace));
    topRightRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() - recHeight - recSpace));

    QVector<QPointF> midRectVec;
    midRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y()));
    midRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() - recHeight));
    midRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() - recHeight));
    midRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y()));
    midRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() + recHeight));
    midRectVec.append(QPointF(midLeft.x() + recWidth, midRight.y() + recHeight));

    QVector<QPointF> bottomLeftRectVec;
    bottomLeftRectVec.append(QPointF(midLeft.x(), midLeft.y() + recHeight + recSpace));
    bottomLeftRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y() + recSpace));
    bottomLeftRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() + recHeight + recSpace));
    bottomLeftRectVec.append(QPointF(bottomLeft.x() + recWidth, bottomLeft.y() - recHeight * 2));
    bottomLeftRectVec.append(QPointF(bottomLeft.x(), bottomLeft.y()));

    QVector<QPointF> bottomRectVec;
    bottomRectVec.append(QPointF(bottomLeft.x() + recSpace, bottomLeft.y()));
    bottomRectVec.append(QPointF(bottomLeft.x() + recWidth + recSpace, bottomRight.y() - recHeight * 2));
    bottomRectVec.append(QPointF(bottomRight.x() - recWidth - recSpace, bottomRight.y() - recHeight * 2));
    bottomRectVec.append(QPointF(bottomRight.x() - recSpace, bottomRight.y()));

    QVector<QPointF> bottomRightRectVec;
    bottomRightRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() + recHeight + recSpace));
    bottomRightRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y() + recSpace));
    bottomRightRectVec.append(QPointF(midRight.x(), midRight.y() + recHeight + recSpace));
    bottomRightRectVec.append(QPointF(bottomRight.x(), bottomRight.y()));
    bottomRightRectVec.append(QPointF(bottomRight.x() - recWidth, bottomRight.y() - recHeight * 2));

    QLinearGradient numberGradient(QPointF(0, 0), QPointF(0, this->height()));
    numberGradient.setColorAt(0.0, d->m_numberStartColor);
    numberGradient.setColorAt(1.0, d->m_numberEndColor);
    painter->setBrush(numberGradient);

    switch (d->m_number) {
    case 0:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 1:
        //painter->drawPolygon(topLeftRectVec);
        //painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 2:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        //painter->drawPolygon(bottomRightRectVec);
        break;
    case 3:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 4:
        painter->drawPolygon(topLeftRectVec);
        //painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 5:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        //painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 6:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        //painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 7:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 8:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 9:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    default:
        break;
    }

    switch (d->m_symbol) {
    case QExtNumberLed::Symbol_Dot:
    {
        painter->drawEllipse(bottomRight.x() + margin, bottomRight.y() - recHeight - recRadius / 2, recRadius, recRadius);
        break;
    }
    case QExtNumberLed::Symbol_Colon:
    {
        int iHeight = this->height() / 3;
        painter->drawEllipse(bottomRight.x() + margin, iHeight, recRadius, recRadius);
        painter->drawEllipse(bottomRight.x() + margin, iHeight * 2, recRadius, recRadius);
        break;
    }
    case QExtNumberLed::Symbol_Line:
    {
        QVector<QPointF> lineRectVec;
        lineRectVec.append(QPointF(midRight.x() + recRadius, midRight.y() - recHeight));
        lineRectVec.append(QPointF(this->width() - recSpace, midRight.y() - recHeight));
        lineRectVec.append(QPointF(this->width() - recSpace, midRight.y() + recHeight));
        lineRectVec.append(QPointF(midRight.x() + recRadius, midRight.y() + recHeight));
        painter->drawPolygon(lineRectVec);
        break;
    }
    default:
        break;
    }

    painter->restore();
}

