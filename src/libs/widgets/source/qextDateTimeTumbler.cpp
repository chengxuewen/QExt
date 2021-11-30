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
    : QWidget(parent), dd_ptr(new QEXTDateTimeTumblerPrivate(this))
{
    this->initForm();
}

QEXTDateTimeTumbler::~QEXTDateTimeTumbler()
{

}

void QEXTDateTimeTumbler::initForm()
{
    Q_D(QEXTDateTimeTumbler);

    d->m_tumblerYear = new QEXTTumbler(this);
    QStringList listYear;
    for (int i = 2015; i <= 2030; i++) {
        listYear << QString("%1").arg(i);
    }
    d->m_tumblerYear->setValueList(listYear);

    d->m_tumblerMonth = new QEXTTumbler(this);
    QStringList listMonth;
    for (int i = 1; i <= 12; i++) {
        listMonth << QString("%1 月").arg(i);
    }
    d->m_tumblerMonth->setValueList(listMonth);

    d->m_tumblerDay = new QEXTTumbler(this);
    QStringList listDay;
    for (int i = 1; i <= 31; i++) {
        listDay << QString("%1").arg(i);
    }
    d->m_tumblerDay->setValueList(listDay);

    connect(d->m_tumblerYear, SIGNAL(currentValueChanged(QString)), this, SLOT(currentValueChanged(QString)));
    connect(d->m_tumblerMonth, SIGNAL(currentValueChanged(QString)), this, SLOT(currentValueChanged(QString)));

    d->m_tumblerHour = new QEXTTumbler(this);
    QStringList listHour;
    for (int i = 0; i <= 23; i++) {
        listHour << QString("%1").arg(i);
    }
    d->m_tumblerHour->setValueList(listHour);

    d->m_tumblerMin = new QEXTTumbler(this);
    QStringList listMin;
    for (int i = 0; i <= 59; i++) {
        listMin << QString("%1").arg(i);
    }
    d->m_tumblerMin->setValueList(listMin);

    d->m_tumblerSec = new QEXTTumbler(this);
    QStringList listSec;
    for (int i = 0; i <= 59; i++) {
        listSec << QString("%1").arg(i);
    }
    d->m_tumblerSec->setValueList(listSec);

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
    Q_D(QEXTDateTimeTumbler);
    int month = d->m_tumblerMonth->currentValue().left(2).toInt();

    //Remember the previous date
    int day = d->m_tumblerDay->currentValue().left(2).toInt();

    //Calculates the maximum date of the month
    int maxDay = 30;
    if (month == 2) {
        //Common year 28 days leap year 29 days
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

    //Set to the maximum date if the last date is greater than the maximum date
    if (day > maxDay) {
        d->m_tumblerDay->setCurrentIndex(maxDay - 1);
    } else {
        d->m_tumblerDay->setCurrentIndex(day - 1);
    }
}

int QEXTDateTimeTumbler::year() const
{
    Q_D(const QEXTDateTimeTumbler);
    return d->m_tumblerYear->currentValue().toInt();
}

int QEXTDateTimeTumbler::month() const
{
    Q_D(const QEXTDateTimeTumbler);
    return d->m_tumblerMonth->currentValue().left(2).toInt();
}

int QEXTDateTimeTumbler::day() const
{
    Q_D(const QEXTDateTimeTumbler);
    return d->m_tumblerDay->currentValue().toInt();
}

int QEXTDateTimeTumbler::hour() const
{
    Q_D(const QEXTDateTimeTumbler);
    return d->m_tumblerHour->currentValue().toInt();
}

int QEXTDateTimeTumbler::min() const
{
    Q_D(const QEXTDateTimeTumbler);
    return d->m_tumblerMin->currentValue().toInt();
}

int QEXTDateTimeTumbler::sec() const
{
    Q_D(const QEXTDateTimeTumbler);
    return d->m_tumblerSec->currentValue().toInt();
}

void QEXTDateTimeTumbler::setYear(int year)
{
    Q_D(QEXTDateTimeTumbler);
    d->m_tumblerYear->setCurrentValue(QString("%1").arg(year));
}

void QEXTDateTimeTumbler::setMonth(int month)
{
    Q_D(QEXTDateTimeTumbler);
    d->m_tumblerMonth->setCurrentValue(QString("%1 月").arg(month));
}

void QEXTDateTimeTumbler::setDay(int day)
{
    Q_D(QEXTDateTimeTumbler);
    d->m_tumblerDay->setCurrentValue(QString("%1").arg(day));
}

void QEXTDateTimeTumbler::setHour(int hour)
{
    Q_D(QEXTDateTimeTumbler);
    d->m_tumblerHour->setCurrentValue(QString("%1").arg(hour));
}

void QEXTDateTimeTumbler::setMin(int min)
{
    Q_D(QEXTDateTimeTumbler);
    d->m_tumblerMin->setCurrentValue(QString("%1").arg(min));
}

void QEXTDateTimeTumbler::setSec(int sec)
{
    Q_D(QEXTDateTimeTumbler);
    d->m_tumblerSec->setCurrentValue(QString("%1").arg(sec));
}

void QEXTDateTimeTumbler::setDateTime(int year, int month, int day, int hour, int min, int sec)
{
    this->setYear(year);
    this->setMonth(month);
    this->setDay(day);
    this->setHour(hour);
    this->setMin(min);
    this->setSec(sec);
}
