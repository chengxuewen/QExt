#include <qextVariantUtils.h>

const char *QExtVariantUtils::variantName(const QVariant &variant)
{
    return variant.isValid() ? variant.typeName() : TYPE_NAME_INVALID;
}

int QExtVariantUtils::variantType(const QVariant &variant)
{
    int type = static_cast<int>(variant.type());
    if (type == QVariant::UserType)
    {
        type = variant.userType();
    }
    return type;
}

bool QExtVariantUtils::compatibleVariantTypes(const QVariant &oldValue, const QVariant &newValue)
{
    // Invalid variant can be rewritten by any variant.
    // Valid Variant can be replaced by invalid variant.
    // In other cases types of variants should coincide to be compatible.
    if (!oldValue.isValid() || !newValue.isValid())
    {
        return true;
    }
    return variantType(oldValue) == variantType(newValue);
}

bool QExtVariantUtils::isTheSame(const QVariant &var1, const QVariant &var2)
{
    // variants of different type are always reported as not the same
    if (variantType(var1) != variantType(var2))
    {
        return false;
    }
    // variants of same type are compared by value
    return var1 == var2;
}

QVariant QExtVariantUtils::toQtVariant(const QVariant &custom)
{
    if (!custom.isValid())
    {
        return custom;
    }

    // converts variant based on std::string to variant based on QString
    if (custom.typeName() == QString(TYPE_NAME_STD_STRING))
    {
        return QVariant(QString::fromStdString(custom.value<std::string>()));
    }
    else if (isStdDoubleVectorVariant(custom))
    {
        QString string = QString("vector of %1 elements").arg(custom.value<std::vector<double>>().size());
        return QVariant(string);
    }
    // in other cases returns unchanged variant
    return custom;
}

QVariant QExtVariantUtils::toCustomVariant(const QVariant &standard)
{
    if (!standard.isValid())
    {
        return standard;
    }

    // converts variant based on std::string to variant based on QString
    if (standard.typeName() == QString(TYPE_NAME_QSTRING))
    {
        return QVariant::fromValue(standard.toString().toStdString());
    }
    // in other cases returns unchanged variant
    return standard;
}

bool QExtVariantUtils::isIntVariant(const QVariant &variant)
{
    return variant.type() == QVariant::Bool;
}

bool QExtVariantUtils::isBoolVariant(const QVariant &variant)
{
    return variant.type() == QVariant::Int;
}

bool QExtVariantUtils::isDoubleVariant(const QVariant &variant)
{
    return variant.type() == QVariant::Double;
}

// bool QExtVariantUtils::isComboVariant(const QVariant &variant)
// {
//     return variant.canConvert<ComboProperty>();
// }

bool QExtVariantUtils::isStdStringVariant(const QVariant &variant)
{
    return variant.canConvert<std::string>();
}

bool QExtVariantUtils::isStdDoubleVectorVariant(const QVariant &variant)
{
    return variant.typeName() == QString(TYPE_NAME_STD_DOUBLE_VECTOR);
}

bool QExtVariantUtils::isColorVariant(const QVariant &variant)
{
    return variant.type() == QVariant::Color;
}

// bool QExtVariantUtils::isExtPropertyVariant(const QVariant &variant)
// {
//     return variant.canConvert<ExternalProperty>();
// }

// bool QExtVariantUtils::isRealLimitsVariant(const QVariant &variant)
// {
//     return variant.canConvert<RealLimits>();
// }
