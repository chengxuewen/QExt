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
#include <qextMvvmItemConverterFactory.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemConverter.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonModelConverter.h>
#include <stdexcept>

using namespace ModelView;

namespace
{
std::unique_ptr<QEXTMvvmJsonItemConverterInterface> CreateConverter(const QEXTMvvmItemFactoryInterface* factory,
                                                            ConverterMode mode)
{
    if (mode == ConverterMode::clone)
        return CreateItemCloneConverter(factory);
    else if (mode == ConverterMode::copy)
        return CreateItemCopyConverter(factory);
    else if (mode == ConverterMode::project)
        return CreateItemProjectConverter(factory);
    else
        throw std::runtime_error("Error in QEXTMvvmJsonModelConverter: unknown converter mode");
}

} // namespace

QEXTMvvmJsonModelConverter::QEXTMvvmJsonModelConverter(ConverterMode mode) : m_mode(mode) {}

QEXTMvvmJsonModelConverter::~QEXTMvvmJsonModelConverter() = default;

QJsonObject QEXTMvvmJsonModelConverter::to_json(const QEXTMvvmSessionModel& model) const
{
    QJsonObject result;

    if (!model.rootItem())
        throw std::runtime_error("JsonModel::to_json() -> Error. Model is not initialized.");

    result[QEXTMvvmJsonItemFormatAssistant::sessionModelKey] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

    auto itemConverter = CreateConverter(model.factory(), m_mode);

    for (auto item : model.rootItem()->children())
        itemArray.append(itemConverter->to_json(item));

    result[QEXTMvvmJsonItemFormatAssistant::itemsKey] = itemArray;

    return result;
}

void QEXTMvvmJsonModelConverter::from_json(const QJsonObject& json, QEXTMvvmSessionModel& model) const
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Model is not initialized.");

    QEXTMvvmJsonItemFormatAssistant assistant;
    if (!assistant.isSessionModel(json))
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Invalid json object.");

    if (json[QEXTMvvmJsonItemFormatAssistant::sessionModelKey].toString()
        != QString::fromStdString(model.modelType()))
        throw std::runtime_error(
            "JsonModel::json_to_model() -> Unexpected model type '" + model.modelType()
            + "', json key '"
            + json[QEXTMvvmJsonItemFormatAssistant::sessionModelKey].toString().toStdString() + "'");

    auto itemConverter = CreateConverter(model.factory(), m_mode);

    auto rebuild_root = [&json, &itemConverter](auto parent) {
        for (const auto ref : json[QEXTMvvmJsonItemFormatAssistant::itemsKey].toArray()) {
            auto item = itemConverter->from_json(ref.toObject());
            parent->insertItem(item.release(), QEXTMvvmTagRow::append());
        }
    };
    model.clear(rebuild_root);
}
