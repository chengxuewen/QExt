/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2022~Present ChengXueWen. Contact: 1398831004@qq.com.
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

#ifndef _QEXTTHERMOMETER_P_H
#define _QEXTTHERMOMETER_P_H

#include <qextThermometer.h>

class QExtThermometer;
class QEXT_WIDGETS_API QExtThermometerPrivate
{
public:
    explicit QExtThermometerPrivate(QExtThermometer *q);
    virtual ~QExtThermometerPrivate();

    QExtThermometer * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;

    int m_precision;
    int m_longStep;
    int m_shortStep;
    int m_space;

    bool m_animation;
    double m_animationStep;

    bool m_userValueVisible;
    double m_userValue;
    QColor m_userValueColor;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;
    QColor m_lineColor;
    QColor m_barBackgroundColor;
    QColor m_barColor;

    QExtThermometer::BarPosition m_barPosition;
    QExtThermometer::TickPosition m_tickPosition;

    int m_barWidth;
    int m_barHeight;
    int m_radius;
    int m_targetX;
    QRectF m_barRect;
    QRectF m_circleRect;

    bool m_reverse;
    double m_currentValue;
    QTimer *m_timer;

private:
    QEXT_DISABLE_COPY_MOVE(QExtThermometerPrivate)
    QEXT_DECL_PUBLIC(QExtThermometer)
};

#endif // _QEXTTHERMOMETER_P_H
