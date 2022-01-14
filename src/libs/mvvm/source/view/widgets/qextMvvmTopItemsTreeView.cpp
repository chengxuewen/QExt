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
#include <qextMvvmTopItemsTreeView.h>

namespace ModelView
{
QEXTMvvmTopItemsTreeView::QEXTMvvmTopItemsTreeView(QEXTMvvmSessionModel* model, QWidget* parent) : QEXTMvvmItemsTreeView(parent)
{
    setViewModel(QEXTMvvmFactory::CreateTopItemsViewModel(model));
}

QEXTMvvmTopItemsTreeView::~QEXTMvvmTopItemsTreeView() = default;

} // namespace ModelView
