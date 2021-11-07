#ifndef _QEXTMVVMREMOVEITEMCOMMAND_P_H
#define _QEXTMVVMREMOVEITEMCOMMAND_P_H

#include <qextMvvmAbstractItemCommand_p.h>
#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmPath.h>

#include <QSharedPointer>

class QEXTMvvmRemoveItemCommand;
class QEXT_MVVM_API QEXTMvvmRemoveItemCommandPrivate : public QEXTMvvmAbstractItemCommandPrivate
{
public:
    explicit QEXTMvvmRemoveItemCommandPrivate(QEXTMvvmRemoveItemCommand *q);
    ~QEXTMvvmRemoveItemCommandPrivate() QEXT_DECL_OVERRIDE;

    QEXTMvvmTagRow m_tagrow;
    QEXTMvvmPath m_itemPath;
    QSharedPointer<QEXTMvvmItemBackupStrategy> m_backupStrategy;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmRemoveItemCommandPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmRemoveItemCommand)
};

#endif // _QEXTMVVMREMOVEITEMCOMMAND_P_H
