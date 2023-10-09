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

#include <private/qextHidableTabWidget_p.h>
#include <qextIconFontAwesome.h>

#include <QTabBar>
#include <QToolButton>
#include <QSizePolicy>
#include <QTimer>
#include <QChar>

#define DOUBLE_CLICK_DELAY (200) // ms


QExtHidableTabWidgetPrivate::QExtHidableTabWidgetPrivate(QExtHidableTabWidget *q)
    : q_ptr(q)
{

}

QExtHidableTabWidgetPrivate::~QExtHidableTabWidgetPrivate()
{

}



QExtHidableTabWidget::QExtHidableTabWidget(QWidget *parent) :
    QTabWidget(parent), dd_ptr(new QExtHidableTabWidgetPrivate(this))
{
    dd_ptr->m_maxHeight = this->maximumHeight();
    dd_ptr->m_hideAction.reset(new QAction("", this));
    dd_ptr->m_hideAction->setCheckable(true);
    dd_ptr->m_hideAction->setIcon(qextIconFontAwesome->icon(QEXTIconFontAwesome::FA_sort));
    dd_ptr->m_hideAction->setToolTip("Hide Panels");
    dd_ptr->m_hideButton.reset(new QToolButton(this));
    dd_ptr->m_hideButton->setObjectName("hidableTabWidgetHideButton");
    dd_ptr->m_hideButton->setDefaultAction(dd_ptr->m_hideAction.data());
    dd_ptr->m_hideButton->setAutoRaise(true);
    this->setCornerWidget(dd_ptr->m_hideButton.data());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(dd_ptr->m_hideAction.data(), &QAction::toggled, this, &QExtHidableTabWidget::onHideAction);
    this->connectSignals();
}

QExtHidableTabWidget::~QExtHidableTabWidget()
{

}

void QExtHidableTabWidget::onHideAction(bool checked)
{
    if (checked) // hide
    {
        this->setFixedHeight(this->tabBar()->height());
        disconnect(this, &QExtHidableTabWidget::tabBarDoubleClicked, this, &QExtHidableTabWidget::onTabBarDoubleClicked);
        QTimer::singleShot(DOUBLE_CLICK_DELAY, this, &QExtHidableTabWidget::connectSignals);
    }
    else // show
    {
        this->setMaximumHeight(dd_ptr->m_maxHeight); // just a very big number
        disconnect(this, &QExtHidableTabWidget::tabBarClicked, this, &QExtHidableTabWidget::onTabBarClicked);
        QTimer::singleShot(DOUBLE_CLICK_DELAY, this, &QExtHidableTabWidget::connectSignals);
    }
}

void QExtHidableTabWidget::onTabBarClicked()
{
    dd_ptr->m_hideAction->setChecked(false);
}

void QExtHidableTabWidget::onTabBarDoubleClicked()
{
    dd_ptr->m_hideAction->setChecked(true);
}

void QExtHidableTabWidget::connectSignals()
{
    if (dd_ptr->m_hideAction->isChecked()) // hidden
    {
        connect(this, &QExtHidableTabWidget::tabBarClicked, this, &QExtHidableTabWidget::onTabBarClicked);
    }
    else // shown
    {
        connect(this, &QExtHidableTabWidget::tabBarDoubleClicked, this, &QExtHidableTabWidget::onTabBarDoubleClicked);
    }
}

void QExtHidableTabWidget::showTabs()
{
    dd_ptr->m_hideAction->setChecked(false);
}
