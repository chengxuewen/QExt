#ifndef QEXTBINDRETURNFUNCTORTEST_H
#define QEXTBINDRETURNFUNCTORTEST_H

#include <qextObject.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>
#include <qextReferenceWrapper.h>
#include <qextBindReturnFunctor.h>
#include <qextBindFunctor.h>
#include <qextSlot.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextBindReturnFunctorTest
{

    static std::string sg_string = "";

    struct Foo
    {
        void operator()(int i)
        {
            std::stringstream sstream;
            sstream << "Foo(int " << i << ") ";
            sg_string = sstream.str();
        }

        float operator()(float i)
        {
            std::stringstream sstream;
            sstream << "Foo(float " << i << ") ";
            sg_string = sstream.str();
            return i * 5;
        }
    };

    class Bar : public QEXTObject
    {
    public:
        Bar(int i = 0) : m_i(i) {}
        operator int()
        {
            return m_i;
        }
        int m_i;
    };



    TEST_GROUP(qextBindReturnFunctorTest)
    {
    };

    TEST(qextBindReturnFunctorTest, testSimple)
    {
        CHECK(-12345 == qextBindReturnFunctor(Foo(), -12345)(5));
        CHECK("Foo(int 5) " == sg_string);
    }

    TEST(qextBindReturnFunctorTest, testReferences)
    {
        std::string str("guest book");

        qextBindReturnFunctor<QEXTReferenceWrapper<std::string> >(Foo(), qextReferenceWrapper(str))(6) = "main";
        sg_string += str;
        CHECK("Foo(int 6) main" == sg_string);
    }

    TEST(qextBindReturnFunctorTest, testAutoDisconnect)
    {
        QEXTSlot<int, int> slot;
        {
            Bar choco(-1);
            slot = qextBindReturnFunctor(Foo(), qextReferenceWrapper(choco));
            CHECK(-1 == slot(7));
            CHECK("Foo(int 7) " == sg_string);
        } // auto-disconnect

        CHECK(0 == slot(8));
    }

} // namespace qextBindReturnFunctorTest

#endif // QEXTBINDRETURNFUNCTORTEST_H
