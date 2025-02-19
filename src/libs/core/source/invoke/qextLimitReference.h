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

#ifndef _QEXTLIMITREFERENCE_H
#define _QEXTLIMITREFERENCE_H

#include <qextGlobal.h>
#include <qextVisitor.h>
#include <qextTypeTrait.h>

#include <QObject>

/**
 * @brief A QExtLimitReference<Foo> object stores a reference (Foo&), but make sure that, if Foo inherits from
 * QObject, then qextVisitEach<>() will "limit" itself to the QObject reference instead of the derived reference.
 * This avoids use of a reference to the derived type when the derived destructor has run.
 * That can be a problem when using virtual inheritance.
 *
 * If Foo inherits from QObject then both the derived reference and the QObject reference are stored, so we can later
 * retrieve the QObject reference without doing an implicit conversion.
 * To retrieve the derived reference (so that you invoke methods or members of it), use invoke().
 * To retrieve the QObject reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QObject then invoke() and visit() just return the derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QExtBoundArgument), bound return values, and, with
 * qextMakeFunctor(), the reference to the handling object.
 *
 * @tparam Type The type of the reference.
 */
template <class Type, bool I_derives_Object = QExtIsBaseOf<QObject, Type>::value>
class QExtLimitReference
{
public:
    /**
     * @brief Constructor.
     * @param target The reference to limit.
     */
    QExtLimitReference(Type &target) : mVisited(target) {}
    QExtLimitReference(const QExtLimitReference &other) : mVisited(other.mVisited) {}

    /**
     * @brief Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if Type derives from QObject.
     * @return The reference.
     */
    const Type &visit() const
    {
        return mVisited;
    }
    /**
     * @brief Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    Type &invoke() const
    {
        return mVisited;
    }

private:
    Type &mVisited; // The reference.
};

/**
 * @brief QExtLimitReference object for a class that derives from trackable.
 * @tparam Type The type of the reference.
 */
template <class Type>
class QExtLimitReference<Type, true>
{
public:
    /**
     * @brief Constructor.
     * @param target The reference to limit.
     */
    QExtLimitReference(Type &target) : mVisited(target), mInvoked(target) {}
    QExtLimitReference(const QExtLimitReference &other) : mVisited(other.mVisited), mInvoked(other.mInvoked) {}

    /**
     * @brief Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if Type derives from QObject.
     * @return The reference.
     */
    const QObject &visit() const
    {
        return mVisited;
    }
    /**
     * @brief Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    Type &invoke() const
    {
        return mInvoked;
    }

private:
    QObject &mVisited; // The trackable reference.
    Type &mInvoked; // The reference.
};

/**
 * @brief Implementation of visitor specialized for the QExtLimitReference class, to call qextVisitEach() on the entity
 * returned by the QExtLimitReference's visit() method.
 * @tparam Type The type of the reference.
 * @tparam Action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param target The visited instance.
 */
template <class Type, bool I_derives_Object>
struct QExtVisitor<QExtLimitReference<Type, I_derives_Object> >
{
    typedef QExtLimitReference<Type, I_derives_Object> TargetType;
    template <class Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.visit());
    }
};

/**
 * @brief A QExtConstLimitReference<Foo> object stores a reference (Foo&), but make sure that, if Foo inherits from
 * QObject, then qextVisitEach<>() will "limit" itself to the QObject reference instead of the derived reference.
 * This avoids use of a reference to the derived type when the derived destructor has run.
 * That can be a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the QObject reference are stored, so we can later
 * retrieve the QObject reference without doing an implicit conversion.
 * To retrieve the derived reference (so that you invoke methods or members of it), use invoke().
 * To retrieve the trackable reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QObject then invoke() and visit() just return the derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QExtBoundArgument), bound return values, and, with
 * qextMakeFunctor(), the reference to the handling object.
 *
 * @tparam Type The type of the reference.
 */
template <class Type, bool I_derives_Object = QExtIsBaseOf<QObject, Type>::value>
class QExtConstLimitReference
{
public:
    /**
     * @brief Constructor.
     * @param target The reference to limit.
     */
    QExtConstLimitReference(const Type &target) : mVisited(target) {}
    QExtConstLimitReference(const QExtConstLimitReference &other) : mVisited(other.mVisited) {}

    /**
     * @brief Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if Type derives from QObject.
     * @return The reference.
     */
    const Type &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    const Type &invoke() const
    {
        return mVisited;
    }

private:
    const Type &mVisited; // The reference.
};

/**
 * @brief QExtConstLimitReference object for a class that derives from trackable.
 * @tparam Type The type of the reference.
 */
template <class Type>
class QExtConstLimitReference<Type, true>
{
public:
    /**
     * @brief Constructor.
     * @param target The reference to limit.
     */
    QExtConstLimitReference(const Type &target) : mVisited(target), mInvoked(target) {}
    QExtConstLimitReference(const QExtConstLimitReference &other) : mVisited(other.mVisited), mInvoked(other.mInvoked) {}

    /**
     * @brief Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if Type derives from QObject.
     * @return The reference.
     */
    const QObject &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    const Type &invoke() const
    {
        return mInvoked;
    }

private:
    const QObject &mVisited; // The trackable reference.
    const Type &mInvoked; // The reference.
};

/**
 * @brief Implementation of visitor specialized for the QExtConstLimitReference class, to call qextVisitEach() on the
 * entity returned by the QExtConstLimitReference's visit() method.
 * @tparam Type The type of the reference.
 * @tparam Action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param target The visited instance.
 */
template <class Type, bool I_derives_Object>
struct QExtVisitor<QExtConstLimitReference<Type, I_derives_Object> >
{
    typedef QExtConstLimitReference<Type, I_derives_Object> TargetType;
    template <class Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.visit());
    }
};

