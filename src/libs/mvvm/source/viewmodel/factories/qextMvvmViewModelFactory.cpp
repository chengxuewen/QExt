// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmViewModelFactory.h>
#include <viewmodel/qextMvvmDefaultViewModel.h>
#include <viewmodel/qextMvvmPropertyFlatViewModel.h>
#include <viewmodel/qextMvvmPropertyTableViewModel.h>
#include <viewmodel/qextMvvmPropertyViewModel.h>
#include <viewmodel/qextMvvmTopItemsViewModel.h>

using namespace ModelView;

std::unique_ptr<ViewModel> Factory::CreateDefaultViewModel(ModelView::SessionModel* model)
{
    return std::make_unique<DefaultViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyViewModel(SessionModel* model)
{
    return std::make_unique<PropertyViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyTableViewModel(SessionModel* model)
{
    return std::make_unique<PropertyTableViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreateTopItemsViewModel(SessionModel* model)
{
    return std::make_unique<TopItemsViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyFlatViewModel(SessionModel* model)
{
    return std::make_unique<PropertyFlatViewModel>(model);
}
