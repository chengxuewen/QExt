/*************************************************************************************
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
*************************************************************************************/

#ifndef _QEXTRETURNTYPEDEDUCE_H
#define _QEXTRETURNTYPEDEDUCE_H

#include <qextFunctorTrait.h>
#include <qextTypeTrait.h>



/** A hint to the compiler.
 * Functors which have all methods based on templates
 * should publicly inherit from this hint and define
 * a nested template class @p ReturnTypeDeduce that
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
 * \ingroup qextAdaptors
 */
struct QEXTAdaptorBase : public QEXTFunctorBase
{
};

/** Deduce the return type of a functor.
 * <tt>typename ReturnTypeDeduce<Functor, list of arg_types>::Type</tt>
 * deduces a functor's result type if @p Functor inherits from
 * QEXTFunctorBase and defines @p Return or if @p functor_type
 * is actually a (member) function type. Multi-type functors are not
 * supported.
 *
 * QExt adaptors use
 * <tt>typename ReturnTypeDeduce<Functor, list of arg_types>::Type</tt>
 * to determine the return type of their <tt>templated operator()</tt> overloads.
 *
 * Adaptors in turn define a nested template class @p ReturnTypeDeduce
 * that is used by template specializations of the global ReturnTypeDeduce
 * template to correctly deduce the return types of the adaptor's suitable
 * <tt>template operator()</tt> overload.
 *
 * \ingroup qextAdaptors
 */
template <
    typename T_functor,
    typename T_arg1 = void,
    typename T_arg2 = void,
    typename T_arg3 = void,
    typename T_arg4 = void,
    typename T_arg5 = void,
    typename T_arg6 = void,
    typename T_arg7 = void,
    bool I_derives_adaptor_base = QEXTIsBaseOf< QEXTAdaptorBase, T_functor >::value >
struct QEXTReturnTypeDeduce
{
    typedef typename QEXTFunctorTrait< T_functor >::Return Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTReturnTypeDeduce template
 * for 0 arguments.
 */
template < typename T_functor >
struct QEXTReturnTypeDeduce< T_functor, void, void, void, void, void, void, void, true >
{
    typedef typename T_functor::template ReturnTypeDeduce<>::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTReturnTypeDeduce template
 * for 1 arguments.
 */
template < typename T_functor, typename T_arg1 >
struct QEXTReturnTypeDeduce< T_functor, T_arg1, void, void, void, void, void, void, true >
{
    typedef typename T_functor::template ReturnTypeDeduce< T_arg1 >::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTReturnTypeDeduce template
 * for 2 arguments.
 */
template < typename T_functor, typename T_arg1, typename T_arg2 >
struct QEXTReturnTypeDeduce< T_functor, T_arg1, T_arg2, void, void, void, void, void, true >
{
    typedef typename T_functor::template ReturnTypeDeduce< T_arg1, T_arg2 >::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTReturnTypeDeduce template
 * for 3 arguments.
 */
template < typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QEXTReturnTypeDeduce< T_functor, T_arg1, T_arg2, T_arg3, void, void, void, void, true >
{
    typedef typename T_functor::template ReturnTypeDeduce< T_arg1, T_arg2, T_arg3 >::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTReturnTypeDeduce template
 * for 4 arguments.
 */
template < typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QEXTReturnTypeDeduce< T_functor, T_arg1, T_arg2, T_arg3, T_arg4, void, void, void, true >
{
    typedef typename T_functor::template ReturnTypeDeduce< T_arg1, T_arg2, T_arg3, T_arg4 >::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTReturnTypeDeduce template
 * for 5 arguments.
 */
template < typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QEXTReturnTypeDeduce< T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, void, void, true >
{
    typedef typename T_functor::template ReturnTypeDeduce< T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTReturnTypeDeduce template
 * for 6 arguments.
 */
template < typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QEXTReturnTypeDeduce< T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, void, true >
{
    typedef typename T_functor::template ReturnTypeDeduce< T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >::Type Type;
};

/** Deduce the return type of a functor.
 * This is the template specialization of the QEXTReturnTypeDeduce template
 * for 7 arguments.
 */
template < typename T_functor, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
struct QEXTReturnTypeDeduce< T_functor, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, true >
{
    typedef typename T_functor::template ReturnTypeDeduce< T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::Type Type;
};



#endif // _QEXTRETURNTYPEDEDUCE_H
