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

#ifndef _QEXTLIMITREFERENCE_H
#define _QEXTLIMITREFERENCE_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>
#include <qextVisitor.h>

#include <QObject>

/** A QEXTLimitReference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QObject, then qextVisitEach<>() will "limit" itself to the
 * QObject reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from QObject then both the derived reference and the
 * QObject reference are stored, so we can later retrieve the QObject
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the QObject
 * reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QObject then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with qextMemberFunctor(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_Object = QEXTIsBaseOf<QObject, T_type>::value>
class QEXTLimitReference
{
public:
    /** Constructor.
     * \param target The reference to limit.
     */
    QEXTLimitReference(T_type &target) : m_visited(target) {}
    QEXTLimitReference(const QEXTLimitReference &other) : m_visited(other.m_visited) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     *  or QObject& if T_type derives from QObject.
     * \return The reference.
     */
    const T_type &visit() const
    {
        return m_visited;
    }
    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * \return The reference.
     */
    T_type &invoke() const
    {
        return m_visited;
    }

private:
    /** The reference.
     */
    T_type &m_visited;
};


/** QEXTLimitReference object for a class that derives from trackable.
 * - @e T_type The type of the reference.
 */
template <typename T_type>
class QEXTLimitReference<T_type, true>
{
public:
    /** Constructor.
     * \param target The reference to limit.
     */
    QEXTLimitReference(T_type &target) : m_visited(target), m_invoked(target) {}
    QEXTLimitReference(const QEXTLimitReference &other) : m_visited(other.m_visited), m_invoked(other.m_invoked) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if T_type derives from QObject.
     * \return The reference.
     */
    const QObject &visit() const
    {
        return m_visited;
    }
    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * \return The reference.
     */
    T_type &invoke() const
    {
        return m_invoked;
    }

private:
    /** The trackable reference.
     */
    QObject &m_visited;
    /** The reference.
     */
    T_type &m_invoked;
};


/** Implementation of visitor specialized for the QEXTLimitReference
 * class, to call qextVisitEach() on the entity returned by the QEXTLimitReference's
 * visit() method.
 * @tparam T_type The type of the reference.
 * @tparam T_action The type of functor to invoke.
 * \param action The functor to invoke.
 * \param target The visited instance.
 */
template <typename T_type, bool I_derives_Object>
struct QEXTVisitor<QEXTLimitReference<T_type, I_derives_Object> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action, const QEXTLimitReference<T_type, I_derives_Object> &target)
    {
        qextVisitEach(action, target.visit());
    }
};



/** A QEXTConstLimitReference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QObject, then qextVisitEach<>() will "limit" itself to the
 * QObject reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the
 * QObject reference are stored, so we can later retrieve the QObject
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the trackable
 * reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QObject then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with qextMemberFunctor(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_Object = QEXTIsBaseOf<QObject, T_type>::value>
class QEXTConstLimitReference
{
public:
    /** Constructor.
     * \param target The reference to limit.
     */
    QEXTConstLimitReference(const T_type &target) : m_visited(target) {}
    QEXTConstLimitReference(const QEXTConstLimitReference &other) : m_visited(other.m_visited) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     *  or QObject& if T_type derives from QObject.
     * \return The reference.
     */
    const T_type &visit() const
    {
        return m_visited;
    }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * \return The reference.
     */
    const T_type &invoke() const
    {
        return m_visited;
    }

private:
    /** The reference.
     */
    const T_type &m_visited;
};

/** QEXTConstLimitReference object for a class that derives from trackable.
 * - @e T_type The type of the reference.
 */
template <typename T_type>
class QEXTConstLimitReference<T_type, true>
{
public:
    /** Constructor.
     * \param target The reference to limit.
     */
    QEXTConstLimitReference(const T_type &target) : m_visited(target), m_invoked(target) {}
    QEXTConstLimitReference(const QEXTConstLimitReference &other) : m_visited(other.m_visited), m_invoked(other.m_invoked) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if T_type derives from QObject.
     * \return The reference.
     */
    const QObject &visit() const
    {
        return m_visited;
    }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * \return The reference.
     */
    const T_type &invoke() const
    {
        return m_invoked;
    }

private:
    /** The trackable reference.
     */
    const QObject &m_visited;
    /** The reference.
     */
    const T_type &m_invoked;
};

/** Implementation of visitor specialized for the QEXTConstLimitReference
 * class, to call qextVisitEach() on the entity returned by the QEXTConstLimitReference's
 * visit() method.
 * @tparam T_type The type of the reference.
 * @tparam T_action The type of functor to invoke.
 * \param action The functor to invoke.
 * \param target The visited instance.
 */
template <typename T_type, bool I_derives_Object>
struct QEXTVisitor<QEXTConstLimitReference<T_type, I_derives_Object> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTConstLimitReference<T_type, I_derives_Object> &target)
    {
        qextVisitEach(action, target.visit());
    }
};



