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
#include <qextObject.h>

#include <QSlider>

#ifndef Q_WS_QWS
    #if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
        #include <QtDesigner/QDesignerExportWidget>
    #else
        #include <QtUiPlugin/QDesignerExportWidget>
    #endif
#endif

class QEXTTooltip;
class QEXT_WIDGET_API QEXTSlider : public QSlider
{
    Q_OBJECT
    Q_ENUMS(ArrowStyle)
    Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)
    Q_PROPERTY(int arrowSize READ getArrowSize WRITE setArrowSize)
    Q_PROPERTY(ArrowStyle arrowStyle READ getArrowStyle WRITE setArrowStyle)
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
    Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)

    Q_PROPERTY(int labTipWidth READ getLabTipWidth WRITE setLabTipWidth)
    Q_PROPERTY(int labTipHeight READ getLabTipHeight WRITE setLabTipHeight)
    Q_PROPERTY(QFont labTipFont READ getLabTipFont WRITE setLabTipFont)

    Q_PROPERTY(bool showTime READ getShowTime WRITE setShowTime)
    Q_PROPERTY(bool clickEnable READ getClickEnable WRITE setClickEnable)
    Q_PROPERTY(QString unit READ getUnit WRITE setUnit)

public:
    enum ArrowStyle {
        ArrowStyle_Left = 0,    //向左箭头
        ArrowStyle_Right = 1,   //向右箭头
        ArrowStyle_Top = 2,     //向上箭头
        ArrowStyle_Bottom = 3   //向下箭头
    };

    explicit QEXTSlider(QWidget *parent = 0);
    ~QEXTSlider();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    int borderRadius;               //边框圆角角度
    int arrowSize;                  //箭头大小
    ArrowStyle arrowStyle;          //箭头样式

    QColor background;              //背景色
    QColor foreground;              //前景色

    int labTipWidth;                //气泡提示宽度
    int labTipHeight;               //气泡提示高度
    QFont labTipFont;               //气泡提示字体

    bool showTime;                  //是否显示时间
    bool clickEnable;               //是否单击切换到当前
    QString unit;                   //单位

    QEXTTooltip *labTip;               //气泡提示标签

public:
    int getBorderRadius()           const;
    int getArrowSize()              const;
    ArrowStyle getArrowStyle()      const;

    QColor getBackground()          const;
    QColor getForeground()          const;

    int getLabTipWidth()            const;
    int getLabTipHeight()           const;
    QFont getLabTipFont()           const;

    bool getShowTime()              const;
    bool getClickEnable()           const;
    QString getUnit()               const;

public Q_SLOTS:
    //设置边框圆角角度
    void setBorderRadius(int borderRadius);
    //设置箭头大小
    void setArrowSize(int arrowSize);
    //设置箭头样式
    void setArrowStyle(const ArrowStyle &arrowStyle);

    //设置前景色
    void setBackground(const QColor &background);
    //设置前景色
    void setForeground(const QColor &foreground);

    //设置气泡提示宽度
    void setLabTipWidth(int labTipWidth);
    //设置气泡提示高度
    void setLabTipHeight(int labTipHeight);
    //设置气泡提示字体
    void setLabTipFont(const QFont &labTipFont);

    //设置显示时间
    void setShowTime(bool showTime);
    //设置是否单击切换到当前
    void setClickEnable(bool clickEnable);
    //设置单位字符
    void setUnit(const QString &unit);

Q_SIGNALS:
    void clicked();
};

#endif // _QEXTSLIDER_H
