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
#include <qextMvvmFactory.h>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemConverter.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonModelConverter.h>

#include <stdexcept>



namespace
{
    QEXTMvvmJsonItemConverterInterface *qextMvvmCreateConverter(const QEXTMvvmItemFactoryInterface *factory, ConverterMode mode)
    {
        if (mode == ConverterMode::clone)
        {
            return QEXTMvvmFactory::createItemCloneConverter(factory);
        }
        else if (mode == ConverterMode::copy)
        {
            return QEXTMvvmFactory::createItemCopyConverter(factory);
        }
        else if (mode == ConverterMode::project)
        {
            return QEXTMvvmFactory::createItemProjectConverter(factory);
        }
        else
        {
            throw std::runtime_error("Error in QEXTMvvmJsonModelConverter: unknown converter mode");
        }
    }

    void qextMvvmRebuildRoot(QEXTMvvmItem *parent)
    {
        json[QEXTMvvmJsonItemFormatAssistant::itemsKey].toArray();
        for (const auto ref : json[QEXTMvvmJsonItemFormatAssistant::itemsKey].toArray())
        {
            auto item = itemConverter->fromJson(ref.toObject());
            parent->insertItem(item, QEXTMvvmTagRow::append());
        }
    }

} // namespace

QEXTMvvmJsonModelConverter::QEXTMvvmJsonModelConverter(ConverterMode mode) : m_mode(mode) {}

QEXTMvvmJsonModelConverter::~QEXTMvvmJsonModelConverter() = default;

QJsonObject QEXTMvvmJsonModelConverter::toJson(const QEXTMvvmModel &model) const
{
    QJsonObject result;

    if (!model.rootItem())
    {
        throw std::runtime_error("JsonModel::to_json() -> Error. Model is not initialized.");
    }

    result[QEXTMvvmJsonItemFormatAssistant::sessionModelKey] = model.modelType();

    QJsonArray itemArray;

    auto itemConverter = qextMvvmCreateConverter(model.factory(), m_mode);

    for (auto item : model.rootItem()->children())
    {
        itemArray.append(itemConverter->toJson(item));
    }

    result[QEXTMvvmJsonItemFormatAssistant::itemsKey] = itemArray;

    return result;
}

void QEXTMvvmJsonModelConverter::fromJson(const QJsonObject &json, QEXTMvvmModel &model) const
{
//    if (!model.rootItem())
//    {
//        throw std::runtime_error("JsonModel::json_to_model() -> Error. Model is not initialized.");
//    }

//    QEXTMvvmJsonItemFormatAssistant assistant;
//    if (!assistant.isSessionModel(json))
//    {
//        throw std::runtime_error("JsonModel::json_to_model() -> Error. Invalid json object.");
//    }

//    if (json[QEXTMvvmJsonItemFormatAssistant::sessionModelKey].toString() != model.modelType())
//        throw std::runtime_error(
//            "JsonModel::json_to_model() -> Unexpected model type '" + model.modelType().toStdString()
//            + "', json key '"
//            + json[QEXTMvvmJsonItemFormatAssistant::sessionModelKey].toString().toStdString() + "'");

//    auto itemConverter = qextMvvmCreateConverter(model.factory(), m_mode);

//    auto rebuild_root = [&json, &itemConverter](auto parent)
//    {
//        for (const auto ref : json[QEXTMvvmJsonItemFormatAssistant::itemsKey].toArray())
//        {
//            auto item = itemConverter->fromJson(ref.toObject());
//            parent->insertItem(item, QEXTMvvmTagRow::append());
//        }
//    };
//    model.clear(rebuild_root);
}
