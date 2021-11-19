#ifndef _QEXTTOOLTIP_H
#define _QEXTTOOLTIP_H

/***************************************************************************************************
 *@Brief:工具提示标签控件
 *  1.可设置前景色和背景色
 *  2.可设置箭头位置方向 左右上下
 *  3.可设置箭头大小
 *  4.可设置显示倒三角
 *  5.可设置倒三角长度/位置/颜色
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武（QQ:517216493）代码。
 *@Date:2016-11-28
 *@History:
 *  Modification data:2021-10-17
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QLabel>

class QEXTTooltipPrivate;
class QEXT_WIDGETS_API QEXTTooltip : public QLabel
{
    Q_OBJECT
    Q_ENUMS(ArrowPositionType)
    Q_ENUMS(TrianglePositionType)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)

    Q_PROPERTY(bool arrowVisiable READ arrowVisiable WRITE setArrowVisiable)
    Q_PROPERTY(int arrowSize READ arrowSize WRITE setArrowSize)
    Q_PROPERTY(ArrowPositionType arrowPosition READ arrowPosition WRITE setArrowPosition)

    Q_PROPERTY(bool triangleVisiable READ triangleVisiable WRITE setTriangleVisiable)
    Q_PROPERTY(int triangleLen READ triangleLen WRITE setTriangleLen)
    Q_PROPERTY(TrianglePositionType trianglePosition READ trianglePosition WRITE setTrianglePosition)
    Q_PROPERTY(QColor triangleColor READ triangleColor WRITE setTriangleColor)

public:
    enum ArrowPositionType
    {
        ArrowPosition_Left = 0,     //向左箭头
        ArrowPosition_Right = 1,    //向右箭头
        ArrowPosition_Top = 2,      //向上箭头
        ArrowPosition_Bottom = 3    //向下箭头
    };

    enum TrianglePositionType
    {
        TrianglePosition_Left = 0,  //左侧
        TrianglePosition_Right = 1, //右侧
        TrianglePosition_Top = 2,   //顶部
        TrianglePosition_Bottom = 3 //底部
    };

    explicit QEXTTooltip(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTTooltip();

    int borderRadius() const;
    QColor backgroundColor() const;
    QColor foregroundColor() const;

    bool arrowVisiable() const;
    int arrowSize() const;
    ArrowPositionType arrowPosition() const;

    bool triangleVisiable() const;
    int triangleLen() const;
    TrianglePositionType trianglePosition() const;
    QColor triangleColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    //设置边框圆角角度
    void setBorderRadius(int radius);
    //设置前景色
    void setBackgroundColor(const QColor &color);
    //设置前景色
    void setForegroundColor(const QColor &color);

    //设置显示箭头
    void setArrowVisiable(bool visiable);
    //设置箭头大小
    void setArrowSize(int size);
    //设置箭头位置
    void setArrowPosition(const ArrowPositionType &position);

    //设置显示倒三角
    void setTriangleVisiable(bool visiable);
    //设置倒三角边长
    void setTriangleLen(int len);
    //设置倒三角位置
    void setTrianglePosition(const TrianglePositionType &position);
    //设置倒三角颜色
    void setTriangleColor(const QColor &color);

Q_SIGNALS:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawText(QPainter *painter);
    void drawTriangle(QPainter *painter);

    QScopedPointer<QEXTTooltipPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTTooltip)
    Q_DECLARE_PRIVATE(QEXTTooltip)
};

#endif // _QEXTTOOLTIP_H
