// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmJsonItemContainerConverter.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionItemContainer.h>
#include <qextMvvmCompatibilityUtils.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonTagInfoConverter.h>
#include <QJsonArray>
#include <QJsonObject>

using namespace ModelView;

struct QExtMvvmJsonItemContainerConverter::JsonItemContainerConverterImpl {
    QExtUniquePointer<QExtMvvmJsonTagInfoConverterInterface> m_taginfo_converter;
    QExtMvvmConverterCallbacks m_converter_callbacks;

    JsonItemContainerConverterImpl(QExtMvvmConverterCallbacks callbacks = {})
        : m_converter_callbacks(std::move(callbacks))
    {
        m_taginfo_converter = qextMakeUnique<QExtMvvmJsonTagInfoConverter>();
    }

    QJsonObject create_json(const QExtMvvmSessionItem& item)
    {
        return m_converter_callbacks.m_create_json ? m_converter_callbacks.m_create_json(item)
                                                   : QJsonObject();
    }

    QExtUniquePointer<QExtMvvmSessionItem> create_item(const QJsonObject& json)
    {
        return m_converter_callbacks.m_create_item ? m_converter_callbacks.m_create_item(json)
                                                   : QExtUniquePointer<QExtMvvmSessionItem>();
    }

    void update_item(const QJsonObject& json, QExtMvvmSessionItem* item)
    {
        if (m_converter_callbacks.m_update_item)
            m_converter_callbacks.m_update_item(json, item);
    }

    //! Update container from json content. Number of existing container items should match size
    //! of json array.
    void update_items(const QJsonObject& json, QExtMvvmSessionItemContainer& container)
    {
        auto array = json[QExtMvvmJsonItemFormatAssistant::itemsKey].toArray();
        if (array.size() != container.itemCount())
            throw std::runtime_error("Error in QExtMvvmJsonItemContainerConverter: size is different");
        int index{0};
        for (const auto obj : array)
            update_item(obj.toObject(), container.itemAt(index++));
    }

    void create_items(const QJsonObject& json, QExtMvvmSessionItemContainer& container)
    {
        for (const auto obj : json[QExtMvvmJsonItemFormatAssistant::itemsKey].toArray()) {
            if (auto item = create_item(obj.toObject()); item)
                container.insertItem(item.release(), container.itemCount());
        }
    }

    //! Populates container with content reconstructed from JSON object. Container must be empty.

    void populate_container(const QJsonObject& json, QExtMvvmSessionItemContainer& container)
    {
        if (!container.empty())
            throw std::runtime_error(
                "Error in QExtMvvmJsonItemContainerConverter: container is not empty.");

        create_items(json, container);
    }

    //! Update container with content reconstructed from JSON object.
    //! It is assumed, that container has some items already created.

    void update_container(const QJsonObject& json, QExtMvvmSessionItemContainer& container)
    {
        QExtMvvmTagInfo tagInfo =
            m_taginfo_converter->from_json(json[QExtMvvmJsonItemFormatAssistant::tagInfoKey].toObject());

        if (Compatibility::IsCompatibleSinglePropertyTag(container, tagInfo))
            update_items(json, container);

        else if (Compatibility::IsCompatibleGroupTag(container, tagInfo))
            update_items(json, container);

        else if (Compatibility::IsCompatibleUniversalTag(container, tagInfo))
            create_items(json, container);

        else
            throw std::runtime_error("Error in QExtMvvmJsonItemContainerConverter: can't convert json");
    }
};

QExtMvvmJsonItemContainerConverter::QExtMvvmJsonItemContainerConverter(QExtMvvmConverterCallbacks callbacks)
    : p_impl(qextMakeUnique<JsonItemContainerConverterImpl>(std::move(callbacks)))
{
}

QExtMvvmJsonItemContainerConverter::~QExtMvvmJsonItemContainerConverter() = default;

QJsonObject QExtMvvmJsonItemContainerConverter::to_json(const QExtMvvmSessionItemContainer& container)
{
    QJsonObject result;
    result[QExtMvvmJsonItemFormatAssistant::tagInfoKey] =
        p_impl->m_taginfo_converter->to_json(container.tagInfo());

    QJsonArray itemArray;
    for (auto item : container)
        itemArray.append(p_impl->create_json(*item));
    result[QExtMvvmJsonItemFormatAssistant::itemsKey] = itemArray;

    return result;
}

//! Reconstructs QExtMvvmSessionItemContainer from the content of JSON object. Can work in two modes:
//! + If QExtMvvmSessionItemContainer is empty, the content will be reconstructed from JSON
//! + If QExtMvvmSessionItemContainer contains some items already, they will be populated from JSON.
//! Second mode is used when loading project from disk to allow back compatibility.

void QExtMvvmJsonItemContainerConverter::from_json(const QJsonObject& json, QExtMvvmSessionItemContainer& container)
{
    static QExtMvvmJsonItemFormatAssistant assistant;

    if (!assistant.isSessionItemContainer(json))
        throw std::runtime_error("Error in QExtMvvmJsonItemContainerConverter: given JSON can't represent "
                                 "QExtMvvmSessionItemContainer.");

    QExtMvvmTagInfo tagInfo = p_impl->m_taginfo_converter->from_json(
        json[QExtMvvmJsonItemFormatAssistant::tagInfoKey].toObject());

    if (tagInfo.name() != container.tagInfo().name())
        throw std::runtime_error("Error in QExtMvvmJsonItemContainerConverter: attempt to update "
                                 "container from JSON representing another container.");

    if (container.empty())
        p_impl->populate_container(json, container);
    else
        p_impl->update_container(json, container);
}
