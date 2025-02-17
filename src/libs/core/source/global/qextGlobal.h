/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTGLOBAL_H
#define _QEXTGLOBAL_H

#include <qextCompiler.h>
#include <qextCoreConfig.h>

#include <QObject>
#include <QVariant>
#include <QtGlobal>

/***********************************************************************************************************************
 *   QExt compiler dll visibility macro declare
***********************************************************************************************************************/
#if !defined(Q_DECL_EXPORT)
#   if defined(QEXT_CC_GNU) && (QEXT_CC_GNU > 400)
#       define QEXT_DECL_EXPORT __attribute__((visibility("default")))
#       define QEXT_DECL_IMPORT __attribute__((visibility("default")))
#       define QEXT_DECL_HIDDEN __attribute__((visibility("hidden")))
#   elif defined(QEXT_CC_MINGW) || defined(QEXT_CC_MSVC)
#       define QEXT_DECL_EXPORT __declspec(dllexport)
#       define QEXT_DECL_IMPORT __declspec(dllimport)
#       define QEXT_DECL_HIDDEN
#   elif defined(QEXT_CC_CLANG)
#       define QEXT_DECL_EXPORT __attribute__((visibility("default")))
#       define QEXT_DECL_IMPORT __attribute__((visibility("default")))
#       define QEXT_DECL_HIDDEN __attribute__((visibility("hidden")))
#   endif
#else
#   define QEXT_DECL_EXPORT Q_DECL_EXPORT
#   define QEXT_DECL_IMPORT Q_DECL_IMPORT
#   define QEXT_DECL_HIDDEN Q_DECL_HIDDEN
#endif

#ifndef QEXT_DECL_EXPORT
#   define QEXT_DECL_EXPORT
#endif
#ifndef QEXT_DECL_IMPORT
#   define QEXT_DECL_IMPORT
#endif
#ifndef QEXT_DECL_HIDDEN
#   define QEXT_DECL_HIDDEN
#endif


/***********************************************************************************************************************
    QExt compiler CXX11 feature macro declare
***********************************************************************************************************************/
#if QEXT_CC_FEATURE_NULLPTR
#   define QEXT_NULLPTR nullptr
#else
#   define QEXT_NULLPTR NULL
#endif

#if QEXT_CC_FEATURE_CONSTEXPR
#   define QEXT_CONSTEXPR constexpr
#   define QEXT_RELAXED_CONSTEXPR constexpr
#   define QEXT_STATIC_CONSTANT(type, assignment) static constexpr type assignment
#else
#   define QEXT_CONSTEXPR
#   define QEXT_RELAXED_CONSTEXPR const
#   define QEXT_STATIC_CONSTANT(type, assignment) enum { assignment }
#endif

#if QEXT_CC_FEATURE_EXPLICIT_OVERRIDES
#   define QEXT_OVERRIDE override
#   define QEXT_FINAL final
#else
#   define QEXT_OVERRIDE
#   define QEXT_FINAL
#endif

#if QEXT_CC_FEATURE_NOEXCEPT
#   define QEXT_NOEXCEPT noexcept
#   define QEXT_NOEXCEPT_EXPR(x) noexcept(x)
#else
#   define QEXT_NOEXCEPT
#   define QEXT_NOEXCEPT_EXPR(x)
#endif
#define QEXT_NOTHROW QEXT_NOEXCEPT

#if QEXT_CC_FEATURE_DEFAULT_MEMBERS
#   define QEXT_EQ_DEFAULT = default
#   define QEXT_EQ_DEFAULT_FUNC = default;
#else
#   define QEXT_EQ_DEFAULT
#   define QEXT_EQ_DEFAULT_FUNC {}
#endif

#if QEXT_CC_FEATURE_DELETE_MEMBERS
#   define QEXT_EQ_DELETE = delete
#   define QEXT_EQ_DELETE_FUNC = delete;
#else
#   define QEXT_EQ_DELETE
#   define QEXT_EQ_DELETE_FUNC {}
#endif

#if QEXT_CC_FEATURE_ALIGNOF
#   define QEXT_ALIGNOF(x)  alignof(x)
#else
#   define QEXT_ALIGNOF(x)
#endif

#if QEXT_CC_FEATURE_ALIGNAS
#   define QEXT_ALIGN(n)   alignas(n)
#else
#   define QEXT_ALIGN(n)
#endif

#if QEXT_CC_FEATURE_VARIADIC_TEMPLATES
#   if QEXT_FEATURE_ENABLE_VARIADIC_TEMPLATES
#       define QEXT_USE_VARIADIC_TEMPLATES 1
#   endif
#endif
#ifndef QEXT_USE_VARIADIC_TEMPLATES
#   define QEXT_USE_VARIADIC_TEMPLATES 0
#endif


