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

#ifndef _QEXTARROWCOMPASS_P_H
#define _QEXTARROWCOMPASS_P_H

#include <qextArrowCompass.h>

#include <QColor>
#include <QPropertyAnimation>

class QExtArrowCompass;
class QEXT_WIDGETS_API QExtArrowCompassPrivate
{
public:
    explicit QExtArrowCompassPrivate(QExtArrowCompass *q);
    virtual ~QExtArrowCompassPrivate();

    QExtArrowCompass * const q_ptr;

    double m_value;
    int m_precision;

    QColor m_crownColorStart;
    QColor m_crownColorEnd;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;

    QColor m_darkColor;
    QColor m_lightColor;

    QColor m_foregroundColor;
    QColor m_textColor;

    QColor m_northPointerColor;
    QColor m_southPointerColor;

    QColor m_centerStartColor;
    QColor m_centerEndColor;

    bool m_animationVisible;
    double m_currentValue;
    QScopedPointer<QPropertyAnimation> m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtArrowCompassPrivate)
    QEXT_DECL_PUBLIC(QExtArrowCompass)
};

#endif // _QEXTARROWCOMPASS_P_H
