#ifndef _QEXTMVVMCOMMANDUTILS_H
#define _QEXTMVVMCOMMANDUTILS_H

#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmItemCopyStrategy.h>

#include <QSharedPointer>

class QEXTMvvmModel;
struct QEXT_MVVM_API QEXTMvvmCommandUtils
{
    //! Creates strategy suitable for item saving/restoring. Restored item will have same identifiers
    //! as original.

    static QEXTMvvmItemBackupStrategy *createItemBackupStrategy(const QEXTMvvmModel *model);

    //! Returns strategy for item copying. Identifiers of the copy will be different from identifiers
    //! of the original.

    static QEXTMvvmItemCopyStrategy *createItemCopyStrategy(const QEXTMvvmModel *model);
};

#endif // _QEXTMVVMCOMMANDUTILS_H
