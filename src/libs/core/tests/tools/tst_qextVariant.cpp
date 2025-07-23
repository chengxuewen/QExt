#include <qextVariant.h>
#include <qextGlobal.h>

#include <QtTest>
#include <QDebug>
#include <QtEndian>
#include <QByteArray>

#include <sstream>

#if QEXT_VARIANT_HAVE_STD_VARIANT
#define variant_noexcept  noexcept
const void * test_nullptr = QEXT_NULLPTR;
#else
const void * test_nullptr = QEXT_VARIANT_NULLPTR;
#endif

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


class approx
{
public:
    explicit approx ( double magnitude )
        : epsilon_  ( 100.0 * static_cast<double>( std::numeric_limits<float>::epsilon() ) )
        , scale_    ( 1.0 )
        , magnitude_( magnitude ) {}

    static approx custom() { return approx( 0 ); }

    approx operator()( double new_magnitude )
    {
        approx appr( new_magnitude );
        appr.epsilon( epsilon_ );
        appr.scale  ( scale_   );
        return appr;
    }

    double magnitude() const { return magnitude_; }

    approx & epsilon( double epsilon ) { epsilon_ = epsilon; return *this; }
    approx & scale  ( double scale   ) { scale_   = scale;   return *this; }

    friend bool operator == ( double lhs, approx const & rhs )
    {
        // Thanks to Richard Harris for his help refining this formula.
        return std::abs( lhs - rhs.magnitude_ ) < rhs.epsilon_ * ( rhs.scale_ + (std::min)( std::abs( lhs ), std::abs( rhs.magnitude_ ) ) );
    }

    friend bool operator == ( approx const & lhs, double rhs ) { return  operator==( rhs, lhs ); }
    friend bool operator != ( double lhs, approx const & rhs ) { return !operator==( lhs, rhs ); }
    friend bool operator != ( approx const & lhs, double rhs ) { return !operator==( rhs, lhs ); }

    friend bool operator <= ( double lhs, approx const & rhs ) { return lhs < rhs.magnitude_ || lhs == rhs; }
    friend bool operator <= ( approx const & lhs, double rhs ) { return lhs.magnitude_ < rhs || lhs == rhs; }
    friend bool operator >= ( double lhs, approx const & rhs ) { return lhs > rhs.magnitude_ || lhs == rhs; }
    friend bool operator >= ( approx const & lhs, double rhs ) { return lhs.magnitude_ > rhs || lhs == rhs; }

private:
    double epsilon_;
    double scale_;
    double magnitude_;
};


struct Tracer
{
    State state;
    static int instances;

    static void reset() QEXT_NOEXCEPT { instances = 0; }

    ~Tracer() QEXT_NOEXCEPT { --instances; }
    Tracer()  QEXT_NOEXCEPT { ++instances; state = default_constructed; }

    Tracer( const Tracer & ) QEXT_NOEXCEPT  { ++instances; state = copy_constructed; }
    Tracer & operator= ( const Tracer & ) QEXT_NOEXCEPT  { state = copy_assigned; return *this; }

#if QEXT_VARIANT_CPP11_OR_GREATER
    Tracer( Tracer && ) QEXT_NOEXCEPT  { ++instances; state = move_constructed; }
    Tracer &  operator= ( Tracer && ) QEXT_NOEXCEPT  { state = move_assigned; return *this; }
#endif
};

int Tracer::instances = 0;

struct TracerX : Tracer{};
struct TracerY : Tracer{};

struct V
{
    State state;
    int   value;

    V(             ) : state( default_constructed ), value( deflt() ) {}
    V( int       v ) : state( value_constructed   ), value( v       ) {}
    V( V const & v ) : state( copy_constructed    ), value( v.value ) {}

    V & operator=( int       v ) { state = value_copy_assigned; value = v; return *this; }
    V & operator=( V const & v ) { state = copy_assigned      ; value = v.value; return *this; }

#if QEXT_VARIANT_CPP11_OR_GREATER
    V(             V && v ) : state( move_constructed   ), value(  std::move( v.value ) ) {}
    V & operator=( V && v ) { state = move_assigned      ; value = std::move( v.value ); return *this; }
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

#if QEXT_VARIANT_CPP11_OR_GREATER
    S(             V && v ) : state(  value_move_constructed ), value(  std::move( v ) ) { v.state = moved_from; }
    S(             S && s ) : state(  move_constructed       ), value(  std::move( s.value ) ) { s.state = moved_from; }

    S & operator=( V && v ) { state = value_move_assigned     ; value = std::move( v ); v.state = moved_from; return *this; }
    S & operator=( S && s ) { state = move_assigned           ; value = std::move( s.value ); s.state = moved_from; return *this; }
#endif

    bool operator==( S const & other ) const { return state == other.state && value == other.value; }
};

inline std::ostream & operator<<( std::ostream & os, V const & v )
{
    return os << "[V:" << std::to_string( v.value ) << "]";
}

class NoDefaultConstruct { NoDefaultConstruct(){} };

struct BlowCopyMoveConstruct
{
    static bool blow;
    static void enable_blow() { blow = true; }
    static void disable_blow() { blow = false; }

    ~BlowCopyMoveConstruct() {}
    BlowCopyMoveConstruct( bool blow_ = true ) { blow = blow_; }
    BlowCopyMoveConstruct( BlowCopyMoveConstruct const & ) { if ( blow ) throw 42; }
    BlowCopyMoveConstruct & operator=( BlowCopyMoveConstruct const & ) { return *this; }
#if QEXT_VARIANT_CPP11_OR_GREATER
    BlowCopyMoveConstruct( BlowCopyMoveConstruct && ) { if ( blow ) throw 42; }
    BlowCopyMoveConstruct & operator=( BlowCopyMoveConstruct && ) = default;
#endif
};

bool BlowCopyMoveConstruct::blow = true;

struct BlowCopyMoveAssign
{
    ~BlowCopyMoveAssign() {};
    BlowCopyMoveAssign() {}
    BlowCopyMoveAssign( BlowCopyMoveAssign const & ) {}
    BlowCopyMoveAssign & operator=( BlowCopyMoveAssign const & ) { throw 42; return *this; }
#if QEXT_VARIANT_CPP11_OR_GREATER
    BlowCopyMoveAssign( BlowCopyMoveAssign && ) = default;
    BlowCopyMoveAssign & operator=( BlowCopyMoveAssign && ) { throw 42; return *this; }
#endif
};

typedef QExtVariant<char, BlowCopyMoveConstruct> empty_variant_t;

empty_variant_t make_empty_variant()
{
    empty_variant_t var = 'a';

    try { var = BlowCopyMoveConstruct(); } catch(...) {}

    return var;
}

empty_variant_t make_non_empty_variant()
{
    return empty_variant_t( 'a' );
}

template< typename T >
std::size_t to_size_t( T v )
{
    return v;
}

class QExtVariantTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void construct();
    void obtain();
    void inspect();
    void copyAssign();
    void moveAssign();
    void inPlace();
    void emplace();
    void swap();
    void visit();
    void check();
    void get();
    void compare();
    void helper();
};

