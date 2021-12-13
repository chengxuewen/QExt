// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMMANAGER_H
#define MVVM_MODEL_ITEMMANAGER_H

#include <memory>
#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class ItemPool;
class ItemFactoryInterface;

//! Manages item creation/registration for SessionModel.

class QEXT_MVVM_API ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    void setItemFactory(std::unique_ptr<ItemFactoryInterface> factory);
    void setItemPool(std::shared_ptr<ItemPool> pool);

    std::unique_ptr<QEXTMvvmSessionItem> createItem(const model_type& modelType = {}) const;

    std::unique_ptr<QEXTMvvmSessionItem> createRootItem() const;

    QEXTMvvmSessionItem* findItem(const identifier_type& id) const;

    identifier_type findIdentifier(QEXTMvvmSessionItem* item) const;

    const ItemPool* itemPool() const;
    ItemPool* itemPool();

    void register_item(QEXTMvvmSessionItem* item);
    void unregister_item(QEXTMvvmSessionItem* item);

    const ItemFactoryInterface* factory() const;

private:
    std::shared_ptr<ItemPool> m_item_pool;
    std::unique_ptr<ItemFactoryInterface> m_item_factory;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMMANAGER_H
