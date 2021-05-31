#ifndef QEXTRETYPERETURNFUNCTOR_H
#define QEXTRETYPERETURNFUNCTOR_H

#include <qextadaptortrait.h>

template <typename T_return, typename T_functor>
struct QEXTRetypeReturnFunctor : public QEXTAdapts<T_functor>
{

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef T_return Type;
    };

    typedef T_return ResultType;

    T_return operator()() {
        T_return(this->m_functor());
    }

    template <typename T_arg1>
    inline T_return operator()(T_arg1 arg1) {
        return T_return(this->m_functor.template operator ()<
                        typename QEXTTypeTrait<T_arg1>::Pass>
                        (arg1));
    }

    template <typename T_arg1, typename T_arg2>
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2) {
        return T_return(this->m_functor.template operator ()<
                        typename QEXTTypeTrait<T_arg1>::Pass,
                        typename QEXTTypeTrait<T_arg2>::Pass>
                        (arg1, arg2));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return T_return(this->m_functor.template operator ()<
                        typename QEXTTypeTrait<T_arg1>::Pass,
                        typename QEXTTypeTrait<T_arg2>::Pass,
                        typename QEXTTypeTrait<T_arg3>::Pass>
                        (arg1, arg2, arg3));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return T_return(this->m_functor.template operator ()<
                        typename QEXTTypeTrait<T_arg1>::Pass,
                        typename QEXTTypeTrait<T_arg2>::Pass,
                        typename QEXTTypeTrait<T_arg3>::Pass,
                        typename QEXTTypeTrait<T_arg4>::Pass>
                        (arg1, arg2, arg3, arg4));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return T_return(this->m_functor.template operator ()<
                        typename QEXTTypeTrait<T_arg1>::Pass,
                        typename QEXTTypeTrait<T_arg2>::Pass,
                        typename QEXTTypeTrait<T_arg3>::Pass,
                        typename QEXTTypeTrait<T_arg4>::Pass,
                        typename QEXTTypeTrait<T_arg5>::Pass>
                        (arg1, arg2, arg3, arg4, arg5));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return T_return(this->m_functor.template operator ()<
                        typename QEXTTypeTrait<T_arg1>::Pass,
                        typename QEXTTypeTrait<T_arg2>::Pass,
                        typename QEXTTypeTrait<T_arg3>::Pass,
                        typename QEXTTypeTrait<T_arg4>::Pass,
                        typename QEXTTypeTrait<T_arg5>::Pass,
                        typename QEXTTypeTrait<T_arg6>::Pass>
                        (arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    inline T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return T_return(this->m_functor.template operator ()<
                        typename QEXTTypeTrait<T_arg1>::Pass,
                        typename QEXTTypeTrait<T_arg2>::Pass,
                        typename QEXTTypeTrait<T_arg3>::Pass,
                        typename QEXTTypeTrait<T_arg4>::Pass,
                        typename QEXTTypeTrait<T_arg5>::Pass,
                        typename QEXTTypeTrait<T_arg6>::Pass,
                        typename QEXTTypeTrait<T_arg7>::Pass>
                        (arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }

    QEXTRetypeReturnFunctor() {}

    explicit QEXTRetypeReturnFunctor(typename QEXTTypeTrait<T_functor>::Take functor)
        : QEXTAdapts<T_functor>(functor) {}
};

template <typename T_functor>
struct QEXTRetypeReturnFunctor<void, T_functor> : public QEXTAdapts<T_functor>
{

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef void Type;
    };

    typedef void ResultType;

    void operator()() {
        this->m_functor();
    }

    template <typename T_arg1>
    inline void operator()(T_arg1 arg1) {
        this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass>
                (arg1);
    }



    template <typename T_arg1, typename T_arg2>
    inline void operator()(T_arg1 arg1, T_arg2 arg2) {
        this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass, typename QEXTTypeTrait<T_arg2>::Pass>
                (arg1, arg2);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg1, arg2, arg3);
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg3, arg4);
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg4, arg5);
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6);
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    inline void operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }


    QEXTRetypeReturnFunctor() {}
    QEXTRetypeReturnFunctor(typename QEXTTypeTrait<T_functor>::Take functor)
        : QEXTAdapts<T_functor>(functor) {}
};


template <typename T_return, typename T_functor>
struct QEXTVisitor<QEXTRetypeReturnFunctor<T_return, T_functor> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTRetypeReturnFunctor<T_return, T_functor> &target) {
        qextVisitEach(action, target.m_functor);
    }
};

template <typename T_return, typename T_functor>
inline QEXTRetypeReturnFunctor<T_return, T_functor>
qextRetypeReturnFunctor(const T_functor &functor) {
    return QEXTRetypeReturnFunctor<T_return, T_functor>(functor);
}


template <typename T_functor>
inline QEXTRetypeReturnFunctor<void, T_functor>
qextHideReturnFunctor(const T_functor &functor) {
    return QEXTRetypeReturnFunctor<void, T_functor>(functor);
}


#endif // QEXTRETYPERETURNFUNCTOR_H
