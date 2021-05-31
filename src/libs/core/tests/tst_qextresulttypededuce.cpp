#include <qextresulttypededuce.h>

#include <QtTest>
#include <QDebug>

class QEXTResultTypeDeduceTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();

public:
    static QString sm_result;
};

QString QEXTResultTypeDeduceTest::sm_result = "";



template <class T>
void Bar(T)
{
    QEXTResultTypeDeduceTest::sm_result = "unknown";
}

template <>
void Bar<int>(int)
{
    QEXTResultTypeDeduceTest::sm_result = "int";
}

template <>
void Bar<long>(long)
{
    QEXTResultTypeDeduceTest::sm_result = "long";
}

template <>
void Bar<double>(double)
{
    QEXTResultTypeDeduceTest::sm_result = "double";
}

struct Foo : public QEXTFunctorBase
{
    typedef double ResultType;

    int operator()(int i = 1);
    double operator()(const int&, int);
};

struct Foo2 : public Foo {};

struct Foo3 : public QEXTFunctorBase
{
    typedef int ResultType;

    int operator()(int i = 1);
    double operator()(const int&, int);
};




void QEXTResultTypeDeduceTest::testSimple()
{
    QEXTResultTypeDeduceTest::sm_result = "";
    Bar(QEXTResultTypeDeduce<Foo2, long>::Type());
    QVERIFY("double" == QEXTResultTypeDeduceTest::sm_result);

    QEXTResultTypeDeduceTest::sm_result = "";
    Bar(QEXTResultTypeDeduce<Foo2, int, int>::Type());
    QVERIFY("double" == QEXTResultTypeDeduceTest::sm_result);

    QEXTResultTypeDeduceTest::sm_result = "";
    Bar(QEXTResultTypeDeduce<Foo3, int, int>::Type());
    QVERIFY("int" == QEXTResultTypeDeduceTest::sm_result);

    QEXTResultTypeDeduceTest::sm_result = "";
    Bar(QEXTResultTypeDeduce<Foo2, int, int, int>::Type());
    QVERIFY("double" == QEXTResultTypeDeduceTest::sm_result);
}

QTEST_APPLESS_MAIN(QEXTResultTypeDeduceTest)

#include <tst_qextresulttypededuce.moc>