/** A QEXTVolatileLimitReference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QObject, then qextVisitEach<>() will "limit" itself to the
 * QObject reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the
 * QObject reference are stored, so we can later retrieve the QObject
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the trackable
 * reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QObject then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with qextMemberFunctor(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_Object = QEXTIsBaseOf<QObject, T_type>::value>
class QEXTVolatileLimitReference
{
public:
    /** Constructor.
     * \param target The reference to limit.
     */
    QEXTVolatileLimitReference(T_type &target) : m_visited(target) {}
    QEXTVolatileLimitReference(const QEXTVolatileLimitReference &other) : m_visited(other.m_visited) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     *  or QObject& if T_type derives from QObject.
     * \return The reference.
     */
    const T_type &visit() const
    {
        return m_visited;
    }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * \return The reference.
     */
    volatile T_type &invoke() const
    {
        return m_visited;
    }

private:
    /** The reference.
     */
    T_type &m_visited;
};


/** QEXTVolatileLimitReference object for a class that derives from trackable.
 * - @e T_type The type of the reference.
 */
template <typename T_type>
class QEXTVolatileLimitReference<T_type, true>
{
public:
    /** Constructor.
     * \param target The reference to limit.
     */
    QEXTVolatileLimitReference(T_type &target) : m_visited(target), m_invoked(target) {}
    QEXTVolatileLimitReference(const QEXTVolatileLimitReference &other) : m_visited(other.m_visited), m_invoked(other.m_invoked) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     *  or QObject& if T_type derives from QObject.
     * \return The reference.
     */
    const QObject &visit() const
    {
        return m_visited;
    }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * \return The reference.
     */
    volatile T_type &invoke() const
    {
        return m_invoked;
    }

private:
    /** The trackable reference.
     */
    QObject &m_visited;
    /** The reference.
     */
    T_type &m_invoked;
};

/** Implementation of visitor specialized for the QEXTVolatileLimitReference
 * class, to call qextVisitEach() on the entity returned by the QEXTVolatileLimitReference's
 * visit() method.
 * @tparam T_type The type of the reference.
 * @tparam T_action The type of functor to invoke.
 * \param action The functor to invoke.
 * \param target The visited instance.
 */
template <typename T_type, bool I_derives_Object>
struct QEXTVisitor<QEXTVolatileLimitReference<T_type, I_derives_Object> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTVolatileLimitReference<T_type, I_derives_Object> &target)
    {
        qextVisitEach(action, target.visit());
    }
};



/** A QEXTConstVolatileLimitReference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QObject, then qextVisitEach<>() will "limit" itself to the
 * QObject reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the
 * QObject reference are stored, so we can later retrieve the QObject
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the trackable
 * reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QObject then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with qextMemberFunctor(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_Object = QEXTIsBaseOf<QObject, T_type>::value>
class QEXTConstVolatileLimitReference
{
public:
    /** Constructor.
     * \param target The reference to limit.
     */
    QEXTConstVolatileLimitReference(const T_type &target) : m_visited(target) {}
    QEXTConstVolatileLimitReference(const QEXTConstVolatileLimitReference &other) : m_visited(other.m_visited) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if T_type derives from QObject.
     * \return The reference.
     */
    const T_type &visit() const
    {
        return m_visited;
    }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * \return The reference.
     */
    const volatile T_type &invoke() const
    {
        return m_visited;
    }

private:
    /** The reference.
     */
    const T_type &m_visited;
};

/** QEXTConstVolatileLimitReference object for a class that derives from trackable.
 * - @e T_type The type of the reference.
 */
template <typename T_type>
class QEXTConstVolatileLimitReference<T_type, true>
{
public:
    /** Constructor.
     * \param target The reference to limit.
     */
    QEXTConstVolatileLimitReference(const T_type &target) : m_visited(target), m_invoked(target) {}
    QEXTConstVolatileLimitReference(const QEXTConstVolatileLimitReference &other) : m_visited(other.m_visited), m_invoked(other.m_invoked) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QObject& if T_type derives from QObject.
     * \return The reference.
     */
    const QObject &visit() const
    {
        return m_visited;
    }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * \return The reference.
     */
    const volatile T_type &invoke() const
    {
        return m_invoked;
    }

private:
    /** The trackable reference.
     */
    const QObject &m_visited;
    /** The reference.
     */
    const T_type &m_invoked;
};

/** Implementation of visitor specialized for the QEXTConstVolatileLimitReference
 * class, to call qextVisitEach() on the entity returned by the QEXTConstVolatileLimitReference's
 * visit() method.
 * @tparam T_type The type of the reference.
 * @tparam T_action The type of functor to invoke.
 * \param action The functor to invoke.
 * \param target The visited instance.
 */
template <typename T_type, bool I_derives_Object>
struct QEXTVisitor<QEXTConstVolatileLimitReference<T_type, I_derives_Object> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTConstVolatileLimitReference<T_type, I_derives_Object> &target)
    {
        qextVisitEach(action, target.visit());
    }
};



#endif // _QEXTLIMITREFERENCE_H
