#ifndef _QEXTMVVMSIGNALSCALLBACKTYPES_H
#define _QEXTMVVMSIGNALSCALLBACKTYPES_H

#include <qextMvvmTagRow.h>

#include <functional>
#include <string>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionModel;

namespace QEXTMvvmCallbacks
{
using slot_t = const void*;
using item_t = std::function<void(QEXTMvvmSessionItem*)>;
using item_int_t = std::function<void(QEXTMvvmSessionItem*, int)>;
using item_str_t = std::function<void(QEXTMvvmSessionItem*, std::string)>;
using item_tagrow_t = std::function<void(QEXTMvvmSessionItem*, QEXTMvvmTagRow)>;
using model_t = std::function<void(QEXTMvvmSessionModel*)>;
} // namespace Callbacks

} // namespace ModelView

#endif // _QEXTMVVMSIGNALSCALLBACKTYPES_H
