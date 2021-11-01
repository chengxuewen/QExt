#include <qextMvvmComboProperty.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmVariantConstants.h>

namespace
{
const QString qstring_name = "QString";
}

using namespace ModelView;

std::string Utils::VariantName(const QEXTMvvmVariant& variant)
{
    return variant.isValid() ? variant.typeName() : Constants::invalid_type_name;
}

int Utils::VariantType(const QEXTMvvmVariant& variant)
{
    auto result = static_cast<int>(variant.type());
    if (result == QEXTMvvmVariant::UserType)
        result = variant.userType();
    return result;
}

bool Utils::CompatibleVariantTypes(const QEXTMvvmVariant& oldValue, const QEXTMvvmVariant& newValue)
{
    // Invalid variant can be rewritten by any variant.
    // Valid QEXTMvvmVariant can be replaced by invalid variant.
    // In other cases types of variants should coincide to be compatible.

    if (!oldValue.isValid() || !newValue.isValid())
        return true;

    return Utils::VariantType(oldValue) == Utils::VariantType(newValue);
}

bool Utils::IsTheSame(const QEXTMvvmVariant& var1, const QEXTMvvmVariant& var2)
{
    // variants of different type are always reported as not the same
    if (VariantType(var1) != VariantType(var2))
        return false;

    // variants of same type are compared by value
    return var1 == var2;
}

QEXTMvvmVariant Utils::toQtVariant(const QEXTMvvmVariant& custom)
{
    if (!custom.isValid())
        return custom;

    // converts variant based on std::string to variant based on QString
    if (custom.typeName() == Constants::string_type_name) {
        return QEXTMvvmVariant(QString::fromStdString(custom.value<std::string>()));
    } else if (IsDoubleVectorVariant(custom)) {
        QString str =
            QString("vector of %1 elements").arg(custom.value<std::vector<double>>().size());
        return QEXTMvvmVariant(str);
    }

    // in other cases returns unchanged variant
    return custom;
}

QEXTMvvmVariant Utils::toCustomVariant(const QEXTMvvmVariant& standard)
{
    if (!standard.isValid())
        return standard;

    // converts variant based on std::string to variant based on QString
    if (standard.typeName() == qstring_name)
        return QEXTMvvmVariant::fromValue(standard.toString().toStdString());

    // in other cases returns unchanged variant
    return standard;
}

bool Utils::IsBoolVariant(const QEXTMvvmVariant& variant)
{
    return variant.type() == QEXTMvvmVariant::Bool;
}

bool Utils::IsIntVariant(const QEXTMvvmVariant& variant)
{
    return variant.type() == QEXTMvvmVariant::Int;
}

bool Utils::IsDoubleVariant(const QEXTMvvmVariant& variant)
{
    return variant.type() == QEXTMvvmVariant::Double;
}

bool Utils::IsComboVariant(const QEXTMvvmVariant& variant)
{
    return variant.canConvert<QEXTMvvmComboProperty>();
}

bool Utils::IsStdStringVariant(const QEXTMvvmVariant& variant)
{
    return variant.canConvert<std::string>();
}

bool Utils::IsDoubleVectorVariant(const QEXTMvvmVariant& variant)
{
    return variant.typeName() == Constants::vector_double_type_name;
}

bool Utils::IsColorVariant(const QEXTMvvmVariant& variant)
{
    return variant.type() == QEXTMvvmVariant::Color;
}

bool Utils::IsExtPropertyVariant(const QEXTMvvmVariant& variant)
{
    return variant.canConvert<QEXTMvvmExternalProperty>();
}

bool Utils::IsRealLimitsVariant(const QEXTMvvmVariant& variant)
{
    return variant.canConvert<QEXTMvvmRealLimits>();
}
