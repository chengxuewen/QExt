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

#ifndef _QEXTKNOB_P_H
#define _QEXTKNOB_P_H

#include <qextProgressKnob.h>

class QPropertyAnimation;
class QExtProgressKnob;
class QEXT_WIDGETS_API QExtProgressKnobPrivate
{
public:
    explicit QExtProgressKnobPrivate(QExtProgressKnob *q);
    virtual ~QExtProgressKnobPrivate();

    QExtProgressKnob * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    int m_startAngle;
    int m_endAngle;

    QColor m_backgroundColor;
    QColor m_progressColor;
    QColor m_progressBackgroundColor;
    QColor m_circleStartColor;
    QColor m_circleEndColor;
    QColor m_textColor;

    bool m_pointerVisible;
    bool m_valueVisible;
    QExtProgressKnob::PointerStyle m_pointerStyle;

    bool m_pressed;
    bool m_hover;
    bool m_animationEnable;
    int m_radiusCoverCircle;
    int m_radiusCircle;
    QPropertyAnimation *m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtProgressKnobPrivate)
    QEXT_DECL_PUBLIC(QExtProgressKnob)
};

#endif // _QEXTKNOB_P_H
