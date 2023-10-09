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

    int m_leftPadding;
    int m_rightPadding;
    int m_topPadding;
    int m_bottomPadding;
    QExtNavigationButton::TextAlignType m_textAlign;

    bool m_triangleVisible;
    QExtNavigationButton::PositionType m_trianglePosition;
    int m_triangleLen;
    QColor m_triangleColor;

    bool m_iconVisible;
    QExtNavigationButton::PositionType m_iconPosition;
    int m_iconSpace;
    QSize m_iconSize;
    QPixmap m_normalIcon;
    QPixmap m_hoverIcon;
    QPixmap m_checkIcon;
    QChar m_normalFontIcon;
    QChar m_hoverFontIcon;
    QChar m_checkFontIcon;

    bool m_lineVisible;
    QExtNavigationButton::PositionType m_linePosition;
    int m_lineSpace;
    int m_lineWidth;
    QColor m_lineColor;

    QColor m_normalBackgroundColor;
    QColor m_hoverBackgroundColor;
    QColor m_checkBackgroundColor;
    QColor m_normalTextColor;
    QColor m_hoverTextColor;
    QColor m_checkTextColor;

    QBrush m_normalBackgroundBrush;
    QBrush m_hoverBackgroundBrush;
    QBrush m_checkBackgroundBrush;

    bool m_hovered;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtNavigationButtonPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationButton)
};

#endif // _QEXTNAVIGATIONBUTTON_P_H
