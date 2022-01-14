#ifndef _QEXTMVVMGLOBAL_H
#define _QEXTMVVMGLOBAL_H

#include <qextGlobal.h>

#include <QVariant>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_MVVM_LIB // defined if we are building the lib
        #define QEXT_MVVM_API Q_DECL_EXPORT
    #else
        #define QEXT_MVVM_API Q_DECL_IMPORT
    #endif
    #define QEXT_MVVM_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_MVVM_API
    #define QEXT_MVVM_HIDDEN
#endif

#include <memory>

template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

template<typename T>
inline T clamp(T x, T min, T max)
{
    return std::max(std::min(x, max), min);
}

#endif // _QEXTMVVMGLOBAL_H
