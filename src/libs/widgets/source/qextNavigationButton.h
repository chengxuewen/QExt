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

#ifndef _QEXTNAVIGATIONBUTTON_H
#define _QEXTNAVIGATIONBUTTON_H

#include <qextWidgetGlobal.h>

#include <QPushButton>

class QExtNavigationButtonPrivate;
class QEXT_WIDGETS_API QExtNavigationButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(int leftPadding READ leftPadding WRITE setLeftPadding)
    Q_PROPERTY(int rightPadding READ rightPadding WRITE setRightPadding)
    Q_PROPERTY(int topPadding READ topPadding WRITE setTopPadding)
    Q_PROPERTY(int bottomPadding READ bottomPadding WRITE setBottomPadding)
    Q_PROPERTY(TextAlignType textAlign READ textAlign WRITE setTextAlign)

    Q_PROPERTY(bool triangleVisible READ isTriangleVisible WRITE setTriangleVisible)
    Q_PROPERTY(int triangleLen READ triangleLen WRITE setTriangleLen)
    Q_PROPERTY(PositionType trianglePosition READ trianglePosition WRITE setTrianglePosition)
    Q_PROPERTY(QColor triangleColor READ triangleColor WRITE setTriangleColor)

    Q_PROPERTY(bool iconVisible READ isIconVisible WRITE setIconVisible)
    Q_PROPERTY(int iconSpace READ iconSpace WRITE setIconSpace)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QPixmap normalIcon READ normalIcon WRITE setNormalIcon)
    Q_PROPERTY(QPixmap hoveredIcon READ hoveredIcon WRITE setHoverIcon)
    Q_PROPERTY(QPixmap checkedIcon READ checkedIcon WRITE setCheckIcon)
    Q_PROPERTY(QChar normalFontIcon READ normalFontIcon WRITE setNormalFontIcon)
    Q_PROPERTY(QChar hoveredFontIcon READ hoveredFontIcon WRITE setHoverFontIcon)
    Q_PROPERTY(QChar checkedFontIcon READ checkedFontIcon WRITE setCheckFontIcon)

    Q_PROPERTY(bool lineVisible READ isLineVisible WRITE setLineVisible)
    Q_PROPERTY(int lineSpace READ lineSpace WRITE setLineSpace)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(PositionType linePosition READ linePosition WRITE setLinePosition)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)

    Q_PROPERTY(QColor normalBackgroundColor READ normalBackgroundColor WRITE setNormalBackgroundColor)
    Q_PROPERTY(QColor hoveredBackgroundColor READ hoveredBackgroundColor WRITE setHoverBackgroundColor)
    Q_PROPERTY(QColor checkedBackgroundColor READ checkedBackgroundColor WRITE setCheckBackgroundColor)
    Q_PROPERTY(QColor normalTextColor READ normalTextColor WRITE setNormalTextColor)
    Q_PROPERTY(QColor hoveredTextColor READ hoveredTextColor WRITE setHoverTextColor)
    Q_PROPERTY(QColor checkedTextColor READ checkedTextColor WRITE setCheckTextColor)

public:
    enum TextAlignType
    {
        TextAlign_Left = Qt::AlignLeft,
        TextAlign_Right = Qt::AlignRight,
        TextAlign_Top = Qt::AlignTop,
        TextAlign_Bottom = Qt::AlignBottom,
        TextAlign_Center = Qt::AlignCenter
    };
    Q_ENUMS(TextAlignType)

    enum PositionType
    {
        Position_Left = 0,
        Position_Right = 1,
        Position_Top = 2,
        Position_Bottom = 3
    };
    Q_ENUMS(PositionType)

    explicit QExtNavigationButton(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QExtNavigationButton();

    void setIcon(const QIcon &icon);

    int leftPadding() const;
    int rightPadding() const;
    int topPadding() const;
    int bottomPadding() const;
    TextAlignType textAlign() const;

    bool isTriangleVisible() const;
    PositionType trianglePosition() const;
    int triangleLen() const;
    QColor triangleColor() const;

    bool isIconVisible() const;
    PositionType iconPosition() const;
    int iconSpace() const;
    QSize iconSize() const;
    QPixmap normalIcon() const;
    QPixmap hoveredIcon() const;
    QPixmap checkedIcon() const;
    QChar normalFontIcon() const;
    QChar hoveredFontIcon() const;
    QChar checkedFontIcon() const;

    bool isLineVisible() const;
    PositionType linePosition() const;
    int lineSpace() const;
    int lineWidth() const;
    QColor lineColor() const;

    QColor normalBackgroundColor() const;
    QColor hoveredBackgroundColor() const;
    QColor checkedBackgroundColor() const;
    QColor normalTextColor() const;
    QColor hoveredTextColor() const;
    QColor checkedTextColor() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    void setLeftPadding(int padding);
    void setRightPadding(int padding);
    void setTopPadding(int padding);
    void setBottomPadding(int padding);
    void setPadding(int padding);
    void setPadding(int left, int right, int top, int bottom);

    void setTextAlign(const TextAlignType &textAlign);

    void setTriangleVisible(bool visiable);
    void setTrianglePosition(const PositionType &position);
    void setTriangleLen(int len);
    void setTriangleColor(const QColor &color);

    void setIconVisible(bool visiable);
    void setIconPosition(const PositionType &position);
    void setIconSpace(int space);
    void setIconSize(const QSize &size);
    void setIcon(const QPixmap &pixmap);
    void setNormalIcon(const QPixmap &pixmap);
    void setHoverIcon(const QPixmap &pixmap);
    void setCheckIcon(const QPixmap &pixmap);
    void setFontIcon(const QChar &icon);
    void setNormalFontIcon(const QChar &icon);
    void setHoverFontIcon(const QChar &icon);
    void setCheckFontIcon(const QChar &icon);

    void setLineVisible(bool visiable);
    void setLinePosition(const PositionType &position);
    void setLineSpace(int space);
    void setLineWidth(int width);
    void setLineColor(const QColor &color);

    void setNormalBackgroundColor(const QColor &color);
    void setHoverBackgroundColor(const QColor &color);
    void setCheckBackgroundColor(const QColor &color);

    void setNormalTextColor(const QColor &color);
    void setHoverTextColor(const QColor &color);
    void setCheckTextColor(const QColor &color);

    void setNormalBackgroundBrush(const QBrush &brush);
    void setHoverBackgroundBrush(const QBrush &brush);
    void setCheckBackgroundBrush(const QBrush &brush);

protected:
    void enterEvent(QEvent *) QEXT_DECL_OVERRIDE;
    void leaveEvent(QEvent *) QEXT_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    void drawBackground(QPainter *painter);
    void drawText(QPainter *painter);
    void drawIcon(QPainter *painter);
    void drawLine(QPainter *painter);
    void drawTriangle(QPainter *painter);

    QScopedPointer<QExtNavigationButtonPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtNavigationButton)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtNavigationButton)
};

#endif // _QEXTNAVIGATIONBUTTON_H
