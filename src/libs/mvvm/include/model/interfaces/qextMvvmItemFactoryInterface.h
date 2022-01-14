#ifndef _QEXTMVVMMODELITEMFACTORYINTERFACE_H
#define _QEXTMVVMMODELITEMFACTORYINTERFACE_H

#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Interface class for all factories capable of producing QEXTMvvmSessionItem's.

class QEXT_MVVM_API QEXTMvvmItemFactoryInterface
{
public:
    virtual ~QEXTMvvmItemFactoryInterface() = default;

    virtual std::unique_ptr<QEXTMvvmSessionItem> createItem(const model_type& modelType) const = 0;

    virtual std::unique_ptr<QEXTMvvmSessionItem> createEmptyItem() const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELITEMFACTORYINTERFACE_H
