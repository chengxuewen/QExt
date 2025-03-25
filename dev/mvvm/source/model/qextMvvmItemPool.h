// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_ITEMPOOL_H
#define MVVM_MODEL_ITEMPOOL_H

#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>
#include <map>

namespace ModelView {

class QExtMvvmSessionItem;

//! Provides registration of QExtMvvmSessionItem pointers and their unique identifiers
//! in global memory pool.

class QEXT_MVVM_API QExtMvvmItemPool {
public:
    QExtMvvmItemPool() = default;
    QExtMvvmItemPool(const QExtMvvmItemPool&) = delete;
    QExtMvvmItemPool(QExtMvvmItemPool&&) = delete;
    QExtMvvmItemPool& operator=(const QExtMvvmItemPool&) = delete;
    QExtMvvmItemPool& operator=(QExtMvvmItemPool&&) = delete;

    size_t size() const;

    QExtMvvmIdentifierType register_item(QExtMvvmSessionItem* item, QExtMvvmIdentifierType key = {});
    void unregister_item(QExtMvvmSessionItem* item);

    QExtMvvmIdentifierType key_for_item(const QExtMvvmSessionItem* item) const;

    QExtMvvmSessionItem* item_for_key(const QExtMvvmIdentifierType& key) const;

private:
    std::map<QExtMvvmIdentifierType, QExtMvvmSessionItem*> m_key_to_item;
    std::map<const QExtMvvmSessionItem*, QExtMvvmIdentifierType> m_item_to_key;
};

} // namespace ModelView

#endif // MVVM_MODEL_ITEMPOOL_H
