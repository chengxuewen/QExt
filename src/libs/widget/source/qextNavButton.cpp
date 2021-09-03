#pragma execution_character_set("utf-8")

#include <qextNavButton.h>
#include <qextNavButton_p.h>

#include <QDebug>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

QEXTNavButtonPrivate::QEXTNavButtonPrivate(QEXTNavButton *qq)
    : QEXTObjectPrivate(qq)
{
    m_leftPadding = 5;
    m_rightPadding = 5;
    m_topPadding = 5;
    m_bottomPadding = 5;
    m_textAlign = QEXTNavButton::TextAlign_Center;

    m_triangleVisiable = false;
    m_triangleLen = 5;
    m_trianglePosition = QEXTNavButton::Position_Right;
    m_triangleColor = QColor(255, 255, 255);

    m_iconVisiable = false;
    m_iconPosition = QEXTNavButton::Position_Left;
    m_iconSpace = 10;
    m_iconSize = QSize(16, 16);
    m_normalIcon = QPixmap();
    m_hoverIcon = QPixmap();
    m_checkIcon = QPixmap();

    m_lineVisiable = true;
    m_lineSpace = 0;
    m_lineWidth = 5;
    m_linePosition = QEXTNavButton::Position_Left;
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

QEXTNavButtonPrivate::~QEXTNavButtonPrivate()
{

}


QEXTNavButton::QEXTNavButton(QWidget *parent)
    : QPushButton(parent), QEXTObject(*(new QEXTNavButtonPrivate(this)))
{
    this->setCheckable(true);
}

QEXTNavButton::~QEXTNavButton()
{

}

void QEXTNavButton::setIcon(const QIcon &icon)
{
    this->setIcon(icon.pixmap(100, 100));
    QPushButton::setIcon(icon);
}

void QEXTNavButton::enterEvent(QEvent *)
{
    QEXT_DECL_D(QEXTNavButton);
    d->m_hovered = true;
    this->update();
}

void QEXTNavButton::leaveEvent(QEvent *)
{
    QEXT_DECL_D(QEXTNavButton);
    d->m_hovered = false;
    this->update();
}

void QEXTNavButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);
    this->drawText(&painter);
    this->drawIcon(&painter);
    this->drawLine(&painter);
    this->drawTriangle(&painter);

    QStyleOption opt;
    opt.init(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void QEXTNavButton::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTNavButton);
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

    //如果画刷存在则取画刷
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
        //根据当前状态选择对应颜色
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

void QEXTNavButton::drawText(QPainter *painter)
{
    QEXT_DECL_D(QEXTNavButton);

    painter->save();
    int width = this->width();
    int height = this->height();
    painter->setBrush(Qt::NoBrush);

    //根据当前状态选择对应颜色
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

void QEXTNavButton::drawIcon(QPainter *painter)
{
    QEXT_DECL_D(QEXTNavButton);
    if (!d->m_iconVisiable)
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
        //等比例平滑缩放图标
        pix = pix.scaled(d->m_iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
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

void QEXTNavButton::drawLine(QPainter *painter)
{
    QEXT_DECL_D(QEXTNavButton);
    if (!d->m_lineVisiable)
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

    //根据线条位置设置线条坐标
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

void QEXTNavButton::drawTriangle(QPainter *painter)
{
    QEXT_DECL_D(QEXTNavButton);
    if (!d->m_triangleVisiable)
    {
        return;
    }

    //选中或者悬停显示
    if (!d->m_hovered && !isChecked())
    {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_triangleColor);

    //绘制在右侧中间,根据设定的倒三角的边长设定三个点位置
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

int QEXTNavButton::leftPadding() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_leftPadding;
}

int QEXTNavButton::rightPadding() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_rightPadding;
}

int QEXTNavButton::topPadding() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_topPadding;
}

int QEXTNavButton::bottomPadding() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_bottomPadding;
}

QEXTNavButton::TextAlign QEXTNavButton::textAlign() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_textAlign;
}

bool QEXTNavButton::isTriangleVisiable() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_triangleVisiable;
}

int QEXTNavButton::triangleLen() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_triangleLen;
}

QEXTNavButton::Position QEXTNavButton::trianglePosition() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_trianglePosition;
}

QColor QEXTNavButton::triangleColor() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_triangleColor;
}

bool QEXTNavButton::isIconVisiable() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_iconVisiable;
}

QEXTNavButton::Position QEXTNavButton::iconPosition() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_iconPosition;
}

int QEXTNavButton::iconSpace() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_iconSpace;
}

QSize QEXTNavButton::iconSize() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_iconSize;
}

QPixmap QEXTNavButton::normalIcon() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_normalIcon;
}

QPixmap QEXTNavButton::hoveredIcon() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_hoverIcon;
}

QPixmap QEXTNavButton::checkedIcon() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_checkIcon;
}

QChar QEXTNavButton::normalFontIcon() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_normalFontIcon;
}

QChar QEXTNavButton::hoveredFontIcon() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_hoverFontIcon;
}

QChar QEXTNavButton::checkedFontIcon() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_checkFontIcon;
}

bool QEXTNavButton::isLineVisiable() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_lineVisiable;
}

int QEXTNavButton::lineSpace() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_lineSpace;
}

int QEXTNavButton::lineWidth() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_lineWidth;
}

QEXTNavButton::Position QEXTNavButton::linePosition() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_linePosition;
}

QColor QEXTNavButton::lineColor() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_lineColor;
}

QColor QEXTNavButton::normalBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_normalBackgroundColor;
}

QColor QEXTNavButton::hoveredBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_hoverBackgroundColor;
}

QColor QEXTNavButton::checkedBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_checkBackgroundColor;
}

QColor QEXTNavButton::normalTextColor() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_normalTextColor;
}

QColor QEXTNavButton::hoveredTextColor() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_hoverTextColor;
}

QColor QEXTNavButton::checkedTextColor() const
{
    QEXT_DECL_DC(QEXTNavButton);
    return d->m_checkTextColor;
}

QSize QEXTNavButton::sizeHint() const
{
    return QSize(100, 30);
}

QSize QEXTNavButton::minimumSizeHint() const
{
    return QSize(20, 10);
}

void QEXTNavButton::setLeftPadding(int padding)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_leftPadding != padding)
    {
        d->m_leftPadding = padding;
        this->update();
    }
}

void QEXTNavButton::setRightPadding(int padding)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_rightPadding != padding)
    {
        d->m_rightPadding = padding;
        this->update();
    }
}

void QEXTNavButton::setTopPadding(int padding)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_topPadding != padding)
    {
        d->m_topPadding = padding;
        this->update();
    }
}

void QEXTNavButton::setBottomPadding(int padding)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_bottomPadding != padding)
    {
        d->m_bottomPadding = padding;
        this->update();
    }
}

void QEXTNavButton::setPadding(int padding)
{
    this->setPadding(padding, padding, padding, padding);
}

void QEXTNavButton::setPadding(int left, int right, int top, int bottom)
{
    QEXT_DECL_D(QEXTNavButton);
    d->m_leftPadding = left;
    d->m_rightPadding = right;
    d->m_topPadding = top;
    d->m_bottomPadding = bottom;
    this->update();
}

void QEXTNavButton::setTextAlign(const QEXTNavButton::TextAlign &textAlign)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_textAlign != textAlign)
    {
        d->m_textAlign = textAlign;
        this->update();
    }
}

void QEXTNavButton::setTriangleVisiable(bool visiable)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_triangleVisiable != visiable)
    {
        d->m_triangleVisiable = visiable;
        this->update();
    }
}

void QEXTNavButton::setTriangleLen(int len)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_triangleLen != len)
    {
        d->m_triangleLen = len;
        this->update();
    }
}

void QEXTNavButton::setTrianglePosition(const QEXTNavButton::Position &position)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_trianglePosition != position)
    {
        d->m_trianglePosition = position;
        this->update();
    }
}

void QEXTNavButton::setTriangleColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_triangleColor != color)
    {
        d->m_triangleColor = color;
        this->update();
    }
}

void QEXTNavButton::setIconVisiable(bool visiable)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_iconVisiable != visiable)
    {
        d->m_iconVisiable = visiable;
        this->update();
    }
}

void QEXTNavButton::setIconPosition(const QEXTNavButton::Position &position)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_iconPosition != position)
    {
        d->m_iconPosition = position;
        this->update();
    }
}

void QEXTNavButton::setIconSpace(int space)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_iconSpace != space)
    {
        d->m_iconSpace = space;
        this->update();
    }
}

