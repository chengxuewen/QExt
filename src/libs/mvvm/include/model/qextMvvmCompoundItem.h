#ifndef _QEXTMVVMCOMPOUNDITEM_H
#define _QEXTMVVMCOMPOUNDITEM_H

#include <qextMvvmPropertyItem.h>
#include <qextMvvmItem.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmUtils.h>
#include <qextMvvmRealLimits.h>

//! Complex item holding mixed QEXTMvvmItem types (single properties and other CompountItems).
class QEXT_MVVM_API QEXTMvvmCompoundItem : public QEXTMvvmItem
{
public:
    QEXTMvvmCompoundItem(const QString& modelType = QEXTMvvmConstants::CompoundItemType);

    //! Adds property item of given type.
    template <typename T = QEXTMvvmPropertyItem> T* addProperty(const QString& name);

    template <typename V> QEXTMvvmPropertyItem* addProperty(const QString& name, const V& value);

    //! Register char property. Special case to turn it into QString.
    QEXTMvvmPropertyItem* addProperty(const QString& name, const char* value);

    QString displayName() const QEXT_DECL_OVERRIDE;
};

template <typename T> T* QEXTMvvmCompoundItem::addProperty(const QString& name)
{
    T* property = new T;
    registerTag(QEXTMvvmTagInfo::propertyTag(name, property->modelType()));
    property->setDisplayName(name);
    insertItem(property, {name, 0});
    return property;
}

inline QEXTMvvmPropertyItem* QEXTMvvmCompoundItem::addProperty(const QString& name, const char* value)
{
    return addProperty(name, QString(value));
}

template <typename V>
QEXTMvvmPropertyItem* QEXTMvvmCompoundItem::addProperty(const QString& name, const V& value)
{
    QEXTMvvmPropertyItem *property = new QEXTMvvmPropertyItem;
    this->registerTag(QEXTMvvmTagInfo::propertyTag(name, property->modelType()));
    property->setDisplayName(name);
    property->setData(value);

    // FIXME consider limitless values by default.
    if (QEXTTypeIsFloatingPoint<V>::value)
    {
        property->setData(QEXTMvvmRealLimits::nonnegative(), QEXTMvvmItem::Role_Limits);
    }

    this->insertItem(property, QEXTMvvmTagRow(name, 0));
    return property;
}


#endif // _QEXTMVVMCOMPOUNDITEM_H
