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
    m_hovered = false;
    m_padding = 5;
    m_iconSpace = 10;
    m_iconVisible = false;
    m_normalIcon = QPixmap();
    m_hoverIcon = QPixmap();
    m_checkIcon = QPixmap();
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
    painter->setPen(Qt::NoPen);
    if (this->isFlat())
    {
        color = palette.color(QPalette::Button);
    }
    else
    {
        if (this->isChecked())
        {
            color = palette.color(QPalette::ButtonText);
        }
        else if (this->isEnabled() && d->m_hovered)
        {
            color = palette.color(QPalette::ButtonText);
            color.setAlphaF(0.2);
        }
        else
        {
            color = palette.color(QPalette::Button);
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
    painter->setBrush(Qt::NoBrush);
    const bool checked = this->isChecked();
    if (this->isFlat())
    {
        color = checked || d->m_hovered ? palette.color(QPalette::ButtonText)
                                        : palette.color(QPalette::BrightText);
    }
    else
    {
        if (checked)
        {
            color = this->isEnabled() ? palette.color(QPalette::Button)
                                      : palette.color(QPalette::BrightText);
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

    painter->save();
    QColor iconColor;
    QPalette palette = this->palette();
    const bool checked = this->isChecked();
    if (this->isFlat())
    {
        iconColor = checked || d->m_hovered ? palette.color(QPalette::ButtonText)
                                            : palette.color(QPalette::BrightText);
    }
    else
    {
        iconColor = checked ? palette.color(QPalette::Button)
                            : palette.color(QPalette::ButtonText);
    }

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

    QPixmap pixmap;
    if (this->isChecked())
    {
        pixmap = d->m_checkIcon;
    }
    else if (d->m_hovered)
    {
        pixmap = d->m_hoverIcon;
    }
    else
    {
        pixmap = d->m_normalIcon;
    }
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPainter iconPainter(&pixmap);
        iconPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        iconPainter.fillRect(pixmap.rect(), iconColor);
        painter->drawPixmap(iconRect, pixmap);
    }

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

    painter->save();
    QPen pen;
    pen.setWidth(this->font().pixelSize() / 2);
    pen.setColor(this->palette().color(QPalette::ButtonText));
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
    QPalette palette = this->palette();
    color = palette.color(QPalette::Button);
    painter->setBrush(color);
    painter->setPen(Qt::NoPen);

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
    if (d->m_padding != padding)
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
    if (d->m_iconVisible != visiable)
    {
        d->m_iconVisible = visiable;
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
    if (d->m_iconSpace != space)
    {
        d->m_iconSpace = space;
        this->update();
    }
}

QPixmap QExtNavigationButton::normalIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_normalIcon;
}

void QExtNavigationButton::setNormalIcon(const QPixmap &pixmap)
{
    Q_D(QExtNavigationButton);
    d->m_normalIcon = pixmap;
    this->update();
}

QPixmap QExtNavigationButton::hoveredIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_hoverIcon;
}

void QExtNavigationButton::setHoverIcon(const QPixmap &pixmap)
{
    Q_D(QExtNavigationButton);
    d->m_hoverIcon = pixmap;
    this->update();
}

QPixmap QExtNavigationButton::checkedIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_checkIcon;
}

void QExtNavigationButton::setCheckIcon(const QPixmap &pixmap)
{
    Q_D(QExtNavigationButton);
    d->m_checkIcon = pixmap;
    this->update();
}

void QExtNavigationButton::setIcon(const QPixmap &pixmap)
{
    this->setNormalIcon(pixmap);
    this->setHoverIcon(pixmap);
    this->setCheckIcon(pixmap);
}

void QExtNavigationButton::setIcon(const QIcon &icon)
{
    this->setIcon(icon.pixmap(this->iconSize()));
    QPushButton::setIcon(icon);
}

QSize QExtNavigationButton::sizeHint() const
{
    return QSize(100, 30);
}

QSize QExtNavigationButton::minimumSizeHint() const
{
    return QSize(20, 10);
}
