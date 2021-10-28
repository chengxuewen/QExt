#ifndef _QEXTSLOT_H
#define _QEXTSLOT_H

#include <qextFunction.h>
#include <qextGlobal.h>

#include <QObject>
#include <QPointer>
#include <QSet>

QT_WARNING_DISABLE_GCC("-Wcast-function-type")

namespace qextPrivate
{

    struct QEXT_CORE_API QEXTSlotData
    {
        QEXTSlotData();
        QEXTSlotData(const QEXTSlotData &other);
        virtual ~QEXTSlotData() {}

        QEXTSlotData &operator=(const QEXTSlotData &other);

        bool operator==(const QEXTSlotData &other) const;
        bool operator!=(const QEXTSlotData &other) const;

        QAtomicInt m_trackable;
        QList<QPointer< QObject > > m_objectList;
    };

    class QEXT_CORE_API QEXTSlotBase
    {
    public:
        typedef void *(*HookFunction)(void *);

        QEXTSlotBase();
        QEXTSlotBase(const QSharedPointer< QEXTSlotData > &data);
        QEXTSlotBase(const QEXTSlotBase &other);
        virtual ~QEXTSlotBase() {}

        QEXTSlotBase &operator=(const QEXTSlotBase &other);

        bool operator==(const QEXTSlotBase &other) const;
        bool operator!=(const QEXTSlotBase &other) const;

        bool isNull() const;
        bool isTrackable() const;
        bool isValid() const;

        bool isBlocked() const;
        bool setBlock(bool block = true);
        bool unblock();

        void setParent(void *parent, HookFunction cleanup);
        bool isConnected() const;
        void disconnect();

    public:
        friend struct QEXTSlotObjectBind;
        QAtomicInt m_blocked;
        void *m_parent;
        HookFunction m_cleanupFunc;

        HookFunction m_callFunc;
        mutable QSharedPointer< QEXTSlotData > m_data;
    };

    struct QEXTSlotObjectBind
    {
        QEXTSlotObjectBind(QEXTSlotData *data) : m_data(data) {}
        virtual ~QEXTSlotObjectBind() {}

        void operator()(const QObject *object) const
        {
            if (object)
            {
                QObject *obj = const_cast< QObject * >(object);
                m_data->m_trackable.store(QEXT_ATOMIC_INT_TRUE);
                m_data->m_objectList.append(QPointer<QObject>(obj));
            }
        }

        QEXTSlotData *m_data;
    };

    template < typename T_functor >
    struct QEXTSlotFunctorData : public QEXTSlotData
    {
        typedef QEXTSlotFunctorData< T_functor > Self;
        typedef typename QEXTAdaptorTrait< T_functor >::Adaptor Adaptor;

        QEXTSlotFunctorData(const T_functor &functor) : m_functor(functor)
        {
            qextVisitEachType< QObject * >(QEXTSlotObjectBind(this), functor);
        }
        QEXTSlotFunctorData(const QEXTSlotFunctorData &other) : QEXTSlotData(other), m_functor(other.m_functor) {}

        Adaptor m_functor;
    };

