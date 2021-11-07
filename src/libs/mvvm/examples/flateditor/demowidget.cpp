// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "demowidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QTreeView>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <qextMvvmDefaultViewModel.h>
#include <qextMvvmTopItemsViewModel.h>
#include <qextMvvmPropertyFlatView.h>
#include <qextMvvmStandardTreeViews.h>



QEXTMvvmDemoWidget::QEXTMvvmDemoWidget(QEXTMvvmModel* model, QWidget* parent)
    : QWidget(parent)
    , m_defaultTreeView(new QEXTMvvmAllItemsTreeView(model))
    , m_propertyTreeView(new QEXTMvvmPropertyTreeView)
    , m_propertyFlatView(new QEXTMvvmPropertyFlatView)
    , m_sessionModel(model)
{

    auto layout = new QHBoxLayout;
    layout->addLayout(create_left_layout());
    layout->addLayout(create_right_layout());
    layout->addLayout(layout);
    setLayout(layout);

    connect_views();
}

QEXTMvvmDemoWidget::~QEXTMvvmDemoWidget() = default;

//! Connect tree views to provide mutual item selection.

void QEXTMvvmDemoWidget::connect_views()
{
    // select items in other views when selection in m_defaultTreeView has changed
    auto on_item_selected = [this](QEXTMvvmItem* item) {
        m_propertyTreeView->setItem(item);
        m_propertyFlatView->setItem(item);
    };
    connect(m_defaultTreeView, &QEXTMvvmAllItemsTreeView::itemSelected, on_item_selected);
}

QBoxLayout* QEXTMvvmDemoWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_defaultTreeView);
    return result;
}

QBoxLayout* QEXTMvvmDemoWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_propertyTreeView);
    result->addWidget(m_propertyFlatView);
    return result;
}
