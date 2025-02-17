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

#include "qextMVVMGlobal.h"
#include <functional>
#include <memory>

class QJsonObject;

namespace ModelView {

class SessionItem;
class SessionItemTags;
struct ConverterCallbacks;

//! Converter between SessionItemTags and JSON object.

class QEXT_MVVM_API JsonItemTagsConverter {
public:
    JsonItemTagsConverter(ConverterCallbacks callbacks);
    ~JsonItemTagsConverter();

    QJsonObject to_json(const SessionItemTags& item_tags);

    void from_json(const QJsonObject& json, SessionItemTags& item_tags);

private:
    struct JsonItemTagsConverterImpl;
    QExtUniquePointer<JsonItemTagsConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMTAGSCONVERTER_H
