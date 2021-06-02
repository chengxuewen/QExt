#ifndef QEXTLIMITREFERENCE_H
#define QEXTLIMITREFERENCE_H

#include <qexttrackable.h>
#include <qexttypetrait.h>
#include <qextvisitor.h>

/** A QEXTLimitReference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QEXTTrackable, then qextVisitEach<>() will "limit" itself to the
 * QEXTTrackable reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from QEXTTrackable then both the derived reference and the
 * QEXTTrackable reference are stored, so we can later retrieve the QEXTTrackable
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the QEXTTrackable
 * reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QEXTTrackable then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with qextMemberFunctor(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_trackable = QEXTBaseAndDerivedTester<QEXTTrackable, T_type>::value>
class QEXTLimitReference
{
public:
    /** Constructor.
     * @param target The reference to limit.
     */
    QEXTLimitReference(T_type &target) : m_visited(target) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     *  or QEXTTrackable& if T_type derives from QEXTTrackable.
     * @return The reference.
     */
    const T_type &visit() const { return m_visited; }
    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    T_type &invoke() const { return m_visited; }

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
     * @param target The reference to limit.
     */
    QEXTLimitReference(T_type &target) : m_visited(target), m_invoked(target) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QEXTTrackable& if T_type derives from QEXTTrackable.
     * @return The reference.
     */
    const QEXTTrackable &visit() const { return m_visited; }
    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    T_type &invoke() const { return m_invoked; }

private:
    /** The trackable reference.
     */
    QEXTTrackable &m_visited;
    /** The reference.
     */
    T_type &m_invoked;
};


/** Implementation of visitor specialized for the QEXTLimitReference
 * class, to call qextVisitEach() on the entity returned by the QEXTLimitReference's
 * visit() method.
 * @tparam T_type The type of the reference.
 * @tparam T_action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param target The visited instance.
 */
template <typename T_type, bool I_derives_trackable>
struct QEXTVisitor<QEXTLimitReference<T_type, I_derives_trackable> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action, const QEXTLimitReference<T_type, I_derives_trackable> &target) {
        qextVisitEach(action, target.visit());
    }
};



/** A QEXTConstLimitReference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QEXTTrackable, then qextVisitEach<>() will "limit" itself to the
 * QEXTTrackable reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the
 * QEXTTrackable reference are stored, so we can later retrieve the QEXTTrackable
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the trackable
 * reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QEXTTrackable then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with qextMemberFunctor(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_trackable = QEXTBaseAndDerivedTester<QEXTTrackable, T_type>::value>
class QEXTConstLimitReference
{
public:
    /** Constructor.
     * @param target The reference to limit.
     */
    QEXTConstLimitReference(const T_type &target) : m_visited(target) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     *  or QEXTTrackable& if T_type derives from QEXTTrackable.
     * @return The reference.
     */
    const T_type &visit() const { return m_visited; }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    const T_type &invoke() const { return m_visited; }

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
     * @param target The reference to limit.
     */
    QEXTConstLimitReference(const T_type &target) : m_visited(target), m_invoked(target) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QEXTTrackable& if T_type derives from QEXTTrackable.
     * @return The reference.
     */
    const QEXTTrackable &visit() const { return m_visited; }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    const T_type &invoke() const { return m_invoked; }

private:
    /** The trackable reference.
     */
    const QEXTTrackable &m_visited;
    /** The reference.
     */
    const T_type &m_invoked;
};

/** Implementation of visitor specialized for the QEXTConstLimitReference
 * class, to call qextVisitEach() on the entity returned by the QEXTConstLimitReference's
 * visit() method.
 * @tparam T_type The type of the reference.
 * @tparam T_action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param target The visited instance.
 */
template <typename T_type, bool I_derives_trackable>
struct QEXTVisitor<QEXTConstLimitReference<T_type, I_derives_trackable> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTConstLimitReference<T_type, I_derives_trackable> &target) {
        qextVisitEach(action, target.visit());
    }
};



