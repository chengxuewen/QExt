/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTSWITCHBUTTON_P_H
#define _QEXTSWITCHBUTTON_P_H

#include <qextSwitchButton.h>

#include <QVariantAnimation>

class QExtSwitchButton;
class QEXT_WIDGETS_API QExtSwitchButtonPrivate
{
public:
    explicit QExtSwitchButtonPrivate(QExtSwitchButton *q);
    virtual ~QExtSwitchButtonPrivate();

    QExtSwitchButton * const q_ptr;

    int m_space;
    int m_rectRadius;
    bool m_checked;
    bool m_textVisible;
    bool m_circleVisible;
    bool m_animationEnable;

    QExtSwitchButton::Style m_buttonStyle;

    QColor m_backgroundOffColor;
    QColor m_backgroundOnColor;
    QColor m_sliderOffColor;
    QColor m_sliderOnColor;
    QColor m_offTextColor;
    QColor m_onTextColor;

    QString m_offText;
    QString m_onText;

    int m_step;
    int m_startX;
    int m_endX;
    QScopedPointer<QTimer> m_timer;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtSwitchButtonPrivate)
    QEXT_DECL_PUBLIC(QExtSwitchButton)
};

#endif // _QEXTSWITCHBUTTON_P_H
