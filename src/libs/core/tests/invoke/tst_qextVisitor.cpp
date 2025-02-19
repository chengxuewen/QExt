#include <qextVisitor.h>
#include <qextAdaptorTrait.h>
#include <qextFunction.h>
#include <qextMemberFunctor.h>

#include <QtTest>
#include <iostream>
#include <string>
#include <sstream>

static std::string sg_string = "";

class QExtVisitorTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testTypeVisitor();
    void testCase1();
};

class MClass1
{
public:
    MClass1() {}

    void exec(int i) const
    {
        std::stringstream sstream;
        sstream << "MClass1::exec:" << i;
        sg_string = sstream.str();
    }
};

class MClass2
{
public:
    MClass2() {}

    void exec(int i) const
    {
        std::stringstream sstream;
        sstream << "MClass2::exec:" << i;
        sg_string = sstream.str();
    }
};

class MClassFunctor
{
public:
    MClassFunctor() {}

    void operator ()(const MClass1 *obj) const
    {
        obj->exec(0);
    }
};

class MTrackableClass1 : QObject
{
public:
    MTrackableClass1(const std::string &str) : m_string(str) {}

    void exec(int i)
    {
        std::stringstream sstream;
        sstream << "MClass2::exec:" << m_string << i;
        sg_string = sstream.str();
    }

private:
    std::string m_string;
};





class NsExtClass
{
};

class MyClass1 : public QObject
{
public:
    MyClass1(const std::string &str) : s(str) {}

    void execute(int i)
    {
        std::stringstream sstream;
        sstream << s << i;
        sg_string = sstream.str();
    }
private:
    std::string s;
};

class MyClass2 : public NsExtClass, public QObject
{
public:
    MyClass2(const std::string &str) : s(str) {}

    void execute(int i)
    {
        std::stringstream sstream;
        sstream << s << i;
        sg_string = sstream.str();
    }
private:
    std::string s;
};


template <typename T_functor>
struct MyAdaptor1 : public QExtAdapts<T_functor>
{
    template <typename T_arg1 = void, class T_arg2 = void>
    struct ReturnTypeDeduce
    {
        typedef typename QExtReturnTypeDeduce<T_functor, T_arg1, T_arg2>::Type Type;
    };
    typedef typename QExtFunctorTrait<T_functor>::ResultType ResultType;

    ResultType
    operator()() const
    {
        sg_string = "MyAdaptor1()() ";
        return this->mFunctor();
    }

    template <typename T_arg1>
    typename ReturnTypeDeduce<T_arg1>::type
    operator()(T_arg1 arg1) const
    {
        sg_string = "MyAdaptor1()(arg1) ";
        return this->mFunctor(arg1);
    }

    template <typename T_arg1, class T_arg2>
    typename ReturnTypeDeduce<T_arg1, T_arg2>::type
    operator()(T_arg1 arg1, T_arg2 arg2) const
    {
        sg_string = "MyAdaptor1()(arg1, arg2) ";
        return this->mFunctor(arg1, arg2);
    }

    // Constructs a MyAdaptor1 object that wraps the passed functor.
    // Initializes adapts<T_functor>::mFunctor, which is invoked from operator()().
    explicit MyAdaptor1(const T_functor &functor) : QExtAdapts<T_functor>(functor) {}
};

template <typename T_action, class T_functor>
void qextVisitEach(const T_action &action,
                   const MyAdaptor1<T_functor> &target)
{
    qextVisitEach(action, target.mFunctor);
}

template <typename T_functor>
inline MyAdaptor1<T_functor>
my_adaptor1(const T_functor &func)
{
    return MyAdaptor1<T_functor>(func);
}


template <typename T_functor>
struct QExtVisitor<MyAdaptor1<T_functor> >
{
    template <typename T_action>
    static void doVisitEach(const T_action &action,
                            const MyAdaptor1<T_functor> &target)
    {
        qextVisitEach(action, target.mFunctor);
    }
};


void QExtVisitorTest::testTypeVisitor()
{
    MClassFunctor mClassFunctor;
    MClass1 mClass1;
    QExtBoundConstMemberFunctor<void, MClass1, int> boundMemFunctor = qextMakeFunctor(&mClass1, &MClass1::exec);

    // test valid inherit visit, action exec success
    sg_string = "";
    qextVisitEachType<MClass1 *>(mClassFunctor, boundMemFunctor);
    QVERIFY("MClass1::exec:0" == sg_string);

    // test unvalid inherit visit, action not exec
    sg_string = "";
    qextVisitEachType<MClass2 *>(mClassFunctor, boundMemFunctor);
    QVERIFY("" == sg_string);
}

void QExtVisitorTest::testCase1()
{
    QExtFunction<void, int> sl1;
    {
        sg_string = "";
        MyClass1 my_class1("x=");
        sl1 = qextMakeFunctor(&my_class1, &MyClass1::execute);
        sl1(-2);
        QVERIFY("x=-2" == sg_string);
    } // auto-disconnect sl1

    sg_string = "";
    sl1(-2);
    QVERIFY("" == sg_string);
}

QTEST_APPLESS_MAIN(QExtVisitorTest)

#include <tst_qextVisitor.moc>
