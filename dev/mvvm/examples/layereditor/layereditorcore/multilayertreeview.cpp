// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "multilayertreeview.h"
#include "applicationmodels.h"
#include "customeditorfactory.h"
#include "customlayerrowstrategy.h"
#include "samplemodel.h"
#include "viewmodel/factories/viewmodelfactory.h"
#include "viewmodel/viewmodel/standardchildrenstrategies.h"
#include "viewmodel/viewmodel/viewmodeldelegate.h"
#include <QHeaderView>
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

MultiLayerTreeView::MultiLayerTreeView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(qextMakeUnique<QExtMvvmViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_delegate->setEditorFactory(qextMakeUnique<CustomEditorFactory>(models));

    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers); // provide one click editing
    m_treeView->setAlternatingRowColors(true);

    setItem(models->sampleModel()->topItem<MultiLayerItem>());
}

void MultiLayerTreeView::setItem(ModelView::QExtMvvmSessionItem* multilayer)
{
    if (!multilayer)
        return;

    m_viewModel =
        Factory::CreateViewModel<QExtMvvmTopItemsStrategy, CustomLayerRowStrategy>(multilayer->model());
    m_viewModel->setRootSessionItem(multilayer);

    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
}

MultiLayerTreeView::~MultiLayerTreeView() = default;
