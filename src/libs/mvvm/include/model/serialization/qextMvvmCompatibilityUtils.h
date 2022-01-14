#ifndef _QEXTMVVMSERIALIZATIONCOMPATIBILITYUTILS_H
#define _QEXTMVVMSERIALIZATIONCOMPATIBILITYUTILS_H

//! @file compatibilityutils.h
//! @brief Place for utils to fix back compatibility of serialized projects.

#include <memory>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItemData;
class QEXTMvvmSessionItemContainer;
class QEXTMvvmTagInfo;

namespace QEXTMvvmCompatibility
{

//! Returns `true` if given TagInfo is compatible with given container.
//! See explanations in the code.

QEXT_MVVM_API
bool IsCompatibleUniversalTag(const QEXTMvvmSessionItemContainer& container, const QEXTMvvmTagInfo& taginfo);

//! Returns `true` if given TagInfo is a single property tag which is compatible with given
//! container. See more explanations in the code.

QEXT_MVVM_API
bool IsCompatibleSinglePropertyTag(const QEXTMvvmSessionItemContainer& container, const QEXTMvvmTagInfo& taginfo);

//! Returns `true` if given TagInfo is a tag from GroupItem which is compatible with given
//! container. See more explanations in the code.

QEXT_MVVM_API bool IsCompatibleGroupTag(const QEXTMvvmSessionItemContainer& container,
                                            const QEXTMvvmTagInfo& taginfo);

} // namespace Compatibility

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONCOMPATIBILITYUTILS_H
