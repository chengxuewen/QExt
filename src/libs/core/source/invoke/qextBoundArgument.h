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

#ifndef _QEXTBOUNDARGUMENT_H
#define _QEXTBOUNDARGUMENT_H

#include <qextLimitReference.h>
#include <qextReferenceWrapper.h>

/** A QExtBoundArgument<Foo> object stores a bound (for instance, with qextBindFunctor(), or qextBindReturnFunctor()) argument.
 *
 * If Foo is a wrapped reference to a class Bar (QExtReferenceWrapper<Bar>) then this
 * object is implemented on top of a limit_reference. When the slot is
 * invoked, the QExtLimitReference::invoke() method provides the argument (a Bar&).
 * When the slot is visited (e.g. qextVisitEach<>()), we simply visit the QExtLimitReference,
 * which will visit the derived type, or a QObject base if necessary.
 *
 * Likewise, If Foo is a wrapped const reference to a class Bar (QExtConstReferenceWrapper<Bar>)
 * then this object is implemented on top of a QExtConstLimitReference.
 *
 * If Foo is something else (such as an argument that is bound by value) QExtBoundArgument just
 * stores a cop of that value, and both invoke() and visit() simply return it.
 *
 * This object is used by the qextBindFunctor<> and qextBindReturnFunctor<> objects,
 * depending on whether the argument is bound as a parameter or as a return value.
 *
 * The general template implementation is used for parameters that are passed by value.
 * @e T_type The type of the bound argument.
 */
template<typename T_type>
class QExtBoundArgument
{
public:
    /** Constructor.
     * \param argument The argument to bind.
     */
    QExtBoundArgument(const T_type &argument) : m_visited(argument) {}

    QExtBoundArgument(const QExtBoundArgument &other) : m_visited(other.m_visited) {}

    QExtBoundArgument &operator=(const QExtBoundArgument &other)
    {
        if (this != &other)
        {
            m_visited = other.m_visited;
        }
        return *this;
    }

    bool operator==(const QExtBoundArgument &other) const
    {
        return m_visited == other.m_visited;
    }

    /** Retrieve the entity to visit in qextVisitEach().
     * \return The bound argument.
     */
    const T_type &visit() const
    {
        return m_visited;
    }

    /** Retrieve the entity to pass to the bound functor or return.
     * \return The bound argument.
     */
    T_type &invoke()
    {
        return m_visited;
    }

private:
    /** The value of the argument.
     */
    T_type m_visited;
};


//Template specialization:
/** QExtBoundArgument object for a bound argument that is passed by qextBindFunctor() or
 * returned by qextBindReturnFunctor() by reference, specialized for QExtReferenceWrapper<> types.
 * @e T_wrapped The type of the bound argument.
 */
template<typename T_wrapped>
class QExtBoundArgument<QExtReferenceWrapper<T_wrapped> >
{
public:
    /** Constructor.
     * \param argument The argument to bind.
     */
    QExtBoundArgument(const QExtReferenceWrapper<T_wrapped> &argument) : m_visited(qextUnwrapReference(argument)) {}

    /** Retrieve the entity to visit in qextVisitEach().
     * \return The QExtLimitReference to the bound argument.
     */
    const QExtLimitReference<T_wrapped> &visit() const
    {
        return m_visited;
    }

    /** Retrieve the entity to pass to the bound functor or return.
     * \return The bound argument.
     */
    T_wrapped &invoke()
    {
        return m_visited.invoke();
    }

private:
    /** The QExtLimitReference to the bound argument.
     */
    QExtLimitReference<T_wrapped> m_visited;
};

/** bound_argument object for a bound argument that is passed by qextBindFunctor() or
 * returned by qextBindReturnFunctor() by const reference, specialized for const QExtReferenceWrapper<> types.
 * - @e T_wrapped The type of the bound argument.
 */
template<typename T_wrapped>
class QExtBoundArgument<QExtConstReferenceWrapper<T_wrapped> >
{
public:
    /** Constructor.
     * \param argument The argument to bind.
     */
    QExtBoundArgument(const QExtConstReferenceWrapper<T_wrapped> &argument) : m_visited(
            qextUnwrapReference(argument)) {}

    QExtBoundArgument(const QExtBoundArgument &other) : m_visited(other.m_visited) {}

    QExtBoundArgument &operator=(const QExtBoundArgument &other)
    {
        if (this != &other)
        {
            m_visited = other.m_visited;
        }
        return *this;
    }

    bool operator==(const QExtBoundArgument &other) const
    {
        return m_visited == other.m_visited;
    }

    /** Retrieve the entity to visit in qextVisitEach().
     * \return The QExtConstLimitReference to the bound argument.
     */
    const QExtConstLimitReference<T_wrapped> &visit() const
    {
        return m_visited;
    }

    /** Retrieve the entity to pass to the bound functor or return.
     * \return The bound argument.
     */
    const T_wrapped &invoke()
    {
        return m_visited.invoke();
    }

private:
    /** The QExtConstLimitReference to the bound argument.
     */
    QExtConstLimitReference<T_wrapped> m_visited;
};

/** Implementation of QExtVisitor<>::doVisitEach<>() specialized for the bound_argument class.
 * Call qextVisitEach() on the entity returned by the QExtBoundArgument's visit()
 * method.
 * @tparam T_type The type of bound_argument.
 * @tparam T_action The type of functor to invoke.
 * \param action The functor to invoke.
 * \param argument The visited instance.
 */
template<typename T_type>
struct QExtVisitor<QExtBoundArgument<T_type> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtBoundArgument<T_type> &argument)
    {
        qextVisitEach(action, argument.visit());
    }
};


#endif // _QEXTBOUNDARGUMENT_H
