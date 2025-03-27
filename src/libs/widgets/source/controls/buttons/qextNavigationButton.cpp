/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2018 feiyangqingyun. Contact: QQ:517216493
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

#include <private/qextNavigationButton_p.h>

#include <QDebug>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

QExtNavigationButtonPrivate::QExtNavigationButtonPrivate(QExtNavigationButton *q)
    : q_ptr(q)
{
    m_padding = 5;
    m_hovered = false;
    m_iconSpace = 10;
    m_iconVisible = true;
    m_textPixelSize = -1;
    m_navigationPosition = QExtNavigationButton::Position_Right;
}

QExtNavigationButtonPrivate::~QExtNavigationButtonPrivate()
{

}


QExtNavigationButton::QExtNavigationButton(QWidget *parent)
    : QPushButton(parent)
    , dd_ptr(new QExtNavigationButtonPrivate(this))
{
    this->setCheckable(true);
}

QExtNavigationButton::~QExtNavigationButton()
{

}

void QExtNavigationButton::setCheckable(bool)
{
    QPushButton::setCheckable(true);
}

QExtNavigationButton::PositionEnum QExtNavigationButton::navigationPosition() const
{
    Q_D(const QExtNavigationButton);
    return d->m_navigationPosition;
}

void QExtNavigationButton::setNavigationPosition(QExtNavigationButton::PositionEnum position)
{
    Q_D(QExtNavigationButton);
    if (d->m_navigationPosition != position)
    {
        d->m_navigationPosition = position;
        this->update();
    }
}

void QExtNavigationButton::enterEvent(QEvent *)
{
    Q_D(QExtNavigationButton);
    d->m_hovered = true;
    this->update();
}

void QExtNavigationButton::leaveEvent(QEvent *)
{
    Q_D(QExtNavigationButton);
    d->m_hovered = false;
    this->update();
}

void QExtNavigationButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);
    this->drawText(&painter);
    this->drawIcon(&painter);
    this->drawLine(&painter);
    this->drawTriangle(&painter);
}

void QExtNavigationButton::drawBackground(QPainter *painter)
{
    Q_D(QExtNavigationButton);

    painter->save();
    QColor color;
    QPalette palette = this->palette();
    QWidget *parentWidget = this->parentWidget();
    QPalette parentPalette = parentWidget ? parentWidget->palette() : QPalette();
    const bool checked = this->isChecked();
    const bool enabled = this->isEnabled();
    painter->setPen(Qt::NoPen);
    if (this->isFlat())
    {
        if (checked)
        {
            color = palette.color(QPalette::ButtonText);
            color.setAlphaF(0.2);
        }
        else if (enabled && d->m_hovered)
        {
            color = palette.color(QPalette::ButtonText);
            color.setAlphaF(0.2);
        }
        else
        {
            color = parentPalette.color(QPalette::Window);
        }
    }
    else
    {
        if (checked)
        {
            color = palette.color(QPalette::ButtonText);
            if (!enabled)
            {
                color.setAlphaF(0.2);
            }
        }
        else if (enabled && d->m_hovered)
        {
            color = palette.color(QPalette::ButtonText);
            color.setAlphaF(0.2);
        }
        else
        {
            color = parentPalette.color(QPalette::Window);
        }
    }
    painter->setBrush(color);

    QRect bgRect;
    int width = this->width();
    int height = this->height();
    const int lineSpace = 0;
    if (Position_Left == d->m_navigationPosition)
    {
        bgRect = QRect(lineSpace, 0, width - lineSpace, height);
    }
    else if (Position_Right == d->m_navigationPosition)
    {
        bgRect = QRect(0, 0, width - lineSpace, height);
    }
    else if (Position_Top == d->m_navigationPosition)
    {
        bgRect = QRect(0, lineSpace, width, height - lineSpace);
    }
    else if (Position_Bottom == d->m_navigationPosition)
    {
        bgRect = QRect(0, 0, width, height - lineSpace);
    }
    painter->drawRect(bgRect);

    painter->restore();
}

