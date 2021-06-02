#ifndef QEXTSLOT_H
#define QEXTSLOT_H

#include <qextslotbase.h>
#include <qextadaptortrait.h>

#include <QPointer>
#include <QObject>

namespace qextinternal {

template <typename T_obj, bool I_qobject_derived = QEXTBaseAndDerivedTester<QObject, T_obj>::value>
struct QEXTQObjectTrait
{
    typedef T_obj ObjectType;
    typedef T_obj TrackableType;

    static bool isTrackable() { return false; }
};

template <typename T_obj>
struct QEXTQObjectTrait<T_obj, true>
{
    typedef T_obj ObjectType;
    typedef QPointer<T_obj> TrackableType;

    static bool isTrackable() { return true; }

    TrackableType m_trackable;
};





/** A typed QEXTSlotRep.
 * A typed QEXTSlotRep holds a functor that can be invoked from
 * QEXTSlot::operator()(). qextVisitEach() is used to visit the functor's
 * targets that inherit trackable recursively and register the
 * notification callback. Consequently the QEXTSlotRep object will be
 * notified when some referred object is destroyed or overwritten.
 */
template <typename T_functor>
struct QEXTTypedSlotRep : public QEXTSlotRep
{
    typedef QEXTTypedSlotRep<T_functor> Self;

    /* Use an adaptor type so that arguments can be passed as const references
     * through explicit template instantiation from QEXTSlotCall#::callIt() */
    typedef typename QEXTAdaptorTrait<T_functor>::AdaptorType AdaptorType;

    /** Constructs an invalid typed QEXTSlotRep object.
     * The notification callback is registered using qextVisitEach().
     * @param functor The functor contained by the new QEXTSlotRep object.
     */
    QEXTTypedSlotRep(const T_functor &functor)
        : QEXTSlotRep(QEXT_NULLPTR, &destroy, &deepCopy), m_functor(functor) {
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoBind(this), m_functor);
    }

    QEXTTypedSlotRep(const QEXTTypedSlotRep &src)
        : QEXTSlotRep(src.m_call, &destroy, &deepCopy), m_functor(src.m_functor) {
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoBind(this), m_functor);
    }

    ~QEXTTypedSlotRep() {}

    /** Detaches the stored functor from the other referred trackables and destroys it.
     * This does not destroy the base QEXTSlotRep object.
     */
    static void *destroy(void *data) {
        Self *self = static_cast<Self*>(reinterpret_cast<QEXTSlotRep*>(data));
        self->m_call = QEXT_NULLPTR;
        self->m_destroy = QEXT_NULLPTR;
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoUnbind(self), self->m_functor);
        //        self->m_functor.~AdaptorType();
        return QEXT_NULLPTR;
    }

    /** Makes a deep copy of the slot_rep object.
     * Deep copy means that the notification callback of the new
     * QEXTSlotRep object is registered in the referred trackables.
     * @return A deep copy of the QEXTSlotRep object.
     */
    static void *deepCopy(void *data) {
        QEXTSlotRep *rep = reinterpret_cast<QEXTSlotRep *>(data);
        return static_cast<QEXTSlotRep *>(new Self(*static_cast<Self*>(rep)));
    }

    /** The functor contained by this QEXTSlotRep object. */
    AdaptorType m_functor;
};

/** Abstracts functor execution.
 * callIt() invokes a functor of type @e T_functor with a list of
 * parameters whose types are given by the template arguments.
 * address() forms a function pointer from callIt().
 *
 * The following template arguments are used:
 * - @e T_functor The functor type.
 * - @e T_return The return type of call_it().
 * - @e T_arg1 Argument type used in the definition of callIt().
 * - @e T_arg2 Argument type used in the definition of callIt().
 * - @e T_arg3 Argument type used in the definition of callIt().
 * - @e T_arg4 Argument type used in the definition of callIt().
 * - @e T_arg5 Argument type used in the definition of callIt().
 * - @e T_arg6 Argument type used in the definition of callIt().
 * - @e T_arg7 Argument type used in the definition of callIt().
 *
 */
