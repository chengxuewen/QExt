// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_FUNCTION_TYPES_H
#define MVVM_MODEL_FUNCTION_TYPES_H

#include <functional>
#include <qextMemory.h>

namespace ModelView {

class QExtMvvmSessionItem;

//! Definition for item factory funciton.
using QExtMvvmItemFactoryFunc = std::function<QExtUniquePointer<QExtMvvmSessionItem>()>;

//! Creates factory function for item of specific type.
template <typename T>
QExtMvvmItemFactoryFunc
qextMvvmItemFactoryFunction()
{
    return []() { return qextMakeUnique<T>(); };
}

} // namespace ModelView

#endif // MVVM_MODEL_FUNCTION_TYPES_H
