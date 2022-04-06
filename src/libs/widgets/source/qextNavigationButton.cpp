#include <qextNavigationButton.h>
#include <qextNavigationButton_p.h>

#include <QDebug>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

QEXTNavigationButtonPrivate::QEXTNavigationButtonPrivate(QEXTNavigationButton *q)
    : q_ptr(q)
{
    m_leftPadding = 5;
    m_rightPadding = 5;
    m_topPadding = 5;
    m_bottomPadding = 5;
    m_textAlign = QEXTNavigationButton::TextAlign_Center;

    m_triangleVisible = false;
    m_triangleLen = 5;
    m_trianglePosition = QEXTNavigationButton::Position_Right;
    m_triangleColor = QColor(255, 255, 255);

    m_iconVisible = false;
    m_iconPosition = QEXTNavigationButton::Position_Left;
    m_iconSpace = 10;
    m_iconSize = QSize(16, 16);
    m_normalIcon = QPixmap();
    m_hoverIcon = QPixmap();
    m_checkIcon = QPixmap();

    m_lineVisible = true;
    m_lineSpace = 0;
    m_lineWidth = 5;
    m_linePosition = QEXTNavigationButton::Position_Left;
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

QEXTNavigationButtonPrivate::~QEXTNavigationButtonPrivate()
{

}


QEXTNavigationButton::QEXTNavigationButton(QWidget *parent)
    : QPushButton(parent), dd_ptr(new QEXTNavigationButtonPrivate(this))
{
    this->setCheckable(true);
}

QEXTNavigationButton::~QEXTNavigationButton()
{

}

void QEXTNavigationButton::setIcon(const QIcon &icon)
{
    this->setIcon(icon.pixmap(100, 100));
    QPushButton::setIcon(icon);
}

void QEXTNavigationButton::enterEvent(QEvent *)
{
    Q_D(QEXTNavigationButton);
    d->m_hovered = true;
    this->update();
}

void QEXTNavigationButton::leaveEvent(QEvent *)
{
    Q_D(QEXTNavigationButton);
    d->m_hovered = false;
    this->update();
}

void QEXTNavigationButton::paintEvent(QPaintEvent *)
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

void QEXTNavigationButton::drawBackground(QPainter *painter)
{
    Q_D(QEXTNavigationButton);
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

void QEXTNavigationButton::drawText(QPainter *painter)
{
    Q_D(QEXTNavigationButton);

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

void QEXTNavigationButton::drawIcon(QPainter *painter)
{
    Q_D(QEXTNavigationButton);
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

void QEXTNavigationButton::drawLine(QPainter *painter)
{
    Q_D(QEXTNavigationButton);
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

void QEXTNavigationButton::drawTriangle(QPainter *painter)
{
    Q_D(QEXTNavigationButton);
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

int QEXTNavigationButton::leftPadding() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_leftPadding;
}

int QEXTNavigationButton::rightPadding() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_rightPadding;
}

int QEXTNavigationButton::topPadding() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_topPadding;
}

int QEXTNavigationButton::bottomPadding() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_bottomPadding;
}

QEXTNavigationButton::TextAlignType QEXTNavigationButton::textAlign() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_textAlign;
}

bool QEXTNavigationButton::isTriangleVisible() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_triangleVisible;
}

int QEXTNavigationButton::triangleLen() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_triangleLen;
}

QEXTNavigationButton::PositionType QEXTNavigationButton::trianglePosition() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_trianglePosition;
}

QColor QEXTNavigationButton::triangleColor() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_triangleColor;
}

bool QEXTNavigationButton::isIconVisible() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_iconVisible;
}

QEXTNavigationButton::PositionType QEXTNavigationButton::iconPosition() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_iconPosition;
}

int QEXTNavigationButton::iconSpace() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_iconSpace;
}

QSize QEXTNavigationButton::iconSize() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_iconSize;
}

QPixmap QEXTNavigationButton::normalIcon() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_normalIcon;
}

QPixmap QEXTNavigationButton::hoveredIcon() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_hoverIcon;
}

QPixmap QEXTNavigationButton::checkedIcon() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_checkIcon;
}

QChar QEXTNavigationButton::normalFontIcon() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_normalFontIcon;
}

QChar QEXTNavigationButton::hoveredFontIcon() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_hoverFontIcon;
}

QChar QEXTNavigationButton::checkedFontIcon() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_checkFontIcon;
}

bool QEXTNavigationButton::isLineVisible() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_lineVisible;
}

int QEXTNavigationButton::lineSpace() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_lineSpace;
}

int QEXTNavigationButton::lineWidth() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_lineWidth;
}

QEXTNavigationButton::PositionType QEXTNavigationButton::linePosition() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_linePosition;
}

