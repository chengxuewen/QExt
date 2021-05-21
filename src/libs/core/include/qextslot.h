#ifndef QEXTSLOT_H
#define QEXTSLOT_H

#include <qextslotbase.h>
#include <qextadaptortrait.h>

namespace qextinternal {

template <class T_functor>
struct QEXTTypedSlotRepresentation : public QEXTSlotRepresentation
{
    typedef QEXTTypedSlotRepresentation<T_functor> Self;
    /* Use an adaptor type so that arguments can be passed as const references
   * through explicit template instantiation from slot_call#::call_it() */
    typedef typename QEXTAdaptorTrait<T_functor>::AdaptorType AdaptorType;

    QEXTTypedSlotRepresentation(const T_functor &functor)
        : QEXTSlotRepresentation(QEXT_NULLPTR, &destroy, &deepCopy), m_functor(functor) {
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoBind(this), m_functor);
    }

    QEXTTypedSlotRepresentation(const QEXTTypedSlotRepresentation &cl)
        : QEXTSlotRepresentation(cl.m_call, &destroy, &deepCopy), m_functor(cl.m_functor) {
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoBind(this), m_functor);
    }

    ~QEXTTypedSlotRepresentation() {
        m_call = QEXT_NULLPTR;
        m_destroy = QEXT_NULLPTR;
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoUnbind(this), m_functor);
    }

    /** Detaches the stored functor from the other referred trackables and destroys it.
   * This does not destroy the base slot_rep object.
   */
    static void *destroy(void *data) {
        Self *self = static_cast<Self*>(reinterpret_cast<QEXTSlotRepresentation*>(data));
        self->m_call = QEXT_NULLPTR;
        self->m_destroy = QEXT_NULLPTR;
        qextVisitEachType<QEXTTrackable *>(QEXTSlotDoUnbind(self), self->m_functor);
        self->m_functor.~AdaptorType();
        /* don't call disconnect() here: destroy() is either called
       * a) from the parent itself (in which case disconnect() leads to a segfault) or
       * b) from a parentless QEXTSlot (in which case disconnect() does nothing)
       */
        return QEXT_NULLPTR;
    }

    static void *deepCopy(void *data) {
        QEXTSlotRepresentation *rep = reinterpret_cast<QEXTSlotRepresentation *>(data);
        return static_cast<QEXTSlotRepresentation *>(new Self(*static_cast<Self*>(rep)));
    }

    AdaptorType m_functor;
};


template<class T_functor, class T_return>
struct QEXTSlotCall0
{
    static T_return callIt(QEXTSlotRepresentation *rep) {
        typedef QEXTTypedSlotRepresentation<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
        return (typedRep->m_functor)();
    }

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};


template<class T_functor, class T_return, class T_arg1>
struct QEXTSlotCall1
{
    static T_return callIt(QEXTSlotRepresentation *rep, typename QEXTTypeTrait<T_arg1>::Take arg1) {
        typedef QEXTTypedSlotRepresentation<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
//        return (typedRep->m_functor).template operator<typename QEXTTypeTrait<T_arg1>::Take>(arg1);
        typedRep->m_functor(arg1);
    }

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};


template<class T_functor, class T_return, class T_arg1, class T_arg2>
struct QEXTSlotCall2
{
    static T_return callIt(QEXTSlotRepresentation *rep, typename QEXTTypeTrait<T_arg1>::Take arg1, typename QEXTTypeTrait<T_arg2>::Take arg2) {
        typedef QEXTTypedSlotRepresentation<T_functor> TypedSlot;
        TypedSlot *typedRep = static_cast<TypedSlot*>(rep);
//        return (typedRep->m_functor).QEXT_WORKAROUND_OPERATOR_PARENTHESES<typename QEXTTypeTrait<T_arg1>::Take, typename QEXTTypeTrait<T_arg2>::Take>(arg1, arg2);
        typedRep->m_functor(arg1, arg2);
    }

    static HookFunctionType address() {
        return reinterpret_cast<HookFunctionType>(&callIt);
    }
};

} /* namespace qextinternal */



