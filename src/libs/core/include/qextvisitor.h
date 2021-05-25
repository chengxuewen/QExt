#ifndef QEXTVISITOR_H
#define QEXTVISITOR_H

#include <qexttypetrait.h>

namespace qextinternal {

//This should really be an inner class of LimitDerivedTarget, without the T_limit template type,
//But the SUN CC 5.7 (not earlier versions) compiler finds it ambiguous when we specify a particular specialization of it.
//and does not seem to allow us to tell it explicitly that it's an inner class.
template <bool I_derived, typename T_type, typename T_limit> struct QEXTWithType;

//Specialization for I_derived = false
template <typename T_type, typename T_limit>
struct QEXTWithType<false, T_type, T_limit>
{
    static void execute(const T_type &, const T_limit &) {}
};

//Specialization for I_derived = true
template <typename T_type, typename T_limit>
struct QEXTWithType<true, T_type, T_limit>
{
    static void execute(const T_type &type, const T_limit &action) {
        action.m_action(type);
    }
};


/// Helper struct for qextVisitEachType().
template <typename T_target, typename T_action>
struct QEXTLimitDerivedTarget
{
    typedef QEXTLimitDerivedTarget<T_target, T_action> T_self;

    QEXTLimitDerivedTarget(const T_action& action) : m_action(action) {}

    template <typename T_type>
    void operator()(const T_type &type) const {
        QEXTWithType<QEXTBaseAndDerivedTester<T_target, T_type>::value, T_type, T_self>::execute(type, *this);
    }

    T_action m_action;
};

// Specialization for T_target pointer types, to provide a slightly different execute() implementation.
template <bool I_derived, typename T_type, typename T_limit> struct QEXTWithTypePointer;

//Specialization for I_derived = false
template <typename T_type, typename T_limit>
struct QEXTWithTypePointer<false, T_type, T_limit>
{
    static void execute(const T_type&, const T_limit&) {}
};

//Specialization for I_derived = true
template <typename T_type, typename T_limit>
struct QEXTWithTypePointer<true, T_type, T_limit>
{
    static void execute(const T_type &type, const T_limit &action) { action.m_action(&type); }
};

template <typename T_target, typename T_action>
struct QEXTLimitDerivedTarget<T_target*, T_action>
{
    typedef QEXTLimitDerivedTarget<T_target*, T_action> T_self;

    QEXTLimitDerivedTarget(const T_action &action) : m_action(action) {}

    template <typename T_type>
    void operator()(const T_type &type) const {
        QEXTWithTypePointer<QEXTBaseAndDerivedTester<T_target, T_type>::value, T_type, T_self>::execute(type, *this);
    }

    T_action m_action;
};

} // namespace qextinternal


template <typename T_functor>
struct QEXTVisitor
{
    template <typename T_action>
    static void doVisitEach(const T_action &action, const T_functor &functor) {
        action(functor);
    }
};


template <typename T_action, typename T_functor>
void qextVisitEach(const T_action &action, const T_functor &functor) {
    QEXTVisitor<T_functor>::doVisitEach(action, functor);
}


template <typename T_type, typename T_action, typename T_functor>
void qextVisitEachType(const T_action &action, const T_functor &functor) {
    typedef qextinternal::QEXTLimitDerivedTarget<T_type, T_action> LimitedActionType;

    LimitedActionType limitedAction(action);
    qextVisitEach(limitedAction, functor);
}


#endif // QEXTVISITOR_H
