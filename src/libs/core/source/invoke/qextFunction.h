#ifndef _QEXTFUNCTION_H
#define _QEXTFUNCTION_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>
#include <qextAdaptorTrait.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>

#include <QObject>
#include <QSharedPointer>
#include <QPointer>
#include <QSet>

namespace detail
{

    struct QEXT_CORE_API QExtFunctionData
    {
        QExtFunctionData();
        QExtFunctionData(const QExtFunctionData &other);
        virtual ~QExtFunctionData() {}

        QExtFunctionData &operator=(const QExtFunctionData &other);

        bool operator==(const QExtFunctionData &other) const;
        bool operator!=(const QExtFunctionData &other) const;

        QAtomicInt m_trackable;
        QList<QPointer< QObject > > m_objectList;
    };

    class QEXT_CORE_API QExtFunctionBase
    {
    public:
        typedef void *(*HookFunction)(void *);

        QExtFunctionBase();
        QExtFunctionBase(const QSharedPointer< QExtFunctionData > &data);
        QExtFunctionBase(const QExtFunctionBase &other);
        virtual ~QExtFunctionBase() {}

        QExtFunctionBase &operator=(const QExtFunctionBase &other);

        bool operator==(const QExtFunctionBase &other) const;
        bool operator!=(const QExtFunctionBase &other) const;

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
        friend struct QExtFunctionObjectBind;
        QAtomicInt m_blocked;
        void *m_parent;
        HookFunction m_cleanupFunc;

        HookFunction m_callFunc;
        mutable QSharedPointer< QExtFunctionData > m_data;
    };

    struct QExtFunctionObjectBind
    {
        QExtFunctionObjectBind(QExtFunctionData *data) : m_data(data) {}
        virtual ~QExtFunctionObjectBind() {}

        void operator()(const QObject *object) const
        {
            if (object)
            {
                QObject *obj = const_cast< QObject * >(object);
                m_data->m_trackable = QEXT_ATOMIC_INT_TRUE;
                m_data->m_objectList.append(QPointer<QObject>(obj));
            }
        }

        QExtFunctionData *m_data;
    };

    template < typename T_functor >
    struct QExtFunctionFunctorData : public QExtFunctionData
    {
        typedef QExtFunctionFunctorData< T_functor > Self;
        typedef typename QExtAdaptorTrait< T_functor >::AdaptorType AdaptorType;

        QExtFunctionFunctorData(const T_functor &functor) : mFunctor(functor)
        {
            qextVisitEachType< QObject * >(QExtFunctionObjectBind(this), functor);
        }
        QExtFunctionFunctorData(const QExtFunctionFunctorData &other) : QExtFunctionData(other), mFunctor(other.mFunctor) {}

