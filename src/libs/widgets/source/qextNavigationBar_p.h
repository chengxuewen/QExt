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

#ifndef _QEXTNAVIGATIONBAR_P_H
#define _QEXTNAVIGATIONBAR_P_H

#include <qextNavigationBar.h>

class QExtNavigationBar;
class QEXT_WIDGETS_API QExtNavigationBarPrivate
{
public:
    explicit QExtNavigationBarPrivate(QExtNavigationBar *q);
    virtual ~QExtNavigationBarPrivate();

    int initStep(int distance);

    QExtNavigationBar * const q_ptr;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;

    QColor m_barStartColor;
    QColor m_barEndColor;

    QColor m_textNormalColor;
    QColor m_textSelectColor;

    QColor m_oldBackgroundEndColor;
    QColor m_oldBarEndColor;

    QString m_items;
    int m_currentIndex;
    QString m_currentItem;

    int m_backgroundRadius;
    int m_barRadius;
    int m_space;

    int m_lineWidth;
    QColor m_lineColor;

    QExtNavigationBar::BarStyleType m_barStyle;

    bool m_keyMoveEnable;
    bool m_horizontal;
    bool m_flat;

    QVector<QPair<QString, QRectF> > m_listItem;

    QRectF m_barRect;
    QRectF m_targetRect;
    double m_barLen;
    double m_targetLen;

    double m_initLen;
    int m_step;

    bool m_isForward;
    bool m_isVirgin;
    QTimer *m_timer;

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationBarPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationBar)
};

#endif // _QEXTNAVIGATIONBAR_P_H
