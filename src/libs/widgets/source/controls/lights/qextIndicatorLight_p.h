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

#ifndef _QEXTINDICATORLIGHT_P_H
#define _QEXTINDICATORLIGHT_P_H

#include <qextIndicatorLight.h>

#include <QColor>
#include <QTimer>

class QExtIndicatorLight;
class QEXT_WIDGETS_API QExtIndicatorLightPrivate
{
public:
    explicit QExtIndicatorLightPrivate(QExtIndicatorLight *q);
    virtual ~QExtIndicatorLightPrivate();

    QExtIndicatorLight * const q_ptr;

    QString m_text;
    QColor m_lightTextColor;
    QColor m_normalTextColor;
    QColor m_lightBackgroundColor;
    QColor m_normalBackgroundColor;
    int m_fontPixelSize;

    QColor m_outBorderStartColor;
    QColor m_outBorderEndColor;
    QColor m_inBorderStartColor;
    QColor m_inBorderEndColor;
    QExtIndicatorLight::Style m_style;
    QExtIndicatorLight::Shape m_shape;

    bool m_moveEnable;
    bool m_overlayVisible;
    QColor m_overlayColor;

    QScopedPointer<QTimer> m_flickerTimer;
    bool m_lightState;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtIndicatorLightPrivate)
    QEXT_DECLARE_PUBLIC(QExtIndicatorLight)
};

#endif // _QEXTINDICATORLIGHT_P_H
