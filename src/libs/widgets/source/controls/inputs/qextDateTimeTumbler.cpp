/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <private/qextDateTimeTumbler_p.h>
#include <qextTumbler.h>

#include <QBoxLayout>
#include <QDebug>

QExtDateTimeTumblerPrivate::QExtDateTimeTumblerPrivate(QExtDateTimeTumbler *q)
    : q_ptr(q)
    , m_year(0)
    , m_month(0)
    , m_day(0)
    , m_hour(0)
    , m_min(0)
    , m_sec(0)
    , m_tumblerYear(QEXT_NULLPTR)
    , m_tumblerMonth(QEXT_NULLPTR)
    , m_tumblerDay(QEXT_NULLPTR)
    , m_tumblerHour(QEXT_NULLPTR)
    , m_tumblerMin(QEXT_NULLPTR)
    , m_tumblerSec(QEXT_NULLPTR)
{

}

QExtDateTimeTumblerPrivate::~QExtDateTimeTumblerPrivate()
{

}



QExtDateTimeTumbler::QExtDateTimeTumbler(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtDateTimeTumblerPrivate(this))
{
    this->initForm();
}

QExtDateTimeTumbler::~QExtDateTimeTumbler()
{

}

void QExtDateTimeTumbler::initForm()
{
    Q_D(QExtDateTimeTumbler);

    d->m_tumblerYear = new QExtTumbler(this);
    QStringList listYear;
    for (int i = 2015; i <= 2030; i++) {
        listYear << QString("%1").arg(i);
    }
    d->m_tumblerYear->setValueList(listYear);

    d->m_tumblerMonth = new QExtTumbler(this);
    QStringList listMonth;
    for (int i = 1; i <= 12; i++) {
        listMonth << QString("%1 月").arg(i);
    }
    d->m_tumblerMonth->setValueList(listMonth);

    d->m_tumblerDay = new QExtTumbler(this);
    QStringList listDay;
    for (int i = 1; i <= 31; i++) {
        listDay << QString("%1").arg(i);
    }
    d->m_tumblerDay->setValueList(listDay);

    connect(d->m_tumblerYear, SIGNAL(currentValueChanged(QString)), this, SLOT(currentValueChanged(QString)));
    connect(d->m_tumblerMonth, SIGNAL(currentValueChanged(QString)), this, SLOT(currentValueChanged(QString)));

    d->m_tumblerHour = new QExtTumbler(this);
    QStringList listHour;
    for (int i = 0; i <= 23; i++) {
        listHour << QString("%1").arg(i);
    }
    d->m_tumblerHour->setValueList(listHour);

    d->m_tumblerMin = new QExtTumbler(this);
    QStringList listMin;
    for (int i = 0; i <= 59; i++) {
        listMin << QString("%1").arg(i);
    }
    d->m_tumblerMin->setValueList(listMin);

    d->m_tumblerSec = new QExtTumbler(this);
    QStringList listSec;
    for (int i = 0; i <= 59; i++) {
        listSec << QString("%1").arg(i);
    }
    d->m_tumblerSec->setValueList(listSec);

    QHBoxLayout *layout = new QHBoxLayout(this);
    qextSetLayoutMargin(layout, 0);
    layout->setSpacing(0);
    layout->addWidget(d->m_tumblerYear);
    layout->addWidget(d->m_tumblerMonth);
    layout->addWidget(d->m_tumblerDay);
    layout->addWidget(d->m_tumblerHour);
    layout->addWidget(d->m_tumblerMin);
    layout->addWidget(d->m_tumblerSec);
}

void QExtDateTimeTumbler::currentValueChanged(const QString &)
{
    Q_D(QExtDateTimeTumbler);
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

int QExtDateTimeTumbler::year() const
{
    Q_D(const QExtDateTimeTumbler);
    return d->m_tumblerYear->currentValue().toInt();
}

int QExtDateTimeTumbler::month() const
{
    Q_D(const QExtDateTimeTumbler);
    return d->m_tumblerMonth->currentValue().left(2).toInt();
}

int QExtDateTimeTumbler::day() const
{
    Q_D(const QExtDateTimeTumbler);
    return d->m_tumblerDay->currentValue().toInt();
}

int QExtDateTimeTumbler::hour() const
{
    Q_D(const QExtDateTimeTumbler);
    return d->m_tumblerHour->currentValue().toInt();
}

int QExtDateTimeTumbler::min() const
{
    Q_D(const QExtDateTimeTumbler);
    return d->m_tumblerMin->currentValue().toInt();
}

int QExtDateTimeTumbler::sec() const
{
    Q_D(const QExtDateTimeTumbler);
    return d->m_tumblerSec->currentValue().toInt();
}

void QExtDateTimeTumbler::setYear(int year)
{
    Q_D(QExtDateTimeTumbler);
    d->m_tumblerYear->setCurrentValue(QString("%1").arg(year));
}

void QExtDateTimeTumbler::setMonth(int month)
{
    Q_D(QExtDateTimeTumbler);
    d->m_tumblerMonth->setCurrentValue(QString("%1 月").arg(month));
}

void QExtDateTimeTumbler::setDay(int day)
{
    Q_D(QExtDateTimeTumbler);
    d->m_tumblerDay->setCurrentValue(QString("%1").arg(day));
}

void QExtDateTimeTumbler::setHour(int hour)
{
    Q_D(QExtDateTimeTumbler);
    d->m_tumblerHour->setCurrentValue(QString("%1").arg(hour));
}

void QExtDateTimeTumbler::setMin(int min)
{
    Q_D(QExtDateTimeTumbler);
    d->m_tumblerMin->setCurrentValue(QString("%1").arg(min));
}

void QExtDateTimeTumbler::setSec(int sec)
{
    Q_D(QExtDateTimeTumbler);
    d->m_tumblerSec->setCurrentValue(QString("%1").arg(sec));
}

void QExtDateTimeTumbler::setDateTime(int year, int month, int day, int hour, int min, int sec)
{
    this->setYear(year);
    this->setMonth(month);
    this->setDay(day);
    this->setHour(hour);
    this->setMin(min);
    this->setSec(sec);
}
