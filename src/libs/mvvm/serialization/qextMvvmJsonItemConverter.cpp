#include <qextMvvmUniqueIdGenerator.h>
#include <qextMvvmItemFactoryInterface.h>
#include <qextMvvmItem.h>
#include <qextMvvmItemData.h>
#include <qextMvvmItemTags.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemConverter.h>
#include <qextMvvmJsonItemDataConverter.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonItemTagsConverter.h>

#include <QJsonArray>
#include <QJsonObject>

namespace
{

//! Creates converter for QEXTMvvmItemData/JSON.

QEXTMvvmJsonItemDataConverterInterface *createDataConverter(const ConverterMode& mode)
{
    return mode == ConverterMode::project ? QEXTMvvmJsonItemDataConverter::createProjectConverter()
                                          : QEXTMvvmJsonItemDataConverter::createCopyConverter();
}

} // namespace

struct QEXTMvvmJsonItemConverter::JsonItemConverterImpl {
    QEXTMvvmJsonItemConverter* m_self{nullptr};
    QScopedPointer<QEXTMvvmJsonItemDataConverterInterface> m_itemdata_converter;
    QScopedPointer<QEXTMvvmJsonItemTagsConverter> m_itemtags_converter;
    QEXTMvvmConverterContext m_context;

    JsonItemConverterImpl(QEXTMvvmJsonItemConverter* parent, const QEXTMvvmConverterContext& context)
        : m_self(parent), m_context(context)
    {
        //! Callback to convert QEXTMvvmItem to JSON object.
        auto create_json = [this](const QEXTMvvmItem& item) { return m_self->toJson(&item); };

        //! Callback to create QEXTMvvmItem from JSON object.
        auto create_item = [this](const QJsonObject& json) { return m_self->fromJson(json); };

        //! Callback to update QEXTMvvmItem from JSON object.
        auto update_item = [this](const QJsonObject& json, QEXTMvvmItem* item) {
            populate_item(json, *item);
        };

        QEXTMvvmConverterCallbacks callbacks{create_json, create_item, update_item};

        m_itemdata_converter.reset(createDataConverter(m_context.m_mode));
        m_itemtags_converter.reset(new QEXTMvvmJsonItemTagsConverter(callbacks));
    }

    const QEXTMvvmItemFactoryInterface* factory() { return m_context.m_factory; }

    void populate_item_data(const QJsonArray& json, QEXTMvvmItemData& item_data)
    {
        m_itemdata_converter->from_json(json, item_data);
    }

    void populate_item_tags(const QJsonObject& json, QEXTMvvmItemTags& item_tags)
    {
        m_itemtags_converter->from_json(json, item_tags);
    }

    void populate_item(const QJsonObject& json, QEXTMvvmItem& item)
    {
        auto modelType = json[QEXTMvvmJsonItemFormatAssistant::modelKey].toString();

        if (modelType != item.modelType())
            throw std::runtime_error("Item model mismatch");

        if (isRebuildItemDataAndTagFromJson(m_context.m_mode)) {
            item.setDataAndTags(new QEXTMvvmItemData, new QEXTMvvmItemTags);
        }

        populate_item_data(json[QEXTMvvmJsonItemFormatAssistant::itemDataKey].toArray(), *item.itemData());
        populate_item_tags(json[QEXTMvvmJsonItemFormatAssistant::itemTagsKey].toObject(), *item.itemTags());

        for (auto child : item.children())
            child->setParent(&item);

        if (isRegenerateIdWhenBackFromJson(m_context.m_mode))
            item.setData(QEXTMvvmUniqueIdGenerator::generate(), QEXTMvvmItem::Role_Identifier);
    }

    QJsonObject itemToJson(const QEXTMvvmItem& item) const
    {
        QJsonObject result;
        result[QEXTMvvmJsonItemFormatAssistant::modelKey] = item.modelType();
        result[QEXTMvvmJsonItemFormatAssistant::itemDataKey] =
            m_itemdata_converter->to_json(*item.itemData());
        result[QEXTMvvmJsonItemFormatAssistant::itemTagsKey] =
            m_itemtags_converter->to_json(*item.itemTags());

        return result;
    }
};

QEXTMvvmJsonItemConverter::QEXTMvvmJsonItemConverter(const QEXTMvvmConverterContext& context)
    : p_impl(new JsonItemConverterImpl(this, context))
{
}

QEXTMvvmJsonItemConverter::~QEXTMvvmJsonItemConverter()
{

}

QJsonObject QEXTMvvmJsonItemConverter::toJson(const QEXTMvvmItem* item) const
{
    return item ? p_impl->itemToJson(*item) : QJsonObject();
}

QEXTMvvmItem *QEXTMvvmJsonItemConverter::fromJson(const QJsonObject& json) const
{
    static QEXTMvvmJsonItemFormatAssistant assistant;

    if (!assistant.isSessionItem(json))
        throw std::runtime_error("JsonItemConverterV2::from_json() -> Error. Given json object "
                                 "can't represent a QEXTMvvmItem.");

    auto modelType = json[QEXTMvvmJsonItemFormatAssistant::modelKey].toString();
    auto result = p_impl->factory()->createItem(modelType);

    p_impl->populate_item(json, *result);

    return result;
}
