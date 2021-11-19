#ifndef _QEXTNAVIGATIONBAR_P_H
#define _QEXTNAVIGATIONBAR_P_H

#include <qextWidgetGlobal.h>
#include <qextNavigationBar.h>

class QEXTNavigationBar;
class QEXT_WIDGETS_API QEXTNavigationBarPrivate
{
public:
    explicit QEXTNavigationBarPrivate(QEXTNavigationBar *q);
    virtual ~QEXTNavigationBarPrivate();

    int initStep(int distance);     //计算步长

    QEXTNavigationBar * const q_ptr;

    QColor m_backgroundStartColor;            //导航条主背景渐变开始颜色
    QColor m_backgroundEndColor;              //导航条主背景渐变结束颜色

    QColor m_barStartColor;           //导航条当前条目渐变开始颜色
    QColor m_barEndColor;             //导航条当前条目渐变结束颜色

    QColor m_textNormalColor;         //文字正常颜色
    QColor m_textSelectColor;         //文字选中颜色

    QColor m_oldBackgroundEndColor;          //用于扁平化切换
    QColor m_oldBarEndColor;         //用于扁平化切换

    QString m_items;                  //所有条目文字信息
    int m_currentIndex;               //当前选中条目索引
    QString m_currentItem;            //当前选中条目文字

    int m_backgroundRadius;                   //背景圆角半径
    int m_barRadius;                  //选中条目背景圆角半径
    int m_space;                      //条目元素之间的间距

    int m_lineWidth;                  //线条宽度
    QColor m_lineColor;               //线条颜色

    QEXTNavigationBar::BarStyleType m_barStyle;              //选中元素样式

    bool m_keyMoveEnable;                   //是否支持按键移动
    bool m_horizontal;                //是否横向显示
    bool m_flat;                      //是否扁平化

    //元素集合,成对出现,元素的名字,矩形区域范围
    QVector<QPair<QString, QRectF> > m_listItem;

    QRectF m_barRect;
    QRectF m_targetRect;     //选中区域和目标区域的矩形
    double m_barLen;
    double m_targetLen;       //选中区域和目标区域的长度

    double m_initLen;                 //导航条的长度
    int m_step;                       //每次移动的步长

    bool m_isForward;                 //是否往前移动
    bool m_isVirgin;                  //是否首次处理
    QTimer *m_timer;                  //滑动绘制定时器

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNavigationBarPrivate)
    Q_DECLARE_PUBLIC(QEXTNavigationBar)
};

#endif // _QEXTNAVIGATIONBAR_P_H
