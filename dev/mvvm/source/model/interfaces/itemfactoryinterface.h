// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_ITEMFACTORYINTERFACE_H
#define MVVM_INTERFACES_ITEMFACTORYINTERFACE_H

#include "model/core/types.h"
#include "model/model/function_types.h"
#include <qextMvvmGlobal.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionItem;

//! Interface class for all factories capable of producing QExtMvvmSessionItem's.

class QEXT_MVVM_API QExtMvvmItemFactoryInterface
{
public:
    virtual ~QExtMvvmItemFactoryInterface() = default;

    virtual void registerItem(const std::string& modelType, QExtMvvmItemFactoryFunc func,
                              const std::string& label) = 0;

    virtual QExtUniquePointer<QExtMvvmSessionItem> createItem(const QExtMvvmModelType& modelType) const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ITEMFACTORYINTERFACE_H
