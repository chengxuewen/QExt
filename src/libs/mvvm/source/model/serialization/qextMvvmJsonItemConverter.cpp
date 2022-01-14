// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmUniqueIdGenerator.h>
#include <qextMvvmItemFactoryInterface.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionItemData.h>
#include <qextMvvmSessionItemTags.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemConverter.h>
#include <qextMvvmJsonItemDataConverter.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonItemTagsConverter.h>

#include <QJsonArray>
#include <QJsonObject>

using namespace ModelView;

namespace
{

//! Creates converter for SessionItemData/JSON.

std::unique_ptr<QEXTMvvmJsonItemDataConverterInterface> createDataConverter(const ConverterMode& mode)
{
    return mode == ConverterMode::project ? QEXTMvvmJsonItemDataConverter::createProjectConverter()
                                          : QEXTMvvmJsonItemDataConverter::createCopyConverter();
}

} // namespace

struct QEXTMvvmJsonItemConverter::JsonItemConverterImpl {
    QEXTMvvmJsonItemConverter* m_self{nullptr};
    std::unique_ptr<QEXTMvvmJsonItemDataConverterInterface> m_itemdata_converter;
    std::unique_ptr<QEXTMvvmJsonItemTagsConverter> m_itemtags_converter;
    QEXTMvvmConverterContext m_context;

    JsonItemConverterImpl(QEXTMvvmJsonItemConverter* parent, const QEXTMvvmConverterContext& context)
        : m_self(parent), m_context(context)
    {
        //! Callback to convert QEXTMvvmSessionItem to JSON object.
        auto create_json = [this](const QEXTMvvmSessionItem& item) { return m_self->to_json(&item); };

        //! Callback to create QEXTMvvmSessionItem from JSON object.
        auto create_item = [this](const QJsonObject& json) { return m_self->from_json(json); };

        //! Callback to update QEXTMvvmSessionItem from JSON object.
        auto update_item = [this](const QJsonObject& json, QEXTMvvmSessionItem* item) {
            populate_item(json, *item);
        };

        QEXTMvvmConverterCallbacks callbacks{create_json, create_item, update_item};

        m_itemdata_converter = createDataConverter(m_context.m_mode);
        m_itemtags_converter = make_unique<QEXTMvvmJsonItemTagsConverter>(callbacks);
    }

    const QEXTMvvmItemFactoryInterface* factory() { return m_context.m_factory; }

    void populate_item_data(const QJsonArray& json, QEXTMvvmSessionItemData& item_data)
    {
        m_itemdata_converter->from_json(json, item_data);
    }

    void populate_item_tags(const QJsonObject& json, QEXTMvvmSessionItemTags& item_tags)
    {
        m_itemtags_converter->from_json(json, item_tags);
    }

    void populate_item(const QJsonObject& json, QEXTMvvmSessionItem& item)
    {
        auto modelType = json[QEXTMvvmJsonItemFormatAssistant::modelKey].toString().toStdString();

        if (modelType != item.modelType())
            throw std::runtime_error("Item model mismatch");

        if (isRebuildItemDataAndTagFromJson(m_context.m_mode)) {
            item.setDataAndTags(make_unique<QEXTMvvmSessionItemData>(),
                                make_unique<QEXTMvvmSessionItemTags>());
        }

        populate_item_data(json[QEXTMvvmJsonItemFormatAssistant::itemDataKey].toArray(), *item.itemData());
        populate_item_tags(json[QEXTMvvmJsonItemFormatAssistant::itemTagsKey].toObject(), *item.itemTags());

        for (auto child : item.children())
            child->setParent(&item);

        if (isRegenerateIdWhenBackFromJson(m_context.m_mode))
            item.setData(QEXTMvvmUniqueIdGenerator::generate(), ItemDataRole::IDENTIFIER);
    }

    QJsonObject item_to_json(const QEXTMvvmSessionItem& item) const
    {
        QJsonObject result;
        result[QEXTMvvmJsonItemFormatAssistant::modelKey] = QString::fromStdString(item.modelType());
        result[QEXTMvvmJsonItemFormatAssistant::itemDataKey] =
            m_itemdata_converter->to_json(*item.itemData());
        result[QEXTMvvmJsonItemFormatAssistant::itemTagsKey] =
            m_itemtags_converter->to_json(*item.itemTags());

        return result;
    }
};

QEXTMvvmJsonItemConverter::QEXTMvvmJsonItemConverter(const QEXTMvvmConverterContext& context)
    : p_impl(make_unique<JsonItemConverterImpl>(this, context))
{
}

QEXTMvvmJsonItemConverter::~QEXTMvvmJsonItemConverter() = default;

QJsonObject QEXTMvvmJsonItemConverter::to_json(const QEXTMvvmSessionItem* item) const
{
    return item ? p_impl->item_to_json(*item) : QJsonObject();
}

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmJsonItemConverter::from_json(const QJsonObject& json) const
{
    static QEXTMvvmJsonItemFormatAssistant assistant;

    if (!assistant.isSessionItem(json))
        throw std::runtime_error("JsonItemConverterV2::from_json() -> Error. Given json object "
                                 "can't represent a QEXTMvvmSessionItem.");

    auto modelType = json[QEXTMvvmJsonItemFormatAssistant::modelKey].toString().toStdString();
    auto result = p_impl->factory()->createItem(modelType);

    p_impl->populate_item(json, *result);

    return result;
}
