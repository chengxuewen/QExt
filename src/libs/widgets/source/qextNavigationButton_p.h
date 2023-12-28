/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2018 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTNAVIGATIONBUTTON_P_H
#define _QEXTNAVIGATIONBUTTON_P_H

#include <qextNavigationButton.h>

class QExtNavigationButton;
class QEXT_WIDGETS_API QExtNavigationButtonPrivate
{
public:
    explicit QExtNavigationButtonPrivate(QExtNavigationButton *q);
    virtual ~QExtNavigationButtonPrivate();

    QExtNavigationButton * const q_ptr;

    int m_padding;
    int m_iconSpace;
    bool m_hovered;
    bool m_iconVisible;
    QPixmap m_hoverIcon;
    QPixmap m_checkIcon;
    QPixmap m_normalIcon;
    QExtNavigationButton::PositionEnum m_navigationPosition;

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationButtonPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationButton)
};

#endif // _QEXTNAVIGATIONBUTTON_P_H
