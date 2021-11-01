#ifndef _QEXTMVVMITEMPOOL_H
#define _QEXTMVVMITEMPOOL_H

#include <map>
#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Provides registration of QEXTMvvmSessionItem pointers and their unique identifiers
//! in global memory pool.

class QEXT_MVVM_API QEXTMvvmItemPool
{
public:
    QEXTMvvmItemPool() = default;
    QEXTMvvmItemPool(const QEXTMvvmItemPool&) = delete;
    QEXTMvvmItemPool(QEXTMvvmItemPool&&) = delete;
    QEXTMvvmItemPool& operator=(const QEXTMvvmItemPool&) = delete;
    QEXTMvvmItemPool& operator=(QEXTMvvmItemPool&&) = delete;

    size_t size() const;

    QEXTMvvmIdentifierType register_item(QEXTMvvmSessionItem* item, QEXTMvvmIdentifierType key = {});
    void unregister_item(QEXTMvvmSessionItem* item);

    QEXTMvvmIdentifierType key_for_item(QEXTMvvmSessionItem* item) const;

    QEXTMvvmSessionItem* item_for_key(const QEXTMvvmIdentifierType& key) const;

private:
    std::map<QEXTMvvmIdentifierType, QEXTMvvmSessionItem*> m_key_to_item;
    std::map<QEXTMvvmSessionItem*, QEXTMvvmIdentifierType> m_item_to_key;
};

} // namespace ModelView

#endif // _QEXTMVVMITEMPOOL_H
