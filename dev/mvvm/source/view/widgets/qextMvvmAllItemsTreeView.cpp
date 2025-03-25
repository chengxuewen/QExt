// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmAllItemsTreeView.h>
#include <qextMvvmViewModelFactory.h>

namespace ModelView {
AllItemsTreeView::AllItemsTreeView(QExtMvvmSessionModel* model, QWidget* parent) : QExtMvvmItemsTreeView(parent)
{
    setViewModel(Factory::CreateDefaultViewModel(model));
}

AllItemsTreeView::~AllItemsTreeView() = default;

} // namespace ModelView
