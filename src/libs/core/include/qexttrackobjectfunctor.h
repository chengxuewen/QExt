#ifndef QEXTTRACKOBJECTFUNCTOR_H
#define QEXTTRACKOBJECTFUNCTOR_H

#include <qextlimitreference.h>
#include <qextadaptortrait.h>



/** @defgroup qextTrackObjectFunctor qextTrackObjectFunctor()
 * qextTrackObjectFunctor() tracks trackable objects, referenced from a functor.
 * It can be useful when you assign a C++11 lambda expression or a std::function<>
 * to a slot, or connect it to a signal, and the lambda expression or std::function<>
 * contains references to trackable derived objects.
 *
 * The functor returned by qextTrackObjectFunctor() is formally an adaptor, but it does
 * not alter the signature, return type or behaviour of the supplied functor.
 * Up to 7 objects can be tracked. operator()() can have up to 7 arguments.
 *
 * @par Example:
 * @code
 * QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE
 * struct bar : public QEXTTrackable {};
 * QEXTSignal<void> some_signal;
 * void foo(bar&);
 * {
 *   bar some_bar;
 *   some_signal.connect([&some_bar](){ foo(some_bar); });
 *     // NOT disconnected automatically when some_bar goes out of scope
 *   some_signal.connect(qextTrackObjectFunctor([&some_bar](){ foo(some_bar); }, some_bar);
 *     // disconnected automatically when some_bar goes out of scope
 * }
 * @endcode
 *
 * @newin{2,4}
 *
 * @ingroup adaptors
 */



/** QEXTTrackObjectFunctor1 wraps a functor and stores a reference to a trackable object.
 * Use the convenience function qextTrackObjectFunctor() to create an instance of QEXTTrackObjectFunctor1.
 *
 * @tparam T_functor The type of functor to wrap.
 * @tparam T_obj1 The type of a trackable object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1>
class QEXTTrackObjectFunctor1 : public QEXTAdapts<T_functor>
{
public:
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

    typedef typename AdaptorType::ResultType ResultType;


    /** Constructs a QEXTTrackObjectFunctor1 object that wraps the passed functor and
     * stores a reference to the passed trackable object.
     * @param func Functor.
     * @param obj1 Trackable object.
     */
    QEXTTrackObjectFunctor1(const T_functor &func, const T_obj1 &obj1)
        : QEXTAdapts<T_functor>(func), m_obj1(obj1) {}


    /** Invokes the wrapped functor.
     * @return The return value of the functor invocation.
     */
    ResultType operator()() {
        return this->m_functor();
    }

    /** Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1>
    typename ResultTypeDeduce<T_arg1>::Type
    operator()(T_arg1 arg1) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass>
                (arg1);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::Type
    operator()(T_arg1 arg1, T_arg2 arg2) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass>
                (arg1, arg2);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass>
                (arg1, arg2, arg3);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass>
                (arg1, arg2, arg3, arg4);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass>
                (arg1, arg2, arg3, arg4, arg5);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Invokes the wrapped functor passing on the arguments.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
    typename ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
    operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) {
        return this->m_functor.template operator ()<
                typename QEXTTypeTrait<T_arg1>::Pass,
                typename QEXTTypeTrait<T_arg2>::Pass,
                typename QEXTTypeTrait<T_arg3>::Pass,
                typename QEXTTypeTrait<T_arg4>::Pass,
                typename QEXTTypeTrait<T_arg5>::Pass,
                typename QEXTTypeTrait<T_arg6>::Pass,
                typename QEXTTypeTrait<T_arg7>::Pass>
                (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    QEXTConstLimitReference<T_obj1> m_obj1;
};


/** QEXTTrackObjectFunctor2 wraps a functor and stores 2 references to trackable objects.
 * Use the convenience function qextTrackObjectFunctor() to create an instance of QEXTTrackObjectFunctor2.
 *
 * @tparam T_functor The type of functor to wrap.
 * @tparam T_obj1 The type of a trackable object.
 * @tparam T_obj2 The type of a trackable object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2>
class QEXTTrackObjectFunctor2 : public QEXTTrackObjectFunctor1<T_functor, T_obj1>
{
public:
    /** Constructs a QEXTTrackObjectFunctor2 object that wraps the passed functor and
     * stores references to the passed trackable objects.
     * @param func Functor.
     * @param obj1 Trackable object.
     * @param obj2 Trackable object.
     */
    QEXTTrackObjectFunctor2(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2)
        : QEXTTrackObjectFunctor1<T_functor, T_obj1>(func, obj1), m_obj2(obj2) {}

    QEXTConstLimitReference<T_obj2> m_obj2;
};


