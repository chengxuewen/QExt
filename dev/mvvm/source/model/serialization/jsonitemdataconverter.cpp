// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/serialization/jsonitemdataconverter.h"
#include "model/model/mvvm_types.h"
#include "model/model/sessionitemdata.h"
#include "model/serialization/jsonitemformatassistant.h"
#include "model/serialization/jsonvariantconverter.h"
#include <QJsonArray>
#include <QJsonObject>
#include <set>
#include <stdexcept>

using namespace ModelView;

namespace {
QJsonValue keyValue(const QJsonValue& parent_value, const QString& key)
{
    const QJsonObject& parent_object = parent_value.toObject();
    return parent_object.value(key);
}
} // namespace

QExtMvvmJsonItemDataConverter::QExtMvvmJsonItemDataConverter(accept_strategy_t to_json_accept,
                                             accept_strategy_t from_json_accept)
    : m_to_json_accept(to_json_accept)
    , m_from_json_accept(from_json_accept)
    , m_variant_converter(qextMakeUnique<QExtMvvmJsonVariantConverter>())
{
}

QExtMvvmJsonItemDataConverter::~QExtMvvmJsonItemDataConverter() = default;

QJsonArray QExtMvvmJsonItemDataConverter::to_json(const QExtMvvmSessionItemData& data)
{
    QJsonArray result;

    for (const auto& x : data) {
        QJsonObject object;
        if (isRoleToJson(x.m_role)) {
            object[QExtMvvmJsonItemFormatAssistant::roleKey] = x.m_role;
            object[QExtMvvmJsonItemFormatAssistant::variantKey] = m_variant_converter->get_json(x.m_data);
            result.append(object);
        }
    }

    return result;
}

//! Updates existing data with JSON content.

void QExtMvvmJsonItemDataConverter::from_json(const QJsonArray& object, QExtMvvmSessionItemData& data)
{
    static QExtMvvmJsonItemFormatAssistant assistant;
    auto persistent_data = qextMakeUnique<QExtMvvmSessionItemData>();

    for (const auto& x : object) {
        if (!assistant.isSessionItemData(x.toObject()))
            throw std::runtime_error("JsonItemData::get_data() -> Invalid json object.");
        auto role = keyValue(x, QExtMvvmJsonItemFormatAssistant::roleKey).toInt();
        auto variant = m_variant_converter->get_variant(
            keyValue(x, QExtMvvmJsonItemFormatAssistant::variantKey).toObject());
        if (isRoleFromJson(role))
            persistent_data->setData(variant, role);
    }

    auto runtime_roles = data.roles();
    auto persistent_roles = persistent_data->roles();

    std::set<int> roles(runtime_roles.begin(), runtime_roles.end());
    roles.insert(persistent_roles.begin(), persistent_roles.end());

    for (auto role : roles) {
        // all roles existing in `persistent` will be taken from there
        if (persistent_data->hasData(role))
            data.setData(persistent_data->data(role), role);
    }
}

//! Creates JSON data converter intended for simple data copying. Nothing is filtered out.

QExtUniquePointer<QExtMvvmJsonItemDataConverterInterface> QExtMvvmJsonItemDataConverter::createCopyConverter()
{
    return qextMakeUnique<QExtMvvmJsonItemDataConverter>();
}

//! Creates JSON data converter intended for project saving. Only IDENTIFIER and DATA gous to/from
//! JSON.

QExtUniquePointer<QExtMvvmJsonItemDataConverterInterface> QExtMvvmJsonItemDataConverter::createProjectConverter()
{
    auto accept_roles = [](int role) {
        return role == ItemDataRole::IDENTIFIER || role == ItemDataRole::DATA;
    };
    return qextMakeUnique<QExtMvvmJsonItemDataConverter>(accept_roles, accept_roles);
}

//! Returns true if given role should be saved in json object.

bool QExtMvvmJsonItemDataConverter::isRoleToJson(int role) const
{
    return m_to_json_accept ? m_to_json_accept(role) : true;
}

//! Returns true if given role should be parsed from json object.

bool QExtMvvmJsonItemDataConverter::isRoleFromJson(int role) const
{
    return m_from_json_accept ? m_from_json_accept(role) : true;
}
