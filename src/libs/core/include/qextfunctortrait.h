#ifndef QEXTFUNCTORTRAIT_H
#define QEXTFUNCTORTRAIT_H

#include <qextglobal.h>
#include <qexttypetrait.h>

#include <QString>

struct QEXTFunctorBase {
    typedef void ResultType;
    typedef void ObjectType;
    virtual ~QEXTFunctorBase() {}
};

template <typename T_functor, bool I_derives_functor_base = QEXTBaseAndDerivedTester<QEXTFunctorBase, T_functor>::value>
struct QEXTFunctorTrait
{
    typedef void ResultType;
    typedef void ObjectType;
    typedef T_functor FunctorType;

    QString typeName() const { return "UnknownCustom"; }
};

template <typename T_functor>
struct QEXTFunctorTrait<T_functor, true>
{
    typedef typename T_functor::ResultType ResultType;
    typedef typename T_functor::ObjectType ObjectType;
    typedef T_functor FunctorType;

    QString typeName() const { return "QEXTFunctorBase"; }
};


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7> class QEXTPointerFunctor7;
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTFunctorTrait<T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7), false>
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QEXTPointerFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> FunctorType;

    QString typeName() const { return "QEXTPointerFunctor7"; }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6> class QEXTPointerFunctor6;
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTFunctorTrait<T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6), false>
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QEXTPointerFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> FunctorType;

    QString typeName() const { return "QEXTPointerFunctor6"; }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5> class QEXTPointerFunctor5;
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTFunctorTrait<T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5), false>
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QEXTPointerFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> FunctorType;

    QString typeName() const { return "QEXTPointerFunctor5"; }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4> class QEXTPointerFunctor4;
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTFunctorTrait<T_return (*)(T_arg1, T_arg2, T_arg3, T_arg4), false>
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QEXTPointerFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4> FunctorType;

    QString typeName() const { return "QEXTPointerFunctor4"; }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3> class QEXTPointerFunctor3;
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTFunctorTrait<T_return (*)(T_arg1, T_arg2, T_arg3), false>
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QEXTPointerFunctor3<T_return, T_arg1, T_arg2, T_arg3> FunctorType;

    QString typeName() const { return "QEXTPointerFunctor3"; }
};

template <typename T_return, typename T_arg1, typename T_arg2> class QEXTPointerFunctor2;
template <typename T_return, typename T_arg1, typename T_arg2>
struct QEXTFunctorTrait<T_return (*)(T_arg1, T_arg2), false>
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QEXTPointerFunctor2<T_return, T_arg1, T_arg2> FunctorType;

    QString typeName() const { return "QEXTPointerFunctor2"; }
};

template <typename T_return, typename T_arg1> class QEXTPointerFunctor1;
template <typename T_return, typename T_arg1>
struct QEXTFunctorTrait<T_return (*)(T_arg1), false>
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QEXTPointerFunctor1<T_return, T_arg1> FunctorType;

    QString typeName() const { return "QEXTPointerFunctor1"; }
};

template <typename T_return> class QEXTPointerFunctor0;
template <typename T_return>
struct QEXTFunctorTrait<T_return (*)(), false>
{
    typedef T_return ResultType;
    typedef void ObjectType;
    typedef QEXTPointerFunctor0<T_return> FunctorType;

    QString typeName() const { return "QEXTPointerFunctor0"; }
};