    template <
        typename T_functor,
        typename T_return,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7 >
    struct QEXTSlotCall7
    {
        static T_return call(
            const QSharedPointer< QEXTSlotData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7)
        {
            typedef QEXTSlotFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                   .template operator() <
                   typename QEXTTypeTrait< T_arg1 >::Take,
                   typename QEXTTypeTrait< T_arg2 >::Take,
                   typename QEXTTypeTrait< T_arg3 >::Take,
                   typename QEXTTypeTrait< T_arg4 >::Take,
                   typename QEXTTypeTrait< T_arg5 >::Take,
                   typename QEXTTypeTrait< T_arg6 >::Take,
                   typename QEXTTypeTrait< T_arg7 >::Take > (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        static QEXTSlotBase::HookFunction address()
        {
            return reinterpret_cast< QEXTSlotBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    struct QEXTSlotCall6
    {
        static T_return call(
            const QSharedPointer< QEXTSlotData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6)
        {
            typedef QEXTSlotFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                   .template operator() <
                   typename QEXTTypeTrait< T_arg1 >::Take,
                   typename QEXTTypeTrait< T_arg2 >::Take,
                   typename QEXTTypeTrait< T_arg3 >::Take,
                   typename QEXTTypeTrait< T_arg4 >::Take,
                   typename QEXTTypeTrait< T_arg5 >::Take,
                   typename QEXTTypeTrait< T_arg6 >::Take > (arg1, arg2, arg3, arg4, arg5, arg6);
        }

        static QEXTSlotBase::HookFunction address()
        {
            return reinterpret_cast< QEXTSlotBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    struct QEXTSlotCall5
    {
        static T_return call(
            const QSharedPointer< QEXTSlotData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5)
        {
            typedef QEXTSlotFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                   .template operator() <
                   typename QEXTTypeTrait< T_arg1 >::Take,
                   typename QEXTTypeTrait< T_arg2 >::Take,
                   typename QEXTTypeTrait< T_arg3 >::Take,
                   typename QEXTTypeTrait< T_arg4 >::Take,
                   typename QEXTTypeTrait< T_arg5 >::Take > (arg1, arg2, arg3, arg4, arg5);
        }

        static QEXTSlotBase::HookFunction address()
        {
            return reinterpret_cast< QEXTSlotBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    struct QEXTSlotCall4
    {
        static T_return call(
            const QSharedPointer< QEXTSlotData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4)
        {
            typedef QEXTSlotFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                   .template operator() <
                   typename QEXTTypeTrait< T_arg1 >::Take,
                   typename QEXTTypeTrait< T_arg2 >::Take,
                   typename QEXTTypeTrait< T_arg3 >::Take,
                   typename QEXTTypeTrait< T_arg4 >::Take > (arg1, arg2, arg3, arg4);
        }

        static QEXTSlotBase::HookFunction address()
        {
            return reinterpret_cast< QEXTSlotBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
    struct QEXTSlotCall3
    {
        static T_return call(
            const QSharedPointer< QEXTSlotData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg3 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3)
        {
            typedef QEXTSlotFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                   .template operator()< typename QEXTTypeTrait< T_arg1 >::Take, typename QEXTTypeTrait< T_arg2 >::Take, typename QEXTTypeTrait< T_arg3 >::Take >(
                       arg1, arg2, arg3);
        }

        static QEXTSlotBase::HookFunction address()
        {
            return reinterpret_cast< QEXTSlotBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2 >
    struct QEXTSlotCall2
    {
        static T_return
        call(const QSharedPointer< QEXTSlotData > &functionData, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2)
        {
            typedef QEXTSlotFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                   .template operator()< typename QEXTTypeTrait< T_arg1 >::Take, typename QEXTTypeTrait< T_arg2 >::Take >(arg1, arg2);
        }

        static QEXTSlotBase::HookFunction address()
        {
            return reinterpret_cast< QEXTSlotBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1 >
    struct QEXTSlotCall1
    {
        static T_return call(const QSharedPointer< QEXTSlotData > &functionData, typename QEXTTypeTrait< T_arg1 >::Take arg1)
        {
            typedef QEXTSlotFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor).template operator()< typename QEXTTypeTrait< T_arg1 >::Take >(arg1);
        }

        static QEXTSlotBase::HookFunction address()
        {
            return reinterpret_cast< QEXTSlotBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return >
    struct QEXTSlotCall0
    {
        static T_return call(const QSharedPointer< QEXTSlotData > &functionData)
        {
            typedef QEXTSlotFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)();
        }

        static QEXTSlotBase::HookFunction address()
        {
            return reinterpret_cast< QEXTSlotBase::HookFunction >(&call);
        }
    };

    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
    class QEXTSlot7 : public QEXTSlotBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QEXTTypeTrait< T_arg4 >::Take Arg4;
        typedef typename QEXTTypeTrait< T_arg5 >::Take Arg5;
        typedef typename QEXTTypeTrait< T_arg6 >::Take Arg6;
        typedef typename QEXTTypeTrait< T_arg7 >::Take Arg7;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTSlotData > &, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);

        QEXTSlot7() {}
        template < typename T_functor >
        QEXTSlot7(const T_functor &functor)
            : QEXTSlotBase(QSharedPointer< QEXTSlotData >(new QEXTSlotFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTSlotCall7< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::address();
        }
        QEXTSlot7(const QEXTSlot7 &other) : QEXTSlotBase(other) {}

        T_return operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7) const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            }
            return T_return();
        }
    };

    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    class QEXTSlot6 : public QEXTSlotBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QEXTTypeTrait< T_arg4 >::Take Arg4;
        typedef typename QEXTTypeTrait< T_arg5 >::Take Arg5;
        typedef typename QEXTTypeTrait< T_arg6 >::Take Arg6;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTSlotData > &, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);

        QEXTSlot6() {}
        template < typename T_functor >
        QEXTSlot6(const T_functor &functor)
            : QEXTSlotBase(QSharedPointer< QEXTSlotData >(new QEXTSlotFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTSlotCall6< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >::address();
        }
        QEXTSlot6(const QEXTSlot6 &other) : QEXTSlotBase(other) {}

        T_return operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6) const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data, arg1, arg2, arg3, arg4, arg5, arg6);
            }
            return T_return();
        }
    };

    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    class QEXTSlot5 : public QEXTSlotBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QEXTTypeTrait< T_arg4 >::Take Arg4;
        typedef typename QEXTTypeTrait< T_arg5 >::Take Arg5;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTSlotData > &, Arg1, Arg2, Arg3, Arg4, Arg5);

        QEXTSlot5() {}
        template < typename T_functor >
        QEXTSlot5(const T_functor &functor)
            : QEXTSlotBase(QSharedPointer< QEXTSlotData >(new QEXTSlotFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTSlotCall5< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >::address();
        }
        QEXTSlot5(const QEXTSlot5 &other) : QEXTSlotBase(other) {}

        T_return operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5) const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data, arg1, arg2, arg3, arg4, arg5);
            }
            return T_return();
        }
    };

    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    class QEXTSlot4 : public QEXTSlotBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QEXTTypeTrait< T_arg4 >::Take Arg4;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTSlotData > &, Arg1, Arg2, Arg3, Arg4);

        QEXTSlot4() {}
        template < typename T_functor >
        QEXTSlot4(const T_functor &functor)
            : QEXTSlotBase(QSharedPointer< QEXTSlotData >(new QEXTSlotFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTSlotCall4< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4 >::address();
        }
        QEXTSlot4(const QEXTSlot4 &other) : QEXTSlotBase(other) {}

        T_return operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4) const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data, arg1, arg2, arg3, arg4);
            }
            return T_return();
        }
    };

    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
    class QEXTSlot3 : public QEXTSlotBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTSlotData > &, Arg1, Arg2, Arg3);

        QEXTSlot3() {}
        template < typename T_functor >
        QEXTSlot3(const T_functor &functor)
            : QEXTSlotBase(QSharedPointer< QEXTSlotData >(new QEXTSlotFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTSlotCall3< T_functor, T_return, T_arg1, T_arg2, T_arg3 >::address();
        }
        QEXTSlot3(const QEXTSlot3 &other) : QEXTSlotBase(other) {}

        T_return operator()(Arg1 arg1, Arg2 arg2, Arg3 arg3) const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data, arg1, arg2, arg3);
            }
            return T_return();
        }
    };

    template < typename T_return, typename T_arg1, typename T_arg2 >
    class QEXTSlot2 : public QEXTSlotBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTSlotData > &, Arg1, Arg2);

        QEXTSlot2() {}
        template < typename T_functor >
        QEXTSlot2(const T_functor &functor)
            : QEXTSlotBase(QSharedPointer< QEXTSlotData >(new QEXTSlotFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTSlotCall2< T_functor, T_return, T_arg1, T_arg2 >::address();
        }
        QEXTSlot2(const QEXTSlot2 &other) : QEXTSlotBase(other) {}

        T_return operator()(Arg1 arg1, Arg2 arg2) const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data, arg1, arg2);
            }
            return T_return();
        }
    };

    template < typename T_return, typename T_arg1 >
    class QEXTSlot1 : public QEXTSlotBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTSlotData > &, Arg1);

        QEXTSlot1() {}
        template < typename T_functor >
        QEXTSlot1(const T_functor &functor)
            : QEXTSlotBase(QSharedPointer< QEXTSlotData >(new QEXTSlotFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTSlotCall1< T_functor, T_return, T_arg1 >::address();
        }
        QEXTSlot1(const QEXTSlot1 &other) : QEXTSlotBase(other) {}

        T_return operator()(Arg1 arg1) const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data, arg1);
            }
            return T_return();
        }
    };

    template < typename T_return >
    class QEXTSlot0 : public QEXTSlotBase
    {
    public:
        typedef T_return Return;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTSlotData > &);

        QEXTSlot0() {}
        template < typename T_functor >
        QEXTSlot0(const T_functor &functor)
            : QEXTSlotBase(QSharedPointer< QEXTSlotData >(new QEXTSlotFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTSlotCall0< T_functor, T_return >::address();
        }
        QEXTSlot0(const QEXTSlot0 &other) : QEXTSlotBase(other) {}

        T_return operator()() const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data);
            }
            return T_return();
        }
    };

} // namespace qextPrivate

