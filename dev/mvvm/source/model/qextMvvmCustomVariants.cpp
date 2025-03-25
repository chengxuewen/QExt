// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCustomVariants.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmVariantConstants.h>

namespace {
const QString qstring_name = "QString";
}

using namespace ModelView;

std::string Utils::VariantName(const QVariant& variant)
{
    return variant.isValid() ? variant.typeName() : Constants::invalid_type_name;
}

int Utils::VariantType(const QVariant& variant)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    auto result = static_cast<int>(variant.type());
    if (result == QVariant::UserType)
    {
        result = variant.userType();
    }
#else
    auto result = variant.typeId();
    if (result == QMetaType::User)
    {
        result = variant.userType();
    }
#endif
    return result;
}

bool Utils::CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue)
{
    // Invalid variant can be rewritten by any variant.
    // Valid QVariant can be replaced by invalid variant.
    // In other cases types of variants should coincide to be compatible.

    if (!oldValue.isValid() || !newValue.isValid())
        return true;

    return Utils::VariantType(oldValue) == Utils::VariantType(newValue);
}

bool Utils::IsTheSame(const QVariant& var1, const QVariant& var2)
{
    // variants of different type are always reported as not the same
    if (VariantType(var1) != VariantType(var2))
        return false;

    // variants of same type are compared by value
    return var1 == var2;
}

QVariant Utils::toQtVariant(const QVariant& custom)
{
    if (!custom.isValid())
        return custom;

    // converts variant based on std::string to variant based on QString
    if (custom.typeName() == Constants::string_type_name) {
        return QVariant(QString::fromStdString(custom.value<std::string>()));
    }
    else if (IsDoubleVectorVariant(custom)) {
        QString str =
            QString("vector of %1 elements").arg(custom.value<std::vector<double>>().size());
        return QVariant(str);
    }

    // in other cases returns unchanged variant
    return custom;
}

QVariant Utils::toCustomVariant(const QVariant& standard)
{
    if (!standard.isValid())
        return standard;

    // converts variant based on std::string to variant based on QString
    if (standard.typeName() == qstring_name)
        return QVariant::fromValue(standard.toString().toStdString());

    // in other cases returns unchanged variant
    return standard;
}

bool Utils::IsBoolVariant(const QVariant& variant)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return variant.type() == QVariant::Bool;
#else
    return variant.typeId() == QMetaType::Bool;
#endif
}

bool Utils::IsIntVariant(const QVariant& variant)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return variant.type() == QVariant::Int;
#else
    return variant.typeId() == QMetaType::Int;
#endif
}

bool Utils::IsDoubleVariant(const QVariant& variant)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return variant.type() == QVariant::Double;
#else
    return variant.typeId() == QMetaType::Double;
#endif
}

bool Utils::IsComboVariant(const QVariant& variant)
{
    return variant.canConvert<QExtMvvmComboProperty>();
}

bool Utils::IsStdStringVariant(const QVariant& variant)
{
    return variant.canConvert<std::string>();
}

bool Utils::IsDoubleVectorVariant(const QVariant& variant)
{
    return variant.typeName() == Constants::vector_double_type_name;
}

bool Utils::IsColorVariant(const QVariant& variant)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return variant.type() == QVariant::Color;
#else
    return variant.typeId() == QMetaType::QColor;
#endif
}

bool Utils::IsExtPropertyVariant(const QVariant& variant)
{
    return variant.canConvert<QExtMvvmExternalProperty>();
}

bool Utils::IsRealLimitsVariant(const QVariant& variant)
{
    return variant.canConvert<QExtMvvmRealLimits>();
}
