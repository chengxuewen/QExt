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
// LambdaOperator LBOPR
template <typename T_type>
struct QEXTLBOPRArithmetic {};

template <typename T_type>
struct QEXTLBOPRBitwise {};

template <typename T_type>
struct QEXTLBOPRLogical {};

template <typename T_type>
struct QEXTLBOPRRelational {};

template <typename T_type>
struct QEXTLBOPRArithmeticAssign {};

template <typename T_type>
struct QEXTLBOPRBitwiseAssign {};

template <typename T_type>
struct QEXTLBOPROther {};

template <typename T_type>
struct QEXTLBOPRUnaryArithmetic {};

template <typename T_type>
struct QEXTLBOPRUnaryBitwise {};

template <typename T_type>
struct QEXTLBOPRUnaryLogical {};

template <typename T_type>
struct QEXTLBOPRUnaryOther {};

template <typename T_type>
struct QEXTLBOPRCast {};

struct QEXTLBOPRPlus {};
struct QEXTLBOPRMinus {};
struct QEXTLBOPRMultiplies {};
struct QEXTLBOPRDivides {};
struct QEXTLBOPRModulus {};
struct QEXTLBOPRLeftshift {};
struct QEXTLBOPRRightshift {};
struct QEXTLBOPRAnd {};
struct QEXTLBOPROr {};
struct QEXTLBOPRXor {};
struct QEXTLBOPRLess {};
struct QEXTLBOPRGreater {};
struct QEXTLBOPRLessEqual {};
struct QEXTLBOPRGreaterEqual {};
struct QEXTLBOPREqualTo {};
struct QEXTLBOPRNotEqualTo {};
struct QEXTLBOPRSubscript {};
struct QEXTLBOPRAssign {};
struct QEXTLBOPRPreIncrement {};
struct QEXTLBOPRPreDecrement {};
struct QEXTLBOPRNegate {};
struct QEXTLBOPRNot {};
struct QEXTLBOPRAddress {};
struct QEXTLBOPRDereference {};
struct QEXTLBOPRReinterpret {};
struct QEXTLBOPRStatic {};
struct QEXTLBOPRDynamic {};
struct QEXTLBOPRComma {};

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce
{
    typedef typename QEXTTypeTrait<T_test1>::Type Type;
}; // TODO: e.g. T_test1=int, T_test2=double yields int but it should yield double !

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<QEXTLBOPRLogical<T_action>, T_test1, T_test2>
{
    typedef bool Type;
};

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<QEXTLBOPRRelational<T_action>, T_test1, T_test2>
{
    typedef bool Type;
};

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmeticAssign<T_action>, T_test1, T_test2>
{
    typedef T_test1 Type;
};

template <typename T_action, typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwiseAssign<T_action>, T_test1, T_test2>
{
    typedef T_test1 Type;
};

template <typename T_test1, typename T_test2>
struct QEXTLambdaActionResultTypeDeduce<QEXTLBOPROther<QEXTLBOPRSubscript>, T_test1, T_test2>
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
struct QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryLogical<T_action>, T_test>
{
    typedef bool Type;
};

template <typename T_test>
struct QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryOther<QEXTLBOPRAddress>, T_test>
{
    typedef typename QEXTTypeTrait<T_test>::Pointer Type;
};

template <typename T_test>
struct QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryOther<QEXTLBOPRDereference>, T_test>
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
struct QEXTLambdaAction<QEXTLBOPRArithmetic<QEXTLBOPRPlus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmetic<QEXTLBOPRPlus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 + arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmetic<QEXTLBOPRMinus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmetic<QEXTLBOPRMinus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 - arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmetic<QEXTLBOPRMultiplies> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmetic<QEXTLBOPRMultiplies>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 * arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmetic<QEXTLBOPRDivides> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmetic<QEXTLBOPRDivides>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 / arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmetic<QEXTLBOPRModulus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmetic<QEXTLBOPRModulus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 % arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwise<QEXTLBOPRLeftshift> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 << arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwise<QEXTLBOPRRightshift> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwise<QEXTLBOPRRightshift>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 >> arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwise<QEXTLBOPRAnd> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwise<QEXTLBOPRAnd>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1  &arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwise<QEXTLBOPROr> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwise<QEXTLBOPROr>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 | arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwise<QEXTLBOPRXor> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwise<QEXTLBOPRXor>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 ^ arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRLogical<QEXTLBOPRAnd> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRLogical<QEXTLBOPRAnd>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 & &arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRLogical<QEXTLBOPROr> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRLogical<QEXTLBOPROr>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 || arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRRelational<QEXTLBOPRLess> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRRelational<QEXTLBOPRLess>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 < arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRRelational<QEXTLBOPRGreater> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRRelational<QEXTLBOPRGreater>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 > arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRRelational<QEXTLBOPRLessEqual> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRRelational<QEXTLBOPRLessEqual>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 <= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRRelational<QEXTLBOPRGreaterEqual> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRRelational<QEXTLBOPRGreaterEqual>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 >= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRRelational<QEXTLBOPREqualTo> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRRelational<QEXTLBOPREqualTo>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 == arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRRelational<QEXTLBOPRNotEqualTo> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRRelational<QEXTLBOPRNotEqualTo>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 != arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 += arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 -= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 *= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 /= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 %= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 <<= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 >>= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 &= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwiseAssign<QEXTLBOPROr> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwiseAssign<QEXTLBOPROr>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 |= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRBitwiseAssign<QEXTLBOPRXor> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRBitwiseAssign<QEXTLBOPRXor>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 ^= arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPRComma >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPRComma, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return (void)arg1 , arg2;
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPROther<QEXTLBOPRSubscript> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPROther<QEXTLBOPRSubscript>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1[arg2];
    }
};

