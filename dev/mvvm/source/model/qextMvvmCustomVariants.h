// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_CUSTOMVARIANTS_H
#define MVVM_MODEL_CUSTOMVARIANTS_H

//! @file customvariants.h
//! Registrations and translations for custom variants.


#include <qextMvvmGlobal.h>
#include <qextMvvmRealLimits.h>
#include <QMetaType>
#include <string>
#include <vector>

namespace ModelView
{
namespace Utils
{

//! Returns name of variant.
QEXT_MVVM_API std::string VariantName(const QVariant& variant);

//! Returns type of variant (additionally checks for user type).
QEXT_MVVM_API int VariantType(const QVariant& variant);

//! Returns true if variants has compatible types.
QEXT_MVVM_API bool CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue);

//! Returns true if given variants have same type and value.
QEXT_MVVM_API bool IsTheSame(const QVariant& var1, const QVariant& var2);

//! Converts custom variant to standard variant which Qt views will understand.
QEXT_MVVM_API QVariant toQtVariant(const QVariant& custom);

//! Converts Qt variant to custom variant on board of QExtMvvmSessionItem.
QEXT_MVVM_API QVariant toCustomVariant(const QVariant& standard);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsBoolVariant(const QVariant& variant);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsIntVariant(const QVariant& variant);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsDoubleVariant(const QVariant& variant);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsComboVariant(const QVariant& variant);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsStdStringVariant(const QVariant& variant);

//! Returns true in the case of variant based on std::vector<double>.
QEXT_MVVM_API bool IsDoubleVectorVariant(const QVariant& variant);

//! Returns true in the case of QColor based variant.
QEXT_MVVM_API bool IsColorVariant(const QVariant& variant);

//! Returns true in the case of QExtMvvmExternalProperty based variant.
QEXT_MVVM_API bool IsExtPropertyVariant(const QVariant& variant);

//! Returns true in the case of QExtMvvmRealLimits based variant.
QEXT_MVVM_API bool IsRealLimitsVariant(const QVariant& variant);
}
} // namespace ModelView::Utils

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<double>)
Q_DECLARE_METATYPE(ModelView::QExtMvvmRealLimits)

#endif // MVVM_MODEL_CUSTOMVARIANTS_H
