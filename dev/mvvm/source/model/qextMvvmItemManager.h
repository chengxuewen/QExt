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

#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmItemPool;
class QExtMvvmItemFactoryInterface;

//! Manages item creation/registration for QExtMvvmSessionModel.

class QEXT_MVVM_API QExtMvvmItemManager {
public:
    QExtMvvmItemManager();
    ~QExtMvvmItemManager();

    void setItemFactory(QExtUniquePointer<QExtMvvmItemFactoryInterface> factory);
    void setItemPool(std::shared_ptr<QExtMvvmItemPool> pool);

    QExtUniquePointer<QExtMvvmSessionItem> createItem(const QExtMvvmModelType& modelType = {}) const;

    QExtUniquePointer<QExtMvvmSessionItem> createRootItem() const;

    QExtMvvmSessionItem* findItem(const QExtMvvmIdentifierType& id) const;

    QExtMvvmIdentifierType findIdentifier(const QExtMvvmSessionItem* item) const;

    const QExtMvvmItemPool* itemPool() const;
    QExtMvvmItemPool* itemPool();

    void registerInPool(QExtMvvmSessionItem* item);
    void unregisterFromPool(QExtMvvmSessionItem* item);

    const QExtMvvmItemFactoryInterface* factory() const;

    QExtMvvmItemFactoryInterface* factory();

private:
    std::shared_ptr<QExtMvvmItemPool> m_item_pool;
    QExtUniquePointer<QExtMvvmItemFactoryInterface> m_item_factory;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMMANAGER_H
