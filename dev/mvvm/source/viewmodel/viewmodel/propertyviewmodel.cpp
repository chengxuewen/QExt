// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/viewmodel/propertyviewmodel.h"
#include "viewmodel/viewmodel/standardviewmodelcontrollers.h"

using namespace ModelView;

QExtMvvmPropertyViewModel::QExtMvvmPropertyViewModel(QExtMvvmSessionModel* model, QObject* parent)
    : QExtMvvmViewModel(qextMakeUnique<QExtMvvmPropertyViewModelController>(model, this), parent)
{
}
