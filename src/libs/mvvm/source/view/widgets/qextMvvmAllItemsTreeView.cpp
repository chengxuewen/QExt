// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmViewModelFactory.h>
#include <viewmodel/qextMvvmViewModel.h>
#include <qextMvvmAllItemsTreeView.h>

namespace ModelView
{
QEXTMvvmAllItemsTreeView::QEXTMvvmAllItemsTreeView(QEXTMvvmSessionModel* model, QWidget* parent) : QEXTMvvmItemsTreeView(parent)
{
    setViewModel(QEXTMvvmFactory::CreateDefaultViewModel(model));
}

QEXTMvvmAllItemsTreeView::~QEXTMvvmAllItemsTreeView() = default;

} // namespace ModelView
