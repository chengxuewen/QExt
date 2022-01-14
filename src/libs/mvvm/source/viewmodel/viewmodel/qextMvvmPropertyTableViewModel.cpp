// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/qextMvvmPropertyTableViewModel.h>
#include <viewmodel/qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

QEXTMvvmPropertyTableViewModel::QEXTMvvmPropertyTableViewModel(QEXTMvvmSessionModel* model, QObject* parent)
    : QEXTMvvmViewModel(make_unique<QEXTMvvmPropertyTableViewModelController>(model, this), parent)
{
}
