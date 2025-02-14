/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~present ChengXueWen.
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


#ifndef _QEXTVARIANT_H
#define _QEXTVARIANT_H

#include <nonstd/variant.hpp>

#define qextVariantGet nonstd::get
#define qextVariantSwap nonstd::swap
#define qextVariantVisit nonstd::visit
#define qextVariantGetIf nonstd::get_if
#define qextVariantInPlace nonstd::in_place
#define qextVariantInPlaceType nonstd::in_place_type
#define qextVariantInPlaceIndex nonstd::in_place_index
#define qextVariantHoldsAlternative nonstd::holds_alternative

#define QEXT_VARIANT_NULLPTR variant_nullptr
#define QEXT_VARIANT_CPLUSPLUS variant_CPLUSPLUS
#define QEXT_VARIANT_CPP98_OR_GREATER variant_CPP98_OR_GREATER
#define QEXT_VARIANT_CPP11_OR_GREATER variant_CPP11_OR_GREATER
#define QEXT_VARIANT_CPP14_OR_GREATER variant_CPP14_OR_GREATER
#define QEXT_VARIANT_CPP17_OR_GREATER variant_CPP17_OR_GREATER
#define QEXT_VARIANT_CPP20_OR_GREATER variant_CPP20_OR_GREATER

#define QEXT_VARIANT_HAVE_STD_VARIANT variant_HAVE_STD_VARIANT
#define QEXT_VARIANT_CONFIG_NO_EXCEPTIONS variant_CONFIG_NO_EXCEPTIONS
#define QEXT_VARIANT_HAVE_IN_PLACE_TYPES nonstd_lite_HAVE_IN_PLACE_TYPES

typedef nonstd::monostate QExtVariantMonostate;
typedef nonstd::bad_variant_access QExtBadVariantAccess;

#define QExtVariant nonstd::variant
#define QExtVariantSize nonstd::variant_size
#define QExtVariantAlternative nonstd::variant_alternative
#if QEXT_VARIANT_CPP11_OR_GREATER
#   define QExtVariantAlternativeT nonstd::variant_alternative_t
#endif

#endif // _QEXTVARIANT_H
