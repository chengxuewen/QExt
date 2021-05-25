#ifndef QEXTLIMITREFERENCE_H
#define QEXTLIMITREFERENCE_H

#include <qexttrackable.h>
#include <qexttypetrait.h>
#include <qextvisitor.h>

/** A limit_reference<Foo> object stores a reference (Foo&), but make sure that,
 * if Foo inherits from QEXTTrackable, then visit_each<>() will "limit" itself to the
 * sigc::QEXTTrackable reference instead of the derived reference. This avoids use of
 * a reference to the derived type when the derived destructor has run. That can be
 * a problem when using virtual inheritance.
 *
 * If Foo inherits from QEXTTrackable then both the derived reference and the
 * sigc::QEXTTrackable reference are stored, so we can later retrieve the sigc::QEXTTrackable
 * reference without doing an implicit conversion. To retrieve the derived reference
 * (so that you invoke methods or members of it), use invoke(). To retrieve the QEXTTrackable
 * reference (so that you can call visit_each() on it), you use visit().
 *
 * If Foo does not inherit from sigc::QEXTTrackable then invoke() and visit() just return the
 * derived reference.
 *
 * This is used for bound (sigc::bind) slot parameters (via QEXTBoundArgument), bound return values,
 * and, with mem_fun(), the reference to the handling object.
 *
 * - @e T_type The type of the reference.
 */
template <typename T_type, bool I_derives_trackable = QEXTBaseAndDerivedTester<QEXTTrackable, T_type>::value>
class QEXTLimitReference
{
public:
    QEXTLimitReference(T_type &target) : m_visited(target) {}

    inline const T_type &visit() const { return m_visited; }
    inline T_type &invoke() const { return m_visited; }

private:
    T_type &m_visited;
};


template <typename T_type>
class QEXTLimitReference<T_type, true>
{
public:
    QEXTLimitReference(T_type &target) : m_visited(target), m_invoked(target) {}

    inline const QEXTTrackable &visit() const { return m_visited; }
    inline T_type& invoke() const { return m_invoked; }

private:
    QEXTTrackable &m_visited;
    T_type &m_invoked;
};


template <typename T_type, bool I_derives_trackable>
struct QEXTVisitor<QEXTLimitReference<T_type, I_derives_trackable> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action, const QEXTLimitReference<T_type, I_derives_trackable> &target) {
        qextVisitEach(action, target.visit());
    }
};



template <typename T_type, bool I_derives_trackable = QEXTBaseAndDerivedTester<QEXTTrackable, T_type>::value>
class QEXTConstLimitReference
{
public:
    QEXTConstLimitReference(const T_type &target) : m_visited(target) {}

    inline const T_type &visit() const { return m_visited; }

    inline const T_type &invoke() const { return m_visited; }

private:
    const T_type &m_visited;
};

template <typename T_type>
class QEXTConstLimitReference<T_type, true>
{
public:
    QEXTConstLimitReference(const T_type &target) : m_visited(target), m_invoked(target) {}

    inline const QEXTTrackable &visit() const { return m_visited; }

    inline const T_type &invoke() const { return m_invoked; }

private:
    const QEXTTrackable &m_visited;
    const T_type &m_invoked;
};

template <typename T_type, bool I_derives_trackable>
struct QEXTVisitor<QEXTConstLimitReference<T_type, I_derives_trackable> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTConstLimitReference<T_type, I_derives_trackable> &target) {
        qextVisitEach(action, target.visit());
    }
};



template <typename T_type, bool I_derives_trackable = QEXTBaseAndDerivedTester<QEXTTrackable, T_type>::value>
class QEXTVolatileLimitReference
{
public:
    QEXTVolatileLimitReference(T_type &target) : m_visited(target) {}

    inline const T_type &visit() const { return m_visited; }

    inline volatile T_type &invoke() const { return m_visited; }

private:
    T_type &m_visited;
};


template <typename T_type>
class QEXTVolatileLimitReference<T_type, true>
{
public:
    QEXTVolatileLimitReference(T_type &target) : m_visited(target), m_invoked(target) {}

    inline const QEXTTrackable &visit() const { return m_visited; }

    inline volatile T_type &invoke() const { return m_invoked; }

private:
    QEXTTrackable &m_visited;
    T_type &m_invoked;
};

template <typename T_type, bool I_derives_trackable>
struct QEXTVisitor<QEXTVolatileLimitReference<T_type, I_derives_trackable> >
{
    template <typename T_action>
    static void doVisitEach(const T_action& action,
                            const QEXTVolatileLimitReference<T_type, I_derives_trackable> &target) {
        qextVisitEach(action, target.visit());
    }
};



template <typename T_type, bool I_derives_trackable = QEXTBaseAndDerivedTester<QEXTTrackable, T_type>::value>
class QEXTConstVolatileLimitReference
{
public:
    QEXTConstVolatileLimitReference(const T_type &target) : m_visited(target) {}

    inline const T_type &visit() const { return m_visited; }

    inline const volatile T_type &invoke() const { return m_visited; }

private:
    const T_type &m_visited;
};

template <typename T_type>
class QEXTConstVolatileLimitReference<T_type, true>
{
public:
    QEXTConstVolatileLimitReference(const T_type &target) : m_visited(target), m_invoked(target) {}

    inline const QEXTTrackable &visit() const { return m_visited; }

    inline const volatile T_type &invoke() const { return m_invoked; }

private:
    const QEXTTrackable &m_visited;
    const T_type &m_invoked;
};

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
