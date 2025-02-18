// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "view/widgets/allitemstreeview.h"
#include "viewmodel/factories/viewmodelfactory.h"

namespace ModelView {
AllItemsTreeView::AllItemsTreeView(SessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Factory::CreateDefaultViewModel(model));
}

AllItemsTreeView::~AllItemsTreeView() = default;

} // namespace ModelView
