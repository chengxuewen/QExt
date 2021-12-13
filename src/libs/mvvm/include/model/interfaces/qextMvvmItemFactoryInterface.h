// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMFACTORYINTERFACE_H
#define MVVM_MODEL_ITEMFACTORYINTERFACE_H

#include <memory>
#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Interface class for all factories capable of producing QEXTMvvmSessionItem's.

class QEXT_MVVM_API ItemFactoryInterface
{
public:
    virtual ~ItemFactoryInterface() = default;

    virtual std::unique_ptr<QEXTMvvmSessionItem> createItem(const model_type& modelType) const = 0;

    virtual std::unique_ptr<QEXTMvvmSessionItem> createEmptyItem() const = 0;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMFACTORYINTERFACE_H
