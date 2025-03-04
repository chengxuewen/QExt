// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/serialization/jsonitemconverter.h"
#include "model/core/uniqueidgenerator.h"
#include "model/interfaces/itemfactoryinterface.h"
#include "model/model/sessionitem.h"
#include "model/model/sessionitemdata.h"
#include "model/model/sessionitemtags.h"
#include "model/serialization/jsonitem_types.h"
#include "model/serialization/jsonitemdataconverter.h"
#include "model/serialization/jsonitemformatassistant.h"
#include "model/serialization/jsonitemtagsconverter.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace ModelView;

namespace {

//! Creates converter for QExtMvvmSessionItemData/JSON.

QExtUniquePointer<QExtMvvmJsonItemDataConverterInterface> createDataConverter(const QExtMvvmConverterMode& mode)
{
    return mode == QExtMvvmConverterMode::project ? QExtMvvmJsonItemDataConverter::createProjectConverter()
                                          : QExtMvvmJsonItemDataConverter::createCopyConverter();
}

} // namespace

struct QExtMvvmJsonItemConverter::JsonItemConverterImpl {
    QExtMvvmJsonItemConverter* m_self{nullptr};
    QExtUniquePointer<QExtMvvmJsonItemDataConverterInterface> m_itemdata_converter;
    QExtUniquePointer<QExtMvvmJsonItemTagsConverter> m_itemtags_converter;
    QExtMvvmConverterContext m_context;

    JsonItemConverterImpl(QExtMvvmJsonItemConverter* parent, const QExtMvvmConverterContext& context)
        : m_self(parent), m_context(context)
    {
        //! Callback to convert QExtMvvmSessionItem to JSON object.
        auto create_json = [this](const QExtMvvmSessionItem& item) { return m_self->to_json(&item); };

        //! Callback to create QExtMvvmSessionItem from JSON object.
        auto create_item = [this](const QJsonObject& json) { return m_self->from_json(json); };

        //! Callback to update QExtMvvmSessionItem from JSON object.
        auto update_item = [this](const QJsonObject& json, QExtMvvmSessionItem* item) {
            populate_item(json, *item);
        };

        QExtMvvmConverterCallbacks callbacks{create_json, create_item, update_item};

        m_itemdata_converter = createDataConverter(m_context.m_mode);
        m_itemtags_converter = qextMakeUnique<QExtMvvmJsonItemTagsConverter>(callbacks);
    }

    const QExtMvvmItemFactoryInterface* factory() { return m_context.m_factory; }

    void populate_item_data(const QJsonArray& json, QExtMvvmSessionItemData& item_data)
    {
        m_itemdata_converter->from_json(json, item_data);
    }

    void populate_item_tags(const QJsonObject& json, QExtMvvmSessionItemTags& item_tags)
    {
        m_itemtags_converter->from_json(json, item_tags);
    }

    void populate_item(const QJsonObject& json, QExtMvvmSessionItem& item)
    {
        auto modelType = json[QExtMvvmJsonItemFormatAssistant::modelKey].toString().toStdString();

        if (modelType != item.modelType())
            throw std::runtime_error("Item model mismatch");

        if (isRebuildItemDataAndTagFromJson(m_context.m_mode)) {
            item.setDataAndTags(qextMakeUnique<QExtMvvmSessionItemData>(),
                                qextMakeUnique<QExtMvvmSessionItemTags>());
        }

        populate_item_data(json[QExtMvvmJsonItemFormatAssistant::itemDataKey].toArray(), *item.itemData());
        populate_item_tags(json[QExtMvvmJsonItemFormatAssistant::itemTagsKey].toObject(), *item.itemTags());

        for (auto child : item.children())
            child->setParent(&item);

        if (isRegenerateIdWhenBackFromJson(m_context.m_mode))
            item.setData(QExtMvvmUniqueIdGenerator::generate(), ItemDataRole::IDENTIFIER);
    }

    QJsonObject item_to_json(const QExtMvvmSessionItem& item) const
    {
        QJsonObject result;
        result[QExtMvvmJsonItemFormatAssistant::modelKey] = QString::fromStdString(item.modelType());
        result[QExtMvvmJsonItemFormatAssistant::itemDataKey] =
            m_itemdata_converter->to_json(*item.itemData());
        result[QExtMvvmJsonItemFormatAssistant::itemTagsKey] =
            m_itemtags_converter->to_json(*item.itemTags());

        return result;
    }
};

QExtMvvmJsonItemConverter::QExtMvvmJsonItemConverter(const QExtMvvmConverterContext& context)
    : p_impl(qextMakeUnique<JsonItemConverterImpl>(this, context))
{
}

QExtMvvmJsonItemConverter::~QExtMvvmJsonItemConverter() = default;

QJsonObject QExtMvvmJsonItemConverter::to_json(const QExtMvvmSessionItem* item) const
{
    return item ? p_impl->item_to_json(*item) : QJsonObject();
}

QExtUniquePointer<QExtMvvmSessionItem> QExtMvvmJsonItemConverter::from_json(const QJsonObject& json) const
{
    static QExtMvvmJsonItemFormatAssistant assistant;

    if (!assistant.isSessionItem(json))
        throw std::runtime_error("JsonItemConverterV2::from_json() -> Error. Given json object "
                                 "can't represent a QExtMvvmSessionItem.");

    auto modelType = json[QExtMvvmJsonItemFormatAssistant::modelKey].toString().toStdString();
    auto result = p_impl->factory()->createItem(modelType);

    p_impl->populate_item(json, *result);

    return result;
}
