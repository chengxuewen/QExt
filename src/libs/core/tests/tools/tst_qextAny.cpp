#include <qextAny.h>
#include <qextGlobal.h>

#include <QtTest>
#include <QDebug>
#include <QtEndian>
#include <QByteArray>

#include <sstream>


// Suppress:
// - unused parameter, for cases without assertions such as [.std...]
#if defined(__clang__)
# pragma clang diagnostic ignored "-Wunneeded-member-function"
#elif defined __GNUC__
//# pragma GCC   diagnostic ignored ""
#endif

// Note: use qextAnyCast( ptr-to-QExtAny ) to preserve move-state.

namespace {

// ensure comparison of pointers for lest:

//const void * lest_nullptr = 0;

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

struct V
{
    State state;
    int   value;

    V(             ) : state( default_constructed ), value( deflt() ) {}
    V( int       v ) : state( value_constructed   ), value( v       ) {}
    V( V const & v ) : state( copy_constructed    ), value( v.value ) {}

    V & operator=( int       v ) { state = value_copy_assigned; value = v; return *this; }
    V & operator=( V const & v ) { state = copy_assigned      ; value = v.value; return *this; }

#if QEXT_ANY_CPP11_OR_GREATER
    V(             V && v ) : state( move_constructed   ), value(  std::move( v.value ) ) { v.state = moved_from; }
    V & operator=( V && v ) { state = move_assigned      ; value = std::move( v.value ); v.state = moved_from; return *this; }
#endif

    static int deflt() { return 42; }

    bool operator==( V const & other ) const { return state == other.state && value == other.value; }
};

struct S
{
    State state;
    V     value;

    S(             ) : state( default_constructed    ) {}
    S( V const & v ) : state( value_copy_constructed ), value( v ) {}
    S( S const & s ) : state( copy_constructed       ), value( s.value        ) {}

    S & operator=( V const & v ) { state = value_copy_assigned; value = v; return *this; }
    S & operator=( const S & s ) { state = copy_assigned      ; value = s.value; return *this; }

#if QEXT_ANY_CPP11_OR_GREATER
    S(             V && v ) : state(  value_move_constructed ), value(  std::move( v )     ) { v.state = moved_from; }
    S(             S && s ) : state(  move_constructed       ), value(  std::move( s.value ) ) { s.state = moved_from; }

    S & operator=( V && v ) { state = value_move_assigned     ; value = std::move( v       ); v.state = moved_from; return *this; }
    S & operator=( S && s ) { state = move_assigned           ; value = std::move( s.value ); s.state = moved_from; return *this; }
#endif

    bool operator==( S const & rhs ) const { return state == rhs.state && value == rhs.value; }
};

inline std::ostream & operator<<( std::ostream & os, V const & v )
{
    return os << "[V:" << std::to_string( v.value ) << "]";
}

inline std::ostream & operator<<( std::ostream & os, S const & s )
{
    return os << "[S:" << std::to_string( s.value.state ) << ", " << std::to_string( s.value.value ) << "]";
}

#if QEXT_ANY_CPP11_OR_GREATER
struct InitList
{
    std::vector<int> vec;
    char c;
    S s;

    InitList( std::initializer_list<int> il, char k, S const & t)
        : vec( il ), c( k ), s( t ) {}

    InitList( std::initializer_list<int> il, char k, S && t)
        : vec( il ), c( k ), s( std::move(t) ) {}
};
#endif

} // anonymous namespace

class QExtAnyTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void construct();
};



