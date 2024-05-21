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

#ifndef _QEXTTRACKOBJECTFUNCTOR_H
#define _QEXTTRACKOBJECTFUNCTOR_H

#include <qextAdaptorTrait.h>
#include <qextLimitReference.h>


namespace detail
{

    /** @defgroup qextTrackObjectFunctor qextTrackObjectFunctor()
     * qextTrackObjectFunctor() tracks trackable objects, referenced from a functor.
     * It can be useful when you assign a C++11 lambda expression or a std::function<>
     * to a slot, or connect it to a signal, and the lambda expression or std::function<>
     * contains references to trackable derived objects.
     *
     * The functor returned by qextTrackObjectFunctor() is formally an adaptor, but it does
     * not alter the signature, return type or behaviour of the supplied functor.
     * Up to 7 objects can be tracked. operator()() can have up to 7 arguments.
     *
     * @par Example:
     * @code
     * QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE
     * struct bar : public QObject {};
     * QExtSignal<void> some_signal;
     * void foo(bar&);
     * {
     *   bar some_bar;
     *   some_signal.connect([&some_bar](){ foo(some_bar); });
     *     // NOT disconnected automatically when some_bar goes out of scope
     *   some_signal.connect(qextTrackObjectFunctor([&some_bar](){ foo(some_bar); }, some_bar);
     *     // disconnected automatically when some_bar goes out of scope
     * }
     * @endcode
     *
     * @newin{2,4}
     *
     * \ingroup adaptors
     */

    /** QExtTrackObjectFunctorBase wraps a functor and stores a reference to a trackable object.
     * Use the convenience function qextTrackObjectFunctor() to create an instance of QExtTrackObjectFunctorBase.
     *
     * @tparam T_functor The type of functor to wrap.
     * @tparam T_obj1 The type of a trackable object.
     *
     * @newin{2,4}
     *
     * \ingroup qextTrackObjectFunctor
     */
    template<typename T_functor>
    class QExtTrackObjectFunctorBase : public QExtAdapts<T_functor>
    {
    public:
        typedef typename QExtAdapts<T_functor>::Adaptor Adaptor;

        template<
                typename T_arg1 = void,
                typename T_arg2 = void,
                typename T_arg3 = void,
                typename T_arg4 = void,
                typename T_arg5 = void,
                typename T_arg6 = void,
                typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef typename Adaptor::template ReturnTypeDeduce<
                    typename QExtTypeTrait<T_arg1>::Pass,
                    typename QExtTypeTrait<T_arg2>::Pass,
                    typename QExtTypeTrait<T_arg3>::Pass,
                    typename QExtTypeTrait<T_arg4>::Pass,
                    typename QExtTypeTrait<T_arg5>::Pass,
                    typename QExtTypeTrait<T_arg6>::Pass,
                    typename QExtTypeTrait<T_arg7>::Pass>::Type Type;
        };

        typedef typename Adaptor::Return Return;

        /** Constructs a QExtTrackObjectFunctorBase object that wraps the passed functor and
         * stores a reference to the passed trackable object.
         * \param func Functor.
         * \param obj1 Trackable object.
         */
        QExtTrackObjectFunctorBase(const T_functor &func) : QExtAdapts<T_functor>(func) {}

        /** Invokes the wrapped functor.
         * \return The return value of the functor invocation.
         */
        Return operator()()
        {
            return this->m_functor();
        }

        /** Invokes the wrapped functor passing on the arguments.
         * \param arg1 Argument to be passed on to the functor.
         * \return The return value of the functor invocation.
         */
        template<typename T_arg1>
        typename ReturnTypeDeduce<T_arg1>::Type operator()(T_arg1 arg1)
        {
            return this->m_functor.template operator()<typename QExtTypeTrait<T_arg1>::Pass>(arg1);
        }

