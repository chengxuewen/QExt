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
    m_leftPadding = 5;
    m_rightPadding = 5;
    m_topPadding = 5;
    m_bottomPadding = 5;
    m_textAlign = QExtNavigationButton::TextAlign_Center;

    m_triangleVisible = false;
    m_triangleLen = 5;
    m_trianglePosition = QExtNavigationButton::Position_Right;
    m_triangleColor = QColor(255, 255, 255);

    m_iconVisible = false;
    m_iconPosition = QExtNavigationButton::Position_Left;
    m_iconSpace = 10;
    m_iconSize = QSize(16, 16);
    m_normalIcon = QPixmap();
    m_hoverIcon = QPixmap();
    m_checkIcon = QPixmap();

    m_lineVisible = true;
    m_lineSpace = 0;
    m_lineWidth = 5;
    m_linePosition = QExtNavigationButton::Position_Left;
    m_lineColor = QColor(0, 187, 158);

    m_normalBackgroundColor = QColor(230, 230, 230);
    m_hoverBackgroundColor = QColor(130, 130, 130);
    m_checkBackgroundColor = QColor(80, 80, 80);
    m_normalTextColor = QColor(100, 100, 100);
    m_hoverTextColor = QColor(255, 255, 255);
    m_checkTextColor = QColor(255, 255, 255);

    m_normalBackgroundBrush = Qt::NoBrush;
    m_hoverBackgroundBrush = Qt::NoBrush;
    m_checkBackgroundBrush = Qt::NoBrush;

    m_hovered = false;
}

QExtNavigationButtonPrivate::~QExtNavigationButtonPrivate()
{

}


QExtNavigationButton::QExtNavigationButton(QWidget *parent)
    : QPushButton(parent), dd_ptr(new QExtNavigationButtonPrivate(this))
{
    this->setCheckable(true);
}

QExtNavigationButton::~QExtNavigationButton()
{

}

void QExtNavigationButton::setIcon(const QIcon &icon)
{
    this->setIcon(icon.pixmap(100, 100));
    QPushButton::setIcon(icon);
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

void QExtNavigationButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);
    this->drawText(&painter);
    this->drawIcon(&painter);
    this->drawLine(&painter);
    this->drawTriangle(&painter);

    QStyleOption opt;

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    opt.initFrom(this);
#else
    opt.init(this);
#endif
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void QExtNavigationButton::drawBackground(QPainter *painter)
{
    Q_D(QExtNavigationButton);
    painter->save();
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();

    QRect bgRect;
    if (d->m_linePosition == Position_Left)
    {
        bgRect = QRect(d->m_lineSpace, 0, width - d->m_lineSpace, height);
    }
    else if (d->m_linePosition == Position_Right)
    {
        bgRect = QRect(0, 0, width - d->m_lineSpace, height);
    }
    else if (d->m_linePosition == Position_Top)
    {
        bgRect = QRect(0, d->m_lineSpace, width, height - d->m_lineSpace);
    }
    else if (d->m_linePosition == Position_Bottom)
    {
        bgRect = QRect(0, 0, width, height - d->m_lineSpace);
    }

    QBrush bgBrush;
    if (isChecked())
    {
        bgBrush = d->m_checkBackgroundBrush;
    }
    else if (d->m_hovered)
    {
        bgBrush = d->m_hoverBackgroundBrush;
    }
    else
    {
        bgBrush = d->m_normalBackgroundBrush;
    }

    if (bgBrush != Qt::NoBrush)
    {
        painter->setBrush(bgBrush);
    }
    else
    {
        QColor bgColor;
        if (isChecked())
        {
            bgColor = d->m_checkBackgroundColor;
        }
        else if (d->m_hovered)
        {
            bgColor = d->m_hoverBackgroundColor;
        }
        else
        {
            bgColor = d->m_normalBackgroundColor;
        }

        painter->setBrush(bgColor);
    }

    painter->drawRect(bgRect);

    painter->restore();
}

void QExtNavigationButton::drawText(QPainter *painter)
{
    Q_D(QExtNavigationButton);

    painter->save();
    int width = this->width();
    int height = this->height();
    painter->setBrush(Qt::NoBrush);

    QColor textColor;
    if (this->isChecked())
    {
        textColor = d->m_checkTextColor;
    }
    else if (d->m_hovered)
    {
        textColor = d->m_hoverTextColor;
    }
    else
    {
        textColor = d->m_normalTextColor;
    }

    QRect textRect = QRect(d->m_leftPadding, d->m_topPadding, width - d->m_leftPadding - d->m_rightPadding, height - d->m_topPadding - d->m_bottomPadding);
    painter->setPen(textColor);
    painter->drawText(textRect, d->m_textAlign, this->text());

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
    int width = this->width();
    int height = this->height();

    QRect iconRect;
    if (Position_Left == d->m_iconPosition)
    {
        iconRect = QRect(d->m_iconSpace, (height - d->m_iconSize.height()) / 2, d->m_iconSize.width(), d->m_iconSize.height());
    }
    else if (Position_Right == d->m_iconPosition)
    {
        iconRect = QRect(width - d->m_iconSpace, (height - d->m_iconSize.height()) / 2, d->m_iconSize.width(), d->m_iconSize.height());
    }
    else if (Position_Top == d->m_iconPosition)
    {
        iconRect = QRect((width - d->m_iconSize.width()) / 2, d->m_iconSpace, d->m_iconSize.width(), d->m_iconSize.height());
    }
    else if (Position_Bottom == d->m_iconPosition)
    {
        iconRect = QRect((width - d->m_iconSize.width()) / 2, height - d->m_iconSpace, d->m_iconSize.width(), d->m_iconSize.height());
    }

    QPixmap pix;
    QChar fontIcon;
    QColor iconColor;
    if (this->isChecked())
    {
        pix = d->m_checkIcon;
        fontIcon = d->m_checkFontIcon;
        iconColor = d->m_checkTextColor;
    }
    else if (d->m_hovered)
    {
        pix = d->m_hoverIcon;
        fontIcon = d->m_hoverFontIcon;
        iconColor = d->m_hoverTextColor;
    }
    else
    {
        pix = d->m_normalIcon;
        fontIcon = d->m_normalFontIcon;
        iconColor = d->m_normalTextColor;
    }
    if (!pix.isNull())
    {
        pix = pix.scaled(d->m_iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPainter iconPainter(&pix);
        iconPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        iconPainter.fillRect(pix.rect(), iconColor);
        painter->drawPixmap(iconRect, pix);
    } else if (!fontIcon.isNull()) {
        QFont font;
        font.setPixelSize(d->m_iconSize.height());
        painter->setFont(font);
        painter->setPen(iconColor);
        painter->drawText(iconRect, Qt::AlignCenter, fontIcon);
    }

    painter->restore();
}

void QExtNavigationButton::drawLine(QPainter *painter)
{
    Q_D(QExtNavigationButton);
    if (!d->m_lineVisible)
    {
        return;
    }

    if (!isChecked())
    {
        return;
    }

    painter->save();

    QPen pen;
    pen.setWidth(d->m_lineWidth);
    pen.setColor(d->m_lineColor);
    painter->setPen(pen);

    QPoint pointStart, pointEnd;
    if (d->m_linePosition == Position_Left)
    {
        pointStart = QPoint(0, 0);
        pointEnd = QPoint(0, height());
    }
    else if (d->m_linePosition == Position_Right)
    {
        pointStart = QPoint(width(), 0);
        pointEnd = QPoint(width(), height());
    }
    else if (d->m_linePosition == Position_Top)
    {
        pointStart = QPoint(0, 0);
        pointEnd = QPoint(width(), 0);
    }
    else if (d->m_linePosition == Position_Bottom)
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
    if (!d->m_triangleVisible)
    {
        return;
    }

    if (!d->m_hovered && !isChecked())
    {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_triangleColor);

    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;

    QPolygon pts;
    if (d->m_trianglePosition == Position_Left)
    {
        pts.setPoints(3, d->m_triangleLen, midHeight, 0, midHeight - d->m_triangleLen, 0, midHeight + d->m_triangleLen);
    }
    else if (d->m_trianglePosition == Position_Right)
    {
        pts.setPoints(3, width - d->m_triangleLen, midHeight, width, midHeight - d->m_triangleLen, width, midHeight + d->m_triangleLen);
    }
    else if (d->m_trianglePosition == Position_Top)
    {
        pts.setPoints(3, midWidth, d->m_triangleLen, midWidth - d->m_triangleLen, 0, midWidth + d->m_triangleLen, 0);
    }
    else if (d->m_trianglePosition == Position_Bottom)
    {
        pts.setPoints(3, midWidth, height - d->m_triangleLen, midWidth - d->m_triangleLen, height, midWidth + d->m_triangleLen, height);
    }

    painter->drawPolygon(pts);

    painter->restore();
}

int QExtNavigationButton::leftPadding() const
{
    Q_D(const QExtNavigationButton);
    return d->m_leftPadding;
}

int QExtNavigationButton::rightPadding() const
{
    Q_D(const QExtNavigationButton);
    return d->m_rightPadding;
}

int QExtNavigationButton::topPadding() const
{
    Q_D(const QExtNavigationButton);
    return d->m_topPadding;
}

int QExtNavigationButton::bottomPadding() const
{
    Q_D(const QExtNavigationButton);
    return d->m_bottomPadding;
}

QExtNavigationButton::TextAlignType QExtNavigationButton::textAlign() const
{
    Q_D(const QExtNavigationButton);
    return d->m_textAlign;
}

bool QExtNavigationButton::isTriangleVisible() const
{
    Q_D(const QExtNavigationButton);
    return d->m_triangleVisible;
}

int QExtNavigationButton::triangleLen() const
{
    Q_D(const QExtNavigationButton);
    return d->m_triangleLen;
}

QExtNavigationButton::PositionType QExtNavigationButton::trianglePosition() const
{
    Q_D(const QExtNavigationButton);
    return d->m_trianglePosition;
}

QColor QExtNavigationButton::triangleColor() const
{
    Q_D(const QExtNavigationButton);
    return d->m_triangleColor;
}

bool QExtNavigationButton::isIconVisible() const
{
    Q_D(const QExtNavigationButton);
    return d->m_iconVisible;
}

QExtNavigationButton::PositionType QExtNavigationButton::iconPosition() const
{
    Q_D(const QExtNavigationButton);
    return d->m_iconPosition;
}

int QExtNavigationButton::iconSpace() const
{
    Q_D(const QExtNavigationButton);
    return d->m_iconSpace;
}

QSize QExtNavigationButton::iconSize() const
{
    Q_D(const QExtNavigationButton);
    return d->m_iconSize;
}

QPixmap QExtNavigationButton::normalIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_normalIcon;
}

