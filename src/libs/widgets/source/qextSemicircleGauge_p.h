/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTGAUGESEMICIRCLE_P_H
#define _QEXTGAUGESEMICIRCLE_P_H

#include <qextSemicircleGauge.h>

#include <QColor>
#include <QPropertyAnimation>

class QExtSemicircleGauge;
class QEXT_WIDGETS_API QExtSemicircleGaugePrivate
{
public:
    explicit QExtSemicircleGaugePrivate(QExtSemicircleGauge *q);
    virtual ~QExtSemicircleGaugePrivate();

    QExtSemicircleGauge * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;

    int m_scaleMajor;
    int m_scaleMinor;
    int m_startAngle;
    int m_endAngle;

    QColor m_usedColor;
    QColor m_freeColor;

    QColor m_scaleColor;
    QColor m_pointerColor;
    QColor m_textColor;
    QColor m_titleColor;

    bool m_overlayVisible;
    QColor m_overlayColor;

    QExtSemicircleGauge::PointerStyleType m_pointerStyle;

    int m_offsetY;
    int m_radiusY;

    double m_currentValue;
    bool m_animationVisible;
    QPropertyAnimation *m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtSemicircleGaugePrivate)
    QEXT_DECL_PUBLIC(QExtSemicircleGauge)
};

#endif // _QEXTGAUGESEMICIRCLE_P_H
