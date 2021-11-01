// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <factories/viewmodelfactory.h>
#include <viewmodel/defaultviewmodel.h>
#include <viewmodel/propertyflatviewmodel.h>
#include <viewmodel/propertytableviewmodel.h>
#include <viewmodel/propertyviewmodel.h>
#include <viewmodel/topitemsviewmodel.h>

using namespace ModelView;

std::unique_ptr<ViewModel> Factory::CreateDefaultViewModel(ModelView::QEXTMvvmSessionModel* model)
{
    return std::make_unique<DefaultViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyViewModel(QEXTMvvmSessionModel* model)
{
    return std::make_unique<PropertyViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyTableViewModel(QEXTMvvmSessionModel* model)
{
    return std::make_unique<PropertyTableViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreateTopItemsViewModel(QEXTMvvmSessionModel* model)
{
    return std::make_unique<TopItemsViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyFlatViewModel(QEXTMvvmSessionModel* model)
{
    return std::make_unique<PropertyFlatViewModel>(model);
}
