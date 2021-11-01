// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/standardviewmodelcontrollers.h>
#include <viewmodel/topitemsviewmodel.h>

using namespace ModelView;

TopItemsViewModel::TopItemsViewModel(QEXTMvvmSessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<TopItemsViewModelController>(model, this), parent)
{
}
