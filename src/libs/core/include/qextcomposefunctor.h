#ifndef QEXTCOMPOSEFUNCTOR_H
#define QEXTCOMPOSEFUNCTOR_H

#include <qextadaptortrait.h>
#include <qextresulttypededuce.h>


template <typename T_setter, typename T_getter1, typename T_getter2, typename T_getter3>
struct QEXTCompose3Functor : public QEXTAdapts<T_setter>
{
    typedef typename QEXTAdapts<T_setter>::AdaptorType AdaptorType;
    typedef T_setter    SetterType;
    typedef T_getter1   Getter1Type;
    typedef T_getter2   Getter2Type;
    typedef T_getter3   Getter3Type;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
        typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
        typename QEXTResultTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
        >::Type ResultType;
    };

    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1>::Type,
                typename QEXTResultTypeDeduce<T_getter2>::Type,
                typename QEXTResultTypeDeduce<T_getter3>::Type>
                (m_getter1(), m_getter2(), m_getter3());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1>::Type,
                typename QEXTResultTypeDeduce<T_getter3, T_arg1>::Type>
                (m_getter1(arg1), m_getter2(arg1), m_getter3(arg1));
    }

    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2>::Type,
                typename QEXTResultTypeDeduce<T_getter3, T_arg1, T_arg2>::Type>
                (m_getter1(arg1, arg2), m_getter2(arg1, arg2), m_getter3(arg1, arg2));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3>::Type,
                typename QEXTResultTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3>::Type>
                (m_getter1(arg1, arg2, arg3), m_getter2(arg1, arg2, arg3), m_getter3(arg1, arg2, arg3));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4>::Type,
                typename QEXTResultTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4>::Type>
                (m_getter1(arg1, arg2, arg3, arg4), m_getter2(arg1, arg2, arg3, arg4), m_getter3(arg1, arg2, arg3, arg4));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type,
                typename QEXTResultTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type>
                (m_getter1(arg1, arg2, arg3, arg4, arg5), m_getter2(arg1, arg2, arg3, arg4, arg5), m_getter3(arg1, arg2, arg3, arg4, arg5));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type,
                typename QEXTResultTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type>
                (m_getter1(arg1, arg2, arg3, arg4, arg5, arg6), m_getter2(arg1, arg2, arg3, arg4, arg5, arg6), m_getter3(arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QEXTResultTypeDeduce<T_getter3, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>
                (m_getter1(arg1, arg2, arg3, arg4, arg5, arg6, arg7), m_getter2(arg1, arg2, arg3, arg4, arg5, arg6, arg7), m_getter3(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }

    QEXTCompose3Functor(const T_setter &setter, const T_getter1 &getter1, const T_getter2 &getter2, const T_getter3 &getter3)
        : QEXTAdapts<T_setter>(setter), m_getter1(getter1), m_getter2(getter2), m_getter3(getter3) {}

    Getter1Type m_getter1;
    Getter2Type m_getter2;
    Getter3Type m_getter3;
};

template <typename T_setter, typename T_getter1, typename T_getter2, typename T_getter3>
struct QEXTVisitor<QEXTCompose3Functor<T_setter, T_getter1, T_getter2, T_getter3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTCompose3Functor<T_setter, T_getter1, T_getter2, T_getter3> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_getter1);
        qextVisitEach(action, target.m_getter2);
        qextVisitEach(action, target.m_getter3);
    }
};