        /** Invokes the wrapped functor passing on the arguments.
         * \param arg1 Argument to be passed on to the functor.
         * \param arg2 Argument to be passed on to the functor.
         * \return The return value of the functor invocation.
         */
        template<typename T_arg1, typename T_arg2>
        typename ReturnTypeDeduce<T_arg1, T_arg2>::Type operator()(T_arg1 arg1, T_arg2 arg2)
        {
            return this->m_functor.template operator()<typename QExtTypeTrait<T_arg1>::Pass, typename QExtTypeTrait<T_arg2>::Pass>(
                    arg1, arg2);
        }

        /** Invokes the wrapped functor passing on the arguments.
         * \param arg1 Argument to be passed on to the functor.
         * \param arg2 Argument to be passed on to the functor.
         * \param arg3 Argument to be passed on to the functor.
         * \return The return value of the functor invocation.
         */
        template<typename T_arg1, typename T_arg2, typename T_arg3>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3>::Type operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3)
        {
            return this->m_functor.template
                    operator()<typename QExtTypeTrait<T_arg1>::Pass, typename QExtTypeTrait<T_arg2>::Pass, typename QExtTypeTrait<T_arg3>::Pass>(
                    arg1, arg2, arg3);
        }

        /** Invokes the wrapped functor passing on the arguments.
         * \param arg1 Argument to be passed on to the functor.
         * \param arg2 Argument to be passed on to the functor.
         * \param arg3 Argument to be passed on to the functor.
         * \param arg4 Argument to be passed on to the functor.
         * \return The return value of the functor invocation.
         */
        template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4>::Type
        operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4)
        {
            return this->m_functor.template operator()<
                    typename QExtTypeTrait<T_arg1>::Pass,
                    typename QExtTypeTrait<T_arg2>::Pass,
                    typename QExtTypeTrait<T_arg3>::Pass,
                    typename QExtTypeTrait<T_arg4>::Pass>(arg1, arg2, arg3, arg4);
        }

        /** Invokes the wrapped functor passing on the arguments.
         * \param arg1 Argument to be passed on to the functor.
         * \param arg2 Argument to be passed on to the functor.
         * \param arg3 Argument to be passed on to the functor.
         * \param arg4 Argument to be passed on to the functor.
         * \param arg5 Argument to be passed on to the functor.
         * \return The return value of the functor invocation.
         */
        template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>::Type
        operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5)
        {
            return this->m_functor.template operator()<
                    typename QExtTypeTrait<T_arg1>::Pass,
                    typename QExtTypeTrait<T_arg2>::Pass,
                    typename QExtTypeTrait<T_arg3>::Pass,
                    typename QExtTypeTrait<T_arg4>::Pass,
                    typename QExtTypeTrait<T_arg5>::Pass>(arg1, arg2, arg3, arg4, arg5);
        }

        /** Invokes the wrapped functor passing on the arguments.
         * \param arg1 Argument to be passed on to the functor.
         * \param arg2 Argument to be passed on to the functor.
         * \param arg3 Argument to be passed on to the functor.
         * \param arg4 Argument to be passed on to the functor.
         * \param arg5 Argument to be passed on to the functor.
         * \param arg6 Argument to be passed on to the functor.
         * \return The return value of the functor invocation.
         */
        template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>::Type
        operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6)
        {
            return this->m_functor.template operator()<
                    typename QExtTypeTrait<T_arg1>::Pass,
                    typename QExtTypeTrait<T_arg2>::Pass,
                    typename QExtTypeTrait<T_arg3>::Pass,
                    typename QExtTypeTrait<T_arg4>::Pass,
                    typename QExtTypeTrait<T_arg5>::Pass,
                    typename QExtTypeTrait<T_arg6>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6);
        }

        /** Invokes the wrapped functor passing on the arguments.
         * \param arg1 Argument to be passed on to the functor.
         * \param arg2 Argument to be passed on to the functor.
         * \param arg3 Argument to be passed on to the functor.
         * \param arg4 Argument to be passed on to the functor.
         * \param arg5 Argument to be passed on to the functor.
         * \param arg6 Argument to be passed on to the functor.
         * \param arg7 Argument to be passed on to the functor.
         * \return The return value of the functor invocation.
         */
        template<typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        typename ReturnTypeDeduce<T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>::Type
        operator()(T_arg1 arg1, T_arg2 arg2, T_arg3 arg3, T_arg4 arg4, T_arg5 arg5, T_arg6 arg6, T_arg7 arg7)
        {
            return this->m_functor.template operator()<
                    typename QExtTypeTrait<T_arg1>::Pass,
                    typename QExtTypeTrait<T_arg2>::Pass,
                    typename QExtTypeTrait<T_arg3>::Pass,
                    typename QExtTypeTrait<T_arg4>::Pass,
                    typename QExtTypeTrait<T_arg5>::Pass,
                    typename QExtTypeTrait<T_arg6>::Pass,
                    typename QExtTypeTrait<T_arg7>::Pass>(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
    };

    /** QExtTrackObjectFunctor2 wraps a functor and stores 2 references to trackable objects.
     * Use the convenience function qextTrackObjectFunctor() to create an instance of QExtTrackObjectFunctor2.
     *
     * @tparam T_functor The type of functor to wrap.
     * @tparam T_obj1 The type of a trackable object.
     * @tparam T_obj2 The type of a trackable object.
     *
     * @newin{2,4}
     *
     * \ingroup qextTrackObjectFunctor
     */
    template<typename T_functor, typename T_obj1>
    class QExtTrackObjectFunctor1 : public QExtTrackObjectFunctorBase<T_functor>
    {
    public:
        /** Constructs a QExtTrackObjectFunctor2 object that wraps the passed functor and
         * stores references to the passed trackable objects.
         * \param func Functor.
         * \param obj1 Trackable object.
         * \param obj2 Trackable object.
         */
        QExtTrackObjectFunctor1(const T_functor &func, const T_obj1 &obj1) : QExtTrackObjectFunctorBase<T_functor>(func)
                                                                             , m_obj1(obj1) {}

        QExtConstLimitReference<T_obj1> m_obj1;
    };

    /** QExtTrackObjectFunctor2 wraps a functor and stores 2 references to trackable objects.
     * Use the convenience function qextTrackObjectFunctor() to create an instance of QExtTrackObjectFunctor2.
     *
     * @tparam T_functor The type of functor to wrap.
     * @tparam T_obj1 The type of a trackable object.
     * @tparam T_obj2 The type of a trackable object.
     *
     * @newin{2,4}
     *
     * \ingroup qextTrackObjectFunctor
     */
    template<typename T_functor, typename T_obj1, typename T_obj2>
    class QExtTrackObjectFunctor2 : public QExtTrackObjectFunctorBase<T_functor>
    {
    public:
        /** Constructs a QExtTrackObjectFunctor2 object that wraps the passed functor and
         * stores references to the passed trackable objects.
         * \param func Functor.
         * \param obj1 Trackable object.
         * \param obj2 Trackable object.
         */
        QExtTrackObjectFunctor2(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2)
                : QExtTrackObjectFunctorBase<T_functor>(func), m_obj1(obj1), m_obj2(obj2)
        {
        }

        QExtConstLimitReference<T_obj1> m_obj1;
        QExtConstLimitReference<T_obj2> m_obj2;
    };

    /** QExtTrackObjectFunctor3 wraps a functor and stores 3 references to trackable objects.
     * Use the convenience function qextTrackObjectFunctor() to create an instance of QExtTrackObjectFunctor3.
     *
     * @tparam T_functor The type of functor to wrap.
     * @tparam T_obj1 The type of a trackable object.
     * @tparam T_obj2 The type of a trackable object.
     * @tparam T_obj3 The type of a trackable object.
     *
     * @newin{2,4}
     *
     * \ingroup qextTrackObjectFunctor
     */
    template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3>
    class QExtTrackObjectFunctor3 : public QExtTrackObjectFunctorBase<T_functor>
    {
    public:
        /** Constructs a QExtTrackObjectFunctor3 object that wraps the passed functor and
         * stores references to the passed trackable objects.
         * \param func Functor.
         * \param obj1 Trackable object.
         * \param obj2 Trackable object.
         * \param obj3 Trackable object.
         */
        QExtTrackObjectFunctor3(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3)
                : QExtTrackObjectFunctorBase<T_functor>(func), m_obj1(obj1), m_obj2(obj2), m_obj3(obj3)
        {
        }

        QExtConstLimitReference<T_obj1> m_obj1;
        QExtConstLimitReference<T_obj2> m_obj2;
        QExtConstLimitReference<T_obj3> m_obj3;
    };

    /** QExtTrackObjectFunctor4 wraps a functor and stores 4 references to trackable objects.
     * Use the convenience function qextTrackObjectFunctor() to create an instance of QExtTrackObjectFunctor4.
     *
     * @tparam T_functor The type of functor to wrap.
     * @tparam T_obj1 The type of a trackable object.
     * @tparam T_obj2 The type of a trackable object.
     * @tparam T_obj3 The type of a trackable object.
     * @tparam T_obj4 The type of a trackable object.
     *
     * @newin{2,4}
     *
     * \ingroup qextTrackObjectFunctor
     */
    template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4>
    class QExtTrackObjectFunctor4 : public QExtTrackObjectFunctorBase<T_functor>
    {
    public:
        /** Constructs a QExtTrackObjectFunctor4 object that wraps the passed functor and
         * stores references to the passed trackable objects.
         * \param func Functor.
         * \param obj1 Trackable object.
         * \param obj2 Trackable object.
         * \param obj3 Trackable object.
         * \param obj4 Trackable object.
         */
        QExtTrackObjectFunctor4(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3,
                                const T_obj4 &obj4)
                : QExtTrackObjectFunctorBase<T_functor>(func), m_obj1(obj1), m_obj2(obj2), m_obj3(obj3), m_obj4(obj4)
        {
        }

        QExtConstLimitReference<T_obj1> m_obj1;
        QExtConstLimitReference<T_obj2> m_obj2;
        QExtConstLimitReference<T_obj3> m_obj3;
        QExtConstLimitReference<T_obj4> m_obj4;
    };

    /** QExtTrackObjectFunctor5 wraps a functor and stores 5 references to trackable objects.
     * Use the convenience function qextTrackObjectFunctor() to create an instance of QExtTrackObjectFunctor5.
     *
     * @tparam T_functor The type of functor to wrap.
     * @tparam T_obj1 The type of a trackable object.
     * @tparam T_obj2 The type of a trackable object.
     * @tparam T_obj3 The type of a trackable object.
     * @tparam T_obj4 The type of a trackable object.
     * @tparam T_obj5 The type of a trackable object.
     *
     * @newin{2,4}
     *
     * \ingroup qextTrackObjectFunctor
     */
    template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5>
    class QExtTrackObjectFunctor5 : public QExtTrackObjectFunctorBase<T_functor>
    {
    public:
        /** Constructs a QExtTrackObjectFunctor5 object that wraps the passed functor and
         * stores references to the passed trackable objects.
         * \param func Functor.
         * \param obj1 Trackable object.
         * \param obj2 Trackable object.
         * \param obj3 Trackable object.
         * \param obj4 Trackable object.
         * \param obj5 Trackable object.
         */
        QExtTrackObjectFunctor5(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3,
                                const T_obj4 &obj4, const T_obj5 &obj5)
                : QExtTrackObjectFunctorBase<T_functor>(func), m_obj1(obj1), m_obj2(obj2), m_obj3(obj3), m_obj4(obj4)
                  , m_obj5(obj5)
        {
        }

        QExtConstLimitReference<T_obj1> m_obj1;
        QExtConstLimitReference<T_obj2> m_obj2;
        QExtConstLimitReference<T_obj3> m_obj3;
        QExtConstLimitReference<T_obj4> m_obj4;
        QExtConstLimitReference<T_obj5> m_obj5;
    };

    /** QExtTrackObjectFunctor6 wraps a functor and stores 6 references to trackable objects.
     * Use the convenience function qextTrackObjectFunctor() to create an instance of QExtTrackObjectFunctor6.
     *
     * @tparam T_functor The type of functor to wrap.
     * @tparam T_obj1 The type of a trackable object.
     * @tparam T_obj2 The type of a trackable object.
     * @tparam T_obj3 The type of a trackable object.
     * @tparam T_obj4 The type of a trackable object.
     * @tparam T_obj5 The type of a trackable object.
     * @tparam T_obj6 The type of a trackable object.
     *
     * @newin{2,4}
     *
     * \ingroup qextTrackObjectFunctor
     */
    template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6>
    class QExtTrackObjectFunctor6 : public QExtTrackObjectFunctorBase<T_functor>
    {
    public:
        /** Constructs a QExtTrackObjectFunctor6 object that wraps the passed functor and
         * stores references to the passed trackable objects.
         * \param func Functor.
         * \param obj1 Trackable object.
         * \param obj2 Trackable object.
         * \param obj3 Trackable object.
         * \param obj4 Trackable object.
         * \param obj5 Trackable object.
         * \param obj6 Trackable object.
         */
        QExtTrackObjectFunctor6(
                const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4,
                const T_obj5 &obj5, const T_obj6 &obj6)
                : QExtTrackObjectFunctorBase<T_functor>(func), m_obj1(obj1), m_obj2(obj2), m_obj3(obj3), m_obj4(obj4)
                  , m_obj5(obj5), m_obj6(obj6)
        {
        }

        QExtConstLimitReference<T_obj1> m_obj1;
        QExtConstLimitReference<T_obj2> m_obj2;
        QExtConstLimitReference<T_obj3> m_obj3;
        QExtConstLimitReference<T_obj4> m_obj4;
        QExtConstLimitReference<T_obj5> m_obj5;
        QExtConstLimitReference<T_obj6> m_obj6;
    };

    /** QExtTrackObjectFunctor7 wraps a functor and stores 7 references to trackable objects.
     * Use the convenience function qextTrackObjectFunctor() to create an instance of QExtTrackObjectFunctor7.
     *
     * @tparam T_functor The type of functor to wrap.
     * @tparam T_obj1 The type of a trackable object.
     * @tparam T_obj2 The type of a trackable object.
     * @tparam T_obj3 The type of a trackable object.
     * @tparam T_obj4 The type of a trackable object.
     * @tparam T_obj5 The type of a trackable object.
     * @tparam T_obj6 The type of a trackable object.
     * @tparam T_obj7 The type of a trackable object.
     *
     * @newin{2,4}
     *
     * \ingroup qextTrackObjectFunctor
     */
    template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6, typename T_obj7>
    class QExtTrackObjectFunctor7 : public QExtTrackObjectFunctorBase<T_functor>
    {
    public:
        /** Constructs a QExtTrackObjectFunctor7 object that wraps the passed functor and
         * stores references to the passed trackable objects.
         * \param func Functor.
         * \param obj1 Trackable object.
         * \param obj2 Trackable object.
         * \param obj3 Trackable object.
         * \param obj4 Trackable object.
         * \param obj5 Trackable object.
         * \param obj6 Trackable object.
         * \param obj7 Trackable object.
         */
        QExtTrackObjectFunctor7(
                const T_functor &func,
                const T_obj1 &obj1,
                const T_obj2 &obj2,
                const T_obj3 &obj3,
                const T_obj4 &obj4,
                const T_obj5 &obj5,
                const T_obj6 &obj6,
                const T_obj7 &obj7)
                : QExtTrackObjectFunctorBase<T_functor>(func), m_obj1(obj1), m_obj2(obj2), m_obj3(obj3), m_obj4(obj4)
                  , m_obj5(obj5), m_obj6(obj6), m_obj7(obj7)
        {
        }

        QExtTrackObjectFunctor7(const QExtTrackObjectFunctor7 &other)
                : QExtTrackObjectFunctorBase<T_functor>(other.m_functor)
                  , m_obj1(other.m_obj1)
                  , m_obj2(other.m_obj2)
                  , m_obj3(other.m_obj3)
                  , m_obj4(other.m_obj4)
                  , m_obj5(other.m_obj5)
                  , m_obj6(other.m_obj6)
                  , m_obj7(other.m_obj7)
        {
        }

        QExtConstLimitReference<T_obj1> m_obj1;
        QExtConstLimitReference<T_obj2> m_obj2;
        QExtConstLimitReference<T_obj3> m_obj3;
        QExtConstLimitReference<T_obj4> m_obj4;
        QExtConstLimitReference<T_obj5> m_obj5;
        QExtConstLimitReference<T_obj6> m_obj6;
        QExtConstLimitReference<T_obj7> m_obj7;
    };

} // namespace QExtPrivate

template<
        typename T_functor,
        typename T_obj1,
        typename T_obj2 = QExtNil,
        typename T_obj3 = QExtNil,
        typename T_obj4 = QExtNil,
        typename T_obj5 = QExtNil,
        typename T_obj6 = QExtNil,
        typename T_obj7 = QExtNil>
class QExtTrackObjectFunctor
        : public detail::QExtTrackObjectFunctor7<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7>
{
public:
    typedef detail::QExtTrackObjectFunctor7<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7> Base;
    typedef typename Base::Return Return;

    QExtTrackObjectFunctor(
            const T_functor &func,
            const T_obj1 &obj1,
            const T_obj2 &obj2,
            const T_obj3 &obj3,
            const T_obj4 &obj4,
            const T_obj5 &obj5,
            const T_obj6 &obj6,
            const T_obj7 &obj7)
            : Base(func, obj1, obj2, obj3, obj4, obj5, obj6, obj7)
    {
    }

    QExtTrackObjectFunctor(const QExtTrackObjectFunctor &other) : Base(other) {}
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtTrackObjectFunctor7 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QExtTrackObjectFunctor7 object.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6, typename T_obj7>
struct QExtVisitor<QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
        qextVisitEach(action, target.m_obj4);
        qextVisitEach(action, target.m_obj5);
        qextVisitEach(action, target.m_obj6);
        qextVisitEach(action, target.m_obj7);
    }
};

template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6>
class QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, QExtNil>
        : public detail::QExtTrackObjectFunctor6<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6>
{
public:
    typedef detail::QExtTrackObjectFunctor6<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6> Base;
    typedef typename Base::Return Return;

    QExtTrackObjectFunctor(
            const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4,
            const T_obj5 &obj5, const T_obj6 &obj6)
            : Base(func, obj1, obj2, obj3, obj4, obj5, obj6)
    {
    }

    QExtTrackObjectFunctor(const QExtTrackObjectFunctor &other) : Base(other) {}
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtTrackObjectFunctor6 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QExtTrackObjectFunctor6 object.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6>
struct QExtVisitor<QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
        qextVisitEach(action, target.m_obj4);
        qextVisitEach(action, target.m_obj5);
        qextVisitEach(action, target.m_obj6);
    }
};

template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5>
class QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, QExtNil, QExtNil>
        : public detail::QExtTrackObjectFunctor5<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5>
{
public:
    typedef detail::QExtTrackObjectFunctor5<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5> Base;
    typedef typename Base::Return Return;

    QExtTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3,
                           const T_obj4 &obj4, const T_obj5 &obj5)
            : Base(func, obj1, obj2, obj3, obj4, obj5)
    {
    }

    QExtTrackObjectFunctor(const QExtTrackObjectFunctor &other) : Base(other) {}
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtTrackObjectFunctor5 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QExtTrackObjectFunctor5 object.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5>
struct QExtVisitor<QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action,
                            const QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
        qextVisitEach(action, target.m_obj4);
        qextVisitEach(action, target.m_obj5);
    }
};

template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4>
class QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, QExtNil, QExtNil, QExtNil>
        : public detail::QExtTrackObjectFunctor4<T_functor, T_obj1, T_obj2, T_obj3, T_obj4>
{
public:
    typedef detail::QExtTrackObjectFunctor4<T_functor, T_obj1, T_obj2, T_obj3, T_obj4> Base;
    typedef typename Base::Return Return;

    QExtTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3,
                           const T_obj4 &obj4)
            : Base(func, obj1, obj2, obj3, obj4)
    {
    }

    QExtTrackObjectFunctor(const QExtTrackObjectFunctor &other) : Base(other) {}
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtTrackObjectFunctor4 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QExtTrackObjectFunctor4 object.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4>
struct QExtVisitor<QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
        qextVisitEach(action, target.m_obj4);
    }
};

template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3>
class QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtTrackObjectFunctor3<T_functor, T_obj1, T_obj2, T_obj3>
{
public:
    typedef detail::QExtTrackObjectFunctor3<T_functor, T_obj1, T_obj2, T_obj3> Base;
    typedef typename Base::Return Return;

    QExtTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3) : Base(
            func, obj1, obj2, obj3) {}

    QExtTrackObjectFunctor(const QExtTrackObjectFunctor &other) : Base(other) {}
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtTrackObjectFunctor3 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QExtTrackObjectFunctor3 object.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3>
struct QExtVisitor<QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3> >
{
    template<typename T_action>
    static void
    doVisitEach(const T_action &action, const QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
        qextVisitEach(action, target.m_obj3);
    }
};

template<typename T_functor, typename T_obj1, typename T_obj2>
class QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtTrackObjectFunctor2<T_functor, T_obj1, T_obj2>
{
public:
    typedef detail::QExtTrackObjectFunctor2<T_functor, T_obj1, T_obj2> Base;
    typedef typename Base::Return Return;

    QExtTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2) : Base(func, obj1, obj2) {}

    QExtTrackObjectFunctor(const QExtTrackObjectFunctor &other) : Base(other) {}
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtTrackObjectFunctor2 performs a functor
 * on the functor and on the trackable object instances stored in the
 * QExtTrackObjectFunctor2 object.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2>
struct QExtVisitor<QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
        qextVisitEach(action, target.m_obj2);
    }
};

template<typename T_functor, typename T_obj1>
class QExtTrackObjectFunctor<T_functor, T_obj1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil>
        : public detail::QExtTrackObjectFunctor1<T_functor, T_obj1>
{
public:
    typedef detail::QExtTrackObjectFunctor1<T_functor, T_obj1> Base;
    typedef typename Base::Return Return;

    QExtTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1) : Base(func, obj1) {}

    QExtTrackObjectFunctor(const QExtTrackObjectFunctor &other) : Base(other) {}
};

//template specialization of QExtVisitor<>::doVisitEach<>(action, functor):
/** Performs a functor on each of the targets of a functor.
 * The function overload for QExtTrackObjectFunctorBase performs a functor
 * on the functor and on the trackable object instances stored in the
 * QExtTrackObjectFunctorBase object.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1>
struct QExtVisitor<QExtTrackObjectFunctor<T_functor, T_obj1> >
{
    template<typename T_action>
    static void doVisitEach(const T_action &action, const QExtTrackObjectFunctor<T_functor, T_obj1> &target)
    {
        qextVisitEach(action, target.m_functor);
        qextVisitEach(action, target.m_obj1);
    }
};

/** Creates an adaptor of type QExtTrackObjectFunctor7 which wraps a functor.
 * \param func Functor that shall be wrapped.
 * \param obj1 Trackable object.
 * \param obj2 Trackable object.
 * \param obj3 Trackable object.
 * \param obj4 Trackable object.
 * \param obj5 Trackable object.
 * \param obj6 Trackable object.
 * \param obj7 Trackable object.
 * \return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6, typename T_obj7>
inline QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7> qextTrackObjectFunctor(
        const T_functor &func,
        const T_obj1 &obj1,
        const T_obj2 &obj2,
        const T_obj3 &obj3,
        const T_obj4 &obj4,
        const T_obj5 &obj5,
        const T_obj6 &obj6,
        const T_obj7 &obj7)
{
    return QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6, T_obj7>(func, obj1, obj2,
                                                                                                     obj3, obj4, obj5,
                                                                                                     obj6, obj7);
}

/** Creates an adaptor of type QExtTrackObjectFunctor6 which wraps a functor.
 * \param func Functor that shall be wrapped.
 * \param obj1 Trackable object.
 * \param obj2 Trackable object.
 * \param obj3 Trackable object.
 * \param obj4 Trackable object.
 * \param obj5 Trackable object.
 * \param obj6 Trackable object.
 * \return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5, typename T_obj6>
inline QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6> qextTrackObjectFunctor(
        const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3, const T_obj4 &obj4,
        const T_obj5 &obj5, const T_obj6 &obj6)
{
    return QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5, T_obj6>(func, obj1, obj2, obj3,
                                                                                             obj4, obj5, obj6);
}

/** Creates an adaptor of type QExtTrackObjectFunctor5 which wraps a functor.
 * \param func Functor that shall be wrapped.
 * \param obj1 Trackable object.
 * \param obj2 Trackable object.
 * \param obj3 Trackable object.
 * \param obj4 Trackable object.
 * \param obj5 Trackable object.
 * \return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4, typename T_obj5>
inline QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3,
                       const T_obj4 &obj4, const T_obj5 &obj5)
{
    return QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4, T_obj5>(func, obj1, obj2, obj3, obj4,
                                                                                     obj5);
}

/** Creates an adaptor of type QExtTrackObjectFunctor4 which wraps a functor.
 * \param func Functor that shall be wrapped.
 * \param obj1 Trackable object.
 * \param obj2 Trackable object.
 * \param obj3 Trackable object.
 * \param obj4 Trackable object.
 * \return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3, typename T_obj4>
inline QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3,
                       const T_obj4 &obj4)
{
    return QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3, T_obj4>(func, obj1, obj2, obj3, obj4);
}

/** Creates an adaptor of type QExtTrackObjectFunctor3 which wraps a functor.
 * \param func Functor that shall be wrapped.
 * \param obj1 Trackable object.
 * \param obj2 Trackable object.
 * \param obj3 Trackable object.
 * \return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2, typename T_obj3>
inline QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2, const T_obj3 &obj3)
{
    return QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2, T_obj3>(func, obj1, obj2, obj3);
}

/** Creates an adaptor of type QExtTrackObjectFunctor2 which wraps a functor.
 * \param func Functor that shall be wrapped.
 * \param obj1 Trackable object.
 * \param obj2 Trackable object.
 * \return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1, typename T_obj2>
inline QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2>
qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1, const T_obj2 &obj2)
{
    return QExtTrackObjectFunctor<T_functor, T_obj1, T_obj2>(func, obj1, obj2);
}

/** Creates an adaptor of type QExtTrackObjectFunctorBase which wraps a functor.
 * \param func Functor that shall be wrapped.
 * \param obj1 Trackable object.
 * \return Adaptor that executes func() on invocation.
 *
 * @newin{2,4}
 *
 * \ingroup qextTrackObjectFunctor
 */
template<typename T_functor, typename T_obj1>
inline QExtTrackObjectFunctor<T_functor, T_obj1> qextTrackObjectFunctor(const T_functor &func, const T_obj1 &obj1)
{
    return QExtTrackObjectFunctor<T_functor, T_obj1>(func, obj1);
}


#endif // _QEXTTRACKOBJECTFUNCTOR_H
