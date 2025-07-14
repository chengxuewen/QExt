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

#ifndef _QEXTINVOKE_H
#define _QEXTINVOKE_H

#include <nonstd/invoke.hpp>

#define QEXT_INVOKE_CPP98_OR_GREATER invoke_CPP98_OR_GREATER
#define QEXT_INVOKE_CPP11_OR_GREATER invoke_CPP11_OR_GREATER
#define QEXT_INVOKE_CPP14_OR_GREATER invoke_CPP14_OR_GREATER
#define QEXT_INVOKE_CPP17_OR_GREATER invoke_CPP17_OR_GREATER
#define QEXT_INVOKE_CPP20_OR_GREATER invoke_CPP20_OR_GREATER


#ifdef invoke_HAVE_NODISCARD
#   define QEXT_INVOKE_HAVE_NODISCARD invoke_HAVE_NODISCARD
#else
#   define QEXT_INVOKE_HAVE_NODISCARD 0
#endif
#ifdef invoke_HAVE_STD_INVOKE
#   define QEXT_INVOKE_HAVE_STD_INVOKE invoke_HAVE_STD_INVOKE
#else
#   define QEXT_INVOKE_HAVE_STD_INVOKE 0
#endif
#ifdef invoke_HAVE_TYPE_TRAITS
#   define QEXT_INVOKE_HAVE_TYPE_TRAITS invoke_HAVE_TYPE_TRAITS
#else
#   define QEXT_INVOKE_HAVE_TYPE_TRAITS 0
#endif
#ifdef invoke_HAVE_CONSTEXPR_11
#   define QEXT_INVOKE_HAVE_CONSTEXPR_11 invoke_HAVE_CONSTEXPR_11
#else
#   define QEXT_INVOKE_HAVE_CONSTEXPR_11 0
#endif
#ifdef invoke_HAVE_CONSTEXPR_14
#   define QEXT_INVOKE_HAVE_CONSTEXPR_14 invoke_HAVE_CONSTEXPR_14
#else
#   define QEXT_INVOKE_HAVE_CONSTEXPR_14 0
#endif
#ifdef invoke_HAVE_TR1_TYPE_TRAITS
#   define QEXT_INVOKE_HAVE_TR1_TYPE_TRAITS invoke_HAVE_TR1_TYPE_TRAITS
#else
#   define QEXT_INVOKE_HAVE_TR1_TYPE_TRAITS 0
#endif


#ifdef invoke_COMPILER_MSVC_VER
#   define QEXT_INVOKE_COMPILER_MSVC_VER invoke_COMPILER_MSVC_VER
#else
#   define QEXT_INVOKE_COMPILER_MSVC_VER 0
#endif
#ifdef invoke_COMPILER_MSVC_VERSION
#   define QEXT_INVOKE_COMPILER_MSVC_VERSION invoke_COMPILER_MSVC_VERSION
#else
#   define QEXT_INVOKE_COMPILER_MSVC_VERSION 0
#endif
#ifdef invoke_COMPILER_GNUC_VERSION
#   define QEXT_INVOKE_COMPILER_GNUC_VERSION invoke_COMPILER_GNUC_VERSION
#else
#   define QEXT_INVOKE_COMPILER_GNUC_VERSION 0
#endif
#ifdef invoke_COMPILER_CLANG_VERSION
#   define QEXT_INVOKE_COMPILER_CLANG_VERSION invoke_COMPILER_CLANG_VERSION
#else
#   define QEXT_INVOKE_COMPILER_CLANG_VERSION 0
#endif


#ifdef invoke_CPP11_90
#   define QEXT_INVOKE_CPP11_90 invoke_CPP11_90
#else
#   define QEXT_INVOKE_CPP11_90 0
#endif
#ifdef invoke_CPP11_100
#   define QEXT_INVOKE_CPP11_100 invoke_CPP11_100
#else
#   define QEXT_INVOKE_CPP11_100 0
#endif
#ifdef invoke_CPP11_120
#   define QEXT_INVOKE_CPP11_120 invoke_CPP11_120
#else
#   define QEXT_INVOKE_CPP11_120 0
#endif
#ifdef invoke_CPP11_140
#   define QEXT_INVOKE_CPP11_140 invoke_CPP11_140
#else
#   define QEXT_INVOKE_CPP11_140 0
#endif
#ifdef invoke_CPP11_000
#   define QEXT_INVOKE_CPP11_000 invoke_CPP11_000
#else
#   define QEXT_INVOKE_CPP11_000 0
#endif
#ifdef invoke_CPP14_000
#   define QEXT_INVOKE_CPP14_000 invoke_CPP14_000
#else
#   define QEXT_INVOKE_CPP14_000 0
#endif
#ifdef invoke_CPP17_000
#   define QEXT_INVOKE_CPP17_000 invoke_CPP17_000
#else
#   define QEXT_INVOKE_CPP17_000 0
#endif
#ifdef invoke_CPP20_000
#   define QEXT_INVOKE_CPP20_000 invoke_CPP20_000
#else
#   define QEXT_INVOKE_CPP20_000 0
#endif
#ifdef invoke_CPP20_000
#   define QEXT_INVOKE_CPP20_000 invoke_CPP20_000
#else
#   define QEXT_INVOKE_CPP20_000 0
#endif


#ifdef invoke_BETWEEN
#   define QEXT_INVOKE_BETWEEN invoke_BETWEEN
#else
#   define QEXT_INVOKE_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )
#endif
#ifdef invoke_constexpr
#   define QEXT_INVOKE_CONSTEXPR invoke_constexpr
#else
#   define QEXT_INVOKE_CONSTEXPR
#endif
#ifdef invoke_constexpr14
#   define QEXT_INVOKE_CONSTEXPR14 invoke_constexpr14
#else
#   define QEXT_INVOKE_CONSTEXPR14
#endif
#ifdef invoke_noexcept
#   define QEXT_INVOKE_NOEXCEPT invoke_noexcept
#else
#   define QEXT_INVOKE_NOEXCEPT
#endif
#ifdef invoke_noexcept_op
#   define QEXT_INVOKE_NOEXCEPT_OP invoke_noexcept_op
#else
#   define QEXT_INVOKE_NOEXCEPT_OP(expr) /*noexcept(expr)*/
#endif
#ifdef invoke_nodiscard
#   define QEXT_INVOKE_NODISCARD invoke_nodiscard
#else
#   define QEXT_INVOKE_NODISCARD
#endif
#ifdef invoke_USES_STD_INVOKE
#   define QEXT_INVOKE_USES_STD_INVOKE invoke_USES_STD_INVOKE
#else
#   define QEXT_INVOKE_USES_STD_INVOKE
#endif


#define qextInvoke nonstd::invoke
#define qextInvokeApply nonstd::apply

#endif // _QEXTINVOKE_H
