#ifndef _QEXTMVVMCALLBACKTYPES_H
#define _QEXTMVVMCALLBACKTYPES_H

#include <functional>
#include <qextMvvmTagRow.h>
#include <string>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionModel;

namespace Callbacks
{
using slot_t = const void*;
using item_t = std::function<void(QEXTMvvmSessionItem*)>;
using item_int_t = std::function<void(QEXTMvvmSessionItem*, int)>;
using item_str_t = std::function<void(QEXTMvvmSessionItem*, std::string)>;
using item_tagrow_t = std::function<void(QEXTMvvmSessionItem*, QEXTMvvmTagRow)>;
using model_t = std::function<void(QEXTMvvmSessionModel*)>;
} // namespace Callbacks

} // namespace ModelView

#endif // _QEXTMVVMCALLBACKTYPES_H