/***********************************************************************************************************************
    QExt disable copy move macro declare
***********************************************************************************************************************/
// disable copy macro define
#define QEXT_DECL_DISABLE_COPY(Class) \
    Class(const Class &) QEXT_EQ_DELETE; \
    Class &operator=(const Class &) QEXT_EQ_DELETE;

// disable move macro define
#if QEXT_CC_FEATURE_RVALUE_REFS
#   define QEXT_DECL_DISABLE_MOVE(Class) \
    Class(Class &&) QEXT_EQ_DELETE; \
    Class &operator=(Class &&) QEXT_EQ_DELETE;
#else
#   define QEXT_DECL_DISABLE_MOVE(Class)
#endif

// disable copy move macro define
#define QEXT_DISABLE_COPY_MOVE(Class) \
    QEXT_DECL_DISABLE_COPY(Class) \
    QEXT_DECL_DISABLE_MOVE(Class)


template <typename T> inline T *qextGetPtrHelper(T *ptr) { return ptr; }
template <typename Wrapper> static inline typename Wrapper::pointer qextGetPtrHelper(const Wrapper &p) { return p.data(); }

// The body must be a statement:
#define QEXT_CAST_IGNORE_ALIGN(body) QEXT_WARNING_PUSH QEXT_WARNING_DISABLE_GCC("-Wcast-align") body QEXT_WARNING_POP
#define QEXT_DECL_PRIVATE(Class) \
    inline Class##Private *d_func() \
    { QEXT_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private *>(qextGetPtrHelper(d_ptr));) } \
    inline const Class##Private *d_func() const \
    { QEXT_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private *>(qextGetPtrHelper(d_ptr));) } \
    friend class Class##Private;

#define QEXT_DECL_PRIVATE_D(Dptr, Class) \
    inline Class##Private *d_func() \
    { QEXT_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private *>(qextGetPtrHelper(Dptr));) } \
    inline const Class##Private *d_func() const \
    { QEXT_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private *>(qextGetPtrHelper(Dptr));) } \
    friend class Class##Private;

#define QEXT_DECL_PUBLIC(Class) \
    inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class;


#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
#   define QEXT_DECL_UNSETENV(env) qunsetenv(env)
#else
#   define QEXT_DECL_UNSETENV(env)
#endif


template<typename T>
inline T qextFindChild(const QObject *o, const QString &name = QString())
{
    return o->findChild<T>(name);
}

template<typename T>
inline QList<T> qextFindChildren(const QObject *o, const QString &name = QString())
{
    return o->findChildren<T>(name);
}

template<typename T>
inline T qextVariantValue(const QVariant &variant)
{
    return qvariant_cast<T>(variant);
}

template<typename T>
inline bool qextVariantCanConvert(const QVariant &variant)
{
    return variant.template canConvert<T>();
}

//TODO
template<typename T>
inline void qextMetaEnum(const QVariant &variant)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))

#else

#endif
}



/***********************************************************************************************************************
    QExt force inline macro declare
***********************************************************************************************************************/
#if defined(QEXT_CC_MSVC)
#   define QEXT_ATTR_ALWAYS_INLINE   __forceinline
#   define QEXT_ATTR_FORCE_INLINE    __forceinline
#   define QEXT_ATTR_NEVER_INLINE    __declspec(noinline)
#   define QEXT_ATTR_USED
#elif defined(QEXT_CC_GNU)
#   define QEXT_ATTR_FORCE_INLINE    inline __attribute__((always_inline))
#   define QEXT_ATTR_ALWAYS_INLINE   inline __attribute__((always_inline))
#   define QEXT_ATTR_NEVER_INLINE    __attribute__((noinline))
#   define QEXT_ATTR_USED           __attribute__((used))
#elif defined(QEXT_CC_CLANG)
#   define QEXT_ATTR_FORCE_INLINE    inline __attribute__((always_inline))
#   define QEXT_ATTR_ALWAYS_INLINE   inline __attribute__((always_inline))
#   define QEXT_ATTR_NEVER_INLINE
#   define QEXT_ATTR_USED           __attribute__((used))
#else
#   define QEXT_ATTR_FORCE_INLINE    inline // no force inline for other platforms possible
#   define QEXT_ATTR_ALWAYS_INLINE   inline
#   define QEXT_ATTR_NEVER_INLINE
#   define QEXT_ATTR_USED
#endif


/***********************************************************************************************************************
    QExt unused macro declare
***********************************************************************************************************************/
#if defined(QEXT_CC_GNU) || defined(QEXT_CC_CLANG)
#   define QEXT_DECL_UNUSED  __attribute__((__unused__))
#endif

#ifndef QEXT_DECL_UNUSED
#   define QEXT_DECL_UNUSED
#endif


/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL and declare namespace
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_CORE_LIB    // defined if we are building the lib
#       define QEXT_CORE_API QEXT_DECL_EXPORT
#   else
#       define QEXT_CORE_API Q_DECL_IMPORT
#   endif
#   define QEXT_CORE_HIDDEN QEXT_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_CORE_API
#   define QEXT_CORE_HIDDEN
#endif


