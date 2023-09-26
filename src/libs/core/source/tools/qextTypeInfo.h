#ifndef _QEXTTYPEINFO_H
#define _QEXTTYPEINFO_H

#include <qextGlobal.h>
#include <qextTypeTrait.h>


/**
 * \brief type trait functionality
 * catch-all template.
 */
template < typename T_type >
class QEXTTypeInfo
{
public:
    enum
    {
        isPointer = false,
        isIntegral = QEXTTypeIsIntegral< T_type >::value,
        isComplex = true,
        isStatic = true,
        isRelocatable = QEXT_IS_ENUM(T_type),
        isLarge = (sizeof(T_type) > sizeof(void *)),
        isDummy = false, //### Qt6: remove
        sizeOf = sizeof(T_type)
    };
};

template <>
class QEXTTypeInfo< void >
{
public:
    enum
    {
        isPointer = false,
        isIntegral = false,
        isComplex = false,
        isStatic = false,
        isRelocatable = false,
        isLarge = false,
        isDummy = false,
        sizeOf = 0
    };
};

template < typename T_type >
class QEXTTypeInfo< T_type * >
{
public:
    enum
    {
        isPointer = true,
        isIntegral = false,
        isComplex = false,
        isStatic = false,
        isRelocatable = true,
        isLarge = false,
        isDummy = false,
        sizeOf = sizeof(T_type *)
    };
};

/*!
    \class QEXTTypeInfoQuery
    \inmodule QEXTCore
    \internal
    \brief QEXTTypeInfoQuery is used to query the values of a given QEXTTypeInfo<T_type>

    We use it because there may be some QEXTTypeInfo<T_type> specializations in user
    code that don't provide certain flags that we added after Qt 5.0. They are:
    \list
      \li isRelocatable: defaults to !isStatic
    \endlist

    DO NOT specialize this class elsewhere.
*/
// apply defaults for a generic QEXTTypeInfo<T_type> that didn't provide the new values
template < typename T_type, typename = void >
struct QEXTTypeInfoQuery : public QEXTTypeInfo< T_type >
{
    enum
    {
        isRelocatable = !QEXTTypeInfo< T_type >::isStatic
    };
};

// if QEXTTypeInfo<T_type>::isRelocatable exists, use it
template < typename T_type >
struct QEXTTypeInfoQuery< T_type, typename QEXTTypeEnableIf< QEXTTypeInfo< T_type >::isRelocatable || true >::Type > : public QEXTTypeInfo< T_type >
{
};

/*!
    \class QEXTTypeInfoMerger
    \inmodule QEXTCore

    \brief QEXTTypeInfoMerger merges the QEXTTypeInfo flags of T1, T2... and presents them
    as a QEXTTypeInfo<T_type> would do.

    Let's assume that we have a simple set of structs:

    \snippet code/src_corelib_global_qglobal.cpp 50

    To create a proper QEXTTypeInfo specialization for A struct, we have to check
    all sub-components; B, C and D, then take the lowest common denominator and call
    QEXT_DECL_TYPEINFO with the resulting flags. An easier and less fragile approach is to
    use QEXTTypeInfoMerger, which does that automatically. So struct A would have
    the following QEXTTypeInfo definition:

    \snippet code/src_corelib_global_qglobal.cpp 51
*/
template < typename T_type, typename T1, typename T2 = T1, typename T3 = T1, typename T4 = T1 >
class QEXTTypeInfoMerger
{
public:
    enum
    {
        isComplex
        = QEXTTypeInfoQuery< T1 >::isComplex || QEXTTypeInfoQuery< T2 >::isComplex || QEXTTypeInfoQuery< T3 >::isComplex || QEXTTypeInfoQuery< T4 >::isComplex,
        isStatic = QEXTTypeInfoQuery< T1 >::isStatic || QEXTTypeInfoQuery< T2 >::isStatic || QEXTTypeInfoQuery< T3 >::isStatic || QEXTTypeInfoQuery< T4 >::isStatic,
        isRelocatable = QEXTTypeInfoQuery< T1 >::isRelocatable && QEXTTypeInfoQuery< T2 >::isRelocatable && QEXTTypeInfoQuery< T3 >::isRelocatable
                        && QEXTTypeInfoQuery< T4 >::isRelocatable,
        isLarge = sizeof(T_type) > sizeof(void *),
        isPointer = false,
        isIntegral = false,
        isDummy = false,
        sizeOf = sizeof(T_type)
    };
};

