#ifndef QEXTHIDEFUNCTOR_H
#define QEXTHIDEFUNCTOR_H

#include <qextadaptortrait.h>
#include <qextvisitor.h>

template <int I_location, typename T_functor>
struct QEXTHideFunctor;


template <typename T_functor>
struct QEXTHideFunctor <-1, T_functor> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType  ResultType;


    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1) {
        return this->m_functor();
    }

    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass>
                (arg1);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>
                (arg1, arg2);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg1, arg2, arg3);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg3, arg4);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg4, arg5);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6);
    }


    explicit QEXTHideFunctor(const T_functor &func)
        : QEXTAdapts<T_functor>(func) {}
};


template <typename T_functor>
struct QEXTHideFunctor <0, T_functor> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;


    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType  ResultType;


    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1) {
        return this->m_functor();
    }


    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg2>::Pass>
                (arg2);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg2, arg3);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg2, arg3, arg4);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg2, arg3, arg4, arg5);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg2, arg3, arg4, arg5, arg6);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg2, arg3, arg4, arg5, arg6, arg7);
    }

    explicit QEXTHideFunctor(const T_functor &func)
        : QEXTAdapts<T_functor>(func) {}
};


template <typename T_functor>
struct QEXTHideFunctor <1, T_functor> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type Type;
    };

    typedef typename AdaptorType::ResultType  ResultType;


    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass>
                (arg1);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg1, arg3);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg3, arg4);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg3, arg4, arg5);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg3, arg4, arg5, arg6);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg1, arg3, arg4, arg5, arg6, arg7);
    }


    explicit QEXTHideFunctor(const T_functor &func)
        : QEXTAdapts<T_functor>(func) {}
};

template <typename T_functor>
struct QEXTHideFunctor <2, T_functor> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType  ResultType;

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>
                (arg1, arg2);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg4);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg4, arg5);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg4, arg5, arg6);
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg4, arg5, arg6, arg7);
    }

    explicit QEXTHideFunctor(const T_functor &func)
        : QEXTAdapts<T_functor>(func) {}
};


template <typename T_functor>
struct QEXTHideFunctor<3, T_functor> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void, typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg1, arg2, arg3);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg5);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg5, arg6);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg5, arg6, arg7);
    }

    explicit QEXTHideFunctor(const T_functor &func)
        : QEXTAdapts<T_functor>(func) { }
};

template <typename T_functor>
struct QEXTHideFunctor<4, T_functor> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg3, arg4);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg6);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg4, arg6, arg7);
    }

    explicit QEXTHideFunctor(const T_functor &func)
        : QEXTAdapts<T_functor>(func) { }
};

template <typename T_functor>
struct QEXTHideFunctor<5, T_functor> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg4, arg5);
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg7);
    }

    explicit QEXTHideFunctor(const T_functor &func)
        : QEXTAdapts<T_functor>(func) { }
};


template <typename T_functor>
struct QEXTHideFunctor<6, T_functor> : public QEXTAdapts<T_functor>
{
    typedef typename QEXTAdapts<T_functor>::AdaptorType AdaptorType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTTypeTrait<T_arg1>::Pass,
        typename QEXTTypeTrait<T_arg2>::Pass,
        typename QEXTTypeTrait<T_arg3>::Pass,
        typename QEXTTypeTrait<T_arg4>::Pass,
        typename QEXTTypeTrait<T_arg5>::Pass,
        typename QEXTTypeTrait<T_arg6>::Pass>::Type Type;
    };
    typedef typename AdaptorType::ResultType ResultType;

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6);
    }

    explicit QEXTHideFunctor(const T_functor &func)
        : QEXTAdapts<T_functor>(func) { }
};

template <int I_location, typename T_functor>
struct QEXTVisitor<QEXTHideFunctor<I_location, T_functor> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTHideFunctor<I_location, T_functor> &target) {
        qextVisitEach(action, target.m_functor);
    }
};

template <int I_location, typename T_functor>
inline QEXTHideFunctor<I_location, T_functor>
qextHideFunctor(const T_functor &func) {
    return QEXTHideFunctor<I_location, T_functor>(func);
}


template <typename T_functor>
inline QEXTHideFunctor<-1, T_functor>
qextHideFunctor(const T_functor &func) {
    return QEXTHideFunctor<-1, T_functor>(func);
}

#endif // QEXTHIDEFUNCTOR_H
