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

#include <private/qextCollapseTabWidget_p.h>
#include <qextSvgIconsResource.h>

#include <QTabBar>
#include <QToolButton>
#include <QSizePolicy>
#include <QTimer>
#include <QChar>
#include <QDebug>

#define DOUBLE_CLICK_DELAY (200) // ms
#define ANIMATION_DURATION (200) // ms

QExtCollapseTabWidgetPrivate::QExtCollapseTabWidgetPrivate(QExtCollapseTabWidget *q)
    : q_ptr(q)
    , m_animationEnable(true)
    , m_collapsed(false)
{
}

QExtCollapseTabWidgetPrivate::~QExtCollapseTabWidgetPrivate()
{
}

QExtCollapseTabWidget::QExtCollapseTabWidget(QWidget *parent)
    : QTabWidget(parent), dd_ptr(new QExtCollapseTabWidgetPrivate(this))
{
    Q_D(QExtCollapseTabWidget);
    /* init animation */
    d->m_animation.reset(new QVariantAnimation(this));
    d->m_animation->setDuration(ANIMATION_DURATION);
    connect(d->m_animation.data(), SIGNAL(valueChanged(QVariant)), this, SLOT(onAnimationValueChanged(QVariant)));

    /* init ui */
    d->m_expandHeight = -1;
    d->m_maximumHeight = this->maximumHeight();
    d->m_minimumHeight = this->minimumHeight();
    d->m_collapsedHeight = this->tabBar()->height();
    QIcon icon(QExtSvgIconsResource::svgResource(QExtSvgIconsResource::Icon_arrows_caret_collapse));
    d->m_collapseButton.reset(new QToolButton(this));
    d->m_collapseButton->setObjectName("collapseTabWidget");
    d->m_collapseButton->setToolTip(tr("%1 TabWidget").arg(d->m_collapsed ? "Collapse" : "Expand"));
    d->m_collapseButton->setFixedSize(QSize(d->m_collapsedHeight, d->m_collapsedHeight));
    d->m_collapseButton->setCheckable(false);
    d->m_collapseButton->setAutoRaise(true);
    d->m_collapseButton->setIcon(icon);
    this->setCornerWidget(d->m_collapseButton.data());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(d->m_collapseButton.data(), SIGNAL(pressed()), this, SLOT(onToolButtonClicked()));
    this->connectSignals();
}

QExtCollapseTabWidget::~QExtCollapseTabWidget()
{
}

bool QExtCollapseTabWidget::isCollapsed() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->m_collapsed && this->tabBar()->height() == this->height();
}

bool QExtCollapseTabWidget::isAnimationEnable() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->m_animation->duration() > 0;
}

QIcon QExtCollapseTabWidget::collapseIcon() const
{

}

void QExtCollapseTabWidget::setCollapseIcon(const QIcon &icon)
{

}

void QExtCollapseTabWidget::setCollapseState(bool collapse)
{
    Q_D(QExtCollapseTabWidget);
    const int height = this->height();
    if (!d->m_collapsed && height != d->m_expandHeight)
    {
        d->m_expandHeight = height;
    }
    d->m_animation->setStartValue(height);
    d->m_animation->setEndValue(collapse ? d->m_collapsedHeight : d->m_expandHeight);
    d->m_animation->start();
    d->m_collapsed = collapse;
    QTimer::singleShot(DOUBLE_CLICK_DELAY, this, SLOT(connectSignals()));
}

void QExtCollapseTabWidget::setAnimationEnable(bool enable)
{
    Q_D(QExtCollapseTabWidget);
    d->m_animation->setDuration(enable ? ANIMATION_DURATION : 0);
}

void QExtCollapseTabWidget::onTabBarClicked()
{
    this->setCollapseState(false);
}

void QExtCollapseTabWidget::onToolButtonClicked()
{
    Q_D(QExtCollapseTabWidget);
    this->setCollapseState(!d->m_collapsed);
}

void QExtCollapseTabWidget::onTabBarDoubleClicked()
{
    this->setCollapseState(true);
}

void QExtCollapseTabWidget::onAnimationValueChanged(const QVariant &value)
{
    Q_D(QExtCollapseTabWidget);
    const int height = value.toInt();
    if (height != d->m_expandHeight)
    {
        this->setFixedHeight(height);
    }
    else
    {
        this->setFixedHeight(height);
        // if (d->m_animation->endValue() == value)
        // {
        //     this->setMaximumHeight(d->m_maximumHeight); // just a very big number
        //     this->setMinimumHeight(d->m_minimumHeight); // just a very big number
        //     auto rect = this->geometry();
        //     rect.setHeight(d->m_expandHeight);
        //     this->setGeometry(rect); // just a very big number
        // }
        // else
        // {
        //     this->setFixedHeight(height);
        // }
    }

    if (d->m_animation->endValue() == value)
    {
        if (d->m_collapsed)
        {
            emit this->tabsCollapsed();
        }
        else
        {
            emit this->tabsExpanded();
        }
        emit this->tabsCollapseChanged(d->m_collapsed);
    }
}

void QExtCollapseTabWidget::connectSignals()
{
    Q_D(QExtCollapseTabWidget);
    if (d->m_collapsed) // collapsed
    {
        disconnect(this, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(onTabBarDoubleClicked()));
        connect(this, SIGNAL(tabBarClicked(int)), this, SLOT(onTabBarClicked()));
    }
    else // expand
    {
        disconnect(this, SIGNAL(tabBarClicked(int)), this, SLOT(onTabBarClicked()));
        connect(this, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(onTabBarDoubleClicked()));
    }
}

void QExtCollapseTabWidget::expandTabs()
{
    this->setCollapseState(false);
}

void QExtCollapseTabWidget::collapseTabs()
{
    this->setCollapseState(true);
}
