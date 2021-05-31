#ifndef QEXTLAMBDABASE_H
#define QEXTLAMBDABASE_H

#include <qextadaptortrait.h>
#include <qexttypetrait.h>
#include <qextvisitor.h>
#include <qextreferencewrapper.h>

struct QEXTLambdaBase : public QEXTAdaptorBase {};


template <typename T_type> struct QEXTLambda;

namespace qextinternal {


template <typename T_type, bool I_islambda = QEXTBaseAndDerivedTester<QEXTLambdaBase, T_type>::value> struct QEXTLambdaCore;


template <typename T_type>
struct QEXTLambdaCore<T_type, true> : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename T_type::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type Type;
    };

    typedef typename T_type::ResultType ResultType;
    typedef T_type LambdaType;

    ResultType
    operator()() const {
        return m_value();
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator ()(T_arg1 arg1) const {
        return m_value.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass>
                (arg1);
    }


    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2) const {
        return m_value.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>
                (arg1, arg2);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return m_value.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg1, arg2, arg3);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return m_value.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg3, arg4);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return m_value.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg4, arg5);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return m_value.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator ()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return m_value.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    QEXTLambdaCore() {}

    explicit QEXTLambdaCore(const T_type &value)
        : m_value(value) {}

    T_type m_value;
};




template <typename T_type>
struct QEXTLambdaCore<T_type, false> : public QEXTLambdaBase
{
    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_type Type;
    };
    typedef T_type ResultType; // all operator() overloads return T_type.
    typedef QEXTLambda<T_type> LambdaType;

    ResultType operator()() const {
        return m_value;
    }

    template <typename T_arg1>
    ResultType operator ()(T_arg1) const {
        return m_value;
    }

    template <typename T_arg1, typename T_arg2>
    ResultType operator ()(T_arg1, T_arg2) const {
        return m_value;
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    ResultType operator ()(T_arg1, T_arg2, T_arg3) const {
        return m_value;
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    ResultType operator ()(T_arg1, T_arg2, T_arg3, T_arg4) const {
        return m_value;
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    ResultType operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const {
        return m_value;
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    ResultType operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const {
        return m_value;
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    ResultType operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const {
        return m_value;
    }

    explicit QEXTLambdaCore(typename QEXTTypeTrait<T_type>::Take value)
        : m_value(value) {}

    T_type m_value;
};

} /* namespace qextinternal */



template <typename T_functor, bool I_islambda>
struct QEXTVisitor<qextinternal::QEXTLambdaCore<T_functor, I_islambda> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const qextinternal::QEXTLambdaCore<T_functor, I_islambda> &target) {
        qextVisitEach(action, target.m_value);
    }
};

template <typename T_type>
struct QEXTLambdaOther;
struct QEXTLambdaSubscript;
struct QEXTLambdaAssign;

template <typename T_action, typename T_type1, typename T_type2>
struct QEXTLambdaOperator;

template <typename T_type>
struct QEXTUnwrapLambdaType;

template <typename T_type>
T_type& qextUnwrapLambdaValue(T_type &arg) {
    return arg;
}

template <typename T_type>
const T_type& qextUnwrapLambdaValue(const T_type &arg) {
    return arg;
}

template <typename T_type>
const T_type& qextUnwrapLambdaValue(const QEXTLambda<T_type> &arg) {
    return arg.m_value;
}



template <typename T_type>
struct QEXTLambda : public qextinternal::QEXTLambdaCore<T_type>
{
    typedef QEXTLambda<T_type> Self;

    QEXTLambda() {}

    QEXTLambda(typename QEXTTypeTrait<T_type>::Take value)
        : qextinternal::QEXTLambdaCore<T_type>(value) {}

    // operators for QEXTLambdaOther<QEXTLambdaSubscript>
    template <typename T_arg>
    QEXTLambda<QEXTLambdaOperator<QEXTLambdaOther<QEXTLambdaSubscript>, Self, typename QEXTUnwrapLambdaType<T_arg>::Type> >
    operator [] (const T_arg &arg) const {
        typedef QEXTLambdaOperator<QEXTLambdaOther<QEXTLambdaSubscript>, Self, typename QEXTUnwrapLambdaType<T_arg>::Type> LambdaOperatorType;
        return QEXTLambda<LambdaOperatorType>(LambdaOperatorType(this->m_value, qextUnwrapLambdaValue(arg)));
    }

    // operators for QEXTLambdaOther<QEXTLambdaAssign>
    template <typename T_arg>
    QEXTLambda<QEXTLambdaOperator<QEXTLambdaOther<QEXTLambdaAssign>, Self, typename QEXTUnwrapLambdaType<T_arg>::Type> >
    operator = (const T_arg &arg) const {
        typedef QEXTLambdaOperator<QEXTLambdaOther<QEXTLambdaAssign>, Self, typename QEXTUnwrapLambdaType<T_arg>::Type> LambdaOperatorType;
        return QEXTLambda<LambdaOperatorType>(LambdaOperatorType(this->m_value, qextUnwrapLambdaValue(arg)));
    }
};

template <typename T_type>
struct QEXTVisitor<QEXTLambda<T_type> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTLambda<T_type> &target) {
        qextVisitEach(action, target.m_value);
    }
};

template <typename T_type>
QEXTLambda<T_type&> qextLambda(T_type &value) {
    return QEXTLambda<T_type&>(value);
}

template <typename T_type>
QEXTLambda<const T_type&> qextLambda(const T_type &value) {
    return QEXTLambda<const T_type&>(value);
}


template <typename T_type>
struct QEXTUnwrapLambdaType
{
    typedef typename QEXTUnwrapReference<T_type>::Type Type;
};


template <typename T_type>
struct QEXTUnwrapLambdaType<QEXTLambda<T_type> >
{
    typedef T_type Type;
};


#endif // QEXTLAMBDABASE_H