QPixmap QExtNavigationButton::hoveredIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_hoverIcon;
}

QPixmap QExtNavigationButton::checkedIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_checkIcon;
}

QChar QExtNavigationButton::normalFontIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_normalFontIcon;
}

QChar QExtNavigationButton::hoveredFontIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_hoverFontIcon;
}

QChar QExtNavigationButton::checkedFontIcon() const
{
    Q_D(const QExtNavigationButton);
    return d->m_checkFontIcon;
}

bool QExtNavigationButton::isLineVisible() const
{
    Q_D(const QExtNavigationButton);
    return d->m_lineVisible;
}

int QExtNavigationButton::lineSpace() const
{
    Q_D(const QExtNavigationButton);
    return d->m_lineSpace;
}

int QExtNavigationButton::lineWidth() const
{
    Q_D(const QExtNavigationButton);
    return d->m_lineWidth;
}

QExtNavigationButton::PositionType QExtNavigationButton::linePosition() const
{
    Q_D(const QExtNavigationButton);
    return d->m_linePosition;
}

QColor QExtNavigationButton::lineColor() const
{
    Q_D(const QExtNavigationButton);
    return d->m_lineColor;
}

QColor QExtNavigationButton::normalBackgroundColor() const
{
    Q_D(const QExtNavigationButton);
    return d->m_normalBackgroundColor;
}

QColor QExtNavigationButton::hoveredBackgroundColor() const
{
    Q_D(const QExtNavigationButton);
    return d->m_hoverBackgroundColor;
}

QColor QExtNavigationButton::checkedBackgroundColor() const
{
    Q_D(const QExtNavigationButton);
    return d->m_checkBackgroundColor;
}

QColor QExtNavigationButton::normalTextColor() const
{
    Q_D(const QExtNavigationButton);
    return d->m_normalTextColor;
}

QColor QExtNavigationButton::hoveredTextColor() const
{
    Q_D(const QExtNavigationButton);
    return d->m_hoverTextColor;
}

