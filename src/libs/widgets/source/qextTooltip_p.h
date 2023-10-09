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

#ifndef _QEXTTOOLTIP_P_H
#define _QEXTTOOLTIP_P_H

#include <qextTooltip.h>

class QExtTooltip;
class QEXT_WIDGETS_API QExtTooltipPrivate
{
public:
    explicit QExtTooltipPrivate(QExtTooltip *q);
    virtual ~QExtTooltipPrivate();

    QExtTooltip * const q_ptr;

    int m_borderRadius;
    QColor m_backgroundColor;
    QColor m_foregroundColor;

    bool m_arrowVisible;
    int m_arrowSize;
    QExtTooltip::ArrowPositionType m_arrowPosition;

    bool m_triangleVisible;
    int m_triangleLen;
    QExtTooltip::TrianglePositionType m_trianglePosition;
    QColor m_triangleColor;

    QRect m_backgroundRect;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtTooltipPrivate)
    QEXT_DECL_PUBLIC(QExtTooltip)
};

#endif // _QEXTTOOLTIP_P_H
