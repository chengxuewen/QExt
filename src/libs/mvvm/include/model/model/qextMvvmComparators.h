#ifndef _QEXTMVVMMODELCOMPARATORS_H
#define _QEXTMVVMMODELCOMPARATORS_H

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

#endif // _QEXTMVVMMODELCOMPARATORS_H
