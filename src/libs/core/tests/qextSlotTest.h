#ifndef QEXTSLOTTEST_H
#define QEXTSLOTTEST_H

#include <qextSlot.h>
#include <qextBindFunctor.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>
#include <qextTrackObjectFunctor.h>

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#if QEXT_CC_STD_11
    #include <functional>
#endif

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextSlotTest
{

    static int sg_result = 0;
    static std::string *sg_string = QEXT_DECL_NULLPTR;

    void fooObj(QEXTObject &)
    {
        *sg_string = "fooObj(x)";
    }

    class Foo
    {
    public:
        void operator()(int i)
        {
            sg_result = i;
            std::stringstream sstream;
            sstream << "foo(int " << i << ")";
            *sg_string = sstream.str();
        }

        void operator()(std::string &str)
        {
            std::stringstream sstream;
            sstream << "foo(string '" << str << "') ";
            *sg_string = sstream.str();
            str = "foo was here";
        }

        void operator()(int, int)
        {
            *sg_string = "foo(int, int)";
        }
    };

    class MObj : public QEXTObject
    {
    public:
        MObj() {}

        void function()
        {
            *sg_string = "MObj::function()";
        }
    };

    TEST_GROUP(qextSlotTest) {};

    TEST(qextSlotTest, str)
    {
        std::string string;
        sg_string = &string;

        *sg_string = "qextSlotTest";
    }

    TEST(qextSlotTest, testSimple)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot< void, int > s1 = Foo();
        s1(1);
        CHECK(1 == sg_result);

        s1 = Foo();
        s1(2);
        CHECK(2 == sg_result);
    }

    TEST(qextSlotTest, testImplicitConversion)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot< void, char > s2 = Foo();
        s2(3);
        CHECK(3 == sg_result);
    }

    TEST(qextSlotTest, testReference)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot< void, std::string & > sl1 = Foo();
        std::string str("guest book");
        sl1(str);
        *sg_string += str;
        CHECK("foo(string 'guest book') foo was here" == *sg_string);
    }

    TEST(qextSlotTest, testEqualOperator)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot< void, std::string & > sl1 = Foo();
        std::string str("guest book");
        sl1(str);

        str = "guest book";
        QEXTSlot< void, std::string & > sl2;
        sl2 = sl1;
        sl1 = sl2;
        sl1(str);
        *sg_string += "foo was here";
        CHECK("foo(string 'guest book') foo was here" == *sg_string);
    }

    TEST(qextSlotTest, testCopyCtor)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot< void, int > s1 = Foo();
        s1(1);
        CHECK(1 == sg_result);

        s1 = Foo();
        s1(2);
        CHECK(2 == sg_result);

        QEXTSlot< void, int > s1_clone(s1);
        s1_clone(4);
        CHECK("foo(int 4)" == *sg_string);
    }

    void functionFoo()
    {
        *sg_string = "functionFoo";
    }

    void functionBar()
    {
        *sg_string = "functionBar";
    }

    TEST(qextSlotTest, testDisconnect)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot< void > theSlot(&functionFoo);
        CHECK(!theSlot.isConnected());
        CHECK(!theSlot.isBlocked());
        CHECK(!theSlot.isNull());
        CHECK(!theSlot.isTrackable());
        CHECK(theSlot.isValid());
        theSlot();
        CHECK("functionFoo" == *sg_string);

        theSlot = qextPointerFunctor(&functionBar);
        theSlot();
        CHECK("functionBar" == string);

        QEXTSlot< void > objS1ot;
        {
            MObj mObj;
            *sg_string = "";
            objS1ot = qextMemberFunctor(&mObj, &MObj::function);
            CHECK(!objS1ot.isConnected());
            CHECK(!objS1ot.isBlocked());
            CHECK(!objS1ot.isNull());
            CHECK(objS1ot.isTrackable());
            CHECK(objS1ot.isValid());
            objS1ot();
            CHECK("MObj::function()" == string);
        }
        CHECK(objS1ot.isNull());
        CHECK(!objS1ot.isValid());
        objS1ot();
        CHECK("MObj::function()" == string);
    }

    int func1(int i)
    {
        return i;
    }

    TEST(qextSlotTest, testFunctor)
    {
        QEXTPointerFunctor<int, int> func = qextPointerFunctor(&func1);
        QEXTSlot<int, int> slot = func;
        CHECK(1 == slot(1));
    }

    class FType
    {
    public:
        FType() {}

        int func(int i)
        {
            return i;
        }

        void funcR(int &i)
        {
            i++;
        }
    };

    TEST(qextSlotTest, testMemFunctor)
    {
        FType fType;
        QEXTMemberFunctor<int, FType, int> memFunc = qextMemberFunctor(&FType::func);
        QEXTSlot<int, FType *, int> slot = memFunc;
        CHECK(1 == slot(&fType, 1));

        QEXTMemberFunctor<void, FType, int &> memFuncR = qextMemberFunctor(&FType::funcR);
        QEXTSlot<void, FType *, int &> slotR = memFuncR;
        int a1 = 1;
        slotR(&fType, a1);
        CHECK(2 == a1);

        QEXTBoundMemberFunctor<int, FType, int> boundMemFunc = qextMemberFunctor(&fType, &FType::func);
        QEXTSlot<int, int> slot2 = boundMemFunc;
        CHECK(1 == slot2(1));
    }

    TEST(qextSlotTest, testCompare)
    {
        QEXTMemberFunctor<void, FType, int &> memFuncR = qextMemberFunctor(&FType::funcR);
        QEXTSlot<void, FType *, int &> slotR = memFuncR;
        QEXTSlot<void, FType *, int &> slotR1 = slotR;
        QEXTSlot<void, FType *, int &> slotR2;
        QEXTSlot<void, FType *, int &> slotR3;
        CHECK(slotR == slotR1);
        CHECK_FALSE(slotR == slotR2);
        CHECK(slotR2 == slotR3);
    }

    TEST(qextSlotTest, testCopyInvalid)
    {
        std::string string;
        sg_string = &string;

        QEXTObject *obj = new QEXTObject;

        *sg_string = "";
        QEXTSlot<void> fooSlot = qextBindFunctor(qextPointerFunctor(&fooObj), qextReferenceWrapper(*obj));
        fooSlot();
        CHECK("fooObj(x)" == *sg_string);

        // This invalidates foo.
        delete obj;

        // Try to crash if the invalid slot parameter is used by libsigc++,
        // and get a debugger backtrace at the point that it happens.
        //
        // Comment this out to get a meaningful backtrace from valgrind.
        //
        // Try to pollute the memory previously occupied by the QEXTObject
        // instance. The hope is that with a regular memory allocator (i.e. not
        // valgrind), we end up with buffer == (void *)t.
        void *buffer = malloc(sizeof(QEXTObject));
        memset(buffer, 0xFF, sizeof(QEXTObject));

        //  the copy constructor fails
        // because the pointer value it dereferences does not point to a
        // QEXTObject anymore, it now points to a polluted buffer.
        *sg_string = "";
        QEXTSlot<void> barSlot = fooSlot;
        barSlot();
        CHECK("" == *sg_string);

        free(buffer);
    }


