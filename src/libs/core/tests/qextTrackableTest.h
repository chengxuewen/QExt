#ifndef QEXTTRACKABLETEST_H
#define QEXTTRACKABLETEST_H

#include <qextObject.h>
#include <qextMemberFunctor.h>
#include <qextSlot.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextTrackableTest
{

    static std::string sg_string = "";


    class MYClass: public QEXTObject
    {
    public:
        void foo()
        {
            std::stringstream sstream;
            sstream << i;
            sg_string = sstream.str();
        }

        int i;
    };

    TEST_GROUP(qextTrackAbleTest)
    {
    };

    TEST(qextTrackAbleTest, testSimple)
    {
        QEXTSlot<void> slot;
        MYClass *myClass = new MYClass;
        myClass->i = 11;
        slot = qextMemberFunctor(myClass, &MYClass::foo);
        delete myClass;
        myClass = QEXT_DECL_NULLPTR;

        QEXTSlot<void> sl;
        {
            sg_string = "";
            MYClass t;
            t.i = 10;
            sl = qextMemberFunctor(&t, &MYClass::foo);
            sl();
            CHECK("10" == sg_string);
        }

        sg_string = "";
        sl();
        CHECK("" == sg_string);

        MYClass *myCLass = new MYClass;
        delete myCLass;
        myCLass = QEXT_DECL_NULLPTR;
    }

} // namespace qextTrackableTest

#endif // QEXTTRACKABLETEST_H
