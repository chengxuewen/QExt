#ifndef _QEXTINDICATORLIGHT_P_H
#define _QEXTINDICATORLIGHT_P_H

#include <qextWidgetGlobal.h>
#include <qextIndicatorLight.h>

#include <QColor>
#include <QTimer>

class QEXTIndicatorLight;
class QEXT_WIDGET_API QEXTIndicatorLightPrivate
{
public:
    explicit QEXTIndicatorLightPrivate(QEXTIndicatorLight *q);
    virtual ~QEXTIndicatorLightPrivate();

    QEXTIndicatorLight * const q_ptr;

    QString m_text;                  //文本
    QColor m_lightTextColor;            //文字高亮颜色
    QColor m_normalTextColor;           //文字正常颜色
    QColor m_lightBackgroundColor;      //高亮颜色
    QColor m_normalBackgroundColor;     //正常颜色
    int m_fontPixelSize;               //字体大小

    QColor m_outBorderStartColor;       //外边框渐变开始颜色
    QColor m_outBorderEndColor;         //外边框渐变结束颜色
    QColor m_inBorderStartColor;        //里边框渐变开始颜色
    QColor m_inBorderEndColor;          //里边框渐变结束颜色
    QEXTIndicatorLight::Style m_style;    //风格类型
    QEXTIndicatorLight::Shape m_shape;    //形状类型

    bool m_moveEnable;                 //是否能够移动
    bool m_overlayVisiable;            //是否显示遮罩层
    QColor m_overlayColor;              //遮罩层颜色

    QScopedPointer<QTimer> m_flickerTimer;            //定时器切换颜色
    bool m_lightState;                 //是否亮

private:
    QEXT_DECL_PUBLIC(QEXTIndicatorLight)
    QEXT_DECL_DISABLE_COPY(QEXTIndicatorLightPrivate)
};

#endif // _QEXTINDICATORLIGHT_P_H
