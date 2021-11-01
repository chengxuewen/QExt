#ifndef _QEXTMVVMITEMFACTORYINTERFACE_H
#define _QEXTMVVMITEMFACTORYINTERFACE_H

#include <memory>
#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Interface class for all factories capable of producing QEXTMvvmSessionItem's.

class QEXT_MVVM_API QEXTMvvmItemFactoryInterface
{
public:
    virtual ~QEXTMvvmItemFactoryInterface() = default;

    virtual std::unique_ptr<QEXTMvvmSessionItem> createItem(const QEXTMvvmModelType& modelType) const = 0;

    virtual std::unique_ptr<QEXTMvvmSessionItem> createEmptyItem() const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMITEMFACTORYINTERFACE_H
