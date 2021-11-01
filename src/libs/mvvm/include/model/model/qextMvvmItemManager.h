#ifndef _QEXTMVVMITEMMANAGER_H
#define _QEXTMVVMITEMMANAGER_H

#include <memory>
#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmItemPool;
class QEXTMvvmItemFactoryInterface;

//! Manages item creation/registration for QEXTMvvmSessionModel.

class QEXT_MVVM_API QEXTMvvmItemManager
{
public:
    QEXTMvvmItemManager();
    ~QEXTMvvmItemManager();

    void setItemFactory(std::unique_ptr<QEXTMvvmItemFactoryInterface> factory);
    void setItemPool(std::shared_ptr<QEXTMvvmItemPool> pool);

    std::unique_ptr<QEXTMvvmSessionItem> createItem(const QEXTMvvmModelType& modelType = {}) const;

    std::unique_ptr<QEXTMvvmSessionItem> createRootItem() const;

    QEXTMvvmSessionItem* findItem(const QEXTMvvmIdentifierType& id) const;

    QEXTMvvmIdentifierType findIdentifier(QEXTMvvmSessionItem* item) const;

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

#endif // _QEXTMVVMITEMMANAGER_H
