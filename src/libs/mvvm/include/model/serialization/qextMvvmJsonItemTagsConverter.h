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

#include <functional>
#include <memory>
#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionItem;
class SessionItemTags;
class ConverterCallbacks;

//! Converter between SessionItemTags and JSON object.

class QEXT_MVVM_API JsonItemTagsConverter
{
public:
    JsonItemTagsConverter(ConverterCallbacks callbacks);
    ~JsonItemTagsConverter();

    QJsonObject to_json(const SessionItemTags& item_tags);

    void from_json(const QJsonObject& json, SessionItemTags& item_tags);

private:
    struct JsonItemTagsConverterImpl;
    std::unique_ptr<JsonItemTagsConverterImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONITEMTAGSCONVERTER_H
