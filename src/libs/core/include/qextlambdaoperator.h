#ifndef QEXTLAMBDAOPERATOR_H
#define QEXTLAMBDAOPERATOR_H

#include <qextlambdabase.h>
#include <qexttypetrait.h>


template <typename T_type>
struct QEXTDereferenceTrait { typedef void Type; };

template <typename T_type>
struct QEXTDereferenceTrait<T_type*> { typedef T_type Type; };

template <typename T_type>
struct QEXTDereferenceTrait<const T_type*> { typedef const T_type Type; };

template <typename T_type>
struct QEXTDereferenceTrait<T_type*&> { typedef T_type Type; };

template <typename T_type>
struct QEXTDereferenceTrait<const T_type*&> { typedef const T_type Type; };

template <typename T_type>
struct QEXTDereferenceTrait<T_type* const&> { typedef T_type Type; };

template <typename T_type>
struct QEXTDereferenceTrait<const T_type* const&> { typedef const T_type Type; };

template <typename T_type>
struct arithmetic {};

template <typename T_type>
struct bitwise {};

template <typename T_type>
struct logical {};

template <typename T_type>
struct relational {};

template <typename T_type>
struct arithmetic_assign {};

template <typename T_type>
struct bitwise_assign {};

template <typename T_type>
struct other {};

template <typename T_type>
struct unary_arithmetic {};

template <typename T_type>
struct unary_bitwise {};

template <typename T_type>
struct unary_logical {};

template <typename T_type>
struct unary_other {};

template <typename T_type>
struct cast_ {};

struct plus {};
struct minus {};
struct multiplies {};
struct divides {};
struct modulus {};
struct leftshift {};
struct rightshift {};
struct and_ {};
struct or_ {};
struct xor_ {};
struct less {};
struct greater {};
struct less_equal {};
struct greater_equal {};
struct equal_to {};
struct not_equal_to {};
struct subscript {};
struct assign {};
struct pre_increment {};
struct pre_decrement {};
struct negate {};
struct not_ {};
struct address {};
struct dereference {};
struct reinterpret_ {};
struct static_ {};
struct dynamic_ {};
struct comma {};

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce
{
    typedef typename QEXTTypeTrait<T_test1>::Type Type;
}; // TODO: e.g. T_test1=int, T_test2=double yields int but it should yield double !

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<logical<T_action>, T_test1, T_test2>
{
    typedef bool Type;
};

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<relational<T_action>, T_test1, T_test2>
{
    typedef bool Type;
};

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<arithmetic_assign<T_action>, T_test1, T_test2>
{
    typedef T_test1 Type;
};

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<bitwise_assign<T_action>, T_test1, T_test2>
{
    typedef T_test1 Type;
};

template <typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<other<subscript>, T_test1, T_test2>
{
    typedef typename QEXTTypeTrait<typename QEXTDereferenceTrait<T_test1>::Type>::Pass Type;
};

template <typename T_action, typename T_test>
struct QEXTLambdaActionUnaryResultTypeDeduce
{
    typedef typename QEXTTypeTrait<T_test>::Type Type;
};

template <typename T_action, typename T_type, typename T_test>
struct LambdaActionConvertResultTypeDeduce
{
    typedef typename QEXTTypeTrait<T_type>::Type Type;
};

template <typename T_action, typename T_test>
struct QEXTLambdaActionUnaryResultTypeDeduce<unary_logical<T_action>, T_test>
{
    typedef bool Type;
};

template <typename T_test>
struct QEXTLambdaActionUnaryResultTypeDeduce<unary_other<address>, T_test>
{
    typedef typename QEXTTypeTrait<T_test>::Pointer Type;
};

template <typename T_test>
struct QEXTLambdaActionUnaryResultTypeDeduce<unary_other<dereference>, T_test>
{
    typedef typename QEXTTypeTrait<typename QEXTDereferenceTrait<T_test>::Type>::Pass Type;
};



template <typename T_action>
struct QEXTLambdaAction {};