/** QEXTTrackObjectFunctor3 wraps a functor and stores 3 references to trackable objects.
 * Use the convenience function qextTrackObjectFunctor() to create an instance of QEXTTrackObjectFunctor3.
 *
 * @tparam T_functor The type of functor to wrap.
 * @tparam T_obj1 The type of a trackable object.
 * @tparam T_obj2 The type of a trackable object.
 * @tparam T_obj3 The type of a trackable object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3>
class QEXTTrackObjectFunctor3 : public QEXTTrackObjectFunctor1<T_functor, T_obj1>
{
public:
    /** Constructs a QEXTTrackObjectFunctor3 object that wraps the passed functor and
     * stores references to the passed trackable objects.
     * @param func Functor.
     * @param obj1 Trackable object.
     * @param obj2 Trackable object.
     * @param obj3 Trackable object.
     */
    QEXTTrackObjectFunctor3(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3)
        : QEXTTrackObjectFunctor1<T_functor, T_obj1>(func, obj1), m_obj2(obj2), m_obj3(obj3) {}

    QEXTConstLimitReference<T_obj2> m_obj2;
    QEXTConstLimitReference<T_obj3> m_obj3;
};


/** QEXTTrackObjectFunctor4 wraps a functor and stores 4 references to trackable objects.
 * Use the convenience function qextTrackObjectFunctor() to create an instance of QEXTTrackObjectFunctor4.
 *
 * @tparam T_functor The type of functor to wrap.
 * @tparam T_obj1 The type of a trackable object.
 * @tparam T_obj2 The type of a trackable object.
 * @tparam T_obj3 The type of a trackable object.
 * @tparam T_obj4 The type of a trackable object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4>
class QEXTTrackObjectFunctor4 : public QEXTTrackObjectFunctor1<T_functor, T_obj1>
{
public:
    /** Constructs a QEXTTrackObjectFunctor4 object that wraps the passed functor and
     * stores references to the passed trackable objects.
     * @param func Functor.
     * @param obj1 Trackable object.
     * @param obj2 Trackable object.
     * @param obj3 Trackable object.
     * @param obj4 Trackable object.
     */
    QEXTTrackObjectFunctor4(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4)
        : QEXTTrackObjectFunctor1<T_functor, T_obj1>(func, obj1), m_obj2(obj2), m_obj3(obj3), m_obj4(obj4) {}

    QEXTConstLimitReference<T_obj2> m_obj2;
    QEXTConstLimitReference<T_obj3> m_obj3;
    QEXTConstLimitReference<T_obj4> m_obj4;
};

