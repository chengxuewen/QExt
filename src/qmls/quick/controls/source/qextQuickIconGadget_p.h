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

#ifndef _QEXTQUICKICONGADGET_P_H
#define _QEXTQUICKICONGADGET_P_H

#include <qextQuickIconGadget.h>

#include <QColor>

class QEXT_QUICKCONTROLS_API QExtQuickIconGadgetPrivate
{
    Q_DISABLE_COPY(QExtQuickIconGadgetPrivate)
    Q_DECLARE_PUBLIC(QExtQuickIconGadget)
public:
    explicit QExtQuickIconGadgetPrivate(QExtQuickIconGadget *q);
    virtual ~QExtQuickIconGadgetPrivate();

    QExtQuickIconGadget * const q_ptr;

    qreal m_width;
    qreal m_height;
    int m_type;
    int m_position;
    qreal m_scale;
    QColor m_color;
    QString m_source;
};



#endif // _QEXTQUICKICONGADGET_P_H