template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7> class QEXTMemberFunctor7;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7> class QEXTConstMemberFunctor7;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7> class QEXTVolatileMemberFunctor7;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7> class QEXTConstVolatileMemberFunctor7;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7), false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> FunctorType;

    QString typeName() const { return "QEXTMemberFunctor7"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> FunctorType;

    QString typeName() const { return "QEXTConstMemberFunctor7"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> FunctorType;

    QString typeName() const { return "QEXTVolatileMemberFunctor7"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> FunctorType;

    QString typeName() const { return "QEXTConstVolatileMemberFunctor7"; }
};


template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6> class QEXTMemberFunctor6;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6> class QEXTConstMemberFunctor6;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6> class QEXTVolatileMemberFunctor6;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6> class QEXTConstVolatileMemberFunctor6;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6), false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> FunctorType;

    QString typeName() const { return "QEXTMemberFunctor6"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> FunctorType;

    QString typeName() const { return "QEXTConstMemberFunctor6"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> FunctorType;

    QString typeName() const { return "QEXTVolatileMemberFunctor6"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> FunctorType;

    QString typeName() const { return "QEXTConstVolatileMemberFunctor6"; }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5> class QEXTMemberFunctor5;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5> class QEXTConstMemberFunctor5;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5> class QEXTVolatileMemberFunctor5;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5> class QEXTConstVolatileMemberFunctor5;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5), false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> FunctorType;

    QString typeName() const { return "QEXTMemberFunctor5"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> FunctorType;

    QString typeName() const { return "QEXTConstMemberFunctor5"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> FunctorType;

    QString typeName() const { return "QEXTVolatileMemberFunctor5"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> FunctorType;

    QString typeName() const { return "QEXTConstVolatileMemberFunctor5"; }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4> class QEXTMemberFunctor4;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4> class QEXTConstMemberFunctor4;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4> class QEXTVolatileMemberFunctor4;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4> class QEXTConstVolatileMemberFunctor4;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4), false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> FunctorType;

    QString typeName() const { return "QEXTMemberFunctor4"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) const, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> FunctorType;

    QString typeName() const { return "QEXTConstMemberFunctor4"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> FunctorType;

    QString typeName() const { return "QEXTVolatileMemberFunctor4"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> FunctorType;

    QString typeName() const { return "QEXTConstVolatileMemberFunctor4"; }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3> class QEXTMemberFunctor3;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3> class QEXTConstMemberFunctor3;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3> class QEXTVolatileMemberFunctor3;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3> class QEXTConstVolatileMemberFunctor3;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3), false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> FunctorType;

    QString typeName() const { return "QEXTMemberFunctor3"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) const, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> FunctorType;

    QString typeName() const { return "QEXTConstMemberFunctor3"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> FunctorType;

    QString typeName() const { return "QEXTVolatileMemberFunctor3"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2, T_arg3) const volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> FunctorType;

    QString typeName() const { return "QEXTConstVolatileMemberFunctor3"; }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2> class QEXTMemberFunctor2;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2> class QEXTConstMemberFunctor2;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2> class QEXTVolatileMemberFunctor2;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2> class QEXTConstVolatileMemberFunctor2;
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2), false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> FunctorType;

    QString typeName() const { return "QEXTMemberFunctor2"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2) const, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> FunctorType;

    QString typeName() const { return "QEXTConstMemberFunctor2"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2) volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> FunctorType;

    QString typeName() const { return "QEXTVolatileMemberFunctor2"; }
};
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1, T_arg2) const volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> FunctorType;

    QString typeName() const { return "QEXTConstVolatileMemberFunctor2"; }
};

template <typename T_return, typename T_obj, typename T_arg1> class QEXTMemberFunctor1;
template <typename T_return, typename T_obj, typename T_arg1> class QEXTConstMemberFunctor1;
template <typename T_return, typename T_obj, typename T_arg1> class QEXTVolatileMemberFunctor1;
template <typename T_return, typename T_obj, typename T_arg1> class QEXTConstVolatileMemberFunctor1;
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1), false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTMemberFunctor1<T_return, T_obj, T_arg1> FunctorType;

    QString typeName() const { return "QEXTMemberFunctor1"; }
};
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1) const, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstMemberFunctor1<T_return, T_obj, T_arg1> FunctorType;

    QString typeName() const { return "QEXTConstMemberFunctor1"; }
};
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1) volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1> FunctorType;

    QString typeName() const { return "QEXTVolatileMemberFunctor1"; }
};
template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTFunctorTrait<T_return (T_obj::*)(T_arg1) const volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> FunctorType;

    QString typeName() const { return "QEXTConstVolatileMemberFunctor1"; }
};

template <typename T_return, typename T_obj> class QEXTMemberFunctor0;
template <typename T_return, typename T_obj> class QEXTConstMemberFunctor0;
template <typename T_return, typename T_obj> class QEXTVolatileMemberFunctor0;
template <typename T_return, typename T_obj> class QEXTConstVolatileMemberFunctor0;
template <typename T_return, typename T_obj>
struct QEXTFunctorTrait<T_return (T_obj::*)(), false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTMemberFunctor0<T_return, T_obj> FunctorType;

    QString typeName() const { return "QEXTMemberFunctor0"; }
};
template <typename T_return, typename T_obj>
struct QEXTFunctorTrait<T_return (T_obj::*)() const, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstMemberFunctor0<T_return, T_obj> FunctorType;

    QString typeName() const { return "QEXTConstMemberFunctor0"; }
};
template <typename T_return, typename T_obj>
struct QEXTFunctorTrait<T_return (T_obj::*)() volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTVolatileMemberFunctor0<T_return, T_obj> FunctorType;

    QString typeName() const { return "QEXTVolatileMemberFunctor0"; }
};
template <typename T_return, typename T_obj>
struct QEXTFunctorTrait<T_return (T_obj::*)() const volatile, false>
{
    typedef T_return ResultType;
    typedef T_obj ObjectType;
    typedef QEXTConstVolatileMemberFunctor0<T_return, T_obj> FunctorType;

    QString typeName() const { return "QEXTConstVolatileMemberFunctor0"; }
};

#endif // QEXTFUNCTORTRAIT_H
