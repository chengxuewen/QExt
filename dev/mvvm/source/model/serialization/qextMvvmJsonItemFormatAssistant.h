// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMFORMATASSISTANT_H
#define MVVM_SERIALIZATION_JSONITEMFORMATASSISTANT_H

#include <qextMvvmJsonItemConverterInterface.h>
#include <QString>

namespace ModelView {

//! Utility class to determine, whether given JSON object can represent various parts of
//! QExtMvvmSessionModel. It is made a class (and not a set of free functions) to allow different formats in
//! the future.

class QEXT_MVVM_API QExtMvvmJsonItemFormatAssistant
{
public:
    static constexpr const char *modelKey = "model";
    static constexpr const char *itemDataKey = "itemData";
    static constexpr const char *itemTagsKey = "itemTags";
    static constexpr const char *defaultTagKey = "defaultTag";
    static constexpr const char *containerKey = "containers";
    static constexpr const char *tagInfoKey = "tagInfo";
    static constexpr const char *itemsKey = "items";
    static constexpr const char *sessionModelKey = "sessionmodel";
    static constexpr const char *versionKey = "version";
    static constexpr const char *roleKey = "role";
    static constexpr const char *variantKey = "variant";

    bool isSessionItem(const QJsonObject& json) const;
    bool isSessionItemData(const QJsonObject& json) const;
    bool isSessionItemTags(const QJsonObject& json) const;
    bool isSessionItemContainer(const QJsonObject& json) const;
    bool isSessionModel(const QJsonObject& object) const;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMFORMATASSISTANT_H
