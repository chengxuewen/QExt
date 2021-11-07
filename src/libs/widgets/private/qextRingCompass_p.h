#ifndef _QEXTRINGCOMPASSGAUGE_P_H
#define _QEXTRINGCOMPASSGAUGE_P_H

#include <qextWidgetGlobal.h>

#include <QColor>

class QEXTRingCompass;
class QEXT_WIDGETS_API QEXTRingCompassPrivate
{
public:
    explicit QEXTRingCompassPrivate(QEXTRingCompass *q);
    virtual ~QEXTRingCompassPrivate();

    QEXTRingCompass * const q_ptr;

    double m_value;               //当前值
    QColor m_backgroundColor;             //背景颜色
    QColor m_textColor;           //文字颜色
    QColor m_borderColor;         //边框颜色
    int m_borderWidth;            //边框宽度

    QColor m_northDotColor;       //正北点颜色
    QColor m_otherDotColor;       //其它方向点颜色
    QColor m_pointerColor;        //指针颜色

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTRingCompassPrivate)
    QEXT_DECL_PUBLIC(QEXTRingCompass)
};

#endif // _QEXTRINGCOMPASSGAUGE_P_H
