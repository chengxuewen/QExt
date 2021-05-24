#ifndef QEXTMEMBERFUNCTOR_H
#define QEXTMEMBERFUNCTOR_H

#include <qextglobal.h>
#include <qextfunctortrait.h>
#include <qextlimitreference.h>


template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTMemberFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7);
    typedef T_return ResultType;

    QEXTMemberFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTMemberFunctor7(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor7(const QEXTMemberFunctor7 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTMemberFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6);
    typedef T_return ResultType;

    QEXTMemberFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTMemberFunctor6(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor6(const QEXTMemberFunctor6 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTMemberFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5);
    typedef T_return ResultType;

    QEXTMemberFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTMemberFunctor5(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor5(const QEXTMemberFunctor5 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTMemberFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4);
    typedef T_return ResultType;

    QEXTMemberFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTMemberFunctor4(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor4(const QEXTMemberFunctor4 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTMemberFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3);
    typedef T_return ResultType;

    QEXTMemberFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTMemberFunctor3(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor3(const QEXTMemberFunctor3 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTMemberFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2);
    typedef T_return ResultType;

    QEXTMemberFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTMemberFunctor2(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor2(const QEXTMemberFunctor2 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj, typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2);
    }

    T_return operator()(T_obj &obj, typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj.*m_funcPtr)(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTMemberFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1);
    typedef T_return ResultType;

    QEXTMemberFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTMemberFunctor1(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor1(const QEXTMemberFunctor1 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj->*(this->m_funcPtr))(arg1);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj.*m_funcPtr)(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj>
class QEXTMemberFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)();
    typedef T_return ResultType;

    QEXTMemberFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTMemberFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTMemberFunctor0(const QEXTMemberFunctor0 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj) const {
        return (obj->*(this->m_funcPtr))();
    }

    T_return operator()(T_obj &obj) const {
        return (obj.*m_funcPtr)();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTMemberFunctor
        : public QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }
};

template <typename T_return, typename T_obj>
class QEXTMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTMemberFunctor0<T_return, T_obj>
{
    typedef QEXTMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTMemberFunctor() {}
    QEXTMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTMemberFunctor(const QEXTMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj) const {
        return BaseType::operator ()(obj);
    }

    T_return operator()(T_obj &obj) const {
        return BaseType::operator ()(obj);
    }
};



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTConstMemberFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const;
    typedef T_return ResultType;

    QEXTConstMemberFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstMemberFunctor7(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor7(const QEXTConstMemberFunctor7 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTConstMemberFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const;
    typedef T_return ResultType;

    QEXTConstMemberFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstMemberFunctor6(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor6(const QEXTConstMemberFunctor6 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTConstMemberFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const;
    typedef T_return ResultType;

    QEXTConstMemberFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstMemberFunctor5(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor5(const QEXTConstMemberFunctor5 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTConstMemberFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4) const;
    typedef T_return ResultType;

    QEXTConstMemberFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstMemberFunctor4(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor4(const QEXTConstMemberFunctor4 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTConstMemberFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3) const;
    typedef T_return ResultType;

    QEXTConstMemberFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstMemberFunctor3(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor3(const QEXTConstMemberFunctor3 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTConstMemberFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2) const;
    typedef T_return ResultType;

    QEXTConstMemberFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstMemberFunctor2(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor2(const QEXTConstMemberFunctor2 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj.*m_funcPtr)(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTConstMemberFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1) const;
    typedef T_return ResultType;

    QEXTConstMemberFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstMemberFunctor1(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor1(const QEXTConstMemberFunctor1 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj, typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj->*(this->m_funcPtr))(arg1);
    }

    T_return operator()(const T_obj &obj, typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj.*m_funcPtr)(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj>
class QEXTConstMemberFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)() const;
    typedef T_return ResultType;

    QEXTConstMemberFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstMemberFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTConstMemberFunctor0(const QEXTConstMemberFunctor0 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const {
        return (obj->*(this->m_funcPtr))();
    }

    T_return operator()(const T_obj &obj) const {
        return (obj.*m_funcPtr)();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTConstMemberFunctor
        : public QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTConstMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTConstMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }
};

template <typename T_return, typename T_obj>
class QEXTConstMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstMemberFunctor0<T_return, T_obj>
{
    typedef QEXTConstMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstMemberFunctor() {}
    QEXTConstMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstMemberFunctor(const QEXTConstMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const {
        return BaseType::operator ()(obj);
    }

    T_return operator()(const T_obj &obj) const {
        return BaseType::operator ()(obj);
    }
};



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTVolatileMemberFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile;
    typedef T_return ResultType;

    QEXTVolatileMemberFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTVolatileMemberFunctor7(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor7(const QEXTVolatileMemberFunctor7 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTVolatileMemberFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile;
    typedef T_return ResultType;

    QEXTVolatileMemberFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTVolatileMemberFunctor6(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor6(const QEXTVolatileMemberFunctor6 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTVolatileMemberFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile;
    typedef T_return ResultType;

    QEXTVolatileMemberFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTVolatileMemberFunctor5(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor5(const QEXTVolatileMemberFunctor5 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTVolatileMemberFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4) volatile;
    typedef T_return ResultType;

    QEXTVolatileMemberFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTVolatileMemberFunctor4(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor4(const QEXTVolatileMemberFunctor4 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTVolatileMemberFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3) volatile;
    typedef T_return ResultType;

    QEXTVolatileMemberFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTVolatileMemberFunctor3(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor3(const QEXTVolatileMemberFunctor3 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTVolatileMemberFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2) volatile;
    typedef T_return ResultType;

    QEXTVolatileMemberFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTVolatileMemberFunctor2(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor2(const QEXTVolatileMemberFunctor2 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj.*m_funcPtr)(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTVolatileMemberFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1) volatile;
    typedef T_return ResultType;

    QEXTVolatileMemberFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTVolatileMemberFunctor1(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor1(const QEXTVolatileMemberFunctor1 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj->*(this->m_funcPtr))(arg1);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj.*m_funcPtr)(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj>
class QEXTVolatileMemberFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)() volatile;
    typedef T_return ResultType;

    QEXTVolatileMemberFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTVolatileMemberFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTVolatileMemberFunctor0(const QEXTVolatileMemberFunctor0 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(T_obj *obj) const {
        return (obj->*(this->m_funcPtr))();
    }

    T_return operator()(T_obj &obj) const {
        return (obj.*m_funcPtr)();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTVolatileMemberFunctor
        : public QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }

    T_return operator()(T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }
};

template <typename T_return, typename T_obj>
class QEXTVolatileMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTVolatileMemberFunctor() {}
    QEXTVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTVolatileMemberFunctor(const QEXTVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(T_obj *obj) const {
        return BaseType::operator ()(obj);
    }

    T_return operator()(T_obj &obj) const {
        return BaseType::operator ()(obj);
    }
};



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTConstVolatileMemberFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile;
    typedef T_return ResultType;

    QEXTConstVolatileMemberFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstVolatileMemberFunctor7(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor7(const QEXTConstVolatileMemberFunctor7 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTConstVolatileMemberFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile;
    typedef T_return ResultType;

    QEXTConstVolatileMemberFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstVolatileMemberFunctor6(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor6(const QEXTConstVolatileMemberFunctor6 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTConstVolatileMemberFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile;
    typedef T_return ResultType;

    QEXTConstVolatileMemberFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstVolatileMemberFunctor5(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor5(const QEXTConstVolatileMemberFunctor5 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTConstVolatileMemberFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile;
    typedef T_return ResultType;

    QEXTConstVolatileMemberFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstVolatileMemberFunctor4(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor4(const QEXTConstVolatileMemberFunctor4 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTConstVolatileMemberFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2, T_arg3) const volatile;
    typedef T_return ResultType;

    QEXTConstVolatileMemberFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstVolatileMemberFunctor3(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor3(const QEXTConstVolatileMemberFunctor3 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (obj.*m_funcPtr)(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTConstVolatileMemberFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1, T_arg2) const volatile;
    typedef T_return ResultType;

    QEXTConstVolatileMemberFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstVolatileMemberFunctor2(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor2(const QEXTConstVolatileMemberFunctor2 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj->*(this->m_funcPtr))(arg1, arg2);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (obj.*m_funcPtr)(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTConstVolatileMemberFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)(T_arg1) const volatile;
    typedef T_return ResultType;

    QEXTConstVolatileMemberFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstVolatileMemberFunctor1(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor1(const QEXTConstVolatileMemberFunctor1 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj->*(this->m_funcPtr))(arg1);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (obj.*m_funcPtr)(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj>
class QEXTConstVolatileMemberFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (T_obj::*FunctionType)() const volatile;
    typedef T_return ResultType;

    QEXTConstVolatileMemberFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTConstVolatileMemberFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTConstVolatileMemberFunctor0(const QEXTConstVolatileMemberFunctor0 &src) : m_funcPtr(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const {
        return (obj->*(this->m_funcPtr))();
    }

    T_return operator()(const T_obj &obj) const {
        return (obj.*m_funcPtr)();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTConstVolatileMemberFunctor
        : public QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(obj, arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(obj, arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }

    T_return operator()(const T_obj &obj,
                        typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(obj, arg1);
    }
};

template <typename T_return, typename T_obj>
class QEXTConstVolatileMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTConstVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTConstVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTConstVolatileMemberFunctor() {}
    QEXTConstVolatileMemberFunctor(FunctionType func) : BaseType(func) {}
    QEXTConstVolatileMemberFunctor(const QEXTConstVolatileMemberFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(const T_obj *obj) const {
        return BaseType::operator ()(obj);
    }

    T_return operator()(const T_obj &obj) const {
        return BaseType::operator ()(obj);
    }
};



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTBoundMemberFunctor7
        : public QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor7(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundMemberFunctor7(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor7(const QEXTBoundMemberFunctor7 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    QEXTLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundMemberFunctor6
        : public QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor6(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundMemberFunctor6(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor6(const QEXTBoundMemberFunctor6 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    QEXTLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundMemberFunctor5
        : public QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor5(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundMemberFunctor5(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor5(const QEXTBoundMemberFunctor5 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    QEXTLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundMemberFunctor4
        : public QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor4(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundMemberFunctor4(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor4(const QEXTBoundMemberFunctor4 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    QEXTLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundMemberFunctor3
        : public QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor3(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundMemberFunctor3(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor3(const QEXTBoundMemberFunctor3 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    QEXTLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundMemberFunctor2
        : public QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor2(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundMemberFunctor2(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor2(const QEXTBoundMemberFunctor2 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
    }

    QEXTLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundMemberFunctor1
        : public QEXTMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor1(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundMemberFunctor1(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor1(const QEXTBoundMemberFunctor1 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1);
    }

    QEXTLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundMemberFunctor0
        : public QEXTMemberFunctor0<T_return, T_obj>
{
    typedef QEXTMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor0(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundMemberFunctor0(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundMemberFunctor0(const QEXTBoundMemberFunctor0 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()() const {
        return (m_obj.invoke().*(this->m_funcPtr))();
    }

    QEXTLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundMemberFunctor0<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor0<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTBoundMemberFunctor
        : public QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundMemberFunctor0<T_return, T_obj>
{
    typedef QEXTBoundMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundMemberFunctor(const QEXTBoundMemberFunctor &src) : BaseType(src) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundMemberFunctor<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundMemberFunctor<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTBoundConstMemberFunctor7
        : public QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor7(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstMemberFunctor7(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor7(const QEXTBoundConstMemberFunctor7 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    QEXTConstLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundConstMemberFunctor6
        : public QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor6(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstMemberFunctor6(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor6(const QEXTBoundConstMemberFunctor6 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    QEXTConstLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundConstMemberFunctor5
        : public QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor5(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstMemberFunctor5(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor5(const QEXTBoundConstMemberFunctor5 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    QEXTConstLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundConstMemberFunctor4
        : public QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor4(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstMemberFunctor4(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor4(const QEXTBoundConstMemberFunctor4 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    QEXTConstLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundConstMemberFunctor3
        : public QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor3(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstMemberFunctor3(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor3(const QEXTBoundConstMemberFunctor3 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    QEXTConstLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundConstMemberFunctor2
        : public QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor2(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstMemberFunctor2(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor2(const QEXTBoundConstMemberFunctor2 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
    }

    QEXTConstLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundConstMemberFunctor1
        : public QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTConstMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor1(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstMemberFunctor1(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor1(const QEXTBoundConstMemberFunctor1 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1);
    }

    QEXTConstLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundConstMemberFunctor0
        : public QEXTConstMemberFunctor0<T_return, T_obj>
{
    typedef QEXTConstMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor0(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstMemberFunctor0(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstMemberFunctor0(const QEXTBoundConstMemberFunctor0 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()() const {
        return (m_obj.invoke().*(this->m_funcPtr))();
    }

    QEXTConstLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundConstMemberFunctor0<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor0<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTBoundConstMemberFunctor
        : public QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundConstMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstMemberFunctor0<T_return, T_obj>
{
    typedef QEXTBoundConstMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstMemberFunctor(const QEXTBoundConstMemberFunctor &src) : BaseType(src) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundConstMemberFunctor<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstMemberFunctor<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTBoundVolatileMemberFunctor7
        : public QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor7(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundVolatileMemberFunctor7(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor7(const QEXTBoundVolatileMemberFunctor7 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    QEXTVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundVolatileMemberFunctor6
        : public QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor6(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundVolatileMemberFunctor6(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor6(const QEXTBoundVolatileMemberFunctor6 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    QEXTVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundVolatileMemberFunctor5
        : public QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor5(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundVolatileMemberFunctor5(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor5(const QEXTBoundVolatileMemberFunctor5 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    QEXTVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundVolatileMemberFunctor4
        : public QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor4(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundVolatileMemberFunctor4(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor4(const QEXTBoundVolatileMemberFunctor4 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    QEXTVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundVolatileMemberFunctor3
        : public QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor3(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundVolatileMemberFunctor3(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor3(const QEXTBoundVolatileMemberFunctor3 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    QEXTVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundVolatileMemberFunctor2
        : public QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor2(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundVolatileMemberFunctor2(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor2(const QEXTBoundVolatileMemberFunctor2 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
    }

    QEXTVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundVolatileMemberFunctor1
        : public QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor1( T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundVolatileMemberFunctor1( T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor1(const QEXTBoundVolatileMemberFunctor1 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1);
    }

    QEXTVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundVolatileMemberFunctor0
        : public QEXTVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor0(T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundVolatileMemberFunctor0(T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundVolatileMemberFunctor0(const QEXTBoundVolatileMemberFunctor0 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()() const {
        return (m_obj.invoke().*(this->m_funcPtr))();
    }

    QEXTVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor0<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor0<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTBoundVolatileMemberFunctor
        : public QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundVolatileMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTBoundVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundVolatileMemberFunctor(T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundVolatileMemberFunctor(const QEXTBoundVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundVolatileMemberFunctor<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundVolatileMemberFunctor<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTBoundConstVolatileMemberFunctor7
        : public QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor7(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstVolatileMemberFunctor7(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor7(const QEXTBoundConstVolatileMemberFunctor7 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundConstVolatileMemberFunctor6
        : public QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor6(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstVolatileMemberFunctor6(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor6(const QEXTBoundConstVolatileMemberFunctor6 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundConstVolatileMemberFunctor5
        : public QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor5(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstVolatileMemberFunctor5(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor5(const QEXTBoundConstVolatileMemberFunctor5 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4, arg5);
    }

    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundConstVolatileMemberFunctor4
        : public QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor4(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstVolatileMemberFunctor4(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor4(const QEXTBoundConstVolatileMemberFunctor4 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3, arg4);
    }

    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundConstVolatileMemberFunctor3
        : public QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor3(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstVolatileMemberFunctor3(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor3(const QEXTBoundConstVolatileMemberFunctor3 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2, arg3);
    }

    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundConstVolatileMemberFunctor2
        : public QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor2(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstVolatileMemberFunctor2(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor2(const QEXTBoundConstVolatileMemberFunctor2 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1, arg2);
    }

    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundConstVolatileMemberFunctor1
        : public QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor1(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstVolatileMemberFunctor1(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor1(const QEXTBoundConstVolatileMemberFunctor1 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return (m_obj.invoke().*(this->m_funcPtr))(arg1);
    }

    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundConstVolatileMemberFunctor0
        : public QEXTConstVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTConstVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor0(const T_obj *obj, FunctionType func) : BaseType(func), m_obj(*obj) {}
    QEXTBoundConstVolatileMemberFunctor0(const T_obj &obj, FunctionType func) : BaseType(func), m_obj(obj) {}
    QEXTBoundConstVolatileMemberFunctor0(const QEXTBoundConstVolatileMemberFunctor0 &src) : BaseType(src.m_funcPtr), m_obj(src.m_obj) {}

    T_return operator()() const {
        return (m_obj.invoke().*(this->m_funcPtr))();
    }

    QEXTConstVolatileLimitReference<T_obj> m_obj;
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTBoundConstVolatileMemberFunctor
        : public QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
    typedef QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
    typedef QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
    typedef QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
{
    typedef QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
{
    typedef QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
{
    typedef QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
{
    typedef QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return, typename T_obj, typename T_arg1>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1> &target) {
        qextVisitEach(action, target.m_obj);
    }
};

template <typename T_return, typename T_obj>
class QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>
{
    typedef QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj> BaseType;
public:
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTBoundConstVolatileMemberFunctor(const T_obj *obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const T_obj &obj, FunctionType func) : BaseType(obj, func) {}
    QEXTBoundConstVolatileMemberFunctor(const QEXTBoundConstVolatileMemberFunctor &src) : BaseType(src) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};

template <typename T_return, typename T_obj>
struct QEXTVisitor<QEXTBoundConstVolatileMemberFunctor<T_return, T_obj> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const QEXTBoundConstVolatileMemberFunctor<T_return, T_obj> &target) {
        qextVisitEach(action, target.m_obj);
    }
};



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_return (T_obj::*func)(T_arg1, T_arg2) ) {
    return QEXTMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_return (T_obj::*func)(T_arg1) ) {
    return QEXTMemberFunctor1<T_return, T_obj, T_arg1>(func);
}

template <typename T_return, typename T_obj>
inline QEXTMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_return (T_obj::*func)() ) {
    return QEXTMemberFunctor0<T_return, T_obj>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) ) {
    return QEXTMemberFunctor<T_return, T_obj, T_arg1>(func);
}

template <typename T_return, typename T_obj>
inline QEXTMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_return (T_obj::*func)() ) {
    return QEXTMemberFunctor<T_return, T_obj>(func);
}



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_return (T_obj::*func)(T_arg1, T_arg2) const) {
    return QEXTConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_return (T_obj::*func)(T_arg1) const) {
    return QEXTConstMemberFunctor1<T_return, T_obj, T_arg1>(func);
}

template <typename T_return, typename T_obj>
inline QEXTConstMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_return (T_obj::*func)() const) {
    return QEXTConstMemberFunctor0<T_return, T_obj>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTConstMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) const) {
    return QEXTConstMemberFunctor<T_return, T_obj, T_arg1>(func);
}

template <typename T_return, typename T_obj>
inline QEXTConstMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_return (T_obj::*func)() const) {
    return QEXTConstMemberFunctor<T_return, T_obj>(func);
}



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_return (T_obj::*func)(T_arg1, T_arg2) volatile) {
    return QEXTVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_return (T_obj::*func)(T_arg1) volatile) {
    return QEXTVolatileMemberFunctor1<T_return, T_obj, T_arg1>(func);
}

template <typename T_return, typename T_obj>
inline QEXTVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_return (T_obj::*func)() volatile) {
    return QEXTVolatileMemberFunctor0<T_return, T_obj>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj, T_arg1>(func);
}

template <typename T_return, typename T_obj>
inline QEXTVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_return (T_obj::*func)() volatile) {
    return QEXTVolatileMemberFunctor<T_return, T_obj>(func);
}



template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_return (T_obj::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_return (T_obj::*func)(T_arg1) const volatile) {
    return QEXTConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>(func);
}

template <typename T_return, typename T_obj>
inline QEXTConstVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_return (T_obj::*func)() const volatile) {
    return QEXTConstVolatileMemberFunctor0<T_return, T_obj>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_obj,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_obj, typename T_arg1, typename T_arg2>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_obj, typename T_arg1>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_return (T_obj::*func)(T_arg1) const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(func);
}

template <typename T_return, typename T_obj>
inline QEXTConstVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_return (T_obj::*func)() const volatile) {
    return QEXTConstVolatileMemberFunctor<T_return, T_obj>(func);
}



template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTBoundMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTBoundMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTBoundMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTBoundMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTBoundMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) ) {
    return QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) ) {
    return QEXTBoundMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj *obj, T_return (T_obj2::*func)(T_arg1) ) {
    return QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj &obj, T_return (T_obj2::*func)(T_arg1) ) {
    return QEXTBoundMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj *obj, T_return (T_obj2::*func)() ) {
    return QEXTBoundMemberFunctor0<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj &obj, T_return (T_obj2::*func)() ) {
    return QEXTBoundMemberFunctor0<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1) ) {
    return QEXTBoundMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)() ) {
    return QEXTBoundMemberFunctor<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)() ) {
    return QEXTBoundMemberFunctor<T_return, T_obj>(obj, func);
}



template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTBoundConstMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTBoundConstMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTBoundConstMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTBoundConstMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTBoundConstMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const) {
    return QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const) {
    return QEXTBoundConstMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj *obj, T_return (T_obj2::*func)(T_arg1) const) {
    return QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj &obj, T_return (T_obj2::*func)(T_arg1) const) {
    return QEXTBoundConstMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj *obj, T_return (T_obj2::*func)() const) {
    return QEXTBoundConstMemberFunctor0<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj &obj, T_return (T_obj2::*func)() const) {
    return QEXTBoundConstMemberFunctor0<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1) const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)() const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)() const) {
    return QEXTBoundConstMemberFunctor<T_return, T_obj>(obj, func);
}



template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTBoundVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTBoundVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTBoundVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTBoundVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) volatile)
{ return QEXTBoundVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func); }

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) volatile) {
    return QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) volatile)
{ return QEXTBoundVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func); }

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj *obj, T_return (T_obj2::*func)(T_arg1) volatile) {
    return QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj &obj, T_return (T_obj2::*func)(T_arg1) volatile) {
    return QEXTBoundVolatileMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj *obj, T_return (T_obj2::*func)() volatile) {
    return QEXTBoundVolatileMemberFunctor0<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj &obj, T_return (T_obj2::*func)() volatile) {
    return QEXTBoundVolatileMemberFunctor0<T_return, T_obj>(obj, func);
}



template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1) volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)() volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)() volatile) {
    return QEXTBoundVolatileMemberFunctor<T_return, T_obj>(obj, func);
}



template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor7(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor7<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor6(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor6<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor5(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor5<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor4(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor4<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor3(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor3<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor2(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor2<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj *obj, T_return (T_obj2::*func)(T_arg1) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>
qextMemberFunctor1(T_obj &obj, T_return (T_obj2::*func)(T_arg1) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor1<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj *obj, T_return (T_obj2::*func)() const volatile) {
    return QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>
qextMemberFunctor0(T_obj &obj, T_return (T_obj2::*func)() const volatile) {
    return QEXTBoundConstVolatileMemberFunctor0<T_return, T_obj>(obj, func);
}



template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2, T_arg3) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2, T_arg3>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1, typename T_arg2>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1, T_arg2) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1, T_arg2>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)(T_arg1) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2, typename T_arg1>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)(T_arg1) const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj, T_arg1>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj *obj, T_return (T_obj2::*func)() const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj>(obj, func);
}

template <typename T_return, typename T_obj, typename T_obj2>
inline QEXTBoundConstVolatileMemberFunctor<T_return, T_obj>
qextMemberFunctor(T_obj &obj, T_return (T_obj2::*func)() const volatile) {
    return QEXTBoundConstVolatileMemberFunctor<T_return, T_obj>(obj, func);
}


#endif // QEXTMEMBERFUNCTOR_H
