// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialtablewidget.h"
#include "materialmodel.h"
#include "viewmodel/factories/viewmodelfactory.h"
#include "model/signals/modelmapper.h"
#include "model/standarditems/containeritem.h"
#include "viewmodel/viewmodel/viewmodeldelegate.h"
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

MaterialTableWidget::MaterialTableWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(qextMakeUnique<QExtMvvmViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_treeView->setHeaderHidden(false);
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers); // provide one click editing
    m_treeView->setAlternatingRowColors(true);

    auto on_model_reset = [this, material_model](QExtMvvmSessionModel*) {
        setItem(material_model->topItem<ModelView::QExtMvvmContainerItem>());
    };
    material_model->mapper()->setOnModelReset(on_model_reset, this);
    on_model_reset(material_model);
}

void MaterialTableWidget::setItem(QExtMvvmSessionItem* material_container)
{
    m_viewModel = Factory::CreatePropertyTableViewModel(material_container->model());
    m_viewModel->setRootSessionItem(material_container);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->setRootIsDecorated(false);
    m_treeView->resizeColumnToContents(1);
}

MaterialTableWidget::~MaterialTableWidget() = default;
