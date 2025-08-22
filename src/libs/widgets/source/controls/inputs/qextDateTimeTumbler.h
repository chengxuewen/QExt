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

#ifndef _QEXTDATETIMETUMBLER_H
#define _QEXTDATETIMETUMBLER_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QDateTime>

class QExtTumbler;
class QExtDateTimeTumblerPrivate;
class QEXT_WIDGETS_API QExtDateTimeTumbler : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int year READ year WRITE setYear)
    Q_PROPERTY(int month READ month WRITE setMonth)
    Q_PROPERTY(int day READ day WRITE setDay)

    Q_PROPERTY(int hour READ hour WRITE setHour)
    Q_PROPERTY(int min READ min WRITE setMin)
    Q_PROPERTY(int sec READ sec WRITE setSec)

public:
    explicit QExtDateTimeTumbler(QWidget *parent = QEXT_NULLPTR);
    ~QExtDateTimeTumbler();

    int year() const;
    int month() const;
    int day() const;

    int hour() const;
    int min() const;
    int sec() const;

public Q_SLOTS:
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);

    void setHour(int hour);
    void setMin(int min);
    void setSec(int sec);

    void setDateTime(int year, int month, int day, int hour, int min, int sec);

protected Q_SLOTS:
    void currentValueChanged(const QString &);

protected:
    void initForm();

    QScopedPointer<QExtDateTimeTumblerPrivate> dd_ptr;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDateTimeTumbler)
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtDateTimeTumbler)
};

#endif // _QEXTDATETIMETUMBLER_H
