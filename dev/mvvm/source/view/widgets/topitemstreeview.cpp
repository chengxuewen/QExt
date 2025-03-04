// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "view/widgets/topitemstreeview.h"
#include "viewmodel/factories/viewmodelfactory.h"

namespace ModelView {
QExtMvvmTopItemsTreeView::QExtMvvmTopItemsTreeView(QExtMvvmSessionModel* model, QWidget* parent) : QExtMvvmItemsTreeView(parent)
{
    setViewModel(Factory::CreateTopItemsViewModel(model));
}

QExtMvvmTopItemsTreeView::~QExtMvvmTopItemsTreeView() = default;

} // namespace ModelView
