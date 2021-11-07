#ifndef _QEXTMVVMCOPYITEMCOMMAND_P_H
#define _QEXTMVVMCOPYITEMCOMMAND_P_H

#include <qextMvvmAbstractItemCommand_p.h>
#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmPath.h>

#include <QSharedPointer>

class QEXTMvvmCopyItemCommand;
class QEXT_MVVM_API QEXTMvvmCopyItemCommandPrivate : public QEXTMvvmAbstractItemCommandPrivate
{
public:
    explicit QEXTMvvmCopyItemCommandPrivate(QEXTMvvmCopyItemCommand *q);
    ~QEXTMvvmCopyItemCommandPrivate() QEXT_DECL_OVERRIDE;

    QEXTMvvmTagRow m_tagrow;
    QEXTMvvmPath m_itempath;
    QSharedPointer<QEXTMvvmItemBackupStrategy> m_itemBackupStrategy;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmCopyItemCommandPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmCopyItemCommand)
};

#endif // _QEXTMVVMCOPYITEMCOMMAND_P_H
