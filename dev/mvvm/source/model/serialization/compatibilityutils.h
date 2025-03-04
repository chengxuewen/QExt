// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_COMPATIBILITYUTILS_H
#define MVVM_SERIALIZATION_COMPATIBILITYUTILS_H

//! @file compatibilityutils.h
//! @brief Place for utils to fix back compatibility of serialized projects.

#include <qextMvvmGlobal.h>

namespace ModelView {

class QExtMvvmSessionItemContainer;
class QExtMvvmTagInfo;

namespace Compatibility {

//! Returns `true` if given QExtMvvmTagInfo is compatible with given container.
//! See explanations in the code.

QEXT_MVVM_API
bool IsCompatibleUniversalTag(const QExtMvvmSessionItemContainer& container, const QExtMvvmTagInfo& taginfo);

//! Returns `true` if given QExtMvvmTagInfo is a single property tag which is compatible with given
//! container. See more explanations in the code.

QEXT_MVVM_API
bool IsCompatibleSinglePropertyTag(const QExtMvvmSessionItemContainer& container, const QExtMvvmTagInfo& taginfo);

//! Returns `true` if given QExtMvvmTagInfo is a tag from QExtMvvmGroupItem which is compatible with given
//! container. See more explanations in the code.

QEXT_MVVM_API bool IsCompatibleGroupTag(const QExtMvvmSessionItemContainer& container,
                                            const QExtMvvmTagInfo& taginfo);

} // namespace Compatibility

} // namespace ModelView

#endif // MVVM_SERIALIZATION_COMPATIBILITYUTILS_H
