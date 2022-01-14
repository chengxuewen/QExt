// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmComboProperty.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmVariantConstants.h>

namespace
{
const QString qstring_name = "QString";
}

using namespace ModelView;

std::string QEXTMvvmUtils::VariantName(const QVariant& variant)
{
    return variant.isValid() ? variant.typeName() : QEXTMvvmConstants::invalid_type_name;
}

int QEXTMvvmUtils::VariantType(const QVariant& variant)
{
    auto result = static_cast<int>(variant.type());
    if (result == QVariant::UserType)
        result = variant.userType();
    return result;
}

bool QEXTMvvmUtils::CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue)
{
    // Invalid variant can be rewritten by any variant.
    // Valid Variant can be replaced by invalid variant.
    // In other cases types of variants should coincide to be compatible.

    if (!oldValue.isValid() || !newValue.isValid())
        return true;

    return QEXTMvvmUtils::VariantType(oldValue) == QEXTMvvmUtils::VariantType(newValue);
}

bool QEXTMvvmUtils::IsTheSame(const QVariant& var1, const QVariant& var2)
{
    // variants of different type are always reported as not the same
    if (VariantType(var1) != VariantType(var2))
        return false;

    // variants of same type are compared by value
    return var1 == var2;
}

QVariant QEXTMvvmUtils::toQtVariant(const QVariant& custom)
{
    if (!custom.isValid())
        return custom;

    // converts variant based on std::string to variant based on QString
    if (custom.typeName() == QEXTMvvmConstants::string_type_name) {
        return QVariant(QString::fromStdString(custom.value<std::string>()));
    } else if (IsDoubleVectorVariant(custom)) {
        QString str =
            QString("vector of %1 elements").arg(custom.value<std::vector<double>>().size());
        return QVariant(str);
    }

    // in other cases returns unchanged variant
    return custom;
}

QVariant QEXTMvvmUtils::toCustomVariant(const QVariant& standard)
{
    if (!standard.isValid())
        return standard;

    // converts variant based on std::string to variant based on QString
    if (standard.typeName() == qstring_name)
        return QVariant::fromValue(standard.toString().toStdString());

    // in other cases returns unchanged variant
    return standard;
}

bool QEXTMvvmUtils::IsBoolVariant(const QVariant& variant)
{
    return variant.type() == QVariant::Bool;
}

bool QEXTMvvmUtils::IsIntVariant(const QVariant& variant)
{
    return variant.type() == QVariant::Int;
}

bool QEXTMvvmUtils::IsDoubleVariant(const QVariant& variant)
{
    return variant.type() == QVariant::Double;
}

bool QEXTMvvmUtils::IsComboVariant(const QVariant& variant)
{
    return variant.canConvert<QEXTMvvmComboProperty>();
}

bool QEXTMvvmUtils::IsStdStringVariant(const QVariant& variant)
{
    return variant.canConvert<std::string>();
}

bool QEXTMvvmUtils::IsDoubleVectorVariant(const QVariant& variant)
{
    return variant.typeName() == QEXTMvvmConstants::vector_double_type_name;
}

bool QEXTMvvmUtils::IsColorVariant(const QVariant& variant)
{
    return variant.type() == QVariant::Color;
}

bool QEXTMvvmUtils::IsExtPropertyVariant(const QVariant& variant)
{
    return variant.canConvert<QEXTMvvmExternalProperty>();
}

bool QEXTMvvmUtils::IsRealLimitsVariant(const QVariant& variant)
{
    return variant.canConvert<QEXTMvvmRealLimits>();
}
