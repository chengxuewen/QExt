#ifndef _QEXTMVVMUNIQUEIDGENERATOR_H
#define _QEXTMVVMUNIQUEIDGENERATOR_H

#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

/*!
@class QEXTMvvmUniqueIdGenerator
@brief Provides generation of unique QEXTMvvmItem itentifier.

In the future might be turned to singleton to keep track of all generated identifier
and make sure, that QEXTMvvmItem identifiers loaded from disk, are different from those
generated during dynamic session. For the moment though, we rely on zero-probability of
such event.
*/

class QEXT_MVVM_API QEXTMvvmUniqueIdGenerator
{
public:
    static QString generate();
};


#endif // _QEXTMVVMUNIQUEIDGENERATOR_H
