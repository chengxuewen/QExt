#ifndef _QEXTDATETIMETUMBLER_P_H
#define _QEXTDATETIMETUMBLER_P_H

#include <qextWidgetGlobal.h>

class QEXTTumbler;
class QEXTDateTimeTumbler;
class QEXT_WIDGETS_API QEXTDateTimeTumblerPrivate
{
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

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTDateTimeTumblerPrivate)
    QEXT_DECL_PUBLIC(QEXTDateTimeTumbler)
};

#endif // _QEXTDATETIMETUMBLER_P_H
