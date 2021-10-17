#ifndef _QEXTBREATHINGLIGHT_P_H
#define _QEXTBREATHINGLIGHT_P_H

#include <qextWidgetGlobal.h>

#include <qextObject_p.h>

#include <QColor>
#include <QTimer>

class QEXTBreathingLight;
class QEXT_WIDGET_API QEXTBreathingLightPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTBreathingLightPrivate(QEXTBreathingLight *qq);
    ~QEXTBreathingLightPrivate();

    int m_step;                    //颜色透明渐变步长
    int m_interval;                //定时器间隔
    QColor m_backgroundColor;       //背景颜色

    int m_offset;                  //偏移量
    bool m_isAdd;                  //是否增加
    QScopedPointer<QTimer> m_timer;               //绘制定时器


private:
    QEXT_DECL_PUBLIC(QEXTBreathingLight)
    QEXT_DISABLE_COPY_MOVE(QEXTBreathingLightPrivate)
};

#endif // _QEXTBREATHINGLIGHT_P_H
