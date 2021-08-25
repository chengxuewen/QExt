// clang-format off
#ifndef QEXTGLOBAL_H
#define QEXTGLOBAL_H

#include "qextconfig.h"
#include <QtGlobal>

/********************************************************************************
   QEXT force inline macro define
********************************************************************************/
#if defined(QEXT_CXX_COMPILER_MSVC)
#define QEXT_FORCE_INLINE __forceinline
#elif defined(QEXT_CXX_COMPILER_GNU)
#define QEXT_FORCE_INLINE inline __attribute__((always_inline))
#elif defined(QEXT_CXX_COMPILER_CLANG)
#define QEXT_FORCE_INLINE inline __attribute__((always_inline))
#else
#define QEXT_FORCE_INLINE inline // no force inline for other platforms possible
#endif

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL and declare namespace
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
#ifdef QEXT_BUILD_CORE_LIB    // defined if we are building the lib
#define QEXT_CORE_API Q_DECL_EXPORT
#else
#define QEXT_CORE_API Q_DECL_IMPORT
#endif
#define QEXT_CORE_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#define QEXT_CORE_API
#define QEXT_CORE_HIDDEN
#endif

/********************************************************************************
    C++11 keywords and expressions
********************************************************************************/
#ifdef QEXT_CXX_STANDARD_11
#define QEXT_DECL_NULLPTR nullptr
#define QEXT_DECL_EQ_DEFAULT = default
#define QEXT_DECL_EQ_DELETE = delete
#define QEXT_DECL_CONSTEXPR constexpr
#define QEXT_DECL_RELAXED_CONSTEXPR const
#define QEXT_DECL_OVERRIDE override
#define QEXT_DECL_FINAL final
#define QEXT_DECL_NOEXCEPT noexcept
#define QEXT_DECL_NOEXCEPT_EXPR(x) noexcept(x)
#else
#define QEXT_DECL_NULLPTR NULL
#define QEXT_DECL_EQ_DEFAULT
#define QEXT_DECL_EQ_DELETE
#define QEXT_DECL_CONSTEXPR
#define QEXT_DECL_RELAXED_CONSTEXPR const
#define QEXT_DECL_OVERRIDE
#define QEXT_DECL_FINAL
#define QEXT_DECL_NOEXCEPT
#define QEXT_DECL_NOEXCEPT_EXPR(x)
#endif

/*
   Some classes do not permit copies to be made of an object. These
   classes contains a private copy constructor and assignment
   operator to disable copying (the compiler gives an error message).
*/
#define QEXT_DISABLE_COPY(Class)                                                                                                                               \
    Class(const Class &) QEXT_DECL_EQ_DELETE;                                                                                                                       \
    Class &operator=(const Class &) QEXT_DECL_EQ_DELETE;

#ifdef QEXT_CXX_STANDARD_11
#define QEXT_DISABLE_MOVE(Class)                                                                                                                               \
    Class(Class &&) QEXT_DECL_EQ_DELETE;                                                                                                                            \
    Class &operator=(Class &&) QEXT_DECL_EQ_DELETE;
#else
#define QEXT_DISABLE_MOVE(x)
#endif

#define QEXT_DISABLE_COPY_MOVE(Class)                                                                                                                          \
    QEXT_DISABLE_COPY(Class)                                                                                                                                   \
    QEXT_DISABLE_MOVE(Class)


/********************************************************************************
 * class private implementation macro
********************************************************************************/
template<typename T>
static inline T *qextGetPtrHelper(T *ptr)
{
    return ptr;
}
template<typename Wrapper>
static inline typename Wrapper::pointer qextGetPtrHelper(const Wrapper &p)
{
    return p.get();
}

#define QEXT_DECL_PRIVATE(Class)                                                                                                    \
    inline Class##Private *d_func() { return reinterpret_cast<Class##Private *>(qextGetPtrHelper(d_objPtr)); }                      \
    inline const Class##Private *d_func() const { return reinterpret_cast<const Class##Private *>(qextGetPtrHelper(d_objPtr)); }    \
    friend class Class##Private;

#define QEXT_DECL_PRIVATE_D(Dptr, Class)                                                                    \
    inline Class##Private *d_func() { return reinterpret_cast<Class##Private *>(Dptr); }                    \
    inline const Class##Private *d_func() const { return reinterpret_cast<const Class##Private *>(Dptr); }  \
    friend class Class##Private;

#define QEXT_DECL_PUBLIC(Class)                                                             \
    inline Class *q_func() { return static_cast<Class *>(q_objPtr); }                       \
    inline const Class *q_func() const { return static_cast<const Class *>(q_objPtr); }     \
    friend class Class;

#define QEXT_DECL_D(Class) Class##Private *const d = d_func();
#define QEXT_DECL_Q(Class) Class *const q = q_func();
#define QEXT_DECL_DC(Class) QEXT_DECL_D(const Class)
#define QEXT_DECL_QC(Class) QEXT_DECL_Q(const Class)
#define QEXT_PRIVATE_SLOT(Func) Q_PRIVATE_SLOT(d_func(), Func)


#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
typedef qintptr QEXTSocketDescriptor;
#else
typedef int QEXTSocketDescriptor;
#endif

/********************************************************************************
   QEXT version macro
********************************************************************************/
// QEXT_VERSION is (major << 16) + (minor << 8) + patch.
#define QEXT_VERSION QEXT_VERSION_CHECK(QEXT_VERSION_MAJOR, QEXT_VERSION_MINOR, QEXT_VERSION_PATCH)
// can be used like #if (QEXT_VERSION >= QEXT_VERSION_CHECK(0, 3, 1))
#define QEXT_VERSION_CHECK(major, minor, patch) ((major << 16) | (minor << 8) | (patch))

/********************************************************************************
   QEXT nil struct type.
   The nil struct type is used as default template argument in the templates.
********************************************************************************/
struct QEXTNil
{
};

#endif // QEXTGLOBAL_H

// clang-format on
