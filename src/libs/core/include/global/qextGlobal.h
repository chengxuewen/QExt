#ifndef _QEXTGLOBAL_H
#define _QEXTGLOBAL_H

#include <qextConfig.h>
#include <qextCompiler.h>

#include <QtGlobal>

/********************************************************************************
    QEXT compiler dll visibility macro declare
********************************************************************************/
#if !defined(Q_DECL_EXPORT)
    #if defined(QEXT_CC_GNU) && (QEXT_CC_GNU > 400)
        #define QEXT_DECL_EXPORT __attribute__((visibility("default")))
        #define QEXT_DECL_IMPORT __attribute__((visibility("default")))
        #define QEXT_DECL_HIDDEN __attribute__((visibility("hidden")))
    #elif defined(QEXT_CC_MINGW) || defined(QEXT_CC_MSVC)
        #define QEXT_DECL_EXPORT __declspec(dllexport)
        #define QEXT_DECL_IMPORT __declspec(dllimport)
        #define QEXT_DECL_HIDDEN
    #elif defined(QEXT_CC_CLANG)
        #define QEXT_DECL_EXPORT __attribute__((visibility("default")))
        #define QEXT_DECL_IMPORT __attribute__((visibility("default")))
        #define QEXT_DECL_HIDDEN __attribute__((visibility("hidden")))
    #endif
#else
    #define QEXT_DECL_EXPORT Q_DECL_EXPORT
    #define QEXT_DECL_IMPORT Q_DECL_IMPORT
    #define QEXT_DECL_HIDDEN Q_DECL_HIDDEN
#endif

#ifndef QEXT_DECL_EXPORT
    #define QEXT_DECL_EXPORT
#endif
#ifndef QEXT_DECL_IMPORT
    #define QEXT_DECL_IMPORT
#endif
#ifndef QEXT_DECL_HIDDEN
    #define QEXT_DECL_HIDDEN
#endif


/********************************************************************************
    QEXT compiler CXX11 feature macro declare
********************************************************************************/
#if QEXT_CC_FEATURE_NULLPTR
    #define QEXT_DECL_NULLPTR nullptr
#else
    #define QEXT_DECL_NULLPTR NULL
#endif

#if QEXT_CC_FEATURE_CONSTEXPR
    #define QEXT_DECL_CONSTEXPR constexpr
    #define QEXT_DECL_RELAXED_CONSTEXPR constexpr
#else
    #define QEXT_DECL_CONSTEXPR
    #define QEXT_DECL_RELAXED_CONSTEXPR const
#endif

#if QEXT_CC_FEATURE_EXPLICIT_OVERRIDES
    #define QEXT_DECL_OVERRIDE override
    #define QEXT_DECL_FINAL final
#else
    #define QEXT_DECL_OVERRIDE
    #define QEXT_DECL_FINAL
#endif

#if QEXT_CC_FEATURE_EXPLICIT_OVERRIDES
    #define QEXT_DECL_OVERRIDE override
    #define QEXT_DECL_FINAL final
#else
    #define QEXT_DECL_OVERRIDE
    #define QEXT_DECL_FINAL
#endif

#if QEXT_CC_FEATURE_NOEXCEPT
    #define QEXT_DECL_NOEXCEPT noexcept
    #define QEXT_DECL_NOEXCEPT_EXPR(x) noexcept(x)
#else
    #define QEXT_DECL_NOEXCEPT
    #define QEXT_DECL_NOEXCEPT_EXPR(x)
#endif
#define QEXT_DECL_NOTHROW QEXT_DECL_NOEXCEPT

#if QEXT_CC_FEATURE_DEFAULT_MEMBERS
    #define QEXT_DECL_EQ_DEFAULT = default
    #define QEXT_DECL_EQ_DEFAULT_FUNC = default;
#else
    #define QEXT_DECL_EQ_DEFAULT
    #define QEXT_DECL_EQ_DEFAULT_FUNC {}
#endif

#if QEXT_CC_FEATURE_DELETE_MEMBERS
    #define QEXT_DECL_EQ_DELETE = delete
    #define QEXT_DECL_EQ_DELETE_FUNC = delete;