#define QEXT_DECL_MOVABLE_CONTAINER(CONTAINER)                                                                                                                   \
    template < typename T_type >                                                                                                                               \
    class CONTAINER;                                                                                                                                           \
    template < typename T_type >                                                                                                                               \
    class QEXTTypeInfo< CONTAINER< T_type > >                                                                                                                    \
    {                                                                                                                                                          \
    public:                                                                                                                                                    \
        enum                                                                                                                                                   \
        {                                                                                                                                                      \
            isPointer = false,                                                                                                                                 \
            isIntegral = false,                                                                                                                                \
            isComplex = true,                                                                                                                                  \
            isRelocatable = true,                                                                                                                              \
            isStatic = false,                                                                                                                                  \
            isLarge = (sizeof(CONTAINER< T_type >) > sizeof(void *)),                                                                                          \
            isDummy = false,                                                                                                                                   \
            sizeOf = sizeof(CONTAINER< T_type >)                                                                                                               \
        };                                                                                                                                                     \
    }
#undef QEXT_DECL_MOVABLE_CONTAINER

/*
   Specialize a specific type with:

     QEXT_DECL_TYPEINFO(type, flags);

   where 'type' is the name of the type to specialize and 'flags' is
   logically-OR'ed combination of the flags below.
*/
enum QEXT_TYPEINFO_FLAGS /* TYPEINFO flags */
{
    QEXT_TYPEINFO_COMPLEX = 0,
    QEXT_TYPEINFO_PRIMITIVE = 0x1,
    QEXT_TYPEINFO_STATIC = 0,
    QEXT_TYPEINFO_MOVABLE = 0x2,
    QEXT_TYPEINFO_DUMMY = 0x4,
    QEXT_TYPEINFO_RELOCATABLE = 0x8
};

#define QEXT_DECL_TYPEINFO_BODY(TYPE, FLAGS)                                                   \
    class QEXTTypeInfo< TYPE >                                                                 \
    {                                                                                        \
    public:                                                                                  \
        enum                                                                                 \
        {                                                                                    \
            isComplex = (((FLAGS)&QEXT_TYPEINFO_PRIMITIVE) == 0),                              \
            isStatic = (((FLAGS) & (QEXT_TYPEINFO_MOVABLE | QEXT_TYPEINFO_PRIMITIVE)) == 0),     \
            isRelocatable = !isStatic || ((FLAGS)&QEXT_TYPEINFO_RELOCATABLE),                  \
            isLarge = (sizeof(TYPE) > sizeof(void *)),                                       \
            isPointer = false,                                                               \
            isIntegral = QEXTTypeIsIntegral< TYPE >::value,                                    \
            isDummy = (((FLAGS)&QEXT_TYPEINFO_DUMMY) != 0),                                    \
            sizeOf = sizeof(TYPE)                                                            \
        };                                                                                   \
        static inline const char *name()                                                     \
        {                                                                                    \
            return #TYPE;                                                                    \
        }                                                                                    \
    }

#define QEXT_DECL_TYPEINFO(TYPE, FLAGS)                                                        \
    template <>                                                                              \
    QEXT_DECL_TYPEINFO_BODY(TYPE, FLAGS)

/* Specialize QEXTTypeInfo for TestClass<T_type> */
template < typename T_type >
class TestClass;
template < typename T_type >
QEXT_DECL_TYPEINFO_BODY(TestClass< T_type >, QEXT_TYPEINFO_PRIMITIVE);

/*
   Specialize a shared type with:

     QEXT_DECL_SHARED(type)

   where 'type' is the name of the type to specialize.  NOTE: shared
   types must define a member-swap, and be defined in the same
   namespace as Qt for this to work.

   If the type was already released without QEXT_DECL_SHARED applied,
   _and_ without an explicit QEXT_DECL_TYPEINFO(type, QEXT_TYPEINFO_MOVABLE),
   then use QEXT_DECL_SHARED_NOT_MOVABLE_UNTIL_QT6(type) to mark the
   type shared (incl. swap()), without marking it movable (which
   would change the memory layout of QList, a BiC change.
*/

#define QEXT_DECL_SHARED_IMPL(TYPE, FLAGS)                                                                    \
    QEXT_DECL_TYPEINFO(TYPE, FLAGS);                                                                          \
    inline void swap(TYPE &value1, TYPE &value2) QEXT_DECL_NOEXCEPT_EXPR(noexcept(value1.swap(value2)))       \
    {                                                                                                       \
        value1.swap(value2);                                                                                \
    }
#define QEXT_DECL_SHARED(TYPE) QEXT_DECL_SHARED_IMPL(TYPE, QEXT_TYPEINFO_MOVABLE)

/*
   QEXTTypeInfo primitive specializations
*/
QEXT_DECL_TYPEINFO(bool, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(char, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(signed char, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(unsigned char, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(short, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(unsigned short, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(int, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(unsigned int, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(long, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(unsigned long, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(qint64, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(quint64, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(float, QEXT_TYPEINFO_PRIMITIVE);
QEXT_DECL_TYPEINFO(double, QEXT_TYPEINFO_PRIMITIVE);
#ifndef _QEXT_OS_DARWIN
QEXT_DECL_TYPEINFO(long double, QEXT_TYPEINFO_PRIMITIVE);
#endif



#endif // _QEXTTYPEINFO_H
