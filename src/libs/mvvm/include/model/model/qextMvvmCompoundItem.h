#ifndef _QEXTMVVMMODELCOMPOUNDITEM_H
#define _QEXTMVVMMODELCOMPOUNDITEM_H

#include <qextMvvmCustomVariants.h>
#include <qextMvvmPropertyItem.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmRealLimits.h>

#include <qextTypeTrait.h>

namespace ModelView
{

//! Complex item holding mixed QEXTMvvmSessionItem types (single properties and other CompountItems).

class QEXT_MVVM_API QEXTMvvmCompoundItem : public QEXTMvvmSessionItem
{
public:
    QEXTMvvmCompoundItem(const std::string& modelType = QEXTMvvmConstants::CompoundItemType);

    //! Adds property item of given type.
    template <typename T = QEXTMvvmPropertyItem> T* addProperty(const std::string& name);

    template <typename V> QEXTMvvmPropertyItem* addProperty(const std::string& name, const V& value);

    //! Register char property. Special case to turn it into std::string.
    QEXTMvvmPropertyItem* addProperty(const std::string& name, const char* value);

    std::string displayName() const override;
};

template <typename T> T* QEXTMvvmCompoundItem::addProperty(const std::string& name)
{
    T* property = new T;
    registerTag(QEXTMvvmTagInfo::propertyTag(name, property->modelType()));
    property->setDisplayName(name);
    insertItem(property, {name, 0});
    return property;
}

inline QEXTMvvmPropertyItem* QEXTMvvmCompoundItem::addProperty(const std::string& name, const char* value)
{
    return addProperty(name, std::string(value));
}

template <typename V>
QEXTMvvmPropertyItem* QEXTMvvmCompoundItem::addProperty(const std::string& name, const V& value)
{
    auto property = new QEXTMvvmPropertyItem;
    registerTag(QEXTMvvmTagInfo::propertyTag(name, property->modelType()));
    property->setDisplayName(name);
    property->setData(value);

    // FIXME consider limitless values by default.
    if (QEXTTypeIsFloatingPoint<V>::value)
    {
        property->setData(QEXTMvvmRealLimits::nonnegative(), ItemDataRole::LIMITS);
    }

    insertItem(property, {name, 0});
    return property;
}

} // namespace ModelView

#endif // _QEXTMVVMMODELCOMPOUNDITEM_H
