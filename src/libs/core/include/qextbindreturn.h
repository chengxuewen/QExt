#ifndef QEXTBINDRETURN_H
#define QEXTBINDRETURN_H

#include <qextadaptortrait.h>
#include <qextboundargument.h>
#include <qextreferencewrapper.h>


template <typename T_return, typename T_functor>
struct QEXTBindReturnFunctor : public QEXTAdapts<T_functor>
{
    template <typename T_arg1 = void, typename T_arg2 = void>
    struct ReturnTypeDeduce
    {
        typedef typename QEXTUnwrapReference<T_return>::Type Type;
    };
    typedef typename QEXTUnwrapReference<T_return>::Type ResultType;

    QEXTBindReturnFunctor(typename QEXTTypeTrait<T_functor>::Take functor, typename QEXTTypeTrait<T_return>::Take returnValue)
        : QEXTAdapts<T_functor>(functor), m_returnValue(returnValue) {}

    typename QEXTUnwrapReference<T_return>::Type
    operator()() {
        this->m_functor();
        return m_returnValue.invoke();
    }

    template <typename T_arg1>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1) {
        this->m_functor(arg1);
        //        this->m_functor.operator()<typename QEXTTypeTrait<T_arg1>::Pass>(arg1);
        return m_returnValue.invoke();
    }

    template <typename T_arg1, typename T_arg2>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
//        this->m_functor.template operator()<typename QEXTTypeTrait<T_arg1>::Pass, typename QEXTTypeTrait<T_arg2>::Pass>(arg1, arg2);
        this->m_functor(arg1, arg2);
        return m_returnValue.invoke();
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        //        this->m_functor.operator()<
        //                typename QEXTTypeTrait<T_arg1>::Pass,
        //                typename QEXTTypeTrait<T_arg2>::Pass,
        //                typename QEXTTypeTrait<T_arg3>::Pass>(arg1, arg2, arg3);
        this->m_functor(arg1, arg2, arg3);
        return m_returnValue.invoke();
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        //        this->m_functor.operator()<
        //                typename QEXTTypeTrait<T_arg1>::Pass,
        //                typename QEXTTypeTrait<T_arg2>::Pass,
        //                typename QEXTTypeTrait<T_arg3>::Pass,
        //                typename QEXTTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4);
        this->m_functor(arg1, arg2, arg3, arg4);
        return m_returnValue.invoke();
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        //        this->m_functor.operator()<
        //                typename QEXTTypeTrait<T_arg1>::Pass,
        //                typename QEXTTypeTrait<T_arg2>::Pass,
        //                typename QEXTTypeTrait<T_arg3>::Pass,
        //                typename QEXTTypeTrait<T_arg4>::Pass,
        //                typename QEXTTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5);
        this->m_functor(arg1, arg2, arg3, arg4, arg5);
        return m_returnValue.invoke();
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        //        this->m_functor.operator()<
        //                typename QEXTTypeTrait<T_arg1>::Pass,
        //                typename QEXTTypeTrait<T_arg2>::Pass,
        //                typename QEXTTypeTrait<T_arg3>::Pass,
        //                typename QEXTTypeTrait<T_arg4>::Pass,
        //                typename QEXTTypeTrait<T_arg5>::Pass,
        //                typename QEXTTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6);
        this->m_functor(arg1, arg2, arg3, arg4, arg5, arg6);
        return m_returnValue.invoke();
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename QEXTUnwrapReference<T_return>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        //        this->m_functor.operator()<
        //                typename QEXTTypeTrait<T_arg1>::Pass,
        //                typename QEXTTypeTrait<T_arg2>::Pass,
        //                typename QEXTTypeTrait<T_arg3>::Pass,
        //                typename QEXTTypeTrait<T_arg4>::Pass,
        //                typename QEXTTypeTrait<T_arg5>::Pass,
        //                typename QEXTTypeTrait<T_arg6>::Pass,
        //                typename QEXTTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        this->m_functor(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return m_returnValue.invoke();
    }

    QEXTBoundArgument<T_return> m_returnValue; // public, so that visit_each() can access it
};



template <typename T_return, typename T_functor>
struct QEXTVisitor<QEXTBindReturnFunctor<T_return, T_functor> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBindReturnFunctor<T_return, T_functor> &target) {
        qextVisitEach(action, target.m_returnValue);
        qextVisitEach(action, target.m_functor);
    }
};

template <typename T_return, typename T_functor>
QEXTBindReturnFunctor<T_return, T_functor>
qextBindReturn(const T_functor &functor, T_return returnValue) {
    return QEXTBindReturnFunctor<T_return, T_functor>(functor, returnValue);
}


#endif // QEXTBINDRETURN_H
