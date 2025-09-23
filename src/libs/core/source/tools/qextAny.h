/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com
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

#ifndef _QEXTANY_H
#define _QEXTANY_H

#include <nonstd/any.hpp>

typedef nonstd::any QExtAny;
typedef nonstd::bad_any_cast QExtBadAnyCast;

#define QEXT_ANY_CPP98_OR_GREATER any_CPP98_OR_GREATER
#define QEXT_ANY_CPP11_OR_GREATER any_CPP11_OR_GREATER
#define QEXT_ANY_CPP14_OR_GREATER any_CPP14_OR_GREATER
#define QEXT_ANY_CPP17_OR_GREATER any_CPP17_OR_GREATER
#define QEXT_ANY_CPP20_OR_GREATER any_CPP20_OR_GREATER
#define QEXT_ANY_CPP23_OR_GREATER any_CPP23_OR_GREATER
#define QEXT_HAVE_IN_PLACE_TYPES nonstd_lite_HAVE_IN_PLACE_TYPES
#define QEXT_HAVE_STD_ANY any_HAVE_STD_ANY
#define QEXT_USES_STD_ANY any_USES_STD_ANY
#define QEXT_ANY_NODISCARD any_nodiscard
#define QEXT_ANY_NOEXCEPT any_noexcept

#define qextMakeAnyInPlaceType nonstd::in_place_type
#define qextAnyCast nonstd::any_cast
#define qextMakeAny nonstd::make_any
#define qextSwapAny nonstd::swap

#endif // _QEXTANY_H
