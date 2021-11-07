// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphpropertywidget.h"
#include "graphmodel.h"
#include <QBoxLayout>
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmItemsTreeView.h>



GraphPropertyWidget::GraphPropertyWidget(GraphModel* model, QWidget* parent)
    : QWidget(parent), m_treeView(new QEXTMvvmItemsTreeView)
{
    auto layout = new QVBoxLayout;
    layout->addWidget(m_treeView);
    setLayout(layout);
    setModel(model);
}

GraphPropertyWidget::~GraphPropertyWidget()
{

}

void GraphPropertyWidget::setModel(GraphModel* model)
{
    if (!model)
        return;

    m_treeView->setViewModel(QEXTMvvmViewModelFactory::createDefaultViewModel(model));
}
