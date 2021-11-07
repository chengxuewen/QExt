#include <qextMvvmConstants.h>
#include <qextMvvmItemData.h>
#include <qextMvvmJsonItemDataConverter.h>
#include <qextMvvmJsonItemFormatAssistant.h>
#include <qextMvvmJsonVariantConverter.h>
#include <qextMvvmItem.h>

#include <QJsonArray>
#include <QJsonObject>

#include <set>
#include <stdexcept>



namespace
{
QJsonValue keyValue(const QJsonValue& parent_value, const QString& key)
{
    const QJsonObject& parent_object = parent_value.toObject();
    return parent_object.value(key);
}
} // namespace

QEXTMvvmJsonItemDataConverter::QEXTMvvmJsonItemDataConverter(accept_strategy_t to_json_accept,
                                             accept_strategy_t from_json_accept)
    : m_to_json_accept(to_json_accept)
    , m_from_json_accept(from_json_accept)
    , m_variant_converter(new QEXTMvvmJsonVariantConverter)
{
}

QEXTMvvmJsonItemDataConverter::~QEXTMvvmJsonItemDataConverter() = default;

QJsonArray QEXTMvvmJsonItemDataConverter::to_json(const QEXTMvvmItemData& data)
{
    QJsonArray result;

    for (const auto& x : data) {
        QJsonObject object;
        if (isRoleToJson(x.m_role)) {
            object[QEXTMvvmJsonItemFormatAssistant::roleKey] = x.m_role;
            object[QEXTMvvmJsonItemFormatAssistant::variantKey] = m_variant_converter->getJson(x.m_data);
            result.append(object);
        }
    }

    return result;
}

//! Updates existing data with JSON content.

void QEXTMvvmJsonItemDataConverter::from_json(const QJsonArray& object, QEXTMvvmItemData& data)
{
    static QEXTMvvmJsonItemFormatAssistant assistant;
    auto persistent_data = new QEXTMvvmItemData;

    for (const auto& x : object) {
        if (!assistant.isSessionItemData(x.toObject()))
            throw std::runtime_error("JsonItemData::get_data() -> Invalid json object.");
        auto role = keyValue(x, QEXTMvvmJsonItemFormatAssistant::roleKey).toInt();
        auto variant = m_variant_converter->getVariant(
            keyValue(x, QEXTMvvmJsonItemFormatAssistant::variantKey).toObject());
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

QEXTMvvmJsonItemDataConverterInterface *QEXTMvvmJsonItemDataConverter::createCopyConverter()
{
    return new QEXTMvvmJsonItemDataConverter;
}

//! Creates JSON data converter intended for project saving. Only IDENTIFIER and DATA gous to/from
//! JSON.

QEXTMvvmJsonItemDataConverterInterface *QEXTMvvmJsonItemDataConverter::createProjectConverter()
{
    accept_strategy_t accept_roles = [](int role) {
        return role == QEXTMvvmItem::Role_Identifier || role == QEXTMvvmItem::Role_Data;
    };
    return new QEXTMvvmJsonItemDataConverter(accept_roles, accept_roles);
}

//! Returns true if given role should be saved in json object.

bool QEXTMvvmJsonItemDataConverter::isRoleToJson(int role) const
{
    return m_to_json_accept.isValid() ? m_to_json_accept(role) : true;
}

//! Returns true if given role should be parsed from json object.

bool QEXTMvvmJsonItemDataConverter::isRoleFromJson(int role) const
{
    return m_from_json_accept.isValid() ? m_from_json_accept(role) : true;
}
