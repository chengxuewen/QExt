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

#ifndef _QEXTDATETIMETUMBLER_P_H
#define _QEXTDATETIMETUMBLER_P_H

#include <qextDateTimeTumbler.h>

class QExtTumbler;
class QExtDateTimeTumbler;
class QEXT_WIDGETS_API QExtDateTimeTumblerPrivate
{
public:
    explicit QExtDateTimeTumblerPrivate(QExtDateTimeTumbler *q);
    virtual ~QExtDateTimeTumblerPrivate();

    QExtDateTimeTumbler * const q_ptr;

    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_min;
    int m_sec;

    QExtTumbler *m_tumblerYear;
    QExtTumbler *m_tumblerMonth;
    QExtTumbler *m_tumblerDay;
    QExtTumbler *m_tumblerHour;
    QExtTumbler *m_tumblerMin;
    QExtTumbler *m_tumblerSec;

private:
    QEXT_DISABLE_COPY_MOVE(QExtDateTimeTumblerPrivate)
    QEXT_DECL_PUBLIC(QExtDateTimeTumbler)
};

#endif // _QEXTDATETIMETUMBLER_P_H