template<typename T_functor, typename T_return,
         typename T_arg1, typename T_arg2, typename T_arg3,
         typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTSlotCall7
{
    /** Invokes a functor of type @p T_functor.
     * @param rep slot_rep object that holds a functor of type @p T_functor.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return values of the functor invocation.
     */
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6,
                           typename QEXTTypeTrait<T_arg7>::Take arg7) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take,
                typename QEXTTypeTrait<T_arg4>::Take,
                typename QEXTTypeTrait<T_arg5>::Take,
                typename QEXTTypeTrait<T_arg6>::Take,
                typename QEXTTypeTrait<T_arg7>::Take>(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Forms a function pointer from callIt().
     * @return A function pointer formed from callIt().
     */
    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

/** Abstracts functor execution.
 * callIt() invokes a functor of type @e T_functor with a list of
 * parameters whose types are given by the template arguments.
 * address() forms a function pointer from callIt().
 *
 * The following template arguments are used:
 * - @e T_functor The functor type.
 * - @e T_return The return type of callIt().
 * - @e T_arg1 Argument type used in the definition of callIt().
 * - @e T_arg2 Argument type used in the definition of callIt().
 * - @e T_arg3 Argument type used in the definition of callIt().
 * - @e T_arg4 Argument type used in the definition of callIt().
 * - @e T_arg5 Argument type used in the definition of callIt().
 * - @e T_arg6 Argument type used in the definition of callIt().
 *
 */
template<typename T_functor, typename T_return,
         typename T_arg1, typename T_arg2, typename T_arg3,
         typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTSlotCall6
{
    /** Invokes a functor of type @p T_functor.
     * @param rep slot_rep object that holds a functor of type @p T_functor.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return values of the functor invocation.
     */
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take,
                typename QEXTTypeTrait<T_arg4>::Take,
                typename QEXTTypeTrait<T_arg5>::Take,
                typename QEXTTypeTrait<T_arg6>::Take>(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Forms a function pointer from callIt().
     * @return A function pointer formed from callIt().
     */
    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

/** Abstracts functor execution.
 * callIt() invokes a functor of type @e T_functor with a list of
 * parameters whose types are given by the template arguments.
 * address() forms a function pointer from callIt().
 *
 * The following template arguments are used:
 * - @e T_functor The functor type.
 * - @e T_return The return type of callIt().
 * - @e T_arg1 Argument type used in the definition of callIt().
 * - @e T_arg2 Argument type used in the definition of callIt().
 * - @e T_arg3 Argument type used in the definition of callIt().
 * - @e T_arg4 Argument type used in the definition of callIt().
 * - @e T_arg5 Argument type used in the definition of callIt().
 *
 */
template<typename T_functor, typename T_return,
         typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTSlotCall5
{
    /** Invokes a functor of type @p T_functor.
     * @param rep slot_rep object that holds a functor of type @p T_functor.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return values of the functor invocation.
     */
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take,
                typename QEXTTypeTrait<T_arg4>::Take,
                typename QEXTTypeTrait<T_arg5>::Take>(arg1, arg2, arg3, arg4, arg5);
    }

    /** Forms a function pointer from callIt().
     * @return A function pointer formed from callIt().
     */
    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

/** Abstracts functor execution.
 * callIt() invokes a functor of type @e T_functor with a list of
 * parameters whose types are given by the template arguments.
 * address() forms a function pointer from callIt().
 *
 * The following template arguments are used:
 * - @e T_functor The functor type.
 * - @e T_return The return type of callIt().
 * - @e T_arg1 Argument type used in the definition of callIt().
 * - @e T_arg2 Argument type used in the definition of callIt().
 * - @e T_arg3 Argument type used in the definition of callIt().
 * - @e T_arg4 Argument type used in the definition of callIt().
 *
 */
template<typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTSlotCall4
{
    /** Invokes a functor of type @p T_functor.
     * @param rep slot_rep object that holds a functor of type @p T_functor.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return values of the functor invocation.
     */
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take,
                typename QEXTTypeTrait<T_arg4>::Take>(arg1, arg2, arg3, arg4);
    }

    /** Forms a function pointer from callIt().
     * @return A function pointer formed from callIt().
     */
    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

/** Abstracts functor execution.
 * callIt() invokes a functor of type @e T_functor with a list of
 * parameters whose types are given by the template arguments.
 * address() forms a function pointer from callIt().
 *
 * The following template arguments are used:
 * - @e T_functor The functor type.
 * - @e T_return The return type of callIt().
 * - @e T_arg1 Argument type used in the definition of callIt().
 * - @e T_arg2 Argument type used in the definition of callIt().
 * - @e T_arg3 Argument type used in the definition of callIt().
 *
 */
template<typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTSlotCall3
{
    /** Invokes a functor of type @p T_functor.
     * @param rep slot_rep object that holds a functor of type @p T_functor.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return values of the functor invocation.
     */
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take>(arg1, arg2, arg3);
    }

    /** Forms a function pointer from callIt().
     * @return A function pointer formed from callIt().
     */
    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

/** Abstracts functor execution.
 * callIt() invokes a functor of type @e T_functor with a list of
 * parameters whose types are given by the template arguments.
 * address() forms a function pointer from callIt().
 *
 * The following template arguments are used:
 * - @e T_functor The functor type.
 * - @e T_return The return type of callIt().
 * - @e T_arg1 Argument type used in the definition of callIt().
 * - @e T_arg2 Argument type used in the definition of callIt().
 *
 */
template<typename T_functor, typename T_return, typename T_arg1, typename T_arg2>
struct QEXTSlotCall2
{
    /** Invokes a functor of type @p T_functor.
     * @param rep slot_rep object that holds a functor of type @p T_functor.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return values of the functor invocation.
     */
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take>(arg1, arg2);
    }

    /** Forms a function pointer from callIt().
     * @return A function pointer formed from callIt().
     */
    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};


/** Abstracts functor execution.
 * callIt() invokes a functor of type @e T_functor with a list of
 * parameters whose types are given by the template arguments.
 * address() forms a function pointer from callIt().
 *
 * The following template arguments are used:
 * - @e T_functor The functor type.
 * - @e T_return The return type of callIt().
 * - @e T_arg1 Argument type used in the definition of callIt().
 *
 */
template<typename T_functor, typename T_return, typename T_arg1>
struct QEXTSlotCall1
{
    /** Invokes a functor of type @p T_functor.
     * @param rep QEXTSlotRep object that holds a functor of type @p T_functor.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return values of the functor invocation.
     */
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take>(arg1);
    }

    /** Forms a function pointer from callIt().
     * @return A function pointer formed from callIt().
     */
    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

/** Abstracts functor execution.
 * callIt() invokes a functor of type @e T_functor with a list of
 * parameters whose types are given by the template arguments.
 * address() forms a function pointer from callIt().
 *
 * The following template arguments are used:
 * - @e T_functor The functor type.
 * - @e T_return The return type of callIt().
 *
 */
template<typename T_functor, typename T_return>
struct QEXTSlotCall0
{
    /** Invokes a functor of type @p T_functor.
     * @param rep QEXTSlotRep object that holds a functor of type @p T_functor.
     * @return The return values of the functor invocation.
     */
    static T_return callIt(QEXTSlotRep *rep) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor)();
    }

    /** Forms a function pointer from callIt().
     * @return A function pointer formed from callIt().
     */
    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

} /* namespace qextinternal */


