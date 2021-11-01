#ifndef _QEXTMVVMJSONITEMTAGSCONVERTER_H
#define _QEXTMVVMJSONITEMTAGSCONVERTER_H

#include <functional>
#include <memory>
#include <qextMvvmGlobal.h>

class QJsonObject;

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionItemTags;
class QEXTMvvmConverterCallbacks;

//! Converter between QEXTMvvmSessionItemTags and JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemTagsConverter
{
public:
    QEXTMvvmJsonItemTagsConverter(QEXTMvvmConverterCallbacks callbacks);
    ~QEXTMvvmJsonItemTagsConverter();

    QJsonObject to_json(const QEXTMvvmSessionItemTags& item_tags);

    void from_json(const QJsonObject& json, QEXTMvvmSessionItemTags& item_tags);

private:
    struct JsonItemTagsConverterImpl;
    std::unique_ptr<JsonItemTagsConverterImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMJSONITEMTAGSCONVERTER_H
