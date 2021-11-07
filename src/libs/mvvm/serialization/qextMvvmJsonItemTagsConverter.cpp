// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonArray>
#include <QJsonObject>
#include <qextMvvmItem.h>
#include <qextMvvmItemTags.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemContainerConverter.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonItemTagsConverter.h>
#include <qextMvvmJsonTagInfoConverter.h>



struct QEXTMvvmJsonItemTagsConverter::JsonItemTagsConverterImpl {
    QScopedPointer<QEXTMvvmJsonItemContainerConverter> m_container_converter;
    QScopedPointer<QEXTMvvmJsonTagInfoConverterInterface> m_taginfo_converter;

    JsonItemTagsConverterImpl(QEXTMvvmConverterCallbacks callbacks = {})
    {
        m_container_converter.reset(new QEXTMvvmJsonItemContainerConverter(callbacks));
        m_taginfo_converter.reset(new QEXTMvvmJsonTagInfoConverter);
    }

    //! Create containers from JSON. QEXTMvvmItemTags should be empty.

    void create_containers(const QJsonObject& json, QEXTMvvmItemTags& item_tags)
    {
        if (item_tags.tagsCount())
            throw std::runtime_error("Error in QEXTMvvmJsonItemTagsConverter: no containers expected.");

        auto default_tag = json[QEXTMvvmJsonItemFormatAssistant::defaultTagKey].toString();
        item_tags.setDefaultTag(default_tag);

        auto container_array = json[QEXTMvvmJsonItemFormatAssistant::containerKey].toArray();

        for (const auto ref : container_array) {
            QJsonObject json_container = ref.toObject();
            QJsonObject json_taginfo =
                json_container[QEXTMvvmJsonItemFormatAssistant::tagInfoKey].toObject();
            QEXTMvvmTagInfo tagInfo = m_taginfo_converter->fromJson(json_taginfo);
            item_tags.registerTag(tagInfo);
        }
    }

    //! Populate containers from JSON. Container must be already created.

    void populate_containers(const QJsonObject& json, QEXTMvvmItemTags& item_tags)
    {
        auto container_array = json[QEXTMvvmJsonItemFormatAssistant::containerKey].toArray();

        if (container_array.size() != item_tags.tagsCount())
            throw std::runtime_error("Error in QEXTMvvmJsonItemTagsConverter: mismatch in number of tags");

        auto default_tag = json[QEXTMvvmJsonItemFormatAssistant::defaultTagKey].toString();
        if (default_tag != item_tags.defaultTag())
            throw std::runtime_error("Error in QEXTMvvmJsonItemTagsConverter: default tag mismatch.");

        int index(0);
        for (const auto container_ref : container_array)
            m_container_converter->from_json(container_ref.toObject(), item_tags.at(index++));
    }
};

QEXTMvvmJsonItemTagsConverter::QEXTMvvmJsonItemTagsConverter(QEXTMvvmConverterCallbacks callbacks)
    : p_impl(new JsonItemTagsConverterImpl(callbacks))
{
}

QEXTMvvmJsonItemTagsConverter::~QEXTMvvmJsonItemTagsConverter() = default;

QJsonObject QEXTMvvmJsonItemTagsConverter::to_json(const QEXTMvvmItemTags& item_tags)
{
    QJsonObject result;
    result[QEXTMvvmJsonItemFormatAssistant::defaultTagKey] = item_tags.defaultTag();

    QJsonArray containerArray;
    for (auto container : item_tags)
        containerArray.append(p_impl->m_container_converter->to_json(*container));
    result[QEXTMvvmJsonItemFormatAssistant::containerKey] = containerArray;

    return result;
}

//! Reconstructs QEXTMvvmItemTags from the content of JSON object. Can work in two modes:
//! + If QEXTMvvmItemTags is empty, all tags will be reconstructed as in JSON, and then populated
//!   with the content.
//! + If QEXTMvvmItemTags contains some tags already, they will be populated from JSON. in this
//!   case it will be assumed, that existing item's tags are matching JSON.

void QEXTMvvmJsonItemTagsConverter::from_json(const QJsonObject& json, QEXTMvvmItemTags& item_tags)
{
    static QEXTMvvmJsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemTags(json))
        throw std::runtime_error(
            "Error in QEXTMvvmJsonItemTagsConverter: given json object can't represent a QEXTMvvmItemTags.");

    if (!item_tags.tagsCount())
        p_impl->create_containers(json, item_tags);

    p_impl->populate_containers(json, item_tags);
}
