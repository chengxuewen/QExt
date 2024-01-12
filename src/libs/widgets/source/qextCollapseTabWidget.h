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

#ifndef _QEXTCOLLAPSETABWIDGET_H
#define _QEXTCOLLAPSETABWIDGET_H

#include <qextWidgetGlobal.h>

#include <QTabWidget>
#include <QAction>

class QToolButton;

class QExtCollapseTabWidgetPrivate;
class QEXT_WIDGETS_API QExtCollapseTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit QExtCollapseTabWidget(QWidget *parent = QEXT_NULLPTR);
    ~QExtCollapseTabWidget() QEXT_OVERRIDE;

    bool isCollapsed() const;
    bool isAnimationEnable() const;

    QIcon collapseIcon() const;
    void setCollapseIcon(const QIcon &icon);

Q_SIGNALS:
    void tabsExpanded();
    void tabsCollapsed();
    void tabsCollapseChanged(bool collapsed);
    void animationEnableChanged(bool enable);

public Q_SLOTS:
    void expandTabs();
    void collapseTabs();
    void setCollapseState(bool collapse);
    void setAnimationEnable(bool enable);

private Q_SLOTS:
    void onTabBarClicked();
    void onToolButtonClicked();
    void onTabBarDoubleClicked();
    void onAnimationValueChanged(const QVariant &value);

    void connectSignals();

protected:
    QScopedPointer<QExtCollapseTabWidgetPrivate> dd_ptr;

private:
    Q_DISABLE_COPY(QExtCollapseTabWidget)
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtCollapseTabWidget)
};

#endif // _QEXTCOLLAPSETABWIDGET_H
