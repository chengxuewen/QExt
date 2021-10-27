#ifndef _QEXTNAVBUTTON_H
#define _QEXTNAVBUTTON_H

/**
 * 导航按钮控件 作者:feiyangqingyun(QQ:517216493) 2017-12-19
 * 1:可设置文字的左侧+右侧+顶部+底部间隔
 * 2:可设置文字对齐方式
 * 3:可设置显示倒三角/倒三角边长/倒三角位置/倒三角颜色
 * 4:可设置显示图标/图标间隔/图标尺寸/正常状态图标/悬停状态图标/选中状态图标
 * 5:可设置显示边框线条/线条宽度/线条间隔/线条位置/线条颜色
 * 6:可设置正常背景颜色/悬停背景颜色/选中背景颜色
 * 7:可设置正常文字颜色/悬停文字颜色/选中文字颜色
 * 8:可设置背景颜色为画刷颜色
 */

#include <qextWidgetGlobal.h>

#include <QPushButton>

class QEXTNavButtonPrivate;
class QEXT_WIDGET_API QEXTNavButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(int leftPadding READ leftPadding WRITE setLeftPadding)
    Q_PROPERTY(int rightPadding READ rightPadding WRITE setRightPadding)
    Q_PROPERTY(int topPadding READ topPadding WRITE setTopPadding)
    Q_PROPERTY(int bottomPadding READ bottomPadding WRITE setBottomPadding)
    Q_PROPERTY(TextAlign textAlign READ textAlign WRITE setTextAlign)

    Q_PROPERTY(bool triangleVisiable READ isTriangleVisiable WRITE setTriangleVisiable)
    Q_PROPERTY(int triangleLen READ triangleLen WRITE setTriangleLen)
    Q_PROPERTY(Position trianglePosition READ trianglePosition WRITE setTrianglePosition)
    Q_PROPERTY(QColor triangleColor READ triangleColor WRITE setTriangleColor)

    Q_PROPERTY(bool iconVisiable READ isIconVisiable WRITE setIconVisiable)
    Q_PROPERTY(int iconSpace READ iconSpace WRITE setIconSpace)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(QPixmap normalIcon READ normalIcon WRITE setNormalIcon)
    Q_PROPERTY(QPixmap hoveredIcon READ hoveredIcon WRITE setHoverIcon)
    Q_PROPERTY(QPixmap checkedIcon READ checkedIcon WRITE setCheckIcon)
    Q_PROPERTY(QChar normalFontIcon READ normalFontIcon WRITE setNormalFontIcon)
    Q_PROPERTY(QChar hoveredFontIcon READ hoveredFontIcon WRITE setHoverFontIcon)
    Q_PROPERTY(QChar checkedFontIcon READ checkedFontIcon WRITE setCheckFontIcon)

    Q_PROPERTY(bool lineVisiable READ isLineVisiable WRITE setLineVisiable)
    Q_PROPERTY(int lineSpace READ lineSpace WRITE setLineSpace)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(Position linePosition READ linePosition WRITE setLinePosition)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)

    Q_PROPERTY(QColor normalBackgroundColor READ normalBackgroundColor WRITE setNormalBackgroundColor)
    Q_PROPERTY(QColor hoveredBackgroundColor READ hoveredBackgroundColor WRITE setHoverBackgroundColor)
    Q_PROPERTY(QColor checkedBackgroundColor READ checkedBackgroundColor WRITE setCheckBackgroundColor)
    Q_PROPERTY(QColor normalTextColor READ normalTextColor WRITE setNormalTextColor)
    Q_PROPERTY(QColor hoveredTextColor READ hoveredTextColor WRITE setHoverTextColor)
    Q_PROPERTY(QColor checkedTextColor READ checkedTextColor WRITE setCheckTextColor)

public:
    enum TextAlign
    {
        TextAlign_Left = Qt::AlignLeft,   //左侧对齐
        TextAlign_Right = Qt::AlignRight,  //右侧对齐
        TextAlign_Top = Qt::AlignTop,    //顶部对齐
        TextAlign_Bottom = Qt::AlignBottom, //底部对齐
        TextAlign_Center = Qt::AlignCenter  //居中对齐
    };
    Q_ENUMS(TextAlign)

    enum Position
    {
        Position_Left = 0,  //左侧
        Position_Right = 1, //右侧
        Position_Top = 2,   //顶部
        Position_Bottom = 3 //底部
    };
    Q_ENUMS(Position)

    explicit QEXTNavButton(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavButton();

    void setIcon(const QIcon &icon);

    int leftPadding() const;
    int rightPadding() const;
    int topPadding() const;
    int bottomPadding() const;
    TextAlign textAlign() const;

    bool isTriangleVisiable() const;
    Position trianglePosition() const;
    int triangleLen() const;
    QColor triangleColor() const;

    bool isIconVisiable() const;
    Position iconPosition() const;
    int iconSpace() const;
    QSize iconSize() const;
    QPixmap normalIcon() const;
    QPixmap hoveredIcon() const;
    QPixmap checkedIcon() const;
    QChar normalFontIcon() const;
    QChar hoveredFontIcon() const;
    QChar checkedFontIcon() const;

    bool isLineVisiable() const;
    Position linePosition() const;
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

    void setTextAlign(const TextAlign &textAlign);

    void setTriangleVisiable(bool visiable);
    void setTrianglePosition(const Position &position);
    void setTriangleLen(int len);
    void setTriangleColor(const QColor &color);

    void setIconVisiable(bool visiable);
    void setIconPosition(const Position &position);
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

    void setLineVisiable(bool visiable);
    void setLinePosition(const Position &position);
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

    QScopedPointer<QEXTNavButtonPrivate> d_ptr;

private:
    QEXT_DECL_PRIVATE(QEXTNavButton)
    QEXT_DISABLE_COPY_MOVE(QEXTNavButton)
};

#endif // _QEXTNAVBUTTON_H
