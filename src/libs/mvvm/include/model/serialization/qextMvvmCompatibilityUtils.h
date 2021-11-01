#ifndef _QEXTMVVMCOMPATIBILITYUTILS_H
#define _QEXTMVVMCOMPATIBILITYUTILS_H

//! @file compatibilityutils.h
//! @brief Place for utils to fix back compatibility of serialized projects.

#include <memory>
#include <qextMvvmGlobal.h>

namespace ModelView
{

    class QEXTMvvmSessionItemData;
    class QEXTMvvmSessionItemContainer;
    class QEXTMvvmTagInfo;

    namespace Compatibility
    {

//! Returns `true` if given QEXTMvvmTagInfo is compatible with given container.
//! See explanations in the code.

        QEXT_MVVM_API
        bool IsCompatibleUniversalTag(const QEXTMvvmSessionItemContainer &container, const QEXTMvvmTagInfo &taginfo);

//! Returns `true` if given QEXTMvvmTagInfo is a single property tag which is compatible with given
//! container. See more explanations in the code.

        QEXT_MVVM_API
        bool IsCompatibleSinglePropertyTag(const QEXTMvvmSessionItemContainer &container, const QEXTMvvmTagInfo &taginfo);

//! Returns `true` if given QEXTMvvmTagInfo is a tag from QEXTMvvmGroupItem which is compatible with given
//! container. See more explanations in the code.

        QEXT_MVVM_API bool IsCompatibleGroupTag(const QEXTMvvmSessionItemContainer &container,
                                                const QEXTMvvmTagInfo &taginfo);

    } // namespace Compatibility

} // namespace ModelView

#endif // _QEXTMVVMCOMPATIBILITYUTILS_H