/** Converts an arbitrary functor to a unified type which is opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg3 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg4 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg5 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg6 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg7 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * To use simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments compiler errors are triggered. When called the slot
 * will invoke the functor with minimal copies.
 * setBlock() and unblock() can be used to block the functor's invocation
 * from operator()() temporarily.
 *
 * You should use the more convenient unnumbered QEXTSlot template.
 *
 * @ingroup slot
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTSlot7 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;
    typedef typename QEXTTypeTrait<T_arg2>::Take Arg2Type;
    typedef typename QEXTTypeTrait<T_arg3>::Take Arg3Type;
    typedef typename QEXTTypeTrait<T_arg4>::Take Arg4Type;
    typedef typename QEXTTypeTrait<T_arg5>::Take Arg5Type;
    typedef typename QEXTTypeTrait<T_arg6>::Take Arg6Type;
    typedef typename QEXTTypeTrait<T_arg7>::Take Arg7Type;

    typedef T_return (*CallType)(RepType*, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type);

    QEXTSlot7() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot7(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall7<T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::address();
    }
    QEXTSlot7(const QEXTSlot7 &src) : QEXTSlotBase(src) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3,
                        Arg4Type arg4, Arg5Type arg5, Arg6Type arg6, Arg7Type arg7) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
        return T_return();
    }

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlot7& operator=(const QEXTSlot7 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

/** Converts an arbitrary functor to a unified type which is opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg3 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg4 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg5 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg6 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * To use simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments compiler errors are triggered. When called the slot
 * will invoke the functor with minimal copies.
 * setBlock() and unblock() can be used to block the functor's invocation
 * from operator()() temporarily.
 *
 * You should use the more convenient unnumbered QEXTSlot template.
 *
 * @ingroup slot
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTSlot6 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;
    typedef typename QEXTTypeTrait<T_arg2>::Take Arg2Type;
    typedef typename QEXTTypeTrait<T_arg3>::Take Arg3Type;
    typedef typename QEXTTypeTrait<T_arg4>::Take Arg4Type;
    typedef typename QEXTTypeTrait<T_arg5>::Take Arg5Type;
    typedef typename QEXTTypeTrait<T_arg6>::Take Arg6Type;

    typedef T_return (*CallType)(RepType*, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type);

    QEXTSlot6() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot6(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall6<T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::address();
    }
    QEXTSlot6(const QEXTSlot6 &src) : QEXTSlotBase(src) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6);
        }
        return T_return();
    }

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlot6& operator=(const QEXTSlot6 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

/** Converts an arbitrary functor to a unified type which is opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg3 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg4 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg5 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * To use simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments compiler errors are triggered. When called the slot
 * will invoke the functor with minimal copies.
 * setBlock() and unblock() can be used to block the functor's invocation
 * from operator()() temporarily.
 *
 * You should use the more convenient unnumbered QEXTSlot template.
 *
 * @ingroup slot
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTSlot5 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;
    typedef typename QEXTTypeTrait<T_arg2>::Take Arg2Type;
    typedef typename QEXTTypeTrait<T_arg3>::Take Arg3Type;
    typedef typename QEXTTypeTrait<T_arg4>::Take Arg4Type;
    typedef typename QEXTTypeTrait<T_arg5>::Take Arg5Type;

    typedef T_return (*CallType)(RepType*, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type);

    QEXTSlot5() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot5(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall5<T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::address();
    }
    QEXTSlot5(const QEXTSlot5 &src) : QEXTSlotBase(src) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3, arg4, arg5);
        }
        return T_return();
    }

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlot5& operator=(const QEXTSlot5 &src) {
        QEXTSlotBase::operator=(src); return *this;
    }
};

/** Converts an arbitrary functor to a unified type which is opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg3 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg4 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * To use simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments compiler errors are triggered. When called the slot
 * will invoke the functor with minimal copies.
 * setBlock() and unblock() can be used to block the functor's invocation
 * from operator()() temporarily.
 *
 * You should use the more convenient unnumbered QEXTSlot template.
 *
 * @ingroup slot
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTSlot4 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;
    typedef typename QEXTTypeTrait<T_arg2>::Take Arg2Type;
    typedef typename QEXTTypeTrait<T_arg3>::Take Arg3Type;
    typedef typename QEXTTypeTrait<T_arg4>::Take Arg4Type;

    typedef T_return (*CallType)(RepType*, Arg1Type, Arg2Type, Arg3Type, Arg4Type);

    QEXTSlot4() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot4(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall4<T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4>::address();
    }
    QEXTSlot4(const QEXTSlot4 &src) : QEXTSlotBase(src) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3, arg4);
        }
        return T_return();
    }

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlot4& operator=(const QEXTSlot4 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

/** Converts an arbitrary functor to a unified type which is opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg3 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * To use simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments compiler errors are triggered. When called the slot
 * will invoke the functor with minimal copies.
 * setBlock() and unblock() can be used to block the functor's invocation
 * from operator()() temporarily.
 *
 * You should use the more convenient unnumbered QEXTSlot template.
 *
 * @ingroup slot
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTSlot3 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;
    typedef typename QEXTTypeTrait<T_arg2>::Take Arg2Type;
    typedef typename QEXTTypeTrait<T_arg3>::Take Arg3Type;

    typedef T_return (*CallType)(RepType*, Arg1Type, Arg2Type, Arg3Type);

    QEXTSlot3() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot3(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall3<T_functor, T_return, T_arg1, T_arg2, T_arg3>::address();
    }
    QEXTSlot3(const QEXTSlot3 &src) : QEXTSlotBase(src) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3);
        }
        return T_return();
    }

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlot3& operator=(const QEXTSlot3 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

/** Converts an arbitrary functor to a unified type which is opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * To use simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments compiler errors are triggered. When called the slot
 * will invoke the functor with minimal copies.
 * setBlock() and unblock() can be used to block the functor's invocation
 * from operator()() temporarily.
 *
 * You should use the more convenient unnumbered QEXTSlot template.
 *
 * @ingroup slot
 */
