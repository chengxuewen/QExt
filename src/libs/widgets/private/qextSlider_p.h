#ifndef _QEXTSLIDER_P_H
#define _QEXTSLIDER_P_H

#include <qextWidgetGlobal.h>
#include <qextSlider.h>

#include <QColor>

class QEXTTooltip;
class QEXTSlider;
class QEXT_WIDGETS_API QEXTSliderPrivate
{
public:
    explicit QEXTSliderPrivate(QEXTSlider *q);
    virtual ~QEXTSliderPrivate();

    QEXTSlider * const q_ptr;

    int m_borderRadius;               //边框圆角角度
    int m_arrowSize;                  //箭头大小
    QEXTSlider::ArrowStyleType m_arrowStyle;          //箭头样式

    QColor m_backgroundColor;              //背景色
    QColor m_foregroundColor;              //前景色

    int m_tooltipWidth;                //气泡提示宽度
    int m_tooltipHeight;               //气泡提示高度
    QFont m_tooltipFont;               //气泡提示字体

    bool m_timeVisiable;                  //是否显示时间
    bool m_clickEnable;
    QString m_unitText;

    QEXTTooltip *m_tooltip;               //气泡提示标签

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSliderPrivate)
    Q_DECLARE_PUBLIC(QEXTSlider)
};

#endif // _QEXTSLIDER_P_H
