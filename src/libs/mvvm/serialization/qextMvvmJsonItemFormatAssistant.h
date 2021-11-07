#ifndef _QEXTMVVMJSONITEMFORMATASSISTANT_H
#define _QEXTMVVMJSONITEMFORMATASSISTANT_H

#include <QString>
#include <memory>
#include <qextMvvmJsonItemConverterInterface.h>

class QEXTMvvmItemFactoryInterface;

//! Utility class to determine, whether given JSON object can represent various parts of
//! QEXTMvvmModel. It is made a class (and not a set of free functions) to allow different formats in
//! the future.

class QEXT_MVVM_API QEXTMvvmJsonItemFormatAssistant
{
public:
    static inline const QString modelKey = "model";
    static inline const QString itemDataKey = "itemData";
    static inline const QString itemTagsKey = "itemTags";
    static inline const QString defaultTagKey = "defaultTag";
    static inline const QString containerKey = "containers";
    static inline const QString tagInfoKey = "tagInfo";
    static inline const QString itemsKey = "items";
    static inline const QString sessionModelKey = "sessionmodel";
    static inline const QString versionKey = "version";
    static inline const QString roleKey = "role";
    static inline const QString variantKey = "variant";

    bool isSessionItem(const QJsonObject& json) const;
    bool isSessionItemData(const QJsonObject& json) const;
    bool isSessionItemTags(const QJsonObject& json) const;
    bool isSessionItemContainer(const QJsonObject& json) const;
    bool isSessionModel(const QJsonObject& object) const;
};

#endif // _QEXTMVVMJSONITEMFORMATASSISTANT_H