#else
    #define QEXT_DECL_EQ_DELETE
    #define QEXT_DECL_EQ_DELETE_FUNC {}
#endif

#if QEXT_CC_FEATURE_ALIGNOF
    #define QEXT_DECL_ALIGNOF(x)  alignof(x)
#else
    #define QEXT_DECL_ALIGNOF(x)
#endif

#if QEXT_CC_FEATURE_ALIGNAS
    #define QEXT_DECL_ALIGN(n)   alignas(n)
#else
    #define QEXT_DECL_ALIGN(n)
#endif





/********************************************************************************
    QEXT disable copy move macro declare
********************************************************************************/
// disable copy macro define
#define QEXT_DECL_DISABLE_COPY(Class)               \
    Class(const Class &) QEXT_DECL_EQ_DELETE;       \
    Class &operator=(const Class &) QEXT_DECL_EQ_DELETE;

// disable move macro define
#if QEXT_CC_FEATURE_RVALUE_REFS
#   define QEXT_DECL_DISABLE_MOVE(Class)   \
    Class(Class &&) QEXT_DECL_EQ_DELETE;   \
    Class &operator=(Class &&) QEXT_DECL_EQ_DELETE;
#else
#   define QEXT_DECL_DISABLE_MOVE(Class)
#endif

// disable copy move macro define
#define QEXT_DECL_DISABLE_COPY_MOVE(Class) \
    QEXT_DECL_DISABLE_COPY(Class)          \
    QEXT_DECL_DISABLE_MOVE(Class)



/********************************************************************************
    QEXT force inline macro declare
********************************************************************************/
#if defined(QEXT_CC_MSVC)
    #define QEXT_DECL_ALWAYS_INLINE   __forceinline
    #define QEXT_DECL_FORCE_INLINE    __forceinline
    #define QEXT_DECL_NEVER_INLINE    __declspec(noinline)
#elif defined(QEXT_CC_GNU)
    #define QEXT_DECL_FORCE_INLINE    inline __attribute__((always_inline))
    #define QEXT_DECL_ALWAYS_INLINE   inline __attribute__((always_inline))
    #define QEXT_DECL_NEVER_INLINE    __attribute__((noinline))
#elif defined(QEXT_CC_CLANG)
    #define QEXT_DECL_FORCE_INLINE    inline __attribute__((always_inline))
    #define QEXT_DECL_ALWAYS_INLINE   inline __attribute__((always_inline))
    #define QEXT_DECL_NEVER_INLINE
#else
    #define QEXT_DECL_FORCE_INLINE    inline // no force inline for other platforms possible
    #define QEXT_DECL_ALWAYS_INLINE   inline
    #define QEXT_DECL_NEVER_INLINE
#endif



/********************************************************************************
    QEXT unused macro declare
********************************************************************************/
#if defined(QEXT_CC_GNU) || defined(QEXT_CC_CLANG)
    #define QEXT_DECL_UNUSED  __attribute__((__unused__))
#endif

#ifndef QEXT_DECL_UNUSED
    #define QEXT_DECL_UNUSED
#endif



/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL and declare namespace
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_CORE_LIB    // defined if we are building the lib
        #define QEXT_CORE_API QEXT_DECL_EXPORT
    #else
        #define QEXT_CORE_API Q_DECL_IMPORT
    #endif
    #define QEXT_CORE_HIDDEN QEXT_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_CORE_API
    #define QEXT_CORE_HIDDEN
#endif



