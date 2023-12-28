/***********************************************************************************************************************
**
** Library: QExt
**
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

#ifndef _QEXTFRAMELESSDIALOG_P_H
#define _QEXTFRAMELESSDIALOG_P_H

#include <qextFramelessDialog.h>

#include <QWidget>
#include <QPoint>
#include <QRect>

class QExtFramelessDialog;
class QEXT_WIDGETS_API QExtFramelessDialogPrivate
{
public:
    explicit QExtFramelessDialogPrivate(QExtFramelessDialog *q);
    virtual ~QExtFramelessDialogPrivate();

    QExtFramelessDialog * const q_ptr;

    int m_padding;
    bool m_moveEnable;
    bool m_resizeEnable;

    QWidget *m_titleBar;

    bool m_mousePressed;
    QPoint m_mousePoint;
    QRect m_mouseRect;

    QList<bool> m_pressedArea;
    QList<QRect> m_pressedRect;

    bool m_isMin;
    Qt::WindowFlags m_flags;

private:
    QEXT_DISABLE_COPY_MOVE(QExtFramelessDialogPrivate)
    QEXT_DECL_PUBLIC(QExtFramelessDialog)
};

#endif // _QEXTFRAMELESSDIALOG_P_H
