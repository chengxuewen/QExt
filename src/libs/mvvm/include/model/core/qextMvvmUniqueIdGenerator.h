#ifndef _QEXTMVVMMODELUNIQUEIDGENERATOR_H
#define _QEXTMVVMMODELUNIQUEIDGENERATOR_H

#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

/*!
@class QEXTMvvmUniqueIdGenerator
@brief Provides generation of unique QEXTMvvmSessionItem itentifier.

In the future might be turned to singleton to keep track of all generated identifier
and make sure, that QEXTMvvmSessionItem identifiers loaded from disk, are different from those
generated during dynamic session. For the moment though, we rely on zero-probability of
such event.
*/

class QEXT_MVVM_API QEXTMvvmUniqueIdGenerator
{
public:
    static identifier_type generate();
};

} // namespace ModelView

#endif // _QEXTMVVMMODELUNIQUEIDGENERATOR_H
