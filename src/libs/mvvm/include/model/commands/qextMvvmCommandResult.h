#ifndef _QEXTMVVMCOMMANDRESULT_H
#define _QEXTMVVMCOMMANDRESULT_H

#include <variant>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Results of command execution.
using QEXTCommandResult = std::variant<bool, ModelView::QEXTMvvmSessionItem*>;

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDRESULT_H
