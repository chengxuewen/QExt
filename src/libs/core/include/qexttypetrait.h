#ifndef QEXTTYPETRAIT_H
#define QEXTTYPETRAIT_H

template <typename T_type>
struct QEXTTypeTrait
{
    typedef T_type  Type;
    typedef T_type& Pass;
    typedef const T_type& Take;
    typedef T_type* Pointer;
};

template <typename T_type, int N>
struct QEXTTypeTrait<T_type[N]>
{
    typedef T_type*  Type;
    typedef T_type*& Pass;
    typedef const T_type*& Take;
    typedef T_type** Pointer;
};

template <typename T_type>
struct QEXTTypeTrait<T_type&>
{
    typedef T_type  Type;
    typedef T_type& Pass;
    typedef T_type& Take;
    typedef T_type* Pointer;
};

template <typename T_type>
struct QEXTTypeTrait<const T_type&>
{
    typedef const T_type  Type;
    typedef const T_type& Pass;
    typedef const T_type& Take;
    typedef const T_type* Pointer;
};

template<>
struct QEXTTypeTrait<void>
{
    typedef void  Type;
    typedef void  Pass;
    typedef void  Take;
    typedef void* Pointer;
};


// From Esa Pulkkin:
/**
 * Compile-time determination of base-class relationship in C++.
 *
 * Use this to provide a template specialization for a set of types.
 * For instance,
 *
 * @code
 * template < class T_thing, bool Tval_derives_from_something = QEXTBaseAndDerivedTester<Something, T_thing>::value >
 * class TheTemplate
 * {
 *   //Standard implementation.
 * }
 *
 * //Specialization for T_things that derive from Something (Tval_derives_from_something is true)
 * template <typename T_thing>
 * class TheTemplate<T_thing, true>
 * {
 *   T_thing thing;
 *   thing.method_that_is_in_something();
 * }
 * @endcode
 *
 * If you need such a template class elsewhere, and you have a C++11 compiler, std::is_base_of<>
 * is recommended.
 */
template <typename T_base, typename T_derived>
struct QEXTBaseAndDerivedTester
{
private:
    struct Big {
        char memory[64];
    };

    //#ifndef SIGC_SELF_REFERENCE_IN_MEMBER_INITIALIZATION
#if 0

    //Allow the internal inner class to access the other (Big) inner class.
    //The Tru64 compiler needs this.
    friend struct InternalClass;

    //Certain compilers, notably GCC 3.2, require these functions to be inside an inner class.
    struct InternalClass
    {
        static Big  isBaseClass(...);
        static char isBaseClass(typename QEXTTypeTrait<T_base>::Pointer);
    };

public:
    static const bool value =
            sizeof(InternalClass::isBaseClass(reinterpret_cast<typename QEXTTypeTrait<T_derived>::Pointer>(0))) ==
            sizeof(char);

#else //SIGC_SELF_REFERENCE_IN_MEMBER_INITIALIZATION

    //The AIX xlC compiler does not like these 2 functions being in the inner class.
    //It says "The incomplete type "test" must not be used as a qualifier.
    //It does not seem necessary anyway.
    static Big  isBaseClass(...);
    static char isBaseClass(typename QEXTTypeTrait<T_base>::Pointer);

public:
    static const bool value =
            sizeof(isBaseClass(reinterpret_cast<typename QEXTTypeTrait<T_derived>::Pointer>(0))) ==
            sizeof(char);

#endif //SIGC_SELF_REFERENCE_IN_MEMBER_INITIALIZATION
};

template <typename T_base>
struct QEXTBaseAndDerivedTester<T_base, T_base>
{
    static const bool value = true;
};

#endif // QEXTTYPETRAIT_H
