#ifndef QEXTVARIANTTEST_H
#define QEXTVARIANTTEST_H

#include <qextGlobal.h>
#include <qextVariant.h>

#include <iostream>
#include <sstream>
#include <string>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextVariantTest
{

    const void *test_nullptr = QEXT_DECL_NULLPTR;

// The following tracer code originates as Oracle from Optional by
// Andrzej Krzemienski, https://github.com/akrzemi1/Optional.

    enum State
    {
        /* 0 */ default_constructed,
        /* 1 */ value_copy_constructed,
        /* 2 */ value_move_constructed,
        /* 3 */ copy_constructed,
        /* 4 */ move_constructed,
        /* 5 */ move_assigned,
        /* 6 */ copy_assigned,
        /* 7 */ value_copy_assigned,
        /* 8 */ value_move_assigned,
        /* 9 */ moved_from,
        /*10 */ value_constructed
    };

    struct Tracer
    {
        State state;
        static int instances;

        static void reset() QEXT_DECL_NOEXCEPT
        {
            instances = 0;
        }

        ~Tracer() QEXT_DECL_NOEXCEPT
        {
            --instances;
        }
        Tracer() QEXT_DECL_NOEXCEPT
        {
            ++instances;
            state = default_constructed;
        }

        Tracer(const Tracer &) QEXT_DECL_NOEXCEPT
        {
            ++instances;
            state = copy_constructed;
        }
        Tracer &operator=(const Tracer &) QEXT_DECL_NOEXCEPT
        {
            state = copy_assigned;
            return *this;
        }
    };

    int Tracer::instances = 0;

    struct TracerX : Tracer
    {
    };
    struct TracerY : Tracer
    {
    };

    struct V
    {
        State state;
        int value;

        V() : state(default_constructed), value(deflt()) {}
        V(int v) : state(value_constructed), value(v) {}
        V(V const &v) : state(copy_constructed), value(v.value) {}

        V &operator=(int v)
        {
            state = value_copy_assigned;
            value = v;
            return *this;
        }
        V &operator=(V const &v)
        {
            state = copy_assigned;
            value = v.value;
            return *this;
        }

        static int deflt()
        {
            return 42;
        }

        bool operator==(V const &other) const
        {
            return state == other.state && value == other.value;
        }
    };

    struct S
    {
        State state;
        V value;

        S() : state(default_constructed) {}
        S(V const &v) : state(value_copy_constructed), value(v) {}
        S(S const &s) : state(copy_constructed), value(s.value) {}

        S &operator=(V const &v)
        {
            state = value_copy_assigned;
            value = v;
            return *this;
        }
        S &operator=(const S &s)
        {
            state = copy_assigned;
            value = s.value;
            return *this;
        }

        bool operator==(S const &other) const
        {
            return state == other.state && value == other.value;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, V const &v)
    {
        QEXT_UNUSED(v)
        //    using lest::to_string;
        //    return os << "[V:" << to_string( v.value ) << "]";
        return os;
    }

    class NoDefaultConstruct
    {
        NoDefaultConstruct() {}
    };

    struct BlowCopyMoveConstruct
    {
        static bool blow;
        static void enable_blow()
        {
            blow = true;
        }
        static void disable_blow()
        {
            blow = false;
        }

        ~BlowCopyMoveConstruct() {}
        BlowCopyMoveConstruct(bool blow_ = true)
        {
            blow = blow_;
        }
        BlowCopyMoveConstruct(BlowCopyMoveConstruct const &)
        {
            if (blow)
            {
                throw 42;
            }
        }
        BlowCopyMoveConstruct &operator=(BlowCopyMoveConstruct const &)
        {
            return *this;
        }
    };

    bool BlowCopyMoveConstruct::blow = true;

    struct BlowCopyMoveAssign
    {
        ~BlowCopyMoveAssign() {};
        BlowCopyMoveAssign() {}
        BlowCopyMoveAssign(BlowCopyMoveAssign const &) {}
        BlowCopyMoveAssign &operator=(BlowCopyMoveAssign const &)
        {
            throw 42;
            return *this;
        }
    };

    typedef QEXTVariant< char, BlowCopyMoveConstruct > empty_variant_t;

    empty_variant_t make_empty_variant()
    {
        empty_variant_t var = 'a';

        try
        {
            var = BlowCopyMoveConstruct();
        }
        catch (...)
        {
        }

        return var;
    }

    empty_variant_t make_non_empty_variant()
    {
        return empty_variant_t('a');
    }

    template < typename T >
    std::size_t to_size_t(T v)
    {
        return v;
    }

    TEST_GROUP(qextUnionVariantTest) {};

    TEST(qextUnionVariantTest, simple)
    {
        QEXTVariant< int, NoDefaultConstruct > var1;
        (void)var1;

        QEXTVariant< QEXTMonostate, NoDefaultConstruct > var2;
        (void)var2;
    }

    TEST(qextUnionVariantTest, defaultConstruct)
    {
        QEXTVariant< S > var;

        CHECK(qextVariantGet< S >(var).value.value == V::deflt());
        CHECK(qextVariantGet< S >(var).value.state == default_constructed);
        CHECK(qextVariantGet< S >(var).state == default_constructed);
    }

    TEST(qextUnionVariantTest, copyConstruct)
    {
        S s(7);
        QEXTVariant< S > var1(s);
        QEXTVariant< S > var2(var1);

        CHECK(qextVariantGet< S >(var2).value.value == 7);
        CHECK(qextVariantGet< S >(var2).state == copy_constructed);
    }

    TEST(qextUnionVariantTest, currentIndexType)
    {
        QEXTVariant< int, S > vari(3);
        QEXTVariant< int, S > vars(S(7));

        CHECK(0u == vari.index());
        CHECK(1u == vars.index());
    }

    TEST(qextUnionVariantTest, copyAssign)
    {
        {
            Tracer::reset();
            {
                TracerY y;
                QEXTVariant< TracerX, TracerY > var1;
                QEXTVariant< TracerX, TracerY > var2;
                QEXTVariant< TracerX, TracerY > var3(y);

                CHECK(Tracer::instances == 4);

                var1 = var2;
                CHECK(Tracer::instances == 4);
                var1 = var3;
                CHECK(Tracer::instances == 4);
            }
            CHECK(Tracer::instances == 0);
        }

        {
            QEXTVariant< Tracer > var1;
            QEXTVariant< Tracer > var2;

            var1 = var2;

            CHECK(qextVariantGet< Tracer >(var1).state == copy_assigned);
        }

        {
            QEXTVariant< BlowCopyMoveAssign > var1;
            QEXTVariant< BlowCopyMoveAssign > var2;

            try
            {
                var1 = var2;
            }
            catch (...)
            {
            }

            CHECK_FALSE(var1.valuelessByException());
        }

        {
            QEXTVariant< int, BlowCopyMoveConstruct > var1;
            QEXTVariant< int, BlowCopyMoveConstruct > var2(BlowCopyMoveConstruct(false));

            BlowCopyMoveConstruct::enable_blow();

            CHECK_FALSE(var1.valuelessByException());

            try
            {
                var1 = var2;
            }
            catch (...)
            {
            }
        }
    }

    TEST(qextUnionVariantTest, elementValueConstruct)
    {
        V v(7);

        QEXTVariant< S > var(v);

        CHECK(qextVariantGet< S >(var).value.value == 7);
        CHECK(v.state != moved_from);
    }

    TEST(qextUnionVariantTest, elementCopyConstruct)
    {
        S s(7);

        QEXTVariant< S > var(s);

        CHECK(qextVariantGet< S >(var).value.value == 7);
        CHECK(qextVariantGet< S >(var).state == copy_constructed);
    }

    TEST(qextUnionVariantTest, elementConvertCopyConstruct)
    {
        int i = 7;

        QEXTVariant< double, std::string > var1(i);
        QEXTVariant< double, std::string > var2(7);

        CHECK(var1.index() == 0u);
        //    CHECK( get<0>(var1) == lest::approx(7) );

        CHECK(var2.index() == 0u);
        //    CHECK( get<0>(var2) == lest::approx(7) );
    }

    TEST(qextUnionVariantTest, elementValueCopyAssign)
    {

        {
            int seven = 7;
            QEXTVariant< int > var = 42;

            var = seven;

            CHECK(qextVariantGet< int >(var) == seven);
        }

        {
            V v(7);
            QEXTVariant< int, S > var1;
            QEXTVariant< int, S > var2;

            var1 = v;
            var2 = V(7); // copy for pre-C++11

            CHECK(qextVariantGet< S >(var1).value.value == 7);
            CHECK(v.state != moved_from);

            CHECK(qextVariantGet< S >(var1).value.value == 7);
        }
    }

    TEST(qextUnionVariantTest, elementCopyAssign)
    {
        S s(7);
        QEXTVariant< int, S > var1;
        QEXTVariant< int, S > var2;

        var1 = s;
        var2 = S(7); // copy for pre-C++11

        CHECK(qextVariantGet< S >(var1).value.value == 7);
        CHECK(s.state != moved_from);

        CHECK(qextVariantGet< S >(var2).value.value == 7);
    }

    TEST(qextUnionVariantTest, elementConvertCopyAssign)
    {
        char const *hello = "hello, world";
        QEXTVariant< int, std::string > var1;
        QEXTVariant< int, std::string > var2;

        var1 = hello;
        var2 = "hello, world";

        CHECK(qextVariantGet< 1 >(var1) == hello);
        CHECK(qextVariantGet< 1 >(var2) == "hello, world");
    }

    TEST(qextUnionVariantTest, swapVariants)
    {
        QEXTVariant< int, S > var1(1);
        QEXTVariant< int, S > var2(2);

        var1.swap(var2);

        CHECK(qextVariantGet< int >(var1) == 2);
        CHECK(qextVariantGet< int >(var2) == 1);
    }

    TEST(qextUnionVariantTest, swapVariantsDifferentIndex)
    {
        S s(7);
        QEXTVariant< int, S > vari(3);
        QEXTVariant< int, S > vars(s);

        vari.swap(vars);

        CHECK(s.value.value == qextVariantGet< S >(vari).value.value);
        CHECK(3 == qextVariantGet< int >(vars));
    }

//
// variant non-member functions:
//

    namespace
    {

        struct Doubler
        {
            template < class T >
            T operator()(T a) const
            {
                return a + a;
            }
        };
    } // namespace

    struct GenericVisitor1
    {
        std::string operator()(int val) const
        {
            std::ostringstream os;
            os << val;
            return os.str();
        }

        std::string operator()(std::string const &val) const
        {
            std::ostringstream os;
            os << val;
            return os.str();
        }
    };

    TEST(qextUnionVariantTest, visitContents)
    {
        typedef QEXTVariant< int, std::string > var_t;
        var_t vi = 7;
        var_t vs = std::string("hello");

        std::string ri = qextVariantVisit< std::string >(GenericVisitor1(), vi);
        std::string rs = qextVariantVisit< std::string >(GenericVisitor1(), vs);

        CHECK(ri == "7");
        CHECK(rs == "hello");
    }

    struct GenericVisitor2
    {
        template < typename T1, typename T2 >
        std::string operator()(T1 const &v1, T2 const &v2) const
        {
            std::ostringstream os;
            os << v1 << v2;
            return os.str();
        }
    };

    TEST(qextUnionVariantTest, visitContentsArgs2)
    {
        typedef QEXTVariant< int, std::string > var_t;
        var_t vi = 7;
        var_t vs = std::string("hello");

        std::string r = qextVariantVisit< std::string >(GenericVisitor2(), vi, vs);

        CHECK(r == "7hello");
    }

    struct GenericVisitor3
    {
        template < typename T1, typename T2, typename T3 >
        std::string operator()(const T1 &v1, const T2 &v2, const T3 &v3) const
        {
            std::ostringstream os;
            os << v1 << v2 << v3;
            return os.str();
        }
    };

    TEST(qextUnionVariantTest, visitContentsArgs3)
    {
        typedef QEXTVariant< int, std::string, double > var_t;
        var_t vi = 7;
        var_t vs = std::string("hello");
        var_t vd = 0.5;

        std::string r = qextVariantVisit< std::string >(GenericVisitor3(), vi, vs, vd);

        CHECK(r == "7hello0.5");
    }

    TEST(qextUnionVariantTest, checkForContentByType)
    {
        typedef QEXTVariant< int, long, double, std::string > var_t;
        var_t vi = 7;
        var_t vl = 7L;
        var_t vd = 7.0;
        var_t vs = std::string("hello");

        CHECK(qextHoldsAlternative< int >(vi));
        CHECK(qextHoldsAlternative< long >(vl));
        CHECK(qextHoldsAlternative< double >(vd));
        CHECK(qextHoldsAlternative< std::string >(vs));

        //#if ! variant_USES_STD_VARIANT // fires static_assert with g++ (GCC) 7.2.0:
        CHECK_FALSE(qextHoldsAlternative< char >(vi));
        CHECK_FALSE(qextHoldsAlternative< short >(vi));
        CHECK_FALSE(qextHoldsAlternative< float >(vd));

        CHECK_FALSE(qextHoldsAlternative< unsigned int >(vi));
        //#endif
    }

    TEST(qextUnionVariantTest, getElementByType)
    {
        QEXTVariant< int, S > var(S(7));

        CHECK(qextVariantGet< S >(var).value.value == 7);
    }

    TEST(qextUnionVariantTest, getElementByIndex)
    {
        QEXTVariant< int, S > var(S(7));

        CHECK(qextVariantGet< 1 >(var).value.value == 7);
    }

    TEST(qextUnionVariantTest, getPointerToElementOrNULLByType)
    {
        QEXTVariant< int, S > var(S(7));

        CHECK(test_nullptr == qextVariantGetIf< int >(&var));

        CHECK(test_nullptr != qextVariantGetIf< S >(&var));
        CHECK(qextVariantGetIf< S >(&var)->value.value == 7);
    }

    TEST(qextUnionVariantTest, getPointerToElementOrNULLByIndex)
    {
        QEXTVariant< int, S > var(S(7));

        CHECK(test_nullptr == qextVariantGetIf< 0 >(&var));

        CHECK(test_nullptr != qextVariantGetIf< 1 >(&var));
        CHECK(qextVariantGetIf< 1 >(&var)->value.value == 7);
    }

    TEST(qextUnionVariantTest, compareVariants)
    {
        QEXTVariant< int, double > v = 3, w = 7;

        CHECK(v == v);
        CHECK(v != w);
        CHECK(v < w);
        CHECK(w > v);
        CHECK(v <= v);
        CHECK(v <= w);
        CHECK(v >= v);
        CHECK(w >= v);

        CHECK_FALSE(v == w);
        CHECK_FALSE(v != v);
        CHECK_FALSE(w < v);
        CHECK_FALSE(v > w);
        CHECK_FALSE(w <= v);
        CHECK_FALSE(v >= w);
    }

    TEST(qextUnionVariantTest, swapVariantsSameIndexNonMember)
    {
        QEXTVariant< int, S > var1(1);
        QEXTVariant< int, S > var2(2);

        qextVariantSwap(var1, var2);

        CHECK(qextVariantGet< int >(var1) == 2);
        CHECK(qextVariantGet< int >(var2) == 1);
    }

    TEST(qextUnionVariantTest, swapVariantsDifferentIndexNonMember)
    {
        S s(7);
        QEXTVariant< int, S > vari(3);
        QEXTVariant< int, S > vars(s);

        qextVariantSwap(vari, vars);

        CHECK(s.value.value == qextVariantGet< S >(vari).value.value);
        CHECK(3 == qextVariantGet< int >(vars));
    }

//
// variant helper classes:
//

    TEST(qextUnionVariantTest, makeVariantDefaultConstructible)
    {
        QEXTVariant< QEXTMonostate, NoDefaultConstruct > var;
        (void)var;

        CHECK(true);
    }

    TEST(qextUnionVariantTest, indicatesInvalidVariantAccess)
    {
        QEXTVariant< char, int > v = 7;
        QEXTVariant< char, int > const c = 7;

        //    CHECK_THROWS( get<  0 >( v ), bad_variant_access );
        //    CHECK_THROWS( get<  0 >( c ), bad_variant_access );
        //    CHECK_THROWS( get<char>( v ), bad_variant_access );
        //    CHECK_THROWS( get<char>( c ), bad_variant_access );
    }

    namespace
    {
        struct t1
        {
        };
        struct t2
        {
        };
        struct t3
        {
        };
        struct t4
        {
        };
        struct t5
        {
        };
        struct t6
        {
        };
        struct t7
        {
        };
        struct t8
        {
        };
    } // namespace

    TEST(qextUnionVariantTest, obtainNumberOfElementTypes)
    {
        typedef QEXTVariant< t1 > var1;
        typedef QEXTVariant< t1, t2 > var2;
        typedef QEXTVariant< t1, t2, t3 > var3;
        typedef QEXTVariant< t1, t2, t3, t4 > var4;
        typedef QEXTVariant< t1, t2, t3, t4, t5 > var5;
        typedef QEXTVariant< t1, t2, t3, t4, t5, t6 > var6;
        typedef QEXTVariant< t1, t2, t3, t4, t5, t6, t7 > var7;
        //  typedef variant<t1, t2, t3, t4, t5, t6, t7, t8> var8;

        CHECK(1u == to_size_t(QEXTVariantSize< var1 >::value));
        CHECK(2u == to_size_t(QEXTVariantSize< var2 >::value));
        CHECK(3u == to_size_t(QEXTVariantSize< var3 >::value));
        CHECK(4u == to_size_t(QEXTVariantSize< var4 >::value));
        CHECK(5u == to_size_t(QEXTVariantSize< var5 >::value));
        CHECK(6u == to_size_t(QEXTVariantSize< var6 >::value));
        CHECK(7u == to_size_t(QEXTVariantSize< var7 >::value));
        //  EXPECT( 8u == to_size_t( variant_size<var8>::value ) );
    }

    TEST(qextUnionVariantTest, obtainNumberOfElementTypesNonStandard)
    {
        typedef QEXTVariant< t1 > var1;
        typedef QEXTVariant< t1, t2 > var2;
        typedef QEXTVariant< t1, t2, t3 > var3;
        typedef QEXTVariant< t1, t2, t3, t4 > var4;
        typedef QEXTVariant< t1, t2, t3, t4, t5 > var5;
        typedef QEXTVariant< t1, t2, t3, t4, t5, t6 > var6;
        typedef QEXTVariant< t1, t2, t3, t4, t5, t6, t7 > var7;
        //  typedef variant<t1, t2, t3, t4, t5, t6, t7, t8> var8;

        CHECK(1u == to_size_t(QEXT_VARIANT_SIZE_V(var1)));
        CHECK(2u == to_size_t(QEXT_VARIANT_SIZE_V(var2)));
        CHECK(3u == to_size_t(QEXT_VARIANT_SIZE_V(var3)));
        CHECK(4u == to_size_t(QEXT_VARIANT_SIZE_V(var4)));
        CHECK(5u == to_size_t(QEXT_VARIANT_SIZE_V(var5)));
        CHECK(6u == to_size_t(QEXT_VARIANT_SIZE_V(var6)));
        CHECK(7u == to_size_t(QEXT_VARIANT_SIZE_V(var7)));
        //  CHECK( 8u == to_size_t( variant_size_V( var8 ) ) );
    }

    TEST(qextUnionVariantTest, assignmentFromElementLvalueMustUseCopyAssignment)
    {
        QEXTVariant< V > var1;
        QEXTVariant< V > var2;
        V seven = 7;

        var1 = 7;
        var2 = seven;

        CHECK(qextVariantGet< V >(var1).state == copy_assigned);
        CHECK(qextVariantGet< V >(var2).state == copy_assigned);
    }

    namespace issue_31
    {

        struct CopyOnly
        {
            CopyOnly() {}
            CopyOnly(CopyOnly const &) {}
            CopyOnly &operator=(CopyOnly const &)
            {
                return *this;
            }
        };
    } // namespace issue_31

    TEST(qextUnionVariantTest, copyAssignmentFromVariantLvalueMustNotRequireElementMoveAssignment)
    {
        using namespace issue_31;

        QEXTVariant< CopyOnly > var1;
        QEXTVariant< CopyOnly > var2;

        var1 = var2;

        CHECK(true);
    }

    namespace issue_33
    {

        template < size_t i >
        class N
        {
            int k;
        };
    } // namespace issue_33

    TEST(qextUnionVariantTest, shouldNotCauseErroneousBadVariantAccessInGet)
    {
        if (4 == sizeof(int))
        {
            using issue_33::N;
            typedef QEXTVariant< N< 0 >, N< 1 >, N< 2 >, N< 3 >, int > variant_t;

            CHECK(qextVariantGet< int >(variant_t(13)));
        }
        else
        {
            CHECK(!!"max_index(): test is not available (sizeof(int) != 4)");
        }
    }

    namespace issue_39
    {

        struct tag_t
        {
        };

        struct myvisitor
        {
            const std::string &operator()(const int &) const
            {
                throw std::exception();
            }
            const std::string &operator()(const tag_t &) const
            {
                throw std::exception();
            }
            const std::string &operator()(const std::string &s) const
            {
                return s;
            }
        };
    } // namespace issue_39


} // namespace qextVariantTest

#endif // QEXTVARIANTTEST_H
