#include <qexttrackobjectfunctor.h>
#include <qexttrackable.h>
#include <qextsignal.h>
#include <qextslot.h>
#include <qextglobal.h>

#include <QtTest>
#include <QDebug>

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

class QEXTTrackObjectFunctorTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();

#ifdef QEXT_CXX_STANDARD_11
    void testLambda();
#endif // #ifdef QEXT_CXX_STANDARD_11

public:
    static int sm_result;
    static QString sm_string;
};

int QEXTTrackObjectFunctorTest::sm_result = 0;
QString QEXTTrackObjectFunctorTest::sm_string = "";





struct Book : public QEXTTrackable
{
    explicit Book(const QString &name) : m_name(name) {}
    operator QString& () { return m_name; }
    operator const QString& () const { return m_name; }

    QString m_name;
};

struct BarGroup4 : public QEXTTrackable
{
};

class Functor1 : public QEXTFunctorBase
{
public:
    typedef QString ResultType;

    Functor1(const BarGroup4 &bar) : m_bar(bar) {}

    QString operator()(int i) {
        return (i < 0) ? "negative" : ((i>0) ? "positive" : "zero");
    }

private:
    const BarGroup4 &m_bar;
};

class Functor2 : public QEXTFunctorBase
{
public:
    typedef QString ResultType;

    Functor2(const BarGroup4 &bar, const Book &book) : m_bar(bar), m_book(book) {}

    QString operator()(int i, const QString &str) const {
        QString result = (i < 0) ? "negative, " : ((i>0) ? "positive, " : "zero, ");
        result += str;
        result += m_book;
        return result;
    }

private:
    const BarGroup4 &m_bar;
    const Book &m_book;
};


inline QString& operator << (QString &s, const Book &b) {
    s += b.m_name;
    return s;
}

void egon(QString &str) {
    QEXTTrackObjectFunctorTest::sm_string += QString("egon(string '%1')").arg(str);
    str = "egon was here";
}

void fooGroup4(BarGroup4&) {
    QEXTTrackObjectFunctorTest::sm_string += QString("fooGroup4(BarGroup4&)");
}






void QEXTTrackObjectFunctorTest::testSimple()
{
    QEXTSlot<QString, int> sl1;
    {
        QEXTTrackObjectFunctorTest::sm_string = "";
        BarGroup4 bar4;
        sl1 = qextTrackObjectFunctor(Functor1(bar4), bar4);
        QEXTTrackObjectFunctorTest::sm_string += sl1(-2);
        QVERIFY("negative" == QEXTTrackObjectFunctorTest::sm_string);
    } // auto-disconnect sl1

    QEXTTrackObjectFunctorTest::sm_string = "";
    QEXTTrackObjectFunctorTest::sm_string += sl1(-2);
    QVERIFY("" == QEXTTrackObjectFunctorTest::sm_string);


    //    Allocate on the heap. valgrind can then find erroneous memory accesses.
    //            (There should be none, of course.)
    QEXTSlot<QString, int, QString> *psl2 = new QEXTSlot<QString, int, QString>;
    BarGroup4 *bar4 = new BarGroup4;
    Book *book4 = new Book("A Book");
    QEXTTrackObjectFunctorTest::sm_string = "";
    *psl2 = qextTrackObjectFunctor(Functor2(*bar4, *book4), *bar4, *book4);
    QEXTTrackObjectFunctorTest::sm_string += (*psl2)(0, "Book title: ");
    QVERIFY("zero, Book title: A Book" == QEXTTrackObjectFunctorTest::sm_string);

    QEXTTrackObjectFunctorTest::sm_string = "";
    delete book4; // auto-disconnect *psl2
    book4 = 0;
    QEXTTrackObjectFunctorTest::sm_string += (*psl2)(0, "Book title: ");
    QVERIFY("" == QEXTTrackObjectFunctorTest::sm_string);
    delete psl2;
    psl2 = 0;
    delete bar4;
    bar4 = 0;
}



#ifdef QEXT_CXX_STANDARD_11
void QEXTTrackObjectFunctorTest::testLambda()
{
    return;
    // auto-disconnect
    // If you want to auto-disconnect a slot with a C++11 lambda expression
    // that contains references to sigc::trackable-derived objects, you must use
    // sigc::track_obj().
    QEXTSlot<void, QString&> sl10;
    {
        QEXTTrackObjectFunctorTest::sm_string = "";
        Book guestBook("karl");
        // sl1 = [&guest_book](std::ostringstream& stream){ stream << guest_book << "\n"; }; // no auto-disconnect
        sl10 = qextTrackObjectFunctor([&guestBook](QString &stream){ stream << guestBook; }, guestBook);
        sl10(QEXTTrackObjectFunctorTest::sm_string);
        QVERIFY("karl" == QEXTTrackObjectFunctorTest::sm_string);

    } // auto-disconnect sl10

    QEXTTrackObjectFunctorTest::sm_string = "";
    sl10(QEXTTrackObjectFunctorTest::sm_string);
    QVERIFY("" == QEXTTrackObjectFunctorTest::sm_string);

    // auto-disconnect
    QEXTSlot<void> sl20;
    {
        QEXTTrackObjectFunctorTest::sm_string = "";
        Book guestBook("karl");
        // sl2 = [&guest_book] () { egon(guest_book); }; // no auto-disconnect
        // sl2 = std::bind(&egon, std::ref(guest_book)); // does not compile (gcc 4.6.3)
        sl20 = qextTrackObjectFunctor([&guestBook] () { egon(guestBook); }, guestBook);
        sl20();
        QVERIFY("egon(string 'karl')" == QEXTTrackObjectFunctorTest::sm_string);

        QEXTTrackObjectFunctorTest::sm_string = "";
        QEXTTrackObjectFunctorTest::sm_string += static_cast<const QString&>(guestBook);
        QVERIFY("egon was here" == QEXTTrackObjectFunctorTest::sm_string);

    } // auto-disconnect sl20

    QEXTTrackObjectFunctorTest::sm_string = "";
    sl20();
    QVERIFY("" == QEXTTrackObjectFunctorTest::sm_string);


    // Code example in the documentation sigc++/adaptors/macros/track_obj.h.m4
    // -----------------------------------------------------------------------
    {
        //struct bar : public sigc::trackable {} some_bar;
        QEXTSignal<void> someSignal;
        {
            QEXTTrackObjectFunctorTest::sm_string = "";
            BarGroup4 someBar;
            //some_signal.connect(sigc::group(&foo,sigc::ref(some_bar)));
            // disconnected automatically if some_bar goes out of scope
            //some_signal.connect([&some_bar](){ foo_group4(some_bar); }); // no auto-disconnect
            //some_signal.connect(sigc::bind(&foo_group4, sigc::ref(some_bar))); // auto-disconnects, but we prefer C++11 lambda
            someSignal.connect(qextTrackObjectFunctor([&someBar](){ fooGroup4(someBar); }, someBar));
            someSignal();
            QVERIFY("FooGroup4(BarGroup4&)" == QEXTTrackObjectFunctorTest::sm_string);

        } // auto-disconnect the lambda expression

        QEXTTrackObjectFunctorTest::sm_string = "";
        someSignal();
        QVERIFY("" == QEXTTrackObjectFunctorTest::sm_string);
    }
}
#endif // #ifdef QEXT_CXX_STANDARD_11

QTEST_APPLESS_MAIN(QEXTTrackObjectFunctorTest)

#include <tst_qexttrackobjectfunctor.moc>
