// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmPropertyTreeView.h>
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmViewModel.h>
#include <QTreeView>

using namespace ModelView;

QExtMvvmPropertyTreeView::QExtMvvmPropertyTreeView(QWidget* parent) : QExtMvvmItemsTreeView(parent)
{
    treeView()->setHeaderHidden(false);
    // provide one click editing
    treeView()->setEditTriggers(QAbstractItemView::AllEditTriggers);
    treeView()->setAlternatingRowColors(true);
}

void QExtMvvmPropertyTreeView::setItem(QExtMvvmSessionItem* item)
{
    if (!item) {
        treeView()->setModel(nullptr);
        return;
    }

    setViewModel(Factory::CreatePropertyViewModel(item->model()));
    viewModel()->setRootSessionItem(item);
    treeView()->setRootIsDecorated(false);
    treeView()->expandAll();
}

QExtMvvmPropertyTreeView::~QExtMvvmPropertyTreeView() = default;