template <typename T_action>
struct QEXTLambdaActionUnary {};

template <typename T_action, typename T_type>
struct QEXTLambdaActionConvert {};

template <>
struct QEXTLambdaAction<arithmetic<plus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic<plus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 + arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic<minus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic<minus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 - arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic<multiplies> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic<multiplies>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 * arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic<divides> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic<divides>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 / arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic<modulus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic<modulus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 % arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise<leftshift> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise<leftshift>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 << arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise<rightshift> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise<rightshift>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 >> arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise<and_> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise<and_>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1  &arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise<or_> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise<or_>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 | arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise<xor_> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise<xor_>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 ^ arg2;
    }
};

template <>
struct QEXTLambdaAction<logical<and_> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<logical<and_>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 & &arg2;
    }
};

template <>
struct QEXTLambdaAction<logical<or_> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<logical<or_>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 || arg2;
    }
};

template <>
struct QEXTLambdaAction<relational<less> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<relational<less>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 < arg2;
    }
};

template <>
struct QEXTLambdaAction<relational<greater> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<relational<greater>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 > arg2;
    }
};

template <>
struct QEXTLambdaAction<relational<less_equal> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<relational<less_equal>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 <= arg2;
    }
};

template <>
struct QEXTLambdaAction<relational<greater_equal> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<relational<greater_equal>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 >= arg2;
    }
};

template <>
struct QEXTLambdaAction<relational<equal_to> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<relational<equal_to>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 == arg2;
    }
};

template <>
struct QEXTLambdaAction<relational<not_equal_to> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<relational<not_equal_to>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 != arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic_assign<plus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic_assign<plus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 += arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic_assign<minus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic_assign<minus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 -= arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic_assign<multiplies> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic_assign<multiplies>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 *= arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic_assign<divides> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic_assign<divides>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 /= arg2;
    }
};

template <>
struct QEXTLambdaAction<arithmetic_assign<modulus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<arithmetic_assign<modulus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 %= arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise_assign<leftshift> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise_assign<leftshift>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 <<= arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise_assign<rightshift> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise_assign<rightshift>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 >>= arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise_assign<and_> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise_assign<and_>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 &= arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise_assign<or_> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise_assign<or_>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 |= arg2;
    }
};

template <>
struct QEXTLambdaAction<bitwise_assign<xor_> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<bitwise_assign<xor_>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 ^= arg2;
    }
};

template <>
struct QEXTLambdaAction<comma >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<comma, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return (void)arg1 , arg2;
    }
};

template <>
struct QEXTLambdaAction<other<subscript> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<other<subscript>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1[arg2];
    }
};

template <>
struct QEXTLambdaAction<other<assign> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<other<assign>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 = arg2;
    }
};

template <>
struct QEXTLambdaActionUnary<unary_arithmetic<pre_increment> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<unary_arithmetic<pre_increment>, T_arg>::Type
    doAction(T_arg arg) {
        return ++arg;
    }
};

template <>
struct QEXTLambdaActionUnary<unary_arithmetic<pre_decrement> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<unary_arithmetic<pre_decrement>, T_arg>::Type
    doAction(T_arg arg) {
        return --arg;
    }
};

template <>
struct QEXTLambdaActionUnary<unary_arithmetic<negate> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<unary_arithmetic<negate>, T_arg>::Type
    doAction(T_arg arg) {
        return -arg;
    }
};

template <>
struct QEXTLambdaActionUnary<unary_bitwise<not_> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<unary_bitwise<not_>, T_arg>::Type
    doAction(T_arg arg) {
        return ~arg;
    }
};

template <>
struct QEXTLambdaActionUnary<unary_logical<not_> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<unary_logical<not_>, T_arg>::Type
    doAction(T_arg arg) {
        return !arg;
    }
};

