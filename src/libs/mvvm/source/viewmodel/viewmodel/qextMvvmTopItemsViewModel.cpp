// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/qextMvvmStandardViewModelControllers.h>
#include <viewmodel/qextMvvmTopItemsViewModel.h>

using namespace ModelView;

QEXTMvvmTopItemsViewModel::QEXTMvvmTopItemsViewModel(QEXTMvvmSessionModel* model, QObject* parent)
    : QEXTMvvmViewModel(make_unique<QEXTMvvmTopItemsViewModelController>(model, this), parent)
{
}
