#ifndef QEXTLAMBDASELECT_H
#define QEXTLAMBDASELECT_H

#include <qextlambdabase.h>

namespace qextinternal {

struct QEXTLambdaSelect1 : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_arg1 Type;
    };
    typedef void ResultType; // no operator ()() overload

    void operator ()() const; // not implemented
    template <typename T_arg1>
    T_arg1 operator ()(T_arg1 arg1) const { return arg1; }

    template <typename T_arg1, typename T_arg2>
    T_arg1 operator ()(T_arg1 arg1, T_arg2) const { return arg1; }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3) const { return arg1; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3, T_arg4) const { return arg1; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3, T_arg4, T_arg5) const { return arg1; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const { return arg1; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const { return arg1; }
};

struct QEXTLambdaSelect2 : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_arg2 Type;
    };
    typedef void ResultType; // no operator ()() overload

    void operator ()() const; // not implemented
    template <typename T_arg1, typename T_arg2>
    T_arg2 operator ()(T_arg1, T_arg2 arg2) const { return arg2; }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3) const { return arg2; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3, T_arg4) const { return arg2; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3, T_arg4, T_arg5) const { return arg2; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3, T_arg4, T_arg5, T_arg6) const { return arg2; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const { return arg2; }
};

struct QEXTLambdaSelect3 : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_arg3 Type;
    };
    typedef void ResultType; // no operator ()() overload

    void operator ()() const; // not implemented
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3) const { return arg3; }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3, T_arg4) const { return arg3; }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3, T_arg4, T_arg5) const { return arg3; }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3, T_arg4, T_arg5, T_arg6) const { return arg3; }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3, T_arg4, T_arg5, T_arg6, T_arg7) const { return arg3; }
};

struct QEXTLambdaSelect4 : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_arg4 Type;
    };
    typedef void ResultType; // no operator ()() overload

    void operator ()() const; // not implemented
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    T_arg4 operator ()(T_arg1, T_arg2, T_arg3, T_arg4 arg4) const { return arg4; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    T_arg4 operator ()(T_arg1, T_arg2, T_arg3, T_arg4 arg4, T_arg5) const { return arg4; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    T_arg4 operator ()(T_arg1, T_arg2, T_arg3, T_arg4 arg4, T_arg5, T_arg6) const { return arg4; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    T_arg4 operator ()(T_arg1, T_arg2, T_arg3, T_arg4 arg4, T_arg5, T_arg6, T_arg7) const { return arg4; }
};

struct QEXTLambdaSelect5 : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_arg5 Type;
    };
    typedef void ResultType; // no operator ()() overload

    void operator ()() const; // not implemented
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    T_arg5 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 arg5) const { return arg5; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    T_arg5 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 arg5, T_arg6) const { return arg5; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    T_arg5 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 arg5, T_arg6, T_arg7) const { return arg5; }
};

struct QEXTLambdaSelect6 : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_arg6 Type;
    };
    typedef void ResultType; // no operator ()() overload

    void operator ()() const; // not implemented
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    T_arg6 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 arg6) const { return arg6; }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    T_arg6 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 arg6, T_arg7) const { return arg6; }
};

struct QEXTLambdaSelect7 : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_arg7 Type;
    };
    typedef void ResultType; // no operator ()() overload

    void operator ()() const; // not implemented
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    T_arg7 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 arg7) const { return arg7; }
};

} /* namespace qextinternal */


extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect1> g_qextLambdaSelector1;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect2> g_qextLambdaSelector2;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect3> g_qextLambdaSelector3;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect4> g_qextLambdaSelector4;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect5> g_qextLambdaSelector5;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect6> g_qextLambdaSelector6;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect7> g_qextLambdaSelector7;

namespace qextLambdaSelectors {
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect1> _1;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect2> _2;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect3> _3;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect4> _4;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect5> _5;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect6> _6;
extern QEXT_CORE_API const QEXTLambda<qextinternal::QEXTLambdaSelect7> _7;
}


#endif // QEXTLAMBDASELECT_H