void QEXTNavButton::setIconSize(const QSize &size)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_iconSize != size)
    {
        d->m_iconSize = size;
        this->update();
    }
}

void QEXTNavButton::setIcon(const QPixmap &pixmap)
{
    this->setNormalIcon(pixmap);
    this->setHoverIcon(pixmap);
    this->setCheckIcon(pixmap);
}

void QEXTNavButton::setNormalIcon(const QPixmap &pixmap)
{
    QEXT_DECL_D(QEXTNavButton);
    d->m_normalIcon = pixmap;
    this->update();
}

void QEXTNavButton::setHoverIcon(const QPixmap &pixmap)
{
    QEXT_DECL_D(QEXTNavButton);
    d->m_hoverIcon = pixmap;
    this->update();
}

void QEXTNavButton::setCheckIcon(const QPixmap &pixmap)
{
    QEXT_DECL_D(QEXTNavButton);
    d->m_checkIcon = pixmap;
    this->update();
}

void QEXTNavButton::setFontIcon(const QChar &icon)
{
    this->setNormalFontIcon(icon);
    this->setHoverFontIcon(icon);
    this->setCheckFontIcon(icon);
}

void QEXTNavButton::setNormalFontIcon(const QChar &icon)
{
    QEXT_DECL_D(QEXTNavButton);
    if (icon != d->m_normalFontIcon)
    {
        d->m_normalFontIcon = icon;
        this->update();
    }
}

void QEXTNavButton::setHoverFontIcon(const QChar &icon)
{
    QEXT_DECL_D(QEXTNavButton);
    if (icon != d->m_hoverFontIcon)
    {
        d->m_hoverFontIcon = icon;
        this->update();
    }
}

void QEXTNavButton::setCheckFontIcon(const QChar &icon)
{
    QEXT_DECL_D(QEXTNavButton);
    if (icon != d->m_checkFontIcon)
    {
        d->m_checkFontIcon = icon;
        this->update();
    }
}

void QEXTNavButton::setLineVisiable(bool visiable)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_lineVisiable != visiable)
    {
        d->m_lineVisiable = visiable;
        this->update();
    }
}

void QEXTNavButton::setLineSpace(int space)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_lineSpace != space)
    {
        d->m_lineSpace = space;
        this->update();
    }
}

void QEXTNavButton::setLineWidth(int width)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_lineWidth != width)
    {
        d->m_lineWidth = width;
        this->update();
    }
}

void QEXTNavButton::setLinePosition(const QEXTNavButton::Position &position)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_linePosition != position)
    {
        d->m_linePosition = position;
        this->update();
    }
}

void QEXTNavButton::setLineColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_lineColor != color)
    {
        d->m_lineColor = color;
        this->update();
    }
}

void QEXTNavButton::setNormalBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_normalBackgroundColor != color)
    {
        d->m_normalBackgroundColor = color;
        this->update();
    }
}

void QEXTNavButton::setHoverBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_hoverBackgroundColor != color)
    {
        d->m_hoverBackgroundColor = color;
        this->update();
    }
}

void QEXTNavButton::setCheckBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_checkBackgroundColor != color)
    {
        d->m_checkBackgroundColor = color;
        this->update();
    }
}

void QEXTNavButton::setNormalTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_normalTextColor != color)
    {
        d->m_normalTextColor = color;
        this->update();
    }
}

void QEXTNavButton::setHoverTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_hoverTextColor != color)
    {
        d->m_hoverTextColor = color;
        this->update();
    }
}

void QEXTNavButton::setCheckTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_checkTextColor != color)
    {
        d->m_checkTextColor = color;
        this->update();
    }
}

void QEXTNavButton::setNormalBackgroundBrush(const QBrush &brush)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_normalBackgroundBrush != brush)
    {
        d->m_normalBackgroundBrush = brush;
        this->update();
    }
}

void QEXTNavButton::setHoverBackgroundBrush(const QBrush &brush)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_hoverBackgroundBrush != brush)
    {
        d->m_hoverBackgroundBrush = brush;
        this->update();
    }
}

void QEXTNavButton::setCheckBackgroundBrush(const QBrush &brush)
{
    QEXT_DECL_D(QEXTNavButton);
    if (d->m_checkBackgroundBrush != brush)
    {
        d->m_checkBackgroundBrush = brush;
        this->update();
    }
}
