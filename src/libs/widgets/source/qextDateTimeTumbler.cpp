#pragma execution_character_set("utf-8")

#include <qextDateTimeTumbler.h>
#include <qextDateTimeTumbler_p.h>
#include <qextTumbler.h>

#include <QBoxLayout>
#include <QDebug>


QEXTDateTimeTumblerPrivate::QEXTDateTimeTumblerPrivate(QEXTDateTimeTumbler *q)
    : q_ptr(q)
    , m_year(0)
    , m_month(0)
    , m_day(0)
    , m_hour(0)
    , m_min(0)
    , m_sec(0)
    , m_tumblerYear(QEXT_DECL_NULLPTR)
    , m_tumblerMonth(QEXT_DECL_NULLPTR)
    , m_tumblerDay(QEXT_DECL_NULLPTR)
    , m_tumblerHour(QEXT_DECL_NULLPTR)
    , m_tumblerMin(QEXT_DECL_NULLPTR)
    , m_tumblerSec(QEXT_DECL_NULLPTR)
{

}

QEXTDateTimeTumblerPrivate::~QEXTDateTimeTumblerPrivate()
{

}



QEXTDateTimeTumbler::QEXTDateTimeTumbler(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTDateTimeTumblerPrivate(this))
{
    this->initForm();
}

QEXTDateTimeTumbler::~QEXTDateTimeTumbler()
{

}

void QEXTDateTimeTumbler::initForm()
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    //年份选择器
    d->m_tumblerYear = new QEXTTumbler(this);
    QStringList listYear;
    for (int i = 2015; i <= 2030; i++) {
        listYear << QString("%1").arg(i);
    }
    d->m_tumblerYear->setValueList(listYear);

    //月份选择器
    d->m_tumblerMonth = new QEXTTumbler(this);
    QStringList listMonth;
    for (int i = 1; i <= 12; i++) {
        listMonth << QString("%1 月").arg(i);
    }
    d->m_tumblerMonth->setValueList(listMonth);

    //日期选择器
    d->m_tumblerDay = new QEXTTumbler(this);
    QStringList listDay;
    for (int i = 1; i <= 31; i++) {
        listDay << QString("%1").arg(i);
    }
    d->m_tumblerDay->setValueList(listDay);

    //年月日联动
    connect(d->m_tumblerYear, SIGNAL(currentValueChanged(QString)), this, SLOT(currentValueChanged(QString)));
    connect(d->m_tumblerMonth, SIGNAL(currentValueChanged(QString)), this, SLOT(currentValueChanged(QString)));

    //时钟选择器
    d->m_tumblerHour = new QEXTTumbler(this);
    QStringList listHour;
    for (int i = 0; i <= 23; i++) {
        listHour << QString("%1").arg(i);
    }
    d->m_tumblerHour->setValueList(listHour);

    //分钟选择器
    d->m_tumblerMin = new QEXTTumbler(this);
    QStringList listMin;
    for (int i = 0; i <= 59; i++) {
        listMin << QString("%1").arg(i);
    }
    d->m_tumblerMin->setValueList(listMin);

    //秒钟选择器
    d->m_tumblerSec = new QEXTTumbler(this);
    QStringList listSec;
    for (int i = 0; i <= 59; i++) {
        listSec << QString("%1").arg(i);
    }
    d->m_tumblerSec->setValueList(listSec);

    //将选择器添加到布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(d->m_tumblerYear);
    layout->addWidget(d->m_tumblerMonth);
    layout->addWidget(d->m_tumblerDay);
    layout->addWidget(d->m_tumblerHour);
    layout->addWidget(d->m_tumblerMin);
    layout->addWidget(d->m_tumblerSec);
}

void QEXTDateTimeTumbler::currentValueChanged(const QString &)
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    int month = d->m_tumblerMonth->currentValue().left(2).toInt();

    //记住之前的日期
    int day = d->m_tumblerDay->currentValue().left(2).toInt();

    //计算该月最大日期
    int maxDay = 30;
    if (month == 2) {
        //平年28天 闰年29天
        int year = d->m_tumblerYear->currentValue().left(4).toInt();
        bool isLoopYear = (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
        if (isLoopYear) {
            maxDay = 29;
        } else {
            maxDay = 28;
        }
    } else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        maxDay = 31;
    }

    QStringList listDay;
    for (int i = 1; i <= maxDay; i++) {
        listDay << QString("%1").arg(i);
    }

    d->m_tumblerDay->setValueList(listDay);

    //如果上次的日期大于最大的日期则设置为最大的日期
    if (day > maxDay) {
        d->m_tumblerDay->setCurrentIndex(maxDay - 1);
    } else {
        d->m_tumblerDay->setCurrentIndex(day - 1);
    }
}

int QEXTDateTimeTumbler::year() const
{
    QEXT_DECL_DC(QEXTDateTimeTumbler);
    return d->m_tumblerYear->currentValue().toInt();
}

int QEXTDateTimeTumbler::month() const
{
    QEXT_DECL_DC(QEXTDateTimeTumbler);
    return d->m_tumblerMonth->currentValue().left(2).toInt();
}

int QEXTDateTimeTumbler::day() const
{
    QEXT_DECL_DC(QEXTDateTimeTumbler);
    return d->m_tumblerDay->currentValue().toInt();
}

int QEXTDateTimeTumbler::hour() const
{
    QEXT_DECL_DC(QEXTDateTimeTumbler);
    return d->m_tumblerHour->currentValue().toInt();
}

int QEXTDateTimeTumbler::min() const
{
    QEXT_DECL_DC(QEXTDateTimeTumbler);
    return d->m_tumblerMin->currentValue().toInt();
}

int QEXTDateTimeTumbler::sec() const
{
    QEXT_DECL_DC(QEXTDateTimeTumbler);
    return d->m_tumblerSec->currentValue().toInt();
}

void QEXTDateTimeTumbler::setYear(int year)
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    d->m_tumblerYear->setCurrentValue(QString("%1").arg(year));
}

void QEXTDateTimeTumbler::setMonth(int month)
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    d->m_tumblerMonth->setCurrentValue(QString("%1 月").arg(month));
}

void QEXTDateTimeTumbler::setDay(int day)
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    d->m_tumblerDay->setCurrentValue(QString("%1").arg(day));
}

void QEXTDateTimeTumbler::setHour(int hour)
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    d->m_tumblerHour->setCurrentValue(QString("%1").arg(hour));
}

void QEXTDateTimeTumbler::setMin(int min)
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    d->m_tumblerMin->setCurrentValue(QString("%1").arg(min));
}

void QEXTDateTimeTumbler::setSec(int sec)
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    d->m_tumblerSec->setCurrentValue(QString("%1").arg(sec));
}

void QEXTDateTimeTumbler::setDateTime(int year, int month, int day, int hour, int min, int sec)
{
    QEXT_DECL_D(QEXTDateTimeTumbler);
    this->setYear(year);
    this->setMonth(month);
    this->setDay(day);
    this->setHour(hour);
    this->setMin(min);
    this->setSec(sec);
}
