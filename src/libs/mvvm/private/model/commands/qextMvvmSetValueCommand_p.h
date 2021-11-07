#ifndef _QEXTMVVMSETVALUECOMMAND_P_H
#define _QEXTMVVMSETVALUECOMMAND_P_H

#include <qextMvvmAbstractItemCommand_p.h>
#include <qextMvvmPath.h>

#include <QVariant>

class QEXTMvvmSetValueCommand;
class QEXT_MVVM_API QEXTMvvmSetValueCommandPrivate : public QEXTMvvmAbstractItemCommandPrivate
{
public:
    explicit QEXTMvvmSetValueCommandPrivate(QEXTMvvmSetValueCommand *q);
    ~QEXTMvvmSetValueCommandPrivate() QEXT_DECL_OVERRIDE;

    QVariant m_value; //! Value to set as a result of command execution.
    int m_role;
    QEXTMvvmPath m_itemPath;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmSetValueCommandPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmSetValueCommand)
};

#endif // _QEXTMVVMSETVALUECOMMAND_P_H