template <>
struct QEXTLambdaActionUnary<unary_other<address> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<unary_other<address>, T_arg>::Type
    doAction(T_arg arg) {
        return &arg;
    }
};

template <>
struct QEXTLambdaActionUnary<unary_other<dereference> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<unary_other<dereference>, T_arg>::Type
    doAction(T_arg arg) {
        return *arg;
    }
};

template <typename T_type>
struct QEXTLambdaActionConvert<cast_<reinterpret_>, T_type>
{
    template <typename T_arg>
    static typename LambdaActionConvertResultTypeDeduce<cast_<reinterpret_>, T_type, T_arg>::Type
    doAction(T_arg arg) {
        return reinterpret_cast<T_type>(arg);
    }
};

template <typename T_type>
struct QEXTLambdaActionConvert<cast_<static_>, T_type>
{
    template <typename T_arg>
    static typename LambdaActionConvertResultTypeDeduce<cast_<static_>, T_type, T_arg>::Type
    doAction(T_arg arg) {
        return static_cast<T_type>(arg);
    }
};

template <typename T_type>
struct QEXTLambdaActionConvert<cast_<dynamic_>, T_type>
{
    template <typename T_arg>
    static typename LambdaActionConvertResultTypeDeduce<cast_<dynamic_>, T_type, T_arg>::Type
    doAction(T_arg arg) {
        return dynamic_cast<T_type>(arg);
    }
};



template <typename T_action, typename T_type1, typename T_type2>
struct QEXTLambdaOperator : public QEXTLambdaBase
{
    typedef typename QEXTLambda<T_type1>::LambdaType Arg1Type;
    typedef typename QEXTLambda<T_type2>::LambdaType Arg2Type;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename Arg1Type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type LeftType;
        typedef typename Arg2Type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type RightType;
        typedef typename QEXTLambdaActionResultTypeDeduce<T_action, LeftType, RightType>::Type Type;
    };

    typedef typename QEXTLambdaActionResultTypeDeduce<
    T_action,
    typename Arg1Type::ResultType,
    typename Arg2Type::ResultType>::Type ResultType;

    ResultType
    operator ()() const {
        return QEXTLambdaAction<T_action>::template doAction<
                typename Arg1Type::ResultType,
                typename Arg2Type::ResultType>(m_arg1(), m_arg2());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator ()(T_arg1 arg1) const {
        return QEXTLambdaAction<T_action>::template doAction<
                typename ResultTypeDeduce<typename QEXTTypeTrait<T_arg1>::Pass>::LeftType,
                typename ResultTypeDeduce<typename QEXTTypeTrait<T_arg1>::Pass>::RightType>
                (m_arg1.template operator ()<typename QEXTTypeTrait<T_arg1>::Pass>(arg1),
                 m_arg2.template operator ()<typename QEXTTypeTrait<T_arg1>::Pass>(arg1));
    }

    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2) const {
        return QEXTLambdaAction<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>::LeftType,
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>::RightType>
                (m_arg1.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2),
                 m_arg2.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return QEXTLambdaAction<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>::LeftType,
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>::RightType>
                (m_arg1.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3),
                 m_arg2.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return QEXTLambdaAction<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>::LeftType,
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>::RightType>
                (m_arg1.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4),
                 m_arg2.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return QEXTLambdaAction<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>::LeftType,
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>::RightType>
                (m_arg1.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5),
                 m_arg2.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return QEXTLambdaAction<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>::LeftType,
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>::RightType>
                (m_arg1.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass,
                 typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6),
                 m_arg2.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass,
                 typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const
    {
        return QEXTLambdaAction<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>::LeftType,
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>::RightType>
                (m_arg1.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass,
                 typename QEXTTypeTrait<T_arg6>::Pass,
                 typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7),
                 m_arg2.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass,
                 typename QEXTTypeTrait<T_arg6>::Pass,
                 typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }


    QEXTLambdaOperator(typename QEXTTypeTrait<T_type1>::Take arg1, typename QEXTTypeTrait<T_type2>::Take arg2)
        : m_arg1(arg1), m_arg2(arg2) {}

    Arg1Type m_arg1;
    Arg2Type m_arg2;
};



