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

std::unique_ptr<QEXTMvvmViewModel> QEXTMvvmFactory::CreateDefaultViewModel(ModelView::QEXTMvvmSessionModel* model)
{
    return make_unique<QEXTMvvmDefaultViewModel>(model);
}

std::unique_ptr<QEXTMvvmViewModel> QEXTMvvmFactory::CreatePropertyViewModel(QEXTMvvmSessionModel* model)
{
    return make_unique<QEXTMvvmPropertyViewModel>(model);
}

std::unique_ptr<QEXTMvvmViewModel> QEXTMvvmFactory::CreatePropertyTableViewModel(QEXTMvvmSessionModel* model)
{
    return make_unique<QEXTMvvmPropertyTableViewModel>(model);
}

std::unique_ptr<QEXTMvvmViewModel> QEXTMvvmFactory::CreateTopItemsViewModel(QEXTMvvmSessionModel* model)
{
    return make_unique<QEXTMvvmTopItemsViewModel>(model);
}

std::unique_ptr<QEXTMvvmViewModel> QEXTMvvmFactory::CreatePropertyFlatViewModel(QEXTMvvmSessionModel* model)
{
    return make_unique<QEXTMvvmPropertyFlatViewModel>(model);
}