QColor QEXTNavigationButton::lineColor() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_lineColor;
}

QColor QEXTNavigationButton::normalBackgroundColor() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_normalBackgroundColor;
}

QColor QEXTNavigationButton::hoveredBackgroundColor() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_hoverBackgroundColor;
}

QColor QEXTNavigationButton::checkedBackgroundColor() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_checkBackgroundColor;
}

QColor QEXTNavigationButton::normalTextColor() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_normalTextColor;
}

QColor QEXTNavigationButton::hoveredTextColor() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_hoverTextColor;
}

QColor QEXTNavigationButton::checkedTextColor() const
{
    Q_D(const QEXTNavigationButton);
    return d->m_checkTextColor;
}

QSize QEXTNavigationButton::sizeHint() const
{
    return QSize(100, 30);
}

QSize QEXTNavigationButton::minimumSizeHint() const
{
    return QSize(20, 10);
}

void QEXTNavigationButton::setLeftPadding(int padding)
{
    Q_D(QEXTNavigationButton);
    if (d->m_leftPadding != padding)
    {
        d->m_leftPadding = padding;
        this->update();
    }
}

void QEXTNavigationButton::setRightPadding(int padding)
{
    Q_D(QEXTNavigationButton);
    if (d->m_rightPadding != padding)
    {
        d->m_rightPadding = padding;
        this->update();
    }
}

void QEXTNavigationButton::setTopPadding(int padding)
{
    Q_D(QEXTNavigationButton);
    if (d->m_topPadding != padding)
    {
        d->m_topPadding = padding;
        this->update();
    }
}

void QEXTNavigationButton::setBottomPadding(int padding)
{
    Q_D(QEXTNavigationButton);
    if (d->m_bottomPadding != padding)
    {
        d->m_bottomPadding = padding;
        this->update();
    }
}

void QEXTNavigationButton::setPadding(int padding)
{
    this->setPadding(padding, padding, padding, padding);
}

void QEXTNavigationButton::setPadding(int left, int right, int top, int bottom)
{
    Q_D(QEXTNavigationButton);
    d->m_leftPadding = left;
    d->m_rightPadding = right;
    d->m_topPadding = top;
    d->m_bottomPadding = bottom;
    this->update();
}

void QEXTNavigationButton::setTextAlign(const QEXTNavigationButton::TextAlignType &textAlign)
{
    Q_D(QEXTNavigationButton);
    if (d->m_textAlign != textAlign)
    {
        d->m_textAlign = textAlign;
        this->update();
    }
}

void QEXTNavigationButton::setTriangleVisible(bool visiable)
{
    Q_D(QEXTNavigationButton);
    if (d->m_triangleVisible != visiable)
    {
        d->m_triangleVisible = visiable;
        this->update();
    }
}

void QEXTNavigationButton::setTriangleLen(int len)
{
    Q_D(QEXTNavigationButton);
    if (d->m_triangleLen != len)
    {
        d->m_triangleLen = len;
        this->update();
    }
}

void QEXTNavigationButton::setTrianglePosition(const QEXTNavigationButton::PositionType &position)
{
    Q_D(QEXTNavigationButton);
    if (d->m_trianglePosition != position)
    {
        d->m_trianglePosition = position;
        this->update();
    }
}

void QEXTNavigationButton::setTriangleColor(const QColor &color)
{
    Q_D(QEXTNavigationButton);
    if (d->m_triangleColor != color)
    {
        d->m_triangleColor = color;
        this->update();
    }
}

void QEXTNavigationButton::setIconVisible(bool visiable)
{
    Q_D(QEXTNavigationButton);
    if (d->m_iconVisible != visiable)
    {
        d->m_iconVisible = visiable;
        this->update();
    }
}

void QEXTNavigationButton::setIconPosition(const QEXTNavigationButton::PositionType &position)
{
    Q_D(QEXTNavigationButton);
    if (d->m_iconPosition != position)
    {
        d->m_iconPosition = position;
        this->update();
    }
}

void QEXTNavigationButton::setIconSpace(int space)
{
    Q_D(QEXTNavigationButton);
    if (d->m_iconSpace != space)
    {
        d->m_iconSpace = space;
        this->update();
    }
}

void QEXTNavigationButton::setIconSize(const QSize &size)
{
    Q_D(QEXTNavigationButton);
    if (d->m_iconSize != size)
    {
        d->m_iconSize = size;
        this->update();
    }
}

void QEXTNavigationButton::setIcon(const QPixmap &pixmap)
{
    this->setNormalIcon(pixmap);
    this->setHoverIcon(pixmap);
    this->setCheckIcon(pixmap);
}

void QEXTNavigationButton::setNormalIcon(const QPixmap &pixmap)
{
    Q_D(QEXTNavigationButton);
    d->m_normalIcon = pixmap;
    this->update();
}

