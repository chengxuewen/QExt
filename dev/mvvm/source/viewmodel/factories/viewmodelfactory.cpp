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