//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
template <typename T_lambda_action, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTLambdaOperator<T_lambda_action, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTLambdaOperator<T_lambda_action, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_arg1);
        qextVisitEach(action, target.m_arg2);
    }
};


template <typename T_action, typename T_type>
struct QEXTLambdaOperatorUnary : public QEXTLambdaBase
{
    typedef typename QEXTLambda<T_type>::LambdaType ArgType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename ArgType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type OperandType;
        typedef typename QEXTLambdaActionUnaryResultTypeDeduce<T_action, OperandType>::Type Type;
    };
    typedef typename QEXTLambdaActionUnaryResultTypeDeduce<
    T_action,
    typename ArgType::ResultType>::Type ResultType;

    ResultType
    operator ()() const {
        return QEXTLambdaActionUnary<T_action>::template doAction<
                typename ArgType::ResultType>(m_arg());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator ()(T_arg1 arg1) const {
        return QEXTLambdaActionUnary<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass>(arg1));
    }


    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2) const {
        return QEXTLambdaActionUnary<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return QEXTLambdaActionUnary<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return QEXTLambdaActionUnary<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4));
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return QEXTLambdaActionUnary<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return QEXTLambdaActionUnary<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass,
                 typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return QEXTLambdaActionUnary<T_action>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass,
                 typename QEXTTypeTrait<T_arg6>::Pass,
                 typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }


    QEXTLambdaOperatorUnary(typename QEXTTypeTrait<T_type>::Take arg)
        : m_arg(arg) {}

    ArgType m_arg;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
template <typename T_lambda_action, typename T_arg>
struct QEXTVisitor<QEXTLambdaOperatorUnary<T_lambda_action, T_arg> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTLambdaOperatorUnary<T_lambda_action, T_arg> &target) {
        qextVisitEach(action, target.m_arg);
    }
};


template <typename T_action, typename T_type, typename T_arg>
struct QEXTLambdaOperatorConvert : public QEXTLambdaBase
{
    typedef typename QEXTLambda<T_arg>::LambdaType ArgType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename ArgType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type OperandType;
        typedef typename LambdaActionConvertResultTypeDeduce<T_action, T_type, OperandType>::Type Type;
    };

    typedef typename LambdaActionConvertResultTypeDeduce<
    T_action, T_type,
    typename ArgType::ResultType>::Type ResultType;

    ResultType
    operator ()() const {
        return QEXTLambdaActionConvert<T_action, T_type>::template doAction<
                typename ArgType::ResultType>(m_arg());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator ()(T_arg1 arg1) const {
        return QEXTLambdaActionConvert<T_action, T_type>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass>(arg1));
    }


    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2) const {
        return QEXTLambdaActionConvert<T_action, T_type>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return QEXTLambdaActionConvert<T_action, T_type>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return QEXTLambdaActionConvert<T_action, T_type>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return QEXTLambdaActionConvert<T_action, T_type>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return QEXTLambdaActionConvert<T_action, T_type>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass,
                 typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return QEXTLambdaActionConvert<T_action, T_type>::template doAction<
                typename ResultTypeDeduce<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>::OperandType>
                (m_arg.template operator ()<
                 typename QEXTTypeTrait<T_arg1>::Pass,
                 typename QEXTTypeTrait<T_arg2>::Pass,
                 typename QEXTTypeTrait<T_arg3>::Pass,
                 typename QEXTTypeTrait<T_arg4>::Pass,
                 typename QEXTTypeTrait<T_arg5>::Pass,
                 typename QEXTTypeTrait<T_arg6>::Pass,
                 typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }


    QEXTLambdaOperatorConvert(typename QEXTTypeTrait<T_arg>::Take arg)
        : m_arg(arg) {}

    ArgType m_arg;
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
template <typename T_lambda_action, typename T_type, typename T_arg>
struct QEXTVisitor<QEXTLambdaOperatorConvert<T_lambda_action, T_type, T_arg> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTLambdaOperatorConvert<T_lambda_action, T_type, T_arg> &target) {
        qextVisitEach(action, target.m_arg);
    }
};

