#ifndef QEXTSWITCHBUTTON_P_H
#define QEXTSWITCHBUTTON_P_H

#include <qextWidgetGlobal.h>
#include <qextSwitchButton.h>

#include <qextobject_p.h>

#include <QVariantAnimation>

class QEXTSwitchButton;
class QEXT_WIDGET_API QEXTSwitchButtonPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTSwitchButtonPrivate(QEXTSwitchButton *qq);
    ~QEXTSwitchButtonPrivate();

    int m_space;                      //滑块离背景间隔
    int m_rectRadius;                 //圆角角度
    bool m_checked;                   //是否选中
    bool m_textVisiable;                  //显示文字
    bool m_circleVisiable;                //显示小圆
    bool m_animationEnable;                 //动画过渡

    QEXTSwitchButton::Style m_buttonStyle;        //开关按钮样式

    QColor m_offBackgroundColor;              //关闭时背景颜色
    QColor m_onBackgroundColor;               //打开时背景颜色
    QColor m_offSliderColor;          //关闭时滑块颜色
    QColor m_onSliderColor;           //打开时滑块颜色
    QColor m_offTextColor;            //关闭时文字颜色
    QColor m_onTextColor;             //打开时文字颜色

    QString m_offText;                //关闭时显示的文字
    QString m_onText;                 //打开时显示的文字

    int m_step;                       //每次移动的步长
    int m_startX;                     //滑块开始X轴坐标
    int m_endX;                       //滑块结束X轴坐标
    QScopedPointer<QTimer> m_timer;                  //定时器绘制

private:
    QEXT_DECL_PUBLIC(QEXTSwitchButton)
    QEXT_DISABLE_COPY_MOVE(QEXTSwitchButtonPrivate)
};

#endif // QEXTSWITCHBUTTON_P_H