void QExtAnyTest::construct()
{

    // "QExtAny: Allows to default construct QExtAny" )
    {
        QExtAny a;

        QVERIFY(! a.has_value() );
    }

    // "QExtAny: Allows to copy-construct from QExtAny" )
    {
        QExtAny a( 7 );

        QExtAny b( a );

        QVERIFY( a.has_value() );
        QVERIFY( b.has_value() );
        QVERIFY( qextAnyCast<int>( b ) == 7 );
    }

    // "QExtAny: Allows to move-construct from QExtAny (C++11)" )
    {
#if QEXT_ANY_CPP11_OR_GREATER
        QExtAny b( QExtAny( 7 ) );

        QVERIFY( qextAnyCast<int>( b ) == 7 );
#else
        QVERIFY( !!"QExtAny: move-construction is not available (no C++11)" );
#endif
    }

    // "QExtAny: Allows to copy-construct from literal value" )
    {
        QExtAny a( 7 );

        QVERIFY( qextAnyCast<int>( a ) == 7 );
    }

    // "QExtAny: Allows to copy-construct from const value" )
    {
        const int i = 7;
        QExtAny a( i );

        QVERIFY( qextAnyCast<int>( a ) == i );
    }

    // "QExtAny: Allows to copy-construct from lvalue references" )
    {
        std::string i = "Test";
        QExtAny a( i );

        QVERIFY( qextAnyCast<std::string>( a ) == i );
    }

    // "QExtAny: Allows to move-construct from value (C++11)" )
    {
#if QEXT_ANY_CPP11_OR_GREATER
        S s( 7 );
        QExtAny a( std::move( s ) );

        QVERIFY( qextAnyCast<S>( &a )->value.value == 7          );
        QVERIFY( qextAnyCast<S>( &a )->state == move_constructed );
        QVERIFY(                  s.state == moved_from       );
#else
        QVERIFY( !!"QExtAny: move-construction is not available (no C++11)" );
#endif
    }

    // "QExtAny: Allows to in-place construct from literal value (C++11)" )
    {
#if QEXT_ANY_CPP11_OR_GREATER
        using pair_t = std::pair<char, int>;

#if QEXT_USES_STD_ANY
        QExtAny a( qextMakeAnyInPlaceType<pair_t>, 'a', 7 );
#else
        QExtAny a( qextMakeAnyInPlaceType<pair_t>, 'a', 7 );
//  QExtAny a( in_place<     pair_t>, 'a', 7 );
#endif
        QVERIFY( qextAnyCast<pair_t>( a ).first  == 'a' );
        QVERIFY( qextAnyCast<pair_t>( a ).second ==  7  );
#else
        QVERIFY( !!"QExtAny: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtAny: Allows to in-place copy-construct from value (C++11)" )
    {
#if QEXT_ANY_CPP11_OR_GREATER
        char c = 'a'; V v( 7 );
        using pair_t = std::pair<char, V>;

#if QEXT_USES_STD_ANY
        QExtAny a( qextMakeAnyInPlaceType<pair_t>, c, v );
#else
        QExtAny a( qextMakeAnyInPlaceType<pair_t>, c, v );
//  QExtAny a( in_place<     pair_t>, c, v );
#endif

        QVERIFY( qextAnyCast<pair_t>( &a )->first        == 'a' );
        QVERIFY( qextAnyCast<pair_t>( &a )->second.value ==  7  );
#if QEXT_USES_STD_ANY
        QVERIFY( qextAnyCast<pair_t>( &a )->second.state == copy_constructed );
#else
        QVERIFY( qextAnyCast<pair_t>( &a )->second.state == move_constructed );
#endif
        QVERIFY(                              v.state != moved_from       );
#else
        QVERIFY( !!"QExtAny: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtAny: Allows to in-place move-construct from value (C++11)" )
    {
#if QEXT_ANY_CPP11_OR_GREATER
        char c = 'a'; V v( 7 );
        using pair_t = std::pair<char, V>;

#if QEXT_USES_STD_ANY
        QExtAny a( qextMakeAnyInPlaceType<pair_t>, c, std::move(v) );
#else
        QExtAny a( qextMakeAnyInPlaceType<pair_t>, c, std::move(v) );
//  QExtAny a( in_place<     pair_t>, c, std::move(v) );
#endif
        QVERIFY( qextAnyCast<pair_t>( &a )->first        == 'a' );
        QVERIFY( qextAnyCast<pair_t>( &a )->second.value ==  7  );
        QVERIFY( qextAnyCast<pair_t>( &a )->second.state == move_constructed );
        QVERIFY(                              v.state == moved_from       );
#else
        QVERIFY( !!"QExtAny: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtAny: Allows to in-place copy-construct from initializer-list (C++11)" )
    {
#if QEXT_ANY_CPP11_OR_GREATER
        S s( 7 );
#if QEXT_USES_STD_ANY
        QExtAny a( qextMakeAnyInPlaceType<InitList>, { 7, 8, 9, }, 'a', s );
#else
        QExtAny a( qextMakeAnyInPlaceType<InitList>, { 7, 8, 9, }, 'a', s );
//  QExtAny a( in_place<     InitList>, { 7, 8, 9, }, 'a', s );
#endif

        QVERIFY( qextAnyCast<InitList>( &a )->vec[0]  ==  7  );
        QVERIFY( qextAnyCast<InitList>( &a )->vec[1]  ==  8  );
        QVERIFY( qextAnyCast<InitList>( &a )->vec[2]  ==  9  );
        QVERIFY( qextAnyCast<InitList>( &a )->c       == 'a' );
        QVERIFY( qextAnyCast<InitList>( &a )->s.value.value ==  7               );
#if QEXT_USES_STD_ANY
        QVERIFY( qextAnyCast<InitList>( &a )->s.state       == copy_constructed );
#else
        QVERIFY( qextAnyCast<InitList>( &a )->s.state       == move_constructed );
#endif
        QVERIFY(                           s.state       != moved_from       );
#else
        QVERIFY( !!"QExtAny: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtAny: Allows to in-place move-construct from initializer-list (C++11)" )
    {
#if QEXT_ANY_CPP11_OR_GREATER
        S s( 7 );
#if QEXT_USES_STD_ANY
        QExtAny a( qextMakeAnyInPlaceType<InitList>, { 7, 8, 9, }, 'a', std::move(s) );
#else
        QExtAny a( qextMakeAnyInPlaceType<InitList>, { 7, 8, 9, }, 'a', std::move(s) );
//  QExtAny a( in_place<     InitList>, { 7, 8, 9, }, 'a', std::move(s) );
#endif

        QVERIFY( qextAnyCast<InitList>( &a )->vec[0]  ==  7  );
        QVERIFY( qextAnyCast<InitList>( &a )->vec[1]  ==  8  );
        QVERIFY( qextAnyCast<InitList>( &a )->vec[2]  ==  9  );
        QVERIFY( qextAnyCast<InitList>( &a )->c       == 'a' );
        QVERIFY( qextAnyCast<InitList>( &a )->s.value.value == 7                );
        QVERIFY( qextAnyCast<InitList>( &a )->s.state       == move_constructed );
        QVERIFY(                           s.state       == moved_from       );
        QVERIFY(                           s.value.state == moved_from       );
#else
        QVERIFY( !!"QExtAny: in-place construction is not available (no C++11)" );
#endif
    }

}

QTEST_APPLESS_MAIN(QExtAnyTest)

#include <tst_qextAny.moc>
