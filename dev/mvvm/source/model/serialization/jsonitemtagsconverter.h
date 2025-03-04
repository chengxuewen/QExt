// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONITEMTAGSCONVERTER_H
#define MVVM_SERIALIZATION_JSONITEMTAGSCONVERTER_H

#include <qextMvvmGlobal.h>
#include <functional>
#include <memory>

class QJsonObject;

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmSessionItemTags;
struct QExtMvvmConverterCallbacks;

//! Converter between QExtMvvmSessionItemTags and JSON object.

class QEXT_MVVM_API QExtMvvmJsonItemTagsConverter {
public:
    QExtMvvmJsonItemTagsConverter(QExtMvvmConverterCallbacks callbacks);
    ~QExtMvvmJsonItemTagsConverter();

    QJsonObject to_json(const QExtMvvmSessionItemTags& item_tags);

    void from_json(const QJsonObject& json, QExtMvvmSessionItemTags& item_tags);

private:
    struct JsonItemTagsConverterImpl;
    QExtUniquePointer<JsonItemTagsConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMTAGSCONVERTER_H