/** QEXTTrackObjectFunctor5 wraps a functor and stores 5 references to trackable objects.
 * Use the convenience function qextTrackObjectFunctor() to create an instance of QEXTTrackObjectFunctor5.
 *
 * @tparam T_functor The type of functor to wrap.
 * @tparam T_obj1 The type of a trackable object.
 * @tparam T_obj2 The type of a trackable object.
 * @tparam T_obj3 The type of a trackable object.
 * @tparam T_obj4 The type of a trackable object.
 * @tparam T_obj5 The type of a trackable object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5>
class QEXTTrackObjectFunctor5 : public QEXTTrackObjectFunctor1<T_functor, T_obj1>
{
public:
    /** Constructs a QEXTTrackObjectFunctor5 object that wraps the passed functor and
     * stores references to the passed trackable objects.
     * @param func Functor.
     * @param obj1 Trackable object.
     * @param obj2 Trackable object.
     * @param obj3 Trackable object.
     * @param obj4 Trackable object.
     * @param obj5 Trackable object.
     */
    QEXTTrackObjectFunctor5(const T_functor &func,
                            const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4, const T_obj5 &obj5)
        : QEXTTrackObjectFunctor1<T_functor, T_obj1>(func, obj1), m_obj2(obj2), m_obj3(obj3), m_obj4(obj4), m_obj5(obj5) {}

    QEXTConstLimitReference<T_obj2> m_obj2;
    QEXTConstLimitReference<T_obj3> m_obj3;
    QEXTConstLimitReference<T_obj4> m_obj4;
    QEXTConstLimitReference<T_obj5> m_obj5;
};


/** QEXTTrackObjectFunctor6 wraps a functor and stores 6 references to trackable objects.
 * Use the convenience function qextTrackObjectFunctor() to create an instance of QEXTTrackObjectFunctor6.
 *
 * @tparam T_functor The type of functor to wrap.
 * @tparam T_obj1 The type of a trackable object.
 * @tparam T_obj2 The type of a trackable object.
 * @tparam T_obj3 The type of a trackable object.
 * @tparam T_obj4 The type of a trackable object.
 * @tparam T_obj5 The type of a trackable object.
 * @tparam T_obj6 The type of a trackable object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6>
class QEXTTrackObjectFunctor6 : public QEXTTrackObjectFunctor1<T_functor, T_obj1>
{
public:
    /** Constructs a QEXTTrackObjectFunctor6 object that wraps the passed functor and
     * stores references to the passed trackable objects.
     * @param func Functor.
     * @param obj1 Trackable object.
     * @param obj2 Trackable object.
     * @param obj3 Trackable object.
     * @param obj4 Trackable object.
     * @param obj5 Trackable object.
     * @param obj6 Trackable object.
     */
    QEXTTrackObjectFunctor6(const T_functor &func,
                            const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3,
                            const T_obj4 &obj4, const T_obj5 &obj5, const T_obj6 &obj6)
        : QEXTTrackObjectFunctor1<T_functor, T_obj1>(func, obj1), m_obj2(obj2), m_obj3(obj3), m_obj4(obj4), m_obj5(obj5), m_obj6(obj6) {}

    QEXTConstLimitReference<T_obj2> m_obj2;
    QEXTConstLimitReference<T_obj3> m_obj3;
    QEXTConstLimitReference<T_obj4> m_obj4;
    QEXTConstLimitReference<T_obj5> m_obj5;
    QEXTConstLimitReference<T_obj6> m_obj6;
};


