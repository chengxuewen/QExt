// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_CORE_UNIQUEIDGENERATOR_H
#define MVVM_CORE_UNIQUEIDGENERATOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmTypes.h>

namespace ModelView {

//! Provides generation of unique QExtMvvmSessionItem identifier.

//! In the future might be turned to singleton to keep track of all generated identifier
//! and make sure, that QExtMvvmSessionItem identifiers loaded from disk, are different from those
//! generated during a dynamic session. For the moment though, we rely on zero-probability of
//! such event.

class QEXT_MVVM_API QExtMvvmUniqueIdGenerator {
public:
    static QExtMvvmIdentifierType generate();
};

} // namespace ModelView

#endif // MVVM_CORE_UNIQUEIDGENERATOR_H