template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTSlot2 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;
    typedef typename QEXTTypeTrait<T_arg2>::Take Arg2Type;

    typedef T_return (*CallType)(RepType*, Arg1Type, Arg2Type);

    QEXTSlot2() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot2(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall2<T_functor, T_return, T_arg1, T_arg2>::address();
    }
    QEXTSlot2(const QEXTSlot2 &src) : QEXTSlotBase(src) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(Arg1Type arg1, Arg2Type arg2) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2);
        }
        return T_return();
    }

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlot2& operator=(const QEXTSlot2 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

/** Converts an arbitrary functor to a unified type which is opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * To use simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments compiler errors are triggered. When called the slot
 * will invoke the functor with minimal copies.
 * setBlock() and unblock() can be used to block the functor's invocation
 * from operator()() temporarily.
 *
 * You should use the more convenient unnumbered QEXTSlot template.
 *
 * @ingroup slot
 */
template <typename T_return, typename T_arg1>
class QEXTSlot1 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return    ResultType;
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;

    typedef T_return (*CallType)(RepType*, Arg1Type);

    QEXTSlot1() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot1(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall1<T_functor, T_return, T_arg1>::address();
    }

    QEXTSlot1(const QEXTSlot1 &src) : QEXTSlotBase(src) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(Arg1Type arg1) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1);
        }
        return T_return();
    }

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlot1& operator=(const QEXTSlot1 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

/** Converts an arbitrary functor to a unified type which is opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 *
 * To use simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments compiler errors are triggered. When called the slot
 * will invoke the functor with minimal copies.
 * setBlock() and unblock() can be used to block the functor's invocation
 * from operator()() temporarily.
 *
 * You should use the more convenient unnumbered QEXTSlot template.
 *
 * @ingroup slot
 */
template <typename T_return>
class QEXTSlot0 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef T_return (*CallType)(RepType*);

    QEXTSlot0() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot0(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall0<T_functor, T_return>::address();
    }
    QEXTSlot0(const QEXTSlot0 &src) : QEXTSlotBase(src) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @return The return value of the functor invocation.
     */
    T_return operator()() const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data());
        }
        return T_return();
    }

    /** Overrides this slot making a copy from another slot.
     * @param src The slot from which to make a copy.
     * @return @p this.
     */
    QEXTSlot0& operator=(const QEXTSlot0 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};