/** QEXTTrackObjectFunctor7 wraps a functor and stores 7 references to trackable objects.
 * Use the convenience function qextTrackObjectFunctor() to create an instance of QEXTTrackObjectFunctor7.
 *
 * @tparam T_functor The type of functor to wrap.
 * @tparam T_obj1 The type of a trackable object.
 * @tparam T_obj2 The type of a trackable object.
 * @tparam T_obj3 The type of a trackable object.
 * @tparam T_obj4 The type of a trackable object.
 * @tparam T_obj5 The type of a trackable object.
 * @tparam T_obj6 The type of a trackable object.
 * @tparam T_obj7 The type of a trackable object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor,
          typename T_obj1, typename T_obj2, typename T_obj3,
          typename T_obj4, typename T_obj5, typename T_obj6, typename T_obj7>
class QEXTTrackObjectFunctor7 : public QEXTTrackObjectFunctor1<T_functor, T_obj1>
{
public:
    /** Constructs a QEXTTrackObjectFunctor7 object that wraps the passed functor and
     * stores references to the passed trackable objects.
     * @param func Functor.
     * @param obj1 Trackable object.
     * @param obj2 Trackable object.
     * @param obj3 Trackable object.
     * @param obj4 Trackable object.
     * @param obj5 Trackable object.
     * @param obj6 Trackable object.
     * @param obj7 Trackable object.
     */
    QEXTTrackObjectFunctor7(const T_functor &func,
                            const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3,
                            const T_obj4 &obj4, const T_obj5 &obj5, const T_obj6 &obj6, const T_obj7 &obj7)
        : QEXTTrackObjectFunctor1<T_functor, T_obj1>(func, obj1), m_obj2(obj2), m_obj3(obj3), m_obj4(obj4), m_obj5(obj5), m_obj6(obj6), m_obj7(obj7) {}

    QEXTConstLimitReference<T_obj2> m_obj2;
    QEXTConstLimitReference<T_obj3> m_obj3;
    QEXTConstLimitReference<T_obj4> m_obj4;
    QEXTConstLimitReference<T_obj5> m_obj5;
    QEXTConstLimitReference<T_obj6> m_obj6;
    QEXTConstLimitReference<T_obj7> m_obj7;
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTTrackObjectFunctor1 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QEXTTrackObjectFunctor1 object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1>
struct QEXTVisitor<QEXTTrackObjectFunctor1<T_functor, T_obj1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTTrackObjectFunctor1<T_functor, T_obj1> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
    }
};


//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTTrackObjectFunctor2 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QEXTTrackObjectFunctor2 object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2>
struct QEXTVisitor<QEXTTrackObjectFunctor2<T_functor, T_obj1, T_obj2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTTrackObjectFunctor2<T_functor, T_obj1, T_obj2> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
    }
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTTrackObjectFunctor3 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QEXTTrackObjectFunctor3 object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3>
struct QEXTVisitor<QEXTTrackObjectFunctor3<T_functor, T_obj1, T_obj2, T_obj3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTTrackObjectFunctor3<T_functor, T_obj1, T_obj2, T_obj3> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
    }
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTTrackObjectFunctor4 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QEXTTrackObjectFunctor4 object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4>
struct QEXTVisitor<QEXTTrackObjectFunctor4<T_functor, T_obj1, T_obj2, T_obj3, T_obj4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTTrackObjectFunctor4<T_functor, T_obj1, T_obj2, T_obj3, T_obj4> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
        qextVisitEach(action, target.m_obj4);
    }
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTTrackObjectFunctor5 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QEXTTrackObjectFunctor5 object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor,
          typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5>
struct QEXTVisitor<QEXTTrackObjectFunctor5<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTTrackObjectFunctor5<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
        qextVisitEach(action, target.m_obj4);
        qextVisitEach(action, target.m_obj5);
    }
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTTrackObjectFunctor6 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QEXTTrackObjectFunctor6 object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor,
          typename T_obj1, typename T_obj2, typename T_obj3,
          typename T_obj4, typename T_obj5, typename T_obj6>
struct QEXTVisitor<QEXTTrackObjectFunctor6<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTTrackObjectFunctor6<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
        qextVisitEach(action, target.m_obj4);
        qextVisitEach(action, target.m_obj5);
        qextVisitEach(action, target.m_obj6);
    }
};

//template specialization of QEXTVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QEXTTrackObjectFunctor7 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QEXTTrackObjectFunctor7 object.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor,
          typename T_obj1, typename T_obj2, typename T_obj3,
          typename T_obj4, typename T_obj5, typename T_obj6, typename T_obj7>
struct QEXTVisitor<QEXTTrackObjectFunctor7<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTTrackObjectFunctor7<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7> &target) {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
        qextVisitEach(action, target.m_obj4);
        qextVisitEach(action, target.m_obj5);
        qextVisitEach(action, target.m_obj6);
        qextVisitEach(action, target.m_obj7);
    }
};



