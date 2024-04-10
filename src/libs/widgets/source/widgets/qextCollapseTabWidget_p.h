/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2022~Present ChengXueWen. Contact: 1398831004@qq.com
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

#ifndef _QEXTCOLLAPSETABWIDGET_P_H
#define _QEXTCOLLAPSETABWIDGET_P_H

#include <qextCollapseTabWidget.h>
#include <qextIconAnimation.h>

#include <QPushButton>
#include <QStateMachine>
#include <QVariantAnimation>

class QExtCollapseTabWidgetPrivate
{
public:
    explicit QExtCollapseTabWidgetPrivate(QExtCollapseTabWidget *q);
    virtual ~QExtCollapseTabWidgetPrivate();

    int rotationAngle();
    QRect collapseButtonRect();
    int rotationAngleFromTabPosition(QTabWidget::TabPosition position);
    QRect collapseButtonRectFromTabPosition(QTabWidget::TabPosition position);

    QExtCollapseTabWidget *const q_ptr;

    QScopedPointer<QPushButton> m_collapseButton;
    QScopedPointer<QExtIconAnimation> m_iconAnimation;
    QScopedPointer<QVariantAnimation> m_sizeAnimation;
    int m_collapseIconDefaultRotationAngle;
    int m_animationEnadValue;
    bool m_collapseVertical;
    bool m_animationEnable;
    bool m_collapsed;
    int m_collapsedSize;
    int m_maximumSize;
    int m_minimumSize;
    int m_expandSize;

private:
    Q_DECLARE_PUBLIC(QExtCollapseTabWidget)
    Q_DISABLE_COPY(QExtCollapseTabWidgetPrivate)
};

#endif // _QEXTCOLLAPSETABWIDGET_P_H
