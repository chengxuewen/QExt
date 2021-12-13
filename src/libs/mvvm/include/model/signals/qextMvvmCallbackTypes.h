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

#include <functional>
#include <qextMvvmTagRow.h>
#include <string>

namespace ModelView
{

class QEXTMvvmSessionItem;
class SessionModel;

namespace Callbacks
{
using slot_t = const void*;
using item_t = std::function<void(QEXTMvvmSessionItem*)>;
using item_int_t = std::function<void(QEXTMvvmSessionItem*, int)>;
using item_str_t = std::function<void(QEXTMvvmSessionItem*, std::string)>;
using item_tagrow_t = std::function<void(QEXTMvvmSessionItem*, TagRow)>;
using model_t = std::function<void(SessionModel*)>;
} // namespace Callbacks

} // namespace ModelView

#endif // MVVM_SIGNALS_CALLBACK_TYPES_H
