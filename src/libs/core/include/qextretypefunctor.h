#ifndef QEXTRETYPEFUNCTOR_H
#define QEXTRETYPEFUNCTOR_H

#include <qextadaptortrait.h>
#include <qextretypereturnfunctor.h>
#include <qextmemberfunctor.h>
#include <qextpointerfunctor.h>
#include <qextslot.h>

#include <QDebug>



/** @defgroup retype qextRetypeFunctor(), qextRetypeReturnFunctor()
 * qextRetypeFunctor() alters a QEXTPointerFunctor, a QEXTMemberFunctor or a QEXTSlot
 * in that it makes C-style casts to the functor's parameter types
 * of all parameters passed through operator()().
 *
 * Use this adaptor for inline conversion between numeric or other simple types.
 * @par Example:
 * @code
 * void foo(int);
 * qextRetypeFunctor(qextPointerFunctor(&foo))(5.7F); // calls foo(5)
 * @endcode
 *
 * The functor that qextRetypeFunctor() returns can be passed directly into
 * QEXTSignal::connect().
 *
 * @par Example:
 * @code
 * QEXTSignal<void,float> some_signal;
 * void foo(int);
 * some_signal.connect(qextRetypeFunctor(qextPointerFunctor(&foo)));
 * @endcode
 *
 * This adaptor builds an exception in that it only works on QEXTPointerFunctor,
 * qextMemberFunctor and QEXTSlot because it needs sophisticated information about
 * the parameter types that cannot be deduced from arbitrary functor types.
 *
 * qextRetypeReturnFunctor() alters the return type of an arbitrary functor.
 * Like in qextRetypeFunctor() a C-style cast is performed. Usage qextRetypeReturnFunctor() is
 * not restricted to QEXT functor types but you need to
 * specify the new return type as a template parameter.
 *
 * @par Example:
 * @code
 * float foo();
 * std::cout << qextRetypeReturnFunctor<int>(&foo)(); // converts foo's return value to an integer
 * @endcode
 *
 * @ingroup adaptors
 */


/** Adaptor that performs C-style casts on the parameters passed on to the functor.
 * Use the convenience function qextRetypeFunctor() to create an instance of retype_functor.
 *
 * The following template arguments are used:
 * - @e T_functor Type of the functor to wrap.
 * - @e T_type1 Type of @e T_functor's 1th argument.
 * - @e T_type2 Type of @e T_functor's 2th argument.
 * - @e T_type3 Type of @e T_functor's 3th argument.
 * - @e T_type4 Type of @e T_functor's 4th argument.
 * - @e T_type5 Type of @e T_functor's 5th argument.
 * - @e T_type6 Type of @e T_functor's 6th argument.
 * - @e T_type7 Type of @e T_functor's 7th argument.
 *
 * @ingroup retype
 */
template <typename T_functor,
          typename T_type1 = QEXTNil, typename T_type2 = QEXTNil, typename T_type3 = QEXTNil,
          typename T_type4 = QEXTNil, typename T_type5 = QEXTNil, typename T_type6 = QEXTNil, typename T_type7 = QEXTNil>
struct QEXTRetypeFunctor : public QEXTAdapts<T_functor>
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
        typename QEXTTypeTrait<T_arg6>::Pass,
        typename QEXTTypeTrait<T_arg7>::Pass>::Type Type;
    };

    typedef typename QEXTAdapts<T_functor>::ResultType ResultType;

    ResultType operator()() {
        return this->m_functor();
    }

    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_type1>::Take>
                (static_cast<T_type1>(arg1));
    }


    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_type1>::Take,
                typename QEXTTypeTrait<T_type2>::Take>
                (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2));
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_type1>::Take,
                typename QEXTTypeTrait<T_type2>::Take,
                typename QEXTTypeTrait<T_type3>::Take>
                (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3));
    }



    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_type1>::Take,
                typename QEXTTypeTrait<T_type2>::Take,
                typename QEXTTypeTrait<T_type3>::Take,
                typename QEXTTypeTrait<T_type4>::Take>
                (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3), static_cast<T_type4>(arg4));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_type1>::Take,
                typename QEXTTypeTrait<T_type2>::Take,
                typename QEXTTypeTrait<T_type3>::Take,
                typename QEXTTypeTrait<T_type4>::Take,
                typename QEXTTypeTrait<T_type5>::Take>
                (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                 static_cast<T_type4>(arg4), static_cast<T_type5>(arg5));
    }


    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_type1>::Take,
                typename QEXTTypeTrait<T_type2>::Take,
                typename QEXTTypeTrait<T_type3>::Take,
                typename QEXTTypeTrait<T_type4>::Take,
                typename QEXTTypeTrait<T_type5>::Take,
                typename QEXTTypeTrait<T_type6>::Take>
                (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                 static_cast<T_type4>(arg4), static_cast<T_type5>(arg5), static_cast<T_type6>(arg6));
    }

    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_type1>::Take,
                typename QEXTTypeTrait<T_type2>::Take,
                typename QEXTTypeTrait<T_type3>::Take,
                typename QEXTTypeTrait<T_type4>::Take,
                typename QEXTTypeTrait<T_type5>::Take,
                typename QEXTTypeTrait<T_type6>::Take,
                typename QEXTTypeTrait<T_type7>::Take>
                (static_cast<T_type1>(arg1), static_cast<T_type2>(arg2), static_cast<T_type3>(arg3),
                 static_cast<T_type4>(arg4), static_cast<T_type5>(arg5), static_cast<T_type6>(arg6), static_cast<T_type7>(arg7));
    }


    /** Constructs a retype_functor object that performs C-style casts on the parameters passed on to the functor.
     * @param functor Functor to invoke from operator()().
     */
    explicit QEXTRetypeFunctor(typename QEXTTypeTrait<T_functor>::Take functor)
        : QEXTAdapts<T_functor>(functor) {}
};