/** A QEXTVolatileLimitReference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QEXTTrackable, then qextVisitEach<>() will "limit" itself to the
 * QEXTTrackable reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the
 * QEXTTrackable reference are stored, so we can later retrieve the QEXTTrackable
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the trackable
 * reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QEXTTrackable then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with qextMemberFunctor(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_trackable = QEXTBaseAndDerivedTester<QEXTTrackable, T_type>::value>
class QEXTVolatileLimitReference
{
public:
    /** Constructor.
     * @param target The reference to limit.
     */
    QEXTVolatileLimitReference(T_type &target) : m_visited(target) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     *  or QEXTTrackable& if T_type derives from QEXTTrackable.
     * @return The reference.
     */
    const T_type &visit() const { return m_visited; }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    volatile T_type &invoke() const { return m_visited; }

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
     * @param target The reference to limit.
     */
    QEXTVolatileLimitReference(T_type &target) : m_visited(target), m_invoked(target) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     *  or QEXTTrackable& if T_type derives from QEXTTrackable.
     * @return The reference.
     */
    const QEXTTrackable &visit() const { return m_visited; }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    volatile T_type &invoke() const { return m_invoked; }

private:
    /** The trackable reference.
     */
    QEXTTrackable &m_visited;
    /** The reference.
     */
    T_type &m_invoked;
};

/** Implementation of visitor specialized for the QEXTVolatileLimitReference
 * class, to call qextVisitEach() on the entity returned by the QEXTVolatileLimitReference's
 * visit() method.
 * @tparam T_type The type of the reference.
 * @tparam T_action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param target The visited instance.
 */
template <typename T_type, bool I_derives_trackable>
struct QEXTVisitor<QEXTVolatileLimitReference<T_type, I_derives_trackable> >
{
    template <typename T_action>
    static void doVisitEach(const T_action& action,
                            const QEXTVolatileLimitReference<T_type, I_derives_trackable> &target) {
        qextVisitEach(action, target.visit());
    }
};



/** A QEXTConstVolatileLimitReference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QEXTTrackable, then qextVisitEach<>() will "limit" itself to the
 * QEXTTrackable reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from trackable then both the derived reference and the
 * QEXTTrackable reference are stored, so we can later retrieve the QEXTTrackable
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the trackable
 * reference (so that you can call qextVisitEach() on it), you use visit().
 *
 * If Foo does not inherit from QEXTTrackable then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (qexBindFunctor) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with qextMemberFunctor(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_trackable = QEXTBaseAndDerivedTester<QEXTTrackable, T_type>::value>
class QEXTConstVolatileLimitReference
{
public:
    /** Constructor.
     * @param target The reference to limit.
     */
    QEXTConstVolatileLimitReference(const T_type &target) : m_visited(target) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QEXTTrackable& if T_type derives from QEXTTrackable.
     * @return The reference.
     */
    const T_type &visit() const { return m_visited; }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    const volatile T_type &invoke() const { return m_visited; }

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
     * @param target The reference to limit.
     */
    QEXTConstVolatileLimitReference(const T_type &target) : m_visited(target), m_invoked(target) {}

    /** Retrieve the entity to visit for qextVisitEach().
     * Depending on the template specialization, this is either a derived reference,
     * or QEXTTrackable& if T_type derives from QEXTTrackable.
     * @return The reference.
     */
    const QEXTTrackable &visit() const { return m_visited; }

    /** Retrieve the reference.
     * This is always a reference to the derived instance.
     * @return The reference.
     */
    const volatile T_type &invoke() const { return m_invoked; }

private:
    /** The trackable reference.
     */
    const QEXTTrackable &m_visited;
    /** The reference.
     */
    const T_type &m_invoked;
};

/** Implementation of visitor specialized for the QEXTConstVolatileLimitReference
 * class, to call qextVisitEach() on the entity returned by the QEXTConstVolatileLimitReference's
 * visit() method.
 * @tparam T_type The type of the reference.
 * @tparam T_action The type of functor to invoke.
 * @param action The functor to invoke.
 * @param target The visited instance.
 */
template <typename T_type, bool I_derives_trackable>
struct QEXTVisitor<QEXTConstVolatileLimitReference<T_type, I_derives_trackable> >
{
    template <typename T_action>
    static void doVisitEach(const T_action& action,
                            const QEXTConstVolatileLimitReference<T_type, I_derives_trackable> &target) {
        qextVisitEach(action, target.visit());
    }
};


#endif // QEXTLIMITREFERENCE_H
