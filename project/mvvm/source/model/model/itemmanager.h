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

#include "model/core/types.h"
#include "qextMVVMGlobal.h"
#include <memory>

namespace ModelView {

class SessionItem;
class ItemPool;
class ItemFactoryInterface;

//! Manages item creation/registration for SessionModel.

class QEXT_MVVM_API ItemManager {
public:
    ItemManager();
    ~ItemManager();

    void setItemFactory(QExtUniquePointer<ItemFactoryInterface> factory);
    void setItemPool(std::shared_ptr<ItemPool> pool);

    QExtUniquePointer<SessionItem> createItem(const model_type& modelType = {}) const;

    QExtUniquePointer<SessionItem> createRootItem() const;

    SessionItem* findItem(const identifier_type& id) const;

    identifier_type findIdentifier(const SessionItem* item) const;

    const ItemPool* itemPool() const;
    ItemPool* itemPool();

    void registerInPool(SessionItem* item);
    void unregisterFromPool(SessionItem* item);

    const ItemFactoryInterface* factory() const;

    ItemFactoryInterface* factory();

private:
    std::shared_ptr<ItemPool> m_item_pool;
    QExtUniquePointer<ItemFactoryInterface> m_item_factory;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMMANAGER_H