template <>
struct QEXTLambdaAction<QEXTLBOPROther<QEXTLBOPRAssign> >
{
    template <typename T_arg1, typename T_arg2>
    static typename QEXTLambdaActionResultTypeDeduce<QEXTLBOPROther<QEXTLBOPRAssign>, T_arg1, T_arg2>::Type
    doAction(T_arg1 arg1, T_arg2 arg2) {
        return arg1 = arg2;
    }
};

template <>
struct QEXTLambdaActionUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreIncrement> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreIncrement>, T_arg>::Type
    doAction(T_arg arg) {
        return ++arg;
    }
};

template <>
struct QEXTLambdaActionUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreDecrement> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreDecrement>, T_arg>::Type
    doAction(T_arg arg) {
        return --arg;
    }
};

template <>
struct QEXTLambdaActionUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRNegate> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryArithmetic<QEXTLBOPRNegate>, T_arg>::Type
    doAction(T_arg arg) {
        return -arg;
    }
};

template <>
struct QEXTLambdaActionUnary<QEXTLBOPRUnaryBitwise<QEXTLBOPRNot> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryBitwise<QEXTLBOPRNot>, T_arg>::Type
    doAction(T_arg arg) {
        return ~arg;
    }
};

template <>
struct QEXTLambdaActionUnary<QEXTLBOPRUnaryLogical<QEXTLBOPRNot> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryLogical<QEXTLBOPRNot>, T_arg>::Type
    doAction(T_arg arg) {
        return !arg;
    }
};

template <>
struct QEXTLambdaActionUnary<QEXTLBOPRUnaryOther<QEXTLBOPRAddress> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryOther<QEXTLBOPRAddress>, T_arg>::Type
    doAction(T_arg arg) {
        return &arg;
    }
};

template <>
struct QEXTLambdaActionUnary<QEXTLBOPRUnaryOther<QEXTLBOPRDereference> >
{
    template <typename T_arg>
    static typename QEXTLambdaActionUnaryResultTypeDeduce<QEXTLBOPRUnaryOther<QEXTLBOPRDereference>, T_arg>::Type
    doAction(T_arg arg) {
        return *arg;
    }
};

template <typename T_type>
struct QEXTLambdaActionConvert<QEXTLBOPRCast<QEXTLBOPRReinterpret>, T_type>
{
    template <typename T_arg>
    static typename LambdaActionConvertResultTypeDeduce<QEXTLBOPRCast<QEXTLBOPRReinterpret>, T_type, T_arg>::Type
    doAction(T_arg arg) {
        return reinterpret_cast<T_type>(arg);
    }
};

template <typename T_type>
struct QEXTLambdaActionConvert<QEXTLBOPRCast<QEXTLBOPRStatic>, T_type>
{
    template <typename T_arg>
    static typename LambdaActionConvertResultTypeDeduce<QEXTLBOPRCast<QEXTLBOPRStatic>, T_type, T_arg>::Type
    doAction(T_arg arg) {
        return static_cast<T_type>(arg);
    }
};

