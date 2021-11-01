#ifndef _QEXTMVVMCOMMANDUTILS_H
#define _QEXTMVVMCOMMANDUTILS_H

#include <memory>
#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmItemCopyStrategy.h>

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Creates strategy suitable for item saving/restoring. Restored item will have same identifiers
//! as original.

QEXT_MVVM_API std::unique_ptr<QEXTMvvmItemBackupStrategy> CreateItemBackupStrategy(const QEXTMvvmSessionModel* model);

//! Returns strategy for item copying. Identifiers of the copy will be different from identifiers
//! of the original.

QEXT_MVVM_API std::unique_ptr<QEXTMvvmItemCopyStrategy> CreateItemCopyStrategy(const QEXTMvvmSessionModel* model);

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDUTILS_H
