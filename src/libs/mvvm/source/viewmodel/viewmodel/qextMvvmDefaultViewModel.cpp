// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/qextMvvmDefaultViewModel.h>
#include <viewmodel/qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

QEXTMvvmDefaultViewModel::QEXTMvvmDefaultViewModel(QEXTMvvmSessionModel* model, QObject* parent)
    : QEXTMvvmViewModel(make_unique<QEXTMvvmDefaultViewModelController>(model, this), parent)
{
}