template <typename T_type>
struct QEXTLambdaActionConvert<QEXTLBOPRCast<QEXTLBOPRDynamic>, T_type>
{
    template <typename T_arg>
    static typename LambdaActionConvertResultTypeDeduce<QEXTLBOPRCast<QEXTLBOPRDynamic>, T_type, T_arg>::Type
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

// Operators for QEXTLambda action QEXTLBOPRArithmetic<QEXTLBOPRPlus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRPlus>, T_arg1, T_arg2> >
operator + (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRPlus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRPlus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator + (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRPlus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRPlus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator + (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRPlus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmetic<QEXTLBOPRMinus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMinus>, T_arg1, T_arg2> >
operator - (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMinus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMinus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator - (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMinus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMinus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator - (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMinus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmetic<QEXTLBOPRMultiplies>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMultiplies>, T_arg1, T_arg2> >
operator * (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMultiplies>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMultiplies>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator * (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMultiplies>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMultiplies>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator * (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRMultiplies>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmetic<QEXTLBOPRDivides>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRDivides>, T_arg1, T_arg2> >
operator / (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRDivides>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRDivides>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator / (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRDivides>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRDivides>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator / (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRDivides>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmetic<QEXTLBOPRModulus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRModulus>, T_arg1, T_arg2> >
operator % (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRModulus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRModulus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator % (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRModulus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRModulus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator % (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmetic<QEXTLBOPRModulus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwise<QEXTLBOPRLeftshift>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, T_arg1, T_arg2> >
operator << (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator << (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator << (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwise<QEXTLBOPRRightshift>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRRightshift>, T_arg1, T_arg2> >
operator >> (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRRightshift>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRRightshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator >> (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRRightshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRRightshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator >> (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRRightshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwise<QEXTLBOPRAnd>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRAnd>, T_arg1, T_arg2> >
operator & (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRAnd>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRAnd>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator & (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRAnd>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRAnd>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator & (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRAnd>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwise<QEXTLBOPROr>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPROr>, T_arg1, T_arg2> >
operator | (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPROr>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPROr>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator | (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPROr>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPROr>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator | (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPROr>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwise<QEXTLBOPRXor>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRXor>, T_arg1, T_arg2> >
operator ^ (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRXor>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRXor>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator ^ (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRXor>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRXor>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator ^ (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwise<QEXTLBOPRXor>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRLogical<QEXTLBOPRAnd>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPRAnd>, T_arg1, T_arg2> >
operator && (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPRAnd>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPRAnd>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator && (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPRAnd>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPRAnd>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator && (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPRAnd>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRLogical<QEXTLBOPROr>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPROr>, T_arg1, T_arg2> >
operator || (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPROr>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPROr>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator || (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPROr>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPROr>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator || (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRLogical<QEXTLBOPROr>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRRelational<QEXTLBOPRLess>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLess>, T_arg1, T_arg2> >
operator < (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLess>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLess>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator < (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLess>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLess>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator < (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLess>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRRelational<QEXTLBOPRGreater>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreater>, T_arg1, T_arg2> >
operator > (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreater>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreater>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator > (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreater>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreater>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator > (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreater>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRRelational<QEXTLBOPRLessEqual>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLessEqual>, T_arg1, T_arg2> >
operator <= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLessEqual>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLessEqual>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator <= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLessEqual>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLessEqual>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator <= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRLessEqual>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRRelational<QEXTLBOPRGreaterEqual>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreaterEqual>, T_arg1, T_arg2> >
operator >= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreaterEqual>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreaterEqual>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator >= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreaterEqual>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreaterEqual>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator >= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRGreaterEqual>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRRelational<QEXTLBOPREqualTo>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPREqualTo>, T_arg1, T_arg2> >
operator == (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPREqualTo>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPREqualTo>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator == (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPREqualTo>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPREqualTo>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator == (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPREqualTo>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRRelational<QEXTLBOPRNotEqualTo>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRNotEqualTo>, T_arg1, T_arg2> >
operator != (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRNotEqualTo>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRNotEqualTo>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator != (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRNotEqualTo>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRNotEqualTo>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator != (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRRelational<QEXTLBOPRNotEqualTo>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus>, T_arg1, T_arg2> >
operator += (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator += (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator += (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRPlus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus>, T_arg1, T_arg2> >
operator -= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator -= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator -= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMinus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies>, T_arg1, T_arg2> >
operator *= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator *= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator *= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRMultiplies>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides>, T_arg1, T_arg2> >
operator /= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator /= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator /= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRDivides>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus>, T_arg1, T_arg2> >
operator %= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator %= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator %= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRArithmeticAssign<QEXTLBOPRModulus>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift>, T_arg1, T_arg2> >
operator <<= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator <<= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator <<= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRLeftshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift>, T_arg1, T_arg2> >
operator >>= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator >>= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator >>= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRRightshift>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd>, T_arg1, T_arg2> >
operator &= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator &= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator &= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRAnd>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwiseAssign<QEXTLBOPROr>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPROr>, T_arg1, T_arg2> >
operator |= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPROr>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPROr>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator |= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPROr>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPROr>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator |= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPROr>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRBitwiseAssign<QEXTLBOPRXor>. At least one of the arguments needs to be of Type lamdba, hence the overloads.
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRXor>, T_arg1, T_arg2> >
operator ^= (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRXor>, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRXor>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> >
operator ^= (const QEXTLambda<T_arg1> &arg1, const T_arg2 &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRXor>, T_arg1, typename QEXTUnwrapReference<T_arg2>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2));
}

template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRXor>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> >
operator ^= (const T_arg1 &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRBitwiseAssign<QEXTLBOPRXor>, typename QEXTUnwrapReference<T_arg1>::Type, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1, arg2.m_value));
}

// Operators for QEXTLambda action QEXTLBOPRComma. For QEXTLBOPRComma we require that both arguments needs to be of Type lamdba
template <typename T_arg1, typename T_arg2>
QEXTLambda<QEXTLambdaOperator<QEXTLBOPRComma, T_arg1, T_arg2> >
operator , (const QEXTLambda<T_arg1> &arg1, const QEXTLambda<T_arg2> &arg2) {
    typedef QEXTLambdaOperator<QEXTLBOPRComma, T_arg1, T_arg2> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg1.m_value, arg2.m_value));
}

// Operator for QEXTLambda action QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreIncrement>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreIncrement>, T_arg> >
operator ++ (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreIncrement>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreDecrement>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreDecrement>, T_arg> >
operator -- (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRPreDecrement>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action QEXTLBOPRUnaryArithmetic<QEXTLBOPRNegate>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRNegate>, T_arg> >
operator - (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<QEXTLBOPRUnaryArithmetic<QEXTLBOPRNegate>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action QEXTLBOPRUnaryBitwise<QEXTLBOPRNot>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<QEXTLBOPRUnaryBitwise<QEXTLBOPRNot>, T_arg> >
operator ~ (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<QEXTLBOPRUnaryBitwise<QEXTLBOPRNot>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action QEXTLBOPRUnaryLogical<QEXTLBOPRNot>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<QEXTLBOPRUnaryLogical<QEXTLBOPRNot>, T_arg> >
operator ! (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<QEXTLBOPRUnaryLogical<QEXTLBOPRNot>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action QEXTLBOPRUnaryOther<QEXTLBOPRAddress>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<QEXTLBOPRUnaryOther<QEXTLBOPRAddress>, T_arg> >
operator & (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<QEXTLBOPRUnaryOther<QEXTLBOPRAddress>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Operator for QEXTLambda action QEXTLBOPRUnaryOther<QEXTLBOPRDereference>.
template <typename T_arg>
QEXTLambda<QEXTLambdaOperatorUnary<QEXTLBOPRUnaryOther<QEXTLBOPRDereference>, T_arg> >
operator * (const QEXTLambda<T_arg> &arg) {
    typedef QEXTLambdaOperatorUnary<QEXTLBOPRUnaryOther<QEXTLBOPRDereference>, T_arg> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(arg.m_value));
}

// Creators for QEXTLambda action QEXTLBOPRCast<QEXTLBOPRReinterpret>.
template <typename T_type, typename T_arg>
QEXTLambda<QEXTLambdaOperatorConvert<QEXTLBOPRCast<QEXTLBOPRReinterpret>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> >
qextLambdaReinterpretCast(const T_arg &arg) {
    typedef QEXTLambdaOperatorConvert<QEXTLBOPRCast<QEXTLBOPRReinterpret>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(qextUnwrapLambdaValue(arg)));
}

// Creators for QEXTLambda action QEXTLBOPRCast<QEXTLBOPRStatic>.
template <typename T_type, typename T_arg>
QEXTLambda<QEXTLambdaOperatorConvert<QEXTLBOPRCast<QEXTLBOPRStatic>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> >
qextLambdaStaticCast(const T_arg &arg) {
    typedef QEXTLambdaOperatorConvert<QEXTLBOPRCast<QEXTLBOPRStatic>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(qextUnwrapLambdaValue(arg)));
}

// Creators for QEXTLambda action QEXTLBOPRCast<QEXTLBOPRDynamic>.
template <typename T_type, typename T_arg>
QEXTLambda<QEXTLambdaOperatorConvert<QEXTLBOPRCast<QEXTLBOPRDynamic>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> >
qextLambdaDynamicCast(const T_arg &arg) {
    typedef QEXTLambdaOperatorConvert<QEXTLBOPRCast<QEXTLBOPRDynamic>, T_type, typename QEXTUnwrapLambdaType<T_arg>::Type> OperatorType;
    return QEXTLambda<OperatorType>(OperatorType(qextUnwrapLambdaValue(arg)));
}



#endif // QEXTLAMBDAOPERATOR_H
