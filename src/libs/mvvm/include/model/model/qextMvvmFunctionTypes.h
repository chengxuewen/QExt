#ifndef _QEXTMVVMFUNCTIONTYPES_H
#define _QEXTMVVMFUNCTIONTYPES_H

#include <functional>
#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;
using item_factory_func_t = std::function<std::unique_ptr<QEXTMvvmSessionItem>()>;

} // namespace ModelView

#endif // _QEXTMVVMFUNCTIONTYPES_H
