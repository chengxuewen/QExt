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
