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

#ifndef _QEXTRANGESLIDER_P_H
#define _QEXTRANGESLIDER_P_H

#include <qextRangeSlider.h>

class QExtRangeSlider;
class QExtRangeSliderPrivate
{
public:
    explicit QExtRangeSliderPrivate(QExtRangeSlider *q);
    virtual ~QExtRangeSliderPrivate();

    QExtRangeSlider * const q_ptr;

    int m_minValue;
    int m_maxValue;
    int m_leftValue;
    int m_rightValue;

    int m_borderWidth;
    bool m_horizontal;
    bool m_textVisible;

    QColor m_usedColor;
    QColor m_freeColor;
    QColor m_textColor;
    QColor m_rangeTextColor;
    QColor m_sliderColor;
    QColor m_borderColor;

    QExtRangeSlider::SliderStyle m_sliderStyle;
    QExtRangeSlider::SliderBgPercent m_sliderBackgroundPercent;
    QExtRangeSlider::SliderPercent m_sliderPercent;

    bool m_leftPressed;
    bool m_rightPressed;

    int m_sliderLen;
    QRect m_leftSliderRect;
    QRect m_rightSliderRect;
};

#endif // _QEXTRANGESLIDER_P_H