        AdaptorType mFunctor;
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
    struct QExtFunctionCall7
    {
        static T_return call(
            const QSharedPointer< QExtFunctionData > &functionData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7)
        {
            typedef QExtFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->mFunctor)
                   .template operator() <
                   typename QExtTypeTrait< T_arg1 >::Take,
                   typename QExtTypeTrait< T_arg2 >::Take,
                   typename QExtTypeTrait< T_arg3 >::Take,
                   typename QExtTypeTrait< T_arg4 >::Take,
                   typename QExtTypeTrait< T_arg5 >::Take,
                   typename QExtTypeTrait< T_arg6 >::Take,
                   typename QExtTypeTrait< T_arg7 >::Take > (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        static QExtFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QExtFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    struct QExtFunctionCall6
    {
        static T_return call(
            const QSharedPointer< QExtFunctionData > &functionData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6)
        {
            typedef QExtFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->mFunctor)
                   .template operator() <
                   typename QExtTypeTrait< T_arg1 >::Take,
                   typename QExtTypeTrait< T_arg2 >::Take,
                   typename QExtTypeTrait< T_arg3 >::Take,
                   typename QExtTypeTrait< T_arg4 >::Take,
                   typename QExtTypeTrait< T_arg5 >::Take,
                   typename QExtTypeTrait< T_arg6 >::Take > (arg1, arg2, arg3, arg4, arg5, arg6);
        }

        static QExtFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QExtFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    struct QExtFunctionCall5
    {
        static T_return call(
            const QSharedPointer< QExtFunctionData > &functionData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5)
        {
            typedef QExtFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->mFunctor)
                   .template operator() <
                   typename QExtTypeTrait< T_arg1 >::Take,
                   typename QExtTypeTrait< T_arg2 >::Take,
                   typename QExtTypeTrait< T_arg3 >::Take,
                   typename QExtTypeTrait< T_arg4 >::Take,
                   typename QExtTypeTrait< T_arg5 >::Take > (arg1, arg2, arg3, arg4, arg5);
        }

        static QExtFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QExtFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    struct QExtFunctionCall4
    {
        static T_return call(
            const QSharedPointer< QExtFunctionData > &functionData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4)
        {
            typedef QExtFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->mFunctor)
                   .template operator() <
                   typename QExtTypeTrait< T_arg1 >::Take,
                   typename QExtTypeTrait< T_arg2 >::Take,
                   typename QExtTypeTrait< T_arg3 >::Take,
                   typename QExtTypeTrait< T_arg4 >::Take > (arg1, arg2, arg3, arg4);
        }

        static QExtFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QExtFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
    struct QExtFunctionCall3
    {
        static T_return call(
            const QSharedPointer< QExtFunctionData > &functionData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg3 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3)
        {
            typedef QExtFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->mFunctor)
                   .template operator()< typename QExtTypeTrait< T_arg1 >::Take, typename QExtTypeTrait< T_arg2 >::Take, typename QExtTypeTrait< T_arg3 >::Take >(
                       arg1, arg2, arg3);
        }

        static QExtFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QExtFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2 >
    struct QExtFunctionCall2
    {
        static T_return
        call(const QSharedPointer< QExtFunctionData > &functionData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2)
        {
            typedef QExtFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->mFunctor)
                   .template operator()< typename QExtTypeTrait< T_arg1 >::Take, typename QExtTypeTrait< T_arg2 >::Take >(arg1, arg2);
        }

        static QExtFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QExtFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1 >
    struct QExtFunctionCall1
    {
        static T_return call(const QSharedPointer< QExtFunctionData > &functionData, typename QExtTypeTrait< T_arg1 >::Take arg1)
        {
            typedef QExtFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->mFunctor).template operator()< typename QExtTypeTrait< T_arg1 >::Take >(arg1);
        }

        static QExtFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QExtFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return >
    struct QExtFunctionCall0
    {
        static T_return call(const QSharedPointer< QExtFunctionData > &functionData)
        {
            typedef QExtFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->mFunctor)();
        }

        static QExtFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QExtFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
    class QExtFunction7 : public QExtFunctionBase
    {
    public:
        typedef T_return ResultType;
        typedef typename QExtTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QExtTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QExtTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QExtTypeTrait< T_arg4 >::Take Arg4;
        typedef typename QExtTypeTrait< T_arg5 >::Take Arg5;
        typedef typename QExtTypeTrait< T_arg6 >::Take Arg6;
        typedef typename QExtTypeTrait< T_arg7 >::Take Arg7;

        typedef T_return (*CallFunction)(const QSharedPointer< QExtFunctionData > &, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);

        QExtFunction7() {}
        template < typename T_functor >
        QExtFunction7(const T_functor &functor)
            : QExtFunctionBase(QSharedPointer< QExtFunctionData >(new QExtFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = detail::QExtFunctionCall7< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::address();
        }
        QExtFunction7(const QExtFunction7 &other) : QExtFunctionBase(other) {}

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
    class QExtFunction6 : public QExtFunctionBase
    {
    public:
        typedef T_return ResultType;
        typedef typename QExtTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QExtTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QExtTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QExtTypeTrait< T_arg4 >::Take Arg4;
        typedef typename QExtTypeTrait< T_arg5 >::Take Arg5;
        typedef typename QExtTypeTrait< T_arg6 >::Take Arg6;

        typedef T_return (*CallFunction)(const QSharedPointer< QExtFunctionData > &, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);

        QExtFunction6() {}
        template < typename T_functor >
        QExtFunction6(const T_functor &functor)
            : QExtFunctionBase(QSharedPointer< QExtFunctionData >(new QExtFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = detail::QExtFunctionCall6< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >::address();
        }
        QExtFunction6(const QExtFunction6 &other) : QExtFunctionBase(other) {}

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
    class QExtFunction5 : public QExtFunctionBase
    {
    public:
        typedef T_return ResultType;
        typedef typename QExtTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QExtTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QExtTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QExtTypeTrait< T_arg4 >::Take Arg4;
        typedef typename QExtTypeTrait< T_arg5 >::Take Arg5;

        typedef T_return (*CallFunction)(const QSharedPointer< QExtFunctionData > &, Arg1, Arg2, Arg3, Arg4, Arg5);

        QExtFunction5() {}
        template < typename T_functor >
        QExtFunction5(const T_functor &functor)
            : QExtFunctionBase(QSharedPointer< QExtFunctionData >(new QExtFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = detail::QExtFunctionCall5< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >::address();
        }
        QExtFunction5(const QExtFunction5 &other) : QExtFunctionBase(other) {}

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
    class QExtFunction4 : public QExtFunctionBase
    {
    public:
        typedef T_return ResultType;
        typedef typename QExtTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QExtTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QExtTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QExtTypeTrait< T_arg4 >::Take Arg4;

        typedef T_return (*CallFunction)(const QSharedPointer< QExtFunctionData > &, Arg1, Arg2, Arg3, Arg4);

        QExtFunction4() {}
        template < typename T_functor >
        QExtFunction4(const T_functor &functor)
            : QExtFunctionBase(QSharedPointer< QExtFunctionData >(new QExtFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = detail::QExtFunctionCall4< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4 >::address();
        }
        QExtFunction4(const QExtFunction4 &other) : QExtFunctionBase(other) {}

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
    class QExtFunction3 : public QExtFunctionBase
    {
    public:
        typedef T_return ResultType;
        typedef typename QExtTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QExtTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QExtTypeTrait< T_arg3 >::Take Arg3;

        typedef T_return (*CallFunction)(const QSharedPointer< QExtFunctionData > &, Arg1, Arg2, Arg3);

        QExtFunction3() {}
        template < typename T_functor >
        QExtFunction3(const T_functor &functor)
            : QExtFunctionBase(QSharedPointer< QExtFunctionData >(new QExtFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = detail::QExtFunctionCall3< T_functor, T_return, T_arg1, T_arg2, T_arg3 >::address();
        }
        QExtFunction3(const QExtFunction3 &other) : QExtFunctionBase(other) {}

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
    class QExtFunction2 : public QExtFunctionBase
    {
    public:
        typedef T_return ResultType;
        typedef typename QExtTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QExtTypeTrait< T_arg2 >::Take Arg2;

        typedef T_return (*CallFunction)(const QSharedPointer< QExtFunctionData > &, Arg1, Arg2);

        QExtFunction2() {}
        template < typename T_functor >
        QExtFunction2(const T_functor &functor)
            : QExtFunctionBase(QSharedPointer< QExtFunctionData >(new QExtFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = detail::QExtFunctionCall2< T_functor, T_return, T_arg1, T_arg2 >::address();
        }
        QExtFunction2(const QExtFunction2 &other) : QExtFunctionBase(other) {}

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
    class QExtFunction1 : public QExtFunctionBase
    {
    public:
        typedef T_return ResultType;
        typedef typename QExtTypeTrait< T_arg1 >::Take Arg1;

        typedef T_return (*CallFunction)(const QSharedPointer< QExtFunctionData > &, Arg1);

        QExtFunction1() {}
        template < typename T_functor >
        QExtFunction1(const T_functor &functor)
            : QExtFunctionBase(QSharedPointer< QExtFunctionData >(new QExtFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = detail::QExtFunctionCall1< T_functor, T_return, T_arg1 >::address();
        }
        QExtFunction1(const QExtFunction1 &other) : QExtFunctionBase(other) {}

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
    class QExtFunction0 : public QExtFunctionBase
    {
    public:
        typedef T_return ResultType;

        typedef T_return (*CallFunction)(const QSharedPointer< QExtFunctionData > &);

        QExtFunction0() {}
        template < typename T_functor >
        QExtFunction0(const T_functor &functor)
            : QExtFunctionBase(QSharedPointer< QExtFunctionData >(new QExtFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = detail::QExtFunctionCall0< T_functor, T_return >::address();
        }
        QExtFunction0(const QExtFunction0 &other) : QExtFunctionBase(other) {}

        T_return operator()() const
        {
            if (this->isValid())
            {
                return (reinterpret_cast< CallFunction >(m_callFunc))(m_data);
            }
            return T_return();
        }
    };

} // namespace QExtPrivate

template <
    typename T_return,
    typename T_arg1 = QExtNil,
    typename T_arg2 = QExtNil,
    typename T_arg3 = QExtNil,
    typename T_arg4 = QExtNil,
    typename T_arg5 = QExtNil,
    typename T_arg6 = QExtNil,
    typename T_arg7 = QExtNil >
class QExtFunction : public detail::QExtFunction7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
public:
    typedef detail::QExtFunction7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > BaseType;

    QExtFunction() {}
    QExtFunction(T_return (*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7))
        : BaseType(QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(func))
    {
    }
    template < typename T_functor >
    QExtFunction(const T_functor &functor) : BaseType(functor)
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(
        T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(
        T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    QExtFunction(const QExtFunction &other) : BaseType(reinterpret_cast< const BaseType & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil >
    : public detail::QExtFunction6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
public:
    typedef detail::QExtFunction6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > BaseType;

    QExtFunction() {}
    QExtFunction(T_return (*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6))
        : BaseType(QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(func))
    {
    }
    template < typename T_functor >
    QExtFunction(const T_functor &functor) : BaseType(functor)
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    QExtFunction(const QExtFunction &other) : BaseType(reinterpret_cast< const BaseType & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil >
    : public detail::QExtFunction5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
public:
    typedef detail::QExtFunction5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > BaseType;

    QExtFunction() {}
    QExtFunction(T_return (*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5))
        : BaseType(QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(func))
    {
    }
    template < typename T_functor >
    QExtFunction(const T_functor &functor) : BaseType(functor)
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    QExtFunction(const QExtFunction &other) : BaseType(reinterpret_cast< const BaseType & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil >
    : public detail::QExtFunction4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >
{
public:
    typedef detail::QExtFunction4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 > BaseType;

    QExtFunction() {}
    QExtFunction(T_return (*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4))
        : BaseType(QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >(func))
    {
    }
    template < typename T_functor >
    QExtFunction(const T_functor &functor) : BaseType(functor)
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    QExtFunction(const QExtFunction &other) : BaseType(reinterpret_cast< const BaseType & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const
    {
        return BaseType::operator()(arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
class QExtFunction< T_return, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil > : public detail::QExtFunction3< T_return, T_arg1, T_arg2, T_arg3 >
{
public:
    typedef detail::QExtFunction3< T_return, T_arg1, T_arg2, T_arg3 > BaseType;

    QExtFunction() {}
    QExtFunction(T_return (*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3))
        : BaseType(QExtPointerFunctor< T_return, T_arg1, T_arg2, T_arg3 >(func))
    {
    }
    template < typename T_functor >
    QExtFunction(const T_functor &functor) : BaseType(functor)
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3))
        : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    QExtFunction(const QExtFunction &other) : BaseType(reinterpret_cast< const BaseType & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const
    {
        return BaseType::operator()(arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2 >
class QExtFunction< T_return, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public detail::QExtFunction2< T_return, T_arg1, T_arg2 >
{
public:
    typedef detail::QExtFunction2< T_return, T_arg1, T_arg2 > BaseType;

    QExtFunction() {}
    QExtFunction(T_return (*func)(T_arg1 arg1, T_arg2 arg2))
        : BaseType(QExtPointerFunctor< T_return, T_arg1, T_arg2 >(func))
    {
    }
    template < typename T_functor >
    QExtFunction(const T_functor &functor) : BaseType(functor)
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2)) : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2)) : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const)
        : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) volatile)
        : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    QExtFunction(const QExtFunction &other) : BaseType(reinterpret_cast< const BaseType & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2) const
    {
        return BaseType::operator()(arg1, arg2);
    }
};

template < typename T_return, typename T_arg1 >
class QExtFunction< T_return, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public detail::QExtFunction1< T_return, T_arg1 >
{
public:
    typedef detail::QExtFunction1< T_return, T_arg1 > BaseType;

    QExtFunction() {}
    QExtFunction(T_return (*func)(T_arg1 arg1))
        : BaseType(QExtPointerFunctor< T_return, T_arg1 >(func))
    {
    }
    template < typename T_functor >
    QExtFunction(const T_functor &functor) : BaseType(functor)
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1)) : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1)) : BaseType(QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) const) : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) const) : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) volatile) : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) volatile) : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) const volatile)
        : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    QExtFunction(const QExtFunction &other) : BaseType(reinterpret_cast< const BaseType & >(other)) {}

    T_return operator()(T_arg1 arg1) const
    {
        return BaseType::operator()(arg1);
    }
};

template <typename T_return>
class QExtFunction<T_return, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil> : public detail::QExtFunction0< T_return >
{
public:
    typedef detail::QExtFunction0< T_return > BaseType;

    QExtFunction() {}
    QExtFunction(T_return (*func)())
        : BaseType(QExtPointerFunctor< T_return >(func))
    {
    }
    template <typename T_functor>
    QExtFunction(const T_functor &functor) : BaseType(functor)
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)()) : BaseType(QExtBoundMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)()) : BaseType(QExtBoundMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)() const) : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)() const) : BaseType(QExtBoundConstMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)() volatile) : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)() volatile) : BaseType(QExtBoundVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj *obj, T_return (T_obj::*func)() const volatile) : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QExtFunction(T_obj &obj, T_return (T_obj::*func)() const volatile) : BaseType(QExtBoundConstVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    QExtFunction(const QExtFunction &other) : BaseType(reinterpret_cast< const BaseType & >(other)) {}

    T_return operator()() const
    {
        return BaseType::operator()();
    }
};

#endif // _QEXTFUNCTION_H
