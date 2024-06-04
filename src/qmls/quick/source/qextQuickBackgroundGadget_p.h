/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
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

#ifndef _QEXTQUICKGADGETBACKGROUND_P_H
#define _QEXTQUICKGADGETBACKGROUND_P_H

#include <qextQuickBackgroundGadget.h>

#include <QColor>

class QEXT_QUICK_API QExtQuickBackgroundGadgetPrivate
{
    Q_DISABLE_COPY(QExtQuickBackgroundGadgetPrivate)
    Q_DECLARE_PUBLIC(QExtQuickBackgroundGadget)
public:
    explicit QExtQuickBackgroundGadgetPrivate(QExtQuickBackgroundGadget *q);
    virtual ~QExtQuickBackgroundGadgetPrivate();

    QExtQuickBackgroundGadget * const q_ptr;

    QColor m_color;
    qreal m_radius;
    qreal m_width;
    qreal m_height;
    qreal m_opacity;
    qreal m_scale;
    bool m_visible;
};

#endif // _QEXTQUICKGADGETBACKGROUND_P_H
