#ifndef QEXTRETURNTYPEDEDUCETEST_H
#define QEXTRETURNTYPEDEDUCETEST_H

#include <qextReturnTypeDeduce.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextReturnTypeDeduceTest
{

    static std::string sg_string = "";


    template <typename T>
    void Bar(T)
    {
        sg_string = "unknown";
    }

    template <>
    void Bar<int>(int)
    {
        sg_string = "int";
    }

    template <>
    void Bar<long>(long)
    {
        sg_string = "long";
    }

    template <>
    void Bar<double>(double)
    {
        sg_string = "double";
    }

    struct Foo : public QEXTFunctorBase
    {
        typedef double Return;

        int operator()(int i = 1);
        double operator()(const int &, int);
    };

    struct Foo2 : public Foo {};

    struct Foo3 : public QEXTFunctorBase
    {
        typedef int Return;

        int operator()(int i = 1);
        double operator()(const int &, int);
    };



    TEST_GROUP(qextReturnTypeDeduceTest)
    {
    };

    TEST(qextReturnTypeDeduceTest, testSimple)
    {
        sg_string = "";
        Bar(QEXTReturnTypeDeduce<Foo2, long>::Type());
        CHECK("double" == sg_string);

        sg_string = "";
        Bar(QEXTReturnTypeDeduce<Foo2, int, int>::Type());
        CHECK("double" == sg_string);

        sg_string = "";
        Bar(QEXTReturnTypeDeduce<Foo3, int, int>::Type());
        CHECK("int" == sg_string);

        sg_string = "";
        Bar(QEXTReturnTypeDeduce<Foo2, int, int, int>::Type());
        CHECK("double" == sg_string);
    }

} // namespace qextReturnTypeDeduceTest

#endif // QEXTRETURNTYPEDEDUCETEST_H
