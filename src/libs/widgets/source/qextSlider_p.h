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

#ifndef _QEXTSLIDER_P_H
#define _QEXTSLIDER_P_H

#include <qextSlider.h>

#include <QColor>

class QExtTooltip;
class QExtSlider;
class QEXT_WIDGETS_API QExtSliderPrivate
{
public:
    explicit QExtSliderPrivate(QExtSlider *q);
    virtual ~QExtSliderPrivate();

    QExtSlider * const q_ptr;

    int m_borderRadius;
    int m_arrowSize;
    QExtSlider::ArrowStyleType m_arrowStyle;

    QColor m_backgroundColor;
    QColor m_foregroundColor;

    int m_tooltipWidth;
    int m_tooltipHeight;
    QFont m_tooltipFont;

    bool m_timeVisible;
    bool m_clickEnable;
    QString m_unitText;

    QExtTooltip *m_tooltip;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtSliderPrivate)
    QEXT_DECL_PUBLIC(QExtSlider)
};

#endif // _QEXTSLIDER_P_H
