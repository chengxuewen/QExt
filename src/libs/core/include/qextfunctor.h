#ifndef QEXTFUNCTOR_H
#define QEXTFUNCTOR_H

#include <qextglobal.h>
#include <qextfunctortrait.h>


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
class QEXTFunctor7 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7);
    typedef T_return ResultType;

    QEXTFunctor7() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTFunctor7(FunctionType func): m_funcPtr(func) {}
    QEXTFunctor7(const QEXTFunctor7 &src): m_funcPtr(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6,
                        typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return m_funcPtr(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTFunctor6 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6);
    typedef T_return ResultType;

    QEXTFunctor6() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTFunctor6(FunctionType func): m_funcPtr(func) {}
    QEXTFunctor6(const QEXTFunctor6 &src): m_funcPtr(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return m_funcPtr(arg1, arg2, arg3, arg4, arg5, arg6);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTFunctor5 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5);
    typedef T_return ResultType;

    QEXTFunctor5() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTFunctor5(FunctionType func): m_funcPtr(func) {}
    QEXTFunctor5(const QEXTFunctor5 &src): m_funcPtr(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return m_funcPtr(arg1, arg2, arg3, arg4, arg5);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTFunctor4 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3, T_arg4);
    typedef T_return ResultType;

    QEXTFunctor4() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTFunctor4(FunctionType func): m_funcPtr(func) {}
    QEXTFunctor4(const QEXTFunctor4 &src): m_funcPtr(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return m_funcPtr(arg1, arg2, arg3, arg4);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTFunctor3 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2, T_arg3);
    typedef T_return ResultType;

    QEXTFunctor3() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTFunctor3(FunctionType func): m_funcPtr(func) {}
    QEXTFunctor3(const QEXTFunctor3 &src): m_funcPtr(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return m_funcPtr(arg1, arg2, arg3);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTFunctor2 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1, T_arg2);
    typedef T_return ResultType;

    QEXTFunctor2() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTFunctor2(FunctionType func): m_funcPtr(func) {}
    QEXTFunctor2(const QEXTFunctor2 &src): m_funcPtr(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return m_funcPtr(arg1, arg2);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return, typename T_arg1>
class QEXTFunctor1 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)(T_arg1);
    typedef T_return ResultType;

    QEXTFunctor1() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTFunctor1(FunctionType func): m_funcPtr(func) {}
    QEXTFunctor1(const QEXTFunctor1 &src): m_funcPtr(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return m_funcPtr(arg1);
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return>
class QEXTFunctor0 : public QEXTFunctorBase
{
public:
    typedef T_return (*FunctionType)();
    typedef T_return ResultType;

    QEXTFunctor0() : m_funcPtr(QEXT_NULLPTR) {}
    QEXTFunctor0(FunctionType func) : m_funcPtr(func) {}
    QEXTFunctor0(const QEXTFunctor0 &src): m_funcPtr(src.m_funcPtr) {}

    T_return operator()() const {
        return m_funcPtr();
    }

protected:
    FunctionType m_funcPtr;
};

template <typename T_return,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTFunctor : public QEXTFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
{
public:
    typedef QEXTFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTFunctor() {}
    QEXTFunctor(FunctionType func) : BaseType(func) {}
    QEXTFunctor(const QEXTFunctor &src) : BaseType(src.m_funcPtr) {}

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

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
{
public:
    typedef QEXTFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTFunctor() {}
    QEXTFunctor(FunctionType func) : BaseType(func) {}
    QEXTFunctor(const QEXTFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5,
                        typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
{
public:
    typedef QEXTFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTFunctor() {}
    QEXTFunctor(FunctionType func) : BaseType(func) {}
    QEXTFunctor(const QEXTFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4,
                        typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4, arg5);
    }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>
{
public:
    typedef QEXTFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTFunctor() {}
    QEXTFunctor(FunctionType func) : BaseType(func) {}
    QEXTFunctor(const QEXTFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3,
                        typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::operator ()(arg1, arg2, arg3, arg4);
    }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTFunctor3<T_return, T_arg1, T_arg2, T_arg3>
{
public:
    typedef QEXTFunctor3<T_return, T_arg1, T_arg2, T_arg3> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTFunctor() {}
    QEXTFunctor(FunctionType func) : BaseType(func) {}
    QEXTFunctor(const QEXTFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2,
                        typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::operator ()(arg1, arg2, arg3);
    }
};

template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTFunctor<T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTFunctor2<T_return, T_arg1, T_arg2>
{
public:
    typedef QEXTFunctor2<T_return, T_arg1, T_arg2> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTFunctor() {}
    QEXTFunctor(FunctionType func) : BaseType(func) {}
    QEXTFunctor(const QEXTFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                        typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::operator ()(arg1, arg2);
    }
};

template <typename T_return, typename T_arg1>
class QEXTFunctor<T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTFunctor1<T_return, T_arg1>
{
public:
    typedef QEXTFunctor1<T_return, T_arg1> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTFunctor() {}
    QEXTFunctor(FunctionType func) : BaseType(func) {}
    QEXTFunctor(const QEXTFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::operator ()(arg1);
    }
};

template <typename T_return>
class QEXTFunctor<T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTFunctor0<T_return>
{
public:
    typedef QEXTFunctor0<T_return> BaseType;
    typedef typename BaseType::FunctionType FunctionType;
    typedef typename BaseType::ResultType ResultType;

    QEXTFunctor() {}
    QEXTFunctor(FunctionType func) : BaseType(func) {}
    QEXTFunctor(const QEXTFunctor &src) : BaseType(src.m_funcPtr) {}

    T_return operator()() const {
        return BaseType::operator ()();
    }
};




template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextFunctor7(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7)) {
    return QEXTFunctor7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextFunctor6(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6)) {
    return QEXTFunctor6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextFunctor5(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5)) {
    return QEXTFunctor5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>
qextFunctor4(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4)) {
    return QEXTFunctor4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTFunctor3<T_return, T_arg1, T_arg2, T_arg3>
qextFunctor3(T_return (*func)(T_arg1, T_arg2, T_arg3)) {
    return QEXTFunctor3<T_return, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_arg1, typename T_arg2>
inline QEXTFunctor2<T_return, T_arg1, T_arg2>
qextFunctor2(T_return (*func)(T_arg1, T_arg2)) {
    return QEXTFunctor2<T_return, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_arg1>
inline QEXTFunctor1<T_return, T_arg1>
qextFunctor1(T_return (*func)(T_arg1)) {
    return QEXTFunctor1<T_return, T_arg1>(func);
}

template <typename T_return>
inline QEXTFunctor0<T_return>
qextFunctor0(T_return (*func)()) {
    return QEXTFunctor0<T_return>(func);
}



template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
inline QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>
qextFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7)) {
    return QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>(func);
}

template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6>
inline QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>
qextFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6)) {
    return QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>(func);
}

template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
inline QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>
qextFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5)) {
    return QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>(func);
}

template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
inline QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4>
qextFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3, T_arg4)) {
    return QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3, T_arg4>(func);
}

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
inline QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3>
qextFunctor(T_return (*func)(T_arg1, T_arg2, T_arg3)) {
    return QEXTFunctor<T_return, T_arg1, T_arg2, T_arg3>(func);
}

template <typename T_return, typename T_arg1, typename T_arg2>
inline QEXTFunctor<T_return, T_arg1, T_arg2>
qextFunctor(T_return (*func)(T_arg1, T_arg2)) {
    return QEXTFunctor<T_return, T_arg1, T_arg2>(func);
}

template <typename T_return, typename T_arg1>
inline QEXTFunctor<T_return, T_arg1>
qextFunctor(T_return (*func)(T_arg1)) {
    return QEXTFunctor<T_return, T_arg1>(func);
}

template <typename T_return>
inline QEXTFunctor<T_return>
qextFunctor(T_return (*func)()) {
    return QEXTFunctor<T_return>(func);
}


#endif // QEXTFUNCTOR_H
