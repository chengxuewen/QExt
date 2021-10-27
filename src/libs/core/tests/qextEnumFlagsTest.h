#ifndef QEXTENUMFLAGSTEST_H
#define QEXTENUMFLAGSTEST_H

#include <qextEnumFlags.h>

#include <iostream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextEnumFlagsTest
{
    class MYClass
    {
    public:
        enum ETypeFlag
        {
            E_1 = (1),
            E_2 = (1 << 1),
            E_3 = (1 << 2),
            E_4 = (1 << 3),
            E_5 = (1 << 4),
            E_6 = (1 << 5),
        };
        QEXT_DECL_ENUMFLAGS(ETypeFlags, ETypeFlag)

        MYClass() {}
    };

    TEST_GROUP(qextEnumFlagsTest)
    {
    };

    TEST(qextEnumFlagsTest, testNoFlag)
    {
        MYClass::ETypeFlags flags;
        CHECK_FALSE(flags.testFlag(MYClass::E_1));
        CHECK_FALSE(flags.testFlag(MYClass::E_2));
        CHECK_FALSE(flags.testFlag(MYClass::E_3));
        CHECK_FALSE(flags.testFlag(MYClass::E_4));
        CHECK_FALSE(flags.testFlag(MYClass::E_5));
        CHECK_FALSE(flags.testFlag(MYClass::E_6));
    }

    TEST(qextEnumFlagsTest, testFlag)
    {
        MYClass::ETypeFlags flags(MYClass::E_1 | MYClass::E_2);
        CHECK(flags.testFlag(MYClass::E_1));
        CHECK(flags.testFlag(MYClass::E_2));
        CHECK_FALSE(flags.testFlag(MYClass::E_3));
        CHECK_FALSE(flags.testFlag(MYClass::E_4));
        CHECK_FALSE(flags.testFlag(MYClass::E_5));
        CHECK_FALSE(flags.testFlag(MYClass::E_6));
    }

    TEST(qextEnumFlagsTest, testCopyCtr)
    {
        MYClass::ETypeFlags flags(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags flags2(flags);
        CHECK(flags.testFlag(MYClass::E_1));
        CHECK(flags.testFlag(MYClass::E_2));
        CHECK_FALSE(flags.testFlag(MYClass::E_3));
        CHECK_FALSE(flags.testFlag(MYClass::E_4));
        CHECK_FALSE(flags.testFlag(MYClass::E_5));
        CHECK_FALSE(flags.testFlag(MYClass::E_6));
    }

    TEST(qextEnumFlagsTest, testCopyOperator)
    {
        MYClass::ETypeFlags flags(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags flags2 = flags;
        CHECK(flags2.testFlag(MYClass::E_1));
        CHECK(flags2.testFlag(MYClass::E_2));
        CHECK_FALSE(flags2.testFlag(MYClass::E_3));
        CHECK_FALSE(flags2.testFlag(MYClass::E_4));
        CHECK_FALSE(flags2.testFlag(MYClass::E_5));
        CHECK_FALSE(flags2.testFlag(MYClass::E_6));
    }

    TEST(qextEnumFlagsTest, testAnd)
    {
        MYClass::ETypeFlags flags(MYClass::E_1 | MYClass::E_2);
        flags &= 0;
        CHECK_FALSE(flags.testFlag(MYClass::E_1));
        CHECK_FALSE(flags.testFlag(MYClass::E_2));

        MYClass::ETypeFlags flags1(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags flags2(MYClass::E_1);
        MYClass::ETypeFlags flags3 = flags1 & flags2;
        CHECK(flags3.testFlag(MYClass::E_1));
        CHECK_FALSE(flags3.testFlag(MYClass::E_2));

        MYClass::ETypeFlags flags4(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags flags5 = flags1 & MYClass::E_1;
        CHECK(flags5.testFlag(MYClass::E_1));
        CHECK_FALSE(flags5.testFlag(MYClass::E_2));
    }

    TEST(qextEnumFlagsTest, testOr)
    {
        MYClass::ETypeFlags flags(MYClass::E_1 | MYClass::E_2);
        CHECK(flags.testFlag(MYClass::E_1));
        CHECK(flags.testFlag(MYClass::E_2));
        CHECK_FALSE(flags.testFlag(MYClass::E_3));
        CHECK_FALSE(flags.testFlag(MYClass::E_4));
        CHECK_FALSE(flags.testFlag(MYClass::E_5));
        CHECK_FALSE(flags.testFlag(MYClass::E_6));
        flags |= MYClass::E_3;
        CHECK(flags.testFlag(MYClass::E_3));

        MYClass::ETypeFlags hasFlags(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags noFlags;
        noFlags |= hasFlags;
        CHECK(noFlags.testFlag(MYClass::E_1));
        CHECK(noFlags.testFlag(MYClass::E_2));

        MYClass::ETypeFlags flags1(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags flags2(MYClass::E_1);
        MYClass::ETypeFlags flags3 = flags1 | flags2;
        CHECK(flags3.testFlag(MYClass::E_1));
        CHECK(flags3.testFlag(MYClass::E_2));

        MYClass::ETypeFlags flags4(MYClass::E_1);
        MYClass::ETypeFlags flags5 = flags1 | MYClass::E_2;
        CHECK(flags5.testFlag(MYClass::E_1));
        CHECK(flags5.testFlag(MYClass::E_2));
    }


    TEST(qextEnumFlagsTest, testXor)
    {
        MYClass::ETypeFlags flags(MYClass::E_1 | MYClass::E_2);
        CHECK(flags.testFlag(MYClass::E_1));
        CHECK(flags.testFlag(MYClass::E_2));
        flags ^= MYClass::E_1;
        CHECK_FALSE(flags.testFlag(MYClass::E_1));

        MYClass::ETypeFlags flags2(MYClass::E_2);
        flags ^= flags2;
        CHECK_FALSE(flags.testFlag(MYClass::E_2));

        MYClass::ETypeFlags flags3(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags flags4(MYClass::E_1);
        MYClass::ETypeFlags flags5 = flags3 ^ flags4;
        CHECK_FALSE(flags5.testFlag(MYClass::E_1));
        CHECK(flags5.testFlag(MYClass::E_2));

        MYClass::ETypeFlags flags6(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags flags7 = flags6 ^ MYClass::E_1;
        CHECK_FALSE(flags7.testFlag(MYClass::E_1));
        CHECK(flags7.testFlag(MYClass::E_2));
    }


    TEST(qextEnumFlagsTest, testNegation)
    {
        MYClass::ETypeFlags flags(MYClass::E_1 | MYClass::E_2);
        MYClass::ETypeFlags flags1 = ~flags;
        CHECK_FALSE(flags1.testFlag(MYClass::E_1));
        CHECK_FALSE(flags1.testFlag(MYClass::E_2));
        CHECK(flags1.testFlag(MYClass::E_3));
        CHECK(flags1.testFlag(MYClass::E_4));
        CHECK(flags1.testFlag(MYClass::E_5));
        CHECK(flags1.testFlag(MYClass::E_6));
    }

    TEST(qextEnumFlagsTest, testCheck)
    {
        MYClass::ETypeFlags flags(MYClass::E_1 | MYClass::E_2);
        CHECK_FALSE(!flags);

        MYClass::ETypeFlags flags1;
        CHECK(!flags1);
    }
}

#endif // QEXTENUMFLAGSTEST_H
