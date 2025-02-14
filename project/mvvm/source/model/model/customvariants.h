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

#include "model/core/variant.h"
#include "qextMVVMGlobal.h"
#include "model/utils/reallimits.h"
#include <QMetaType>
#include <string>
#include <vector>

namespace ModelView::Utils {

//! Returns name of variant.
QEXT_MVVM_API std::string VariantName(const Variant& variant);

//! Returns type of variant (additionally checks for user type).
QEXT_MVVM_API int VariantType(const Variant& variant);

//! Returns true if variants has compatible types.
QEXT_MVVM_API bool CompatibleVariantTypes(const Variant& oldValue, const Variant& newValue);

//! Returns true if given variants have same type and value.
QEXT_MVVM_API bool IsTheSame(const Variant& var1, const Variant& var2);

//! Converts custom variant to standard variant which Qt views will understand.
QEXT_MVVM_API Variant toQtVariant(const Variant& custom);

//! Converts Qt variant to custom variant on board of SessionItem.
QEXT_MVVM_API Variant toCustomVariant(const Variant& standard);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsBoolVariant(const Variant& variant);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsIntVariant(const Variant& variant);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsDoubleVariant(const Variant& variant);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsComboVariant(const Variant& variant);

//! Returns true in the case of double value based variant.
QEXT_MVVM_API bool IsStdStringVariant(const Variant& variant);

//! Returns true in the case of variant based on std::vector<double>.
QEXT_MVVM_API bool IsDoubleVectorVariant(const Variant& variant);

//! Returns true in the case of QColor based variant.
QEXT_MVVM_API bool IsColorVariant(const Variant& variant);

//! Returns true in the case of ExternalProperty based variant.
QEXT_MVVM_API bool IsExtPropertyVariant(const Variant& variant);

//! Returns true in the case of RealLimits based variant.
QEXT_MVVM_API bool IsRealLimitsVariant(const Variant& variant);

} // namespace ModelView::Utils

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<double>)
Q_DECLARE_METATYPE(ModelView::RealLimits)

#endif // MVVM_MODEL_CUSTOMVARIANTS_H
