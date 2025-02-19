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

#ifndef _QEXTRETURNTYPEDEDUCE_H
#define _QEXTRETURNTYPEDEDUCE_H

#include <qextFunctorTrait.h>
#include <qextTypeTrait.h>


/**
 * @brief A hint to the compiler.
 * Functors which have all methods based on templates should publicly inherit from this hint and define a nested
 * template class @p ReturnTypeDeduce that can be used to deduce the methods' return types.
 *
 * QExtAdaptorBase inherits from the QExtFunctorBase hint so erived types should also have a result_type defined.
 *
 * Adaptors don't inherit from this type directly.
 * They use use QExtAdaptors as a base type instead.
 * QExtAdaptors wraps arbitrary functor types as well as function pointers and class methods.
 */
struct QExtAdaptorBase : public QExtFunctorBase { };

/**
 * @brief Deduce the return type of a functor.
 * <tt>typename ReturnTypeDeduce<Functor, list of arg_types>::Type</tt>
 * deduces a functor's result type if @p Functor inherits from QExtFunctorBase and defines @p ResultType or
 * if @p functor_type is actually a (member) function type. Multi-type functors are not supported.
 *
 * QExt adaptors use
 * <tt>typename ReturnTypeDeduce<Functor, list of arg_types>::Type</tt>
 * to determine the return type of their <tt>templated operator()</tt> overloads.
 *
 * Adaptors in turn define a nested template class @p ReturnTypeDeduce that is used by template specializations of
 * the global ReturnTypeDeduce template to correctly deduce the return types of the adaptor's suitable
 * <tt>template operator()</tt> overload.
 */
template<class Functor,
         class Arg1 = void,
         class Arg2 = void,
         class Arg3 = void,
         class Arg4 = void,
         class Arg5 = void,
         class Arg6 = void,
         class Arg7 = void,
         bool I_derives_adaptor_base = QExtIsBaseOf<QExtAdaptorBase, Functor>::value>
struct QExtReturnTypeDeduce
{
    typedef typename QExtFunctorTrait<Functor>::ResultType Type;
};

/**
 * @brief Deduce the return type of a functor.
 * This is the template specialization of the QExtReturnTypeDeduce template for 0 arguments.
 */
template<class Functor>
struct QExtReturnTypeDeduce<Functor, void, void, void, void, void, void, void, true>
{
    typedef class Functor::template ReturnTypeDeduce<>::Type Type;
};

/**
 * @brief Deduce the return type of a functor.
 * This is the template specialization of the QExtReturnTypeDeduce template for 1 arguments.
 */
template<class Functor, class Arg1>
struct QExtReturnTypeDeduce<Functor, Arg1, void, void, void, void, void, void, true>
{
    typedef class Functor::template ReturnTypeDeduce<Arg1>::Type Type;
};

/**
 * @brief Deduce the return type of a functor.
 * This is the template specialization of the QExtReturnTypeDeduce template for 2 arguments.
 */
template<class Functor, class Arg1, class Arg2>
struct QExtReturnTypeDeduce<Functor, Arg1, Arg2, void, void, void, void, void, true>
{
    typedef class Functor::template ReturnTypeDeduce<Arg1, Arg2>::Type Type;
};

/**
 * @brief Deduce the return type of a functor.
 * This is the template specialization of the QExtReturnTypeDeduce template for 3 arguments.
 */
template<class Functor, class Arg1, class Arg2, class Arg3>
struct QExtReturnTypeDeduce<Functor, Arg1, Arg2, Arg3, void, void, void, void, true>
{
    typedef class Functor::template ReturnTypeDeduce<Arg1, Arg2, Arg3>::Type Type;
};

/**
 * @brief Deduce the return type of a functor.
 * This is the template specialization of the QExtReturnTypeDeduce template for 4 arguments.
 */
template<class Functor, class Arg1, class Arg2, class Arg3, class Arg4>
struct QExtReturnTypeDeduce<Functor, Arg1, Arg2, Arg3, Arg4, void, void, void, true>
{
    typedef class Functor::template ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4>::Type Type;
};

/**
 * @brief Deduce the return type of a functor.
 * This is the template specialization of the QExtReturnTypeDeduce template for 5 arguments.
 */
template<class Functor, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
struct QExtReturnTypeDeduce<Functor, Arg1, Arg2, Arg3, Arg4, Arg5, void, void, true>
{
    typedef class Functor::template ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5>::Type Type;
};

/**
 * @brief Deduce the return type of a functor.
 * This is the template specialization of the QExtReturnTypeDeduce template for 6 arguments.
 */
template<class Functor, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6>
struct QExtReturnTypeDeduce<Functor, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, void, true>
{
    typedef class Functor::template ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6>::Type Type;
};

/**
 * @brief Deduce the return type of a functor.
 * This is the template specialization of the QExtReturnTypeDeduce template for 7 arguments.
 */
template<class Functor, class Arg1, class Arg2, class Arg3, class Arg4, class Arg5, class Arg6, class Arg7>
struct QExtReturnTypeDeduce<Functor, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, true>
{
    typedef class Functor::template ReturnTypeDeduce<Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7>::Type Type;
};


#endif // _QEXTRETURNTYPEDEDUCE_H
