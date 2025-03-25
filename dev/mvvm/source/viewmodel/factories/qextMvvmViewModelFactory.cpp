// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmViewModelFactory.h>
#include <qextMvvmDefaultViewModel.h>
#include <qextMvvmPropertyFlatViewModel.h>
#include <qextMvvmPropertyTableViewModel.h>
#include <qextMvvmPropertyViewModel.h>
#include <qextMvvmTopItemsViewModel.h>

using namespace ModelView;

QExtUniquePointer<QExtMvvmViewModel> Factory::CreateDefaultViewModel(ModelView::QExtMvvmSessionModel* model)
{
    return qextMakeUnique<QExtMvvmDefaultViewModel>(model);
}

QExtUniquePointer<QExtMvvmViewModel> Factory::CreatePropertyViewModel(QExtMvvmSessionModel* model)
{
    return qextMakeUnique<QExtMvvmPropertyViewModel>(model);
}

QExtUniquePointer<QExtMvvmViewModel> Factory::CreatePropertyTableViewModel(QExtMvvmSessionModel* model)
{
    return qextMakeUnique<QExtMvvmPropertyTableViewModel>(model);
}

QExtUniquePointer<QExtMvvmViewModel> Factory::CreateTopItemsViewModel(QExtMvvmSessionModel* model)
{
    return qextMakeUnique<QExtMvvmTopItemsViewModel>(model);
}

QExtUniquePointer<QExtMvvmViewModel> Factory::CreatePropertyFlatViewModel(QExtMvvmSessionModel* model)
{
    return qextMakeUnique<QExtMvvmPropertyFlatViewModel>(model);
}
