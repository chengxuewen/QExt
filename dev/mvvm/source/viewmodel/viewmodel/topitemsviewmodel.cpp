// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/topitemsviewmodel.h"
#include "viewmodel/viewmodel/standardviewmodelcontrollers.h"

using namespace ModelView;

QExtMvvmTopItemsViewModel::QExtMvvmTopItemsViewModel(QExtMvvmSessionModel* model, QObject* parent)
    : QExtMvvmViewModel(qextMakeUnique<QExtMvvmTopItemsViewModelController>(model, this), parent)
{
}
