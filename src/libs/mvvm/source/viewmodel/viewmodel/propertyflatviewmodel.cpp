// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/propertyflatviewmodel.h>
#include <viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

PropertyFlatViewModel::PropertyFlatViewModel(QEXTMvvmSessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<PropertyFlatViewModelController>(model, this), parent)
{
}