template <class T_return, class T_arg1, class T_arg2>
class QEXTSlot2 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRepresentation RepType;
public:
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;
    typedef typename QEXTTypeTrait<T_arg2>::Take Arg2Type;
    typedef T_return (*CallType)(RepType*, Arg1Type, Arg2Type);
    typedef T_return ResultType;

    QEXTSlot2() {}
    template <class T_functor>
    QEXTSlot2(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRepresentation<T_functor>(func)) {
        //The QEXTSlotBase:: is necessary to stop the HP-UX aCC compiler from being confused. murrayc.
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall2<T_functor, T_return, T_arg1, T_arg2>::address();
    }
    QEXTSlot2(const QEXTSlot2 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1, Arg2Type arg2) const {
        if (!this->isEmpty() && !this->blocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep, arg1, arg2);
        }
        return T_return();
    }

    QEXTSlot2& operator=(const QEXTSlot2 &src) {
        QEXTSlotBase::operator=(src); return *this;
    }
};

template <class T_return, class T_arg1>
class QEXTSlot1 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRepresentation RepType;
public:
    typedef typename QEXTTypeTrait<T_arg1>::Take Arg1Type;
    typedef T_return (*CallType)(RepType*, Arg1Type);
    typedef T_return ResultType;

    QEXTSlot1() {}
    template <class T_functor>
    QEXTSlot1(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRepresentation<T_functor>(func))
    {
        //The QEXTSlotBase:: is necessary to stop the HP-UX aCC compiler from being confused. murrayc.
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall1<T_functor, T_return, T_arg1>::address();
    }
    QEXTSlot1(const QEXTSlot1 &src) : QEXTSlotBase(src) {}

    T_return operator()(Arg1Type arg1) const {
        if (!this->isEmpty() && !this->blocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep, arg1);
        }
        return T_return();
    }

    QEXTSlot1& operator=(const QEXTSlot1 &src) {
        QEXTSlotBase::operator=(src); return *this;
    }
};

template <class T_return>
class QEXTSlot0 : public QEXTSlotBase
{
    typedef qextinternal::QEXTSlotRepresentation RepType;
public:
    typedef T_return (*CallType)(RepType *);
    typedef T_return ResultType;

    QEXTSlot0() {}
    template <class T_functor>
    QEXTSlot0(const T_functor &func) : QEXTSlotBase(new qextinternal::QEXTTypedSlotRepresentation<T_functor>(func)) {
        //The QEXTSlotBase:: is necessary to stop the HP-UX aCC compiler from being confused. murrayc.
        QEXTSlotBase::m_slotRep->m_call = qextinternal::QEXTSlotCall0<T_functor, T_return>::address();
    }
    QEXTSlot0(const QEXTSlot0 &src) : QEXTSlotBase(src) {}

    T_return operator()() const {
        if (!this->isEmpty() && !this->blocked()) {
            return (reinterpret_cast<CallType>(QEXTSlotBase::m_slotRep->m_call))(QEXTSlotBase::m_slotRep);
        }
        return T_return();
    }

    QEXTSlot0& operator=(const QEXTSlot0 &src) {
        QEXTSlotBase::operator=(src); return *this;
    }
};




template <class T_return, class T_arg1 = QEXTNil, class T_arg2 = QEXTNil>
class QEXTSlot : public QEXTSlot2<T_return, T_arg1, T_arg2>
{
public:
    typedef QEXTSlot2<T_return, T_arg1, T_arg2> ParentType;

    QEXTSlot() {}
    template <class T_functor>
    QEXTSlot(const T_functor &func) : ParentType(func) {}
    QEXTSlot(const QEXTSlot &src) : ParentType(reinterpret_cast<const ParentType&>(src)) {}
};

template <class T_return, class T_arg1>
class QEXTSlot <T_return, T_arg1, QEXTNil> : public QEXTSlot1<T_return, T_arg1>
{
public:
    typedef QEXTSlot1<T_return, T_arg1> ParentType;

    QEXTSlot() {}
    template <class T_functor>
    QEXTSlot(const T_functor &func) : ParentType(func) {}
    QEXTSlot(const QEXTSlot &src) : ParentType(reinterpret_cast<const ParentType&>(src)) {}
};

template <class T_return>
class QEXTSlot <T_return, QEXTNil, QEXTNil> : public QEXTSlot0<T_return>
{
public:
    typedef QEXTSlot0<T_return> ParentType;

    QEXTSlot() {}
    template <class T_functor>
    QEXTSlot(const T_functor &func) : ParentType(func) {}
    QEXTSlot(const QEXTSlot &src) : ParentType(reinterpret_cast<const ParentType&>(src)) {}
};


#endif // QEXTSLOT_H
