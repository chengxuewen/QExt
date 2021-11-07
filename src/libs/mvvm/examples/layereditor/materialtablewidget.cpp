// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTreeView>
#include <QVBoxLayout>
#include "materialmodel.h"
#include "materialtablewidget.h"
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmModelMapper.h>
#include <qextMvvmContainerItem.h>
#include <qextMvvmViewModelDelegate.h>



MaterialTableWidget::MaterialTableWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(new QEXTMvvmViewModelDelegate)
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_treeView->setHeaderHidden(false);
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers); // provide one click editing
    m_treeView->setAlternatingRowColors(true);

    auto on_model_reset = [this, material_model](auto) {
        setItem(material_model->topItem<QEXTMvvmContainerItem>());
    };
    material_model->mapper()->addModelResetedListener(on_model_reset, this);
    on_model_reset(material_model);
}

void MaterialTableWidget::setItem(QEXTMvvmItem* material_container)
{
    m_viewModel.reset(QEXTMvvmViewModelFactory::createPropertyTableViewModel(material_container->model()));
    m_viewModel->setRootItem(material_container);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->setRootIsDecorated(false);
    m_treeView->resizeColumnToContents(1);
}

MaterialTableWidget::~MaterialTableWidget() = default;
