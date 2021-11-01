#ifndef _QEXTMVVMCUSTOMVARIANTS_H
#define _QEXTMVVMCUSTOMVARIANTS_H

//! @file customvariants.h
//! Registrations and translations for custom variants.

#include <QMetaType>
#include <qextMvvmVariant.h>
#include <qextMvvmGlobal.h>
#include <utils/qextMvvmRealLimits.h>
#include <string>
#include <vector>

namespace ModelView
{
    namespace Utils
    {

//! Returns name of variant.
        QEXT_MVVM_API std::string VariantName(const QEXTMvvmVariant &variant);

//! Returns type of variant (additionally checks for user type).
        QEXT_MVVM_API int VariantType(const QEXTMvvmVariant &variant);

//! Returns true if variants has compatible types.
        QEXT_MVVM_API bool CompatibleVariantTypes(const QEXTMvvmVariant &oldValue, const QEXTMvvmVariant &newValue);

//! Returns true if given variants have same type and value.
        QEXT_MVVM_API bool IsTheSame(const QEXTMvvmVariant &var1, const QEXTMvvmVariant &var2);

//! Converts custom variant to standard variant which Qt views will understand.
        QEXT_MVVM_API QEXTMvvmVariant toQtVariant(const QEXTMvvmVariant &custom);

//! Converts Qt variant to custom variant on board of QEXTMvvmSessionItem.
        QEXT_MVVM_API QEXTMvvmVariant toCustomVariant(const QEXTMvvmVariant &standard);

//! Returns true in the case of double value based variant.
        QEXT_MVVM_API bool IsBoolVariant(const QEXTMvvmVariant &variant);

//! Returns true in the case of double value based variant.
        QEXT_MVVM_API bool IsIntVariant(const QEXTMvvmVariant &variant);

//! Returns true in the case of double value based variant.
        QEXT_MVVM_API bool IsDoubleVariant(const QEXTMvvmVariant &variant);

//! Returns true in the case of double value based variant.
        QEXT_MVVM_API bool IsComboVariant(const QEXTMvvmVariant &variant);

//! Returns true in the case of double value based variant.
        QEXT_MVVM_API bool IsStdStringVariant(const QEXTMvvmVariant &variant);

//! Returns true in the case of variant based on std::vector<double>.
        QEXT_MVVM_API bool IsDoubleVectorVariant(const QEXTMvvmVariant &variant);

//! Returns true in the case of QColor based variant.
        QEXT_MVVM_API bool IsColorVariant(const QEXTMvvmVariant &variant);

//! Returns true in the case of QEXTMvvmExternalProperty based variant.
        QEXT_MVVM_API bool IsExtPropertyVariant(const QEXTMvvmVariant &variant);

//! Returns true in the case of QEXTMvvmRealLimits based variant.
        QEXT_MVVM_API bool IsRealLimitsVariant(const QEXTMvvmVariant &variant);

    } // namespace Utils
} // namespace ModelView

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<double>)
Q_DECLARE_METATYPE(ModelView::QEXTMvvmRealLimits)

#endif // _QEXTMVVMCUSTOMVARIANTS_H