void QExtVariantTest::construct()
{
    // QExtVariant: Disallows non-default constructible as first type
    {
        // QExtVariant<NoDefaultConstruct> var;
    }

    // QExtVariant: Allows non-default constructible as second and later type (first: int)
    {
        QExtVariant<int, NoDefaultConstruct> var;
        (void) var;
    }

    // QExtVariant: Allows non-default constructible as second and later type (first: QExtVariantMonostate)
    {
        QExtVariant<QExtVariantMonostate, NoDefaultConstruct> var;
        (void) var;
    }

    // QExtVariant: Allows multiple identical types (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant<QExtVariantMonostate, int, int> var;
        (void) var;

        QVERIFY(true);
#else
        QSKIP("QExtVariant: multiple identical types are not available (no C++11)");
#endif
    }

    // QExtVariant: Allows to default-construct QExtVariant" )
    {
        QExtVariant<S> var;

        QVERIFY( qextVariantGet<S>(var).value.value == V::deflt() );
        QVERIFY( qextVariantGet<S>(var).value.state == default_constructed );
        QVERIFY( qextVariantGet<S>(var).state       == default_constructed );
    }

    // QExtVariant: Allows to copy-construct from QExtVariant" )
    {
        S s( 7 );
        QExtVariant<S> var1( s );

        QExtVariant<S> var2( var1 );

        QVERIFY( qextVariantGet<S>(var2).value.value == 7 );
        QVERIFY( qextVariantGet<S>(var2).state       == copy_constructed );
    }

    // QExtVariant: Allows to move-construct from QExtVariant (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant<S> var{ QExtVariant<S>{ S{} } };

        QVERIFY( qextVariantGet<S>(var).value.value == V::deflt()  );
        QVERIFY( qextVariantGet<S>(var).value.state == move_constructed );
        QVERIFY( qextVariantGet<S>(var).state       == move_constructed );
#else
        QSKIP("QExtVariant: move-construction is not available (no C++11)");
#endif
    }

    // QExtVariant: Allows to move-construct if-noexcept from QExtVariant (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        std::vector< QExtVariant<Tracer> > vec(1);

        QVERIFY( qextVariantGet<Tracer>( vec[0] ).state == default_constructed );

        vec.resize( 7 );
        QVERIFY( qextVariantGet<Tracer>( vec[0] ).state == move_constructed );
#else
        QSKIP("QExtVariant: move-construction is not available (no C++11)");
#endif
    }

    // "QExtVariant: Allows to construct from element value" )
    {
        V v(7);

        QExtVariant<S> var( v );

        QVERIFY( qextVariantGet<S>(var).value.value == 7 );
        QVERIFY(                 v.state != moved_from );
    }

    // "QExtVariant: Allows to copy-construct from element" )
    {
        S s(7);

        QExtVariant<S> var( s );

        QVERIFY( qextVariantGet<S>(var).value.value == 7 );
        QVERIFY( qextVariantGet<S>(var).state       == copy_constructed );
    }

    // "QExtVariant: Allows to move-construct from element (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant<S> var{ S{7} };

        QVERIFY( qextVariantGet<S>(var).value.value == 7 );
        QVERIFY( qextVariantGet<S>(var).state       == move_constructed );
#else
        QSKIP( "QExtVariant: move-construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to convert-copy-construct from element" )
    {
        int i = 7;

        QExtVariant<double, std::string> var1(  static_cast<double>(i) );
        QExtVariant<double, std::string> var2(  static_cast<double>(7) );

        QVERIFY( var1.index() == 0u              );
        QVERIFY( qextVariantGet<0>(var1) == approx(7) );

        QVERIFY( var2.index() == 0u              );
        QVERIFY( qextVariantGet<0>(var2) == approx(7) );
    }

    // "QExtVariant: Allows to convert-move-construct from element (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        struct Int { operator int() { return 7; } };

        QExtVariant<double, std::string> var( static_cast<double>(Int{}) );

        QVERIFY( var.index() == 0u              );
        QVERIFY( qextVariantGet<0>(var) == approx(7) );
#else
        QSKIP( "QExtVariant: move-construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to copy-construct from elements in intializer-list based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s{ 7 };
        std::string hello = "hello";
        using var_t = QExtVariant< int, long, double, std::string, S >;

        std::vector<var_t> vec = { 10, 15L, 1.5, hello, s };

        QVERIFY( qextVariantGet<0>( vec[0] ) == 10    );
        QVERIFY( qextVariantGet<1>( vec[1] ) == 15L   );
        QVERIFY( qextVariantGet<2>( vec[2] ) == approx(1.5) );
        QVERIFY( qextVariantGet<3>( vec[3] ) == hello );
        QVERIFY( qextVariantGet<4>( vec[4] ).value.value == 7 );
        QVERIFY( qextVariantGet<4>( vec[4] ).state       == copy_constructed );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-construct from elements in intializer-list based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        using var_t = QExtVariant<S>;

        std::vector<var_t> vec = { S{7} };

        QVERIFY( qextVariantGet<0>( vec[0] ).value.value == 7 );
        QVERIFY( qextVariantGet<0>( vec[0] ).state       == copy_constructed );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }

}

void QExtVariantTest::obtain()
{
    // QExtVariant: Allows to obtain the index of the current type
    QExtVariant<int, S> vari(   3  );
    QExtVariant<int, S> vars( S(7) );

    QVERIFY( 0u == vari.index() );
    QVERIFY( 1u == vars.index() );
}

void QExtVariantTest::inspect()
{
    // QExtVariant: Allows to inspect if QExtVariant is \"valueless by exception\""
#if QEXT_VARIANT_CPP11_OR_GREATER
    empty_variant_t var{ make_empty_variant() };

    QVERIFY( var.valueless_by_exception() );
#else
    QSKIP( "QExtVariant: emplace is not available (no C++11)" );
#endif
}

