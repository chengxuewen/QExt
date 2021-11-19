#ifndef _QEXTTOOLTIP_P_H
#define _QEXTTOOLTIP_P_H

#include <qextWidgetGlobal.h>
#include <qextTooltip.h>

class QEXTTooltip;
class QEXT_WIDGETS_API QEXTTooltipPrivate
{
public:
    explicit QEXTTooltipPrivate(QEXTTooltip *q);
    virtual ~QEXTTooltipPrivate();

    QEXTTooltip * const q_ptr;

    int m_borderRadius;                   //边框圆角角度
    QColor m_backgroundColor;                  //背景色
    QColor m_foregroundColor;                  //前景色

    bool m_arrowVisiable;                     //显示箭头
    int m_arrowSize;                      //箭头大小
    QEXTTooltip::ArrowPositionType m_arrowPosition;        //箭头位置

    bool m_triangleVisiable;                  //显示倒三角
    int m_triangleLen;                    //倒三角边长
    QEXTTooltip::TrianglePositionType m_trianglePosition;  //倒三角位置
    QColor m_triangleColor;               //倒三角颜色

    QRect m_backgroundRect;                       //绘制区域

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTTooltipPrivate)
    Q_DECLARE_PUBLIC(QEXTTooltip)
};

#endif // _QEXTTOOLTIP_P_H
