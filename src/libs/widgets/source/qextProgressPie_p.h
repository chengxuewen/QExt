/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTPROGRESSPIE_P_H
#define _QEXTPROGRESSPIE_P_H

#include <qextProgressPie.h>

class QExtProgressPie;
class QEXT_WIDGETS_API QExtProgressPiePrivate
{
public:
    explicit QExtProgressPiePrivate(QExtProgressPie *q);
    virtual ~QExtProgressPiePrivate();

    QExtProgressPie * const q_ptr;

    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_baseColor;
    QColor m_innerBackgroundColor;
    QColor m_borderColor;
    QColor m_progressColor;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    double m_nullPosition;
    double m_outlinePenWidth;
    double m_dataPenWidth;

    QExtProgressPie::BarStyle m_barStyle;
    QString m_format;
    bool m_clockWise;
    QGradientStops m_gradientData;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtProgressPiePrivate)
    QEXT_DECL_PUBLIC(QExtProgressPie)
};

#endif // _QEXTPROGRESSPIE_P_H
