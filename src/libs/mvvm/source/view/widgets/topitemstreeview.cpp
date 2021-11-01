// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <factories/viewmodelfactory.h>
#include <viewmodel/viewmodel.h>
#include <widgets/topitemstreeview.h>

namespace ModelView
{
TopItemsTreeView::TopItemsTreeView(QEXTMvvmSessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Factory::CreateTopItemsViewModel(model));
}

TopItemsTreeView::~TopItemsTreeView() = default;

} // namespace ModelView
