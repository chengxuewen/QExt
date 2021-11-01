// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/defaultviewmodel.h>
#include <viewmodel/standardviewmodelcontrollers.h>

using namespace ModelView;

DefaultViewModel::DefaultViewModel(QEXTMvvmSessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<DefaultViewModelController>(model, this), parent)
{
}
