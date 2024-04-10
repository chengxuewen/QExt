/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2022~Present ChengXueWen. Contact: 1398831004@qq.com.
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

#include <private/qextTextLcd_p.h>

#include <QDebug>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QImage>
#include <QVector>
#include <QFontMetrics>
#include <QResizeEvent>
#include <QApplication>

QExtTextLcdPrivate::QExtTextLcdPrivate(QExtTextLcd *q)
    : q_ptr(q)
{
    m_text = "";
    m_textAlignment = Qt::AlignCenter;
    m_fontPixelSize = 12;
    m_rowCount = 16;
    m_radius = 0;
    m_hBorder= 0;
    m_space = 0;
    m_step = 0;
    m_spaceFactory = 0.25;
    m_foregroundColor = QColor(100, 100, 100);
    m_backgroundColor = QColor(Qt::black);
    m_textColor = QColor(100, 184, 255);

    m_highLightBorder = false;
    m_animationType = QExtTextLcd::Animation_Static;
    m_animationInterval = 50;
    m_animationOffset = 0;
}

QExtTextLcdPrivate::~QExtTextLcdPrivate()
{
    if (m_animationTimer->isActive()) {
        m_animationTimer->stop();
    }
}

QExtTextLcd::QExtTextLcd(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtTextLcdPrivate(this))
{
    Q_D(QExtTextLcd);
    d->m_animationTimer.reset(new QTimer);
    d->m_animationTimer->setInterval(d->m_animationInterval);
    connect(d->m_animationTimer.data(), SIGNAL(timeout()), this, SLOT(updateOffsetValue()));
}

QExtTextLcd::~QExtTextLcd()
{

}

QString QExtTextLcd::text() const
{
    Q_D(const QExtTextLcd);
    return d->m_text;
}

int QExtTextLcd::textAlignment() const
{
    Q_D(const QExtTextLcd);
    return d->m_textAlignment;
}

int QExtTextLcd::fontPixelSize() const
{
    Q_D(const QExtTextLcd);
    return d->m_fontPixelSize;
}

int QExtTextLcd::rowCount() const
{
    Q_D(const QExtTextLcd);
    return d->m_rowCount;
}

double QExtTextLcd::spaceFactory() const
{
    Q_D(const QExtTextLcd);
    return d->m_spaceFactory;
}

bool QExtTextLcd::isHighLightBorderEnable() const
{
    Q_D(const QExtTextLcd);
    return d->m_highLightBorder;
}

QExtTextLcd::Animation QExtTextLcd::animationType() const
{
    Q_D(const QExtTextLcd);
    return d->m_animationType;
}

int QExtTextLcd::animationInterval() const
{
    Q_D(const QExtTextLcd);
    return d->m_animationInterval;
}

QColor QExtTextLcd::textColor() const
{
    Q_D(const QExtTextLcd);
    return d->m_textColor;
}

QColor QExtTextLcd::foregroundColor() const
{
    Q_D(const QExtTextLcd);
    return d->m_foregroundColor;
}

QColor QExtTextLcd::backgroundColor() const
{
    Q_D(const QExtTextLcd);
    return d->m_backgroundColor;
}

QSize QExtTextLcd::sizeHint() const
{
    return QSize(200, 80);
}

QSize QExtTextLcd::minimumSizeHint() const
{
    Q_D(const QExtTextLcd);
    return QSize(30, d->m_fontPixelSize * 2);
}

void QExtTextLcd::setText(const QString &strText)
{
    Q_D(QExtTextLcd);
    if (strText != d->m_text) {
        d->m_text = strText;
        this->update();
    }
}

void QExtTextLcd::setTextAlignment(const int &iAlign)
{
    Q_D(QExtTextLcd);
    if (iAlign != d->m_textAlignment) {
        d->m_textAlignment = iAlign;
        this->update();
    }
}

void QExtTextLcd::setFontPixelSize(const int &iSize)
{
    Q_D(QExtTextLcd);
    if (iSize < 8) {
        qWarning() << "QExtTextLcd::setFontPixelSize():iSize must be greate than 8!";
        return;
    }
    if (iSize != d->m_fontPixelSize) {
        d->m_fontPixelSize = iSize;
        this->update();
    }
}

void QExtTextLcd::setRowCount(const int &iCount)
{
    Q_D(QExtTextLcd);
    if (iCount < 8) {
        qWarning() << "QExtTextLcd::setRowCount():iCount must be greate than 8!";
        return;
    }
    if (iCount != d->m_rowCount) {
        d->m_rowCount = iCount;
        this->update();
    }
}

void QExtTextLcd::setSpaceFactory(const double &dFac)
{
    Q_D(QExtTextLcd);
    if (dFac <= 0 || dFac >= 1) {
        qWarning() << "QExtTextLcd::setSpaceFactory():dFac must be greater than 0 and less than 1!";
        return;
    }
    if (dFac != d->m_spaceFactory) {
        d->m_spaceFactory = dFac;
        this->update();
    }
}

void QExtTextLcd::setHighLightBorderEnable(const bool &bEnable)
{
    Q_D(QExtTextLcd);
    if (bEnable != d->m_highLightBorder) {
        d->m_highLightBorder = bEnable;
        this->update();
    }
}

void QExtTextLcd::setAnimationType(const QExtTextLcd::Animation &eType)
{
    Q_D(QExtTextLcd);
    if (eType != d->m_animationType) {
        d->m_animationType = eType;
        if (Animation_Static == eType) {
            if (d->m_animationTimer->isActive()) {
                d->m_animationTimer->stop();
            }
        } else {
            d->m_animationOffset = 0;
            d->m_animationTimer->start();
        }
        this->update();
    }
}

void QExtTextLcd::setAnimationInterval(const int &iInterval)
{
    Q_D(QExtTextLcd);
    if (iInterval <= 0) {
        qWarning() << "QExtTextLcd::setAnimationInterval():iInterval must be greate than 0!";
        return;
    }
    if (iInterval != d->m_animationInterval) {
        d->m_animationInterval = iInterval;
        d->m_animationTimer->setInterval(iInterval);
        this->update();
    }
}

void QExtTextLcd::setTextColor(const QColor &color)
{
    Q_D(QExtTextLcd);
    if (color != d->m_textColor) {
        d->m_textColor = color;
        this->update();
    }
}

void QExtTextLcd::setForegroundColor(const QColor &color)
{
    Q_D(QExtTextLcd);
    if (color != d->m_foregroundColor) {
        d->m_foregroundColor = color;
        this->update();
    }
}

void QExtTextLcd::setBackgroundColor(const QColor &color)
{
    Q_D(QExtTextLcd);
    if (color != d->m_backgroundColor) {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QExtTextLcd::updateOffsetValue()
{
    Q_D(QExtTextLcd);
    d->m_animationOffset++;
    switch (d->m_animationType) {
    case QExtTextLcd::Animation_LeftToRight:
    case QExtTextLcd::Animation_RightToLeft:
    {
        if (d->m_animationOffset >= d->m_imageSize.width() * 2) {
            d->m_animationOffset = 0;
        }
        break;
    }
    case QExtTextLcd::Animation_TopToBottom:
    case QExtTextLcd::Animation_BottomToTop:
    {
        if (d->m_animationOffset >= d->m_imageSize.height() * 2) {
            d->m_animationOffset = 0;
        }
        break;
    }
    default:
        break;
    }
    this->update();
}

void QExtTextLcd::paintEvent(QPaintEvent *)
{
    Q_D(QExtTextLcd);
    if (d->m_ledTextSizeF.toSize() != this->size()) {
        d->m_ledTextSizeF = this->size();
        d->m_step = d->m_ledTextSizeF.height() / double(d->m_rowCount);
        d->m_columnCount = int(d->m_ledTextSizeF.width() / d->m_step);
        d->m_hBorder = (d->m_ledTextSizeF.width() - d->m_step * d->m_columnCount) / 2;
        d->m_space = d->m_step * d->m_spaceFactory;
        d->m_radius = (d->m_step - d->m_space) / 2;
        d->m_pointFVector.resize(d->m_rowCount);
        for (int i = 0; i < d->m_rowCount; ++i) {
            d->m_pointFVector[i].resize(d->m_columnCount);
            double dPosY = (i * 2 + 1) * (d->m_step / 2);
            for (int j = 0; j < d->m_columnCount; ++j) {
                double dPosX = d->m_hBorder + (j * 2 + 1) * (d->m_step / 2);
                d->m_pointFVector[i][j] = QPointF(dPosX, dPosY);
            }
        }
        if (d->m_animationTimer->isActive()) {
            d->m_animationTimer->stop();
            d->m_animationOffset = 0;
            d->m_animationTimer->start();
        }
    }

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    if (QColor(Qt::transparent) != d->m_backgroundColor) {
        painter.setPen(Qt::NoPen);
        painter.fillRect(this->rect(), d->m_backgroundColor);
    }

    //set font
    QFont font = this->font();
    font.setPixelSize(d->m_fontPixelSize);
    font.setStyleStrategy(QFont::NoAntialias);

    //get rect
    QFontMetrics fontMetrics(font);
    QSize fontSize = fontMetrics.size(d->m_textAlignment, d->m_text);
    int iWidth = qMax(fontSize.width(), d->m_columnCount);
    int iHeight = qMax(fontSize.height(), d->m_rowCount);
    QRect imageRect = QRect(0, 0, iWidth, iHeight);
    d->m_imageSize.setWidth(iWidth);
    d->m_imageSize.setHeight(iHeight);

    //draw image
    QImage textImage(d->m_imageSize, QImage::Format_ARGB32_Premultiplied);
    QPainter imagePainter(&textImage);
    imagePainter.setFont(font);
    imagePainter.setBrush(Qt::white);
    imagePainter.setPen(Qt::white);
    imagePainter.drawRect(imageRect);
    imagePainter.setPen(Qt::black);
    imagePainter.drawText(imageRect, d->m_textAlignment, d->m_text);

    int iIndendX = (d->m_imageSize.width() - d->m_columnCount) / 2;
    int iIndendY = (d->m_imageSize.height() - d->m_rowCount) / 2;
    for (int i = 0; i < d->m_imageSize.height(); ++i) {
        for (int j = 0; j < d->m_imageSize.width(); ++j) {
            QColor color = d->m_foregroundColor;
            int iPixelX = j;
            int iPixelY = i;
            switch (d->m_animationType) {
            case Animation_Static:
            {
                iPixelX = iIndendX + j;
                iPixelY = iIndendY + i;
                break;
            }
            case Animation_LeftToRight:
            {
                iPixelX = d->m_imageSize.width() - d->m_animationOffset + j;
                iPixelY = iIndendY + i;
                break;
            }
            case Animation_RightToLeft:
            {
                iPixelX = d->m_animationOffset + j - d->m_imageSize.width();
                iPixelY = iIndendY + i;
                break;
            }
            case Animation_TopToBottom:
            {
                iPixelX = j + iIndendX;
                iPixelY = d->m_imageSize.height() - d->m_animationOffset + i;
                break;
            }
            case Animation_BottomToTop:
            {
                iPixelX = j + iIndendX;
                iPixelY = d->m_animationOffset + i - d->m_imageSize.height();
                break;
            }
            default:
                break;
            }
            if (iPixelX >= 0 && iPixelX < d->m_imageSize.width() && iPixelY >= 0 && iPixelY < d->m_imageSize.height()) {
                if (QColor(textImage.pixel(iPixelX, iPixelY)).name() != "#ffffff") {
                    color = d->m_textColor;
                }
            }
            if (d->m_highLightBorder) {
                if (0 == i || (d->m_rowCount - 1) == i || 0 == j || (d->m_columnCount - 1) == j) {
                    color = d->m_textColor;
                }
            }
            if (i < d->m_rowCount && j < d->m_columnCount) {
                QPointF pointF = d->m_pointFVector[i][j];
                painter.setBrush(QBrush(color));
                painter.drawEllipse(pointF, d->m_radius, d->m_radius);
            }
        }
    }
}
