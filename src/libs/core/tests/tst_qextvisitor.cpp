#include <qextslot.h>
#include <qextvisitor.h>
#include <qexttrackable.h>
#include <qextadaptortrait.h>
#include <qextmemberfunctor.h>

#include <QtTest>
#include <QDebug>

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

class QEXTVisitorTest : public QObject
{
    Q_OBJECT
private slots:
    void testTypeVisitor();
    void testVisitor();
    void testCase1();
    void testCase2();
    void testCase3();

public:
    static QString sm_result;
};

QString QEXTVisitorTest::sm_result = "";


class MClass1
{
public:
    MClass1() {}

    void exec(int i) const {
        QEXTVisitorTest::sm_result = QString("MClass1::exec:%1").arg(i);
    }
};

class MClass2
{
public:
    MClass2() {}

    void exec(int i) const {
        QEXTVisitorTest::sm_result = QString("MClass2::exec:%1").arg(i);
    }
};

class MClassFunctor
{
public:
    MClassFunctor() {}

    void operator ()(const MClass1 *obj) const {
        obj->exec(0);
    }
};

class MTrackableClass1 : QEXTTrackable
{
public:
    MTrackableClass1(const QString &str) : m_string(str) {}

    void exec(int i) {
        QEXTVisitorTest::sm_result = QString("MClass2::exec:%1%2").arg(m_string).arg(i);
    }

private:
    QString m_string;
};





class NsExtClass
{
};

class MyClass1 : public QEXTTrackable
{
public:
    MyClass1(const QString &str) : s(str) {}

    void execute(int i) {
        QEXTVisitorTest::sm_result = QString("%1%2").arg(s).arg(i);
    }
private:
    QString s;
};

class MyClass2 : public NsExtClass, public QEXTTrackable
{
public:
    MyClass2(const QString &str) : s(str) {}

    void execute(int i) {
        QEXTVisitorTest::sm_result = QString("%1%2").arg(s).arg(i);
    }
private:
    QString s;
};


template <class T_functor>
struct MyAdaptor1 : public QEXTAdapts<T_functor>
{
    template <class T_arg1 = void, class T_arg2 = void>
    struct ResultTypeDeduce
    {
        typedef typename QEXTResultTypeDeduce<T_functor, T_arg1, T_arg2>::Type Type;
    };
    typedef typename QEXTFunctorTrait<T_functor>::ResultType ResultType;

    ResultType
    operator()() const {
        QEXTVisitorTest::sm_result = "MyAdaptor1()() ";
        return this->m_functor();
    }

    template <class T_arg1>
    typename ResultTypeDeduce<T_arg1>::type
    operator()(T_arg1 arg1) const {
        QEXTVisitorTest::sm_result = "MyAdaptor1()(arg1) ";
        return this->m_functor(arg1);
    }

    template <class T_arg1, class T_arg2>
    typename ResultTypeDeduce<T_arg1, T_arg2>::type
    operator()(T_arg1 arg1, T_arg2 arg2) const {
        QEXTVisitorTest::sm_result = "MyAdaptor1()(arg1, arg2) ";
        return this->m_functor(arg1, arg2);
    }

    // Constructs a MyAdaptor1 object that wraps the passed functor.
    // Initializes adapts<T_functor>::m_functor, which is invoked from operator()().
    explicit MyAdaptor1(const T_functor& functor) : QEXTAdapts<T_functor>(functor) {}
};

template <class T_action, class T_functor>
void qextVisitEach(const T_action& action,
                   const MyAdaptor1<T_functor>& target) {
    qextVisitEach(action, target.m_functor);
}

template <typename T_functor>
inline MyAdaptor1<T_functor>
my_adaptor1(const T_functor& func)
{
    return MyAdaptor1<T_functor>(func);
}


template <class T_functor>
struct QEXTVisitor<MyAdaptor1<T_functor> >
{
    template <class T_action>
    static void doVisitEach(const T_action& action,
                            const MyAdaptor1<T_functor>& target) {
        qextVisitEach(action, target.m_functor);
    }
};



void QEXTVisitorTest::testTypeVisitor()
{
    MClassFunctor mClassFunctor;
    MClass1 mClass1;
    QEXTBoundConstMemberFunctor<void, MClass1, int> boundMemFunctor = qextMemberFunctor(&mClass1, &MClass1::exec);

    // test valid inherit visit, action exec success
    QEXTVisitorTest::sm_result = "";
    qextVisitEachType<MClass1 *>(mClassFunctor, boundMemFunctor);
    QVERIFY("MClass1::exec:0" == QEXTVisitorTest::sm_result);

    // test unvalid inherit visit, action not exec
    QEXTVisitorTest::sm_result = "";
    qextVisitEachType<MClass2 *>(mClassFunctor, boundMemFunctor);
    QVERIFY("" == QEXTVisitorTest::sm_result);
}

void QEXTVisitorTest::testVisitor()
{

}

void QEXTVisitorTest::testCase1()
{
    QEXTSlot<void, int> sl1;
    {
        QEXTVisitorTest::sm_result = "";
        MyClass1 my_class1("x=");
        sl1 = qextMemberFunctor(&my_class1, &MyClass1::execute);
        sl1(-2);
        QVERIFY("x=-2" == QEXTVisitorTest::sm_result);
    } // auto-disconnect sl1

    QEXTVisitorTest::sm_result = "";
    sl1(-2);
    QVERIFY("" == QEXTVisitorTest::sm_result);
}

//Assume that class sigc::visitor has not been implemented.
//Test with MyClass2, although it is expected to fail in this case.
void QEXTVisitorTest::testCase2()
{

}

//Assume that class sigc::visitor has been implemented.
//Test with MyClass2, which is expected to succeed in this case.
void QEXTVisitorTest::testCase3()
{

}

QTEST_APPLESS_MAIN(QEXTVisitorTest)

#include <tst_qextvisitor.moc>
