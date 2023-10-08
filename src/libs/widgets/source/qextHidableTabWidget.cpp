#include <qextHidableTabWidget.h>
#include <qextIconFontAwesome.h>
#include <private/qextHidableTabWidget_p.h>

#include <QTabBar>
#include <QToolButton>
#include <QSizePolicy>
#include <QTimer>
#include <QChar>

#define DOUBLE_CLICK_DELAY (200) // ms


QEXTHidableTabWidgetPrivate::QEXTHidableTabWidgetPrivate(QEXTHidableTabWidget *q)
    : q_ptr(q)
{

}

QEXTHidableTabWidgetPrivate::~QEXTHidableTabWidgetPrivate()
{

}



QEXTHidableTabWidget::QEXTHidableTabWidget(QWidget *parent) :
    QTabWidget(parent), dd_ptr(new QEXTHidableTabWidgetPrivate(this))
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

    connect(dd_ptr->m_hideAction.data(), &QAction::toggled, this, &QEXTHidableTabWidget::onHideAction);
    this->connectSignals();
}

QEXTHidableTabWidget::~QEXTHidableTabWidget()
{

}

void QEXTHidableTabWidget::onHideAction(bool checked)
{
    if (checked) // hide
    {
        this->setFixedHeight(this->tabBar()->height());
        disconnect(this, &QEXTHidableTabWidget::tabBarDoubleClicked, this, &QEXTHidableTabWidget::onTabBarDoubleClicked);
        QTimer::singleShot(DOUBLE_CLICK_DELAY, this, &QEXTHidableTabWidget::connectSignals);
    }
    else // show
    {
        this->setMaximumHeight(dd_ptr->m_maxHeight); // just a very big number
        disconnect(this, &QEXTHidableTabWidget::tabBarClicked, this, &QEXTHidableTabWidget::onTabBarClicked);
        QTimer::singleShot(DOUBLE_CLICK_DELAY, this, &QEXTHidableTabWidget::connectSignals);
    }
}

void QEXTHidableTabWidget::onTabBarClicked()
{
    dd_ptr->m_hideAction->setChecked(false);
}

void QEXTHidableTabWidget::onTabBarDoubleClicked()
{
    dd_ptr->m_hideAction->setChecked(true);
}

void QEXTHidableTabWidget::connectSignals()
{
    if (dd_ptr->m_hideAction->isChecked()) // hidden
    {
        connect(this, &QEXTHidableTabWidget::tabBarClicked, this, &QEXTHidableTabWidget::onTabBarClicked);
    }
    else // shown
    {
        connect(this, &QEXTHidableTabWidget::tabBarDoubleClicked, this, &QEXTHidableTabWidget::onTabBarDoubleClicked);
    }
}

void QEXTHidableTabWidget::showTabs()
{
    dd_ptr->m_hideAction->setChecked(false);
}
