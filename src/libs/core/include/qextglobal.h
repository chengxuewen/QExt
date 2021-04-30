#ifndef QEXTGLOBAL_H
#define QEXTGLOBAL_H

#include <QtGlobal>
#include "qextconfig.h"


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
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
# ifdef QEXT_BUILD_CORE_LIB // defined if we are building the lib
#  define QEXT_CORE_API Q_DECL_EXPORT
# else
#  define QEXT_CORE_API Q_DECL_IMPORT
# endif
# define QEXT_CORE_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
# define QEXT_CORE_API
# define QEXT_CORE_HIDDEN
#endif



/********************************************************************************
    C++11 keywords and expressions
********************************************************************************/
#ifdef QEXT_CXX_FEATURE_11
# define QEXT_NULLPTR nullptr
# define QEXT_EQ_DEFAULT = default
# define QEXT_EQ_DELETE = delete
# define QEXT_CONSTEXPR constexpr
# define QEXT_RELAXED_CONSTEXPR const
# define QEXT_OVERRIDE override
# define QEXT_FINAL final
# define QEXT_NOEXCEPT noexcept
# define QEXT_NOEXCEPT_EXPR(x) noexcept(x)
#else
# define QEXT_NULLPTR NULL
# define QEXT_EQ_DEFAULT
# define QEXT_EQ_DELETE
# define QEXT_CONSTEXPR
# define QEXT_RELAXED_CONSTEXPR const
# define QEXT_OVERRIDE
# define QEXT_FINAL
# define QEXT_NOEXCEPT
# define QEXT_NOEXCEPT_EXPR(x)
#endif

/*
   Some classes do not permit copies to be made of an object. These
   classes contains a private copy constructor and assignment
   operator to disable copying (the compiler gives an error message).
*/
#define QEXT_DISABLE_COPY(Class) \
    Class(const Class &) QEXT_EQ_DELETE;\
    Class &operator=(const Class &) QEXT_EQ_DELETE;

#ifdef QEXT_CXX_FEATURE_11
# define QEXT_DISABLE_MOVE(Class) \
    Class(Class &&) QEXT_EQ_DELETE; \
    Class &operator=(Class &&) QEXT_EQ_DELETE;
#else
# define QEXT_DISABLE_MOVE(x)
#endif

#define QEXT_DISABLE_COPY_MOVE(Class) \
    QEXT_DISABLE_COPY(Class) \
    QEXT_DISABLE_MOVE(Class)


#define QEXT_DECLARE_PRIVATE(Class) Q_DECLARE_PRIVATE_D(qGetPtrHelper(dd_ptr),Class)
#define QEXT_DECLARE_PUBLIC(Class) Q_DECLARE_PUBLIC(Class)
#define QEXT_D(Class) Q_D(Class)
#define QEXT_Q(Class) Q_Q(Class)
#define QEXT_DC(Class) Q_D(const Class)
#define QEXT_QC(Class) Q_Q(const Class)
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



#endif // QEXTGLOBAL_H
