// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_COMPOUNDITEM_H
#define MVVM_MODEL_COMPOUNDITEM_H

#include <qextMvvmCustomVariants.h>
#include <qextMvvmPropertyItem.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmRealLimits.h>

namespace ModelView {

//! Complex item holding mixed QExtMvvmSessionItem types (single properties and other CompountItems).

class QEXT_MVVM_API QExtMvvmCompoundItem : public QExtMvvmSessionItem {
public:
    QExtMvvmCompoundItem(const std::string& modelType = Constants::CompoundItemType);

    //! Adds property item of given type and register it under the given 'name'.
    template <typename T = QExtMvvmPropertyItem> T* addProperty(const std::string& name);

    //! Adds QExtMvvmPropertyItem and sets its value to 'value'.
    template <typename V> QExtMvvmPropertyItem* addProperty(const std::string& name, const V& value);

    //! Register char property. Special case to turn it into std::string.
    QExtMvvmPropertyItem* addProperty(const std::string& name, const char* value);

    std::string displayName() const override;
};

template <typename T> T* QExtMvvmCompoundItem::addProperty(const std::string& name)
{
    registerTag(QExtMvvmTagInfo::propertyTag(name, T().modelType()));
    auto result = insertItem<T>({name, 0});
    result->setDisplayName(name);
    return result;
}

inline QExtMvvmPropertyItem* QExtMvvmCompoundItem::addProperty(const std::string& name, const char* value)
{
    // Consider merging with the method ::addProperty(const std::string& name, const V& value).
    // Currently it is not possible because of QVariant dependency. It converts 'const char*'
    // to QString, and we want std::string.
    return addProperty(name, std::string(value));
}

template <typename V>
QExtMvvmPropertyItem* QExtMvvmCompoundItem::addProperty(const std::string& name, const V& value)
{
    auto property = addProperty<QExtMvvmPropertyItem>(name);
    property->setData(value);
    if constexpr (std::is_floating_point<V>::value)
        property->setData(QExtMvvmRealLimits::limitless(), ItemDataRole::LIMITS);
    return property;
}

} // namespace ModelView

#endif // MVVM_MODEL_COMPOUNDITEM_H