QColor QExtNavigationButton::checkedTextColor() const
{
    Q_D(const QExtNavigationButton);
    return d->m_checkTextColor;
}

QSize QExtNavigationButton::sizeHint() const
{
    return QSize(100, 30);
}

QSize QExtNavigationButton::minimumSizeHint() const
{
    return QSize(20, 10);
}

void QExtNavigationButton::setLeftPadding(int padding)
{
    Q_D(QExtNavigationButton);
    if (d->m_leftPadding != padding)
    {
        d->m_leftPadding = padding;
        this->update();
    }
}

void QExtNavigationButton::setRightPadding(int padding)
{
    Q_D(QExtNavigationButton);
    if (d->m_rightPadding != padding)
    {
        d->m_rightPadding = padding;
        this->update();
    }
}

void QExtNavigationButton::setTopPadding(int padding)
{
    Q_D(QExtNavigationButton);
    if (d->m_topPadding != padding)
    {
        d->m_topPadding = padding;
        this->update();
    }
}

void QExtNavigationButton::setBottomPadding(int padding)
{
    Q_D(QExtNavigationButton);
    if (d->m_bottomPadding != padding)
    {
        d->m_bottomPadding = padding;
        this->update();
    }
}

void QExtNavigationButton::setPadding(int padding)
{
    this->setPadding(padding, padding, padding, padding);
}

void QExtNavigationButton::setPadding(int left, int right, int top, int bottom)
{
    Q_D(QExtNavigationButton);
    d->m_leftPadding = left;
    d->m_rightPadding = right;
    d->m_topPadding = top;
    d->m_bottomPadding = bottom;
    this->update();
}

void QExtNavigationButton::setTextAlign(const QExtNavigationButton::TextAlignType &textAlign)
{
    Q_D(QExtNavigationButton);
    if (d->m_textAlign != textAlign)
    {
        d->m_textAlign = textAlign;
        this->update();
    }
}

void QExtNavigationButton::setTriangleVisible(bool visiable)
{
    Q_D(QExtNavigationButton);
    if (d->m_triangleVisible != visiable)
    {
        d->m_triangleVisible = visiable;
        this->update();
    }
}

void QExtNavigationButton::setTriangleLen(int len)
{
    Q_D(QExtNavigationButton);
    if (d->m_triangleLen != len)
    {
        d->m_triangleLen = len;
        this->update();
    }
}

void QExtNavigationButton::setTrianglePosition(const QExtNavigationButton::PositionType &position)
{
    Q_D(QExtNavigationButton);
    if (d->m_trianglePosition != position)
    {
        d->m_trianglePosition = position;
        this->update();
    }
}

