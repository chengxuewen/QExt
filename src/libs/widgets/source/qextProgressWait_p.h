#ifndef _QEXTPROGRESSWAIT_P_H
#define _QEXTPROGRESSWAIT_P_H

#include <qextProgressWait.h>

class QEXTProgressWait;
class QEXT_WIDGETS_API QEXTProgressWaitPrivate
{
public:
    explicit QEXTProgressWaitPrivate(QEXTProgressWait *q);
    virtual ~QEXTProgressWaitPrivate();

    QEXTProgressWait * const q_ptr;

    bool m_clockWise;
    bool m_showPercent;
    int m_currentValue;
    int m_maxValue;
    int m_interval;

    int m_minRadius;
    int m_maxRadius;
    int m_offsetRadius;
    int m_leftRadius;
    int m_rightRadius;
    bool m_leftIncrease;
    bool m_rightIncrease;

    QEXTProgressWait::Style m_barStyle;
    QColor m_background;
    QColor m_foreground;
    QColor m_textColor;

    QTimer *m_timer;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressWaitPrivate)
    QEXT_DECL_PUBLIC(QEXTProgressWait)
};

#endif // _QEXTPROGRESSWAIT_P_H
