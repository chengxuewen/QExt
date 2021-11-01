// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTreeView>
#include <factories/viewmodelfactory.h>
#include <qextMvvmSessionItem.h>
#include <viewmodel/viewmodel.h>
#include <widgets/propertytreeview.h>

using namespace ModelView;

PropertyTreeView::PropertyTreeView(QWidget* parent) : ItemsTreeView(parent)
{
    treeView()->setHeaderHidden(false);
    // provide one click editing
    treeView()->setEditTriggers(QAbstractItemView::AllEditTriggers);
    treeView()->setAlternatingRowColors(true);
}

void PropertyTreeView::setItem(QEXTMvvmSessionItem* item)
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

PropertyTreeView::~PropertyTreeView() = default;
