// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_CALLBACK_TYPES_H
#define MVVM_SIGNALS_CALLBACK_TYPES_H

#include <qextMvvmTagRow.h>
#include <functional>
#include <string>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmSessionModel;

namespace Callbacks {
using slot_t = const void*;
using item_t = std::function<void(QExtMvvmSessionItem*)>;
using item_int_t = std::function<void(QExtMvvmSessionItem*, int)>;
using item_str_t = std::function<void(QExtMvvmSessionItem*, std::string)>;
using item_tagrow_t = std::function<void(QExtMvvmSessionItem*, QExtMvvmTagRow)>;
using model_t = std::function<void(QExtMvvmSessionModel*)>;
} // namespace Callbacks

} // namespace ModelView

#endif // MVVM_SIGNALS_CALLBACK_TYPES_H
