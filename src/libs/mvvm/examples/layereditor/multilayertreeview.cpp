// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHeaderView>
#include <QTreeView>
#include <QVBoxLayout>
#include "applicationmodels.h"
#include "customeditorfactory.h"
#include "customlayerrowstrategy.h"
#include "multilayertreeview.h"
#include "samplemodel.h"
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmStandardChildrenStrategies.h>
#include <qextMvvmViewModelDelegate.h>



MultiLayerTreeView::MultiLayerTreeView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(new QEXTMvvmViewModelDelegate)
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_delegate->setEditorFactory(new CustomEditorFactory(models));

    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers); // provide one click editing
    m_treeView->setAlternatingRowColors(true);

    setItem(models->sampleModel()->topItem<MultiLayerItem>());
}

MultiLayerTreeView::~MultiLayerTreeView()
{

}

void MultiLayerTreeView::setItem(QEXTMvvmItem* multilayer)
{
    if (!multilayer)
        return;

    m_viewModel.reset(QEXTMvvmViewModelFactory::createViewModel<QEXTMvvmTopItemsStrategy, CustomLayerRowStrategy>(multilayer->model()));
    m_viewModel->setRootItem(multilayer);

    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
}

