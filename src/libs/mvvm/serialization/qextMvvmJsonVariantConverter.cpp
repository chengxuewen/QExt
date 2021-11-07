#include <qextMvvmComboProperty.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmConstants.h>
#include <qextMvvmJsonUtils.h>
#include <qextMvvmJsonVariantConverter.h>
#include <qextMvvmRealLimits.h>
#include <qextMvvmUtils.h>

#include <QJsonArray>
#include <QJsonObject>

#include <stdexcept>

namespace
{
    const QString QEXT_MVVM_VARIANT_TYPE_KEY = "type";
    const QString QEXT_MVVM_VARIANT_VALUE_KEY = "value";
    const QString QEXT_MVVM_COMBO_VALUE_KEY = "values";
    const QString QEXT_MVVM_COMBO_SELECTION_KEY = "selections";
    const QString QEXT_MVVM_EXTPROPERTY_TEXT_KEY = "text";
    const QString QEXT_MVVM_EXTPROPERTY_COLOR_KEY = "color";
    const QString QEXT_MVVM_EXTPROPERTY_ID_KEY = "identifier";
    const QString QEXT_MVVM_REALLIMITS_TEXT_KEY = "text";
    const QString QEXT_MVVM_REALLIMITS_MIN_KEY = "min";
    const QString QEXT_MVVM_REALLIMITS_MAX_KEY = "max";

    QStringList qextMvvmExpectedVariantKeys();

    QJsonObject qextMvvmFromInvalid(const QVariant &variant);
    QVariant qextMvvmToInvalid(const QJsonObject &object);

    QJsonObject qextMvvmFromBool(const QVariant &variant);
    QVariant qextMvvmToBool(const QJsonObject &object);

    QJsonObject qextMvvmFromInt(const QVariant &variant);
    QVariant qextMvvmToInt(const QJsonObject &object);

    QJsonObject qextMvvmFromString(const QVariant &variant);
    QVariant qextMvvmToString(const QJsonObject &object);

    QJsonObject qextMvvmFromDouble(const QVariant &variant);
    QVariant qextMvvmToDouble(const QJsonObject &object);

    QJsonObject qextMvvmFromVectorDouble(const QVariant &variant);
    QVariant qextMvvmToVectorDouble(const QJsonObject &object);

    QJsonObject qextMvvmFromComboProperty(const QVariant &variant);
    QVariant qextMvvmToComboProperty(const QJsonObject &object);

    QJsonObject qextMvvmFromColor(const QVariant &variant);
    QVariant qextMvvmToColor(const QJsonObject &object);

    QJsonObject qextMvvmFromExtProperty(const QVariant &variant);
    QVariant qextMvvmToExtProperty(const QJsonObject &object);

    QJsonObject qextMvvmFromRealLimits(const QVariant &variant);
    QVariant qextMvvmToRealLimits(const QJsonObject &object);

} // namespace

QEXTMvvmJsonVariantConverter::QEXTMvvmJsonVariantConverter()
{
    m_jsonToVariantconverters[QEXTMvvmConstants::invalid_type_name] = JsonToVariantFunction(qextMvvmToInvalid);
    m_jsonToVariantconverters[QEXTMvvmConstants::bool_type_name] = JsonToVariantFunction(qextMvvmToBool);
    m_jsonToVariantconverters[QEXTMvvmConstants::int_type_name] = JsonToVariantFunction(qextMvvmToInt);
    m_jsonToVariantconverters[QEXTMvvmConstants::string_type_name] = JsonToVariantFunction(qextMvvmToString);
    m_jsonToVariantconverters[QEXTMvvmConstants::double_type_name] = JsonToVariantFunction(qextMvvmToDouble);
    m_jsonToVariantconverters[QEXTMvvmConstants::vector_double_type_name] = JsonToVariantFunction(qextMvvmToVectorDouble);
    m_jsonToVariantconverters[QEXTMvvmConstants::comboproperty_type_name] = JsonToVariantFunction(qextMvvmToComboProperty);
    m_jsonToVariantconverters[QEXTMvvmConstants::color_type_name] = JsonToVariantFunction(qextMvvmToColor);
    m_jsonToVariantconverters[QEXTMvvmConstants::extproperty_type_name] = JsonToVariantFunction(qextMvvmToExtProperty);
    m_jsonToVariantconverters[QEXTMvvmConstants::reallimits_type_name] = JsonToVariantFunction(qextMvvmToRealLimits);

    m_variantToJsonConverters[QEXTMvvmConstants::invalid_type_name] = VariantToJsonFunction(qextMvvmFromInvalid);
    m_variantToJsonConverters[QEXTMvvmConstants::bool_type_name] = VariantToJsonFunction(qextMvvmFromBool);
    m_variantToJsonConverters[QEXTMvvmConstants::int_type_name] = VariantToJsonFunction(qextMvvmFromInt);
    m_variantToJsonConverters[QEXTMvvmConstants::string_type_name] = VariantToJsonFunction(qextMvvmFromString);
    m_variantToJsonConverters[QEXTMvvmConstants::double_type_name] = VariantToJsonFunction(qextMvvmFromDouble);
    m_variantToJsonConverters[QEXTMvvmConstants::vector_double_type_name] = VariantToJsonFunction(qextMvvmFromVectorDouble);
    m_variantToJsonConverters[QEXTMvvmConstants::comboproperty_type_name] = VariantToJsonFunction(qextMvvmFromComboProperty);
    m_variantToJsonConverters[QEXTMvvmConstants::color_type_name] = VariantToJsonFunction(qextMvvmFromColor);
    m_variantToJsonConverters[QEXTMvvmConstants::extproperty_type_name] = VariantToJsonFunction(qextMvvmFromExtProperty);
    m_variantToJsonConverters[QEXTMvvmConstants::reallimits_type_name] = VariantToJsonFunction(qextMvvmFromRealLimits);
}

