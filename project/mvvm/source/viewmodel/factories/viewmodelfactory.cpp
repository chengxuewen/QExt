// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/factories/viewmodelfactory.h"
#include "viewmodel/viewmodel/defaultviewmodel.h"
#include "viewmodel/viewmodel/propertyflatviewmodel.h"
#include "viewmodel/viewmodel/propertytableviewmodel.h"
#include "viewmodel/viewmodel/propertyviewmodel.h"
#include "viewmodel/viewmodel/topitemsviewmodel.h"

using namespace ModelView;

QExtUniquePointer<ViewModel> Factory::CreateDefaultViewModel(ModelView::SessionModel* model)
{
    return qextMakeUnique<DefaultViewModel>(model);
}

QExtUniquePointer<ViewModel> Factory::CreatePropertyViewModel(SessionModel* model)
{
    return qextMakeUnique<PropertyViewModel>(model);
}

QExtUniquePointer<ViewModel> Factory::CreatePropertyTableViewModel(SessionModel* model)
{
    return qextMakeUnique<PropertyTableViewModel>(model);
}

QExtUniquePointer<ViewModel> Factory::CreateTopItemsViewModel(SessionModel* model)
{
    return qextMakeUnique<TopItemsViewModel>(model);
}

QExtUniquePointer<ViewModel> Factory::CreatePropertyFlatViewModel(SessionModel* model)
{
    return qextMakeUnique<PropertyFlatViewModel>(model);
}
