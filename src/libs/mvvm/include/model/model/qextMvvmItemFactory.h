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

#include <memory>
#include <qextMvvmItemFactoryInterface.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class ItemCatalogue;

//! Default QEXTMvvmSessionItem factory.

class QEXT_MVVM_API ItemFactory : public QEXTMvvmItemFactoryInterface
{
public:
    ItemFactory(std::unique_ptr<ItemCatalogue> catalogue);
    ~ItemFactory() override;

    std::unique_ptr<QEXTMvvmSessionItem> createItem(const model_type& modelType) const override;

    std::unique_ptr<QEXTMvvmSessionItem> createEmptyItem() const override;

protected:
    std::unique_ptr<ItemCatalogue> m_catalogue;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMFACTORY_H