template <
    typename T_return,
    typename T_arg1 = QEXTNil,
    typename T_arg2 = QEXTNil,
    typename T_arg3 = QEXTNil,
    typename T_arg4 = QEXTNil,
    typename T_arg5 = QEXTNil,
    typename T_arg6 = QEXTNil,
    typename T_arg7 = QEXTNil >
class QEXTSlot : public qextPrivate::QEXTSlot7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
public:
    typedef qextPrivate::QEXTSlot7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

    QEXTSlot() {}
    template < typename T_functor >
    QEXTSlot(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(
        T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(
        T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    QEXTSlot(const QEXTSlot &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTSlot< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTSlot6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
public:
    typedef qextPrivate::QEXTSlot6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

    QEXTSlot() {}
    template < typename T_functor >
    QEXTSlot(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    QEXTSlot(const QEXTSlot &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTSlot< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTSlot5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
public:
    typedef qextPrivate::QEXTSlot5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

    QEXTSlot() {}
    template < typename T_functor >
    QEXTSlot(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    QEXTSlot(const QEXTSlot &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTSlot< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTSlot4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >
{
public:
    typedef qextPrivate::QEXTSlot4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

    QEXTSlot() {}
    template < typename T_functor >
    QEXTSlot(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    QEXTSlot(const QEXTSlot &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTSlot< T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTSlot3< T_return, T_arg1, T_arg2, T_arg3 >
{
public:
    typedef qextPrivate::QEXTSlot3< T_return, T_arg1, T_arg2, T_arg3 > Base;

    QEXTSlot() {}
    template < typename T_functor >
    QEXTSlot(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    QEXTSlot(const QEXTSlot &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2 >
class QEXTSlot< T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTSlot2< T_return, T_arg1, T_arg2 >
{
public:
    typedef qextPrivate::QEXTSlot2< T_return, T_arg1, T_arg2 > Base;

    QEXTSlot() {}
    template < typename T_functor >
    QEXTSlot(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2)) : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2)) : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    QEXTSlot(const QEXTSlot &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template < typename T_return, typename T_arg1 >
class QEXTSlot< T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTSlot1< T_return, T_arg1 >
{
public:
    typedef qextPrivate::QEXTSlot1< T_return, T_arg1 > Base;

    QEXTSlot() {}
    template < typename T_functor >
    QEXTSlot(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1)) : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1)) : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) const) : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) const) : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) volatile) : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) volatile) : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    QEXTSlot(const QEXTSlot &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1) const
    {
        return Base::operator()(arg1);
    }
};

template < typename T_return >
class QEXTSlot< T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTSlot0< T_return >
{
public:
    typedef qextPrivate::QEXTSlot0< T_return > Base;

    QEXTSlot() {}
    template < typename T_functor >
    QEXTSlot(const T_functor &functor) : Base(functor)
    {
    }
    QEXTSlot(T_return (*func)()) : Base(QEXTPointerFunctor< T_return >(func)) {}
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)()) : Base(QEXTBoundMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)()) : Base(QEXTBoundMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)() const) : Base(QEXTBoundConstMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)() const) : Base(QEXTBoundConstMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)() volatile) : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)() volatile) : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj *obj, T_return (T_obj::*func)() const volatile) : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTSlot(T_obj &obj, T_return (T_obj::*func)() const volatile) : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    QEXTSlot(const QEXTSlot &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};



#endif // _QEXTSLOT_H