/**
 * @brief A QExtVolatileLimitReference<Foo> object stores a reference (Foo&), but make sure that, if Foo inherits from
 * QObject, then qextVisitEach<>() will "limit" itself to the QObject reference instead of the derived reference.
 * This avoids use of a reference to the derived type when the derived destructor has run.
 * That can be a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the QObject reference are stored, so we can later
 * retrieve the QObject reference without doing an implicit conversion.
 * To retrieve the derived reference (so that you invoke methods or members of it), use invoke().
 * To retrieve the trackable reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QObject then invoke() and visit() just return the derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QExtBoundArgument), bound return values, and, with
 * qextMakeFunctor(), the reference to the handling object.
 *
 * @tparam Type The type of the reference.
 */
template <class Type, bool I_derives_Object = QExtIsBaseOf<QObject, Type>::value>
class QExtVolatileLimitReference
{
public:
    /**
     * @brief Constructor.
     * @param target The reference to limit.
     */
    QExtVolatileLimitReference(Type &target) : mVisited(target) {}
    QExtVolatileLimitReference(const QExtVolatileLimitReference &other) : mVisited(other.mVisited) {}

    /**
     * @brief Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if Type derives from QObject.
     * @return The reference.
     */
    const Type &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    volatile Type &invoke() const
    {
        return mVisited;
    }

private:
    Type &mVisited; // The reference.
};


/**
 * @brief QExtVolatileLimitReference object for a class that derives from trackable.
 * @tparam Type The type of the reference.
 */
template <class Type>
class QExtVolatileLimitReference<Type, true>
{
public:
    /**
     * @brief Constructor.
     * @param target The reference to limit.
     */
    QExtVolatileLimitReference(Type &target) : mVisited(target), mInvoked(target) {}

    QExtVolatileLimitReference(const QExtVolatileLimitReference &other)
        : mVisited(other.mVisited), mInvoked(other.mInvoked) {}

    /**
     * @brief Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if Type derives from QObject.
     * @return The reference.
     */
    const QObject &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    volatile Type &invoke() const
    {
        return mInvoked;
    }

private:
    QObject &mVisited; // The trackable reference.
    Type &mInvoked; // The reference.
};

/**
 * @brief Implementation of visitor specialized for the QExtVolatileLimitReference class, to call qextVisitEach() on
 * the entity returned by the QExtVolatileLimitReference's visit() method.
 * @tparam Type The type of the reference.
 * @tparam Action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param target The visited instance.
 */
template <class Type, bool I_derives_Object>
struct QExtVisitor<QExtVolatileLimitReference<Type, I_derives_Object> >
{
    typedef QExtVolatileLimitReference<Type, I_derives_Object> TargetType;
    template <class Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.visit());
    }
};

/**
 * @brief A QExtConstVolatileLimitReference<Foo> object stores a reference (Foo&), but make sure that, if Foo inherits
 * from QObject, then qextVisitEach<>() will "limit" itself to the QObject reference instead of the derived reference.
 * This avoids use of a reference to the derived type when the derived destructor has run.
 * That can be a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the QObject reference are stored, so we can
 * later retrieve the QObject reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke().
 * To retrieve the trackable reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QObject then invoke() and visit() just return the derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QExtBoundArgument), bound return values, and,
 * with qextMakeFunctor(), the reference to the handling object.
 *
 * @tparam Type The type of the reference.
 */
template <typename Type, bool I_derives_Object = QExtIsBaseOf<QObject, Type>::value>
class QExtConstVolatileLimitReference
{
public:
    /**
     * @brief Constructor.
     * @param target The reference to limit.
     */
    QExtConstVolatileLimitReference(const Type &target) : mVisited(target) {}
    QExtConstVolatileLimitReference(const QExtConstVolatileLimitReference &other) : mVisited(other.mVisited) {}

    /**
     * @brief Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if Type derives from QObject.
     * @return The reference.
     */
    const Type &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    const volatile Type &invoke() const
    {
        return mVisited;
    }

private:
    const Type &mVisited; // The reference.
};

/**
 * @brief QExtConstVolatileLimitReference object for a class that derives from trackable.
 * @tparam Type The type of the reference.
 */
template <class Type>
class QExtConstVolatileLimitReference<Type, true>
{
public:
    /**
     * @brief Constructor.
     * @param target The reference to limit.
     */
    QExtConstVolatileLimitReference(const Type &target) : mVisited(target), mInvoked(target) {}
    QExtConstVolatileLimitReference(const QExtConstVolatileLimitReference &other) : mVisited(other.mVisited), mInvoked(other.mInvoked) {}

    /**
     * @brief Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if Type derives from QObject.
     * @return The reference.
     */
    const QObject &visit() const
    {
        return mVisited;
    }

    /**
     * @brief Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    const volatile Type &invoke() const
    {
        return mInvoked;
    }

private:
    const QObject &mVisited; // The trackable reference.
    const Type &mInvoked; // The reference.
};

/**
 * @brief Implementation of visitor specialized for the QExtConstVolatileLimitReference class,
 * to call qextVisitEach() on the entity returned by the QExtConstVolatileLimitReference's visit() method.
 * @tparam Type The type of the reference.
 * @tparam Action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param target The visited instance.
 */
template <class Type, bool I_derives_Object>
struct QExtVisitor<QExtConstVolatileLimitReference<Type, I_derives_Object> >
{
    typedef QExtConstVolatileLimitReference<Type, I_derives_Object> TargetType;
    template <class Action>
    static void doVisitEach(const Action &action, const TargetType &target)
    {
        qextVisitEach(action, target.visit());
    }
};

#endif // _QEXTLIMITREFERENCE_H