#if QEXT_CC_STD_11

    void egon(std::string &str)
    {
        std::stringstream sstream;
        sstream << "egon(string '" << str << "')";
        *sg_string = sstream.str();
        str = "egon was here";
    }


    TEST(qextSlotTest, teststdLambda)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot<void> slot;

        std::string guestBook("karl");
        slot = [ = ]()
        {
            *sg_string = "stdLambda";
        };
        slot();
        CHECK("stdLambda" == *sg_string);

        QEXTFunction<void> trackObjectTestFunctor = [ = ]()
        {
            *sg_string = "qextTrackObjectFunctor::stdLambda";
        };
        slot = qextTrackObjectFunctor(trackObjectTestFunctor, guestBook);
        slot();
        CHECK("qextTrackObjectFunctor::stdLambda" == *sg_string);

        QEXTSlot<int> slot1 = []() ->int { return 22;};
        CHECK(22 == slot1());

        QEXTSlot<int, int> slot2 = [](int i) ->int { return i;};
        CHECK(11 == slot2(11));

        QEXTSlot<std::string, int &> slot3 = [](int &i)
        {
            i++;
            return std::string("name");
        };
        int iValue = 5;
        CHECK("name" == slot3(iValue));
        CHECK(6 == iValue);

        QEXTSlot<double, int, int> slot4 = [](int i, int j)
        {
            return double(i + j);
        };
        CHECK(3 == slot4(1, 2));


        QEXTSlot<double, int, int> slot5;
        auto mod = [](int i, int j)
        {
            return double(i + j);
        };
        slot5 = mod;
        CHECK(3 == slot5(1, 2));
    }

    TEST(qextSlotTest, teststdFunction)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot<int, int> slot;
        typedef std::function<int(int)> Functional;
        auto lambda = [](int a) ->int { return a; };
        Functional obj = lambda;
        slot = obj;
        CHECK(1 == slot(1));
    }


    TEST(qextSlotTest, teststdBind)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot<void> slot;

        std::string guestBook("karl");
        std::function<void()> func(std::bind(&egon, std::ref(guestBook)));
//        slot = std::bind(&egon, std::ref(guestBook)); // does not compile
        slot = func;
        slot();
        CHECK("egon(string 'karl')" == string);
    }
#endif

} // namespace qextSlotTest

#endif // QEXTSLOTTEST_H
