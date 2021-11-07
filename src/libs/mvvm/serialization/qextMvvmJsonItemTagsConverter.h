#ifndef _QEXTMVVMJSONITEMTAGSCONVERTER_H
#define _QEXTMVVMJSONITEMTAGSCONVERTER_H

#include <functional>
#include <QScopedPointer>
#include <qextMvvmGlobal.h>

class QJsonObject;


class QEXTMvvmItem;
class QEXTMvvmItemTags;
class QEXTMvvmConverterCallbacks;

//! Converter between QEXTMvvmItemTags and JSON object.

class QEXT_MVVM_API QEXTMvvmJsonItemTagsConverter
{
public:
    QEXTMvvmJsonItemTagsConverter(QEXTMvvmConverterCallbacks callbacks);
    ~QEXTMvvmJsonItemTagsConverter();

    QJsonObject to_json(const QEXTMvvmItemTags& item_tags);

    void from_json(const QJsonObject& json, QEXTMvvmItemTags& item_tags);

private:
    struct JsonItemTagsConverterImpl;
    QScopedPointer<JsonItemTagsConverterImpl> p_impl;
};

#endif // _QEXTMVVMJSONITEMTAGSCONVERTER_H