void QExtNavigationButton::drawText(QPainter *painter)
{
    Q_D(QExtNavigationButton);

    painter->save();
    QColor color;
    QPalette palette = this->palette();
    QWidget *parentWidget = this->parentWidget();
    QPalette parentPalette = parentWidget ? parentWidget->palette() : QPalette();
    painter->setBrush(Qt::NoBrush);
    const bool checked = this->isChecked();
    const bool enabled = this->isEnabled();
    if (this->isFlat())
    {
        color = palette.color(QPalette::ButtonText);
    }
    else
    {
        if (checked)
        {
            color = enabled ? parentPalette.color(QPalette::Window)
                            : palette.color(QPalette::ButtonText);
        }
        else
        {
            color = palette.color(QPalette::ButtonText);
        }
    }
    painter->setPen(color);

    int width = this->width();
    int height = this->height();
    QRect textRect;
    int textAlign = Qt::AlignCenter;
    if (Position_Left == d->m_navigationPosition)
    {
        textRect = QRect(d->m_padding, 0, width - d->m_padding, height);
        textAlign = Qt::AlignVCenter | Qt::AlignLeft;
    }
    else if (Position_Right == d->m_navigationPosition)
    {
        textRect = QRect(0, 0, width - d->m_padding, height);
        textAlign = Qt::AlignVCenter | Qt::AlignRight;
    }
    else if (Position_Top == d->m_navigationPosition)
    {
        textRect = QRect(0, d->m_padding, width, height - d->m_padding);
        textAlign = Qt::AlignHCenter | Qt::AlignTop;
    }
    else if (Position_Bottom == d->m_navigationPosition)
    {
        textRect = QRect(0, 0, width, height - d->m_padding);
        textAlign = Qt::AlignHCenter | Qt::AlignBottom;
    }
    QFont font = this->font();
    if (d->m_textPixelSize > 0)
    {
        font.setPixelSize(d->m_textPixelSize);
    }
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(textRect, textAlign, this->text());
    painter->restore();
}

void QExtNavigationButton::drawIcon(QPainter *painter)
{
    Q_D(QExtNavigationButton);
    if (!d->m_iconVisible)
    {
        return;
    }
    QIcon icon = this->icon();
    if (icon.isNull())
    {
        return;
    }

    painter->save();
    QRect iconRect;
    const int width = this->width();
    const int height = this->height();
    const QSize iconSize = this->iconSize();
    if (Position_Right == d->m_navigationPosition)
    {
        iconRect = QRect(d->m_iconSpace, (height - iconSize.height()) / 2,
                         iconSize.width(), iconSize.height());
    }
    else if (Position_Left == d->m_navigationPosition)
    {
        iconRect = QRect(width - d->m_iconSpace, (height - iconSize.height()) / 2,
                         iconSize.width(), iconSize.height());
    }
    else if (Position_Bottom == d->m_navigationPosition)
    {
        iconRect = QRect((width - iconSize.width()) / 2, d->m_iconSpace,
                         iconSize.width(), iconSize.height());
    }
    else if (Position_Top == d->m_navigationPosition)
    {
        iconRect = QRect((width - iconSize.width()) / 2, height - d->m_iconSpace,
                         iconSize.width(), iconSize.height());
    }
    QPixmap pixmap = icon.pixmap(this->iconSize());
    QPalette palette = this->palette();
    QWidget *parentWidget = this->parentWidget();
    QPalette parentPalette = parentWidget ? parentWidget->palette() : QPalette();
    if (!this->isEnabled())
    {
        QPainter iconPainter(&pixmap);
        iconPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        iconPainter.fillRect(pixmap.rect(), palette.color(QPalette::ButtonText));
    }
    else if (!this->isFlat() && this->isChecked())
    {
        QPainter iconPainter(&pixmap);
        iconPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        iconPainter.fillRect(pixmap.rect(), parentPalette.color(QPalette::Window));
    }
    painter->drawPixmap(iconRect, pixmap);

    painter->restore();
}

void QExtNavigationButton::drawLine(QPainter *painter)
{
    Q_D(QExtNavigationButton);
    if (!this->isFlat())
    {
        return;
    }
    if (!this->isChecked() && !d->m_hovered)
    {
        return;
    }
    if (!this->isChecked() && !this->isEnabled() && d->m_hovered)
    {
        return;
    }

    painter->save();
    QColor color;
    QPalette palette = this->palette();
    color = palette.color(QPalette::ButtonText);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(this->font().pixelSize() / 2);
    painter->setPen(pen);

    QPoint pointStart, pointEnd;
    if (Position_Left == d->m_navigationPosition)
    {
        pointStart = QPoint(0, 0);
        pointEnd = QPoint(0, height());
    }
    else if (Position_Right == d->m_navigationPosition)
    {
        pointStart = QPoint(width(), 0);
        pointEnd = QPoint(width(), height());
    }
    else if (Position_Top == d->m_navigationPosition)
    {
        pointStart = QPoint(0, 0);
        pointEnd = QPoint(width(), 0);
    }
    else if (Position_Bottom == d->m_navigationPosition)
    {
        pointStart = QPoint(0, height());
        pointEnd = QPoint(width(), height());
    }

    painter->drawLine(pointStart, pointEnd);

    painter->restore();
}

void QExtNavigationButton::drawTriangle(QPainter *painter)
{
    Q_D(QExtNavigationButton);
    if (this->isFlat())
    {
        return;
    }

    if (!this->isChecked() && !d->m_hovered)
    {
        return;
    }

    painter->save();
    QColor color;
    QWidget *parentWidget = this->parentWidget();
    QPalette parentPalette = parentWidget ? parentWidget->palette() : this->palette();
    color = parentPalette.color(QPalette::Window);
    painter->setBrush(color);
    painter->setPen(color);

    const int width = this->width();
    const int height = this->height();
    const int midWidth = width / 2;
    const int midHeight = height / 2;
    const int triangleLen = this->fontMetrics().height() / 2;
    QPolygon polygon;
    if (d->m_navigationPosition == Position_Left)
    {
        polygon.setPoints(3, triangleLen,
                          midHeight, 0, midHeight - triangleLen,
                          0, midHeight + triangleLen);
    }
    else if (d->m_navigationPosition == Position_Right)
    {
        polygon.setPoints(3, width - triangleLen,
                          midHeight, width,
                          midHeight - triangleLen, width, midHeight + triangleLen);
    }
    else if (d->m_navigationPosition == Position_Top)
    {
        polygon.setPoints(3, midWidth,
                          triangleLen, midWidth - triangleLen,
                          0, midWidth + triangleLen, 0);
    }
    else if (d->m_navigationPosition == Position_Bottom)
    {
        polygon.setPoints(3, midWidth,
                          height - triangleLen, midWidth - triangleLen,
                          height, midWidth + triangleLen, height);
    }

    painter->drawPolygon(polygon);

    painter->restore();
}

int QExtNavigationButton::padding() const
{
    Q_D(const QExtNavigationButton);
    return d->m_padding;
}

void QExtNavigationButton::setPadding(int padding)
{
    Q_D(QExtNavigationButton);
    if (padding != d->m_padding)
    {
        d->m_padding = padding;
        this->update();
    }
}

bool QExtNavigationButton::isIconVisible() const
{
    Q_D(const QExtNavigationButton);
    return d->m_iconVisible;
}

void QExtNavigationButton::setIconVisible(bool visiable)
{
    Q_D(QExtNavigationButton);
    if (visiable != d->m_iconVisible)
    {
        d->m_iconVisible = visiable;
        this->update();
    }
}

int QExtNavigationButton::textPixelSize() const
{
    Q_D(const QExtNavigationButton);
    return d->m_textPixelSize;
}

void QExtNavigationButton::setTextPixelSize(int size)
{
    Q_D(QExtNavigationButton);
    if (size != d->m_textPixelSize)
    {
        d->m_textPixelSize = size;
        this->update();
    }
}

int QExtNavigationButton::iconSpace() const
{
    Q_D(const QExtNavigationButton);
    return d->m_iconSpace;
}

void QExtNavigationButton::setIconSpace(int space)
{
    Q_D(QExtNavigationButton);
    if (space != d->m_iconSpace)
    {
        d->m_iconSpace = space;
        this->update();
    }
}

QSize QExtNavigationButton::sizeHint() const
{
    return QSize(100, 30);
}

QSize QExtNavigationButton::minimumSizeHint() const
{
    return QSize(20, 10);
}
