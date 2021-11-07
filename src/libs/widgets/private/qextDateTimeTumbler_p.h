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

    int m_year;               //年份
    int m_month;              //月份
    int m_day;                //日期
    int m_hour;               //时钟
    int m_min;                //分钟
    int m_sec;                //秒钟

    QEXTTumbler *m_tumblerYear;   //年份选择器
    QEXTTumbler *m_tumblerMonth;  //月份选择器
    QEXTTumbler *m_tumblerDay;    //日期选择器
    QEXTTumbler *m_tumblerHour;   //时钟选择器
    QEXTTumbler *m_tumblerMin;    //分钟选择器
    QEXTTumbler *m_tumblerSec;    //秒钟选择器

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTDateTimeTumblerPrivate)
    QEXT_DECL_PUBLIC(QEXTDateTimeTumbler)
};

#endif // _QEXTDATETIMETUMBLER_P_H
