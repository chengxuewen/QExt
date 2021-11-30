#ifndef _QEXTDATETIMETUMBLER_P_H
#define _QEXTDATETIMETUMBLER_P_H

#include <qextWidgetGlobal.h>

class QEXTTumbler;
class QEXTDateTimeTumbler;
class QEXT_WIDGETS_API QEXTDateTimeTumblerPrivate
{
    Q_DISABLE_COPY(QEXTDateTimeTumblerPrivate)
    Q_DECLARE_PUBLIC(QEXTDateTimeTumbler)
public:
    explicit QEXTDateTimeTumblerPrivate(QEXTDateTimeTumbler *q);
    virtual ~QEXTDateTimeTumblerPrivate();

    QEXTDateTimeTumbler * const q_ptr;

    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_min;
    int m_sec;

    QEXTTumbler *m_tumblerYear;
    QEXTTumbler *m_tumblerMonth;
    QEXTTumbler *m_tumblerDay;
    QEXTTumbler *m_tumblerHour;
    QEXTTumbler *m_tumblerMin;
    QEXTTumbler *m_tumblerSec;
};

#endif // _QEXTDATETIMETUMBLER_P_H
