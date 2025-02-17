#include <qextOptional.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

#include <iostream>

#if QEXT_OPTIONAL_USES_STD_OPTIONAL && defined(__APPLE__)
# define opt_value( o ) *o
#else
# define opt_value( o )  o.value()
#endif

namespace {

struct nonpod { nonpod(){} };

struct Implicit { int x;          Implicit(int v) : x(v) {} };
struct Explicit { int x; explicit Explicit(int v) : x(v) {} };

bool operator==( Implicit a, Implicit b ) { return a.x == b.x; }
bool operator==( Explicit a, Explicit b ) { return a.x == b.x; }

std::ostream & operator<<( std::ostream & os, Implicit i ) { return os << "Implicit:" << i.x; }
std::ostream & operator<<( std::ostream & os, Explicit e ) { return os << "Explicit:" << e.x; }

// ensure comparison of pointers for lest:

// const void * lest_nullptr = 0;

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

    V(       ) : state( default_constructed ), value( deflt() ) {}
    V( int v ) : state( value_constructed   ), value( v       ) {}

    bool operator==( V const & rhs ) const { return state == rhs.state && value == rhs.value; }
    bool operator==( int       val ) const { return value == val; }

    static int deflt() { return 42; }
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

#if QEXT_OPTIONAL_CPP11_OR_GREATER
    S(             V && v ) : state(  value_move_constructed ), value(  std::move( v       ) ) { v.state = moved_from; }
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
    return os << "[S:" << std::to_string( s.value.value ) << "]";
}

struct NoDefault
{
    NoDefault( NoDefault const & ) {}
    NoDefault & operator=( NoDefault const & ) { return *this; }

#if QEXT_OPTIONAL_CPP11_OR_GREATER
    NoDefault( NoDefault && ) = default;
    NoDefault & operator=( NoDefault && ) = default;
#endif

private:
    NoDefault();
};

struct CopyOnly
{
    CopyOnly( CopyOnly const & ) {}
    CopyOnly & operator=( CopyOnly const & ) { return *this; }

private:
    CopyOnly();
#if QEXT_OPTIONAL_CPP11_OR_GREATER
    CopyOnly( CopyOnly && ) = delete;
    CopyOnly & operator=( CopyOnly && ) = delete;
#endif
};

struct MoveOnly
{
#if QEXT_OPTIONAL_CPP11_OR_GREATER
    MoveOnly( MoveOnly && ) = default;
    MoveOnly & operator=( MoveOnly && ) = default;
#endif

private:
    MoveOnly();
    MoveOnly( MoveOnly const & );
    MoveOnly & operator=( MoveOnly const & );
};

struct NoDefaultCopyMove
{
    std::string text;
    NoDefaultCopyMove( std::string txt ) : text( txt ) {}

private:
    NoDefaultCopyMove();
    NoDefaultCopyMove( NoDefaultCopyMove const & );
    NoDefaultCopyMove & operator=( NoDefaultCopyMove const & );
#if QEXT_OPTIONAL_CPP11_OR_GREATER
    NoDefaultCopyMove( NoDefaultCopyMove && ) = delete;
    NoDefaultCopyMove & operator=( NoDefaultCopyMove && ) = delete;
#endif
};

#if QEXT_OPTIONAL_CPP11_OR_GREATER
struct InitList
{
    std::vector<int> vec;
    char c;
    S s;

    InitList( std::initializer_list<int> il, char k, S const & t )
        : vec( il ), c( k ), s( t ) {}

    InitList( std::initializer_list<int> il, char k, S && t )
        : vec( il ), c( k ), s( std::move( t ) ) {}
};
#endif

} // anonymous namespace

class QExtOptionalTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void specification();
    void construction();
    void assignment();
    void swap();
    void observers();
    void modifiers();
    void destruction();
    void nonmemberfunctions();
    void negative();
    void Issues();
};


void QExtOptionalTest::specification()
{

    //
    // test specification:
    //

    //( "union: A C++03 union can only contain POD types" )
    {
        union U
        {
            char c;
#if QEXT_OPTIONAL_CPP11_OR_GREATER
            nonpod np;
#endif
        };
    }

}

namespace {

#if QEXT_OPTIONAL_CPP11_OR_GREATER
void use_optional( QExtOptional<Implicit> ) {}
#else
template< typename T >
void use_optional( T ) {}
#endif

}