/** Creates an adaptor of type QEXTTrackObjectFunctor7 which wraps a functor.
 * @param func Functor that shall be wrapped.
 * @param obj1 Trackable object.
 * @param obj2 Trackable object.
 * @param obj3 Trackable object.
 * @param obj4 Trackable object.
 * @param obj5 Trackable object.
 * @param obj6 Trackable object.
 * @param obj7 Trackable object.
 * @return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6, typename T_obj7>
inline QEXTTrackObjectFunctor7<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4, const T_obj5 &obj5, const T_obj6 &obj6, const T_obj7 &obj7) {
    return QEXTTrackObjectFunctor7<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7>(func, obj1, obj2, obj3, obj4, obj5, obj6, obj7);
}

/** Creates an adaptor of type QEXTTrackObjectFunctor6 which wraps a functor.
 * @param func Functor that shall be wrapped.
 * @param obj1 Trackable object.
 * @param obj2 Trackable object.
 * @param obj3 Trackable object.
 * @param obj4 Trackable object.
 * @param obj5 Trackable object.
 * @param obj6 Trackable object.
 * @return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6>
inline QEXTTrackObjectFunctor6<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4, const T_obj5 &obj5, const T_obj6 &obj6) {
    return QEXTTrackObjectFunctor6<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6>(func, obj1, obj2, obj3, obj4, obj5, obj6);
}

/** Creates an adaptor of type QEXTTrackObjectFunctor5 which wraps a functor.
 * @param func Functor that shall be wrapped.
 * @param obj1 Trackable object.
 * @param obj2 Trackable object.
 * @param obj3 Trackable object.
 * @param obj4 Trackable object.
 * @param obj5 Trackable object.
 * @return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5>
inline QEXTTrackObjectFunctor5<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4, const T_obj5 &obj5) {
    return QEXTTrackObjectFunctor5<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5>(func, obj1, obj2, obj3, obj4, obj5);
}

/** Creates an adaptor of type QEXTTrackObjectFunctor4 which wraps a functor.
 * @param func Functor that shall be wrapped.
 * @param obj1 Trackable object.
 * @param obj2 Trackable object.
 * @param obj3 Trackable object.
 * @param obj4 Trackable object.
 * @return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4>
inline QEXTTrackObjectFunctor4<T_functor, T_obj1, T_obj2, T_obj3, T_obj4>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4) {
    return QEXTTrackObjectFunctor4<T_functor, T_obj1, T_obj2, T_obj3, T_obj4>(func, obj1, obj2, obj3, obj4);
}

/** Creates an adaptor of type QEXTTrackObjectFunctor3 which wraps a functor.
 * @param func Functor that shall be wrapped.
 * @param obj1 Trackable object.
 * @param obj2 Trackable object.
 * @param obj3 Trackable object.
 * @return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3>
inline QEXTTrackObjectFunctor3<T_functor, T_obj1, T_obj2, T_obj3>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3) {
    return QEXTTrackObjectFunctor3<T_functor, T_obj1, T_obj2, T_obj3>(func, obj1, obj2, obj3);
}

/** Creates an adaptor of type QEXTTrackObjectFunctor2 which wraps a functor.
 * @param func Functor that shall be wrapped.
 * @param obj1 Trackable object.
 * @param obj2 Trackable object.
 * @return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1, typename T_obj2>
inline QEXTTrackObjectFunctor2<T_functor, T_obj1, T_obj2>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2) {
    return QEXTTrackObjectFunctor2<T_functor, T_obj1, T_obj2>(func, obj1, obj2);
}

/** Creates an adaptor of type QEXTTrackObjectFunctor1 which wraps a functor.
 * @param func Functor that shall be wrapped.
 * @param obj1 Trackable object.
 * @return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * @ingroup qextTrackObjectFunctor
 */
template <typename T_functor, typename T_obj1>
inline QEXTTrackObjectFunctor1<T_functor, T_obj1>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1) {
    return QEXTTrackObjectFunctor1<T_functor, T_obj1>(func, obj1);
}

#endif // QEXTTRACKOBJECTFUNCTOR_H