void QExtNavigationButton::setTriangleColor(const QColor &color)
{
    Q_D(QExtNavigationButton);
    if (d->m_triangleColor != color)
    {
        d->m_triangleColor = color;
        this->update();
    }
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

void QExtNavigationButton::setIconPosition(const QExtNavigationButton::PositionType &position)
{
    Q_D(QExtNavigationButton);
    if (d->m_iconPosition != position)
    {
        d->m_iconPosition = position;
        this->update();
    }
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

void QExtNavigationButton::setIconSize(const QSize &size)
{
    Q_D(QExtNavigationButton);
    if (d->m_iconSize != size)
    {
        d->m_iconSize = size;
        this->update();
    }
}

void QExtNavigationButton::setIcon(const QPixmap &pixmap)
{
    this->setNormalIcon(pixmap);
    this->setHoverIcon(pixmap);
    this->setCheckIcon(pixmap);
}

void QExtNavigationButton::setNormalIcon(const QPixmap &pixmap)
{
    Q_D(QExtNavigationButton);
    d->m_normalIcon = pixmap;
    this->update();
}

void QExtNavigationButton::setHoverIcon(const QPixmap &pixmap)
{
    Q_D(QExtNavigationButton);
    d->m_hoverIcon = pixmap;
    this->update();
}

void QExtNavigationButton::setCheckIcon(const QPixmap &pixmap)
{
    Q_D(QExtNavigationButton);
    d->m_checkIcon = pixmap;
    this->update();
}

void QExtNavigationButton::setFontIcon(const QChar &icon)
{
    this->setNormalFontIcon(icon);
    this->setHoverFontIcon(icon);
    this->setCheckFontIcon(icon);
}

void QExtNavigationButton::setNormalFontIcon(const QChar &icon)
{
    Q_D(QExtNavigationButton);
    if (icon != d->m_normalFontIcon)
    {
        d->m_normalFontIcon = icon;
        this->update();
    }
}

void QExtNavigationButton::setHoverFontIcon(const QChar &icon)
{
    Q_D(QExtNavigationButton);
    if (icon != d->m_hoverFontIcon)
    {
        d->m_hoverFontIcon = icon;
        this->update();
    }
}

void QExtNavigationButton::setCheckFontIcon(const QChar &icon)
{
    Q_D(QExtNavigationButton);
    if (icon != d->m_checkFontIcon)
    {
        d->m_checkFontIcon = icon;
        this->update();
    }
}

void QExtNavigationButton::setLineVisible(bool visiable)
{
    Q_D(QExtNavigationButton);
    if (d->m_lineVisible != visiable)
    {
        d->m_lineVisible = visiable;
        this->update();
    }
}

void QExtNavigationButton::setLineSpace(int space)
{
    Q_D(QExtNavigationButton);
    if (d->m_lineSpace != space)
    {
        d->m_lineSpace = space;
        this->update();
    }
}

void QExtNavigationButton::setLineWidth(int width)
{
    Q_D(QExtNavigationButton);
    if (d->m_lineWidth != width)
    {
        d->m_lineWidth = width;
        this->update();
    }
}

void QExtNavigationButton::setLinePosition(const QExtNavigationButton::PositionType &position)
{
    Q_D(QExtNavigationButton);
    if (d->m_linePosition != position)
    {
        d->m_linePosition = position;
        this->update();
    }
}

void QExtNavigationButton::setLineColor(const QColor &color)
{
    Q_D(QExtNavigationButton);
    if (d->m_lineColor != color)
    {
        d->m_lineColor = color;
        this->update();
    }
}

void QExtNavigationButton::setNormalBackgroundColor(const QColor &color)
{
    Q_D(QExtNavigationButton);
    if (d->m_normalBackgroundColor != color)
    {
        d->m_normalBackgroundColor = color;
        this->update();
    }
}

void QExtNavigationButton::setHoverBackgroundColor(const QColor &color)
{
    Q_D(QExtNavigationButton);
    if (d->m_hoverBackgroundColor != color)
    {
        d->m_hoverBackgroundColor = color;
        this->update();
    }
}

void QExtNavigationButton::setCheckBackgroundColor(const QColor &color)
{
    Q_D(QExtNavigationButton);
    if (d->m_checkBackgroundColor != color)
    {
        d->m_checkBackgroundColor = color;
        this->update();
    }
}

void QExtNavigationButton::setNormalTextColor(const QColor &color)
{
    Q_D(QExtNavigationButton);
    if (d->m_normalTextColor != color)
    {
        d->m_normalTextColor = color;
        this->update();
    }
}

void QExtNavigationButton::setHoverTextColor(const QColor &color)
{
    Q_D(QExtNavigationButton);
    if (d->m_hoverTextColor != color)
    {
        d->m_hoverTextColor = color;
        this->update();
    }
}

void QExtNavigationButton::setCheckTextColor(const QColor &color)
{
    Q_D(QExtNavigationButton);
    if (d->m_checkTextColor != color)
    {
        d->m_checkTextColor = color;
        this->update();
    }
}

void QExtNavigationButton::setNormalBackgroundBrush(const QBrush &brush)
{
    Q_D(QExtNavigationButton);
    if (d->m_normalBackgroundBrush != brush)
    {
        d->m_normalBackgroundBrush = brush;
        this->update();
    }
}

void QExtNavigationButton::setHoverBackgroundBrush(const QBrush &brush)
{
    Q_D(QExtNavigationButton);
    if (d->m_hoverBackgroundBrush != brush)
    {
        d->m_hoverBackgroundBrush = brush;
        this->update();
    }
}

void QExtNavigationButton::setCheckBackgroundBrush(const QBrush &brush)
{
    Q_D(QExtNavigationButton);
    if (d->m_checkBackgroundBrush != brush)
    {
        d->m_checkBackgroundBrush = brush;
        this->update();
    }
}
