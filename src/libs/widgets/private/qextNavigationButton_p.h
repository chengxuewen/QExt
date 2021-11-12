#ifndef _QEXTNAVIGATIONBUTTON_P_H
#define _QEXTNAVIGATIONBUTTON_P_H

#include <qextWidgetGlobal.h>
#include <qextNavigationButton.h>

class QEXTNavigationButton;
class QEXT_WIDGETS_API QEXTNavigationButtonPrivate
{
public:
    explicit QEXTNavigationButtonPrivate(QEXTNavigationButton *q);
    virtual ~QEXTNavigationButtonPrivate();

    QEXTNavigationButton * const q_ptr;

    int m_leftPadding;     //文字左侧间隔
    int m_rightPadding;    //文字右侧间隔
    int m_topPadding;      //文字顶部间隔
    int m_bottomPadding;   //文字底部间隔
    QEXTNavigationButton::TextAlignType m_textAlign; //文字对齐

    bool m_triangleVisiable;                 //显示倒三角
    QEXTNavigationButton::PositionType m_trianglePosition; //倒三角位置
    int m_triangleLen;                   //倒三角边长
    QColor m_triangleColor;              //倒三角颜色

    bool m_iconVisiable;      //显示图标
    QEXTNavigationButton::PositionType m_iconPosition;
    int m_iconSpace;      //图标间隔
    QSize m_iconSize;     //图标尺寸
    QPixmap m_normalIcon; //正常图标
    QPixmap m_hoverIcon;  //悬停图标
    QPixmap m_checkIcon;  //选中图标
    QChar m_normalFontIcon;
    QChar m_hoverFontIcon;
    QChar m_checkFontIcon;

    bool m_lineVisiable;             //显示线条
    QEXTNavigationButton::PositionType m_linePosition; //线条位置
    int m_lineSpace;             //线条间隔
    int m_lineWidth;             //线条宽度
    QColor m_lineColor;          //线条颜色

    QColor m_normalBackgroundColor;   //正常背景颜色
    QColor m_hoverBackgroundColor;    //悬停背景颜色
    QColor m_checkBackgroundColor;    //选中背景颜色
    QColor m_normalTextColor; //正常文字颜色
    QColor m_hoverTextColor;  //悬停文字颜色
    QColor m_checkTextColor;  //选中文字颜色

    QBrush m_normalBackgroundBrush; //正常背景画刷
    QBrush m_hoverBackgroundBrush;  //悬停背景画刷
    QBrush m_checkBackgroundBrush;  //选中背景画刷

    bool m_hovered; //悬停标志位

private:
    QEXT_DECL_PUBLIC(QEXTNavigationButton)
    QEXT_DECL_DISABLE_COPY(QEXTNavigationButtonPrivate)
};

#endif // _QEXTNAVIGATIONBUTTON_P_H