QJsonObject QEXTMvvmJsonVariantConverter::getJson(const QVariant &variant)
{
    const QString typeName = QEXTMvvmUtils::VariantName(variant);
    if (!m_variantToJsonConverters.contains(typeName))
    {
        throw std::runtime_error("json::get_json() -> Error. Unknown variant type '" + typeName.toStdString() + "'.");
    }
    return m_variantToJsonConverters[typeName](variant);
}

QVariant QEXTMvvmJsonVariantConverter::getVariant(const QJsonObject &object)
{
    if (!this->isVariant(object))
    {
        throw std::runtime_error("json::get_variant() -> Error. Invalid json object");
    }

    const QString typeName = object[QEXT_MVVM_VARIANT_TYPE_KEY].toString();
    if (!m_jsonToVariantconverters.contains(typeName))
    {
        throw std::runtime_error("json::get_variant() -> Error. Unknown variant type '" + typeName.toStdString() + "' in json object.");
    }
    return m_jsonToVariantconverters[typeName](object);
}

//! Returns true if given json object represents variant.

bool QEXTMvvmJsonVariantConverter::isVariant(const QJsonObject &object) const
{
    static const QStringList expected = qextMvvmExpectedVariantKeys();
    return object.keys() == expected;
}

namespace
{

    QStringList qextMvvmExpectedVariantKeys()
    {
        QStringList result = QStringList() << QEXT_MVVM_VARIANT_TYPE_KEY << QEXT_MVVM_VARIANT_VALUE_KEY;
        qSort(result.begin(), result.end());
        return result;
    }

    QJsonObject qextMvvmFromInvalid(const QVariant &variant)
    {
        (void)variant;
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::invalid_type_name;
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = QJsonValue();
        return result;
    }

    QVariant qextMvvmToInvalid(const QJsonObject &object)
    {
        (void)object;
        return QVariant();
    }

    QJsonObject qextMvvmFromBool(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::bool_type_name;
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = variant.value<bool>();
        return result;
    }

    QVariant qextMvvmToBool(const QJsonObject &object)
    {
        return object[QEXT_MVVM_VARIANT_VALUE_KEY].toVariant();
    }

    QJsonObject qextMvvmFromInt(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::int_type_name;
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = variant.value<int>();
        return result;
    }

    QVariant qextMvvmToInt(const QJsonObject &object)
    {
        // deliberately recreating variant, otherwise it is changing type to Qariant::Double
        return QVariant::fromValue(object[QEXT_MVVM_VARIANT_VALUE_KEY].toVariant().value<int>());
    }

    QJsonObject qextMvvmFromString(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::string_type_name;
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = variant.value<QString>();
        return result;
    }

    QVariant qextMvvmToString(const QJsonObject &object)
    {
        QString value = object[QEXT_MVVM_VARIANT_VALUE_KEY].toString();
        return QVariant::fromValue(value);
    }

    QJsonObject qextMvvmFromDouble(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::double_type_name;
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = variant.value<double>();
        return result;
    }

    QVariant qextMvvmToDouble(const QJsonObject &object)
    {
        // deliberately recreating variant, otherwise it is changing type to qlonglong for
        // numbers like 43.0
        return object[QEXT_MVVM_VARIANT_VALUE_KEY].toVariant().value<double>();
    }

// --- QVector<double> ------

    QJsonObject qextMvvmFromVectorDouble(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::vector_double_type_name;
        QJsonArray array;
        QVector<double> data = variant.value<QVector<double> >();
        for (int i = 0; i < data.size(); ++i)
        {
            array.append(data.at(i));
        }
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = array;
        return result;
    }

