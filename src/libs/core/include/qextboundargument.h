#ifndef QEXTBOUNDARGUMENT_H
#define QEXTBOUNDARGUMENT_H

#include <qextlimitreference.h>
#include <qextreferencewrapper.h>

template <typename T_type>
class QEXTBoundArgument
{
public:
    QEXTBoundArgument(const T_type &argument) : m_visited(argument) {}

    const T_type &visit() const {
        return m_visited;
    }

    T_type &invoke() {
        return m_visited;
    }

private:
    T_type m_visited;
};


template <typename T_wrapped>
class QEXTBoundArgument<QEXTReferenceWrapper<T_wrapped> >
{
public:
    QEXTBoundArgument(const QEXTReferenceWrapper<T_wrapped> &argument) : m_visited(qextUnwrapReference(argument)) {}

    const QEXTLimitReference<T_wrapped>& visit() const {
        return m_visited;
    }

    T_wrapped& invoke() {
        return m_visited.invoke();
    }

private:
    QEXTLimitReference<T_wrapped> m_visited;
};

template <typename T_wrapped>
class QEXTBoundArgument< QEXTConstReferenceWrapper<T_wrapped> >
{
public:
    QEXTBoundArgument(const QEXTConstReferenceWrapper<T_wrapped> &argument) : m_visited(qextUnwrapReference(argument)) {}

    const QEXTConstLimitReference<T_wrapped>& visit() const {
        return m_visited;
    }

    const T_wrapped& invoke() {
        return m_visited.invoke();
    }

private:
    QEXTConstLimitReference<T_wrapped> m_visited;
};


template <typename T_type>
struct QEXTVisitor<QEXTBoundArgument<T_type> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundArgument<T_type> &argument) {
        qextVisitEach(action, argument.visit());
    }
};

#endif // QEXTBOUNDARGUMENT_H
