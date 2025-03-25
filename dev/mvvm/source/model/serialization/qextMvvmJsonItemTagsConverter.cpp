// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmJsonItemTagsConverter.h>
#include <qextMvvmSessionItemTags.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemContainerConverter.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonTagInfoConverter.h>
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmJsonItemTagsConverter::JsonItemTagsConverterImpl {
    QExtUniquePointer<QExtMvvmJsonItemContainerConverter> m_container_converter;
    QExtUniquePointer<QExtMvvmJsonTagInfoConverterInterface> m_taginfo_converter;

    JsonItemTagsConverterImpl(QExtMvvmConverterCallbacks callbacks = {})
    {
        m_container_converter = qextMakeUnique<QExtMvvmJsonItemContainerConverter>(std::move(callbacks));
        m_taginfo_converter = qextMakeUnique<QExtMvvmJsonTagInfoConverter>();
    }

    //! Create containers from JSON. QExtMvvmSessionItemTags should be empty.

    void create_containers(const QJsonObject& json, QExtMvvmSessionItemTags& item_tags)
    {
        if (item_tags.tagsCount())
            throw std::runtime_error("Error in QExtMvvmJsonItemTagsConverter: no containers expected.");

        auto default_tag = json[QExtMvvmJsonItemFormatAssistant::defaultTagKey].toString().toStdString();
        item_tags.setDefaultTag(default_tag);

        auto container_array = json[QExtMvvmJsonItemFormatAssistant::containerKey].toArray();

        for (const auto ref : container_array) {
            QJsonObject json_container = ref.toObject();
            QJsonObject json_taginfo =
                json_container[QExtMvvmJsonItemFormatAssistant::tagInfoKey].toObject();
            QExtMvvmTagInfo tagInfo = m_taginfo_converter->from_json(json_taginfo);
            item_tags.registerTag(tagInfo);
        }
    }

    //! Populate containers from JSON. Container must be already created.

    void populate_containers(const QJsonObject& json, QExtMvvmSessionItemTags& item_tags)
    {
        auto container_array = json[QExtMvvmJsonItemFormatAssistant::containerKey].toArray();

        if (container_array.size() != item_tags.tagsCount())
            throw std::runtime_error("Error in QExtMvvmJsonItemTagsConverter: mismatch in number of tags");

        auto default_tag = json[QExtMvvmJsonItemFormatAssistant::defaultTagKey].toString().toStdString();
        if (default_tag != item_tags.defaultTag())
            throw std::runtime_error("Error in QExtMvvmJsonItemTagsConverter: default tag mismatch.");

        int index(0);
        for (const auto container_ref : container_array)
            m_container_converter->from_json(container_ref.toObject(), item_tags.at(index++));
    }
};

QExtMvvmJsonItemTagsConverter::QExtMvvmJsonItemTagsConverter(QExtMvvmConverterCallbacks callbacks)
    : p_impl(qextMakeUnique<JsonItemTagsConverterImpl>(callbacks))
{
}

QExtMvvmJsonItemTagsConverter::~QExtMvvmJsonItemTagsConverter() = default;

QJsonObject QExtMvvmJsonItemTagsConverter::to_json(const QExtMvvmSessionItemTags& item_tags)
{
    QJsonObject result;
    result[QExtMvvmJsonItemFormatAssistant::defaultTagKey] = QString::fromStdString(item_tags.defaultTag());

    QJsonArray containerArray;
    for (auto container : item_tags)
        containerArray.append(p_impl->m_container_converter->to_json(*container));
    result[QExtMvvmJsonItemFormatAssistant::containerKey] = containerArray;

    return result;
}

//! Reconstructs QExtMvvmSessionItemTags from the content of JSON object. Can work in two modes:
//! + If QExtMvvmSessionItemTags is empty, all tags will be reconstructed as in JSON, and then populated
//!   with the content.
//! + If QExtMvvmSessionItemTags contains some tags already, they will be populated from JSON. in this
//!   case it will be assumed, that existing item's tags are matching JSON.

void QExtMvvmJsonItemTagsConverter::from_json(const QJsonObject& json, QExtMvvmSessionItemTags& item_tags)
{
    static QExtMvvmJsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemTags(json))
        throw std::runtime_error(
            "Error in QExtMvvmJsonItemTagsConverter: given json object can't represent a QExtMvvmSessionItemTags.");

    if (!item_tags.tagsCount())
        p_impl->create_containers(json, item_tags);

    p_impl->populate_containers(json, item_tags);
}
