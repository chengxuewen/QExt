/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2017 逆风微光(QQ:787701109)
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

#ifndef _QEXTSELECTSLIDER_P_H
#define _QEXTSELECTSLIDER_P_H

#include <qextSelectSlider.h>

#include <QColor>
#include <QPoint>
#include <QRect>

class QExtSelectSlider;
class QEXT_WIDGETS_API QExtSelectSliderPrivate
{
public:
    explicit QExtSelectSliderPrivate(QExtSelectSlider *q);
    virtual ~QExtSelectSliderPrivate();

    QExtSelectSlider * const q_ptr;


    int m_maxValue;
    int m_minValue;
    int m_leftValue;
    int m_rightValue;

    int m_rangeValue;
    int m_step;

    int m_borderWidth;
    bool m_horizontal;

    QColor m_usedColor;
    QColor m_freeColor;
    QColor m_textColor;
    QColor m_rangeTextColor;
    QColor m_sliderColor;
    QColor m_borderColor;
    QColor m_buttonNormalColor;
    QColor m_buttonPressColor;

    int m_buttonWidth;
    int m_sliderHeight;

    QPoint m_posPress;
    QPoint m_posMove;

    bool m_sliderPress;
    bool m_leftPress;
    bool m_rightPress;
    bool m_leftButtonPress;
    bool m_rightButtonPress;

    QRect m_sliderRect;
    QRect m_leftRect;
    QRect m_rightRect;
    QRect m_leftBtnRect;
    QRect m_rightBtnRect;

    QRect m_sliderRectTemp;
    QRect m_leftRectTemp;
    QRect m_rightRectTemp;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtSelectSliderPrivate)
    QEXT_DECLARE_PUBLIC(QExtSelectSlider)
};

#endif // _QEXTSELECTSLIDER_P_H
