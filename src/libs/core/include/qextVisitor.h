/*************************************************************************************
**
** Library: CommonFramework
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright 2002, The libsigc++ Development Team
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
*************************************************************************************/

#ifndef _QEXTVISITOR_H
#define _QEXTVISITOR_H

#include <qextTypeTrait.h>

namespace qextPrivate
{

//This should really be an inner class of limit_derived_target, without the T_limit template type,
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
        static void execute(const T_type &type, const T_limit &action)
        {
            action.m_action(type);
        }
    };


/// Helper struct for qextVisitEachType().
    template <typename T_target, typename T_action>
    struct QEXTDerivedTargetLimitedAction
    {
        typedef QEXTDerivedTargetLimitedAction<T_target, T_action> T_self;

        QEXTDerivedTargetLimitedAction(const T_action &action) : m_action(action) {}

        template <typename T_type>
        void operator()(const T_type &type) const
        {
            QEXTWithType<QEXTIsBaseOf<T_target, T_type>::value, T_type, T_self>::execute(type, *this);
        }

        T_action m_action;
    };

// Specialization for T_type pointer types, to provide a slightly different execute() implementation.
    template <bool I_derived, typename T_type, typename T_limit> struct QEXTWithTypePointer;

//Specialization for I_derived = false
    template <typename T_type, typename T_limit>
    struct QEXTWithTypePointer<false, T_type, T_limit>
    {
        static void execute(const T_type &, const T_limit &) {}
    };

//Specialization for I_derived = true
    template <typename T_type, typename T_limit>
    struct QEXTWithTypePointer<true, T_type, T_limit>
    {
        static void execute(const T_type &type, const T_limit &action)
        {
            action.m_action(&type);
        }
    };

    template <typename T_type, typename T_action>
    struct QEXTDerivedTargetLimitedAction<T_type *, T_action>
    {
        typedef QEXTDerivedTargetLimitedAction<T_type *, T_action> T_self;

        QEXTDerivedTargetLimitedAction(const T_action &action) : m_action(action) {}

        template <typename T_target>
        void operator()(const T_target &target) const
        {
            QEXTWithTypePointer<QEXTIsBaseOf<T_type, T_target>::value, T_target, T_self>::execute(target, *this);
        }

        T_action m_action;
    };

} // namespace qextPrivate


/** QEXTVisitor<T_functor>::doVisitEach() performs a functor on each of the targets of a functor.
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
 *       template <typename T_action>
 *       static void doVisitEach(const T_action &action,
 *                                 const some_ns::some_functor &target)
 *       {
 *         qextVisitEach(action, target.some_data_member);
 *         qextVisitEach(action, target.some_other_functor);
 *       }
 *     };
 *   @endcode
 *
 * @ingroup qextfunctors
 */
template <typename T_functor>
struct QEXTVisitor
{
    template <typename T_action>
    static void doVisitEach(const T_action &action, const T_functor &functor)
    {
        action(functor);
    }
};


/** This function performs a functor on each of the targets of a functor.
 *
 * @ingroup qextfunctors
 */
template <typename T_action, typename T_functor>
void qextVisitEach(const T_action &action, const T_functor &functor)
{
    QEXTVisitor<T_functor>::doVisitEach(action, functor);
}

/** This function performs a functor on each of the targets
 * of a functor limited to a restricted type.
 *
 * @ingroup qextfunctors
 */
template <typename T_type, typename T_action, typename T_functor>
void qextVisitEachType(const T_action &action, const T_functor &functor)
{
    typedef qextPrivate::QEXTDerivedTargetLimitedAction<T_type, T_action> LimitedActionType;

    LimitedActionType limitedAction(action);

    //specifying the types of the template specialization prevents disconnection of bound trackable references (such as with qextReferenceWrapper()),
    //probably because the qextVisitEach<> specializations take various different template types,
    //in various sequences, and we are probably specifying only a subset of them with this.

    //But this is required by the AIX (and maybe IRIX MipsPro  and Tru64) compilers.
    //I guess that qextReferenceWrapper() therefore does not work on those platforms. murrayc
    //qextVisitEach<type_limited_action, T_functor>(limited_action, _A_functor);
    qextVisitEach(limitedAction, functor);
}



#endif // _QEXTVISITOR_H
