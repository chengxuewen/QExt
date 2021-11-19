#ifndef _QEXTSLIDER_H
#define _QEXTSLIDER_H

/***************************************************************************************************
 *@Brief:提示滑块条
 *  1.可设置气泡跟随提示
 *  2.可设置气泡的圆角角度/箭头大小/背景色/前景色/箭头方向
 *  3.可设置是否单击切换到当前
 *  4.可设置气泡宽度/高度/字体
 *  5.可设置是否换算成时间显示
 *  6.支持横向和纵向
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com，基于刘典武-feiyangqingyun（QQ:517216493）代码。
 *@Date:2017-08-30
 *@History:
 *  Modification data:2021-10-17
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QSlider>

class QEXTTooltip;
class QEXTSliderPrivate;
class QEXT_WIDGETS_API QEXTSlider : public QSlider
{
    Q_OBJECT
    Q_ENUMS(ArrowStyleType)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(int arrowSize READ arrowSize WRITE setArrowSize)
    Q_PROPERTY(ArrowStyleType arrowStyle READ arrowStyle WRITE setArrowStyle)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)

    Q_PROPERTY(int toolTipWidth READ toolTipWidth WRITE setToolTipWidth)
    Q_PROPERTY(int toolTipHeight READ toolTipHeight WRITE setToolTipHeight)
    Q_PROPERTY(QFont toolTipFont READ toolTipFont WRITE setToolTipFont)

    Q_PROPERTY(bool timeVisiable READ timeVisiable WRITE setTimeVisiable)
    Q_PROPERTY(bool clickEnable READ clickEnable WRITE setClickEnable)
    Q_PROPERTY(QString unitText READ unitText WRITE setUnitText)

public:
    enum ArrowStyleType
    {
        ArrowStyle_Left = 0,    //向左箭头
        ArrowStyle_Right = 1,   //向右箭头
        ArrowStyle_Top = 2,     //向上箭头
        ArrowStyle_Bottom = 3   //向下箭头
    };

    explicit QEXTSlider(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTSlider();

    int borderRadius() const;
    int arrowSize() const;
    ArrowStyleType arrowStyle() const;

    QColor backgroundColor() const;
    QColor foregroundColor() const;

    int toolTipWidth() const;
    int toolTipHeight() const;
    QFont toolTipFont() const;

    bool timeVisiable() const;
    bool clickEnable() const;
    QString unitText() const;

    QEXTTooltip *tooltip() const;

public Q_SLOTS:
    //设置边框圆角角度
    void setBorderRadius(int radius);
    //设置箭头大小
    void setArrowSize(int size);
    //设置箭头样式
    void setArrowStyle(const ArrowStyleType &style);

    //设置前景色
    void setBackgroundColor(const QColor &color);
    //设置前景色
    void setForegroundColor(const QColor &color);

    //设置气泡提示宽度
    void setToolTipWidth(int width);
    //设置气泡提示高度
    void setToolTipHeight(int height);
    //设置气泡提示字体
    void setToolTipFont(const QFont &font);

    //设置显示时间
    void setTimeVisiable(bool visiable);
    //设置是否单击切换到当前
    void setClickEnable(bool enable);
    //设置单位字符
    void setUnitText(const QString &unit);

Q_SIGNALS:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    QScopedPointer<QEXTSliderPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSlider)
    Q_DECLARE_PRIVATE(QEXTSlider)
};

#endif // _QEXTSLIDER_H
