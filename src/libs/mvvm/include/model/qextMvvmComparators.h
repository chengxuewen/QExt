#ifndef _QEXTMVVMCOMPARATORS_H
#define _QEXTMVVMCOMPARATORS_H

#include <qextMvvmGlobal.h>


//! Helper class to register variant comparators.

class QEXT_MVVM_API QEXTMvvmComparators
{
public:
    static void registerComparators();
    static bool registered();

private:
    static bool m_isRegistered;
};


#endif // _QEXTMVVMCOMPARATORS_H
