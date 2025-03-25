// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmPropertyFlatViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

QExtMvvmPropertyFlatViewModel::QExtMvvmPropertyFlatViewModel(QExtMvvmSessionModel* model, QObject* parent)
    : QExtMvvmViewModel(qextMakeUnique<QExtMvvmPropertyFlatViewModelController>(model, this), parent)
{
}