/** Convenience wrapper for the numbered QEXTSlot# templates.
 * Slots convert arbitrary functors to unified types which are opaque.
 * QEXTSlot itself is a functor or to be more precise a closure. It contains
 * a single, arbitrary functor (or closure) that is executed in operator()().
 *
 * The template arguments determine the function signature of operator()():
 * - @e T_return The return type of operator()().
 * - @e T_arg1 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg3 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg4 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg5 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg6 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 * - @e T_arg7 Argument type used in the definition of operator()(). The default @p QEXTNil means no argument.
 *
 * To use, simply assign the desired functor to the slot. If the functor
 * is not compatible with the parameter list defined with the template
 * arguments, compiler errors are triggered. When called, the slot
 * will invoke the functor with minimal copies.
 * block() and unblock() can be used to temporarily block the functor's
 * invocation from operator()().
 *
 * @par Example:
 * @code
 * void foo(int) {}
 * QEXTSlot<void, int> s = qextPointerFunctor(&foo);
 * s(19);
 * @endcode
 *
 * QEXTSlot<> is similar to std::function<>. If you're going to assign the
 * resulting functor to a QEXTSlot or connect it to a QEXTSignal, it's better
 * not to use std::function. It would become un unnecessary extra wrapper.
 *
 * @ingroup slot
 */
