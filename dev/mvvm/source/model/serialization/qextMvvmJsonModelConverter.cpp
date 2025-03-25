// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmJsonModelConverter.h>
#include <qextMvvmItemConverterFactory.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <QJsonArray>
#include <QJsonObject>
#include <stdexcept>

using namespace ModelView;

namespace {
QExtUniquePointer<QExtMvvmJsonItemConverterInterface> CreateConverter(const QExtMvvmItemFactoryInterface* factory,
                                                            QExtMvvmConverterMode mode)
{
    if (mode == QExtMvvmConverterMode::clone)
        return qextMvvmCreateItemCloneConverter(factory);
    else if (mode == QExtMvvmConverterMode::copy)
        return qextMvvmCreateItemCopyConverter(factory);
    else if (mode == QExtMvvmConverterMode::project)
        return qextMvvmCreateItemProjectConverter(factory);
    else
        throw std::runtime_error("Error in QExtMvvmJsonModelConverter: unknown converter mode");
}

} // namespace

QExtMvvmJsonModelConverter::QExtMvvmJsonModelConverter(QExtMvvmConverterMode mode) : m_mode(mode) {}

QExtMvvmJsonModelConverter::~QExtMvvmJsonModelConverter() = default;

QJsonObject QExtMvvmJsonModelConverter::to_json(const QExtMvvmSessionModel& model) const
{
    QJsonObject result;

    if (!model.rootItem())
        throw std::runtime_error("JsonModel::to_json() -> Error. Model is not initialized.");

    result[QExtMvvmJsonItemFormatAssistant::sessionModelKey] = QString::fromStdString(model.modelType());

    QJsonArray itemArray;

    auto itemConverter = CreateConverter(model.factory(), m_mode);

    for (auto item : model.rootItem()->children())
        itemArray.append(itemConverter->to_json(item));

    result[QExtMvvmJsonItemFormatAssistant::itemsKey] = itemArray;

    return result;
}

void QExtMvvmJsonModelConverter::from_json(const QJsonObject& json, QExtMvvmSessionModel& model) const
{
    if (!model.rootItem())
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Model is not initialized.");

    QExtMvvmJsonItemFormatAssistant assistant;
    if (!assistant.isSessionModel(json))
        throw std::runtime_error("JsonModel::json_to_model() -> Error. Invalid json object.");

    if (json[QExtMvvmJsonItemFormatAssistant::sessionModelKey].toString()
        != QString::fromStdString(model.modelType()))
        throw std::runtime_error(
            "JsonModel::json_to_model() -> Unexpected model type '" + model.modelType()
            + "', json key '"
            + json[QExtMvvmJsonItemFormatAssistant::sessionModelKey].toString().toStdString() + "'");

    auto itemConverter = CreateConverter(model.factory(), m_mode);

    auto rebuild_root = [&json, &itemConverter](QExtMvvmSessionItem *parent) {
        for (const auto ref : json[QExtMvvmJsonItemFormatAssistant::itemsKey].toArray()) {
            parent->insertItem(itemConverter->from_json(ref.toObject()), QExtMvvmTagRow::append());
        }
    };
    model.clear(rebuild_root);
}
