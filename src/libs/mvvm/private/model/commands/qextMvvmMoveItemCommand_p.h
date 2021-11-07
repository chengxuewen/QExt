#ifndef _QEXTMVVMMOVEITEMCOMMAND_P_H
#define _QEXTMVVMMOVEITEMCOMMAND_P_H

#include <qextMvvmAbstractItemCommand_p.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmPath.h>

class QEXTMvvmMoveItemCommand;
class QEXT_MVVM_API QEXTMvvmMoveItemCommandPrivate : public QEXTMvvmAbstractItemCommandPrivate
{
public:
    explicit QEXTMvvmMoveItemCommandPrivate(QEXTMvvmMoveItemCommand *q);
    ~QEXTMvvmMoveItemCommandPrivate() QEXT_DECL_OVERRIDE;

    QEXTMvvmTagRow m_targetTagRow;
    QEXTMvvmPath m_targetParentPath;
    QEXTMvvmPath m_originalParentPath;
    QEXTMvvmTagRow m_originalTagRow;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmMoveItemCommandPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmMoveItemCommand)
};

#endif // _QEXTMVVMMOVEITEMCOMMAND_P_H