//template specialization of visitor<>::do_visit_each<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for qextRetypeFunctor performs a functor on the
 * functor stored in the qextRetypeFunctor object.
 *
 * @ingroup retype
 */
template <typename T_functor,
          typename T_type1, typename T_type2, typename T_type3,
          typename T_type4, typename T_type5, typename T_type6, typename T_type7>
struct QEXTVisitor<QEXTRetypeFunctor<T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTRetypeFunctor<T_functor, T_type1, T_type2, T_type3, T_type4, T_type5, T_type6, T_type7> &target) {
        qextVisitEach(action, target.m_functor);
    }
};

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTSlot.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return>
inline QEXTRetypeFunctor<QEXTPointerFunctor0<T_return> >
qextRetypeFunctor(const QEXTPointerFunctor0<T_return> &functor) {
    return QEXTRetypeFunctor<QEXTPointerFunctor0<T_return> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_arg1>
inline QEXTRetypeFunctor<QEXTPointerFunctor1<T_return, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTPointerFunctor1<T_return, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTPointerFunctor1<T_return, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTPointerFunctor2<T_return, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTPointerFunctor2<T_return, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTPointerFunctor2<T_return, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTPointerFunctor3<T_return, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTPointerFunctor3<T_return, T_arg1, T_arg2, T_arg3> &functor) {
    return QEXTRetypeFunctor<QEXTPointerFunctor3<T_return, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTPointerFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTPointerFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTPointerFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTPointerFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTPointerFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTPointerFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTPointerFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTPointerFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTPointerFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextPointerFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTPointerFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTPointerFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTPointerFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTMemberFunctor0<T_return, T_obj> >
qextRetypeFunctor(const QEXTMemberFunctor0<T_return, T_obj> &functor) {
    return QEXTRetypeFunctor<QEXTMemberFunctor0<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTMemberFunctor1<T_return, T_obj, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor) {
    return QEXTRetypeFunctor<QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on qextMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor0<T_return, T_obj> >
qextRetypeFunctor(const QEXTConstMemberFunctor0<T_return, T_obj> &functor) {
    return QEXTRetypeFunctor<QEXTConstMemberFunctor0<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTConstMemberFunctor1<T_return, T_obj, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor)
{
    return QEXTRetypeFunctor<QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor0<T_return, T_obj> >
qextRetypeFunctor(const QEXTVolatileMemberFunctor0<T_return, T_obj> &functor) {
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor0<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor) {
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor0<T_return, T_obj> >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor0<T_return, T_obj> &functor) {
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor0<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor) {
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTConstVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor0<T_return, T_obj> >
qextRetypeFunctor(const QEXTBoundMemberFunctor0<T_return, T_obj> &functor) {
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor0<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor) {
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor0<T_return, T_obj> >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor0<T_return, T_obj> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor0<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor0<T_return, T_obj> >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor0<T_return, T_obj> &functor) {
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor0<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor) {
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundVolatileMemberFunctor.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>, T_arg1 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>, T_arg1, T_arg2 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>, T_arg1, T_arg2, T_arg3 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>, T_arg1, T_arg2, T_arg3, T_arg4 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(functor);
}

/** Creates an adaptor of type qextRetypeFunctor which performs C-style casts on the parameters passed on to the functor.
 * This function template specialization works on QEXTBoundConstVolatileMemberFunctor7.
 *
 * @param functor Functor that should be wrapped.
 * @return Adaptor that executes @e functor performing C-style casts on the paramters passed on.
 *
 * @ingroup retype
 */
template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
qextRetypeFunctor(const QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &functor) {
    return QEXTRetypeFunctor<QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(functor);
}


#endif // QEXTRETYPEFUNCTOR_H
