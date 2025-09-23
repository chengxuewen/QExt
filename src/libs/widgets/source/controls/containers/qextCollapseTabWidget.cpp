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
#include <qextIconAnimation.h>

#include <QTabBar>
#include <QToolButton>
#include <QSizePolicy>
#include <QTimer>
#include <QChar>
#include <QDebug>
#include <QResizeEvent>
#include <QtMath>

#define DOUBLE_CLICK_DELAY (200) // ms
#define ANIMATION_DURATION (250) // ms

QExtCollapseTabWidgetPrivate::QExtCollapseTabWidgetPrivate(QExtCollapseTabWidget *q)
    : q_ptr(q)
    , mCollapseIconDefaultRotationAngle(0)
    , mAnimationEnabled(false)
    , mCollapsed(false)
{
}

QExtCollapseTabWidgetPrivate::~QExtCollapseTabWidgetPrivate()
{
}

void QExtCollapseTabWidgetPrivate::setDuration()
{
    const int duration = mAnimationEnabled ? ANIMATION_DURATION : 0;
    mSizeAnimation->setDuration(duration);
    mIconAnimation->rotationAnimation()->setDuration(duration);
}

int QExtCollapseTabWidgetPrivate::rotationAngle()
{
    return this->rotationAngleFromTabPosition(q_ptr->tabPosition());
}

QRect QExtCollapseTabWidgetPrivate::collapseButtonRect()
{
    return this->collapseButtonRectFromTabPosition(q_ptr->tabPosition());
}

int QExtCollapseTabWidgetPrivate::rotationAngleFromTabPosition(QTabWidget::TabPosition position)
{
    switch (position)
    {
    case QTabWidget::North: return mCollapseIconDefaultRotationAngle;
    case QTabWidget::South: return mCollapseIconDefaultRotationAngle;
    case QTabWidget::West: return mCollapseIconDefaultRotationAngle + 90;
    case QTabWidget::East: return mCollapseIconDefaultRotationAngle - 90;
    default:
        break;
    }
    return 0;
}

QRect QExtCollapseTabWidgetPrivate::collapseButtonRectFromTabPosition(QTabWidget::TabPosition position)
{
    switch (position)
    {
    case QTabWidget::North:
        return QRect(q_ptr->width() - mCollapsedSize, 0, mCollapsedSize, mCollapsedSize);
    case QTabWidget::South:
        return QRect(q_ptr->width() - mCollapsedSize, q_ptr->height() - mCollapsedSize, mCollapsedSize, mCollapsedSize);
    case QTabWidget::West:
        return QRect(0, q_ptr->height() - mCollapsedSize, mCollapsedSize, mCollapsedSize);
    case QTabWidget::East:
        return QRect(q_ptr->width() - mCollapsedSize, q_ptr->height() - mCollapsedSize, mCollapsedSize, mCollapsedSize);
    default:
        break;
    }
    return QRect();
}

QExtCollapseTabWidget::QExtCollapseTabWidget(QWidget *parent)
    : QTabWidget(parent)
    , dd_ptr(new QExtCollapseTabWidgetPrivate(this))
{
    Q_D(QExtCollapseTabWidget);
    /* init animation */
    d->mSizeAnimation.reset(new QVariantAnimation(this));
    d->mSizeAnimation->setDuration(ANIMATION_DURATION);
    connect(d->mSizeAnimation.data(), SIGNAL(valueChanged(QVariant)), this, SLOT(onAnimationValueChanged(QVariant)));

    /* init ui */
    this->setTabPosition(QTabWidget::North);
    d->mCollapseIconDefaultRotationAngle = 180;
    d->mIconAnimation.reset(new QExtIconAnimation(QIcon(":/QExtWidgets/image/arrow_caret_collapse.svg"), this));
    d->mIconAnimation->rotationAnimation()->setDuration(ANIMATION_DURATION);
    d->mIconAnimation->rotationAnimation()->setStartValue(d->rotationAngle());
    d->mIconAnimation->rotationAnimation()->setEndValue(d->rotationAngle());
    d->mCollapseButton.reset(new QPushButton(this));
    d->mCollapseButton->setObjectName("collapseTabWidget");
    d->mCollapseButton->setToolTip(tr("%1 TabWidget").arg(d->mCollapsed ? "Collapse" : "Expand"));
    d->mCollapseButton->setFixedSize(QSize(d->mCollapsedSize, d->mCollapsedSize));
    d->mCollapseButton->setCheckable(false);
    d->mCollapseButton->setFlat(true);
    d->mCollapseButton->setIcon(d->mIconAnimation->animationIcon());
    d->mCollapseButton->setProperty("radius", "square");
    this->setCornerWidget(d->mCollapseButton.data());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(d->mCollapseButton.data(), SIGNAL(pressed()), this, SLOT(onToolButtonClicked()));
    this->connectSignals();

    d->setDuration();
}

QExtCollapseTabWidget::~QExtCollapseTabWidget()
{
}

bool QExtCollapseTabWidget::isPanelCollapsed() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->mCollapsed;
}

bool QExtCollapseTabWidget::isAnimationEnabled() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->mAnimationEnabled;
}