template <typename T_return,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTSlot : public QEXTSlot7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
public:
    typedef QEXTSlot7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;

    QEXTSlot() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @param arg7 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

/** Convenience wrapper for the numbered QEXTSlot6 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSlot
 * template for 6 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTSlot6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
public:
    typedef QEXTSlot6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;

    QEXTSlot() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @param arg6 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

/** Convenience wrapper for the numbered QEXTSlot5 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSlot
 * template for 5 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTSlot5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
public:
    typedef QEXTSlot5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;

    QEXTSlot() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @param arg5 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

/** Convenience wrapper for the numbered QEXTSlot4 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSlot
 * template for 4 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>
{
public:
    typedef QEXTSlot4<T_return, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;

    QEXTSlot() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @param arg4 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

/** Convenience wrapper for the numbered QEXTSlot3 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSlot
 * template for 3 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot3<T_return, T_arg1, T_arg2, T_arg3>
{
public:
    typedef QEXTSlot3<T_return, T_arg1, T_arg2, T_arg3> BaseType;

    QEXTSlot() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @param arg3 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

/** Convenience wrapper for the numbered QEXTSlot2 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSlot
 * template for 2 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTSlot<T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot2<T_return, T_arg1, T_arg2>
{
public:
    typedef QEXTSlot2<T_return, T_arg1, T_arg2> BaseType;

    QEXTSlot() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @param arg2 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(T_arg1 arg1, T_arg2 arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

/** Convenience wrapper for the numbered QEXTSlot1 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSlot
 * template for 1 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return, typename T_arg1>
class QEXTSlot<T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot1<T_return, T_arg1>
{
public:
    typedef QEXTSlot1<T_return, T_arg1> BaseType;

    QEXTSlot() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @param arg1 Argument to be passed on to the functor.
     * @return The return value of the functor invocation.
     */
    T_return operator()(T_arg1 arg1) const {
        return BaseType::operator ()(arg1);
    }
};

/** Convenience wrapper for the numbered QEXTSlot0 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSlot
 * template for 0 argument(s), specialized for different numbers of arguments
 * This is possible because the template has default (QEXTNil) template types.
 */
template <typename T_return>
class QEXTSlot<T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot0<T_return>
{
public:
    typedef QEXTSlot0<T_return> BaseType;

    QEXTSlot() {}
    /** Constructs a slot from an arbitrary functor.
     * @param func The desired functor the new slot should be assigned to.
     */
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    /** Invoke the contained functor unless slot is in blocking state.
     * @return The return value of the functor invocation.
     */
    T_return operator()() const {
        return BaseType::operator ()();
    }
};


#endif // QEXTSLOT_H
