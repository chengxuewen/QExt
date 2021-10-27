#ifndef QEXTTRACKOBJECTFUNCTORTEST_H
#define QEXTTRACKOBJECTFUNCTORTEST_H

#include <qextTrackObjectFunctor.h>
#include <qextReferenceWrapper.h>
#include <qextObject.h>
#include <qextSignal.h>
#include <qextGlobal.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextTrackObjectFunctorTest
{

    static std::string *sg_string = QEXT_DECL_NULLPTR;


    struct Book : public QEXTObject
    {
        explicit Book(const std::string &name) : m_name(name) {}
        operator std::string &()
        {
            return m_name;
        }
        operator const std::string &() const
        {
            return m_name;
        }

        std::string m_name;
    };

    struct BarGroup4 : public QEXTObject
    {
    };

    class Functor1 : public QEXTFunctorBase
    {
    public:
        typedef std::string Return;

        Functor1(const BarGroup4 &bar) : m_bar(bar) {}

        std::string operator()(int i)
        {
            return (i < 0) ? "negative" : ((i > 0) ? "positive" : "zero");
        }

    private:
        const BarGroup4 &m_bar;
    };

    class Functor2 : public QEXTFunctorBase
    {
    public:
        typedef std::string Return;

        Functor2(const BarGroup4 &bar, const Book &book) : m_bar(bar), m_book(book) {}

        std::string operator()(int i, const std::string &str) const
        {
            std::string result = (i < 0) ? "negative, " : ((i > 0) ? "positive, " : "zero, ");
            result += str;
            result += m_book;
            return result;
        }

    private:
        const BarGroup4 &m_bar;
        const Book &m_book;
    };


    inline std::string &operator << (std::string &s, const Book &b)
    {
        s += b.m_name;
        return s;
    }

    void egon(std::string &str)
    {
        std::stringstream sstream;
        sstream << "egon(string '" << str << "')";
        *sg_string = sstream.str();
        str = "egon was here";
    }

    void fooGroup4(BarGroup4 &)
    {
        *sg_string = std::string("fooGroup4(BarGroup4&)");
    }



    TEST_GROUP(qextTrackObjectFunctorTest)
    {
    };

    TEST(qextTrackObjectFunctorTest, testSimple)
    {
        std::string string;
        sg_string = &string;

        QEXTSlot<std::string, int> sl1;
        {
            *sg_string = "";
            BarGroup4 bar4;
            QEXTObject obj;
            sl1 = qextTrackObjectFunctor(Functor1(bar4), obj);
            *sg_string += sl1(-2);
            CHECK("negative" == *sg_string);
        } // auto-disconnect sl1

        *sg_string = "";
        *sg_string += sl1(-2);
        std::cout << *sg_string << std::endl;
        CHECK("" == *sg_string);


        //    Allocate on the heap. valgrind can then find erroneous memory accesses.
        //            (There should be none, of course.)
        QEXTSlot<std::string, int, std::string> *psl2 = new QEXTSlot<std::string, int, std::string>;
        BarGroup4 *bar4 = new BarGroup4;
        Book *book4 = new Book("A Book");
        *sg_string = "";
        *psl2 = qextTrackObjectFunctor(Functor2(*bar4, *book4), *bar4, *book4);
        *sg_string += (*psl2)(0, "Book title: ");
        CHECK("zero, Book title: A Book" == *sg_string);

        *sg_string = "";
        delete book4; // auto-disconnect *psl2
        book4 = 0;
        *sg_string += (*psl2)(0, "Book title: ");
        CHECK("" == *sg_string);
        delete psl2;
        psl2 = 0;
        delete bar4;
        bar4 = 0;
    }



#if QEXT_CC_STD_11
    TEST(qextTrackObjectFunctorTest, testLambda)
    {
        std::string string;
        sg_string = &string;

        // auto-disconnect
        // If you want to auto-disconnect a slot with a C++11 lambda expression
        // that contains references to QEXTObject-derived objects, you must use
        // qextTrackObjectFunctor().
        QEXTSlot<std::string, int> sl1;
        QEXTSlot<void, std::string &> sl10;
        {
            *sg_string = "";
            Book guestBook("karl");
//            sl1 = [&guestBook](std::string &string)
//            {
//                string = guestBook.m_name;
//            }; // no auto-disconnect

            sl10 = qextTrackObjectFunctor([&guestBook](std::string & stream)
            {
                stream << guestBook;
            }, guestBook);
            sl10(*sg_string);
            CHECK("karl" == *sg_string);

        } // auto-disconnect sl10

        *sg_string = "";
        sl10(*sg_string);
        CHECK("" == *sg_string);

        // auto-disconnect
        QEXTSlot<std::string, int> sl2;
        QEXTSlot<void> sl20;
        {
            *sg_string = "";
            Book guestBook("karl");
//            sl2 = [&guest_book] ()
//            {
//                egon(guest_book);
//            }; // no auto-disconnect
//            sl2 = std::bind(&egon, std::ref(guestBook)); // does not compile (gcc 4.6.3)
            sl20 = qextTrackObjectFunctor([&guestBook] ()
            {
                egon(guestBook);
            }, guestBook);
            sl20();
            CHECK("egon(string 'karl')" == *sg_string);

            *sg_string = "";
            *sg_string += static_cast<const std::string &>(guestBook);
            CHECK("egon was here" == *sg_string);

        } // auto-disconnect sl20

        *sg_string = "";
        sl20();
        CHECK("" == *sg_string);

        {
            //struct bar : public QEXTObject {} some_bar;
            QEXTSignal<void> someSignal;
            {
                *sg_string = "";
                BarGroup4 someBar;
                //some_signal.connect(qextLambdaGroup(&foo,qextReferenceWrapper(some_bar)));
                // disconnected automatically if some_bar goes out of scope
                //some_signal.connect([&some_bar](){ foo_group4(some_bar); }); // no auto-disconnect
                //some_signal.connect(qextBindFunctor(&foo_group4, qextReferenceWrapper(some_bar))); // auto-disconnects, but we prefer C++11 lambda
                someSignal.connect(qextTrackObjectFunctor([&someBar]()
                {
                    fooGroup4(someBar);
                }, someBar));
                someSignal();
                CHECK("fooGroup4(BarGroup4&)" == *sg_string);

            } // auto-disconnect the lambda expression

            *sg_string = "";
            someSignal();
            CHECK("" == *sg_string);
        }
    }
#endif // #if QEXT_CC_STD_11

} // namespace qextTrackObjectFunctorTest

#endif // QEXTTRACKOBJECTFUNCTORTEST_H