    QVariant qextMvvmToVectorDouble(const QJsonObject &object)
    {
        QVector<double> vec;
        QJsonArray array = object[QEXT_MVVM_VARIANT_VALUE_KEY].toArray();
        for (int i = 0; i < array.size(); ++i)
        {
            QJsonValue value = array.at(i);
            vec.append(value.toDouble());
        }
        return QVariant::fromValue(vec);
    }

// --- QEXTMvvmComboProperty ------

    QJsonObject qextMvvmFromComboProperty(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::comboproperty_type_name;
        QEXTMvvmComboProperty combo = variant.value<QEXTMvvmComboProperty>();
        QJsonObject json_data;
        json_data[QEXT_MVVM_COMBO_VALUE_KEY] = combo.stringOfValues();
        json_data[QEXT_MVVM_COMBO_SELECTION_KEY] = combo.stringOfSelections();
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = json_data;
        return result;
    }

    QVariant qextMvvmToComboProperty(const QJsonObject &object)
    {
        QEXTMvvmComboProperty combo;
        QJsonObject json_data = object[QEXT_MVVM_VARIANT_VALUE_KEY].toObject();
        combo.setStringOfValues(json_data[QEXT_MVVM_COMBO_VALUE_KEY].toString());
        combo.setStringOfSelections(json_data[QEXT_MVVM_COMBO_SELECTION_KEY].toString());
        return QVariant::fromValue(combo);
    }

// --- QColor ------

    QJsonObject qextMvvmFromColor(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::color_type_name;
        QColor color = variant.value<QColor>();
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = color.name(QColor::HexArgb);
        return result;
    }

    QVariant qextMvvmToColor(const QJsonObject &object)
    {
        return QVariant::fromValue(QColor(object[QEXT_MVVM_VARIANT_VALUE_KEY].toString()));
    }

// --- QEXTMvvmExternalProperty ------

    QJsonObject qextMvvmFromExtProperty(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::extproperty_type_name;
        QEXTMvvmExternalProperty extprop = variant.value<QEXTMvvmExternalProperty>();
        QJsonObject json_data;
        json_data[QEXT_MVVM_EXTPROPERTY_TEXT_KEY] = extprop.text();
        json_data[QEXT_MVVM_EXTPROPERTY_COLOR_KEY] = extprop.color().name(QColor::HexArgb);
        json_data[QEXT_MVVM_EXTPROPERTY_ID_KEY] = extprop.identifier();
        result[QEXT_MVVM_VARIANT_VALUE_KEY] = json_data;
        return result;
    }

    QVariant qextMvvmToExtProperty(const QJsonObject &object)
    {
        QJsonObject json_data = object[QEXT_MVVM_VARIANT_VALUE_KEY].toObject();
        const QString text = json_data[QEXT_MVVM_EXTPROPERTY_TEXT_KEY].toString();
        const QString color = json_data[QEXT_MVVM_EXTPROPERTY_COLOR_KEY].toString();
        const QString id = json_data[QEXT_MVVM_EXTPROPERTY_ID_KEY].toString();

        return QVariant::fromValue(QEXTMvvmExternalProperty(text, QColor(color), id));
    }

// --- QEXTMvvmRealLimits ------

    QJsonObject qextMvvmFromRealLimits(const QVariant &variant)
    {
        QJsonObject result;
        result[QEXT_MVVM_VARIANT_TYPE_KEY] = QEXTMvvmConstants::reallimits_type_name;
        QEXTMvvmRealLimits limits = variant.value<QEXTMvvmRealLimits>();
        QJsonObject jsonData;

        jsonData[QEXT_MVVM_REALLIMITS_TEXT_KEY] = JsonUtils::ToString(limits);
        jsonData[QEXT_MVVM_REALLIMITS_MIN_KEY] = limits.lowerLimit();
        jsonData[QEXT_MVVM_REALLIMITS_MAX_KEY] = limits.upperLimit();

        result[QEXT_MVVM_VARIANT_VALUE_KEY] = jsonData;
        return result;
    }

    QVariant qextMvvmToRealLimits(const QJsonObject &object)
    {
        QJsonObject json_data = object[QEXT_MVVM_VARIANT_VALUE_KEY].toObject();
        const QString text = json_data[QEXT_MVVM_REALLIMITS_TEXT_KEY].toString();
        const double min = json_data[QEXT_MVVM_REALLIMITS_MIN_KEY].toDouble();
        const double max = json_data[QEXT_MVVM_REALLIMITS_MAX_KEY].toDouble();

        return QVariant::fromValue(JsonUtils::CreateLimits(text, min, max));
    }

} // namespace
