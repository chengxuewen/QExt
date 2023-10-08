#ifndef _QEXTOVENTIMER_P_H
#define _QEXTOVENTIMER_P_H

#include <qextOvenTimer.h>

#include <QDateTime>

class QEXTOvenTimer;
class QEXT_WIDGETS_API QEXTOvenTimerPrivate
{
public:
    explicit QEXTOvenTimerPrivate(QEXTOvenTimer *q);
    virtual ~QEXTOvenTimerPrivate();

    QEXTOvenTimer * const q_ptr;

    int m_duration;
    QDateTime m_finishTime;

    QTimer *m_updateTimer;
    QTimer *m_finishTimer;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTOvenTimerPrivate)
    QEXT_DECL_PUBLIC(QEXTOvenTimer)
};

#endif // _QEXTOVENTIMER_P_H
