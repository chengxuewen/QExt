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

/**
 * @brief A QExtBoundArgument<Foo> object stores a bound (for instance, with qextBindFunctor(),
 * or qextBindReturnFunctor()) argument.
 *
 * If Foo is a wrapped reference to a class Bar (QExtReferenceWrapper<Bar>) then this object is implemented on top of
 * a limit_reference. When the slot is invoked, the QExtLimitReference::invoke() method provides the argument (a Bar&).
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
 * @tparam T The type of the bound argument.
 */
template<class T>
class QExtBoundArgument
{
public:
    /**
     * @brief Constructor.
     * @param argument The argument to bind.
     */
    QExtBoundArgument(const T &argument) : mVisited(argument) {}

    QExtBoundArgument(const QExtBoundArgument &other) : mVisited(other.mVisited) {}

    QExtBoundArgument &operator=(const QExtBoundArgument &other)
    {
        if (this != &other)
        {
            mVisited = other.mVisited;
        }
        return *this;
    }

    bool operator==(const QExtBoundArgument &other) const
    {
        return mVisited == other.mVisited;
    }

    /**
     * @brief Retrieve the entity to visit in qextVisitEach().
     * @return The bound argument.
     */
    const T &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the entity to pass to the bound functor or return.
     * @return The bound argument.
     */
    T &invoke()
    {
        return mVisited;
    }

private:
    T mVisited; // The value of the argument.
};

/**
 * @brief QExtBoundArgument object for a bound argument that is passed by qextBindFunctor() or
 * returned by qextBindReturnFunctor() by reference, specialized for QExtReferenceWrapper<> types.
 * @tparam Wrapped The type of the bound argument.
 */
template<class Wrapped>
class QExtBoundArgument<QExtReferenceWrapper<Wrapped> >
{
public:
    /**
     * @brief Constructor.
     * @param argument The argument to bind.
     */
    QExtBoundArgument(const QExtReferenceWrapper<Wrapped> &argument) : mVisited(qextUnwrapReference(argument)) {}

    /**
     * @brief Retrieve the entity to visit in qextVisitEach().
     * @return The QExtLimitReference to the bound argument.
     */
    const QExtLimitReference<Wrapped> &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the entity to pass to the bound functor or return.
     * @return The bound argument.
     */
    Wrapped &invoke()
    {
        return mVisited.invoke();
    }

private:
    QExtLimitReference<Wrapped> mVisited; // The QExtLimitReference to the bound argument.
};

/**
 * @brief bound_argument object for a bound argument that is passed by qextBindFunctor() or
 * returned by qextBindReturnFunctor() by const reference, specialized for const QExtReferenceWrapper<> types.
 * @tparam Wrapped The type of the bound argument.
 */
template<class Wrapped>
class QExtBoundArgument<QExtConstReferenceWrapper<Wrapped> >
{
public:
    /**
     * @brief Constructor.
     * @param argument The argument to bind.
     */
    QExtBoundArgument(const QExtConstReferenceWrapper<Wrapped> &argument) : mVisited(qextUnwrapReference(argument)) {}

    QExtBoundArgument(const QExtBoundArgument &other) : mVisited(other.mVisited) {}

    QExtBoundArgument &operator=(const QExtBoundArgument &other)
    {
        if (this != &other)
        {
            mVisited = other.mVisited;
        }
        return *this;
    }

    bool operator==(const QExtBoundArgument &other) const
    {
        return mVisited == other.mVisited;
    }

    /**
     * @brief Retrieve the entity to visit in qextVisitEach().
     * @return The QExtConstLimitReference to the bound argument.
     */
    const QExtConstLimitReference<Wrapped> &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the entity to pass to the bound functor or return.
     * @return The bound argument.
     */
    const Wrapped &invoke()
    {
        return mVisited.invoke();
    }

private:
    QExtConstLimitReference<Wrapped> mVisited; // The QExtConstLimitReference to the bound argument.
};

/**
 * @brief Implementation of QExtVisitor<>::doVisitEach<>() specialized for the bound_argument class.
 * Call qextVisitEach() on the entity returned by the QExtBoundArgument's visit() method.
 * @tparam T The type of bound_argument.
 * @tparam Action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param argument The visited instance.
 */
template<class T>
struct QExtVisitor<QExtBoundArgument<T> >
{
    template<typename Action>
    static void doVisitEach(const Action &action, const QExtBoundArgument<T> &argument)
    {
        qextVisitEach(action, argument.visit());
    }
};

#endif // _QEXTBOUNDARGUMENT_H
