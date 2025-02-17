// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/propertyflatviewmodel.h"
#include "viewmodel/viewmodel/standardviewmodelcontrollers.h"

using namespace ModelView;

PropertyFlatViewModel::PropertyFlatViewModel(SessionModel* model, QObject* parent)
    : ViewModel(qextMakeUnique<PropertyFlatViewModelController>(model, this), parent)
{
}
