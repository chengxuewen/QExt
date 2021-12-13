#ifndef _QEXTBREATHINGLIGHT_P_H
#define _QEXTBREATHINGLIGHT_P_H

#include <qextWidgetGlobal.h>

#include <QColor>
#include <QTimer>

class QEXTBreathingLight;
class QEXT_WIDGETS_API QEXTBreathingLightPrivate
{
public:
    explicit QEXTBreathingLightPrivate(QEXTBreathingLight *q);
    virtual ~QEXTBreathingLightPrivate();

    QEXTBreathingLight * const q_ptr;

    int m_step;
    int m_interval;
    QColor m_backgroundColor;

    int m_offset;
    bool m_isAdd;
    QScopedPointer<QTimer> m_timer;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTBreathingLightPrivate)
    QEXT_DECL_PUBLIC(QEXTBreathingLight)
};

#endif // _QEXTBREATHINGLIGHT_P_H
