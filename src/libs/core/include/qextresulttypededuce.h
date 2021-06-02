#ifndef QEXTRETURNTYPEDEDUCE_H
#define QEXTRETURNTYPEDEDUCE_H

#include <qextfunctortrait.h>
#include <qexttypetrait.h>


/** A hint to the compiler.
 * Functors which have all methods based on templates
 * should publicly inherit from this hint and define
 * a nested template class @p ResultTypeDeduce that
 * can be used to deduce the methods' return types.
 *
 * adaptor_base inherits from the QEXTFunctorBase hint so
 * derived types should also have a result_type defined.
 *
 * Adaptors don't inherit from this type directly. They use
 * use QEXTAdaptors as a base type instead. QEXTAdaptors
 * wraps arbitrary functor types as well as function pointers
 * and class methods.
 *
 * @ingroup qextAdaptors
 */
struct QEXTAdaptorBase : public QEXTFunctorBase {};


/** Deduce the return type of a functor.
 * <tt>typename ResultTypeDeduce<FunctorType, list of arg_types>::Type</tt>
 * deduces a functor's result type if @p FunctorType inherits from
 * QEXTFunctorBase and defines @p ResultType or if @p functor_type
 * is actually a (member) function type. Multi-type functors are not
 * supported.
 *
 * QEXT adaptors use
 * <tt>typename ResultTypeDeduce<FunctorType, list of arg_types>::Type</tt>
 * to determine the return type of their <tt>templated operator()</tt> overloads.
 *
 * Adaptors in turn define a nested template class @p ResultTypeDeduce
 * that is used by template specializations of the global ResultTypeDeduce
 * template to correctly deduce the return types of the adaptor's suitable
 * <tt>template operator()</tt> overload.
 *
 * @ingroup qextAdaptors
 */
template <typename T_functor,
          typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
          typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void,
          bool I_derives_adaptor_base = QEXTBaseAndDerivedTester<QEXTAdaptorBase, T_functor>::value>
struct QEXTResultTypeDeduce
{
    typedef typename QEXTFunctorTrait<T_functor>::ResultType Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTResultTypeDeduce template
 * for 0 arguments.
 */
template <typename T_functor>
struct QEXTResultTypeDeduce<T_functor, void, void, void, void, void, void, void, true>
{
    typedef typename T_functor::template ResultTypeDeduce<>::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTResultTypeDeduce template
 * for 1 arguments.
 */
template <typename T_functor, typename T_arg1>
struct QEXTResultTypeDeduce<T_functor, T_arg1, void, void, void, void, void, void, true>
{
    typedef typename T_functor::template ResultTypeDeduce<T_arg1>::Type Type;
};


/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTResultTypeDeduce template
 * for 2 arguments.
 */
template <typename T_functor, typename T_arg1, typename T_arg2>
struct QEXTResultTypeDeduce<T_functor, T_arg1, T_arg2, void, void, void, void, void, true>
{
    typedef typename T_functor::template ResultTypeDeduce<T_arg1, T_arg2>::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTResultTypeDeduce template
 * for 3 arguments.
 */
template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTResultTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, void, void, void, void, true>
{
    typedef typename T_functor::template ResultTypeDeduce<T_arg1, T_arg2, T_arg3>::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTResultTypeDeduce template
 * for 4 arguments.
 */
template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTResultTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, void, void, void, true>
{
    typedef typename T_functor::template ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTResultTypeDeduce template
 * for 5 arguments.
 */
template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTResultTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, void, void, true>
{
    typedef typename T_functor::template ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTResultTypeDeduce template
 * for 6 arguments.
 */
template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTResultTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, void, true>
{
    typedef typename T_functor::template ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTResultTypeDeduce template
 * for 7 arguments.
 */
template <typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTResultTypeDeduce<T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, true>
{
    typedef typename T_functor::template ResultTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type Type;
};


#endif // QEXTRETURNTYPEDEDUCE_H