// Operators for QEXTLambda action arithmetic<plus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<plus>, T_arg1, T_arg2> >
operator + (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<plus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<plus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator + (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic<plus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<plus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator + (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<plus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic<minus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<minus>, T_arg1, T_arg2> >
operator - (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<minus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<minus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator - (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic<minus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<minus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator - (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<minus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic<multiplies>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<multiplies>, T_arg1, T_arg2> >
operator * (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<multiplies>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<multiplies>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator * (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic<multiplies>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<multiplies>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator * (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<multiplies>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic<divides>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<divides>, T_arg1, T_arg2> >
operator / (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<divides>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<divides>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator / (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic<divides>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<divides>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator / (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<divides>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic<modulus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<modulus>, T_arg1, T_arg2> >
operator % (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<modulus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<modulus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator % (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic<modulus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic<modulus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator % (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic<modulus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise<leftshift>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<leftshift>, T_arg1, T_arg2> >
operator << (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<leftshift>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<leftshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator << (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise<leftshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<leftshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator << (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<leftshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise<rightshift>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<rightshift>, T_arg1, T_arg2> >
operator >> (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<rightshift>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<rightshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator >> (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise<rightshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<rightshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator >> (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<rightshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise<and_>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<and_>, T_arg1, T_arg2> >
operator & (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<and_>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<and_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator & (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise<and_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<and_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator & (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<and_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise<or_>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<or_>, T_arg1, T_arg2> >
operator | (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<or_>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<or_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator | (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise<or_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<or_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator | (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<or_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise<xor_>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<xor_>, T_arg1, T_arg2> >
operator ^ (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<xor_>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<xor_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator ^ (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise<xor_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise<xor_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator ^ (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise<xor_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action logical<and_>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<logical<and_>, T_arg1, T_arg2> >
operator && (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<logical<and_>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<logical<and_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator && (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<logical<and_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<logical<and_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator && (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<logical<and_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action logical<or_>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<logical<or_>, T_arg1, T_arg2> >
operator || (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<logical<or_>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<logical<or_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator || (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<logical<or_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<logical<or_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator || (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<logical<or_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action relational<less>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<less>, T_arg1, T_arg2> >
operator < (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<less>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<less>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator < (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<relational<less>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<less>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator < (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<less>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action relational<greater>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<greater>, T_arg1, T_arg2> >
operator > (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<greater>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<greater>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator > (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<relational<greater>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<greater>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator > (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<greater>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action relational<less_equal>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<less_equal>, T_arg1, T_arg2> >
operator <= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<less_equal>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<less_equal>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator <= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<relational<less_equal>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<less_equal>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator <= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<less_equal>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action relational<greater_equal>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<greater_equal>, T_arg1, T_arg2> >
operator >= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<greater_equal>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<greater_equal>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator >= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<relational<greater_equal>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<greater_equal>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator >= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<greater_equal>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action relational<equal_to>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<equal_to>, T_arg1, T_arg2> >
operator == (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<equal_to>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<equal_to>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator == (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<relational<equal_to>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<equal_to>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator == (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<equal_to>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action relational<not_equal_to>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<not_equal_to>, T_arg1, T_arg2> >
operator != (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<not_equal_to>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<not_equal_to>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator != (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<relational<not_equal_to>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<relational<not_equal_to>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator != (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<relational<not_equal_to>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic_assign<plus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<plus>, T_arg1, T_arg2> >
operator += (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<plus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<plus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator += (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<plus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<plus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator += (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<plus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic_assign<minus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<minus>, T_arg1, T_arg2> >
operator -= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<minus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<minus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator -= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<minus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<minus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator -= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<minus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic_assign<multiplies>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<multiplies>, T_arg1, T_arg2> >
operator *= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<multiplies>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<multiplies>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator *= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<multiplies>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<multiplies>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator *= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<multiplies>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic_assign<divides>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<divides>, T_arg1, T_arg2> >
operator /= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<divides>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<divides>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator /= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<divides>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<divides>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator /= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<divides>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action arithmetic_assign<modulus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<modulus>, T_arg1, T_arg2> >
operator %= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<modulus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<modulus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator %= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<modulus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<arithmetic_assign<modulus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator %= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<arithmetic_assign<modulus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise_assign<leftshift>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<leftshift>, T_arg1, T_arg2> >
operator <<= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<leftshift>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<leftshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator <<= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<leftshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<leftshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator <<= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<leftshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise_assign<rightshift>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<rightshift>, T_arg1, T_arg2> >
operator >>= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<rightshift>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<rightshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator >>= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<rightshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<rightshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator >>= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<rightshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise_assign<and_>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<and_>, T_arg1, T_arg2> >
operator &= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<and_>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<and_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator &= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<and_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<and_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator &= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<and_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise_assign<or_>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<or_>, T_arg1, T_arg2> >
operator |= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<or_>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<or_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator |= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<or_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<or_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator |= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<or_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action bitwise_assign<xor_>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<xor_>, T_arg1, T_arg2> >
operator ^= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<xor_>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<xor_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator ^= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<xor_>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<bitwise_assign<xor_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator ^= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<bitwise_assign<xor_>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action comma. For comma we require that both arguments needs to be of Type lamdba
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<comma, T_arg1, T_arg2> >
operator , (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<comma, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

// Operator for QEXTLambda action unary_arithmetic<pre_increment>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<unary_arithmetic<pre_increment>, T_arg> >
operator ++ (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<unary_arithmetic<pre_increment>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action unary_arithmetic<pre_decrement>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<unary_arithmetic<pre_decrement>, T_arg> >
operator -- (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<unary_arithmetic<pre_decrement>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action unary_arithmetic<negate>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<unary_arithmetic<negate>, T_arg> >
operator - (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<unary_arithmetic<negate>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action unary_bitwise<not_>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<unary_bitwise<not_>, T_arg> >
operator ~ (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<unary_bitwise<not_>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action unary_logical<not_>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<unary_logical<not_>, T_arg> >
operator ! (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<unary_logical<not_>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action unary_other<address>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<unary_other<address>, T_arg> >
operator & (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<unary_other<address>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action unary_other<dereference>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<unary_other<dereference>, T_arg> >
operator * (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<unary_other<dereference>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Creators for QEXTLambda action cast_<reinterpret_>.
template <typename T_type, typename T_arg>
QEXTLambda<QEXTLambdaOperatorConvert<cast_<reinterpret_>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> >
reinterpret_cast_(const T_arg &arg) {
    typedef QEXTLambdaOperatorConvert<cast_<reinterpret_>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(qextUnwrapLambdaValue(arg)));
}

// Creators for QEXTLambda action cast_<static_>.
template <typename T_type, typename T_arg>
QEXTLambda<QEXTLambdaOperatorConvert<cast_<static_>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> >
static_cast_(const T_arg &arg) {
    typedef QEXTLambdaOperatorConvert<cast_<static_>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(qextUnwrapLambdaValue(arg)));
}

// Creators for QEXTLambda action cast_<dynamic_>.
template <typename T_type, typename T_arg>
QEXTLambda<QEXTLambdaOperatorConvert<cast_<dynamic_>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> >
dynamic_cast_(const T_arg &arg) {
    typedef QEXTLambdaOperatorConvert<cast_<dynamic_>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(qextUnwrapLambdaValue(arg)));
}



#endif // QEXTLAMBDAOPERATOR_H
