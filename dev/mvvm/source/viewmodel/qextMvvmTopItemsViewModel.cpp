// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmTopItemsViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

QExtMvvmTopItemsViewModel::QExtMvvmTopItemsViewModel(QExtMvvmSessionModel* model, QObject* parent)
    : QExtMvvmViewModel(qextMakeUnique<QExtMvvmTopItemsViewModelController>(model, this), parent)
{
}
