/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTVARIANTUTILS_H
#define _QEXTVARIANTUTILS_H

#include <qextGlobal.h>

namespace QExtVariantUtils
{

static const char TYPE_NAME_INVALID[] = "invalid";
static const char TYPE_NAME_INT[] = "int";
static const char TYPE_NAME_BOOL[] = "bool";
static const char TYPE_NAME_DOUBLE[] = "double";
static const char TYPE_NAME_QCOLOR[] = "QColor";
static const char TYPE_NAME_QSTRING[] = "QString";
static const char TYPE_NAME_STD_STRING[] = "std::string";
static const char TYPE_NAME_STD_DOUBLE_VECTOR[] = "std::vector<double>";
static const char TYPE_NAME_COMBOPROP[] = "ComboProperty";
static const char TYPE_NAME_EXTERPROP[] = "ExternalProperty";
static const char TYPE_NAME_REALLIMITS[] = "RealLimits";

//! Returns name of variant.
QEXT_CORE_API const char *variantName(const QVariant &variant);

//! Returns type of variant (additionally checks for user type).
QEXT_CORE_API int variantType(const QVariant &variant);

//! Returns true if variants has compatible types.
QEXT_CORE_API bool compatibleVariantTypes(const QVariant &oldValue, const QVariant &newValue);

//! Returns true if given variants have same type and value.
QEXT_CORE_API bool isTheSame(const QVariant &var1, const QVariant &var2);

//! Converts custom variant to standard variant which Qt views will understand.
QEXT_CORE_API QVariant toQtVariant(const QVariant &custom);

//! Converts Qt variant to custom variant on board of SessionItem.
QEXT_CORE_API QVariant toCustomVariant(const QVariant &standard);

//! Returns true in the case of double value based variant.
QEXT_CORE_API bool isIntVariant(const QVariant &variant);

//! Returns true in the case of double value based variant.
QEXT_CORE_API bool isBoolVariant(const QVariant &variant);

//! Returns true in the case of double value based variant.
QEXT_CORE_API bool isDoubleVariant(const QVariant &variant);

//! Returns true in the case of double value based variant.
// QEXT_CORE_API bool isComboVariant(const QVariant &variant);

//! Returns true in the case of double value based variant.
QEXT_CORE_API bool isStdStringVariant(const QVariant &variant);

//! Returns true in the case of variant based on std::vector<double>.
QEXT_CORE_API bool isStdDoubleVectorVariant(const QVariant &variant);

//! Returns true in the case of QColor based variant.
QEXT_CORE_API bool isColorVariant(const QVariant &variant);

//! Returns true in the case of ExternalProperty based variant.
// QEXT_CORE_API bool isExtPropertyVariant(const QVariant &variant);

//! Returns true in the case of RealLimits based variant.
// QEXT_CORE_API bool isRealLimitsVariant(const QVariant &variant);

};

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(std::vector<double>)

#endif // _QEXTVARIANTUTILS_H