/***********************************************************************************************************************
   QExt assert macro
***********************************************************************************************************************/
#ifndef QT_ASSERT
QEXT_CORE_API void qextAssert(const char *assertion, const char *file, int line) QEXT_NOTHROW;
inline void qextNoop(void) {}
#   if !defined(QEXT_ASSERT)
#       if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
#           define QEXT_ASSERT(cond)  do { } while ((false) && (cond))
#       else
#           define QEXT_ASSERT(cond) ((!(cond)) ? qextAssert(#cond, __FILE__, __LINE__) : qextNoop())
#       endif
#   endif
#   if defined(QT_NO_DEBUG) && !defined(QT_PAINT_DEBUG)
#       define QT_NO_PAINT_DEBUG
#   endif
    QEXT_CORE_API void qextAssertX(const char *where, const char *what, const char *file, int line) QEXT_NOTHROW;
#   if !defined(QEXT_ASSERT_X)
#       if defined(QT_NO_DEBUG) && !defined(QT_FORCE_ASSERTS)
#           define QEXT_ASSERT_X(cond, where, what) do { } while ((false) && (cond))
#       else
#           define QEXT_ASSERT_X(cond, where, what) ((!(cond)) ? qextAssertX(where, what, __FILE__, __LINE__) : qextNoop())
#       endif
#   endif
#else
#   define QEXT_ASSERT(cond) Q_ASSERT(cond)
#   define QEXT_ASSERT_X(cond, where, what) Q_ASSERT(cond, where, what)
#endif

#ifndef Q_STATIC_ASSERT
#   if QEXT_CC_FEATURE_STATIC_ASSERT
#       define QEXT_STATIC_ASSERT(Condition) static_assert(bool(Condition), #Condition)
#       define QEXT_STATIC_ASSERT_X(Condition, Message) static_assert(bool(Condition), Message)
#   else
// Intentionally undefined
template < bool Test > class QEXTStaticAssertFailure;
template <> class QEXTStaticAssertFailure< true > { };
#       define QEXT_STATIC_ASSERT_PRIVATE_JOIN(A, B) QEXT_STATIC_ASSERT_PRIVATE_JOIN_IMPL(A, B)
#       define QEXT_STATIC_ASSERT_PRIVATE_JOIN_IMPL(A, B) A##B
#       ifdef __COUNTER__
#           define QEXT_STATIC_ASSERT(Condition) \
            enum { QEXT_STATIC_ASSERT_PRIVATE_JOIN(qextStaticAssertResult, __COUNTER__) = sizeof(QEXTStaticAssertFailure< !!(Condition) >) }
#       else
#           define QEXT_STATIC_ASSERT(Condition) \
            enum { QEXT_STATIC_ASSERT_PRIVATE_JOIN(qextStaticAssertResult, __LINE__) = sizeof(QEXTStaticAssertFailure< !!(Condition) >) }
#       endif /* __COUNTER__ */
#       define QEXT_STATIC_ASSERT_X(Condition, Message) QEXT_STATIC_ASSERT(Condition)
#   endif
#else
#   define QEXT_STATIC_ASSERT(Condition) Q_STATIC_ASSERT(Condition)
#   define QEXT_STATIC_ASSERT_X(Condition, Message) Q_STATIC_ASSERT_X(Condition, Message)
#endif


/***********************************************************************************************************************
   QExt version macro
***********************************************************************************************************************/
// QEXT_VERSION is (major << 16) + (minor << 8) + patch.
#define QEXT_VERSION QEXT_VERSION_CHECK(QEXT_VERSION_MAJOR, QEXT_VERSION_MINOR, QEXT_VERSION_PATCH)
// can be used like #if (QEXT_VERSION >= QEXT_VERSION_CHECK(0, 3, 1))
#define QEXT_VERSION_CHECK(major, minor, patch) ((major << 16) | (minor << 8) | (patch))


#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
typedef qintptr QExtSocketDescriptor;
#else
typedef int QExtSocketDescriptor;
#endif

struct QExtNil {};

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

#ifdef QEXT_OS_WIN
#   define QEXT_DIR_SPLIT "\\"
#else
#   define QEXT_DIR_SPLIT "/"
#endif


/***********************************************************************************************************************
Provide a string identifying the current function, non-concatenatable macro
***********************************************************************************************************************/
#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#   define QEXT_STRFUNC     ((const char*) (__func__))
#elif defined (__GNUC__) && defined (__cplusplus)
#   define QEXT_STRFUNC     ((const char*) (__PRETTY_FUNCTION__))
#elif defined (__GNUC__) || (defined(_MSC_VER) && (_MSC_VER > 1300))
#   define QEXT_STRFUNC     ((const char*) (__FUNCTION__))
#else
#   define QEXT_STRFUNC     ((const char*) ("???"))
#endif


#endif // _QEXTGLOBAL_H
