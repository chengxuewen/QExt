// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmDefaultViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>

using namespace ModelView;

QExtMvvmDefaultViewModel::QExtMvvmDefaultViewModel(QExtMvvmSessionModel* model, QObject* parent)
    : QExtMvvmViewModel(qextMakeUnique<QExtMvvmDefaultViewModelController>(model, this), parent)
{
}
