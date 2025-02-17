// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/defaultviewmodel.h"
#include "viewmodel/viewmodel/standardviewmodelcontrollers.h"

using namespace ModelView;

DefaultViewModel::DefaultViewModel(SessionModel* model, QObject* parent)
    : ViewModel(qextMakeUnique<DefaultViewModelController>(model, this), parent)
{
}
