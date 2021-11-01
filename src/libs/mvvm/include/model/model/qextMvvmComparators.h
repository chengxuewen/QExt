#ifndef _QEXTMVVMCOMPARATORS_H
#define _QEXTMVVMCOMPARATORS_H

#include <qextMvvmGlobal.h>

namespace ModelView
{

//! Helper class to register variant comparators.

class QEXT_MVVM_API QEXTMvvmComparators
{
public:
    static void registerComparators();
    static bool registered();

private:
    static bool m_is_registered;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMPARATORS_H
