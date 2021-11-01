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
#include <widgets/allitemstreeview.h>

namespace ModelView
{
AllItemsTreeView::AllItemsTreeView(QEXTMvvmSessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Factory::CreateDefaultViewModel(model));
}

AllItemsTreeView::~AllItemsTreeView() = default;

} // namespace ModelView
