#include <qextInvoke.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

#include <utility>
#include <iostream>

namespace
{

constexpr int f42()
{
    return 42;
}

constexpr int f42_nef() QEXT_INVOKE_NOEXCEPT_OP( false )
{
    return 42;
}

constexpr int arg( int a  )
{
    return a;
}

constexpr int add( int a, int b )
{
    return a + b;
}

struct holder
{
    int v;

    constexpr holder( int v_) : v(v_) {}

    constexpr int val() const
    {
        return v;
    }

    constexpr int add( int a ) const
    {
        return v + a;
    }

    constexpr int add_constref( int const & a ) const
    {
        return v + a;
    }

    constexpr int add_nonconst( int a )
    {
        return v + a;
    }

    void change_arg( int & a ) const
    {
        a = v;
    }
};

struct functor
{
    constexpr int operator()() const
    {
        return 42;
    }

    constexpr int operator()(int i) const
    {
        return i;
    }
};
}

class QExtInvokeTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void invoke();
    void invokeconstexpr();
    void invokeapply();
    void invokeapplyconstexpr();
    void other();
};


void QExtInvokeTest::invoke()
{
    //("invoke: a free function, no arguments")
    {
        QVERIFY( qextInvoke( f42 ) == 42 );
    }

    //("invoke: a free function, no arguments, noexcept(false) (C++11)")
    {
        QVERIFY( qextInvoke( f42_nef ) == 42 );
    }

    //("invoke: a free function, 1 argument")
    {
        QVERIFY( qextInvoke( arg, 7 ) == 7 );
    }

    //("invoke: a free function, 2 arguments")
    {
        QVERIFY( qextInvoke( add, 1, 2 ) == 3 );
    }

    //("invoke: a member function, no arguments")
    {
        const holder v(42);

        QVERIFY( qextInvoke( &holder::val, v ) == 42 );
    }

    //("invoke: a member function, 1 argument")
    {
        const holder v(1);

        QVERIFY( qextInvoke( &holder::add, v, 2 ) == 3 );
    }

    //("invoke: a member function, 1 const ref argument")
    {
        const holder v(1);

        QVERIFY( qextInvoke( &holder::add_constref, v, 2 ) == 3 );
    }

    //("invoke: a non-const member function, 1 argument")
    {
        /*const*/ holder v(1);

        QVERIFY( qextInvoke( &holder::add_nonconst, v, 2 ) == 3 );
    }

    //("invoke: a member function, changing its reference argument")
    {
        int arg = 7;
        holder v(42);

        qextInvoke( &holder::change_arg, v, arg );

        QVERIFY( arg == 42 );
    }

    //("invoke: (access) a data member - via const object ref")
    {
        const holder h(42);

        QVERIFY( qextInvoke( &holder::v, h ) == 42 );
    }

    //("invoke: (access) a data member - via const object ptr")
    {
        const holder h(42);

        QVERIFY( qextInvoke( &holder::v, &h ) == 42 );
    }

    //("invoke: (access) a data member - via non-const object ref")
    {
        holder h(42);

        QVERIFY( qextInvoke( &holder::v, h ) == 42 );
    }

    //("invoke: (access) a data member - via non-const object ptr")
    {
        holder h(42);

        QVERIFY( qextInvoke( &holder::v, &h ) == 42 );
    }

    //("invoke: change an invoked (accessed) data member - via non-const object ref")
    {
        holder h(42);

        qextInvoke( &holder::v, h ) = 7;

        QVERIFY( h.v == 7 );
    }

    //("invoke: change an invoked (accessed) data member - via non-const object ptr")
    {
        holder h(42);

        qextInvoke( &holder::v,  &h ) = 7;

        QVERIFY( h.v == 7 );
    }

    //("invoke: a function object, no arguments")
    {
        QVERIFY( qextInvoke( functor() ) == 42 );
    }

    //("invoke: a function object, 1 argument")
    {
        QVERIFY( qextInvoke( functor(), 42 ) == 42 );
    }

    //("invoke: a lambda, no arguments")
    {
        QVERIFY( qextInvoke( [](){ return 42; } ) == 42 );
    }

    //("invoke: a lambda, 1 argument")
    {
        QVERIFY( qextInvoke( [](int a){ return a; }, 42 ) == 42 );
    }
}

void QExtInvokeTest::invokeconstexpr()
{

    //("invoke: a free function, no arguments - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr auto constexpr_result = qextInvoke( f42 );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a free function, no arguments, noexcept(false) (C++11) - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr auto constexpr_result = qextInvoke( f42_nef );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a free function, 1 argument - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr auto constexpr_result = qextInvoke( arg, 7 );

        QVERIFY( constexpr_result == 7 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a free function, 2 arguments - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr auto constexpr_result = qextInvoke( add, 1, 2 );

        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a member function, no arguments - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr holder v(42);
        constexpr auto constexpr_result = qextInvoke( &holder::val, v );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a member function, 1 argument - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr holder v(1);
        constexpr auto constexpr_result = qextInvoke( &holder::add, v, 2 );

        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a member function, 1 const ref argument - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr holder v(1);
        constexpr auto constexpr_result = qextInvoke( &holder::add_constref, v, 2 );

        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    // //("invoke: a non-const member function, 1 argument - constexpr")
    // {
    // #if QEXT_INVOKE_CPP11_OR_GREATER
    //     constexpr holder v(1);
    //     constexpr auto constexpr_result = qextInvoke( &holder::add_nonconst, v, 2 );
    //
    //     QVERIFY( constexpr_result == 3 );
    // #else
    //     QSKIP( "invoke(): constexpr is not available (no C++11)" );
    // #endif
    // }

    // //("invoke: a member function, changing its reference argument - constexpr")
    // {
    // #if QEXT_INVOKE_CPP11_OR_GREATER
    //     int arg = 7;
    //     constexpr holder v(42);
    //
    //     qextInvoke( &holder::change_arg, v, arg );
    //
    //     QVERIFY( arg == 42 );
    // #else
    //     QSKIP( "invoke(): constexpr is not available (no C++11)" );
    // #endif
    // }

    //("invoke: (access) a data member - via const object ref - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr holder h(42);
        constexpr auto constexpr_result = qextInvoke( &holder::v, h );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: (access) a data member - via const object ptr - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr holder h(42);
        constexpr auto constexpr_result = qextInvoke( &holder::v, &h );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    // //("invoke: (access) a data member - via non-const object ref - constexpr")
    // {
    // #if QEXT_INVOKE_CPP11_OR_GREATER
    //     holder h(42);
    //     constexpr auto constexpr_result = qextInvoke( &holder::v, h );

    //     QVERIFY( constexpr_result == 42 );
    // #else
    //     QSKIP( "invoke(): constexpr is not available (no C++11)" );
    // #endif
    // }

    // //("invoke: (access) a data member - via non-const object ptr - constexpr")
    // {
    // #if QEXT_INVOKE_CPP11_OR_GREATER
    //     holder h(42);
    //     constexpr auto constexpr_result = qextInvoke( &holder::v, &h );

    //     QVERIFY( constexpr_result == 42 );
    // #else
    //     QSKIP( "invoke(): constexpr is not available (no C++11)" );
    // #endif
    // }

    // //("invoke: change an invoked (accessed) data member - via non-const object ref - constexpr")
    // {
    // #if QEXT_INVOKE_CPP11_OR_GREATER
    //     holder h(42);

    //     qextInvoke( &holder::v, h ) = 7;

    //     QVERIFY( h.v == 7 );
    // #else
    //     QSKIP( "invoke(): constexpr is not available (no C++11)" );
    // #endif
    // }

    // //("invoke: change an invoked (accessed) data member - via non-const object ptr - constexpr")
    // {
    // #if QEXT_INVOKE_CPP11_OR_GREATER
    //     holder h(42);

    //     qextInvoke( &holder::v,  &h ) = 7;

    //     QVERIFY( h.v == 7 );
    // #else
    //     QSKIP( "invoke(): constexpr is not available (no C++11)" );
    // #endif
    // }

    //("invoke: a function object, no arguments - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr auto constexpr_result = qextInvoke( functor() );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a function object, 1 argument - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr auto constexpr_result = qextInvoke( functor(), 42 );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr is not available (no C++11, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a lambda, no arguments - constexpr (C++17)")
    {
#if QEXT_INVOKE_CPP17_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr auto constexpr_result = qextInvoke( [](){ return 42; } );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr closure is not available (no C++17, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }

    //("invoke: a lambda, 1 argument - constexpr (C++17)")
    {
#if QEXT_INVOKE_CPP17_OR_GREATER && !(QEXT_INVOKE_USES_STD_INVOKE && QEXT_INVOKE_BETWEEN(QEXT_INVOKE_COMPILER_MSVC_VER, 1910, 1920))
        constexpr auto constexpr_result = qextInvoke( [](int a){ return a; }, 42 );

        QVERIFY( constexpr_result == 42 );
#else
        QSKIP( "invoke(): constexpr closure is not available (no C++17, or VC141/1910/VS2017 with std::invoke())" );
#endif
    }
}

void QExtInvokeTest::invokeapply()
{
#if QEXT_INVOKE_CPP11_OR_GREATER
    QVERIFY( nonstd::apply( add, std::pair<int, int>(1, 2) ) == 3 );
#else
    QSKIP( "apply() is not available (no C++11)" );
#endif

    //("apply: a function object, std::tuple of 2 arguments (C++11)")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        QVERIFY( nonstd::apply( add, std::tuple<int, int>(1, 2) ) == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }

    //("apply: a function object, std::array of 2 arguments (C++11)")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        QVERIFY( nonstd::apply( add, std::array<int,2>({ 1, 2}) ) == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }

    //("apply: a lambda, std::pair of 2 arguments (C++11)")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        QVERIFY( nonstd::apply( [](int a, int b){ return a + b; }, std::pair<int, int>(1, 2)) == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }

    //("apply: a lambda, std::tuple of 2 arguments (C++11)")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        QVERIFY( nonstd::apply( add, std::tuple<int, int>(1, 2) ) == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }

    //("apply: a lambda, std::array of 2 arguments (C++11)")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        QVERIFY( nonstd::apply( [](int a, int b){ return a + b; }, std::array<int,2>({ 1, 2})) == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }
}

void QExtInvokeTest::invokeapplyconstexpr()
{
#if 0
    //("apply: a function object, std::pair of 2 arguments (C++11) - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        constexpr auto constexpr_result = qextInvokeApply( add, std::pair<int, int>(1, 2) );
        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }

    //("apply: a function object, std::tuple of 2 arguments (C++11) - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        constexpr auto constexpr_result = qextInvokeApply( add, std::tuple<int, int>(1, 2) );
        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }

    //("apply: a function object, std::array of 2 arguments (C++11) - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        constexpr auto constexpr_result = qextInvokeApply( add, std::array<int,2>({ 1, 2}) );
        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }

    //("apply: a lambda, std::pair of 2 arguments (C++11) - constexpr")
    {
#if QEXT_INVOKE_CPP17_OR_GREATER
        constexpr auto constexpr_result = qextInvokeApply( [](int a, int b){ return a + b; }, std::pair<int, int>(1, 2) );
        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "apply(): constexpr closure is not available (no C++17)" );
#endif
    }

    //("apply: a lambda, std::tuple of 2 arguments (C++11) - constexpr")
    {
#if QEXT_INVOKE_CPP11_OR_GREATER
        constexpr auto constexpr_result = qextInvokeApply( add, std::tuple<int, int>(1, 2) );
        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "apply() is not available (no C++11)" );
#endif
    }

    //("apply: a lambda, std::array of 2 arguments (C++11) - constexpr")
    {
#if QEXT_INVOKE_CPP17_OR_GREATER
        constexpr auto constexpr_result = qextInvokeApply( [](int a, int b){ return a + b; }, std::array<int,2>({ 1, 2}));
        QVERIFY( constexpr_result == 3 );
#else
        QSKIP( "apply(): constexpr closure is not available (no C++17)" );
#endif
    }
#endif
}

void QExtInvokeTest::other()
{

    //("invoke: App" "[.invoke][.app]")
    {
        std::cout << "App: ...\n";
    }

    //( "tweak header: Reads tweak header if supported " "[tweak]" )
    {
#if QEXT_INVOKE_HAVE_TWEAK_HEADER
        QVERIFY( QEXT_INVOKE_TWEAK_VALUE == 42 );
#else
        QSKIP( "Tweak header is not available (QEXT_INVOKE_HAVE_TWEAK_HEADER: 0)." );
#endif
    }
}

QTEST_APPLESS_MAIN(QExtInvokeTest)

#include <tst_qextInvoke.moc>
