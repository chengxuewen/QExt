#ifndef _QEXTMVVMCOMMANDADAPTER_H
#define _QEXTMVVMCOMMANDADAPTER_H

#include <qextMvvmGlobal.h>

#include <QUndoCommand>
#include <QSharedPointer>

class QEXTMvvmAbstractItemCommand;

//! Adapter to execute our commands within Qt undo/redo framework.

class QEXT_MVVM_API QEXTCommandAdapter : public QUndoCommand
{
public:
    QEXTCommandAdapter(const QSharedPointer<QEXTMvvmAbstractItemCommand> &command);
    ~QEXTCommandAdapter() QEXT_DECL_OVERRIDE;

    void undo() QEXT_DECL_OVERRIDE;
    void redo() QEXT_DECL_OVERRIDE;

private:
    QSharedPointer<QEXTMvvmAbstractItemCommand> m_command;
};


#endif // _QEXTMVVMCOMMANDADAPTER_H
