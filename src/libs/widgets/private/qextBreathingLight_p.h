#ifndef _QEXTBREATHINGLIGHT_P_H
#define _QEXTBREATHINGLIGHT_P_H

#include <qextWidgetGlobal.h>

#include <QColor>
#include <QTimer>

class QEXTBreathingLight;
class QEXT_WIDGETS_API QEXTBreathingLightPrivate
{
    Q_DECLARE_PUBLIC(QEXTBreathingLight)
    Q_DISABLE_COPY(QEXTBreathingLightPrivate)
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
};

#endif // _QEXTBREATHINGLIGHT_P_H