template <typename T_setter, typename T_getter1, typename T_getter2>
struct QEXTCompose2Functor : public QEXTAdapts<T_setter>
{
    typedef typename QEXTAdapts<T_setter>::AdaptorType AdaptorType;
    typedef T_setter    SetterType;
    typedef T_getter1   Getter1Type;
    typedef T_getter2   Getter2Type;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
        typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
        >::Type ResultType;
    };

    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1>::Type,
                typename QEXTResultTypeDeduce<T_getter2>::Type>
                (m_getter1(), m_getter2());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1>::Type>
                (m_getter1(arg1), m_getter2(arg1));
    }

    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2>::Type>
                (m_getter1(arg1, arg2), m_getter2(arg1, arg2));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3>::Type>
                (m_getter1(arg1, arg2, arg3), m_getter2(arg1, arg2, arg3));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4>::Type>
                (m_getter1(arg1, arg2, arg3, arg4), m_getter2(arg1, arg2, arg3, arg4));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type>
                (m_getter1(arg1, arg2, arg3, arg4, arg5), m_getter2(arg1, arg2, arg3, arg4, arg5));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type>
                (m_getter1(arg1, arg2, arg3, arg4, arg5, arg6), m_getter2(arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter1, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type,
                typename QEXTResultTypeDeduce<T_getter2, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>
                (m_getter1(arg1, arg2, arg3, arg4, arg5, arg6, arg7), m_getter2(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }

    QEXTCompose2Functor(const T_setter &setter, const T_getter1 &getter1, const T_getter2 &getter2)
        : QEXTAdapts<T_setter>(setter), m_getter1(getter1), m_getter2(getter2) {}

    Getter1Type m_getter1;
    Getter2Type m_getter2;
};

template <typename T_setter, typename T_getter1, typename T_getter2>
struct QEXTVisitor<QEXTCompose2Functor<T_setter, T_getter1, T_getter2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTCompose2Functor<T_setter, T_getter1, T_getter2> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_getter1);
        qextVisitEach(action, target.m_getter2);
    }
};



template <typename T_setter, typename T_getter>
struct QEXTCompose1Functor : public QEXTAdapts<T_setter>
{
    typedef typename QEXTAdapts<T_setter>::AdaptorType AdaptorType;
    typedef T_setter SetterType;
    typedef T_getter GetterType;

    template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
              typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
    struct ResultTypeDeduce
    {
        typedef typename AdaptorType::template ResultTypeDeduce<
        typename QEXTResultTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>::Type Type;
    };

    typedef typename AdaptorType::ResultType  ResultType;

    ResultType
    operator()() {
        return this->m_functor(m_getter());
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter, T_arg1>::Type>
                (m_getter(arg1));
    }

    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter, T_arg1, T_arg2>::Type>
                (m_getter(arg1, arg2));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3>::Type>
                (m_getter(arg1, arg2, arg3));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4>::Type>
                (m_getter(arg1, arg2, arg3, arg4));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type>
                (m_getter(arg1, arg2, arg3, arg4, arg5));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type>
                (m_getter(arg1, arg2, arg3, arg4, arg5, arg6));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTResultTypeDeduce<T_getter, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type>
                (m_getter(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
    }


    QEXTCompose1Functor(const T_setter &setter, const T_getter &getter)
        : QEXTAdapts<T_setter>(setter), m_getter(getter) {}

    GetterType m_getter;
};

template <typename T_setter, typename T_getter>
struct QEXTVisitor<QEXTCompose1Functor<T_setter, T_getter> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTCompose1Functor<T_setter, T_getter> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_getter);
    }
};




template <typename T_setter, typename T_getter1, typename T_getter2, typename T_getter3>
inline QEXTCompose3Functor<T_setter, T_getter1, T_getter2, T_getter3>
qextComposeFunctor(const T_setter &setter, const T_getter1 &getter1, const T_getter2 &getter2, const T_getter3 &getter3) {
    return QEXTCompose3Functor<T_setter, T_getter1, T_getter2, T_getter3>(setter, getter1, getter2, getter3);
}

template <typename T_setter, typename T_getter1, typename T_getter2>
inline QEXTCompose2Functor<T_setter, T_getter1, T_getter2>
qextComposeFunctor(const T_setter &setter, const T_getter1 &getter1, const T_getter2 &getter2) {
    return QEXTCompose2Functor<T_setter, T_getter1, T_getter2>(setter, getter1, getter2);
}

template <typename T_setter, typename T_getter>
inline QEXTCompose1Functor<T_setter, T_getter>
qextComposeFunctor(const T_setter &setter, const T_getter &getter) {
    return QEXTCompose1Functor<T_setter, T_getter>(setter, getter);
}


#endif // QEXTCOMPOSEFUNCTOR_H
