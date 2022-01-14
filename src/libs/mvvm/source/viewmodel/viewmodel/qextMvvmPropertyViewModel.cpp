// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/qextMvvmPropertyViewModel.h>
#include <viewmodel/qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

QEXTMvvmPropertyViewModel::QEXTMvvmPropertyViewModel(QEXTMvvmSessionModel* model, QObject* parent)
    : QEXTMvvmViewModel(make_unique<QEXTMvvmPropertyViewModelController>(model, this), parent)
{
}
