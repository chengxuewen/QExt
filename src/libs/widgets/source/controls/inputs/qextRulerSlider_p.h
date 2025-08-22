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

#ifndef _QEXTRULERSLIDER_P_H
#define _QEXTRULERSLIDER_P_H

#include <qextRulerSlider.h>

class QExtRulerSlider;
class QExtRulerSliderPrivate
{
public:
    explicit QExtRulerSliderPrivate(QExtRulerSlider *q);
    virtual ~QExtRulerSliderPrivate();

    QExtRulerSlider * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    int m_longStep;
    int m_shortStep;
    int m_space;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;
    QColor m_lineColor;

    QColor m_sliderTopColor;
    QColor m_sliderBottomColor;

    QColor m_tipBackgroundColor;
    QColor m_tipTextColor;

    bool m_pressed;
    double m_currentValue;

    double m_longLineHeight;
    double m_shortLineHeight;
    double m_sliderTopHeight;
    double m_sliderBottomHeight;

    QPointF m_sliderLastPot;
    QPointF m_sliderTopPot;
    QPointF m_sliderLeftPot;
    QPointF m_sliderRightPot;

    QRectF m_sliderRect;
    QRectF m_tipRect;
    QPointF m_lineLeftPot;
    QPointF m_lineRightPot;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtRulerSliderPrivate)
    QEXT_DECLARE_PUBLIC(QExtRulerSlider)
};

#endif // _QEXTRULERSLIDER_P_H
