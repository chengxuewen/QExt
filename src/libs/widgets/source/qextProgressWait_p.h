/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTPROGRESSWAIT_P_H
#define _QEXTPROGRESSWAIT_P_H

#include <qextProgressWait.h>

class QExtProgressWait;
class QEXT_WIDGETS_API QExtProgressWaitPrivate
{
public:
    explicit QExtProgressWaitPrivate(QExtProgressWait *q);
    virtual ~QExtProgressWaitPrivate();

    QExtProgressWait * const q_ptr;

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

    QExtProgressWait::Style m_barStyle;
    QColor m_background;
    QColor m_foreground;
    QColor m_textColor;

    QTimer *m_timer;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtProgressWaitPrivate)
    QEXT_DECL_PUBLIC(QExtProgressWait)
};

#endif // _QEXTPROGRESSWAIT_P_H
