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
#include <layereditorcore/applicationmodels.h>
#include <layereditorcore/customeditorfactory.h>
#include <layereditorcore/customlayerrowstrategy.h>
#include <layereditorcore/multilayertreeview.h>
#include <layereditorcore/samplemodel.h>
#include <qextMvvmViewModelFactory.h>
#include <viewmodel/qextMvvmStandardChildrenStrategies.h>
#include <viewmodel/qextMvvmViewModelDelegate.h>

using namespace ModelView;

MultiLayerTreeView::MultiLayerTreeView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(make_unique<QEXTMvvmViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_delegate->setEditorFactory(make_unique<CustomEditorFactory>(models));

    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers); // provide one click editing
    m_treeView->setAlternatingRowColors(true);

    setItem(models->sampleModel()->topItem<MultiLayerItem>());
}

void MultiLayerTreeView::setItem(ModelView::QEXTMvvmSessionItem* multilayer)
{
    if (!multilayer)
        return;

    m_viewModel =
        QEXTMvvmFactory::CreateViewModel<QEXTMvvmTopItemsStrategy, CustomLayerRowStrategy>(multilayer->model());
    m_viewModel->setRootSessionItem(multilayer);

    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
}

MultiLayerTreeView::~MultiLayerTreeView() = default;
