// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItem.h>
#include <qextMvvmItemContainer.h>
#include <qextMvvmItemTags.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmCompatibilityUtils.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemContainerConverter.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonTagInfoConverter.h>

#include <QJsonArray>
#include <QJsonObject>

struct QEXTMvvmJsonItemContainerConverter::JsonItemContainerConverterImpl {
    QScopedPointer<QEXTMvvmJsonTagInfoConverterInterface> m_taginfo_converter;
    QEXTMvvmConverterCallbacks m_converter_callbacks;

    JsonItemContainerConverterImpl(QEXTMvvmConverterCallbacks callbacks = {})
        : m_converter_callbacks(callbacks)
    {
        m_taginfo_converter.reset(new QEXTMvvmJsonTagInfoConverter);
    }

    QJsonObject create_json(const QEXTMvvmItem &item)
    {
        return m_converter_callbacks.m_create_json.isValid() ? m_converter_callbacks.m_create_json(item)
                                                             : QJsonObject();
    }

    QEXTMvvmItem *createItem(const QJsonObject &json)
    {
        return m_converter_callbacks.m_create_item.isValid() ? m_converter_callbacks.m_create_item(json)
                                                             : new QEXTMvvmItem;
    }

    void update_item(const QJsonObject& json, QEXTMvvmItem* item)
    {
        if (m_converter_callbacks.m_update_item.isValid())
            m_converter_callbacks.m_update_item(json, item);
    }

    //! Update container from json content. Number of existing container items should match size
    //! of json array.
    void update_items(const QJsonObject& json, QEXTMvvmItemContainer& container)
    {
        auto array = json[QEXTMvvmJsonItemFormatAssistant::itemsKey].toArray();
        if (array.size() != container.itemCount())
            throw std::runtime_error("Error in QEXTMvvmJsonItemContainerConverter: size is different");
        int index{0};
        for (const auto obj : array)
            update_item(obj.toObject(), container.itemAt(index++));
    }

    void create_items(const QJsonObject& json, QEXTMvvmItemContainer& container)
    {
        for (const auto obj : json[QEXTMvvmJsonItemFormatAssistant::itemsKey].toArray()) {
            if (auto item = createItem(obj.toObject()); item)
                container.insertItem(item, container.itemCount());
        }
    }

    //! Populates container with content reconstructed from JSON object. Container must be empty.

    void populate_container(const QJsonObject& json, QEXTMvvmItemContainer& container)
    {
        if (!container.isEmpty())
            throw std::runtime_error(
                    "Error in QEXTMvvmJsonItemContainerConverter: container is not empty.");

        create_items(json, container);
    }

    //! Update container with content reconstructed from JSON object.
    //! It is assumed, that container has some items already created.

    void update_container(const QJsonObject& json, QEXTMvvmItemContainer& container)
    {
        QEXTMvvmTagInfo tagInfo =
                m_taginfo_converter->fromJson(json[QEXTMvvmJsonItemFormatAssistant::tagInfoKey].toObject());

        if (Compatibility::IsCompatibleSinglePropertyTag(container, tagInfo))
            update_items(json, container);

        else if (Compatibility::IsCompatibleGroupTag(container, tagInfo))
            update_items(json, container);

        else if (Compatibility::IsCompatibleUniversalTag(container, tagInfo))
            create_items(json, container);

        else
            throw std::runtime_error("Error in QEXTMvvmJsonItemContainerConverter: can't convert json");
    }
};

QEXTMvvmJsonItemContainerConverter::QEXTMvvmJsonItemContainerConverter(QEXTMvvmConverterCallbacks callbacks)
    : p_impl(new JsonItemContainerConverterImpl(callbacks))
{
}

QEXTMvvmJsonItemContainerConverter::~QEXTMvvmJsonItemContainerConverter() = default;

QJsonObject QEXTMvvmJsonItemContainerConverter::to_json(const QEXTMvvmItemContainer& container)
{
    QJsonObject result;
    result[QEXTMvvmJsonItemFormatAssistant::tagInfoKey] =
            p_impl->m_taginfo_converter->toJson(container.tagInfo());

    QJsonArray itemArray;
    for (auto item : container)
        itemArray.append(p_impl->create_json(*item));
    result[QEXTMvvmJsonItemFormatAssistant::itemsKey] = itemArray;

    return result;
}

//! Reconstructs QEXTMvvmItemContainer from the content of JSON object. Can work in two modes:
//! + If QEXTMvvmItemContainer is empty, the content will be reconstructed from JSON
//! + If QEXTMvvmItemContainer contains some items already, they will be populated from JSON.
//! Second mode is used when loading project from disk to allow back compatibility.

void QEXTMvvmJsonItemContainerConverter::from_json(const QJsonObject& json, QEXTMvvmItemContainer& container)
{
    static QEXTMvvmJsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemContainer(json))
        throw std::runtime_error("Error in QEXTMvvmJsonItemContainerConverter: given JSON can't represent "
                                 "QEXTMvvmItemContainer.");

    QEXTMvvmTagInfo tagInfo = p_impl->m_taginfo_converter->fromJson(
                json[QEXTMvvmJsonItemFormatAssistant::tagInfoKey].toObject());

    if (tagInfo.name() != container.tagInfo().name())
        throw std::runtime_error("Error in QEXTMvvmJsonItemContainerConverter: attempt to update "
                                 "container from JSON representing another container.");

    if (container.isEmpty())
        p_impl->populate_container(json, container);
    else
        p_impl->update_container(json, container);
}
