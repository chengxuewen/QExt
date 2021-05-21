#ifndef QEXTVISITOR_H
#define QEXTVISITOR_H

#include <qexttypetrait.h>

namespace qextinternal {

//This should really be an inner class of LimitDerivedTarget, without the T_limit template type,
//But the SUN CC 5.7 (not earlier versions) compiler finds it ambiguous when we specify a particular specialization of it.
//and does not seem to allow us to tell it explicitly that it's an inner class.
template <bool I_derived, class T_type, class T_limit> struct WithType;

//Specialization for I_derived = false
template <class T_type, class T_limit>
struct WithType<false, T_type, T_limit>
{
    static void execute(const T_type &, const T_limit &) {}
};

//Specialization for I_derived = true
template <class T_type, class T_limit>
struct WithType<true, T_type, T_limit>
{
    static void execute(const T_type &type, const T_limit &action) { action.m_action(type); }
};


/// Helper struct for qextVisitEachType().
template <class T_target, class T_action>
struct LimitDerivedTarget
{
    typedef LimitDerivedTarget<T_target, T_action> T_self;

    LimitDerivedTarget(const T_action& action) : m_action(action) {}

    template <class T_type>
    void operator()(const T_type &type) const {
        WithType<QEXTBaseAndDerivedTester<T_target, T_type>::value, T_type, T_self>::execute(type, *this);
    }

    T_action m_action;
};

// Specialization for T_target pointer types, to provide a slightly different execute() implementation.
template <bool I_derived, class T_type, class T_limit> struct WithTypePointer;

//Specialization for I_derived = false
template <class T_type, class T_limit>
struct WithTypePointer<false, T_type, T_limit>
{
    static void execute(const T_type&, const T_limit&) {}
};

//Specialization for I_derived = true
template <class T_type, class T_limit>
struct WithTypePointer<true, T_type, T_limit>
{
    static void execute(const T_type &type, const T_limit &action) { action.m_action(&type); }
};

template <class T_target, class T_action>
struct LimitDerivedTarget<T_target*, T_action>
{
    typedef LimitDerivedTarget<T_target*, T_action> T_self;

    LimitDerivedTarget(const T_action &action) : m_action(action) {}

    template <class T_type>
    void operator()(const T_type &type) const {
        WithTypePointer<QEXTBaseAndDerivedTester<T_target, T_type>::value, T_type, T_self>::execute(type, *this);
    }

    T_action m_action;
};

} // namespace qextinternal


// struct QEXTVisitor was introduced as a result of https://bugzilla.gnome.org/show_bug.cgi?id=724496
// The advantage of using specializations of a template struct instead of overloads of
// a template function is described by Herb Sutter in http://www.gotw.ca/publications/mill17.htm
// In libsigc++ the main reason for using this technique is that we can avoid using ADL
// (argument-dependent lookup), and therefore there is no risk that a qextVisitEach() overload
// in e.g. Boost is selected by mistake.

/** sigc::QEXTVisitor<T_functor>::doVisitEach() performs a functor on each of the targets of a functor.
 * All unknown types just call @a action on them.
 * Add specializations that specialize the @a T_functor argument for your own
 * functor types, so that subobjects get visited. This is needed to enable
 * auto-disconnection support for your functor types.
 *
 * @par Example:
 *   @code
 *   namespace some_ns
 *   {
 *     struct some_functor
 *     {
 *       void operator()() {}
 *       some_possibly_sigc_trackable_derived_type some_data_member;
 *       some_other_functor_type some_other_functor;
 *     };
 *   }
 *
 *     template <>
 *     struct QEXTVisitor<some_ns::some_functor>
 *     {
 *       template <class T_action>
 *       static void doVisitEach(const T_action& action,
 *                                 const some_ns::some_functor& target)
 *       {
 *         sigc::qextVisitEach(action, target.some_data_member);
 *         sigc::qextVisitEach(action, target.some_other_functor);
 *       }
 *     };
 *   @endcode
 *
 * @ingroup sigcfunctors
 */
template <class T_functor>
struct QEXTVisitor
{
    template <class T_action>
    static void doVisitEach(const T_action &action, const T_functor &functor) {
        action(functor);
    }
};

/** This function performs a functor on each of the targets of a functor.
 *
 * @ingroup sigcfunctors
 */
template <class T_action, class T_functor>
void qextVisitEach(const T_action &action, const T_functor &functor) {
    QEXTVisitor<T_functor>::doVisitEach(action, functor);
}

/** This function performs a functor on each of the targets
 * of a functor limited to a restricted type.
 *
 * @ingroup sigcfunctors
 */
template <class T_type, class T_action, class T_functor>
void qextVisitEachType(const T_action &action, const T_functor &functor) {
    typedef qextinternal::LimitDerivedTarget<T_type, T_action> LimitedActionType;

    LimitedActionType limitedAction(action);

    //specifying the types of the template specialization prevents disconnection of bound trackable references (such as with sigc::ref()),
    //probably because the qextVisitEach<> specializations take various different template types,
    //in various sequences, and we are probably specifying only a subset of them with this.
    //
    //But this is required by the AIX (and maybe IRIX MipsPro  and Tru64) compilers.
    //I guess that sigc::ref() therefore does not work on those platforms. murrayc
    // qextVisitEach<LimitedActionType, T_functor>(limited_action, functor);

    //g++ (even slightly old ones) is our primary platform, so we could use the non-crashing version.
    //However, the explicit version also fixes a crash in a slightly more common case: http://bugzilla.gnome.org/show_bug.cgi?id=169225
    //Users (and distributors) of libsigc++ on AIX (and maybe IRIX MipsPro and Tru64) do
    //need to use the version above instead, to allow compilation.

    //Added 2014-03-20: The preceding comment probably does not apply any more,
    //now when the qextVisitEach<>() overloads have been replaced by QEXTVisitor<> specializations.
    //It's probably safe to add explicit template parameters on calls to qextVisitEach(),
    //qextVisitEachType() and QEXTVisitor::doVisitEach(), if necessary.

    qextVisitEach(limitedAction, functor);
}



#endif // QEXTVISITOR_H