void QExtVariantTest::copyAssign()
{
    // "QExtVariant: Allows to copy-assign from QExtVariant"
    {
        // Before assignment, assignee is destructed"
        {
            Tracer::reset();
            {
                TracerY y;
                QExtVariant<TracerX, TracerY> var1;
                QExtVariant<TracerX, TracerY> var2;
                QExtVariant<TracerX, TracerY> var3(y);

                QVERIFY( Tracer::instances == 4 );

                var1 = var2; QVERIFY( Tracer::instances == 4 );
                var1 = var3; QVERIFY( Tracer::instances == 4 );
            }
            QVERIFY( Tracer::instances == 0 );
        }
        // On same-alternative assignment, assignee is copied-to"
        {
            QExtVariant<Tracer> var1;
            QExtVariant<Tracer> var2;

            var1 = var2;

            QVERIFY( qextVariantGet<Tracer>(var1).state == copy_assigned );
        }
        // On same-alternative assignment, assignee does not become valueless-by-exception"
        {
            QExtVariant<BlowCopyMoveAssign> var1;
            QExtVariant<BlowCopyMoveAssign> var2;

            try { var1 = var2; } catch (...) {}

            QVERIFY( !var1.valueless_by_exception() );
        }
        // On non-same-alternative assignment, assignee may become valueless-by-exception"
        {
            QExtVariant<int, BlowCopyMoveConstruct> var1;
            QExtVariant<int, BlowCopyMoveConstruct> var2( BlowCopyMoveConstruct( false ) );

            BlowCopyMoveConstruct::enable_blow();

            QVERIFY( !var1.valueless_by_exception() );

            try { var1 = var2; } catch (...) {}

#if QEXT_VARIANT_USES_STD_VARIANT
#   if QEXT_VARIANT_COMPILER_CLANG_VERSION
            QVERIFY( var1.valueless_by_exception() );
#   elif QEXT_VARIANT_COMPILER_GNU_VERSION
            QVERIFY( var1.valueless_by_exception() );
#   elif QEXT_VARIANT_COMPILER_MSVC_VERSION
            QVERIFY( !var1.valueless_by_exception() );
#   endif
#else // QEXT_VARIANT_USES_STD_VARIANT
            QVERIFY( var1.valueless_by_exception() );
#endif // QEXT_VARIANT_USES_STD_VARIANT
        }
    }

    // "QExtVariant: Allows to copy-assign mutually empty QExtVariant"
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        empty_variant_t var1{ make_empty_variant() };
        empty_variant_t var2{ make_empty_variant() };

        var1 = var2;

        QVERIFY( var1.valueless_by_exception() );
        QVERIFY( var2.valueless_by_exception() );
#else
        QSKIP( !!"QExtVariant: make_empty_variant requires C++11 (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to copy-assign from empty QExtVariant"
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        empty_variant_t var1{ make_non_empty_variant() };
        empty_variant_t var2{ make_empty_variant()     };

        var1 = var2;

        QVERIFY( var1.valueless_by_exception() );
        QVERIFY( var2.valueless_by_exception() );
#else
        QSKIP( !!"QExtVariant: make_empty_variant requires C++11 (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to copy-assign to empty QExtVariant"
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        empty_variant_t var1{ make_empty_variant()     };
        empty_variant_t var2{ make_non_empty_variant() };

        var1 = var2;

        QVERIFY( !var1.valueless_by_exception() );
        QVERIFY( !var2.valueless_by_exception() );
#else
        QSKIP( !!"QExtVariant: make_empty_variant requires C++11 (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to copy-assign from element value" )
    {
        //"same-alternative copy-assignment")
        {
            int seven = 7;
            QExtVariant<int> var = 42;

            var = seven;

            QVERIFY( qextVariantGet<int>(var) == seven );
        }
        //"non-same-alternative copy-assignment")
        {
            V v( 7 );
            QExtVariant<int, S> var1;
            QExtVariant<int, S> var2;

            var1 = v;
            var2 = V( 7 );  // copy for pre-C++11

            QVERIFY( qextVariantGet<S>(var1).value.value == 7 );
            QVERIFY(                 v.state != moved_from );

            QVERIFY( qextVariantGet<S>(var1).value.value == 7 );
        }
    }

    // "QExtVariant: Allows to convert-copy-assign from element value" )
    {
        char const * hello = "hello, world";
        QExtVariant<int, std::string> var1;
        QExtVariant<int, std::string> var2;

        var1 = hello;
        var2 = "hello, world";

        QVERIFY( qextVariantGet<1>(var1) ==  hello         );
        QVERIFY( qextVariantGet<1>(var2) == "hello, world" );
    }
}

void QExtVariantTest::moveAssign()
{

    // "QExtVariant: Allows to move-assign from QExtVariant (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        //"Before assignment, assignee is destructed")
        {
            Tracer::reset();
            {
                TracerY y;
                QExtVariant<TracerX, TracerY> var1;
                QExtVariant<TracerX, TracerY> var2;
                QExtVariant<TracerX, TracerY> var3(y);

                QVERIFY( Tracer::instances == 4 );

                var1 = std::move(var2); QVERIFY( Tracer::instances == 4 );
                var1 = std::move(var3); QVERIFY( Tracer::instances == 4 );
            }
            QVERIFY( Tracer::instances == 0 );
        }
        //"On same-alternative assignment, assignee is moved-to")
        {
            QExtVariant<Tracer> var1;
            QExtVariant<Tracer> var2;

            var1 = std::move(var2);

            QVERIFY( qextVariantGet<Tracer>(var1).state == move_assigned );
        }
        //"On same-alternative assignment, assignee does not become valueless-by-exception")
        {
            QExtVariant<BlowCopyMoveAssign> var1;
            QExtVariant<BlowCopyMoveAssign> var2;

            try { var1 = std::move(var2); } catch (...) {}

            QVERIFY(! var1.valueless_by_exception() );
        }
        //"On non-same-alternative assignment, assignee may become valueless-by-exception")
        {
            QExtVariant<int, BlowCopyMoveConstruct> var1;

            QVERIFY(! var1.valueless_by_exception() );

            try { var1 = BlowCopyMoveConstruct{}; } catch (...) {}

            QVERIFY( var1.valueless_by_exception() );
        }
#else
        QSKIP( "QExtVariant: move-assignment is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-assign mutually empty QExtVariant (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        empty_variant_t var{ make_empty_variant() };

        var = make_empty_variant() ;

        QVERIFY( var.valueless_by_exception() );
#else
        QSKIP( "QExtVariant: move-assignment is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-assign from empty QExtVariant (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        empty_variant_t var{ make_non_empty_variant() };

        var = make_empty_variant() ;

        QVERIFY( var.valueless_by_exception() );
#else
        QSKIP( "QExtVariant: move-assignment is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-assign to empty QExtVariant (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        empty_variant_t var{ make_empty_variant() };

        var = make_non_empty_variant();

        QVERIFY(! var.valueless_by_exception() );
#else
        QSKIP( "QExtVariant: move-assignment is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-assign from element value" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        //"same-alternative move-assignment")
        {
            QExtVariant<int> var = 42;

            var = 7;

            QVERIFY( qextVariantGet<int>(var) == 7 );
        }
        //"non-same-alternative move-assignment")
        {
            QExtVariant<int, S> var;

            var = V( 7 );

            QVERIFY( qextVariantGet<S>(var).value.value == 7 );
            QVERIFY( qextVariantGet<S>(var).value.state == move_constructed );
            QVERIFY( qextVariantGet<S>(var).value.state == move_constructed );
#if QEXT_VARIANT_USES_STD_VARIANT
            QVERIFY( qextVariantGet<S>(var).state       == value_move_constructed );
#else
            QVERIFY( qextVariantGet<S>(var).state       == move_constructed );
#endif
        }
#else
        QSKIP( "QExtVariant: move-construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to copy-assign from element" )
    {
        S s( 7 );
        QExtVariant<int, S> var1;
        QExtVariant<int, S> var2;

        var1 = s;
        var2 = S( 7 );  // copy for pre-C++11

        QVERIFY( qextVariantGet<S>(var1).value.value == 7 );
        QVERIFY(                  s.state != moved_from );

        QVERIFY( qextVariantGet<S>(var2).value.value == 7 );
    }

    // "QExtVariant: Allows to move-assign from element (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant<int, S> var;

        var = S{ 7 };

        QVERIFY( qextVariantGet<S>(var).value.value == 7 );
        QVERIFY( qextVariantGet<S>(var).state       == move_constructed );
#else
        QSKIP( "QExtVariant: move-assignment is not available (no C++11)" );
#endif
    }
}


#if QEXT_VARIANT_CPP11_OR_GREATER

namespace {

struct NoCopyMove
{
    S s; int  value;

    NoCopyMove( S const& t, int v  ) : s( t ), value( v ) {}
    NoCopyMove( S && t    , int v  ) : s( std::move(t) ), value( v ) {}
    NoCopyMove(                    ) = delete;
    NoCopyMove( NoCopyMove const & ) = delete;
    NoCopyMove( NoCopyMove &&      ) = delete;
};
}
#endif

#if QEXT_VARIANT_CPP11_OR_GREATER
struct InitList
{
    std::vector<int> vec;
    char c;
    S s;

    InitList( std::initializer_list<int> il, char k, S const & t)
        : vec( il ), c( k ), s( t ) {}

    InitList( std::initializer_list<int> il, char k, S && t)
        : vec( il ), c( k ), s( std::forward<S>(t) ) {}
};
#endif


void QExtVariantTest::inPlace()
{

    // "QExtVariant: Allows to in-place copy-construct element based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s( 7 );
#if QEXT_VARIANT_HAVE_IN_PLACE_TYPES // or QExtVariant-lite
        QExtVariant<int, NoCopyMove> var( qextVariantInPlaceType<NoCopyMove>, s, 7 );
//  QExtVariant<int, NoCopyMove> var( in_place<     NoCopyMove>, s, 7 );
#else
        QExtVariant<int, NoCopyMove> var( qextVariantInPlaceType<NoCopyMove>, s, 7 );
#endif
        QVERIFY( qextVariantGet<NoCopyMove>( var ).value == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.state == copy_constructed );
#else
        QSKIP( "QExtVariant: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to in-place move-construct element based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
#if QEXT_VARIANT_HAVE_IN_PLACE_TYPES // or QExtVariant-lite
        QExtVariant<int, NoCopyMove> var( qextVariantInPlaceType<NoCopyMove>, S( 7 ), 7 );
//  QExtVariant<int, NoCopyMove> var( in_place<     NoCopyMove>, S( 7 ), 7 );
#else
        QExtVariant<int, NoCopyMove> var( qextVariantInPlaceType<NoCopyMove>, S( 7 ), 7 );
#endif

        QVERIFY( qextVariantGet<NoCopyMove>( var ).value == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.state == move_constructed );
#else
        QSKIP( "QExtVariant: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to in-place copy-construct element based on index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s( 7 );
#if QEXT_VARIANT_HAVE_IN_PLACE_TYPES // or QExtVariant-lite
        QExtVariant<int, NoCopyMove> var( qextVariantInPlaceIndex<1>, s, 7 );
//  QExtVariant<int, NoCopyMove> var( in_place<      1>, s, 7 );
#else
        QExtVariant<int, NoCopyMove> var( qextVariantInPlaceIndex<1>, s, 7 );
#endif

        QVERIFY( qextVariantGet<1>( var ).value == 7 );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == copy_constructed );
#else
        QSKIP( "QExtVariant: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to in-place move-construct element based on index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
#if QEXT_VARIANT_HAVE_IN_PLACE_TYPES // or QExtVariant-lite
        QExtVariant<int, NoCopyMove> var( qextVariantInPlaceIndex<1>, S( 7 ), 7 );
//  QExtVariant<int, NoCopyMove> var( in_place<      1>, S( 7 ), 7 );
#else
        QExtVariant<int, NoCopyMove> var( qextVariantInPlaceIndex<1>, S( 7 ), 7 );
#endif

        QVERIFY( qextVariantGet<1>( var ).value == 7 );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == move_constructed );
#else
        QSKIP( "QExtVariant: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to in-place copy-construct elements from intializer-list based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s( 7 );

#if QEXT_VARIANT_HAVE_IN_PLACE_TYPES // or QExtVariant-lite
        QExtVariant< int, InitList> var( qextVariantInPlaceType<InitList>, { 7, 8, 9, }, 'a', s );
//  QExtVariant< int, InitList> var( in_place<     InitList>, { 7, 8, 9, }, 'a', s );
#else
        QExtVariant< int, InitList> var( qextVariantInPlaceType<InitList>, { 7, 8, 9, }, 'a', s );
#endif

        QVERIFY( qextVariantGet<1>( var ).vec[0]  ==  7  );
        QVERIFY( qextVariantGet<1>( var ).vec[1]  ==  8  );
        QVERIFY( qextVariantGet<1>( var ).vec[2]  ==  9  );
        QVERIFY( qextVariantGet<1>( var ).c       == 'a' );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == copy_constructed );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to in-place move-construct elements from intializer-list based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
#if QEXT_VARIANT_HAVE_IN_PLACE_TYPES // or QExtVariant-lite
        QExtVariant< int, InitList> var( qextVariantInPlaceType<InitList>, { 7, 8, 9, }, 'a', S( 7 ) );
//  QExtVariant< int, InitList> var( in_place<     InitList>, { 7, 8, 9, }, 'a', S( 7 ) );
#else
        QExtVariant< int, InitList> var( qextVariantInPlaceType<InitList>, { 7, 8, 9, }, 'a', S( 7 ) );
#endif

        QVERIFY( qextVariantGet<1>( var ).vec[0]  ==  7  );
        QVERIFY( qextVariantGet<1>( var ).vec[1]  ==  8  );
        QVERIFY( qextVariantGet<1>( var ).vec[2]  ==  9  );
        QVERIFY( qextVariantGet<1>( var ).c       == 'a' );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == move_constructed );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to in-place copy-construct elements from intializer-list based on index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s( 7 );

#if QEXT_VARIANT_HAVE_IN_PLACE_TYPES // or QExtVariant-lite
        QExtVariant< int, InitList> var( qextVariantInPlaceIndex<1>, { 7, 8, 9, }, 'a', s );
//  QExtVariant< int, InitList> var( in_place<      1>, { 7, 8, 9, }, 'a', s );
#else
        QExtVariant< int, InitList> var( qextVariantInPlaceIndex<1>, { 7, 8, 9, }, 'a', s );
#endif

        QVERIFY( qextVariantGet<1>( var ).vec[0]  ==  7  );
        QVERIFY( qextVariantGet<1>( var ).vec[1]  ==  8  );
        QVERIFY( qextVariantGet<1>( var ).vec[2]  ==  9  );
        QVERIFY( qextVariantGet<1>( var ).c       == 'a' );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == copy_constructed );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to in-place move-construct elements from intializer-list based on index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
#if QEXT_VARIANT_HAVE_IN_PLACE_TYPES // or QExtVariant-lite
        QExtVariant< int, InitList> var( qextVariantInPlaceIndex<1>, { 7, 8, 9, }, 'a', S( 7 ) );
//  QExtVariant< int, InitList> var( in_place<      1>, { 7, 8, 9, }, 'a', S( 7 ) );
#else
        QExtVariant< int, InitList> var( qextVariantInPlaceIndex<1>, { 7, 8, 9, }, 'a', S( 7 ) );
#endif

        QVERIFY( qextVariantGet<1>( var ).vec[0]  ==  7  );
        QVERIFY( qextVariantGet<1>( var ).vec[1]  ==  8  );
        QVERIFY( qextVariantGet<1>( var ).vec[2]  ==  9  );
        QVERIFY( qextVariantGet<1>( var ).c       == 'a' );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == move_constructed );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }
}

void QExtVariantTest::emplace()
{

    // "QExtVariant: Allows to copy-emplace element based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s( 7 );
        QExtVariant<int, NoCopyMove> var;

        auto & result = var.emplace<NoCopyMove>( s, 7 );

        QVERIFY( qextVariantGet<NoCopyMove>( var ).value         == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.value.value == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.state       == copy_constructed );

        QVERIFY(                                    7 ==  result.value );
        QVERIFY(&qextVariantGet<NoCopyMove>( var ).value         == &result.value );
#else
        QSKIP( "QExtVariant: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Disallows to copy-emplace non-unique element type on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant<QExtVariantMonostate, int, int> var;
        //var.emplace<int>(7);
        (void) var;

        QVERIFY( true );
#else
        QSKIP( "QExtVariant: multiple identical types are not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-emplace element based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant<int, NoCopyMove> var;

        auto & result = var.emplace<NoCopyMove>( S( 7 ), 7 );

        QVERIFY( qextVariantGet<NoCopyMove>( var ).value         == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.value.value == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.state       == move_constructed );

        QVERIFY(                                    7 ==  result.value );
        QVERIFY(&qextVariantGet<NoCopyMove>( var ).value         == &result.value );
#else
        QSKIP( "QExtVariant: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to copy-emplace element based on index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s( 7 );
        QExtVariant<int, NoCopyMove> var;

        auto & result = var.emplace<1>( s, 7 );

        QVERIFY( qextVariantGet<NoCopyMove>( var ).value         == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.value.value == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.state       == copy_constructed );

        QVERIFY(                                    7 ==  result.value );
        QVERIFY(&qextVariantGet<NoCopyMove>( var ).value         == &result.value );
#else
        QSKIP( "QExtVariant: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-emplace element based on index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant<int, NoCopyMove> var;

        auto & result = var.emplace<1>( S( 7 ), 7 );

        QVERIFY( qextVariantGet<NoCopyMove>( var ).value         == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.value.value == 7 );
        QVERIFY( qextVariantGet<NoCopyMove>( var ).s.state       == move_constructed );

        QVERIFY(                                    7 ==  result.value );
        QVERIFY(&qextVariantGet<NoCopyMove>( var ).value         == &result.value );
#else
        QSKIP( "QExtVariant: in-place construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to copy-emplace elements from intializer-list based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s( 7 );
        QExtVariant< int, InitList> var;

        auto & result = var.emplace<InitList>( { 7, 8, 9, }, 'a', s );

        QVERIFY( qextVariantGet<1>( var ).vec[0]  ==  7  );
        QVERIFY( qextVariantGet<1>( var ).vec[1]  ==  8  );
        QVERIFY( qextVariantGet<1>( var ).vec[2]  ==  9  );
        QVERIFY( qextVariantGet<1>( var ).c       == 'a' );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == copy_constructed );

        QVERIFY(                     7 ==  result.vec[0] );
        QVERIFY(& qextVariantGet<1>( var ).vec[0] == &result.vec[0] );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-emplace elements from intializer-list based on type (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant< int, InitList> var;

        auto & result = var.emplace<InitList>( { 7, 8, 9, }, 'a', S( 7 ) );

        QVERIFY( qextVariantGet<1>( var ).vec[0]  ==  7  );
        QVERIFY( qextVariantGet<1>( var ).vec[1]  ==  8  );
        QVERIFY( qextVariantGet<1>( var ).vec[2]  ==  9  );
        QVERIFY( qextVariantGet<1>( var ).c       == 'a' );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == move_constructed );

        QVERIFY(                     7 ==  result.vec[0] );
        QVERIFY(& qextVariantGet<1>( var ).vec[0] == &result.vec[0] );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to copy-emplace elements from intializer-list based on index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        S s( 7 );
        QExtVariant< int, InitList> var;

        auto & result = var.emplace<1>( { 7, 8, 9, }, 'a', s );

        QVERIFY( qextVariantGet<1>( var ).vec[0]  ==  7  );
        QVERIFY( qextVariantGet<1>( var ).vec[1]  ==  8  );
        QVERIFY( qextVariantGet<1>( var ).vec[2]  ==  9  );
        QVERIFY( qextVariantGet<1>( var ).c       == 'a' );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == copy_constructed );

        QVERIFY(                     7 ==  result.vec[0] );
        QVERIFY(& qextVariantGet<1>( var ).vec[0] == &result.vec[0] );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }

    // "QExtVariant: Allows to move-emplace elements from intializer-list based on index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant< int, InitList> var;

        auto & result = var.emplace<1>( { 7, 8, 9, }, 'a', S( 7 ) );

        QVERIFY( qextVariantGet<1>( var ).vec[0]  ==  7  );
        QVERIFY( qextVariantGet<1>( var ).vec[1]  ==  8  );
        QVERIFY( qextVariantGet<1>( var ).vec[2]  ==  9  );
        QVERIFY( qextVariantGet<1>( var ).c       == 'a' );
        QVERIFY( qextVariantGet<1>( var ).s.value .value == 7  );
        QVERIFY( qextVariantGet<1>( var ).s.state == move_constructed );

        QVERIFY(                     7 ==  result.vec[0] );
        QVERIFY(& qextVariantGet<1>( var ).vec[0] == &result.vec[0] );
#else
        QSKIP( "QExtVariant: initializer_list construction is not available (no C++11)" );
#endif
    }
}

struct Doubler
{
    template< class T >
    T operator()( T a ) const { return a + a; }
};
void QExtVariantTest::swap()
{

    // "QExtVariant: Allows to swap variants, same index (member)" )
    {
        QExtVariant<int, S> var1( 1 );
        QExtVariant<int, S> var2( 2 );

        var1.swap( var2 );

        QVERIFY( qextVariantGet<int>( var1 ) == 2 );
        QVERIFY( qextVariantGet<int>( var2 ) == 1 );
    }

    // "QExtVariant: Allows to swap variants, different index (member)" )
    {
        S s( 7 );
        QExtVariant<int, S> vari( 3 );
        QExtVariant<int, S> vars( s );

        vari.swap( vars );

        QVERIFY( s.value.value == qextVariantGet< S >( vari ).value.value );
        QVERIFY(             3 == qextVariantGet<int>( vars )             );
    }


    // "QExtVariant: Allows to swap variants, same index (non-member)" )
    {
        QExtVariant<int, S> var1( 1 );
        QExtVariant<int, S> var2( 2 );

        qextVariantSwap( var1, var2 );

        QVERIFY( qextVariantGet<int>( var1 ) == 2 );
        QVERIFY( qextVariantGet<int>( var2 ) == 1 );
    }

    // "QExtVariant: Allows to swap variants, different index (non-member)" )
    {
        S s( 7 );
        QExtVariant<int, S> vari( 3 );
        QExtVariant<int, S> vars( s );

        qextVariantSwap( vari, vars );

        QVERIFY( s.value.value == qextVariantGet< S >( vari ).value.value );
        QVERIFY(             3 == qextVariantGet<int>( vars )             );
    }

}

struct GenericVisitor1
{
    std::string operator()( int val ) const
    {
        std::ostringstream os;
        os << val;
        return os.str();
    }

    std::string operator()( std::string const & val ) const
    {
        std::ostringstream os;
        os << val;
        return os.str();
    }
};

struct GenericVisitor2
{
    template< typename T1, typename T2 >
    std::string operator()( T1 const & v1, T2 const & v2 ) const
    {
        std::ostringstream os;
        os << v1 << v2;
        return os.str();
    }
};

struct GenericVisitor3
{
    template<typename T1, typename T2, typename T3>
    std::string operator()(const T1& v1, const T2& v2, const T3& v3) const
    {
        std::ostringstream os;
        os << v1 << v2 << v3;
        return os.str();
    }
};

#if QEXT_VARIANT_CPP14_OR_GREATER

struct RVRefTestVisitor
{
    std::string operator()( int val ) const
    {
        std::ostringstream os;
        os << val;
        return os.str();
    }
    std::string operator()( std::string const & val ) const
    {
        std::ostringstream os;
        os << val;
        return os.str();
    }

    template< typename ... Args >
    std::string operator()( QExtVariant<Args...> const & var ) const
    {
        return visit( RVRefTestVisitor(), var );
    }

    template< typename U >
    std::string operator()( U && val) const
    {
#if QEXT_VARIANT_USES_STD_VARIANT
        std::ostringstream os;
        os << val;
        return os.str();
#else
        static_assert( std::is_const<U>::value, "Wrong branch!" );
        (void) val;
        return ">>> Broken branch! <<<";
#endif
    }
};

struct Unwrapper
{
    RVRefTestVisitor * m_v;

    Unwrapper( RVRefTestVisitor * v )
        : m_v( v )
    {}

    template< typename T >
    auto & Unwrap( T && val ) const
    {
        return std::forward<T>( val );
    }

    template< typename T >
    const auto & Unwrap( std::shared_ptr<T> val ) const
    {
        const auto & result = *val.get();
        return result;
    }

    template< typename ... Args >
    auto operator()( Args &&... args ) const
    {
        return (*m_v)( Unwrap( std::forward<Args>(args))...);
    }
};

#endif


void QExtVariantTest::visit()
{

#if QEXT_VARIANT_USES_STD_VARIANT
        // "QExtVariant: Allows to visit contents (args: 1)" )
#else
        // "QExtVariant: Allows to visit contents (args: 1; configured max args: " + to_string(variant_CONFIG_MAX_VISITOR_ARG_COUNT) + ")" )
#endif
    {
        typedef QExtVariant< int, std::string > var_t;
        var_t vi = 7;
        var_t vs = std::string("hello");
#if QEXT_VARIANT_CPP11_OR_GREATER
        std::string ri = qextVariantVisit(GenericVisitor1(), vi);
        std::string rs = qextVariantVisit(GenericVisitor1(), vs);
#else
        std::string ri = qextVariantVisit<std::string>(GenericVisitor1(), vi);
        std::string rs = qextVariantVisit<std::string>(GenericVisitor1(), vs);
#endif
        QVERIFY( ri == "7" );
        QVERIFY( rs == "hello" );
    }

#if QEXT_VARIANT_USES_STD_VARIANT
    // "QExtVariant: Allows to visit contents (args: 2)" )
#else
    // "QExtVariant: Allows to visit contents (args: 2; configured max args: " + to_string(variant_CONFIG_MAX_VISITOR_ARG_COUNT) + ")" )
#endif
    {
        typedef QExtVariant< int, std::string > var_t;
        var_t vi = 7;
        var_t vs = std::string("hello");

#if QEXT_VARIANT_CPP11_OR_GREATER
        std::string r = qextVariantVisit(GenericVisitor2(), vi, vs);
#else
        std::string r = qextVariantVisit<std::string>(GenericVisitor2(), vi, vs);
#endif

        QVERIFY( r == "7hello" );
    }

#if QEXT_VARIANT_USES_STD_VARIANT
    // "QExtVariant: Allows to visit contents (args: 3)" )
#else
    // "QExtVariant: Allows to visit contents (args: 3; configured max args: " + to_string(variant_CONFIG_MAX_VISITOR_ARG_COUNT) + ")" )
#endif
    {
        typedef QExtVariant< int, std::string, double > var_t;
        var_t vi = 7;
        var_t vs = std::string("hello");
        var_t vd = 0.5;

#if QEXT_VARIANT_CPP11_OR_GREATER
        std::string r = qextVariantVisit(GenericVisitor3(), vi, vs, vd);
#else
        std::string r = qextVariantVisit<std::string>(GenericVisitor3(), vi, vs, vd);
#endif

        QVERIFY( r == "7hello0.5" );
    }

#if QEXT_VARIANT_USES_STD_VARIANT
    // "QExtVariant: Allows to visit contents, rvalue reference (args: 1)" )
#else
    // "QExtVariant: Allows to visit contents, rvalue reference (args: 1; configured max args: " + to_string(variant_CONFIG_MAX_VISITOR_ARG_COUNT) + ")" )
#endif
    {
#if QEXT_VARIANT_CPP14_OR_GREATER
        typedef std::shared_ptr< std::string > string_ptr_t;
        typedef QExtVariant< int, std::string, string_ptr_t > var_t;
        string_ptr_t inner = std::make_shared< std::string >("hello1");

        var_t vstr1 = inner;
        var_t vstr2 = std::string("hello2");
        RVRefTestVisitor visitor;

        std::string rs1 = qextVariantVisit( Unwrapper( &visitor ), vstr1 );
        std::string rs2 = qextVariantVisit( Unwrapper( &visitor ), vstr2 );

        QVERIFY( rs1 == "hello1" );
        QVERIFY( rs2 == "hello2" );
#else
        QSKIP( "QExtVariant: return type deduction is not available (no C++14)" );
#endif
    }

}

void QExtVariantTest::check()
{

    // "QExtVariant: Allows to check for content by type" )
    {
        typedef QExtVariant< int, long, double, std::string > var_t;
        var_t vi = 7;
        var_t vl = 7L;
        var_t vd = 7.0;
        var_t vs = std::string("hello");

        QVERIFY(     qextVariantHoldsAlternative< int          >( vi ) );
        QVERIFY(     qextVariantHoldsAlternative< long         >( vl ) );
        QVERIFY(     qextVariantHoldsAlternative< double       >( vd ) );
        QVERIFY(     qextVariantHoldsAlternative< std::string  >( vs ) );

#if ! QEXT_VARIANT_USES_STD_VARIANT // fires static_assert with g++ (GCC) 7.2.0:
        QVERIFY(! qextVariantHoldsAlternative< char         >( vi ) );
        QVERIFY(! qextVariantHoldsAlternative< short        >( vi ) );
        QVERIFY(! qextVariantHoldsAlternative< float        >( vd ) );

        QVERIFY(! qextVariantHoldsAlternative< unsigned int >( vi ) );
#endif
    }

}

void QExtVariantTest::get()
{

    // "QExtVariant: Allows to get element by type" )
    {
        QExtVariant<int, S> var( S( 7 ) );

        QVERIFY( qextVariantGet<S>(var).value.value == 7 );
    }

    // "QExtVariant: Allows to get element by index" )
    {
        QExtVariant<int, S> var( S( 7 ) );

        QVERIFY( qextVariantGet<1>(var).value.value == 7 );
    }

    // "QExtVariant: Allows to get pointer to element or NULL by type" )
    {
        QExtVariant<int, S> var( S( 7 ) );

        QVERIFY( test_nullptr == qextVariantGetIf<int>( &var ) );

        QVERIFY( test_nullptr != qextVariantGetIf< S >( &var ) );
        QVERIFY(                 qextVariantGetIf< S >( &var )->value.value == 7 );
    }

    // "QExtVariant: Allows to get pointer to element or NULL by index" )
    {
        QExtVariant<int, S> var( S( 7 ) );

        QVERIFY( test_nullptr == qextVariantGetIf<0>( &var ) );

        QVERIFY( test_nullptr != qextVariantGetIf<1>( &var ) );
        QVERIFY(                 qextVariantGetIf<1>( &var )->value.value == 7 );
    }

}

void QExtVariantTest::compare()
{

    // "QExtVariant: Allows to compare variants" )
    {
        QExtVariant<int, double> v = 3, w = 7;

        QVERIFY( v == v );
        QVERIFY( v != w );
        QVERIFY( v <  w );
        QVERIFY( w >  v );
        QVERIFY( v <= v );
        QVERIFY( v <= w );
        QVERIFY( v >= v );
        QVERIFY( w >= v );

        QVERIFY(! (v == w) );
        QVERIFY(! (v != v) );
        QVERIFY(! (w <  v) );
        QVERIFY(! (v >  w) );
        QVERIFY(! (w <= v) );
        QVERIFY(! (v >= w) );
    }

}

//
// QExtVariant helper classes:
//

namespace {
struct t1{};
struct t2{};
struct t3{};
struct t4{};
struct t5{};
struct t6{};
struct t7{};
struct t8{};
}

namespace issue_31 {

struct CopyOnly
{
    CopyOnly() {}
    CopyOnly( CopyOnly const & ) {}
    CopyOnly & operator=( CopyOnly const & ) { return *this; }

#if QEXT_VARIANT_CPP11_OR_GREATER
    CopyOnly( CopyOnly && ) = delete;
    CopyOnly & operator=( CopyOnly && ) = delete;
#endif
};
}

#if QEXT_VARIANT_CPP11_OR_GREATER

namespace {

struct Pad
{
    union { char c; int  i; };
};

// ensure non-char bits differ:

Pad make_pad1() { Pad p; p.i =  0; p.c = 'x'; return p; }
Pad make_pad2() { Pad p; p.i = ~0; p.c = 'x'; return p; }
}

namespace std {

template<>
struct hash<Pad>
{
    std::size_t operator()( Pad const & v ) const variant_noexcept
    {
        return std::hash<char>{}( v.c );
    }
};
}

#endif

namespace issue_33 {

template< size_t i > class N { int k; };
}

namespace issue_39 {

struct tag_t {};

struct myvisitor
{
    const std::string& operator()(const int&) const { throw std::exception(); }
    const std::string& operator()(const tag_t&) const { throw std::exception(); }
    const std::string& operator()(const std::string& s) const { return s; }
};
}

void QExtVariantTest::helper()
{

    // "QExtVariantMonostate: Allows to make QExtVariant default-constructible" )
    {
        QExtVariant<QExtVariantMonostate, NoDefaultConstruct> var;
        (void) var;

        QVERIFY( true );
    }

    // "bad_variant_access: Indicates invalid QExtVariant access" )
    {
        QExtVariant< char, int > v = 7;
        QExtVariant< char, int > const c = 7;

        QVERIFY_EXCEPTION_THROWN( qextVariantGet<  0 >( v ), QExtBadVariantAccess );
        QVERIFY_EXCEPTION_THROWN( qextVariantGet<  0 >( c ), QExtBadVariantAccess );
        QVERIFY_EXCEPTION_THROWN( qextVariantGet<char>( v ), QExtBadVariantAccess );
        QVERIFY_EXCEPTION_THROWN( qextVariantGet<char>( c ), QExtBadVariantAccess );
    }

#if QEXT_VARIANT_USES_STD_VARIANT
    // "QExtVariantSize<>: Allows to obtain number of element types" )
#else
    // "QExtVariantSize<>: Allows to obtain number of element types (configured max types: " + to_string(variant_CONFIG_MAX_TYPE_COUNT) + ")" )
#endif
    {
        typedef QExtVariant<t1> var1;
        typedef QExtVariant<t1, t2> var2;
        typedef QExtVariant<t1, t2, t3> var3;
        typedef QExtVariant<t1, t2, t3, t4> var4;
        typedef QExtVariant<t1, t2, t3, t4, t5> var5;
        typedef QExtVariant<t1, t2, t3, t4, t5, t6> var6;
        typedef QExtVariant<t1, t2, t3, t4, t5, t6, t7> var7;
        //  typedef QExtVariant<t1, t2, t3, t4, t5, t6, t7, t8> var8;

        QVERIFY( 1u == to_size_t( QExtVariantSize<var1>::value ) );
        QVERIFY( 2u == to_size_t( QExtVariantSize<var2>::value ) );
        QVERIFY( 3u == to_size_t( QExtVariantSize<var3>::value ) );
        QVERIFY( 4u == to_size_t( QExtVariantSize<var4>::value ) );
        QVERIFY( 5u == to_size_t( QExtVariantSize<var5>::value ) );
        QVERIFY( 6u == to_size_t( QExtVariantSize<var6>::value ) );
        QVERIFY( 7u == to_size_t( QExtVariantSize<var7>::value ) );
        //  QVERIFY( 8u == to_size_t( QExtVariantSize<var8>::value ) );
    }

#if QEXT_VARIANT_USES_STD_VARIANT
    // "variant_size_v<>: Allows to obtain number of element types (C++14)" )
#else
    // "variant_size_v<>: Allows to obtain number of element types (C++14; configured max types: " + to_string(variant_CONFIG_MAX_TYPE_COUNT) + ")" )
#endif
    {
#if QEXT_VARIANT_CPP14_OR_GREATER
        typedef QExtVariant<t1> var1;
        typedef QExtVariant<t1, t2> var2;
        typedef QExtVariant<t1, t2, t3> var3;
        typedef QExtVariant<t1, t2, t3, t4> var4;
        typedef QExtVariant<t1, t2, t3, t4, t5> var5;
        typedef QExtVariant<t1, t2, t3, t4, t5, t6> var6;
        typedef QExtVariant<t1, t2, t3, t4, t5, t6, t7> var7;
        //  typedef QExtVariant<t1, t2, t3, t4, t5, t6, t7, t8> var8;

        QVERIFY( 1u == QExtVariantSizeV<var1> );
        QVERIFY( 2u == QExtVariantSizeV<var2> );
        QVERIFY( 3u == QExtVariantSizeV<var3> );
        QVERIFY( 4u == QExtVariantSizeV<var4> );
        QVERIFY( 5u == QExtVariantSizeV<var5> );
        QVERIFY( 6u == QExtVariantSizeV<var6> );
        QVERIFY( 7u == QExtVariantSizeV<var7> );
//  QVERIFY( 8u == QExtVariantSizeV<var8>::value );
#else
        QSKIP( "variant_size_v<>: variable templates is not available (no C++14)" );
#endif
    }

#if QEXT_VARIANT_USES_STD_VARIANT
    // "variant_size_V(): Allows to obtain number of element types (non-standard: macro)" )
#else
    // "variant_size_V(): Allows to obtain number of element types (non-standard: macro; configured max types: " + to_string(variant_CONFIG_MAX_TYPE_COUNT) + ")" )
#endif
    {
        typedef QExtVariant<t1> var1;
        typedef QExtVariant<t1, t2> var2;
        typedef QExtVariant<t1, t2, t3> var3;
        typedef QExtVariant<t1, t2, t3, t4> var4;
        typedef QExtVariant<t1, t2, t3, t4, t5> var5;
        typedef QExtVariant<t1, t2, t3, t4, t5, t6> var6;
        typedef QExtVariant<t1, t2, t3, t4, t5, t6, t7> var7;
        //  typedef QExtVariant<t1, t2, t3, t4, t5, t6, t7, t8> var8;

        QVERIFY( 1u == to_size_t( variant_size_V( var1 ) ) );
        QVERIFY( 2u == to_size_t( variant_size_V( var2 ) ) );
        QVERIFY( 3u == to_size_t( variant_size_V( var3 ) ) );
        QVERIFY( 4u == to_size_t( variant_size_V( var4 ) ) );
        QVERIFY( 5u == to_size_t( variant_size_V( var5 ) ) );
        QVERIFY( 6u == to_size_t( variant_size_V( var6 ) ) );
        QVERIFY( 7u == to_size_t( variant_size_V( var7 ) ) );
        //  QVERIFY( 8u == to_size_t( variant_size_V( var8 ) ) );
    }

    // " QExtVariantAlternative<>: Allows to select type by index" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        // QExtVariantAlternative< 0, QExtVariant<char> >::type;
        static_assert( std::is_same<char, typename  QExtVariantAlternative< 0, QExtVariant<char> >::type >::value, " QExtVariantAlternative<0,...>" );
        static_assert( std::is_same<char, typename  QExtVariantAlternative< 1, QExtVariant<int, char> >::type >::value, " QExtVariantAlternative<1,...>" );
        static_assert( std::is_same<char, typename  QExtVariantAlternative< 2, QExtVariant<int, int, char> >::type >::value, " QExtVariantAlternative<2,...>" );
        static_assert( std::is_same<char, typename  QExtVariantAlternative< 3, QExtVariant<int, int, int, char> >::type >::value, " QExtVariantAlternative<3,...>" );
        static_assert( std::is_same<char, typename  QExtVariantAlternative< 4, QExtVariant<int, int, int, int, char> >::type >::value, " QExtVariantAlternative<4,...>" );
        static_assert( std::is_same<char, typename  QExtVariantAlternative< 5, QExtVariant<int, int, int, int, int, char> >::type >::value, " QExtVariantAlternative<5,...>" );
        static_assert( std::is_same<char, typename  QExtVariantAlternative< 6, QExtVariant<int, int, int, int, int, int, char> >::type >::value, " QExtVariantAlternative<6,...>" );
#else
        QSKIP( " qextVariantAlternative<>: static_assert is not available (no C++11)" );
#endif
    }

    // "QExtVariantAlternativeT<>: Allows to select type by index (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        static_assert( std::is_same<char, QExtVariantAlternativeT< 0, QExtVariant<char> > >::value, "QExtVariantAlternativeT<0,...>" );
        static_assert( std::is_same<char, QExtVariantAlternativeT< 1, QExtVariant<int, char> > >::value, "QExtVariantAlternativeT<1,...>" );
        static_assert( std::is_same<char, QExtVariantAlternativeT< 2, QExtVariant<int, int, char> > >::value, "QExtVariantAlternativeT<2,...>" );
        static_assert( std::is_same<char, QExtVariantAlternativeT< 3, QExtVariant<int, int, int, char> > >::value, "QExtVariantAlternativeT<3,...>" );
        static_assert( std::is_same<char, QExtVariantAlternativeT< 4, QExtVariant<int, int, int, int, char> > >::value, "QExtVariantAlternativeT<4,...>" );
        static_assert( std::is_same<char, QExtVariantAlternativeT< 5, QExtVariant<int, int, int, int, int, char> > >::value, "QExtVariantAlternativeT<5,...>" );
        static_assert( std::is_same<char, QExtVariantAlternativeT< 6, QExtVariant<int, int, int, int, int, int, char> > >::value, "QExtVariantAlternativeT<6,...>" );
#else
        QSKIP( "QExtVariantAlternativeT<>: alias template is not available (no C++11)" );
#endif
    }

    // "variant_alternative_T(): Allows to select type by index (non-standard: macro)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        // cannot use QExtVariant<int, char> in macro due to comma:

        typedef QExtVariant<char> var0;
        typedef QExtVariant<int, char> var1;
        typedef QExtVariant<int, int, char> var2;
        typedef QExtVariant<int, int, int, char> var3;
        typedef QExtVariant<int, int, int, int, char> var4;
        typedef QExtVariant<int, int, int, int, int, char> var5;
        typedef QExtVariant<int, int, int, int, int, int, char> var6;

        static_assert( std::is_same<char, variant_alternative_T( 0, var0 ) >::value, "variant_alternative_T(0, var0)" );
        static_assert( std::is_same<char, variant_alternative_T( 1, var1 ) >::value, "variant_alternative_T(1, var1)" );
        static_assert( std::is_same<char, variant_alternative_T( 2, var2 ) >::value, "variant_alternative_T(2, var2)" );
        static_assert( std::is_same<char, variant_alternative_T( 3, var3 ) >::value, "variant_alternative_T(3, var3)" );
        static_assert( std::is_same<char, variant_alternative_T( 4, var4 ) >::value, "variant_alternative_T(4, var4)" );
        static_assert( std::is_same<char, variant_alternative_T( 5, var5 ) >::value, "variant_alternative_T(5, var5)" );
        static_assert( std::is_same<char, variant_alternative_T( 6, var6 ) >::value, "variant_alternative_T(6, var6)" );
#else
        QSKIP( "variant_alternative_T(): static_assert is not available (no C++11)" );
#endif
    }

    // "std::hash<>: Allows to obtain hash (C++11)" )
    {
#if QEXT_VARIANT_CPP11_OR_GREATER
        using variant_t = QExtVariant<char, Pad>;
        variant_t var1( make_pad1() );
        variant_t var2( make_pad2() );

        QVERIFY( std::hash<variant_t>{}( var1 ) == std::hash<variant_t>{}( var2 ) );
#else
        QSKIP( "std::hash<>: std::hash<> is not available (no C++11)" );
#endif
    }

    //"index_of<>(): method should be static" "[.issue-30]")
    {
#if QEXT_VARIANT_CPP11_OR_GREATER && ! QEXT_VARIANT_USES_STD_VARIANT
        typedef QExtVariant<int, double, std::string> Value;
        Value value("Some string");

        switch ( value.index() )
        {
        case Value::index_of<int>():
            // do something
            break;
        case Value::index_of<double>():
            // do something
            break;
        case Value::index_of<std::string>():
            // do something
            break;
        }

        QSKIP( "prevent warnings" );
#else
        QSKIP( "index_of<>(): test is not available (no C++11, or std::QExtVariant)" );
#endif
    }

    //"operator=(T const &): assignment from element lvalue must use copy-assignment in C++11 and later" "[.issue-31]")
    {
        QExtVariant<V> var1;
        QExtVariant<V> var2;
        V seven = 7;

        var1 = 7;
        var2 = seven;

        QVERIFY( qextVariantGet<V>(var1).state == (variant_CPP11_OR_GREATER ? move_assigned : copy_assigned) );
        QVERIFY( qextVariantGet<V>(var2).state == copy_assigned );
    }

    //"operator=(QExtVariant const &): copy-assignment from QExtVariant lvalue must not require element move-assignment in C++11 and later" "[.issue-31]")
    {
        using namespace issue_31;

        QExtVariant<CopyOnly> var1;
        QExtVariant<CopyOnly> var2;

        var1 = var2;

        QVERIFY( true );
    }

    //"max_index(): should not cause erroneous bad_variant_access in get()" "[.issue-33]")
    {
        if ( 4 == sizeof(int) )
        {
            using issue_33::N;
            typedef QExtVariant<N<0>, N<1>, N<2>, N<3>, int> variant_t;

            // EXPECT_NO_THROW( qextVariantGet<int>( variant_t( 13 ) ) );
        }
        else
        {
            QSKIP( "max_index(): test is not available (sizeof(int) != 4)" );
        }
    }

    //"visitor: Visitors can't return references, but they can with std::QExtVariant" "[.issue-39]")
    {
        using namespace issue_39;

#if QEXT_VARIANT_CPP11_OR_GREATER
        QExtVariant<int, tag_t, std::string> v("hello");
        qextVariantVisit( myvisitor(), v );
#else
        QSKIP( "visitor: references cannot be used yet with C++98 (no C++11)" );
#endif
    }

    // "tweak header: reads tweak header if supported " "[tweak]" )
    {
#if QEXT_VARIANT_HAVE_TWEAK_HEADER
        QVERIFY( VARIANT_TWEAK_VALUE == 42 );
#else
        QSKIP( "Tweak header is not available (variant_HAVE_TWEAK_HEADER: 0)." );
#endif
    }
}

QTEST_APPLESS_MAIN(QExtVariantTest)

#include <tst_qextVariant.moc>
