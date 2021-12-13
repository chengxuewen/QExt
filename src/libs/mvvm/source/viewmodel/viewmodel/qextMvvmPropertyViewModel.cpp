// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/qextMvvmPropertyViewModel.h>
#include <viewmodel/qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

PropertyViewModel::PropertyViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<PropertyViewModelController>(model, this), parent)
{
}
