/*************************************************************************************
**
** Library: CommonFramework
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
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

#ifndef _QEXTFUNCTION_H
#define _QEXTFUNCTION_H

#include <qextGlobal.h>
#include <qextAdaptorTrait.h>
#include <qextLimitReference.h>
#include <qextMemberFunctor.h>
#include <qextPointerFunctor.h>
#include <qextTypeTrait.h>

#include <QObject>
#include <QSharedPointer>

QT_WARNING_DISABLE_GCC("-Wcast-function-type")

namespace qextPrivate
{

    struct QEXTFunctionData
    {
        virtual ~QEXTFunctionData() {}
    };

    class QEXTFunctionBase
    {
    public:
        typedef void *(*HookFunction)(void *);

        QEXTFunctionBase() : m_callFunc(QEXT_DECL_NULLPTR) {}
        QEXTFunctionBase(const QSharedPointer< QEXTFunctionData > &data) : m_callFunc(QEXT_DECL_NULLPTR), m_data(data) {}
        QEXTFunctionBase(const QEXTFunctionBase &other) : m_callFunc(other.m_callFunc), m_data(other.m_data) {}
        virtual ~QEXTFunctionBase() {}

        bool isValid() const
        {
            return QEXT_DECL_NULLPTR != m_callFunc && !m_data.isNull();
        }

    protected:
        HookFunction m_callFunc;
        mutable QSharedPointer< QEXTFunctionData > m_data;
    };

    template < typename T_functor >
    struct QEXTFunctionFunctorData : public QEXTFunctionData
    {
        typedef QEXTFunctionFunctorData< T_functor > Self;
        typedef typename QEXTAdaptorTrait< T_functor >::Adaptor Adaptor;

        QEXTFunctionFunctorData(const T_functor &functor) : m_functor(functor) {}
        QEXTFunctionFunctorData(const QEXTFunctionFunctorData &other) : m_functor(other.m_functor) {}

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
    struct QEXTFunctionCall7
    {
        static T_return call(
            const QSharedPointer< QEXTFunctionData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6,
            typename QEXTTypeTrait< T_arg7 >::Take arg7)
        {
            typedef QEXTFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                .template operator()<
                    typename QEXTTypeTrait< T_arg1 >::Take,
                    typename QEXTTypeTrait< T_arg2 >::Take,
                    typename QEXTTypeTrait< T_arg3 >::Take,
                    typename QEXTTypeTrait< T_arg4 >::Take,
                    typename QEXTTypeTrait< T_arg5 >::Take,
                    typename QEXTTypeTrait< T_arg6 >::Take,
                    typename QEXTTypeTrait< T_arg7 >::Take >(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }

        static QEXTFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QEXTFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
    struct QEXTFunctionCall6
    {
        static T_return call(
            const QSharedPointer< QEXTFunctionData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5,
            typename QEXTTypeTrait< T_arg6 >::Take arg6)
        {
            typedef QEXTFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                .template operator()<
                    typename QEXTTypeTrait< T_arg1 >::Take,
                    typename QEXTTypeTrait< T_arg2 >::Take,
                    typename QEXTTypeTrait< T_arg3 >::Take,
                    typename QEXTTypeTrait< T_arg4 >::Take,
                    typename QEXTTypeTrait< T_arg5 >::Take,
                    typename QEXTTypeTrait< T_arg6 >::Take >(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        static QEXTFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QEXTFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
    struct QEXTFunctionCall5
    {
        static T_return call(
            const QSharedPointer< QEXTFunctionData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4,
            typename QEXTTypeTrait< T_arg5 >::Take arg5)
        {
            typedef QEXTFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                .template operator()<
                    typename QEXTTypeTrait< T_arg1 >::Take,
                    typename QEXTTypeTrait< T_arg2 >::Take,
                    typename QEXTTypeTrait< T_arg3 >::Take,
                    typename QEXTTypeTrait< T_arg4 >::Take,
                    typename QEXTTypeTrait< T_arg5 >::Take >(arg1, arg2, arg3, arg4, arg5);
        }

        static QEXTFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QEXTFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
    struct QEXTFunctionCall4
    {
        static T_return call(
            const QSharedPointer< QEXTFunctionData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg2 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3,
            typename QEXTTypeTrait< T_arg4 >::Take arg4)
        {
            typedef QEXTFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                .template operator()<
                    typename QEXTTypeTrait< T_arg1 >::Take,
                    typename QEXTTypeTrait< T_arg2 >::Take,
                    typename QEXTTypeTrait< T_arg3 >::Take,
                    typename QEXTTypeTrait< T_arg4 >::Take >(arg1, arg2, arg3, arg4);
        }

        static QEXTFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QEXTFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
    struct QEXTFunctionCall3
    {
        static T_return call(
            const QSharedPointer< QEXTFunctionData > &functionData,
            typename QEXTTypeTrait< T_arg1 >::Take arg1,
            typename QEXTTypeTrait< T_arg3 >::Take arg2,
            typename QEXTTypeTrait< T_arg3 >::Take arg3)
        {
            typedef QEXTFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                .template operator()< typename QEXTTypeTrait< T_arg1 >::Take, typename QEXTTypeTrait< T_arg2 >::Take, typename QEXTTypeTrait< T_arg3 >::Take >(
                    arg1, arg2, arg3);
        }

        static QEXTFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QEXTFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1, typename T_arg2 >
    struct QEXTFunctionCall2
    {
        static T_return
        call(const QSharedPointer< QEXTFunctionData > &functionData, typename QEXTTypeTrait< T_arg1 >::Take arg1, typename QEXTTypeTrait< T_arg2 >::Take arg2)
        {
            typedef QEXTFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)
                .template operator()< typename QEXTTypeTrait< T_arg1 >::Take, typename QEXTTypeTrait< T_arg2 >::Take >(arg1, arg2);
        }

        static QEXTFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QEXTFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return, typename T_arg1 >
    struct QEXTFunctionCall1
    {
        static T_return call(const QSharedPointer< QEXTFunctionData > &functionData, typename QEXTTypeTrait< T_arg1 >::Take arg1)
        {
            typedef QEXTFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor).template operator()< typename QEXTTypeTrait< T_arg1 >::Take >(arg1);
        }

        static QEXTFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QEXTFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_functor, typename T_return >
    struct QEXTFunctionCall0
    {
        static T_return call(const QSharedPointer< QEXTFunctionData > &functionData)
        {
            typedef QEXTFunctionFunctorData< T_functor > FunctionFunctorData;
            FunctionFunctorData *functionFunctorData = static_cast< FunctionFunctorData * >(functionData.data());
            return (functionFunctorData->m_functor)();
        }

        static QEXTFunctionBase::HookFunction address()
        {
            return reinterpret_cast< QEXTFunctionBase::HookFunction >(&call);
        }
    };

    template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
    class QEXTFunction7 : public QEXTFunctionBase
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

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTFunctionData > &, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7);

        QEXTFunction7() {}
        template < typename T_functor >
        QEXTFunction7(const T_functor &functor) : QEXTFunctionBase(QSharedPointer< QEXTFunctionData >(new QEXTFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTFunctionCall7< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >::address();
        }
        QEXTFunction7(const QEXTFunction7 &other) : QEXTFunctionBase(other) {}

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
    class QEXTFunction6 : public QEXTFunctionBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QEXTTypeTrait< T_arg4 >::Take Arg4;
        typedef typename QEXTTypeTrait< T_arg5 >::Take Arg5;
        typedef typename QEXTTypeTrait< T_arg6 >::Take Arg6;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTFunctionData > &, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6);

        QEXTFunction6() {}
        template < typename T_functor >
        QEXTFunction6(const T_functor &functor) : QEXTFunctionBase(QSharedPointer< QEXTFunctionData >(new QEXTFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTFunctionCall6< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >::address();
        }
        QEXTFunction6(const QEXTFunction6 &other) : QEXTFunctionBase(other) {}

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
    class QEXTFunction5 : public QEXTFunctionBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QEXTTypeTrait< T_arg4 >::Take Arg4;
        typedef typename QEXTTypeTrait< T_arg5 >::Take Arg5;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTFunctionData > &, Arg1, Arg2, Arg3, Arg4, Arg5);

        QEXTFunction5() {}
        template < typename T_functor >
        QEXTFunction5(const T_functor &functor) : QEXTFunctionBase(QSharedPointer< QEXTFunctionData >(new QEXTFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTFunctionCall5< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >::address();
        }
        QEXTFunction5(const QEXTFunction5 &other) : QEXTFunctionBase(other) {}

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
    class QEXTFunction4 : public QEXTFunctionBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;
        typedef typename QEXTTypeTrait< T_arg4 >::Take Arg4;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTFunctionData > &, Arg1, Arg2, Arg3, Arg4);

        QEXTFunction4() {}
        template < typename T_functor >
        QEXTFunction4(const T_functor &functor) : QEXTFunctionBase(QSharedPointer< QEXTFunctionData >(new QEXTFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTFunctionCall4< T_functor, T_return, T_arg1, T_arg2, T_arg3, T_arg4 >::address();
        }
        QEXTFunction4(const QEXTFunction4 &other) : QEXTFunctionBase(other) {}

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
    class QEXTFunction3 : public QEXTFunctionBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;
        typedef typename QEXTTypeTrait< T_arg3 >::Take Arg3;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTFunctionData > &, Arg1, Arg2, Arg3);

        QEXTFunction3() {}
        template < typename T_functor >
        QEXTFunction3(const T_functor &functor) : QEXTFunctionBase(QSharedPointer< QEXTFunctionData >(new QEXTFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTFunctionCall3< T_functor, T_return, T_arg1, T_arg2, T_arg3 >::address();
        }
        QEXTFunction3(const QEXTFunction3 &other) : QEXTFunctionBase(other) {}

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
    class QEXTFunction2 : public QEXTFunctionBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;
        typedef typename QEXTTypeTrait< T_arg2 >::Take Arg2;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTFunctionData > &, Arg1, Arg2);

        QEXTFunction2() {}
        template < typename T_functor >
        QEXTFunction2(const T_functor &functor) : QEXTFunctionBase(QSharedPointer< QEXTFunctionData >(new QEXTFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTFunctionCall2< T_functor, T_return, T_arg1, T_arg2 >::address();
        }
        QEXTFunction2(const QEXTFunction2 &other) : QEXTFunctionBase(other) {}

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
    class QEXTFunction1 : public QEXTFunctionBase
    {
    public:
        typedef T_return Return;
        typedef typename QEXTTypeTrait< T_arg1 >::Take Arg1;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTFunctionData > &, Arg1);

        QEXTFunction1() {}
        template < typename T_functor >
        QEXTFunction1(const T_functor &functor) : QEXTFunctionBase(QSharedPointer< QEXTFunctionData >(new QEXTFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTFunctionCall1< T_functor, T_return, T_arg1 >::address();
        }
        QEXTFunction1(const QEXTFunction1 &other) : QEXTFunctionBase(other) {}

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
    class QEXTFunction0 : public QEXTFunctionBase
    {
    public:
        typedef T_return Return;

        typedef T_return (*CallFunction)(const QSharedPointer< QEXTFunctionData > &);

        QEXTFunction0() {}
        template < typename T_functor >
        QEXTFunction0(const T_functor &functor) : QEXTFunctionBase(QSharedPointer< QEXTFunctionData >(new QEXTFunctionFunctorData< T_functor >(functor)))
        {
            m_callFunc = qextPrivate::QEXTFunctionCall0< T_functor, T_return >::address();
        }
        QEXTFunction0(const QEXTFunction0 &other) : QEXTFunctionBase(other) {}

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
class QEXTFunction : public qextPrivate::QEXTFunction7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >
{
public:
    typedef qextPrivate::QEXTFunction7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 > Base;

    QEXTFunction() {}
    template < typename T_functor >
    QEXTFunction(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func))
    {
    }
    QEXTFunction(const QEXTFunction &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QEXTFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil >
    : public qextPrivate::QEXTFunction6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >
{
public:
    typedef qextPrivate::QEXTFunction6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 > Base;

    QEXTFunction() {}
    template < typename T_functor >
    QEXTFunction(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func))
    {
    }
    QEXTFunction(const QEXTFunction &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QEXTFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil >
    : public qextPrivate::QEXTFunction5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >
{
public:
    typedef qextPrivate::QEXTFunction5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 > Base;

    QEXTFunction() {}
    template < typename T_functor >
    QEXTFunction(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func))
    {
    }
    QEXTFunction(const QEXTFunction &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4, arg5);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QEXTFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTFunction4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >
{
public:
    typedef qextPrivate::QEXTFunction4< T_return, T_arg1, T_arg2, T_arg3, T_arg4 > Base;

    QEXTFunction() {}
    template < typename T_functor >
    QEXTFunction(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func))
    {
    }
    QEXTFunction(const QEXTFunction &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4) const
    {
        return Base::operator()(arg1, arg2, arg3, arg4);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
class QEXTFunction< T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTFunction3< T_return, T_arg1, T_arg2, T_arg3 >
{
public:
    typedef qextPrivate::QEXTFunction3< T_return, T_arg1, T_arg2, T_arg3 > Base;

    QEXTFunction() {}
    template < typename T_functor >
    QEXTFunction(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3))
        : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func))
    {
    }
    QEXTFunction(const QEXTFunction &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3) const
    {
        return Base::operator()(arg1, arg2, arg3);
    }
};

template < typename T_return, typename T_arg1, typename T_arg2 >
class QEXTFunction< T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTFunction2< T_return, T_arg1, T_arg2 >
{
public:
    typedef qextPrivate::QEXTFunction2< T_return, T_arg1, T_arg2 > Base;

    QEXTFunction() {}
    template < typename T_functor >
    QEXTFunction(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2)) : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2)) : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const)
        : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) volatile)
        : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1, T_arg2 arg2) const volatile)
        : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func))
    {
    }
    QEXTFunction(const QEXTFunction &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1, T_arg2 arg2) const
    {
        return Base::operator()(arg1, arg2);
    }
};

template < typename T_return, typename T_arg1 >
class QEXTFunction< T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTFunction1< T_return, T_arg1 >
{
public:
    typedef qextPrivate::QEXTFunction1< T_return, T_arg1 > Base;

    QEXTFunction() {}
    template < typename T_functor >
    QEXTFunction(const T_functor &functor) : Base(functor)
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1)) : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1)) : Base(QEXTBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) const) : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) const) : Base(QEXTBoundConstMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) volatile) : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) volatile) : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)(T_arg1 arg1) const volatile) : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)(T_arg1 arg1) const volatile) : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj, T_arg1 >(obj, func))
    {
    }
    QEXTFunction(const QEXTFunction &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()(T_arg1 arg1) const
    {
        return Base::operator()(arg1);
    }
};

template < typename T_return >
class QEXTFunction< T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil > : public qextPrivate::QEXTFunction0< T_return >
{
public:
    typedef qextPrivate::QEXTFunction0< T_return > Base;

    QEXTFunction() {}
    template < typename T_functor >
    QEXTFunction(const T_functor &functor) : Base(functor)
    {
    }
    QEXTFunction(T_return (*func)()) : Base(QEXTPointerFunctor< T_return >(func)) {}
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)()) : Base(QEXTBoundMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)()) : Base(QEXTBoundMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)() const) : Base(QEXTBoundConstMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)() const) : Base(QEXTBoundConstMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)() volatile) : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)() volatile) : Base(QEXTBoundVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj *obj, T_return (T_obj::*func)() const volatile) : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    template < typename T_obj >
    QEXTFunction(T_obj &obj, T_return (T_obj::*func)() const volatile) : Base(QEXTBoundConstVolatileMemberFunctor< T_return, T_obj >(obj, func))
    {
    }
    QEXTFunction(const QEXTFunction &other) : Base(reinterpret_cast< const Base & >(other)) {}

    T_return operator()() const
    {
        return Base::operator()();
    }
};



#endif // _QEXTFUNCTION_H
