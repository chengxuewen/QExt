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
    , m_collapseIconDefaultRotationAngle(0)
    , m_animationEnable(true)
    , m_collapsed(false)
{
}

QExtCollapseTabWidgetPrivate::~QExtCollapseTabWidgetPrivate()
{
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
    case QTabWidget::North: return m_collapseIconDefaultRotationAngle;
    case QTabWidget::South: return m_collapseIconDefaultRotationAngle;
    case QTabWidget::West: return m_collapseIconDefaultRotationAngle + 90;
    case QTabWidget::East: return m_collapseIconDefaultRotationAngle - 90;
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
        return QRect(q_ptr->width() - m_collapsedSize, 0, m_collapsedSize, m_collapsedSize);
    case QTabWidget::South:
        return QRect(q_ptr->width() - m_collapsedSize, q_ptr->height() - m_collapsedSize, m_collapsedSize, m_collapsedSize);
    case QTabWidget::West:
        return QRect(0, q_ptr->height() - m_collapsedSize, m_collapsedSize, m_collapsedSize);
    case QTabWidget::East:
        return QRect(q_ptr->width() - m_collapsedSize, q_ptr->height() - m_collapsedSize, m_collapsedSize, m_collapsedSize);
    default:
        break;
    }
    return QRect();
}

QExtCollapseTabWidget::QExtCollapseTabWidget(QWidget *parent)
    : QTabWidget(parent), dd_ptr(new QExtCollapseTabWidgetPrivate(this))
{
    Q_D(QExtCollapseTabWidget);
    /* init animation */
    d->m_sizeAnimation.reset(new QVariantAnimation(this));
    d->m_sizeAnimation->setDuration(ANIMATION_DURATION);
    connect(d->m_sizeAnimation.data(), SIGNAL(valueChanged(QVariant)), this, SLOT(onAnimationValueChanged(QVariant)));

    /* init ui */
    this->setTabPosition(QTabWidget::North);
    d->m_collapseIconDefaultRotationAngle = 180;
    d->m_iconAnimation.reset(new QExtIconAnimation(QIcon(":/QExtWidgets/image/arrow_caret_collapse.svg"), this));
    d->m_iconAnimation->rotationAnimation()->setDuration(ANIMATION_DURATION);
    d->m_iconAnimation->rotationAnimation()->setStartValue(d->rotationAngle());
    d->m_iconAnimation->rotationAnimation()->setEndValue(d->rotationAngle());
    d->m_collapseButton.reset(new QPushButton(this));
    d->m_collapseButton->setObjectName("collapseTabWidget");
    d->m_collapseButton->setToolTip(tr("%1 TabWidget").arg(d->m_collapsed ? "Collapse" : "Expand"));
    d->m_collapseButton->setFixedSize(QSize(d->m_collapsedSize, d->m_collapsedSize));
    d->m_collapseButton->setCheckable(false);
    d->m_collapseButton->setFlat(true);
    d->m_collapseButton->setIcon(d->m_iconAnimation->animationIcon());
    d->m_collapseButton->setProperty("radius", "square");
    this->setCornerWidget(d->m_collapseButton.data());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    connect(d->m_collapseButton.data(), SIGNAL(pressed()), this, SLOT(onToolButtonClicked()));
    this->connectSignals();
}

QExtCollapseTabWidget::~QExtCollapseTabWidget()
{
}

bool QExtCollapseTabWidget::isPanelCollapsed() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->m_collapsed;
}

bool QExtCollapseTabWidget::isAnimationEnable() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->m_sizeAnimation->duration() > 0;
}

QIcon QExtCollapseTabWidget::panelCollapseIcon() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->m_collapseButton->icon();
}

void QExtCollapseTabWidget::setPanelCollapseIcon(const QIcon &icon)
{
    Q_D(QExtCollapseTabWidget);
    d->m_iconAnimation->setRawIcon(icon);
    d->m_collapseButton->setIcon(d->m_iconAnimation->animationIcon());
    emit this->panelCollapseIconChanged(icon);
}

int QExtCollapseTabWidget::panelCollapseIconDefaultRotationAngle() const
{
    Q_D(const QExtCollapseTabWidget);
    return d->m_collapseIconDefaultRotationAngle;
}

void QExtCollapseTabWidget::setPanelCollapseIconDefaultRotationAngle(int angle)
{
    Q_D(QExtCollapseTabWidget);
    d->m_collapseIconDefaultRotationAngle = angle;
    d->m_iconAnimation->rotationAnimation()->setStartValue(d->rotationAngle());
    d->m_iconAnimation->rotationAnimation()->setEndValue(d->rotationAngle());
}

void QExtCollapseTabWidget::setTabPosition(QTabWidget::TabPosition position)
{
    Q_D(QExtCollapseTabWidget);
    QTabWidget::setTabPosition(position);
    d->m_expandSize = -1;
    d->m_collapsedSize = this->tabBar()->height();
    d->m_collapseVertical = QTabWidget::North == position || QTabWidget::South == position;
    d->m_maximumSize = d->m_collapseVertical ? this->maximumHeight() : this->maximumWidth();
    d->m_minimumSize = d->m_collapseVertical ? this->minimumHeight() : this->minimumHeight();
    if (!d->m_iconAnimation.isNull())
    {
        d->m_iconAnimation->rotationAnimation()->setStartValue(d->rotationAngle());
        d->m_iconAnimation->rotationAnimation()->setEndValue(d->rotationAngle());
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
    const int currentSize = d->m_collapseVertical ? this->height() : this->width();
    if (!d->m_collapsed && currentSize != d->m_expandSize)
    {
        d->m_expandSize = currentSize;
    }
    d->m_sizeAnimation->setStartValue(currentSize);
    d->m_sizeAnimation->setEndValue(collapse ? d->m_collapsedSize : d->m_expandSize);
    d->m_sizeAnimation->start();
    const int rotationAngle = d->m_iconAnimation->rotationAngle();
    d->m_iconAnimation->rotationAnimation()->setStartValue(rotationAngle);
    d->m_iconAnimation->rotationAnimation()->setEndValue(collapse ? rotationAngle - 180 : rotationAngle + 180);
    d->m_iconAnimation->start();
    d->m_collapsed = collapse;
    QTimer::singleShot(DOUBLE_CLICK_DELAY, this, SLOT(connectSignals()));
}

void QExtCollapseTabWidget::setAnimationEnable(bool enable)
{
    Q_D(QExtCollapseTabWidget);
    const int duration = enable ? ANIMATION_DURATION : 0;
    d->m_sizeAnimation->setDuration(duration);
    d->m_iconAnimation->rotationAnimation()->setDuration(duration);
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
    const int size = value.toInt();
    if (size != d->m_expandSize)
    {
        if (d->m_collapseVertical)
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
        if (d->m_collapseVertical)
        {
            this->setFixedHeight(size);
        }
        else
        {
            this->setFixedWidth(size);
        }
    }

    if (d->m_sizeAnimation->endValue() == value)
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

void QExtCollapseTabWidget::resizeEvent(QResizeEvent *event)
{
    Q_D(QExtCollapseTabWidget);
    QTabWidget::resizeEvent(event);
    d->m_collapseButton->setGeometry(d->collapseButtonRect());
}

void QExtCollapseTabWidget::expandTabs()
{
    this->setCollapseState(false);
}

void QExtCollapseTabWidget::collapseTabs()
{
    this->setCollapseState(true);
}
