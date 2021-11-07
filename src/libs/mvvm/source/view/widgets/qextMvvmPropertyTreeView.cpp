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
#include <qextMvvmItem.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmPropertyTreeView.h>



QEXTMvvmPropertyTreeView::QEXTMvvmPropertyTreeView(QWidget* parent) : QEXTMvvmItemsTreeView(parent)
{
    treeView()->setHeaderHidden(false);
    // provide one click editing
    treeView()->setEditTriggers(QAbstractItemView::AllEditTriggers);
    treeView()->setAlternatingRowColors(true);
}

QEXTMvvmPropertyTreeView::~QEXTMvvmPropertyTreeView()
{

}

void QEXTMvvmPropertyTreeView::setItem(QEXTMvvmItem* item)
{
    if (!item) {
        treeView()->setModel(nullptr);
        return;
    }

    setViewModel(QEXTMvvmViewModelFactory::createPropertyViewModel(item->model()));
    viewModel()->setRootItem(item);
    treeView()->setRootIsDecorated(false);
    treeView()->expandAll();
}