/********************************************************************************
   QEXT assert macro
********************************************************************************/
#ifndef QT_ASSERT
    QEXT_CORE_API void qextAssert(const char *assertion, const char *file, int line) QEXT_DECL_NOTHROW;
    inline void qextNoop(void) {}

    #if !defined(QEXT_ASSERT)
        #if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
            #define QEXT_ASSERT(cond)                                                                                                                                        \
                do                                                                                                                                                         \
                {                                                                                                                                                          \
                } while ((false) && (cond))
        #else
            #define QEXT_ASSERT(cond) ((!(cond)) ? qextAssert(#cond, __FILE__, __LINE__) : qextNoop())
        #endif
    #endif

    #if defined(QT_NO_DEBUG) && !defined(QT_PAINT_DEBUG)
        #define QT_NO_PAINT_DEBUG
    #endif

    QEXT_CORE_API void qextAssertX(const char *where, const char *what, const char *file, int line) QEXT_DECL_NOTHROW;

    #if !defined(QEXT_ASSERT_X)
        #if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
            #define QEXT_ASSERT_X(cond, where, what)                                                                                                                         \
                do                                                                                                                                                         \
                {                                                                                                                                                          \
                } while ((false) && (cond))
        #else
            #define QEXT_ASSERT_X(cond, where, what) ((!(cond)) ? qextAssertX(where, what, __FILE__, __LINE__) : qextNoop())
        #endif
    #endif
#else
    #define QEXT_ASSERT(cond) Q_ASSERT(cond)
    #define QEXT_ASSERT_X(cond, where, what) Q_ASSERT(cond, where, what)
#endif


#ifndef Q_STATIC_ASSERT
    #if QEXT_CC_FEATURE_STATIC_ASSERT
        #define QEXT_STATIC_ASSERT(Condition) static_assert(bool(Condition), #Condition)
        #define QEXT_STATIC_ASSERT_X(Condition, Message) static_assert(bool(Condition), Message)
    #else
        // Intentionally undefined
        template < bool Test >
        class QEXTStaticAssertFailure;
        template <>
        class QEXTStaticAssertFailure< true >
        {
        };


        #define QEXT_STATIC_ASSERT_PRIVATE_JOIN(A, B) QEXT_STATIC_ASSERT_PRIVATE_JOIN_IMPL(A, B)
        #define QEXT_STATIC_ASSERT_PRIVATE_JOIN_IMPL(A, B) A##B
        #ifdef __COUNTER__
        #define QEXT_STATIC_ASSERT(Condition)                                                                                                                            \
            enum                                                                                                                                                       \
            {                                                                                                                                                          \
                QEXT_STATIC_ASSERT_PRIVATE_JOIN(qextStaticAssertResult, __COUNTER__) = sizeof(QEXTStaticAssertFailure< !!(Condition) >)                                      \
            }
        #else
        #define QEXT_STATIC_ASSERT(Condition)                                                                                                                            \
            enum                                                                                                                                                       \
            {                                                                                                                                                          \
                QEXT_STATIC_ASSERT_PRIVATE_JOIN(qextStaticAssertResult, __LINE__) = sizeof(QEXTStaticAssertFailure< !!(Condition) >)                                         \
            }
        #endif /* __COUNTER__ */
        #define QEXT_STATIC_ASSERT_X(Condition, Message) QEXT_STATIC_ASSERT(Condition)
    #endif
#else
    #define QEXT_STATIC_ASSERT(Condition) Q_STATIC_ASSERT(Condition)
    #define QEXT_STATIC_ASSERT_X(Condition) Q_STATIC_ASSERT_X(Condition)
#endif


/********************************************************************************
   QEXT version macro
********************************************************************************/
// QEXT_VERSION is (major << 16) + (minor << 8) + patch.
#define QEXT_VERSION QEXT_VERSION_CHECK(QEXT_VERSION_MAJOR, QEXT_VERSION_MINOR, QEXT_VERSION_PATCH)
// can be used like #if (QEXT_VERSION >= QEXT_VERSION_CHECK(0, 3, 1))
#define QEXT_VERSION_CHECK(major, minor, patch) ((major << 16) | (minor << 8) | (patch))


#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    typedef qintptr QEXTSocketDescriptor;
#else
    typedef int QEXTSocketDescriptor;
#endif

struct QEXTNil {};

#define QEXT_ATOMIC_INT_TRUE 1
#define QEXT_ATOMIC_INT_FALSE 0


template<typename T>
T qextClamp(T x, T min, T max)
{
    if (x > max)
    {
        return max;
    }
    if (x < min)
    {
        return min;
    }
    return x;
}

#endif // _QEXTGLOBAL_H