QIcon QExtCollapseTabWidget::panelCollapseIcon() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->mCollapseButton->icon();
}

void QExtCollapseTabWidget::setPanelCollapseIcon(const QIcon &icon)
{
    Q_D(QExtCollapseTabWidget);
    d->mIconAnimation->setRawIcon(icon);
    d->mCollapseButton->setIcon(d->mIconAnimation->animationIcon());
    emit this->panelCollapseIconChanged(icon);
}

int QExtCollapseTabWidget::panelCollapseIconDefaultRotationAngle() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->mCollapseIconDefaultRotationAngle;
}

void QExtCollapseTabWidget::setPanelCollapseIconDefaultRotationAngle(int angle)
{
    Q_D(QExtCollapseTabWidget);
    d->mCollapseIconDefaultRotationAngle = angle;
    d->mIconAnimation->rotationAnimation()->setStartValue(d->rotationAngle());
    d->mIconAnimation->rotationAnimation()->setEndValue(d->rotationAngle());
}

void QExtCollapseTabWidget::setTabPosition(QTabWidget::TabPosition position)
{
    Q_D(QExtCollapseTabWidget);
    QTabWidget::setTabPosition(position);
    d->mExpandSize = -1;
    d->mCollapsedSize = this->tabBar()->height();
    d->mCollapseVertical = QTabWidget::North == position || QTabWidget::South == position;
    d->mMaximumSize = d->mCollapseVertical ? this->maximumHeight() : this->maximumWidth();
    d->mMinimumSize = d->mCollapseVertical ? this->minimumHeight() : this->minimumHeight();
    if (!d->mIconAnimation.isNull())
    {
        d->mIconAnimation->rotationAnimation()->setStartValue(d->rotationAngle());
        d->mIconAnimation->rotationAnimation()->setEndValue(d->rotationAngle());
    }
}

void QExtCollapseTabWidget::setCornerWidget(QWidget *w, Qt::Corner corner)
{
    Q_UNUSED(w);
    Q_UNUSED(corner);
    // QTabWidget::setCornerWidget(w, corner);
}

void QExtCollapseTabWidget::setCollapseState(bool collapse)
{
    Q_D(QExtCollapseTabWidget);
    const int currentSize = d->mCollapseVertical ? this->height() : this->width();
    if (!d->mCollapsed && currentSize != d->mExpandSize)
    {
        d->mExpandSize = currentSize;
    }
    d->mSizeAnimation->setStartValue(currentSize);
    d->mSizeAnimation->setEndValue(collapse ? d->mCollapsedSize : d->mExpandSize);
    d->mSizeAnimation->start();
    const int rotationAngle = d->mIconAnimation->rotationAngle();
    d->mIconAnimation->rotationAnimation()->setStartValue(rotationAngle);
    d->mIconAnimation->rotationAnimation()->setEndValue(collapse ? rotationAngle - 180 : rotationAngle + 180);
    d->mIconAnimation->start();
    d->mCollapsed = collapse;
    QTimer::singleShot(DOUBLE_CLICK_DELAY, this, SLOT(connectSignals()));
}

void QExtCollapseTabWidget::setAnimationEnable(bool enabled)
{
    Q_D(QExtCollapseTabWidget);
    if (enabled != d->mAnimationEnabled)
    {
        d->mAnimationEnabled = enabled;
        emit this->animationEnableChanged(enabled);
        d->setDuration();
    }
}

void QExtCollapseTabWidget::onTabBarClicked()
{
    this->setCollapseState(false);
}

void QExtCollapseTabWidget::onToolButtonClicked()
{
    Q_D(QExtCollapseTabWidget);
    this->setCollapseState(!d->mCollapsed);
}

void QExtCollapseTabWidget::onTabBarDoubleClicked()
{
    this->setCollapseState(true);
}

void QExtCollapseTabWidget::onAnimationValueChanged(const QVariant &value)
{
    Q_D(QExtCollapseTabWidget);
    const int size = value.toInt();
    if (size != d->mExpandSize)
    {
        if (d->mCollapseVertical)
        {
            this->setFixedHeight(size);
        }
        else
        {
            this->setFixedWidth(size);
        }
    }
    else
    {
        // TODO  split?
        if (d->mCollapseVertical)
        {
            this->setFixedHeight(size);
        }
        else
        {
            this->setFixedWidth(size);
        }
    }

    if (d->mSizeAnimation->endValue() == value)
    {
        if (d->mCollapsed)
        {
            emit this->tabsCollapsed();
        }
        else
        {
            emit this->tabsExpanded();
        }
        emit this->tabsCollapseChanged(d->mCollapsed);
    }
}

void QExtCollapseTabWidget::connectSignals()
{
    Q_D(QExtCollapseTabWidget);
    if (d->mCollapsed) // collapsed
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

void QExtCollapseTabWidget::resizeEvent(QResizeEvent *event)
{
    Q_D(QExtCollapseTabWidget);
    QTabWidget::resizeEvent(event);
    d->mCollapseButton->setGeometry(d->collapseButtonRect());
}

void QExtCollapseTabWidget::expandTabs()
{
    this->setCollapseState(false);
}

void QExtCollapseTabWidget::collapseTabs()
{
    this->setCollapseState(true);
}
