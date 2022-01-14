#ifndef _QEXTMVVMMODELITEMMANAGER_H
#define _QEXTMVVMMODELITEMMANAGER_H

#include <memory>
#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmItemPool;
class QEXTMvvmItemFactoryInterface;

//! Manages item creation/registration for SessionModel.

class QEXT_MVVM_API ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    void setItemFactory(std::unique_ptr<QEXTMvvmItemFactoryInterface> factory);
    void setItemPool(std::shared_ptr<QEXTMvvmItemPool> pool);

    std::unique_ptr<QEXTMvvmSessionItem> createItem(const model_type& modelType = {}) const;

    std::unique_ptr<QEXTMvvmSessionItem> createRootItem() const;

    QEXTMvvmSessionItem* findItem(const identifier_type& id) const;

    identifier_type findIdentifier(QEXTMvvmSessionItem* item) const;

    const QEXTMvvmItemPool* itemPool() const;
    QEXTMvvmItemPool* itemPool();

    void register_item(QEXTMvvmSessionItem* item);
    void unregister_item(QEXTMvvmSessionItem* item);

    const QEXTMvvmItemFactoryInterface* factory() const;

private:
    std::shared_ptr<QEXTMvvmItemPool> m_item_pool;
    std::unique_ptr<QEXTMvvmItemFactoryInterface> m_item_factory;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELITEMMANAGER_H
