/****************************************************************************************************************************
**
** Library: QExt
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
****************************************************************************************************************************/

#ifndef _QEXTVISITOR_H
#define _QEXTVISITOR_H

#include <qextTypeTrait.h>

namespace detail
{
/**
 * @brief This should really be an inner class of limit_derived_target, without the Limit template type。
 * But the SUN CC 5.7 (not earlier versions) compiler finds it ambiguous when we specify a particular
 * specialization of it.
 * And does not seem to allow us to tell it explicitly that it's an inner class.
 */
template<bool I_derived, class Type, class Limit>
struct QExtWithType;

/**
 * @brief Specialization for I_derived = false
 */
template<class Type, class Limit>
struct QExtWithType<false, Type, Limit>
{
    static void execute(const Type &, const Limit &) {}
};

/**
 * @brief Specialization for I_derived = true
 */
template<class Type, class Limit>
struct QExtWithType<true, Type, Limit>
{
    static void execute(const Type &type, const Limit &action)
    {
        action.mAction(type);
    }
};

/**
 * @brief Helper struct for qextVisitEachType().
 */
template<class Target, class Action>
struct QExtDerivedTargetLimitedAction
{
    typedef QExtDerivedTargetLimitedAction<Target, Action> SelfType;

    QExtDerivedTargetLimitedAction(const Action &action) : mAction(action) {}

    template<class Type>
    void operator()(const Type &type) const
    {
        QExtWithType<QExtIsBaseOf<Target, Type>::value, Type, SelfType>::execute(type, *this);
    }

    Action mAction;
};

/**
 * @brief Specialization for Type pointer types, to provide a slightly different execute() implementation.
 */
template<bool I_derived, class Type, class Limit>
struct QExtWithTypePointer;

/**
 * @brief Specialization for I_derived = false
 */
template<class Type, class Limit>
struct QExtWithTypePointer<false, Type, Limit>
{
    static void execute(const Type &, const Limit &) {}
};

/**
 * @brief Specialization for I_derived = true
 */
template<class Type, class Limit>
struct QExtWithTypePointer<true, Type, Limit>
{
    static void execute(const Type &type, const Limit &action)
    {
        action.mAction(&type);
    }
};

template<class Type, class Action>
struct QExtDerivedTargetLimitedAction<Type *, Action>
{
    typedef QExtDerivedTargetLimitedAction<Type *, Action> SelfType;

    QExtDerivedTargetLimitedAction(const Action &action) : mAction(action) {}

    template<class Target>
    void operator()(const Target &target) const
    {
        QExtWithTypePointer<QExtIsBaseOf<Type, Target>::value, Target, SelfType>::execute(target, *this);
    }

    Action mAction;
};

} // namespace detail


/**
 * @brief QExtVisitor<Functor>::doVisitEach() performs a functor on each of the targets of a functor.
 * All unknown types just call @a action on them.
 * Add specializations that specialize the @a Functor argument for your own functor types,
 * so that subobjects get visited.
 * This is needed to enable auto-disconnection support for your functor types.
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
 *     struct QExtVisitor<some_ns::some_functor>
 *     {
 *       template <class Action>
 *       static void doVisitEach(const Action &action,
 *                                 const some_ns::some_functor &target)
 *       {
 *         qextVisitEach(action, target.some_data_member);
 *         qextVisitEach(action, target.some_other_functor);
 *       }
 *     };
 *   @endcode
 */
template<class Functor>
struct QExtVisitor
{
    template<class Action>
    static void doVisitEach(const Action &action, const Functor &functor)
    {
        action(functor);
    }
};

/**
 * @brief This function performs a functor on each of the targets of a functor.
 */
template<class Action, class Functor>
void qextVisitEach(const Action &action, const Functor &functor)
{
    QExtVisitor<Functor>::doVisitEach(action, functor);
}

/**
 * @brief This function performs a functor on each of the targets of a functor limited to a restricted type.
 */
template<class Type, class Action, class Functor>
void qextVisitEachType(const Action &action, const Functor &functor)
{
    typedef detail::QExtDerivedTargetLimitedAction<Type, Action> LimitedActionType;

    LimitedActionType limitedAction(action);

    /**
     * @brief specifying the types of the template specialization prevents disconnection of bound trackable references
     * (such as with qextReferenceWrapper()), probably because the qextVisitEach<> specializations take various
     * different template types, in various sequences, and we are probably specifying only a subset of them with this.
     *
     * But this is required by the AIX (and maybe IRIX MipsPro  and Tru64) compilers.
     * I guess that qextReferenceWrapper() therefore does not work on those platforms. murrayc
     * qextVisitEach<type_limited_action, Functor>(limited_action, _A_functor);
     */
    qextVisitEach(limitedAction, functor);
}

#endif // _QEXTVISITOR_H
