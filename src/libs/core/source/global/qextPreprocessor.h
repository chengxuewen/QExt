#ifndef _QEXTPREPROCESSOR_H
#define _QEXTPREPROCESSOR_H

#define QEXT_PP_STRINGIFY(x)        QEXT_PP_STRINGIFY_(x)
#define QEXT_PP_STRINGIFY_(x)       #x

#define QEXT_PP_JOIN(lhs, rhs)      QEXT_PP_JOIN_1(lhs, rhs)
#define QEXT_PP_JOIN_1(lhs, rhs)    QEXT_PP_JOIN_2(lhs, rhs)
#define QEXT_PP_JOIN_2(lhs, rhs)    lhs##rhs

#endif // _QEXTPREPROCESSOR_H
