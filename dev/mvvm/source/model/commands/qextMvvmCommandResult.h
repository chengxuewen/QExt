// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COMMANDRESULT_H
#define MVVM_COMMANDS_COMMANDRESULT_H

#include <qextVariant.h>

namespace ModelView {

class QExtMvvmSessionItem;

//! Results of command execution.
using QExtMvvmCommandResult = QExtVariant<bool, ModelView::QExtMvvmSessionItem*>;

} // namespace ModelView

#endif // MVVM_COMMANDS_COMMANDRESULT_H
