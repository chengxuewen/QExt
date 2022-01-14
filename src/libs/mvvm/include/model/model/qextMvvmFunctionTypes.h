#ifndef _QEXTMVVMMODELFUNCTIONTYPES_H
#define _QEXTMVVMMODELFUNCTIONTYPES_H

#include <functional>
#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;
using item_factory_func_t = std::function<std::unique_ptr<QEXTMvvmSessionItem>()>;

} // namespace ModelView

#endif // _QEXTMVVMMODELFUNCTIONTYPES_H
