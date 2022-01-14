// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTreeView>
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmSessionItem.h>
#include <viewmodel/qextMvvmViewModel.h>
#include <qextMvvmPropertyTreeView.h>

using namespace ModelView;

QEXTMvvmPropertyTreeView::QEXTMvvmPropertyTreeView(QWidget* parent) : QEXTMvvmItemsTreeView(parent)
{
    treeView()->setHeaderHidden(false);
    // provide one click editing
    treeView()->setEditTriggers(QAbstractItemView::AllEditTriggers);
    treeView()->setAlternatingRowColors(true);
}

void QEXTMvvmPropertyTreeView::setItem(QEXTMvvmSessionItem* item)
{
    if (!item) {
        treeView()->setModel(nullptr);
        return;
    }

    setViewModel(QEXTMvvmFactory::CreatePropertyViewModel(item->model()));
    viewModel()->setRootSessionItem(item);
    treeView()->setRootIsDecorated(false);
    treeView()->expandAll();
}

QEXTMvvmPropertyTreeView::~QEXTMvvmPropertyTreeView() = default;
