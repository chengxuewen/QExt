/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTTEXTLCD_P_H
#define _QEXTTEXTLCD_P_H

#include <qextTextLcd.h>

#include <QTimer>
#include <QColor>
#include <QSizeF>
#include <QPointF>

class QExtTextLcd;
class QEXT_WIDGETS_API QExtTextLcdPrivate
{
public:
    explicit QExtTextLcdPrivate(QExtTextLcd *q);
    virtual ~QExtTextLcdPrivate();

    QExtTextLcd * const q_ptr;

    QSizeF m_ledTextSizeF;
    QSize m_imageSize;
    QString m_text;

    int m_textAlignment;
    int m_fontPixelSize;
    int m_rowCount;
    int m_columnCount;
    double m_spaceFactory;
    double m_space;
    double m_radius;
    double m_step;
    double m_hBorder;
    QVector<QVector<QPointF> > m_pointFVector;

    QColor m_foregroundColor;
    QColor m_backgroundColor;
    QColor m_textColor;

    bool m_highLightBorder;
    QExtTextLcd::Animation m_animationType;
    QScopedPointer<QTimer> m_animationTimer;
    int m_animationInterval;
    int m_animationOffset;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtTextLcdPrivate)
    QEXT_DECLARE_PUBLIC(QExtTextLcd)
};


#endif // _QEXTTEXTLCD_P_H
