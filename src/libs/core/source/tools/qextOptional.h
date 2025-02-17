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

#ifndef _QEXTOPTIONAL_H
#define _QEXTOPTIONAL_H

#include <nonstd/optional.hpp>

#define qextOptionalSwap std::swap
#define qextOptionalInPlace nonstd::in_place
#define qextOptionalInPlaceType nonstd::in_place_type
#define qextOptionalInPlaceIndex nonstd::in_place_index
#define qextOptionalMakeOptional nonstd::make_optional

#define QEXT_OPTIONAL_HAVE_STD_OPTIONAL optional_HAVE_STD_OPTIONAL
#define QEXT_OPTIONAL_HAVE_TWEAK_HEADER optional_HAVE_TWEAK_HEADER
#define QEXT_OPTIONAL_CONFIG_NO_EXCEPTIONS optional_CONFIG_NO_EXCEPTIONS
#define QEXT_OPTIONAL_CONFIG_SELECT_OPTIONAL optional_CONFIG_SELECT_OPTIONAL

#define QEXT_OPTIONAL_CPP11_90 optional_CPP11_90
#define QEXT_OPTIONAL_CPP11_100 optional_CPP11_100
#define QEXT_OPTIONAL_CPP11_110 optional_CPP11_110
#define QEXT_OPTIONAL_CPP11_120 optional_CPP11_120
#define QEXT_OPTIONAL_CPP11_140 optional_CPP11_140
#define QEXT_OPTIONAL_CPP11_141 optional_CPP11_141
#define QEXT_OPTIONAL_CPP14_000 optional_CPP14_000
#define QEXT_OPTIONAL_CPP17_000 optional_CPP17_000
#define QEXT_OPTIONAL_CPP11_110_C350 optional_CPP11_110_C350
#define QEXT_OPTIONAL_CPP11_110_C350_G500 optional_CPP11_110_C350_G500
#define QEXT_OPTIONAL_CPP11_140_C290_G490 optional_CPP11_140_C290_G490
#define QEXT_OPTIONAL_CPP98_OR_GREATER optional_CPP98_OR_GREATER
#define QEXT_OPTIONAL_CPP11_OR_GREATER optional_CPP11_OR_GREATER
#define QEXT_OPTIONAL_CPP14_OR_GREATER optional_CPP14_OR_GREATER
#define QEXT_OPTIONAL_CPP17_OR_GREATER optional_CPP17_OR_GREATER
#define QEXT_OPTIONAL_CPP20_OR_GREATER optional_CPP20_OR_GREATER
#define QEXT_OPTIONAL_CPP23_OR_GREATER optional_CPP23_OR_GREATER

#define QEXT_OPTIONAL_USES_STD_OPTIONAL optional_USES_STD_OPTIONAL

#define QExtOptional nonstd::optional
#define QExtOptionalNullopt nonstd::nullopt
#define QExtOptionalNulloptT nonstd::nullopt_t
#define QExtBadOptionalAccess nonstd::bad_optional_access

#endif // _QEXTOPTIONAL_H
