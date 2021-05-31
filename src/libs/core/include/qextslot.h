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






template <typename T_functor>
struct QEXTTypedSlotRep : public QEXTSlotRep
{
    typedef QEXTTypedSlotRep<T_functor> Self;
    /* Use an adaptor type so that arguments can be passed as const references
     * through explicit template instantiation from slot_call#::callIt() */
    typedef typename QEXTAdaptorTrait<T_functor>::AdaptorType AdaptorType;

    QEXTTypedSlotRep(const T_functor &functor)
        : QEXTSlotRep(QEXT_NULLPTR, &destroy, &deepCopy), m_functor(functor) {
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoBind(this), m_functor);
    }

    QEXTTypedSlotRep(const QEXTTypedSlotRep &src)
        : QEXTSlotRep(src.m_call, &destroy, &deepCopy), m_functor(src.m_functor) {
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoBind(this), m_functor);
    }

    ~QEXTTypedSlotRep() {}

    static void *destroy(void *data) {
        Self *self = static_cast<Self*>(reinterpret_cast<QEXTSlotRep*>(data));
        self->m_call = QEXT_NULLPTR;
        self->m_destroy = QEXT_NULLPTR;
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoUnbind(self), self->m_functor);
//        self->m_functor.~AdaptorType();
        return QEXT_NULLPTR;
    }

    static void *deepCopy(void *data) {
        QEXTSlotRep *rep = reinterpret_cast<QEXTSlotRep *>(data);
        return static_cast<QEXTSlotRep *>(new Self(*static_cast<Self*>(rep)));
    }

    AdaptorType m_functor;
};


template<typename T_functor, typename T_return,
         typename T_arg1, typename T_arg2, typename T_arg3,
         typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTSlotCall7
{
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

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

template<typename T_functor, typename T_return,
         typename T_arg1, typename T_arg2, typename T_arg3,
         typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTSlotCall6
{
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

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

template<typename T_functor, typename T_return,
         typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTSlotCall5
{
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

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

template<typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTSlotCall4
{
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

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

template<typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTSlotCall3
{
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

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

template<typename T_functor, typename T_return, typename T_arg1, typename T_arg2>
struct QEXTSlotCall2
{
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take>(arg1, arg2);
    }

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

template<typename T_functor, typename T_return, typename T_arg1>
struct QEXTSlotCall1
{
    static T_return callIt(QEXTSlotRep *rep,
                           typename QEXTTypeTrait<T_arg1>::Take arg1) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor).template operator ()<
                typename QEXTTypeTrait<T_arg1>::Take>(arg1);
    }

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

template<typename T_functor, typename T_return>
struct QEXTSlotCall0
{
    static T_return callIt(QEXTSlotRep *rep) {
        typedef QEXTTypedSlotRep<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor)();
    }

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

} /* namespace qextinternal */


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
    template <typename T_functor>
    QEXTSlot7(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall7<T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::address();
    }
    QEXTSlot7(const QEXTSlot7 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3,
                        Arg4Type arg4, Arg5Type arg5, Arg6Type arg6, Arg7Type arg7) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
        return T_return();
    }

    QEXTSlot7& operator=(const QEXTSlot7 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

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
    template <typename T_functor>
    QEXTSlot6(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall6<T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::address();
    }
    QEXTSlot6(const QEXTSlot6 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5, Arg6Type arg6) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6);
        }
        return T_return();
    }

    QEXTSlot6& operator=(const QEXTSlot6 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

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
    template <typename T_functor>
    QEXTSlot5(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall5<T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::address();
    }
    QEXTSlot5(const QEXTSlot5 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4, Arg5Type arg5) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3, arg4, arg5);
        }
        return T_return();
    }

    QEXTSlot5& operator=(const QEXTSlot5 &src) {
        QEXTSlotBase::operator=(src); return *this;
    }
};

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
    template <typename T_functor>
    QEXTSlot4(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall4<T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4>::address();
    }
    QEXTSlot4(const QEXTSlot4 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3, arg4);
        }
        return T_return();
    }

    QEXTSlot4& operator=(const QEXTSlot4 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

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
    template <typename T_functor>
    QEXTSlot3(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall3<T_functor, T_return, T_arg1, T_arg2, T_arg3>::address();
    }
    QEXTSlot3(const QEXTSlot3 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2, arg3);
        }
        return T_return();
    }

    QEXTSlot3& operator=(const QEXTSlot3 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

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
    template <typename T_functor>
    QEXTSlot2(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall2<T_functor, T_return, T_arg1, T_arg2>::address();
    }
    QEXTSlot2(const QEXTSlot2 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1, Arg2Type arg2) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1, arg2);
        }
        return T_return();
    }

    QEXTSlot2& operator=(const QEXTSlot2 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

template <typename T_return, typename T_arg1>
class QEXTSlot1 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;

    typedef T_return (*CallType)(RepType*, Arg1Type);

    QEXTSlot1() {}
    template <typename T_functor>
    QEXTSlot1(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall1<T_functor, T_return, T_arg1>::address();
    }
    QEXTSlot1(const QEXTSlot1 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1) const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data(), arg1);
        }
        return T_return();
    }

    QEXTSlot1& operator=(const QEXTSlot1 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};

template <typename T_return>
class QEXTSlot0 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRep RepType;
public:
    typedef T_return ResultType;
    typedef T_return (*CallType)(RepType*);

    QEXTSlot0() {}
    template <typename T_functor>
    QEXTSlot0(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRep<T_functor>(func)) {
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall0<T_functor, T_return>::address();
    }
    QEXTSlot0(const QEXTSlot0 &src) : QEXTSlotBase(src) {}

    T_return operator()() const {
        if (!this->isEmpty() && !this->isBlocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep.data());
        }
        return T_return();
    }

    QEXTSlot0& operator=(const QEXTSlot0 &src) {
        QEXTSlotBase::operator=(src);
        return *this;
    }
};




template <typename T_return,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTSlot : public QEXTSlot7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
public:
    typedef QEXTSlot7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;

    QEXTSlot() {}
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTSlot6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
public:
    typedef QEXTSlot6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;

    QEXTSlot() {}
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTSlot5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
public:
    typedef QEXTSlot5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;

    QEXTSlot() {}
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>
{
public:
    typedef QEXTSlot4<T_return, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;

    QEXTSlot() {}
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot3<T_return, T_arg1, T_arg2, T_arg3>
{
public:
    typedef QEXTSlot3<T_return, T_arg1, T_arg2, T_arg3> BaseType;

    QEXTSlot() {}
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTSlot<T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot2<T_return, T_arg1, T_arg2>
{
public:
    typedef QEXTSlot2<T_return, T_arg1, T_arg2> BaseType;

    QEXTSlot() {}
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_arg1>
class QEXTSlot<T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot1<T_return, T_arg1>
{
public:
    typedef QEXTSlot1<T_return, T_arg1> BaseType;

    QEXTSlot() {}
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    T_return operator()(T_arg1 arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return>
class QEXTSlot<T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSlot0<T_return>
{
public:
    typedef QEXTSlot0<T_return> BaseType;

    QEXTSlot() {}
    template <typename T_functor>
    QEXTSlot(const T_functor &func) : BaseType(func) {}
    QEXTSlot(const QEXTSlot &src) : BaseType(reinterpret_cast<const BaseType&>(src)) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};


#endif // QEXTSLOT_H
