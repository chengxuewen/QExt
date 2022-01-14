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
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionItemContainer.h>
#include <qextMvvmSessionItemTags.h>
#include <qextMvvmTagRow.h>
#include <serialization/qextMvvmCompatibilityUtils.h>
#include <serialization/qextMvvmJsonItemTypes.h>
#include <serialization/qextMvvmJsonItemContainerConverter.h>
#include <serialization/qextMvvmJsonItemFormatAssistant.h>
#include <serialization/qextMvvmJsonTagInfoConverter.h>

using namespace ModelView;

struct QEXTMvvmJsonItemContainerConverter::JsonItemContainerConverterImpl {
    std::unique_ptr<QEXTMvvmJsonTagInfoConverterInterface> m_taginfo_converter;
    QEXTMvvmConverterCallbacks m_converter_callbacks;

    JsonItemContainerConverterImpl(QEXTMvvmConverterCallbacks callbacks = {})
        : m_converter_callbacks(std::move(callbacks))
    {
        m_taginfo_converter = make_unique<QEXTMvvmJsonTagInfoConverter>();
    }

    QJsonObject create_json(const QEXTMvvmSessionItem& item)
    {
        return m_converter_callbacks.m_create_json ? m_converter_callbacks.m_create_json(item)
                                                   : QJsonObject();
    }

    std::unique_ptr<QEXTMvvmSessionItem> create_item(const QJsonObject& json)
    {
        return m_converter_callbacks.m_create_item ? m_converter_callbacks.m_create_item(json)
                                                   : std::unique_ptr<QEXTMvvmSessionItem>();
    }

    void update_item(const QJsonObject& json, QEXTMvvmSessionItem* item)
    {
        if (m_converter_callbacks.m_update_item)
            m_converter_callbacks.m_update_item(json, item);
    }

    //! Update container from json content. Number of existing container items should match size
    //! of json array.
    void update_items(const QJsonObject& json, QEXTMvvmSessionItemContainer& container)
    {
        auto array = json[QEXTMvvmJsonItemFormatAssistant::itemsKey].toArray();
        if (array.size() != container.itemCount())
            throw std::runtime_error("Error in JsonItemContainerConverter: size is different");
        int index{0};
        for (const auto obj : array)
            update_item(obj.toObject(), container.itemAt(index++));
    }

    void create_items(const QJsonObject& json, QEXTMvvmSessionItemContainer& container)
    {
        for (const auto obj : json[QEXTMvvmJsonItemFormatAssistant::itemsKey].toArray()) {
            if (auto item = create_item(obj.toObject()); item)
                container.insertItem(item.release(), container.itemCount());
        }
    }

    //! Populates container with content reconstructed from JSON object. Container must be empty.

    void populate_container(const QJsonObject& json, QEXTMvvmSessionItemContainer& container)
    {
        if (!container.empty())
            throw std::runtime_error(
                "Error in JsonItemContainerConverter: container is not empty.");

        create_items(json, container);
    }

    //! Update container with content reconstructed from JSON object.
    //! It is assumed, that container has some items already created.

    void update_container(const QJsonObject& json, QEXTMvvmSessionItemContainer& container)
    {
        QEXTMvvmTagInfo tagInfo =
            m_taginfo_converter->from_json(json[QEXTMvvmJsonItemFormatAssistant::tagInfoKey].toObject());

        if (QEXTMvvmCompatibility::IsCompatibleSinglePropertyTag(container, tagInfo))
            update_items(json, container);

        else if (QEXTMvvmCompatibility::IsCompatibleGroupTag(container, tagInfo))
            update_items(json, container);

        else if (QEXTMvvmCompatibility::IsCompatibleUniversalTag(container, tagInfo))
            create_items(json, container);

        else
            throw std::runtime_error("Error in JsonItemContainerConverter: can't convert json");
    }
};

QEXTMvvmJsonItemContainerConverter::QEXTMvvmJsonItemContainerConverter(QEXTMvvmConverterCallbacks callbacks)
    : p_impl(make_unique<JsonItemContainerConverterImpl>(std::move(callbacks)))
{
}

QEXTMvvmJsonItemContainerConverter::~QEXTMvvmJsonItemContainerConverter() = default;

QJsonObject QEXTMvvmJsonItemContainerConverter::to_json(const QEXTMvvmSessionItemContainer& container)
{
    QJsonObject result;
    result[QEXTMvvmJsonItemFormatAssistant::tagInfoKey] =
        p_impl->m_taginfo_converter->to_json(container.tagInfo());

    QJsonArray itemArray;
    for (auto item : container)
        itemArray.append(p_impl->create_json(*item));
    result[QEXTMvvmJsonItemFormatAssistant::itemsKey] = itemArray;

    return result;
}

//! Reconstructs SessionItemContainer from the content of JSON object. Can work in two modes:
//! + If SessionItemContainer is empty, the content will be reconstructed from JSON
//! + If SessionItemContainer contains some items already, they will be populated from JSON.
//! Second mode is used when loading project from disk to allow back compatibility.

void QEXTMvvmJsonItemContainerConverter::from_json(const QJsonObject& json, QEXTMvvmSessionItemContainer& container)
{
    static QEXTMvvmJsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemContainer(json))
        throw std::runtime_error("Error in JsonItemContainerConverter: given JSON can't represent "
                                 "SessionItemContainer.");

    QEXTMvvmTagInfo tagInfo = p_impl->m_taginfo_converter->from_json(
        json[QEXTMvvmJsonItemFormatAssistant::tagInfoKey].toObject());

    if (tagInfo.name() != container.tagInfo().name())
        throw std::runtime_error("Error in JsonItemContainerConverter: attempt to update "
                                 "container from JSON representing another container.");

    if (container.empty())
        p_impl->populate_container(json, container);
    else
        p_impl->update_container(json, container);
}
