// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMFACTORY_H
#define MVVM_MODEL_ITEMFACTORY_H

#include "model/interfaces/itemfactoryinterface.h"
#include "qextMVVMGlobal.h"
#include <memory>

namespace ModelView {

class ItemCatalogue;

//! Default SessionItem factory.

class QEXT_MVVM_API ItemFactory : public ItemFactoryInterface {
public:
    ItemFactory(std::unique_ptr<ItemCatalogue> catalogue);
    ~ItemFactory() override;

    void registerItem(const std::string& modelType, item_factory_func_t func,
                      const std::string& label) override;

    std::unique_ptr<SessionItem> createItem(const model_type& modelType) const override;

protected:
    std::unique_ptr<ItemCatalogue> m_catalogue;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMFACTORY_H