void QExtOptionalTest::construction()
{

    // construction:

    //( "QExtOptional: Allows to default construct an empty QExtOptional (1a)" )
    {
        QExtOptional<int> a;

        QVERIFY( !a );
    }

    //( "QExtOptional: Allows to explicitly construct a disengaged, empty QExtOptional via QExtOptionalNullopt (1b)" )
    {
        QExtOptional<int> a( QExtOptionalNullopt );

        QVERIFY( !a );
    }

    //( "QExtOptional: Allows to default construct an empty QExtOptional with a non-default-constructible (1a)" )
    {
        //  FAILS: NoDefault nd;
        //  FAILS: NoDefaultCopyMove ndcm;
        QExtOptional<NoDefault> ond;
        QExtOptional<CopyOnly> oco;
        QExtOptional<MoveOnly> omo;
        QExtOptional<NoDefaultCopyMove> ondcm;

        QVERIFY( !ond );
        QVERIFY( !oco );
        QVERIFY( !omo );
        QVERIFY( !ondcm );
    }

    //( "QExtOptional: Allows to copy-construct from empty QExtOptional (2)" )
    {
        QExtOptional<int> a;

        QExtOptional<int> b( a );

        QVERIFY( !b );
    }

    //( "QExtOptional: Allows to move-construct from empty QExtOptional (C++11, 3)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<int> a;

        QExtOptional<int> b( std::move( a ) );

        QVERIFY( !b );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-construct from empty QExtOptional, explicit converting (C++11, 4a)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<int> a;

        QExtOptional<Explicit> b{ a };

        QVERIFY( !b );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-construct from empty QExtOptional, non-explicit converting (4b)" )
    {
        QExtOptional<int> a;

        QExtOptional<Implicit> b( a );

        QVERIFY( !b );
    }

    //( "QExtOptional: Allows to move-construct from empty QExtOptional, explicit converting (C++11, 5a)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<int> a;

        QExtOptional<Explicit> b{ std::move( a ) };

        QVERIFY( !b );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to move-construct from empty QExtOptional, non-explicit converting (C++11, 5a)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<int> a;

        QExtOptional<Implicit> b( std::move( a ) );

        QVERIFY( !b );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-construct from non-empty QExtOptional (2)" )
    {
        QExtOptional<int> a( 7 );

        QExtOptional<int> b( a );

        QVERIFY(  b      );
        QVERIFY( *b == 7 );
    }

    //( "QExtOptional: Allows to copy-construct from non-empty QExtOptional, explicit converting (C++11, 4a)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<int> a( 7 );

        QExtOptional<Explicit> b{ a };

        QVERIFY(  b                );
        QVERIFY( *b == Explicit{7} );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-construct from non-empty QExtOptional, non-explicit converting (4b)" )
    {
        QExtOptional<int> a( 7 );

        QExtOptional<Implicit> b( a );

        QVERIFY(  b                );
        QVERIFY( *b == Implicit(7) );
    }

    //( "QExtOptional: Allows to move-construct from non-empty QExtOptional (C++11, 3)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<int> a( 7 );

        QExtOptional<int> b( std::move( a ) );

        QVERIFY(  b      );
        QVERIFY( *b == 7 );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to move-construct from non-empty QExtOptional, explicit converting (C++11, 5a)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<int> a( 7 );

        QExtOptional<Explicit> b{ std::move( a ) };

        QVERIFY(  b                );
        QVERIFY( *b == Explicit{7} );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to move-construct from non-empty QExtOptional, non-explicit converting (C++11, 5b)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<int> a( 7 );

        QExtOptional<Implicit> b( std::move( a ) );

        QVERIFY(  b                );
        QVERIFY( *b == Implicit(7) );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-construct from literal value (8)" )
    {
        use_optional( 7 );
        QExtOptional<int> a = 7;

        QVERIFY(  a      );
        QVERIFY( *a == 7 );
    }

    //( "QExtOptional: Allows to copy-construct from literal value, converting (8)" )
    {
        use_optional( '7' );
        QExtOptional<int> a = '7';

        QVERIFY(  a        );
        QVERIFY( *a == '7' );
    }

    //( "QExtOptional: Allows to copy-construct from value (8)" )
    {
        const int i = 7;

        use_optional( i );
        QExtOptional<int> a( i );

        QVERIFY(  a      );
        QVERIFY( *a == 7 );
    }

    //( "QExtOptional: Allows to copy-construct from value, converting (8)" )
    {
        const char c = '7';

        use_optional( c );
        QExtOptional<int> a( c );

        QVERIFY(  a        );
        QVERIFY( *a == '7' );
    }

    //( "QExtOptional: Allows to move-construct from value (C++11, 8b)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );

        QExtOptional<S> a( std::move( s ) );

        QVERIFY( a->value == 7                );
        QVERIFY( a->state == move_constructed );
        QVERIFY(  s.state == moved_from       );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to move-construct from value, explicit converting (C++11, 8a)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        int seven = 7;

        QExtOptional<Explicit> a{ std::move( seven ) };

        QVERIFY(  a                );
        QVERIFY( *a == Explicit{7} );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to move-construct from value, non-explicit converting (C++11, 8b)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        int seven = 7;
        QExtOptional<Implicit> a( std::move( seven ) );

        QVERIFY(  a                );
        QVERIFY( *a == Implicit(7) );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place construct an immovable object (C++11, 6" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        QExtOptional<NoDefaultCopyMove> ondcm( qextOptionalInPlace, std::string("test") );

        QVERIFY( ondcm.has_value() );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place construct from literal value (C++11, 6)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using pair_t = std::pair<char, int>;

        QExtOptional<pair_t> a( qextOptionalInPlace, 'a', 7 );

        QVERIFY( a->first  == 'a' );
        QVERIFY( a->second ==  7  );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place construct from literal value (C++11, 6, const)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using pair_t = std::pair<char, int>;

        QExtOptional<const pair_t> a( qextOptionalInPlace, 'a', 7 );

        QVERIFY( a->first  == 'a' );
        QVERIFY( a->second ==  7  );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place copy-construct from value (C++11, 6)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        char c = 'a'; S s( 7 );
        using pair_t = std::pair<char, S>;

        QExtOptional<pair_t> a( qextOptionalInPlace, c, s );

        QVERIFY( a->first        == 'a' );
        QVERIFY( a->second.value ==  7  );
        QVERIFY( a->second.state == copy_constructed );
        QVERIFY(         s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place copy-construct from value (C++11, 6, const)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        char c = 'a'; S s( 7 );
        using pair_t = std::pair<char, S>;

        QExtOptional<const pair_t> a( qextOptionalInPlace, c, s );

        QVERIFY( a->first        == 'a' );
        QVERIFY( a->second.value ==  7  );
        QVERIFY( a->second.state == copy_constructed );
        QVERIFY(         s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place move-construct from value (C++11, 6)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        char c = 'a'; S s( 7 );
        using pair_t = std::pair<char, S>;

        QExtOptional<pair_t> a( qextOptionalInPlace, c, std::move( s ) );

        QVERIFY( a->first        == 'a' );
        QVERIFY( a->second.value ==  7  );
        QVERIFY( a->second.state == move_constructed );
        QVERIFY(         s.state == moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place copy-construct from initializer-list (C++11, 7)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        QExtOptional<InitList> a( qextOptionalInPlace, { 7, 8, 9, }, 'a', s );

        QVERIFY( a->vec[0]  ==  7 );
        QVERIFY( a->vec[1]  ==  8 );
        QVERIFY( a->vec[2]  ==  9 );
        QVERIFY( a->c       == 'a');
        QVERIFY( a->s.value ==  7 );
#if QEXT_OPTIONAL_USES_STD_OPTIONAL
        QVERIFY( a->s.state == copy_constructed );
#else
        QVERIFY( a->s.state == move_constructed );
#endif
        QVERIFY(    s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place copy-construct from initializer-list (C++11, 7, const)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        QExtOptional<const InitList> a( qextOptionalInPlace, { 7, 8, 9, }, 'a', s );

        QVERIFY( a->vec[0]  ==  7 );
        QVERIFY( a->vec[1]  ==  8 );
        QVERIFY( a->vec[2]  ==  9 );
        QVERIFY( a->c       == 'a');
        QVERIFY( a->s.value ==  7 );
        QVERIFY( a->s.state == copy_constructed );
        QVERIFY(    s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to in-place move-construct from initializer-list (C++11, 7)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        QExtOptional<InitList> a( qextOptionalInPlace, { 7, 8, 9, }, 'a', std::move( s ) );

        QVERIFY( a->vec[0]  ==  7  );
        QVERIFY( a->vec[1]  ==  8  );
        QVERIFY( a->vec[2]  ==  9  );
        QVERIFY( a->c       == 'a' );
        QVERIFY( a->s.value ==  7  );
        QVERIFY( a->s.state == move_constructed );
        QVERIFY(    s.state == moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }
}

void QExtOptionalTest::assignment()
{

    // assignment:

    //( "QExtOptional: Allows to assign QExtOptionalNullopt to disengage (1)" )
    {
        QExtOptional<int>  a( 7 );

        a = QExtOptionalNullopt;

        QVERIFY( !a );
    }

    //( "QExtOptional: Allows to copy-assign from/to engaged and disengaged optionals (2)" )
    {
        {
            QExtOptional<int> d1;
            QExtOptional<int> d2;
            QExtOptional<int> e1( 123 );
            QExtOptional<int> e2( 987 );

            //( "a disengaged QExtOptional assigned QExtOptionalNullopt remains empty" )
            {
                d1 = QExtOptionalNullopt;
                QVERIFY( !d1 );
            }
            //( "a disengaged QExtOptional assigned an engaged QExtOptional obtains its value" )
            {
                d1 = e1;
                QVERIFY(  d1 );
                QVERIFY( *d1 == 123 );
            }
            //( "an engaged QExtOptional assigned an engaged QExtOptional obtains its value" )
            {
                e1 = e2;
                QVERIFY(  e1 );
                QVERIFY( *e1 == 987 );
            }
            //( "an engaged QExtOptional assigned QExtOptionalNullopt becomes empty" )
            {
                e1 = QExtOptionalNullopt;
                QVERIFY( !e1 );
            }
            //( "a disengaged QExtOptional assigned a disengaged QExtOptional remains empty" )
            {
                d1 = d2;
                QVERIFY( !d1 );
            }
        }
    }

    //( "QExtOptional: Allows to move-assign from/to engaged and disengaged optionals (C++11, 3)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        {
            QExtOptional<int> d1;
            QExtOptional<int> d2;
            QExtOptional<int> e1( 123 );
            QExtOptional<int> e2( 987 );

            //( "a disengaged QExtOptional assigned QExtOptionalNullopt remains empty" )
            {
                d1 = std::move( QExtOptionalNullopt );
                QVERIFY( !d1 );
            }
            //( "a disengaged QExtOptional assigned an engaged QExtOptional obtains its value" )
            {
                d1 = std::move( e1);
                QVERIFY(  d1 );
                QVERIFY( *d1 == 123 );
            }
            //( "an engaged QExtOptional assigned an engaged QExtOptional obtains its value" )
            {
                e1 = std::move( e2 );
                QVERIFY(  e1 );
                QVERIFY( *e1 == 987 );
            }
            //( "an engaged QExtOptional assigned QExtOptionalNullopt becomes empty" )
            {
                e1 = std::move( QExtOptionalNullopt );
                QVERIFY( !e1 );
            }
            //( "a disengaged QExtOptional assigned a disengaged QExtOptional remains empty" )
            {
                d1 = std::move( d2);
                QVERIFY( !d1 );
            }}
#else
        QSKIP( "QExtOptional: move-assignment is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-assign from/to engaged and disengaged optionals, converting, (5)" )
    {
        {
            QExtOptional<int>  d1;
            QExtOptional<char> d2;
            QExtOptional<int>  e1( 123 );
            QExtOptional<char> e2( '7' );

            //( "a disengaged QExtOptional assigned an engaged QExtOptional obtains its value, converting" )
            {
                d1 = e2;
                QVERIFY(  d1 );
                QVERIFY( *d1 == '7' );
            }
            //( "an engaged QExtOptional assigned an engaged QExtOptional obtains its value, converting" )
            {
                e1 = e2;
                QVERIFY(  e1 );
                QVERIFY( *e1 == '7' );
            }
            //( "an engaged QExtOptional assigned a disengaged QExtOptional becomes empty, converting" )
            {
                e1 = d2;
                QVERIFY(  !e1 );
            }
            //( "a disengaged QExtOptional assigned a disengaged QExtOptional remains empty, converting" )
            {
                d1 = d2;
                QVERIFY( !d1 );
            }}
    }

    //( "QExtOptional: Allows to move-assign from/to engaged and disengaged optionals, converting (C++11, 6)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        {
            QExtOptional<int>  d1;
            QExtOptional<char> d2;
            QExtOptional<int>  e1( 123 );
            QExtOptional<char> e2( '7' );

            //( "a disengaged QExtOptional assigned an engaged QExtOptional obtains its value, converting" )
            {
                d1 = std::move( e2 );
                QVERIFY(  d1 );
                QVERIFY( *d1 == '7' );
            }
            //( "an engaged QExtOptional assigned an engaged QExtOptional obtains its value, converting" )
            {
                e1 = std::move( e2 );
                QVERIFY(  e1 );
                QVERIFY( *e1 == '7' );
            }
            //( "an engaged QExtOptional assigned a disengaged QExtOptional becomes empty, converting" )
            {
                e1 = std::move( d2 );
                QVERIFY(  !e1 );
            }
            //( "a disengaged QExtOptional assigned a disengaged QExtOptional remains empty, converting" )
            {
                d1 = std::move( d2 );
                QVERIFY( !d1 );
            }}
#else
        QSKIP( "QExtOptional: move-assignment is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-assign from literal value (4)" )
    {
        QExtOptional<int> a;

        a = 7;

        QVERIFY( *a == 7 );
    }

    //( "QExtOptional: Allows to copy-assign from value (4)" )
    {
        const int i = 7;
        QExtOptional<int> a;

        a = i;

        QVERIFY( *a == i );
    }

    //( "QExtOptional: Allows to move-assign from value (C++11, 4)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        QExtOptional<S> a;

        a = std::move( s );

        QVERIFY( a->value == 7 );
        QVERIFY( a->state == move_constructed );
        QVERIFY(  s.state == moved_from       );
#else
        QSKIP( "QExtOptional: move-assign is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-emplace content from arguments (C++11, 7)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using pair_t = std::pair<char, S>;
        S s( 7 );
        QExtOptional<pair_t> a;

        a.emplace( 'a', s );

        QVERIFY( a->first        == 'a' );
        QVERIFY( a->second.value ==  7  );
        QVERIFY( a->second.state == copy_constructed );
        QVERIFY(         s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-emplace content from arguments (C++11, 7, const)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using pair_t = std::pair<char, S>;
        S s( 7 );
        QExtOptional<const pair_t> a;

        a.emplace( 'a', s );

        QVERIFY( a->first        == 'a' );
        QVERIFY( a->second.value ==  7  );
        QVERIFY( a->second.state == copy_constructed );
        QVERIFY(         s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to move-emplace content from arguments (C++11, 7)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using pair_t = std::pair<char, S>;
        S s( 7 );
        QExtOptional<pair_t> a;

        a.emplace( 'a', std::move( s ) );

        QVERIFY( a->first        == 'a' );
        QVERIFY( a->second.value ==  7  );
        QVERIFY( a->second.state == move_constructed );
        QVERIFY(         s.state == moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-emplace content from intializer-list and arguments (C++11, 8)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        QExtOptional<InitList> a;

        a.emplace( { 7, 8, 9, }, 'a', s );

        QVERIFY( a->vec[0]  ==  7  );
        QVERIFY( a->vec[1]  ==  8  );
        QVERIFY( a->vec[2]  ==  9  );
        QVERIFY( a->c       == 'a' );
        QVERIFY( a->s.value ==  7  );
        QVERIFY( a->s.state == copy_constructed );
        QVERIFY(    s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to copy-emplace content from intializer-list and arguments (C++11, 8, const)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        QExtOptional<const InitList> a;

        a.emplace( { 7, 8, 9, }, 'a', s );

        QVERIFY( a->vec[0]  ==  7  );
        QVERIFY( a->vec[1]  ==  8  );
        QVERIFY( a->vec[2]  ==  9  );
        QVERIFY( a->c       == 'a' );
        QVERIFY( a->s.value ==  7  );
        QVERIFY( a->s.state == copy_constructed );
        QVERIFY(    s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to move-emplace content from intializer-list and arguments (C++11, 8)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        QExtOptional<InitList> a;

        a.emplace( { 7, 8, 9, }, 'a', std::move( s ) );

        QVERIFY( a->vec[0]  ==  7  );
        QVERIFY( a->vec[1]  ==  8  );
        QVERIFY( a->vec[2]  ==  9  );
        QVERIFY( a->c       == 'a' );
        QVERIFY( a->s.value ==  7               );
        QVERIFY( a->s.state == move_constructed );
        QVERIFY(    s.state == moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }
}

void QExtOptionalTest::swap()
{

    // swap:

    //( "QExtOptional: Allows to swap with other QExtOptional (member)" )
    {
        {

            //( "swap disengaged with disengaged QExtOptional" )
            {
                QExtOptional<int> d1;
                QExtOptional<int> d2;
                QExtOptional<int> e1( 42 );
                QExtOptional<int> e2( 7 );
                d1.swap( d2 );
                QVERIFY( !d1 );
            }
            //( "swap engaged with engaged QExtOptional" )
            {
                QExtOptional<int> d1;
                QExtOptional<int> d2;
                QExtOptional<int> e1( 42 );
                QExtOptional<int> e2( 7 );
                e1.swap( e2 );
                QVERIFY(  e1  );
                QVERIFY(  e2 );
                QVERIFY( *e1 == 7 );
                QVERIFY( *e2 == 42 );
            }
            //( "swap disengaged with engaged QExtOptional" )
            {
                QExtOptional<int> d1;
                QExtOptional<int> d2;
                QExtOptional<int> e1( 42 );
                QExtOptional<int> e2( 7 );
                d1.swap( e1 );
                QVERIFY(  d1 );
                QVERIFY( !e1 );
                QVERIFY( *d1 == 42 );
            }
            //( "swap engaged with disengaged QExtOptional" )
            {
                QExtOptional<int> d1;
                QExtOptional<int> d2;
                QExtOptional<int> e1( 42 );
                QExtOptional<int> e2( 7 );
                e1.swap( d1 );
                QVERIFY(  d1 );
                QVERIFY( !e1 );
                QVERIFY( *d1 == 42 );
            }
        }
    }
}

void QExtOptionalTest::observers()
{

    // observers:

    //( "QExtOptional: Allows to obtain value via operator->()" )
    {
        {
            QExtOptional<Implicit>        e( Implicit( 42 ) );
            QExtOptional<Implicit> const ce( Implicit( 42 ) );

            //( "operator->() yields pointer to value (const)" )
            {
                QVERIFY(  ce->x == 42 );
            }
            //( "operator->() yields pointer to value (non-const)" )
            {
                e->x = 7;
                QVERIFY(  e->x == 7 );
            }}
    }

    //( "QExtOptional: Allows to obtain moved-value via operator->() (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        {
            QExtOptional<Implicit>        e( Implicit( 42 ) );
            QExtOptional<Implicit> const ce( Implicit( 42 ) );

            //( "operator->() yields pointer to value (const)" )
            {
                QVERIFY(  std::move( ce )->x == 42 );
            }
            //( "operator->() yields pointer to value (non-const)" )
            {
                e->x = 7;
                QVERIFY(  std::move( e )->x == 7 );
            }}
#else
        QSKIP( "QExtOptional: move-semantics are not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to obtain value via operator*()" )
    {
        {
            QExtOptional<int>        e( 42 );
            QExtOptional<int> const ce( 42 );

            //( "operator*() yields value (const)" )
            {
                QVERIFY( *ce == 42 );
            }
            //( "operator*() yields value (non-const)" )
            {
                *e = 7;
                QVERIFY( *e == 7 );
            }}
    }

    //( "QExtOptional: Allows to obtain moved-value via operator*() (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        {
            QExtOptional<int>        e( 42 );
            QExtOptional<int> const ce( 42 );

            //( "operator*() yields value (const)" )
            {
                QVERIFY( *(std::move( ce )) == 42 );
            }
            //( "operator*() yields value (non-const)" )
            {
                *e = 7;
                QVERIFY( *(std::move( e )) == 7 );
            }
        }
#else
        QSKIP( "QExtOptional: move-semantics are not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to obtain has_value() via operator bool()" )
    {
        QExtOptional<int> a;
        QExtOptional<int> b( 7 );

        QVERIFY(! a );
        QVERIFY(     b );
    }

    //( "QExtOptional: Allows to obtain value via value()" )
    {
            QExtOptional<int> e( 42 );
            QExtOptional<int> const ce( 42 );

            //( "value() yields value (const)" )
            {
                QVERIFY( opt_value( ce ) == 42 );
            }
            //( "value() yields value (non-const)" )
            {
                QVERIFY( opt_value( e ) == 42 );
            }
    }

    //( "QExtOptional: Allows to obtain moved-value via value() (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        {
            QExtOptional<int> e( 42 );
            QExtOptional<int> const ce( 42 );

            //( "value() yields value (const)" )
            {
                QVERIFY( opt_value( std::move( ce ) ) == 42 );
            }
            //( "value() yields value (non-const)" )
            {
                QVERIFY( opt_value( std::move( e ) ) == 42 );
            }
        }
#else
        QSKIP( "QExtOptional: move-semantics are not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to obtain value or default via value_or()" )
    {
        {
            QExtOptional<int> d;
            QExtOptional<int> e( 42 );

            //( "value_or( 7 ) yields value for non-empty QExtOptional" )
            {
                QVERIFY( e.value_or( 7 ) == 42 );
            }
            //( "value_or( 7 ) yields default for empty QExtOptional" )
            {
                QVERIFY( d.value_or( 7 ) == 7 );
            }
        }
    }

    //( "QExtOptional: Allows to obtain moved-value or moved-default via value_or() (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        {
            QExtOptional<int> d;
            QExtOptional<int> e( 42 );
            QExtOptional<std::string> ds;
            QExtOptional<std::string> es("77");

            //("for l-values")
            {
                QVERIFY(  d.value_or( 7 ) ==   7  );
                QVERIFY(  e.value_or( 7 ) ==  42  );
                QVERIFY( ds.value_or("7") ==  "7" );
                QVERIFY( es.value_or("7") == "77" );
                QVERIFY(! es->empty() );  // see issue-60
            }
            //("for r-values")
            {
                QVERIFY( std::move(  d ).value_or( 7 ) ==   7  );
                QVERIFY( std::move(  e ).value_or( 7 ) ==  42  );
                QVERIFY( std::move( ds ).value_or("7") ==  "7" );
                QVERIFY( std::move( es ).value_or("7") == "77" );
            }}
#else
        QSKIP( "QExtOptional: move-semantics are not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Allows to obtain value or function call result via value_or_eval()" " [extension]" )
    {
#if !QEXT_OPTIONAL_USES_STD_OPTIONAL
#if !QEXT_OPTIONAL_CONFIG_NO_EXTENSIONS
        const int const7 = 7;

        // accommodate VS2013/MSVC12.0/1800 and earlier:
        struct F { static int seven() { return 7; } };
        //  struct F { static int seven() { return const7; } };

        {
            QExtOptional<int> d;
            QExtOptional<int> e( 42 );

            //( "value_or_eval( F::zero ) yields value for non-empty QExtOptional" )
            {
                QVERIFY( e.value_or_eval( F::seven ) == 42 );
            }
            //( "value_or( 7 ) yields function result for empty QExtOptional" )
            {
                QVERIFY( d.value_or_eval( F::seven ) == F::seven() );
            }
#if QEXT_OPTIONAL_CPP11_OR_GREATER
            //( "value_or_eval( F::zero ) yields value for non-empty QExtOptional - lambda (C++11)" )
            {
                QVERIFY( e.value_or_eval( [const7](){ return const7; } ) == 42 );
            }
            //( "value_or( 7 ) yields function result for empty QExtOptional - lambda (C++11)" )
            {
                QVERIFY( d.value_or_eval( [const7](){ return const7; } ) == const7 );
            }
#endif
        }
#else
        QSKIP( "QExtOptional: value_or_eval() is not available (QEXT_OPTIONAL_CONFIG_NO_EXTENSIONS=1)" );
#endif
#else
        QSKIP( "QExtOptional: value_or_eval() is not available (using std::QExtOptional)" );
#endif
    }

    //( "QExtOptional: Allows to obtain moved-value or function call result via value_or_eval() (C++11)"  " [extension]" )
    {
#if !QEXT_OPTIONAL_USES_STD_OPTIONAL
#if !QEXT_OPTIONAL_CONFIG_NO_EXTENSIONS
#if  QEXT_OPTIONAL_CPP11_OR_GREATER
        {
            QExtOptional<int> d;
            QExtOptional<int> e( 42 );
            QExtOptional<std::string> ds;
            QExtOptional<std::string> es("77");

            //("for l-values")
            {
                QVERIFY(  d.value_or_eval( [](){ return  7;  } ) ==   7  );
                QVERIFY(  e.value_or_eval( [](){ return  7;  } ) ==  42  );
                QVERIFY( ds.value_or_eval( [](){ return "7"; } ) ==  "7" );
                QVERIFY( es.value_or_eval( [](){ return "7"; } ) == "77" );
                QVERIFY(! es->empty() );
            }
            //("for r-values")
            {
                QVERIFY( std::move(  d ).value_or_eval( [](){ return  7;  } ) ==   7  );
                QVERIFY( std::move(  e ).value_or_eval( [](){ return  7;  } ) ==  42  );
                QVERIFY( std::move( ds ).value_or_eval( [](){ return "7"; } ) ==  "7" );
                QVERIFY( std::move( es ).value_or_eval( [](){ return "7"; } ) == "77" );
                QVERIFY( es->empty() );
            }
        }
#else
        QSKIP( "QExtOptional: move-semantics are not available (no C++11)" );
#endif
#else
        QSKIP( "QExtOptional: value_or_eval() is not available (QEXT_OPTIONAL_CONFIG_NO_EXTENSIONS=1)" );
#endif
#else
        QSKIP( "QExtOptional: value_or_eval() is not available (using std::QExtOptional)" );
#endif
    }

    //( "QExtOptional: Throws QExtBadOptionalAccess at disengaged access" )
    {
#if QEXT_OPTIONAL_USES_STD_OPTIONAL && defined(__APPLE__)
        QVERIFY( true );
#else
        {
            QExtOptional<int> d;
            QExtOptional<int> const cd;

            //("for l-values")
            {
                QVERIFY_EXCEPTION_THROWN(  d.value(), QExtBadOptionalAccess );
                QVERIFY_EXCEPTION_THROWN( cd.value(), QExtBadOptionalAccess );
            }
# if QEXT_OPTIONAL_CPP11_OR_GREATER
            //("for r-values")
            {
                QVERIFY_EXCEPTION_THROWN( std::move(  d ).value(), QExtBadOptionalAccess );
                QVERIFY_EXCEPTION_THROWN( std::move( cd ).value(), QExtBadOptionalAccess );
            }
# endif
        }
#endif
    }

    //( "QExtOptional: Throws QExtBadOptionalAccess with non-empty what()" )
    {
        try
        {
            QExtOptional<int> d;
            (void) d.value();
        }
        catch( QExtBadOptionalAccess const & e )
        {
            QVERIFY( ! std::string( e.what() ).empty() );
        }
    }

}

void QExtOptionalTest::modifiers()
{

    // modifiers:

    //( "QExtOptional: Allows to reset content" )
    {
        QExtOptional<int> a = 7;

        a.reset();

        QVERIFY(! a.has_value() );
    }
}

namespace destruction {

struct S
{
    static void reset() { ctor_count() = 0; dtor_count() = 0; }
    static int & ctor_count() { static int i = 0; return i; }
    static int & dtor_count() { static int i = 0; return i; }

    S( int /*i*/             ) { ++ctor_count(); }
    S( char /*c*/, int /*i*/ ) { ++ctor_count(); }
    S( S const &             ) { ++ctor_count(); }
#if QEXT_OPTIONAL_CPP11_OR_GREATER
    S( S&& ) {}
#endif
    ~S() { ++dtor_count(); }
};
} // namespace destruct

void QExtOptionalTest::destruction()
{

    // destruction:

    //( "QExtOptional: Ensure object is destructed only once (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using destruction::S;

        {



            //( "- Destruction with direct initialize (C++11)" )
            {
                S::reset();
                {
                    QExtOptional<S> s( 7 );

                    QVERIFY( s.has_value()        );
                    QVERIFY( S::dtor_count() == 0 );
                }
                QVERIFY( S::dtor_count() == 1 );
            }
            //( "- Destruction with emplace (C++11)" )
            {
                S::reset();
                {
                    QExtOptional<S> s;

                    QVERIFY( S::dtor_count() == 0 );

                    s.emplace( 'c', 42 );

                    QVERIFY( S::dtor_count() == 0 );
                }
                QVERIFY( S::dtor_count() == 1 );
            }}
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "QExtOptional: Ensure balanced construction-destruction (C++98)" )
    {
        using destruction::S;

        {

            S::reset();

            //( "- Destruction with direct initialize (C++98)" )
            {
                {
                    QExtOptional<S> s( 7 );

                    QVERIFY( s.has_value() );
                    QVERIFY( S::ctor_count() == S::dtor_count() + 1 );
                }
                QVERIFY( S::ctor_count() == S::dtor_count() );
            }}
    }

}

void QExtOptionalTest::nonmemberfunctions()
{

    //
    // QExtOptional non-member functions:
    //

    //( "QExtOptional: Allows to swaps engage state and values (non-member)" )
    {
        {

            //( "swap disengaged with disengaged QExtOptional" )
            {
                QExtOptional<int> d1;
                QExtOptional<int> d2;
                QExtOptional<int> e1( 42 );
                QExtOptional<int> e2( 7 );
                qextOptionalSwap( d1, d2 );
                QVERIFY( !d1 );
            }
            //( "swap engaged with engaged QExtOptional" )
            {
                QExtOptional<int> d1;
                QExtOptional<int> d2;
                QExtOptional<int> e1( 42 );
                QExtOptional<int> e2( 7 );
                qextOptionalSwap( e1, e2 );
                QVERIFY(  e1  );
                QVERIFY(  e2 );
                QVERIFY( *e1 == 7 );
                QVERIFY( *e2 == 42 );
            }
            //( "swap disengaged with engaged QExtOptional" )
            {
                QExtOptional<int> d1;
                QExtOptional<int> d2;
                QExtOptional<int> e1( 42 );
                QExtOptional<int> e2( 7 );
                qextOptionalSwap( d1, e1 );
                QVERIFY(  d1 );
                QVERIFY( !e1 );
                QVERIFY( *d1 == 42 );
            }
            //( "swap engaged with disengaged QExtOptional" )
            {
                QExtOptional<int> d1;
                QExtOptional<int> d2;
                QExtOptional<int> e1( 42 );
                QExtOptional<int> e2( 7 );
                qextOptionalSwap( e1, d1 );
                QVERIFY(  d1 );
                QVERIFY( !e1 );
                QVERIFY( *d1 == 42 );
            }
        }
    }

    //( "make_optional: Allows to copy-construct QExtOptional" )
    {
        S s( 7 );

        QVERIFY( qextOptionalMakeOptional( s )->value == 7          );
        QVERIFY(                   s.state != moved_from );
    }

    //( "make_optional: Allows to move-construct QExtOptional (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );

        QVERIFY( qextOptionalMakeOptional( std::move( s ) )->value == 7          );
        QVERIFY(                                s.state == moved_from );
#else
        QSKIP( "QExtOptional: move-construction is not available (no C++11)" );
#endif
    }

    //( "make_optional: Allows to in-place copy-construct QExtOptional from arguments (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using pair_t = std::pair<char, S>;

        S s( 7);
        auto a = qextOptionalMakeOptional<pair_t>( 'a', s );

        QVERIFY( a->first        == 'a' );
        QVERIFY( a->second.value ==  7  );
#if QEXT_OPTIONAL_CPP17_OR_GREATER
        QVERIFY( a->second.state == copy_constructed );
#else
        QVERIFY( a->second.state == move_constructed );
#endif
        QVERIFY(         s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "make_optional: Allows to in-place move-construct QExtOptional from arguments (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using pair_t = std::pair<char, S>;

        S s( 7 );
        auto a = qextOptionalMakeOptional<pair_t>( 'a', std::move( s ) );

        QVERIFY( a->first        == 'a' );
        QVERIFY( a->second.value ==  7  );
        QVERIFY( a->second.state == move_constructed );
        QVERIFY(         s.state == moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "make_optional: Allows to in-place copy-construct QExtOptional from initializer-list and arguments (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        auto a = qextOptionalMakeOptional<InitList>( { 7, 8, 9, }, 'a', s );

        QVERIFY( a->vec[0]  ==  7  );
        QVERIFY( a->vec[1]  ==  8  );
        QVERIFY( a->vec[2]  ==  9  );
        QVERIFY( a->c       == 'a' );
        QVERIFY( a->s.value ==  7  );
#if QEXT_OPTIONAL_USES_STD_OPTIONAL
        QVERIFY( a->s.state == copy_constructed );
#else
        QVERIFY( a->s.state == move_constructed );
#endif
        QVERIFY(    s.state != moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "make_optional: Allows to in-place move-construct QExtOptional from initializer-list and arguments (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        S s( 7 );
        auto a = qextOptionalMakeOptional<InitList>( { 7, 8, 9, }, 'a', std::move( s ) );

        QVERIFY( a->vec[0]  ==  7  );
        QVERIFY( a->vec[1]  ==  8  );
        QVERIFY( a->vec[2]  ==  9  );
        QVERIFY( a->c       == 'a' );
        QVERIFY( a->s.value ==  7  );
        QVERIFY( a->s.state == move_constructed );
        QVERIFY(    s.state == moved_from       );
#else
        QSKIP( "QExtOptional: in-place construction is not available (no C++11)" );
#endif
    }

    //( "std::hash<>: Allows to obtain hash (C++11)" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        const auto a = QExtOptional<int>( 7 );
        const auto b = QExtOptional<int>( 7 );

        QVERIFY( std::hash<QExtOptional<int>>{}( a ) == std::hash<QExtOptional<int>>{}( b ) );
#else
        QSKIP( "std::hash<>: std::hash<> is not available (no C++11)" );
#endif
    }

    //( "tweak header: reads tweak header if supported " "[tweak]" )
    {
// #if QEXT_OPTIONAL_HAVE_TWEAK_HEADER
//         QVERIFY( OPTIONAL_TWEAK_VALUE == 42 );
// #else
//         QSKIP( "Tweak header is not available (QEXT_OPTIONAL_HAVE_TWEAK_HEADER: 0)." );
// #endif
    }

}

struct Struct{ Struct(){} };
void QExtOptionalTest::negative()
{

#if !defined(QEXT_OPTIONAL_FEATURE_MAX_ALIGN_HACK) || !QEXT_OPTIONAL_FEATURE_MAX_ALIGN_HACK

#define QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( type ) \
    "alignment_of<" #type ">: " <<  \
        alignment_of<type>::value  << "\n" <<

        //("alignment_of: Show alignment of various types" "[.]" )
    {
#if QEXT_OPTIONAL_CPP11_OR_GREATER
        using std::alignment_of;
#else
        using ::nonstd::QEXT_OPTIONAL_lite::detail::alignment_of;
#endif

        std::cout <<
            QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( char )
            QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( short )
            QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( int )
            QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( long )
            QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( float )
            QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( double )
            QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( long double )
            QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF( Struct )
            "";
    }
#undef QEXT_OPTIONAL_OUTPUT_ALIGNMENT_OF
#endif

#define QEXT_OPTIONAL_OUTPUT_SIZEOF( type ) \
    "sizeof( QExtOptional<" #type "> ): " << \
        sizeof( QExtOptional<   type>   )    << " (" << sizeof(type) << ")\n" <<

        //("storage_t: Show sizeof various optionals" "[.]" )
    {
        std::cout <<
#if !QEXT_OPTIONAL_USES_STD_OPTIONAL
            "sizeof( nonstd::optional_lite::detail::storage_t<char> ): " <<
            sizeof( nonstd::optional_lite::detail::storage_t<char> )    << "\n" <<
#endif
            QEXT_OPTIONAL_OUTPUT_SIZEOF( char )
            QEXT_OPTIONAL_OUTPUT_SIZEOF( short )
            QEXT_OPTIONAL_OUTPUT_SIZEOF( int )
            QEXT_OPTIONAL_OUTPUT_SIZEOF( long )
            QEXT_OPTIONAL_OUTPUT_SIZEOF( float )
            QEXT_OPTIONAL_OUTPUT_SIZEOF( double )
            QEXT_OPTIONAL_OUTPUT_SIZEOF( long double )
            QEXT_OPTIONAL_OUTPUT_SIZEOF( Struct )
            "";
    }
#undef QEXT_OPTIONAL_OUTPUT_SIZEOF
}

#if QEXT_OPTIONAL_CPP11_110
namespace issue_61 {

// A: copy & move constructable/assignable
struct A
{
#if QEXT_OPTIONAL_CPP11_140
    A() = default;
    A(const A &) = default;
    A& operator=(const A &) = default;
    A(A &&) = default;
    A& operator=(A &&) = default;
#else
    A() {}
    A(const A &) {}
    A& operator=(const A &) { return *this; }
#endif
};

// B: not copy & not move constructable/assignable

struct B
{
#if QEXT_OPTIONAL_CPP11_140
    B() = default;
    B(const B &) = delete;
    B& operator=(const B &) = delete;
    B(B &&) = delete;
    B& operator=(B &&) = delete;
#else
    B() {}
private:
    B(const B &) {}
    B& operator=(const B &) { return *this; }
#endif
};
} // issue_61
#endif

void QExtOptionalTest::Issues()
{

    //( "QExtOptional: isocpp-lib: CH 3, p0032r2 -- let's not have too clever tags" "[.issue-1]" )
    {
        // QVERIFY( false );
#if 0
    QExtOptional< QExtOptional< QExtOptional<int> > > a (
        qextOptionalInPlace,
#if 0
        qextOptionalInPlace,
#else
//        nonstd_lite_in_place_type_t(int),
        static_cast< nonstd::in_place_t >( qextOptionalInPlace ),
#endif
        QExtOptionalNullopt
    );

    QVERIFY(       a );
    QVERIFY(      *a );
    QVERIFY(! **a );
#endif
    }

    //( "QExtOptional: Invalid copy/move constructible/assignable detection" "[.issue-61-print]" )
    {
#if !QEXT_OPTIONAL_CPP11_110
        std::cout << "Note: Test requires C++11/VS2012 or newer, only works from VS2015.\n";
#else
        using issue_61::A;
        using issue_61::B;

        std::cout << "Copy constructible: "
                  << "\n" << std::is_copy_constructible<A>::value
                  << "  " << std::is_copy_constructible<QExtOptional<A>>::value
                  << "\n" << std::is_copy_constructible<B>::value
                  << "  " << std::is_copy_constructible<QExtOptional<B>>::value
                  << std::endl;

        std::cout << "Move constructible: "
                  << "\n" << std::is_move_constructible<A>::value
                  << "  " << std::is_move_constructible<QExtOptional<A>>::value
                  << "\n" << std::is_move_constructible<B>::value
                  << "  " << std::is_move_constructible<QExtOptional<B>>::value
                  << std::endl;

        std::cout << "Copy assignable: "
                  << "\n" << std::is_copy_assignable<A>::value
                  << "  " << std::is_copy_assignable<QExtOptional<A>>::value
                  << "\n" << std::is_copy_assignable<B>::value
                  << "  " << std::is_copy_assignable<QExtOptional<B>>::value
                  << std::endl;

        std::cout << "Move assignable: "
                  << "\n" << std::is_move_assignable<A>::value
                  << "  " << std::is_move_assignable<QExtOptional<A>>::value
                  << "\n" << std::is_move_assignable<B>::value
                  << "  " << std::is_move_assignable<QExtOptional<B>>::value
                  << std::endl;
#endif
    }

    //( "QExtOptional: Invalid copy/move constructible/assignable detection - Copy constructible" "[.issue-61-test]" )
    {
#if QEXT_OPTIONAL_CPP11_140
        using issue_61::A;
        using issue_61::B;

        QVERIFY( std::is_copy_constructible<A>::value );
        QVERIFY( std::is_copy_constructible<QExtOptional<A>>::value );

        QVERIFY( !std::is_copy_constructible<B>::value );
        QVERIFY( !std::is_copy_constructible<QExtOptional<B>>::value );
#else
#endif
    }

    //( "QExtOptional: Invalid copy/move constructible/assignable detection - Move constructible" "[.issue-61-test]" )
    {
#if QEXT_OPTIONAL_CPP11_140
        using issue_61::A;
        using issue_61::B;

        QVERIFY( std::is_move_constructible<A>::value );
        QVERIFY( std::is_move_constructible<QExtOptional<A>>::value );

        QVERIFY( !std::is_move_constructible<B>::value );
        QVERIFY( !std::is_move_constructible<QExtOptional<B>>::value );
#else
#endif
    }

    //( "QExtOptional: Invalid copy/move constructible/assignable detection - Copy assignable" "[.issue-61-test]" )
    {
#if QEXT_OPTIONAL_CPP11_140
        using issue_61::A;
        using issue_61::B;

        QVERIFY( std::is_copy_assignable<A>::value );
        QVERIFY( std::is_copy_assignable<QExtOptional<A>>::value );

        QVERIFY( !std::is_copy_assignable<B>::value );
        QVERIFY( !std::is_copy_assignable<QExtOptional<B>>::value );
#else
#endif
    }

    //( "QExtOptional: Invalid copy/move constructible/assignable detection - Move assignable" "[.issue-61-test]" )
    {
#if QEXT_OPTIONAL_CPP11_140
        using issue_61::A;
        using issue_61::B;

        QVERIFY( std::is_move_assignable<A>::value );
        QVERIFY( std::is_move_assignable<QExtOptional<A>>::value );

        QVERIFY( !std::is_move_assignable<B>::value );
        QVERIFY( !std::is_move_assignable<QExtOptional<B>>::value );
#else
#endif
    }
}

QTEST_APPLESS_MAIN(QExtOptionalTest)

#include <tst_qextOptional.moc>
