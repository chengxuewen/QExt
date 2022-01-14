// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/qextMvvmPropertyFlatViewModel.h>
#include <viewmodel/qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

QEXTMvvmPropertyFlatViewModel::QEXTMvvmPropertyFlatViewModel(QEXTMvvmSessionModel* model, QObject* parent)
    : QEXTMvvmViewModel(make_unique<QEXTMvvmPropertyFlatViewModelController>(model, this), parent)
{
}
