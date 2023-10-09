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

#ifndef _QEXTPROGRESSRING_P_H
#define _QEXTPROGRESSRING_P_H

#include <qextProgressRing.h>

#include <QColor>
#include <QPropertyAnimation>

class QExtProgressRing;
class QEXT_WIDGETS_API QExtProgressRingPrivate
{
public:
    explicit QExtProgressRingPrivate(QExtProgressRing *q);
    virtual ~QExtProgressRingPrivate();

    QExtProgressRing * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;
    QString m_text;

    bool m_clipCenter;
    bool m_clockWise;
    bool m_showPercent;

    int m_alarmMode;
    int m_startAngle;
    int m_ringPadding;
    int m_ringWidth;

    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_ringColor;
    QColor m_ringBackgroundColor;
    QColor m_circleColor;

    int m_ringValue1;
    int m_ringValue2;
    int m_ringValue3;

    QColor m_ringColor1;
    QColor m_ringColor2;
    QColor m_ringColor3;

    bool m_animationEnable;
    double m_currentValue;
    QPropertyAnimation *m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtProgressRingPrivate)
    QEXT_DECL_PUBLIC(QExtProgressRing)
};


#endif // _QEXTPROGRESSRING_P_H
