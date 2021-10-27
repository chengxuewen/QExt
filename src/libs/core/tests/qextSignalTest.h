#ifndef QEXTSIGNALTEST_H
#define QEXTSIGNALTEST_H

#include <qextSignal.h>
#include <qextSlot.h>
#include <qextBindFunctor.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>
#include <qextConnection.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextSignalTest
{
    static std::string *sg_string = QEXT_DECL_NULLPTR;

    int foo(int i)
    {
        std::stringstream sstream;
        sstream << "foo(int " << i << ") ";
        *sg_string += sstream.str();
        return 1;
    }

    int bar(float i)
    {
        std::stringstream sstream;
        sstream << "bar(float " << i << ") ";
        *sg_string += sstream.str();
        return 1;
    }

    struct A : public QEXTObject
    {
        int foo(int i)
        {
            std::stringstream sstream;
            sstream << "A::foo(int " << i << ") ";
            *sg_string += sstream.str();
            return i;
        }

        int foo1(int i)
        {
            const int result = 20 * i - 14;
            std::stringstream sstream;
            sstream << "A::foo1(int " << result << ") ";
            *sg_string = sstream.str();
            return result;
        }

        void bar(std::string &str)
        {
            std::stringstream sstream;
            sstream << "A::bar(string '" << str << "') ";
            *sg_string = sstream.str();
            str = "bar was here";
        }
    };

    void goodByeWorld()
    {
        *sg_string += "Good bye world!";
    }

    struct B : public QEXTObject
    {
        B()
        {
            m_signal.connect(this, &B::destroy);
            m_signal.connect(this, &B::boom);
            m_signal.connect(&goodByeWorld);
        }
        ~B() {}

        // Calling destroy() during signal send seems weird!
        // However, if this works, anything will work!
        void destroy()
        {
            delete this;
        }

        void boom()
        {
            *sg_string = "boom!";
        }

        void send()
        {
            m_signal.send();
        }

        QEXTSignal<void> m_signal;
    };



    QEXTConnection connection;
    class HandlerClass : public QEXTObject
    {
    public:
        void handler()
        {
            *sg_string = "handler called";
            connection.disconnect();
        }
    };


    struct arithmetic_mean_accumulator
    {
        typedef double Return;
        template<typename T_iterator>
        double operator()(T_iterator first, T_iterator last) const
        {
            double value_ = 0;
            int n_ = 0;
            for (; first != last; ++first, ++n_)
            {
                value_ += *first;
            }
            return (n_ ? value_ / n_ : -1); // empty slot list <=> n_==0
        }
    };

    template<typename  Ret>
    struct vector_accumulator
    {
        typedef std::vector<Ret> Return;

        template<typename T_iterator>
        Return operator()(T_iterator first, T_iterator last) const
        {
            Return vec;
            for (; first != last; ++first)
            {
                vec.push_back(*first);
            }
            return vec;
        }
    };



    int ident(int i)
    {
        return i;
    }

    template<typename T>
    struct min_accum
    {
        typedef T Return;

        template<typename T_iterator>
        Return operator()(T_iterator i1, T_iterator i2)
        {
            if (i1 == i2)
            {
                return *i2;
            }
            T_iterator smallest = i1;

            while (++i1 != i2)
                if (*i1 < *smallest)    // or: if (comp(*first,*smallest)) for version (2)
                {
                    smallest = i1;
                }
            return *smallest;
        }
    };

    int foo1(int i)
    {
        const int result = 3 * i + 1;
        std::stringstream sstream;
        sstream << "foo1: " << result << ", ";
        *sg_string = sstream.str();
        return result;
    }

    int bar1(double i)
    {
        const int result = 5 * int(i) - 3;
        std::stringstream sstream;
        sstream << "bar1: " << i << ", ";
        *sg_string = sstream.str();
        return result;
    }



    TEST_GROUP(qextSignalTest) {};

    TEST(qextSignalTest, testEmptySignal)
    {
        std::string string;
        sg_string = &string;

        QEXTSignal<int, int> sig;
        CHECK(0 == sig.size());
        *sg_string = "";
        sig(0);
        CHECK("" == *sg_string);
    }

    TEST(qextSignalTest, testConnectSlots)
    {
        std::string string;
        sg_string = &string;

        QEXTSignal<int, int> sig;
        // connect some slots before emitting & test auto-disconnection
        {
            *sg_string = "";
            A a;
            sig.connect(&foo);
            sig.connect(&a, &A::foo);
            sig.connect(&bar);
            CHECK(3 == sig.size());
            sig(1);
            CHECK("foo(int 1) A::foo(int 1) bar(float 1) " == *sg_string);
        }
        *sg_string = "";
        sig(2);
        CHECK(2 == sig.size());
        CHECK("foo(int 2) bar(float 2) " == *sg_string);
    }

    TEST(qextSignalTest, testReference)
    {
        std::string string;
        sg_string = &string;

        *sg_string = "";
        A a;
        std::string str("guest book");
        QEXTSignal<void, std::string &> sigstr;
        sigstr.connect(&a, &A::bar);
        sigstr(str);
        *sg_string += str;
        CHECK("A::bar(string 'guest book') bar was here" == *sg_string);
    }

    TEST(qextSignalTest, testCompareOperator)
    {
        std::string string;
        sg_string = &string;

        A a;
        QEXTSignal<void, std::string &> sigstr1;
        sigstr1.connect(&a, &A::bar);
        QEXTSignal<void, std::string &> sigstr2;
        CHECK_FALSE(sigstr1 == sigstr2);
        sigstr2 = sigstr1;
        CHECK(sigstr1 == sigstr2);

        sigstr2.connect(&a, &A::bar);
        CHECK_FALSE(sigstr1 == sigstr2);
    }

    TEST(qextSignalTest, testCopyOperator)
    {
        std::string string;
        sg_string = &string;

        QEXTSignal<int, int> sigstr1;
        sigstr1.connect(&foo);
        QEXTSignal<int, int> sigstr2;
        sigstr2 = sigstr1;

        *sg_string = "";
        sigstr1(3);
        CHECK("foo(int 3) " == *sg_string);

        *sg_string = "";
        sigstr2(2);
        CHECK("foo(int 2) " == *sg_string);

        sigstr2.connect(&foo);
        CHECK_FALSE(sigstr1 == sigstr2);
        *sg_string = "";
        sigstr2(2);
        CHECK("foo(int 2) foo(int 2) " == *sg_string);
    }

    TEST(qextSignalTest, testMakeSlot)
    {
        std::string string;
        sg_string = &string;

        QEXTSignal<int, int> sig;
        *sg_string = "";
        sig.connect(&foo);
        QEXTSignal<int, int> sig2;
        sig2.connect(sig.makeSlot());
        sig2(3);
        CHECK("foo(int 3) " == *sg_string);
    }

    TEST(qextSignalTest, testDisconnect)
    {
        std::string string;
        sg_string = &string;

        QEXTSignal<int, int> sig;
        QEXTSignal<int, int>::Iterator confoo;
        QEXTSignal<int, int>::Iterator conbar;

        {
            *sg_string = "";
            A a;
            sig.connect(&a, &A::foo);
            confoo = sig.connect(qextPointerFunctor(&foo));
            conbar = sig.connect(qextPointerFunctor(&bar));
            CHECK(3 == sig.size());
            sig(1);
            CHECK("A::foo(int 1) foo(int 1) bar(float 1) " == *sg_string);
        }                     // auto disconnection! iterators stay valid after disconnections.

        *sg_string = "";
        sig(2);
        CHECK(2 == sig.size());
        CHECK("foo(int 2) bar(float 2) " == *sg_string);

        QEXTConnection cona;  // connection objects are safe to use beyond the life time of a signal.
        *sg_string = "";
        A a;                  // iterators stay valid after further connections.
        cona = sig.slotList().insert(conbar, qextMemberFunctor(&a, &A::foo));
        CHECK(3 == sig.size());
        sig(3);
        CHECK("foo(int 3) A::foo(int 3) bar(float 3) " == *sg_string);

        *sg_string = "";
        conbar->disconnect(); // manual disconnection
        CHECK(2 == sig.size());
        sig(4);
        CHECK("foo(int 4) A::foo(int 4) " == *sg_string);

        *sg_string = "";
        confoo->disconnect(); // manual disconnection
        CHECK(1 == sig.size());
        sig(5);
        CHECK("A::foo(int 5) " == *sg_string);

        *sg_string = "";
        cona.disconnect();    // manual disconnection
        CHECK(0 == sig.size());
        sig(6);
        CHECK("" == *sg_string);

        cona.disconnect();    // already disconnected -> legal with connection objects, however, nothing happens ...

        *sg_string = "";
        B *b = new B;
        b->send();
        CHECK("Good bye world!" == *sg_string);
    }

    TEST(qextSignalTest, testDisconnectDuringEmit)
    {
        std::string string;
        sg_string = &string;

        HandlerClass instance;

        *sg_string = "";
        QEXTSignal<void> signal_test;
        connection = signal_test.connect(instance, &HandlerClass::handler);
        signal_test.send();
        CHECK("handler called" == *sg_string);
    }

    TEST(qextSignalTest, testAccumulated)
    {
        std::string string;
        sg_string = &string;

        QEXTSignal<int, int>::Accumulated<arithmetic_mean_accumulator> sig;
        QEXTSignal<int, int>::Accumulated<vector_accumulator<int> > sig_vec;

        CHECK(-1 == sig(0));
        CHECK(sig_vec(0).empty());

        A a;
        sig.connect(&foo1);
        sig.connect(&a, &A::foo1);
        sig.connect(&bar1);

        sig_vec.connect(&foo1);
        sig_vec.connect(&a, &A::foo1);
        sig_vec.connect(&bar1);

        char buf[1024] = "";

        double dres = sig(1);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%.3f", dres);
        CHECK("4.000" == std::string(buf));

        dres = sig(11);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%.3f", dres);
        CHECK("97.333" == std::string(buf));

        std::vector<int> res1 = sig_vec(1);
        *sg_string = "";
        for (std::vector<int>::iterator i = res1.begin(); i != res1.end(); ++i)
        {
            std::stringstream sstream;
            sstream << *i << " ";
            *sg_string += sstream.str();
        }
        CHECK("4 6 2 " == *sg_string);

        std::vector<int> res3 = sig_vec(3);
        *sg_string = "";
        for (std::vector<int>::iterator i = res3.begin(); i != res3.end(); ++i)
        {
            std::stringstream sstream;
            sstream << *i << " ";
            *sg_string += sstream.str();
        }
        CHECK("10 46 12 " == *sg_string);
    }

    TEST(qextSignalTest, testAccumulatedIter)
    {
        std::string string;
        sg_string = &string;

        QEXTSignal<int>::Accumulated<min_accum<int> > signal;

        signal.connect(qextBindFunctor(&ident, 3));
        signal.connect(qextBindFunctor(&ident, 1));
        signal.connect(qextBindFunctor(&ident, 42));

        CHECK(1 == signal.send());
    }

#if QEXT_CC_STD_11
    TEST(qextSignalTest, teststdLambda)
    {
        QEXTSignal<int> readValue;
        int data = 1000;
        readValue.connect([&data] () -> int { return data; });
        CHECK(1000 == readValue());
    }
#endif
}

#endif // QEXTSIGNALTEST_H