void QEXTNavigationButton::setHoverIcon(const QPixmap &pixmap)
{
    Q_D(QEXTNavigationButton);
    d->m_hoverIcon = pixmap;
    this->update();
}

void QEXTNavigationButton::setCheckIcon(const QPixmap &pixmap)
{
    Q_D(QEXTNavigationButton);
    d->m_checkIcon = pixmap;
    this->update();
}

void QEXTNavigationButton::setFontIcon(const QChar &icon)
{
    this->setNormalFontIcon(icon);
    this->setHoverFontIcon(icon);
    this->setCheckFontIcon(icon);
}

void QEXTNavigationButton::setNormalFontIcon(const QChar &icon)
{
    Q_D(QEXTNavigationButton);
    if (icon != d->m_normalFontIcon)
    {
        d->m_normalFontIcon = icon;
        this->update();
    }
}

void QEXTNavigationButton::setHoverFontIcon(const QChar &icon)
{
    Q_D(QEXTNavigationButton);
    if (icon != d->m_hoverFontIcon)
    {
        d->m_hoverFontIcon = icon;
        this->update();
    }
}

void QEXTNavigationButton::setCheckFontIcon(const QChar &icon)
{
    Q_D(QEXTNavigationButton);
    if (icon != d->m_checkFontIcon)
    {
        d->m_checkFontIcon = icon;
        this->update();
    }
}

void QEXTNavigationButton::setLineVisible(bool visiable)
{
    Q_D(QEXTNavigationButton);
    if (d->m_lineVisible != visiable)
    {
        d->m_lineVisible = visiable;
        this->update();
    }
}

void QEXTNavigationButton::setLineSpace(int space)
{
    Q_D(QEXTNavigationButton);
    if (d->m_lineSpace != space)
    {
        d->m_lineSpace = space;
        this->update();
    }
}

void QEXTNavigationButton::setLineWidth(int width)
{
    Q_D(QEXTNavigationButton);
    if (d->m_lineWidth != width)
    {
        d->m_lineWidth = width;
        this->update();
    }
}

void QEXTNavigationButton::setLinePosition(const QEXTNavigationButton::PositionType &position)
{
    Q_D(QEXTNavigationButton);
    if (d->m_linePosition != position)
    {
        d->m_linePosition = position;
        this->update();
    }
}

void QEXTNavigationButton::setLineColor(const QColor &color)
{
    Q_D(QEXTNavigationButton);
    if (d->m_lineColor != color)
    {
        d->m_lineColor = color;
        this->update();
    }
}

void QEXTNavigationButton::setNormalBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationButton);
    if (d->m_normalBackgroundColor != color)
    {
        d->m_normalBackgroundColor = color;
        this->update();
    }
}

void QEXTNavigationButton::setHoverBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationButton);
    if (d->m_hoverBackgroundColor != color)
    {
        d->m_hoverBackgroundColor = color;
        this->update();
    }
}

void QEXTNavigationButton::setCheckBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationButton);
    if (d->m_checkBackgroundColor != color)
    {
        d->m_checkBackgroundColor = color;
        this->update();
    }
}

void QEXTNavigationButton::setNormalTextColor(const QColor &color)
{
    Q_D(QEXTNavigationButton);
    if (d->m_normalTextColor != color)
    {
        d->m_normalTextColor = color;
        this->update();
    }
}

void QEXTNavigationButton::setHoverTextColor(const QColor &color)
{
    Q_D(QEXTNavigationButton);
    if (d->m_hoverTextColor != color)
    {
        d->m_hoverTextColor = color;
        this->update();
    }
}

void QEXTNavigationButton::setCheckTextColor(const QColor &color)
{
    Q_D(QEXTNavigationButton);
    if (d->m_checkTextColor != color)
    {
        d->m_checkTextColor = color;
        this->update();
    }
}

void QEXTNavigationButton::setNormalBackgroundBrush(const QBrush &brush)
{
    Q_D(QEXTNavigationButton);
    if (d->m_normalBackgroundBrush != brush)
    {
        d->m_normalBackgroundBrush = brush;
        this->update();
    }
}

void QEXTNavigationButton::setHoverBackgroundBrush(const QBrush &brush)
{
    Q_D(QEXTNavigationButton);
    if (d->m_hoverBackgroundBrush != brush)
    {
        d->m_hoverBackgroundBrush = brush;
        this->update();
    }
}

void QEXTNavigationButton::setCheckBackgroundBrush(const QBrush &brush)
{
    Q_D(QEXTNavigationButton);
    if (d->m_checkBackgroundBrush != brush)
    {
        d->m_checkBackgroundBrush = brush;
        this->update();
    }
}
